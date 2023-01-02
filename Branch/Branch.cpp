
#include"Branch.h"



Branch::Branch(const string& numb, const string& begkn, const string& endkn, const Rational& e, const Rational& j, const Rational& r) {
	number = numb;
	E = e;
	J = j;
	R = r;

	if (J != 0) {
		I = J;
		SourseCurrent = true;
	}
	beg = begkn;
	end = endkn;
}
Branch::Branch() {}
Branch::Branch(const Branch& other) {
	this->beg = other.beg;
	this->CountUse = other.CountUse;
	this->E = other.E;
	this->end = other.end;
	this->I = other.I;
	this->J = other.J;
	this->IsFolowKontur = other.IsFolowKontur;
	this->knotnext = other.knotnext;
	this->number = other.number;
	this->NumberUnk = other.NumberUnk;
	this->R = other.R;
	this->SourseCurrent = other.SourseCurrent;
	this->IsIndependent = other.IsIndependent;
}
string Branch::GetBegin()const {
	return beg;
}
string Branch::GetEnd()const {
	return end;
}
Rational Branch::GE()const {
	return E;
}
Rational Branch::GJ()const {
	return J;
}
Rational Branch::GR()const {
	return R;
}
Rational Branch::GI()const {
	return I;
}
int Branch::G_NU()const {
	return NumberUnk;
}
string Branch::G_N()const {
	return number;
}
bool Branch::G_SC()const {
	return SourseCurrent;
}
void Branch::SetNumberUnk(const int& n) {
	NumberUnk = n;
}
void Branch::ChangeI(const Rational& new_I) {
	I = new_I;
	SourseCurrent = true;
}
void Branch::IncrUse() {
	CountUse++;
}
bool Branch::GetIsFolow()const {
	return IsFolowKontur;
}
void Branch::SetIsFollow(const bool& b) {
	IsFolowKontur = b;
}
bool Branch::GetIsIndepend()const {
	return IsIndependent;
}
void Branch::SetIsIndepend(const bool& b) {
	IsIndependent = b;
}
int Branch::GetCountUse()const {
	return CountUse;
}
void Branch::SetEnd(const string& NewEnd) {
	end = NewEnd;
}
void Branch::SetBegin(const string& Newbeg) {
	beg = Newbeg;
}
bool operator<(const Branch& lhs, const Branch& rhs) {
	return lhs.G_NU() < rhs.G_NU();
}
bool operator==(const Branch& lhs, const Branch& rhs) {
	return lhs.G_N() == rhs.G_N();
}
size_t Count(const vector<Branch>& b) {
	size_t n = 0;
	for (const Branch& br : b) {
		if (br.GetCountUse() == 0)
			n++;
	}
	return n;
}

//void EnsureNextSymbolAndSkip(istream& input){
//	if (input.peek() != ',') {
//		stringstream ss;
//		ss << "excepted ',' but has: " << input.peek() << ' ' << "branch has not created!";
//		throw runtime_error(ss.str());
//	}
//	input.ignore(1);
//}
//istream& operator>>(istream& input, Branch& branch) {
//	if(input){
//		string begin, end;
//		Rational e,j,r;
//		string number;
//		input >> number;
//		EnsureNextSymbolAndSkip(input);
//		getline(input, begin, ',');
//		getline(input,end,',');
//		input>>e;
//		EnsureNextSymbolAndSkip(input);
//		input >> j;
//		EnsureNextSymbolAndSkip(input);
//		input >> r;
//		if(input){
//			branch=Branch(number,begin,end,e,j,r);
//		}else{
//			stringstream ss;
//			ss << "The input data does not match format! "<< "Branch has not created!";
//			throw runtime_error(ss.str());
//		}
//
//	}
//	return input;
//}