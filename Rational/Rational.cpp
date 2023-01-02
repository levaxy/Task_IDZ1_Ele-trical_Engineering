#include<string>
#include<iostream>
#include<sstream>
#include"Rational.h"
long long NOD(long long num, long long denom) {
	long long a = abs(num), b = abs(denom);
	while (a > 0 && b > 0) {
		if (a > b) {
			a %= b;
		}
		else {
			b %= a;
		}

	}
	return a + b;
}

Rational::Rational() {
		Numer = 0;
		Denom = 1;
}
Rational::Rational(const Rational& other) {
		this->Numer = other.Numer;
		this->Denom = other.Denom;
}

Rational::Rational(long long numerator, long long denominator) {
		if (denominator <= 0) {
			//throw invalid_argument("Invalid argument");
			denominator *= -1;
			numerator *= -1;
		}
		if (numerator == 0) {
			Numer = 0;
			Denom = 1;
		}
		else {
			long long nod = NOD(numerator, denominator);
			Numer = numerator / nod;
			Denom = denominator / nod;
			if (Denom < 0) {
				Numer *= -1;
				Denom *= -1;
			}
		}
}
long long Rational::Numerator() const {
		return Numer;
}
long long Rational::Denominator() const {
		return Denom;
}
const Rational& Rational::operator = (const Rational& Other) {
		this->Denom = Other.Denom;
		this->Numer = Other.Numer;
		return *this;
}
const Rational& Rational:: operator = (const int& Other) {
		this->Denom = 1;
		this->Numer = Other;
		return *this;
}
Rational::~Rational() {
		Numer = NULL;
		Denom = NULL;
}

bool Rational::	operator==(const Rational& rhs) {
		return this->Numerator() * rhs.Denominator() == rhs.Numerator() * this->Denominator();
}
bool Rational:: operator!=(const Rational& rhs) {
		return this->Numerator() * rhs.Denominator() != rhs.Numerator() * this->Denominator();
}
bool Rational::	operator!=(const int& rhs) {
		return this->Numerator() != (long long)rhs * this->Denominator();
}
bool Rational::	operator==(const int& rhs) {
		return this->Numerator() == (long long)rhs * this->Denominator();
}
bool Rational::	 operator<(const Rational& rhs) {
		return this->Numerator() * rhs.Denominator() < rhs.Numerator() * this->Denominator();
}
bool Rational::	 operator<(const int& rhs) {
		return this->Numerator() < rhs * this->Denominator();
}
bool Rational::	 operator>(const Rational& rhs) {
		return this->Numerator() * rhs.Denominator() > rhs.Numerator() * this->Denominator();
}
bool Rational::	operator>(const int& rhs) {
		return this->Numerator() > rhs * this->Denominator();
}
istream& Rational::operator>>(istream& input) {
		long long n, d;
		char c;
		if (input) {
			input >> n >> c >> d;
			if (input) {
				if (c == '/') {
					this->Numer = n;
					this->Denom = d;
				}
				else {
					input.setstate(ios_base::failbit);
				}
			}
			return input;
		}
}
Rational Rational::operator-() {
		return { this->Numerator() * (-1), this->Denominator() };
}



Rational operator^(const Rational& lhs, int Stepen) {
	long long Numerator, Denominator, mult = 1;
	if (lhs.Numerator() == 0)
		return lhs;
	if (Stepen < 0) {
		Stepen *= -1;
		if (lhs.Numerator() < 0)
			mult = -1;
		Numerator = mult * lhs.Denominator();
		Denominator = mult * lhs.Numerator();
	}
	else {
		Numerator = lhs.Numerator();
		Denominator = lhs.Denominator();
	}
	for (size_t i = 1; i < Stepen; i++)
	{
		Numerator *= Numerator;
		Denominator *= Denominator;
	}

	return { Numerator,Denominator };
}
ostream& operator<<(ostream& output, const Rational& rhs) {
	if (rhs.Denominator() == 1)
		output << rhs.Numerator();
	else {
		stringstream ss;
		ss << rhs.Numerator() << '/' << rhs.Denominator();
		output << ss.str();
	}
	return output;
}
Rational operator/(const Rational& lhs, const Rational& rhs) {
	if (rhs.Numerator() == 0) {
		throw domain_error("");
	}
	return { lhs.Numerator() * rhs.Denominator(),lhs.Denominator() * rhs.Numerator() };
}
Rational operator+(const Rational& lhs, const Rational& rhs) {
	return { lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
		lhs.Denominator() * rhs.Denominator() };
}
Rational operator*(const Rational& lhs, const Rational& rhs) {
	return { lhs.Numerator() * rhs.Numerator(),lhs.Denominator() * rhs.Denominator() };
}
Rational operator-(const Rational& lhs, const Rational& rhs) {
	return { lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
		lhs.Denominator() * rhs.Denominator() };
}
void operator-=(Rational& lhs, const Rational& rhs) {
	lhs = lhs - rhs;
}
void operator+=(Rational& lhs, const Rational& rhs) {
	lhs = lhs + rhs;
}
//Rational operator-(const Rational& rhs) {
//	return { rhs.Numerator()*(-1), rhs.Denominator() };
//}
Rational TransformDoubletoRational(const double& d) {
	double I = (int)d;
	Rational Int((long long)d, 1), Float((long long)((d - I) * 1000000000000000), 1000000000000000);
	return Int + Float;
}