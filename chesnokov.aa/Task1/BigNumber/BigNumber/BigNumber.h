#pragma once
#include <string>
#include <iostream>
/*
 * ������� (32+32 ���) ����������� �����
 * �������/������ ����� � ������� ��������� ��������� 16 ��� 2
 */
enum PrintType
{
	Binar,
	Hex
};
class BigNumber
{
private:
	int m_upper_part;  // ������� ����� ����� (32 ���)
	int m_lower_part;  // ������� ����� ����� (32 ���)
	PrintType pt;      // ����� ������� �������� �� ����� (� �������� 2 ��� 16)

public:
	// ��������� ������� ���������� � 0 (�� 0 �� 63)
    // ���������� ��� � posotion ������� 
	bool GetBit(int position) const;
	// ������������� �������� b � ��������� �������
	void SetBit(int position, bool b);
	// ������������� ��� ������
	void SetPrintType(PrintType _pt) { pt = _pt; }
private:
	// ������������
	void HalfAdder(
		bool inA,       // ���� �
		bool inB,       // ���� B
		bool& outSum,   // ����� �����
		bool& outC      // ����� ������� �������
	);   
	// ������ ��������
	void Adder(
		bool inC,      // ���� �������� �������
		bool inA,
		bool inB,
		bool& outSum,
		bool& outC
	);
	// ���������� ��������� ����� (-num)
	BigNumber Invert() const;
	// ������������� ��������
public:
	// �������� ���������
	friend bool operator==(const BigNumber numL, const BigNumber numR);
	friend bool operator!=(const BigNumber numL, const BigNumber numR);
	BigNumber operator+(const BigNumber& num);
	BigNumber operator-(const BigNumber& num);
	bool operator<(const BigNumber num);
	bool operator>(const BigNumber num);
	bool operator<=(const BigNumber num) { return !(*this > num); }
	bool operator>=(const BigNumber num) { return !(*this < num); }

	// ���������� ��������� ���� ��������
	BigNumber operator*(const BigNumber& num);
	// ���������� ������� ����������
	BigNumber operator/(const BigNumber& num);
	BigNumber& operator=(const BigNumber& num);
	friend std::ostream& operator<< (std::ostream& out, const BigNumber& num);

public:
	//������������
	BigNumber();
	// ������������ �� ���������� ������������� ����� � 16-�� �������
	// ������������� ����� ����� �����������
	BigNumber(std::string HexNum); 
	~BigNumber();
};

std::ostream& operator<< (std::ostream& out, const BigNumber& num);
bool operator==(const BigNumber numL, const BigNumber numR);
bool operator!=(const BigNumber numL, const BigNumber numR);
