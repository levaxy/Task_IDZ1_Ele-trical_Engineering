#pragma once
#include"..\Konturs\Konturs.h"

vector<vector<Rational>> MKCcoefs(const vector<Kontur>& SourseCurrent, vector<Kontur>& Independ);

vector<vector<Rational>> MakeMatrixMKC(vector<Knot>& UnkKn, vector<Kontur>& Ind, vector<Kontur>& SourCur);