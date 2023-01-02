#pragma once
#include"..\Knot\Knot.h"
#include<sstream>
class Kontur
{
public:
	Kontur(const Kontur& other);
	Kontur(const vector<Branch>& brn, const string& Name);
	vector<Branch>GetBrnchs()const;
	string GetName()const;
private:
	string name = "";
	vector<Branch> brn;
};
vector<Kontur> SelectKonturs(vector<Knot>& knots, const bool& IsCurSourse);