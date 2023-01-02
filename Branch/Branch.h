#pragma once
#include"..\Rational\Rational.h"
#include<vector>
class Branch
{
public:
	Branch(const string& numb, const string& begkn, const string& endkn, const Rational& e, const Rational& j, const Rational& r);
	Branch();
	Branch(const Branch& other);
	string GetBegin()const;
	string GetEnd()const;
	Rational GE()const;
	Rational GJ()const;
	Rational GR()const;
	Rational GI()const;
	int G_NU()const;
	string G_N()const;
	bool G_SC()const;
	void SetNumberUnk(const int& n);
	void ChangeI(const Rational& new_I);
	void IncrUse();
	bool GetIsFolow()const;
	void SetIsFollow(const bool& b);
	bool GetIsIndepend()const;
	void SetIsIndepend(const bool& b);
	int GetCountUse()const;
	void SetEnd(const string& NewEnd);
	void SetBegin(const string& Newbeg);
	string knotnext;
	Rational E;
private:
	Rational J;
	Rational R;
	Rational I;
	string end;
	string beg;
	bool SourseCurrent = false;
	int NumberUnk = 0;
	string number = "";
	bool IsIndependent = false;
	bool IsFolowKontur = false;
	int CountUse = 0;
};
bool operator<(const Branch& lhs, const Branch& rhs);
bool operator==(const Branch& lhs, const Branch& rhs);
size_t Count(const vector<Branch>& b);