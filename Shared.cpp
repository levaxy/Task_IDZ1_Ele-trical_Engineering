#include"Shared.h"
#include<iomanip>
void InputChain(vector<Knot>& AllKnot, vector<Branch>& AllBrnchs, vector<Branch>& UnkCurBranch, int& qbrch, int& qknt, int& CountUnknown) {
	cout << "Enter the quantity branches: ";
	cin >> qbrch;
	cout << "Enter the quantity knots: ";
	cin >> qknt;
	cout << "Enter the parameters for an each branches now, and set the direction of the current." << endl;
	for (int i = 0; i < qbrch; i++)
	{
		string name, begink, endk;
		Rational e, r, j;
		double E, R, J;
		cout << "name: ";
		cin >> name;
		cout << " begin knot: ";
		cin >> begink;
		cout << " end knot: ";
		cin >> endk;
		cout << " E, V = ";
		cin >> E;
		e = TransformDoubletoRational(E);
		cout << " R, Ohm = ";
		cin >> R;
		r = TransformDoubletoRational(R);
		cout << " J, A = ";
		cin >> J;
		j = TransformDoubletoRational(J);
		cout << endl;
		AllBrnchs.push_back({ name,begink,endk,e,j,r });
		//	cin>>AllBrnchs[i];
		Knot kn1(AllBrnchs[i].GetBegin()), kn2(AllBrnchs[i].GetEnd());
		if (!AllBrnchs[i].G_SC()) {
			AllBrnchs[i].SetNumberUnk(CountUnknown);//присваиваем  номер неизвестному току
			CountUnknown++;
			if (count(AllKnot.begin(), AllKnot.end(), kn1.GetName()) == 0) {
				kn1.SetUnkBranches(AllBrnchs[i]);
				AllKnot.push_back(kn1);
			}
			else
				for (Knot& k : AllKnot) {
					if (k.GetName() == kn1.GetName())
						k.SetUnkBranches(AllBrnchs[i]);
				}
			if (count(AllKnot.begin(), AllKnot.end(), kn2.GetName()) == 0) {
				kn2.SetUnkBranches(AllBrnchs[i]);
				AllKnot.push_back(kn2);
			}
			else
				for (Knot& k : AllKnot) {
					if (k.GetName() == kn2.GetName())
						k.SetUnkBranches(AllBrnchs[i]);
				}
			UnkCurBranch.push_back(AllBrnchs[i]);
			//заполняем вектор ветвей с неизвестными токами
		}
		else {
			if (count(AllKnot.begin(), AllKnot.end(), kn1.GetName()) == 0) {
				kn1.SetFamBranches(AllBrnchs[i]);
				AllKnot.push_back(kn1);
			}
			else
				for (Knot& k : AllKnot) {
					if (k.GetName() == kn1.GetName())
						k.SetFamBranches(AllBrnchs[i]);
				}
			if (count(AllKnot.begin(), AllKnot.end(), kn2.GetName()) == 0) {
				kn2.SetFamBranches(AllBrnchs[i]);
				AllKnot.push_back(kn2);
			}
			else
				for (Knot& k : AllKnot) {
					if (k.GetName() == kn2.GetName())
						k.SetFamBranches(AllBrnchs[i]);
				}
		}                                       //++счётчик количества неизвестных

	}
}

void ConcVectors(vector<vector<Rational>>& v1, const vector<vector<Rational>>& v2) {
	v1.insert(v1.end(), v2.begin(), v2.end());
}

void PrintVector(const vector<vector<Rational>>& coefs) {
	cout << endl;
	cout << left;
	size_t a = 10;
	for (const vector<Rational>& Eq : coefs) {
		for (const Rational& c : Eq) {
			cout << setw(a) << c << " ";
		}
		cout << endl;
	}
	for (size_t i = 0; i < coefs[0].size(); i++)
	{
		for (size_t j = 0; j < a; j++)
		{
			cout << "/";
		}
	}
	cout << endl;
}

