#pragma once
#include<iostream>
using namespace std;
long long NOD(long long num, long long denom) ;
class Rational {
public:
	Rational();
	Rational(const Rational& other) ;

	Rational(long long numerator, long long denominator);
	long long Numerator() const;
	long long Denominator() const;
	const Rational& operator = (const Rational& Other);
	const Rational& operator = (const int& Other);
	~Rational();

	bool operator==(const Rational& rhs);
	bool operator!=(const Rational& rhs);
	bool operator!=(const int& rhs);
	bool operator==(const int& rhs);
	bool operator<(const Rational& rhs);
	bool operator<(const int& rhs);
	bool operator>(const Rational& rhs);
	bool operator>(const int& rhs);
	istream& operator>>(istream& input);
	Rational operator-();
private:
	long long Numer;
	long long Denom;
};
Rational TransformDoubletoRational(const double& d);
Rational operator^(const Rational& lhs, int Stepen) ;
ostream& operator<<(ostream& output, const Rational& rhs) ;
Rational operator/(const Rational& lhs, const Rational& rhs) ;
Rational operator+(const Rational& lhs, const Rational& rhs) ;
Rational operator*(const Rational& lhs, const Rational& rhs) ;
Rational operator-(const Rational& lhs, const Rational& rhs) ;
void operator-=(Rational& lhs, const Rational& rhs);
void operator+=(Rational& lhs, const Rational& rhs);
//Rational operator-(const Rational& rhs) {
//	return { rhs.Numerator()*(-1), rhs.Denominator() };
//}
