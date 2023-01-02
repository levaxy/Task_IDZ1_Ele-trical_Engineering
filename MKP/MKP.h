#pragma once
#include"\Users\Admin\source\repos\Task_IDZ1_Eleñtrical_Engineering\Knot\Knot.h"
void EquTrans(vector<Knot>& knots, vector<Branch>& unkbr);

void MKPcoefs(vector<Knot>& knots, vector<vector<Rational>>& Poten);

void MKP(vector<Knot> knots, vector<Branch> unkbr, vector<Branch> Allbr);