#pragma once
#include"..\Task_IDZ1_Eleñtrical_Engineering\Knot\Knot.h"
#include<iterator>
void PrintSeparator();

void PrintTrans(const vector<Knot>& knots);

void PrintRes(const vector<Branch>& UnkCurBranch, const vector<Rational>& Unk);

void gayss(vector<vector<Rational>>& arrkoef, vector<Rational>& Branches, const int& n);

void PrintVector(const vector<vector<Rational>>& coefs);

void ConcVectors(vector<vector<Rational>>& v1, const vector<vector<Rational>>& v2);

void InputChain(vector<Knot>& AllKnot, vector<Branch>& AllBrnchs, vector<Branch>& UnkCurBranch, int& qbrch, int& qknt, int& CountUnknown);

void ClearExcessUnkKnotsAndBranches(vector<Knot>& knots, vector<Branch>& unkbr, vector<Branch>& Allbr);

vector<Knot> holdKnotsWithUnkBrnchs(const vector<Knot>& AllKnots);

void Compute1UnkCurrentbyFLK(Knot& knot, vector<Knot>& knots, vector<Branch>& UnkBr, vector<Branch>& Allbr);