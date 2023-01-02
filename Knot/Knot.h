#pragma once
#include"..\Branch\Branch.h"
#include<vector>
class Knot
{
public:
	Knot(const Knot& Other);
	Knot() ;
	Knot(const string& design) ;
	string GetName()const;
	void SetBranches(const Branch& new_branch);
	void SetUnkBranches(const Branch& new_unk_branch);
	void SetFamBranches(const Branch& new_fam_branch);
	void EraseUnk(const string& namebr);
	vector<Branch> GetBranches()const;
	vector<Branch> GetUnkBranches()const;
	vector<Branch> GetFamBranches()const;
	~Knot();
	const Knot& operator = (const Knot& Other);
	vector<Branch> FamBrnchs;
	vector<Branch> Unkbrnchs;
	Rational Potention;
private:
	string name;
	vector<Branch> branches;
};

bool operator==(const Knot& lhs, const Knot& rhs);
bool operator<(const Knot& lhs, const Knot& rhs);