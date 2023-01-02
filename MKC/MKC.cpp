#include"MKC.h"
#include<sstream>

vector<vector<Rational>> MKCcoefs(const vector<Kontur>& SourseCurrent, vector<Kontur>& Independ) {
	cout << "Составляем уравнения по 2 ЗК для независимых контуров\n\n";
	size_t Size = Independ.size(), sizej = SourseCurrent.size();
	vector<vector<Rational>> MKCcoefs(Size, vector<Rational>(Size + 1));
	//vector<Kontur> :: iterator Equ = Independ.begin(),coef= Independ.begin();
	for (size_t Equ = 0; Equ < Size; Equ++) {
		string lp, rp;
		for (size_t coef = 0; coef < Size; coef++) {
			string namek = Independ[coef].GetName();
			if (Equ == coef) {
				if (!lp.empty())
					lp += " + ";
				lp += "I" + namek + "(";
				for (const Branch& br : Independ[Equ].GetBrnchs()) {
					string N = br.G_N();
					stringstream n;
					n << N;
					n.ignore(1);
					n >> N;
					if (br.GE() != 0) {
						if (br.GetIsFolow()) {
							MKCcoefs[Equ][Size] += br.GE();
							if (!rp.empty())
								rp += " + ";
							rp += "E" + N;
						}
						else {
							MKCcoefs[Equ][Size] -= br.GE();
							rp += "-E" + N;
						}
					}
					if (br.GR() != 0) {
						if (br.G_N() != (*(begin(Independ[Equ].GetBrnchs()))).G_N())
							lp += " + ";
						lp += "R" + N;
					}
					MKCcoefs[Equ][Equ] += br.GR();
				}
				lp += ")";
			}
			else {
				int i = 0;
				for (const Branch& br : Independ[coef].GetBrnchs()) {
					for (const Branch& b : Independ[Equ].GetBrnchs()) {
						if (b.G_N() == br.G_N()) {
							if (b.GR() != 0) {
								if (!lp.empty())
									lp += " + ";
								if (i == 0)
									lp += "I" + namek + "(";
								i++;
								string N = br.G_N();
								stringstream n;
								n << N;
								n.ignore(1);
								n >> N;
								if (br.GetIsFolow() && b.GetIsFolow() || !br.GetIsFolow() && !b.GetIsFolow()) {
									MKCcoefs[Equ][coef] += br.GR();
									if (coef != 0)
										lp += " + ";
									lp += +"R" + N;
								}
								else {
									MKCcoefs[Equ][coef] -= br.GR();
									lp += +"-R" + N;
								}
							}
							break;
						}

					}
				}
				if (i > 0)
					lp += ")";

			}
		}
		for (const Kontur& k : SourseCurrent) {
			for (const Branch& br : k.GetBrnchs()) {
				for (const Branch& b : Independ[Equ].GetBrnchs()) {
					if (b.G_N() == br.G_N()) {
						if (b.GR() != 0) {
							string N = br.G_N();
							stringstream n;
							n << N;
							n.ignore(1);
							n >> N;
							if (br.GetIsFolow() && b.GetIsFolow() || !br.GetIsFolow() && !b.GetIsFolow()) {
								MKCcoefs[Equ][Size] -= k.GetBrnchs()[0].GI() * b.GR();
								rp += " -" + k.GetBrnchs()[0].G_N() + "R" + N;
							}
							else {
								if (!rp.empty())
									rp += " + ";
								rp += k.GetBrnchs()[0].G_N() + "R" + N;
								MKCcoefs[Equ][Size] += k.GetBrnchs()[0].GI() * b.GR();
							}
						}
						break;
					}
				}
			}
		}
		cout << lp + " = ";
		if (rp.empty())
			cout << " 0";
		else
			cout << rp << endl << endl;
	}
	return MKCcoefs;
}
vector<vector<Rational>> MakeMatrixMKC(vector<Knot>& UnkKn, vector<Kontur>& Ind, vector<Kontur>& SourCur) {//вызывается из main
	SourCur = SelectKonturs(UnkKn, true);
	vector<vector<Rational>>coefsMKC = MKCcoefs(SourCur, Ind);
	return coefsMKC;
}