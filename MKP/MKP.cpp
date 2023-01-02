#include"MKP.h"
#include"..\Shared.h"
#include<sstream>
#include<iterator>
#define DEBUG
void EquTrans(vector<Knot>& knots, vector<Branch>& unkbr) {
	//unkbr тоже преобразовываем
	cout << "ѕереносим источники Ёƒ—.\n\n";
	vector<Knot> ::iterator kn, k;
	vector<Branch>::iterator B, b, unbr;
	//for ( unbr = unkbr.begin(); unbr != unkbr.end(); unbr++){
	//	if((*unbr).GR()==0){
	//		unbr=unkbr.erase(unbr);
	//		unbr--;
	//	}
	//}
	for (k = knots.begin(); k != knots.end(); k++) {
		for (b = (*k).Unkbrnchs.begin(); b != (*k).Unkbrnchs.end();) {
			if ((*b).GR() == 0) {
				string Bname = (*b).G_N(), Bbegin = (*b).GetBegin(), Bend = (*b).GetEnd();
				Rational BE = (*b).GE();
				for (Branch& br : (*k).Unkbrnchs) {
					if (br.G_N() != Bname && br.GetBegin() != br.GetEnd()) {//идЄм по веткам этого узла и переносим Ёƒ—
						for (Branch& unbr : unkbr) {//в какую-то ветку переносим эдс, в неизвестных тоже делаем это
							if (unbr.G_N() == br.G_N()) {
								string oppk = (unbr.GetBegin() == (*k).GetName()) ? unbr.GetEnd() : unbr.GetBegin();
								for (Knot& opk : knots) {
									if (opk.GetName() == oppk) {
										for (Branch& Br : opk.Unkbrnchs) {
											if (Br.G_N() == unbr.G_N()) {
												if (br.GetBegin() == Bend || Bbegin == br.GetEnd()) {//вы€сн€ем взаимноую направленность веток
													br.E += BE;
													unbr.E += BE;
													Br.E += BE;
												}
												else {
													br.E -= BE;
													unbr.E -= BE;
													Br.E -= BE;
												}
												break;
											}
										}
										break;
									}
								}
								break;
							}
						}
					}
				}
				for (Branch& br : (*k).FamBrnchs) {//делаем тоже самое дл€ известных веток
					string oppk = (br.GetBegin() == (*k).GetName()) ? br.GetEnd() : br.GetBegin();
					if (br.GetBegin() != br.GetEnd())
						for (Knot& opk : knots) {
							if (opk.GetName() == oppk) {
								for (Branch& Br : opk.FamBrnchs) {
									if (Br.G_N() == br.G_N()) {
										if (br.GetBegin() == Bend || Bbegin == br.GetEnd()) {//вы€сн€ем взаимноую направленность веток
											br.E += BE;
											Br.E += BE;
										}
										else {
											br.E -= BE;
											Br.E -= BE;
										}
										break;
									}
								}
								break;
							}
						}
				}
				string nameDelk = (Bbegin == (*k).GetName()) ? Bend : Bbegin;//удал€ем узел
				for (kn = knots.begin(); kn != knots.end(); kn++) {
					if ((*kn).GetName() == nameDelk) {
						for (Branch& br : (*kn).Unkbrnchs)
						{
							if (br.G_N() != Bname) {
								for (Branch& unbr : unkbr) {
									if (unbr.G_N() == br.G_N()) {
										string oppk = (unbr.GetBegin() == (*kn).GetName()) ? unbr.GetEnd() : unbr.GetBegin();
										for (Knot& opk : knots) {
											if (opk.GetName() == oppk) {
												for (Branch& Br : opk.Unkbrnchs) {
													if (Br.G_N() == unbr.G_N()) {
														if (br.GetEnd() == (*kn).GetName()) {
															br.SetEnd((*k).GetName());
															unbr.SetEnd((*k).GetName());
															Br.SetEnd((*k).GetName());
														}
														else {
															unbr.SetBegin((*k).GetName());
															br.SetBegin((*k).GetName());
															Br.SetBegin((*k).GetName());
														}
														break;
													}
												}
												break;
											}
										}
										break;
									}
								}

#ifdef DEBUG
								if (br.GetBegin() != br.GetEnd()) {
									string bname = (*b).G_N();
									(*k).Unkbrnchs.push_back(br);
									for (b = (*k).Unkbrnchs.begin(); b != (*k).Unkbrnchs.end(); b++) {
										if ((*b).G_N() == bname)
											break;
									}
								}
#endif // DEBUG
#ifndef DEBUG
								if (br.GetBegin() != br.GetEnd())
									(*k).Unkbrnchs.push_back(br);
#endif // !DEBUG
							}
						}
						for (Branch& br : (*kn).FamBrnchs) {
							string oppk = (br.GetBegin() == (*kn).GetName()) ? br.GetEnd() : br.GetBegin();
							for (Knot& opk : knots) {
								if (opk.GetName() == oppk) {
									for (Branch& Br : opk.FamBrnchs) {
										if (Br.G_N() == br.G_N()) {
											if (br.GetEnd() == (*kn).GetName()) {
												br.SetEnd((*k).GetName());
												Br.SetEnd((*k).GetName());
											}
											else {
												br.SetBegin((*k).GetName());
												Br.SetBegin((*k).GetName());
											}
											if (br.GetBegin() != br.GetEnd())
												(*k).FamBrnchs.push_back(br);//присоединили ветки того узла к этому(ст€нул	
											break;
										}
									}
									break;
								}
							}
						}//теперь нужно удалить этот узел
#ifdef DEBUG
						string p = (*k).GetName(), bname = (*b).G_N();
						knots.erase(kn);
						for (k = knots.begin(); k != knots.end(); k++) {
							if ((*k).GetName() == p)
								break;
						}
						for (b = (*k).Unkbrnchs.begin(); b != (*k).Unkbrnchs.end(); b++) {
							if ((*b).G_N() == bname)
								break;
						}
#endif // DEBUG
#ifndef DEBUG
						knots.erase(kn);
#endif // !DEBUG

						break;
					}
				}
				if (b == ((*k).Unkbrnchs.end() - 1)) {
					(*k).Unkbrnchs.erase(b);
					break;
				}
				else
					b = (*k).Unkbrnchs.erase(b);
			}
			else
				b++;
		}
	}
}
void MKPcoefs(vector<Knot>& knots, vector<vector<Rational>>& Poten) {
	int counteq = knots.size() - 1;
	for (size_t Equ = 0; Equ < counteq; Equ++) {
		string equation = knots[Equ].GetName() + ": ";
		for (const Branch& b : knots[Equ].GetUnkBranches()) {
			string oppkn, fequ;
			string N = b.G_N();
			stringstream n;
			n << N;
			n.ignore(1);
			n >> N;
			Poten[Equ][Equ] -= b.GR() ^ (-1);
			if (knots[Equ].GetName() == b.GetEnd()) {
				equation += "+ (";
				Poten[Equ][counteq] -= b.GE() / b.GR();
				oppkn = b.GetBegin();
				equation += "ф" + oppkn + " - ф" + b.GetEnd();
				if (b.GE() < 0)
					equation += " - E'" + N;
				else if (b.GE() > 0)
					equation += " + E'" + N;
			}
			else {
				equation += " - (";
				Poten[Equ][counteq] += b.GE() / b.GR();
				oppkn = b.GetEnd();
				equation += "ф" + b.GetBegin() + " - ф" + oppkn;
				if (b.GE() < 0)
					equation += " - E'" + N;
				else if (b.GE() > 0)
					equation += " + E'" + N;
			}
			equation += ")g" + N;
			for (size_t coef = 0; coef < counteq; coef++) {
				if (knots[coef].GetName() == oppkn) {
					Poten[Equ][coef] += b.GR() ^ (-1);
					break;
				}
			}
		}
		for (const Branch& fb : knots[Equ].GetFamBranches()) {
			if (fb.GetBegin() == knots[Equ].GetName()) {
				Poten[Equ][counteq] += fb.GI();
				equation += " - " + fb.G_N();
			}
			else {
				Poten[Equ][counteq] -= fb.GI();
				equation += " + " + fb.G_N();
			}
		}
		equation += " = 0\n\n";
		cout << equation;
	}
	cout << "//////////////////////////////////////////////////////\n\n";
}