void gayss(vector<vector<Rational>>& arrkoef, vector<Rational>& Branches, const int& n) {
	Rational p, gyy;
	PrintVector(arrkoef);
	int i, l, g, h = n, j;
	for (g = 0; g < n - 1; g++) {
		j = g + 1;//фактический номер строки
		while (arrkoef[g][g] == 0) {
			for (i = 0; i <= n; i++) {//идём по строке
				p = arrkoef[g][i];//меняем местами строку с нулём на диаганали со строкой без нуля на диаганали. 
				arrkoef[g][i] = arrkoef[j][i];
				arrkoef[j][i] = p;
			}
			j++;
		}
		for (i = g + 1; i < n; i++) {//сводим к треугольному виду
			gyy = arrkoef[i][g] / arrkoef[g][g];
			for (l = g; l <= n; l++) {
				arrkoef[i][l] -= arrkoef[g][l] * gyy;
			}
		}
		PrintVector(arrkoef);
	}
	int o = -1;
	for (i = 0; i < n; i++) {// обратный ход
		cout << "X" << n - i << " = [" << arrkoef[n - 1 - i][n];
		for (l = h; l < n; l++) {
			if (arrkoef[n - 1 - i][l] != 0)
				cout << " - " << "(" << arrkoef[n - 1 - i][l] << ")" << " * (" << Branches[l] << ")";
			arrkoef[n - 1 - i][n] -= arrkoef[n - 1 - i][l] * Branches[l];
		}
		Branches[n - 1 - i] = arrkoef[n - 1 - i][n] / arrkoef[n - 1 - i][n - 1 - i];
		cout << "]*(" << (arrkoef[n - 1 - i][n - 1 - i] ^ o) << ") = " << Branches[n - 1 - i] << "\n\n";
		h--;
	}
	cout << "///////////////////////////////////\n\n";
}

void PrintRes(const vector<Branch>& UnkCurBranch, const vector<Rational>& Unk) {
	for (size_t i = 0; i < UnkCurBranch.size(); i++) {
		cout << "Current " << UnkCurBranch[i].G_N() << " = " << Unk[i] << " = " << (double)Unk[i].Numerator() / (double)Unk[i].Denominator() << "A" << endl << endl;
	}
	cout << "/////////////////////////\n\n";
}

void PrintTrans(const vector<Knot>& knots) {
	vector<string> passed;
	for (const Knot& k : knots) {
		for (const Branch br : k.GetFamBranches()) {
			if (count(passed.begin(), passed.end(), br.G_N()) == 0) {
				cout << br.G_N() << " begin = " << br.GetBegin() << "; end = " << br.GetEnd();
				if (br.GE() != 0)
					cout << "\tE = " << br.GE() << " = " << (double)br.GE().Numerator() / (double)br.GE().Denominator();
				passed.push_back(br.G_N());
				cout << "\n";
			}
		}
		for (const Branch br : k.GetUnkBranches()) {
			if (count(passed.begin(), passed.end(), br.G_N()) == 0) {
				cout << br.G_N() << " begin = " << br.GetBegin() << "; end = " << br.GetEnd();
				if (br.GE() != 0)
					cout << "\tE = " << br.GE() << " = " << (double)br.GE().Numerator() / (double)br.GE().Denominator();
				passed.push_back(br.G_N());
				cout << "\n";
			}
		}
	}
	cout << "\n\n";
}

void PrintSeparator() {
	cout << "*** ****** *** *** **** ****** **** ****** **** ****** ******** ******* *****\n**** ******* ******* *** *******  **** ***** ******** ***** ****** *****\n\n";
}

void ClearExcessUnkKnotsAndBranches(vector<Knot>& knots, vector<Branch>& unkbr, vector<Branch>& Allbr) {//сюда передаём вектор с неизвестными узлами
	vector<Branch>::iterator br, B;
	vector<Knot>::iterator k;
	for (br = unkbr.begin(); br != unkbr.end(); ) {
		if ((*br).GetBegin() == (*br).GetEnd()) {
			for (Branch& b : Allbr) {
				if (b.G_N() == (*br).G_N()) {
					b.ChangeI((*br).GE() / (*br).GR());
					cout << "В замкнутой ветке " << b.G_N() << "с ЭДС = " << (double)b.GE().Numerator() / (double)b.GE().Denominator() << " ток равен " << b.GI() << " = " << (double)b.GI().Numerator() / (double)b.GI().Denominator() << " A\n\n";
					break;
				}
			}
			for (k = knots.begin(); k != knots.end(); k++) {
				if ((*k).GetName() == (*br).GetBegin()) {
					for (B = (*k).Unkbrnchs.begin(); B != (*k).Unkbrnchs.end(); B++)
					{
						if ((*B).G_N() == (*br).G_N()) {
							//(*B).ChangeI((*B).GE() / (*B).GR());
							//(*k).FamBrnchs.push_back((*B));
							(*k).Unkbrnchs.erase(B);
							break;
						}
					}
					break;
				}
			}
			if (br == unkbr.end() - 1) {//затираем лишнюю ветку 
				unkbr.erase(br);
				break;
			}
			else
				br = unkbr.erase(br);
		}
		else
			br++;
	}

	for (k = knots.begin(); k != knots.end(); k++) {
		for (B = (*k).FamBrnchs.begin(); B != (*k).FamBrnchs.end();)
		{
			if ((*B).GetBegin() == (*B).GetEnd()) {
				if (B == (*k).FamBrnchs.end() - 1) {
					(*k).FamBrnchs.erase(B);
					break;
				}
				else
					B = (*k).FamBrnchs.erase(B);
			}
			else
				B++;
		}
	}

	for (k = knots.begin(); k != knots.end();) {
		if ((*k).GetUnkBranches().size() == 1) {
			string kname = (*k).GetName();
			Compute1UnkCurrentbyFLK(*k, knots, unkbr, Allbr);//передаём узел и вектора веток
			for (k = knots.begin(); k != knots.end(); k++) {
				if ((*k).GetName() == kname)
					break;
			}
			if (k == knots.end() - 1) {
				knots.erase(k);// затираем лишний узел
				break;
			}
			else
				k = knots.erase(k);
		}
		else
			k++;
	}

}

