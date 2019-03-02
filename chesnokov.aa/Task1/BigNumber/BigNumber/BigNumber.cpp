#include "BigNumber.h"
#include <limits>
#include "math.h"

// ����������� ���
bool XOR(bool a, bool b)
{
	return (a || b) && (!(a && b));
}

bool BigNumber::GetBit(int position) const
{
	if (position <= 31)  // ���� ����������� ������� ����� 
	{
		// �������� �������� �� position ������� ������
		// ��������� � ����������� ����� � ������ ���� 0000...001
		// ������ �������� ���������� ����
		return (m_lower_part >> position) & 1;
	}
	else if (position <= 63)  // ���� ����������� ������� ����� 
	{
		// ���������� �� ������� ������
		return (m_upper_part >> (position - 32)) & 1;
	}
	// ����� ��� ��� ����� �������
	return false;
}

// ��� ������ �� ������� �����, ��� �� ����������
void BigNumber::SetBit(int position, bool b)
{
	if (position <= 31)   //������� �����
	{
		if (b)  // ���� ����� ���������� 1
		{
			// ��������� ��� ����� � ������ ���� 000..00100..0
			// ��� 1 �������� ������� position � ���������� ��������� 1 � ������ �����
			m_lower_part = m_lower_part | (int) pow(2, position);
		}
		else // ���� ����� ���������� 0
		{
			// ��������� � ����� � ������ ���� 111..11011..111
			// ��� 0 ����� � ������� position ��������� 0 � ������ �����
			m_lower_part = m_lower_part & ( std::numeric_limits<int>::max() - (int) pow(2,position));
		}
	}
	else if (position <= 63)  
	{
		if (b)  
		{
			m_upper_part = m_upper_part | (int)pow(2, position - 32);
		}
		else 
		{
			m_upper_part = m_upper_part & (std::numeric_limits<int>::max() - (int)pow(2, position - 32));
		}
	}
}

void BigNumber::HalfAdder(bool inA, bool inB, bool & outSum, bool & outC)
{
	outSum = XOR(inA, inB);
	outC = inA && inB;
}

void BigNumber::Adder(bool inC, bool inA, bool inB, bool & outSum, bool & outC)
{
	bool _outSum, _outC1, _outC2;
	HalfAdder(inA, inB, _outSum, _outC1);
	HalfAdder(inC, _outSum, outSum, _outC2);
	outC = _outC1 || _outC2;
}

BigNumber BigNumber::Invert() const
{
	BigNumber res;
	for (int i = 0; i < 64; i++)
	{
		// ����������� ��� ����
		res.SetBit(i, !(this->GetBit(i)));
	}
	res = res + BigNumber("1");  // �������� �� 1
	return res;
}

BigNumber BigNumber::operator+(const BigNumber & num)
{
	BigNumber res;
	bool carry = false;   // ������� �������
	bool sum = false;     // �������� ��� ��������� ����
	for (int i = 0; i < 64; i++)
	{
		Adder(carry, this->GetBit(i), num.GetBit(i), sum, carry);
		res.SetBit(i, sum);
	}
	return res;
}

BigNumber BigNumber::operator-(const BigNumber & num)
{
	BigNumber res;
	res = *this + num.Invert();
	return res;
}

bool BigNumber::operator<(const BigNumber num)
{
	for (int i = 63; i >= 0; i--)
	{
		if (this->GetBit(i) < num.GetBit(i)) return true;
		else if (this->GetBit(i) > num.GetBit(i)) return false;
	}
	return false;
}

bool BigNumber::operator>(const BigNumber num)
{

	for (int i = 63; i >= 0; i--)
	{
		if (this->GetBit(i) > num.GetBit(i)) return true;
		else if (this->GetBit(i) < num.GetBit(i)) return false;
	}
	return false;
}

BigNumber BigNumber::operator*(const BigNumber & num)
{
	// ��������� �� 0
	if (((*this) == BigNumber("0")) || (num == BigNumber("0"))) return BigNumber("0");
	BigNumber i("1"), res("0");
	res = *this;
	for (; i < num; i = i + BigNumber("1"))
	{
		res = res + (*this);
	}
	return res;
}

