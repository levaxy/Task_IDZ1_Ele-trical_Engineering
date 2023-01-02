#pragma once
#include"..\Konturs\Konturs.h"
#include"..\Shared.h"
vector<vector<Rational>> MakeMatrixLowsKirhgoff(const vector<Branch>& UnkBr, vector<Knot>& UnkKn, vector<Kontur>& Ind);

vector<vector<Rational>>FirstLKcoefs(const vector<Knot>& knots, const int& CountUnkCarr);

vector<vector<Rational>>SecondLKcoefs(const vector<Kontur>& konturs, const int& UnkCount);