void Compute1UnkCurrentbyFLK(Knot& knot, vector<Knot>& knots, vector<Branch>& UnkBr, vector<Branch>& Allbr) {
	vector<Branch>::iterator ad, n;
	for (ad = UnkBr.begin(); ad != UnkBr.end();) {
		string adname = (*ad).G_N();
		if (knot.GetUnkBranches()[0] == *ad) {   //если это та неизвестная ветка, которая принадлежит этому узлу
			Rational I;// вычисляем ток с учётом направления ветки
			if ((*ad).GetEnd() == knot.GetName()) {
				for (Branch& J : knot.GetFamBranches()) {
					if (J.GetEnd() == knot.GetName())
						I -= J.GI();
					else
						I += J.GI();
				}
			}
			else {
				for (Branch& J : knot.GetFamBranches()) {
					if (J.GetEnd() == knot.GetName())
						I += J.GI();
					else
						I -= J.GI();
				}
			}
			for (Branch& br : Allbr) {//в общем векторе веток ищем эту ветку и записываем туда значение тока
				if (*ad == br) {
					br.ChangeI(I);
					int Num = br.G_NU();
					br.SetNumberUnk(0);
					knot.SetFamBranches(br);
					knot.EraseUnk((*ad).G_N());
					cout << "According to Kirchhoff's first law, a current " << br.G_N() << " = " << I << " = " << (double)I.Numerator() / (double)I.Denominator() << endl << endl;
					string oppknot;
					if (knot.GetName() == br.GetBegin())//в другом узле удаляем эту ветку из неизвестных и добавляем в известные 
						oppknot = br.GetEnd();
					else
						oppknot = br.GetBegin();
					vector<Knot>::iterator kn = knots.begin();
					for (kn; kn != knots.end(); kn++) {//ищем узел, обновляем, проверяем 
						if (oppknot == (*kn).GetName()) {
							(*kn).EraseUnk(br.G_N());
							(*kn).SetFamBranches(br);
							if ((*kn).GetUnkBranches().size() == 1) {
								Compute1UnkCurrentbyFLK(*kn, knots, UnkBr, Allbr);
								for (kn; kn != knots.end(); kn++) {
									if ((*kn).GetName() == oppknot)
										break;
								}
								kn = knots.erase(kn);
							}
							else if ((*kn).GetUnkBranches().size() == 0)
								kn = knots.erase(kn);
							else
								for (Branch& b : (*kn).Unkbrnchs) {
									if (b.G_NU() > Num) {
										b.SetNumberUnk(b.G_NU() - 1);
										(*kn).EraseUnk(b.G_N());
										(*kn).SetUnkBranches(b);
									}
								}
							break;
						}
					}
					break;
				}
			}
			for (ad = UnkBr.begin(); ad != UnkBr.end(); ad++) {
				if ((*ad).G_N() == adname)
					break;
			}
			if (ad != UnkBr.end() - 1) {
				ad = UnkBr.erase(ad);
				for (n = ad; n != UnkBr.end(); n++) {
					(*n).SetNumberUnk((*n).G_NU() - 1);
				}
			}
			else
				UnkBr.erase(ad);
			break;
		}
		else
			ad++;
	}
}

vector<Knot> holdKnotsWithUnkBrnchs(const vector<Knot>& AllKnots) {
	vector<Knot> withunkbr;
	for (const Knot& k : AllKnots) {
		if (k.GetUnkBranches().size() > 0)
			withunkbr.push_back(k);
	}
	return withunkbr;
}