BigNumber BigNumber::operator/(const BigNumber & num)
{
	if (num == BigNumber("0")) throw "Dividing by zero exception";
	BigNumber res("0");   // c������
	BigNumber tmp;
	tmp = *this;
	while (tmp >= num)
	{
		tmp = tmp - num;
		res = res + BigNumber("1");
	}
	return res;
}

BigNumber & BigNumber::operator=(const BigNumber & num)
{
	// ������ ����������� ��������������� ����� �� ������ ����� � ������
	for (int i = 0; i < 64; i++)
	{
		SetBit(i, num.GetBit(i));
	}
	return *this;
}

BigNumber::BigNumber()
{
	m_lower_part = 0;
	m_upper_part = 0;
	pt = Hex;
}

BigNumber::BigNumber(std::string HexNum)
{
	int symb; // ������� ������ ���������� ������
	// �������� ��� ����
	m_lower_part = m_upper_part = 0;
	pt = Hex;
	int len = HexNum.length();
	for (int i = len - 1; i >= 0; i--) 
		//�������� �� ���� �������� � ������ � �������� �������
	{
		// ������� ����� (��������� � ���������� �����)
		if (HexNum[i] <= '9' && HexNum[i] >= '0') symb = HexNum[i] - '0';
		else if (HexNum[i] <= 'F' && HexNum[i] >= 'A') symb = HexNum[i] - 'A' + 10;
		else symb = 0;  // �� �������� 16-����� ��������
		// ��������� � ��������
		int j = 0;
		while (symb > 0)
		{
			SetBit((len - i - 1) * 4 + j, symb % 2);
			j++;
			symb /= 2;
		} 
	}
}


BigNumber::~BigNumber()
{
	m_lower_part = m_upper_part = 0;
}

// ����� �� �����
std::ostream& operator<< (std::ostream& out, const BigNumber& num)
{
	if (num.m_lower_part == 0 && num.m_upper_part == 0)
	{
		out << 0;
		return out;
	}
	int i = 63;
	switch (num.pt)
	{
	case (Binar):
		// ���������� ���������� ����
		
		while (!num.GetBit(i)) i--;
		// ������ ������ �� ��������
		out << num.GetBit(i);
		i--;
		for (; i >= 0; i--)
		{
			if (i % 4 == 3)
			{
				out << " " << num.GetBit(i);
			}
			else
			{
				out << num.GetBit(i);
			}
		}
		break;
	case (Hex):
		// ������� � Hex ����� �������� ��������� ������ (����������)
		// ���������� ���������� ������� [0000]
		int tet,     // ������� ������, ������� � 1, ������ ������ (����� �� 8*2 = 16)
			offset,  // ������ �� ������ �������
			sum;     // ����� ������� ������� � ���������� �������������
		char ch;     // hex ����� ������� �������
		for (tet = 16; tet >= 1; tet--)
		{
			sum = 0;
			for (offset = 0; offset <= 3; offset++)
			{
				sum += (int) num.GetBit(tet * 4 - offset - 1);
			}
			if (sum) break;  // ���� ��������� ������� �� ������� ��������� �� ���������� 
		}
		// ������� ���������� �������
		for (; tet >= 1; tet--)
		{
			sum = 0;
			//����������� ���������� �������� ��������� �������
			for (offset = 0; offset <= 3; offset++)
			{
				if (num.GetBit(tet * 4 - offset - 1)) // ���� ��������� ��� �� ������
				{
					sum +=(int) pow(2, 3 - offset);
				}	
			}
			// ������� ��������������� hex ������
			if (sum >= 0 && sum <= 9)
			{
				ch = '0' + sum;
			}
			else
			{
				sum -= 10;
				ch = 'A' + sum;
			}
			out << ch;
		}
		break;
		default:
			break;
	}
	return out;
}

bool operator==(const BigNumber numL, const BigNumber numR)
{
	for (int i = 0; i < 64; i++)
	{
		if (numL.GetBit(i) != numR.GetBit(i))
		{
			return false;
		}
	}
	return true;
}

bool operator!=(const BigNumber numL, const BigNumber numR)
{
	return !(numL == numR);
}
