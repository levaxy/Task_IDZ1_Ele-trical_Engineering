#include"..\Branch\Branch.h"
#include"Knot.h"
Knot::Knot(const Knot& Other) {
	this->name = Other.name;
	this->branches = Other.branches;
	this->Unkbrnchs = Other.Unkbrnchs;
	this->FamBrnchs = Other.FamBrnchs;
	this->Potention = Other.Potention;
}
Knot::Knot() {}
Knot::Knot(const string& design) {
	name = design;
}
string Knot::GetName()const {
	return name;
}
void Knot::SetBranches(const Branch& new_branch) {
	branches.push_back(new_branch);
}
void Knot::SetUnkBranches(const Branch& new_unk_branch) {
	Unkbrnchs.push_back(new_unk_branch);
}
void Knot::SetFamBranches(const Branch& new_fam_branch) {
	FamBrnchs.push_back(new_fam_branch);
}
void Knot::EraseUnk(const string& namebr) {
	vector<Branch>::iterator unk;
	for (unk = Unkbrnchs.begin(); unk != Unkbrnchs.end(); unk++) {
		if ((*unk).G_N() == namebr) {
			Unkbrnchs.erase(unk);
			break;
		}
	}
}
vector<Branch> Knot::GetBranches()const {
	return branches;
}
vector<Branch> Knot::GetUnkBranches()const {
	return Unkbrnchs;
}
vector<Branch> Knot::GetFamBranches()const {
	return FamBrnchs;
}
Knot::~Knot() {
	name.clear();
	branches.clear();
	Unkbrnchs.clear();
	FamBrnchs.clear();
}
const Knot& Knot::operator = (const Knot& Other) {
	this->name = Other.name;
	this->branches = Other.branches;
	this->Unkbrnchs = Other.Unkbrnchs;
	this->FamBrnchs = Other.FamBrnchs;
	this->Potention = Other.Potention;
	return *this;
}

bool operator==(const Knot& lhs, const Knot& rhs) {
	return lhs.GetName() == rhs.GetName();
}
bool operator<(const Knot& lhs, const Knot& rhs) {
	return lhs.GetName() < rhs.GetName();
}