void MKP(vector<Knot> knots, vector<Branch> unkbr, vector<Branch> Allbr) {
	cout << "\t\t3. ћ”ѕ\n\n";
	EquTrans(knots, unkbr);//делаем преобразовани€ 
	PrintTrans(knots);
	ClearExcessUnkKnotsAndBranches(knots, unkbr, Allbr);//находим замкнутые ветки и рассчитываем
	size_t knotsz = knots.size();
	vector<vector<Rational>> Poten(knotsz - 1, vector<Rational>(knotsz));
	MKPcoefs(knots, Poten);//составл€ем уравнени€ отн-но потенциалов
	vector<Rational> Pot(knotsz - 1);
	gayss(Poten, Pot, knotsz - 1);//находим потенциалы
	for (size_t i = 0; i < knotsz - 1; i++)
		knots[i].Potention = Pot[i];//присвоим потенциалы узлам и вычислим токи
	for (Branch& b : unkbr) {
		if (b.GR() != 0) {
			string N = b.G_N();
			stringstream n;
			n << N;
			n.ignore(1);
			n >> N;
			string calcI = b.G_N() + " = (ф" + b.GetBegin() + " - ф" + b.GetEnd();
			stringstream ss;
			ss << "(";
			Rational I;
			if (b.GE() > 0) {
				calcI += " + E'" + N;
				ss << b.GE();
			}
			if (b.GE() < 0) {
				calcI += " - E'" + N;
				ss << b.GE();
			}
			calcI += ")g" + N;
			I += b.GE() / b.GR();
			for (const Knot& k : knots) {
				if (k.GetName() == b.GetBegin()) {
					I += k.Potention / b.GR();
					ss << " + (" << k.Potention << ")";
				}
				if (k.GetName() == b.GetEnd()) {
					I -= k.Potention / b.GR();
					ss << " - (" << k.Potention << ")";
				}
			}
			ss << "]*(" << (b.GR() ^ (-1)) << ")";
			cout << calcI << " = " << ss.str() << "\n\n";
			b.ChangeI(I);
			for (Branch& Ab : Allbr) {
				if (Ab.G_N() == b.G_N()) {
					Ab.ChangeI(I);
					break;
				}
			}
		}
	}
	vector<Knot> NewKnot;
	for (const Branch& Ab : Allbr) {
		Knot kn1(Ab.GetBegin()), kn2(Ab.GetEnd());
		if (!Ab.G_SC()) {
			if (count(NewKnot.begin(), NewKnot.end(), kn1.GetName()) == 0) {
				kn1.SetUnkBranches(Ab);
				NewKnot.push_back(kn1);
			}
			else
				for (Knot& k : NewKnot) {
					if (k.GetName() == kn1.GetName())
						k.SetUnkBranches(Ab);
				}
			if (count(NewKnot.begin(), NewKnot.end(), kn2.GetName()) == 0) {
				kn2.SetUnkBranches(Ab);
				NewKnot.push_back(kn2);
			}
			else
				for (Knot& k : NewKnot) {
					if (k.GetName() == kn2.GetName())
						k.SetUnkBranches(Ab);
				}
		}
		else {
			if (count(NewKnot.begin(), NewKnot.end(), kn1.GetName()) == 0) {
				kn1.SetFamBranches(Ab);
				NewKnot.push_back(kn1);
			}
			else
				for (Knot& k : NewKnot) {
					if (k.GetName() == kn1.GetName())
						k.SetFamBranches(Ab);
				}
			if (count(NewKnot.begin(), NewKnot.end(), kn2.GetName()) == 0) {
				kn2.SetFamBranches(Ab);
				NewKnot.push_back(kn2);
			}
			else
				for (Knot& k : NewKnot) {
					if (k.GetName() == kn2.GetName())
						k.SetFamBranches(Ab);
				}
		}
	}
	ClearExcessUnkKnotsAndBranches(NewKnot, unkbr, Allbr);
	for (Branch& Ab : Allbr) {
		cout << Ab.G_N() << " = " << Ab.GI() << " = " << (double)Ab.GI().Numerator() / (double)Ab.GI().Denominator() << " A\n\n";
	}

}