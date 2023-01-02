#include"KL.h"

vector<vector<Rational>>SecondLKcoefs(const vector<Kontur>& konturs, const int& UnkCount) {
	vector<vector<Rational>> coefs(konturs.size(), vector<Rational>(UnkCount + 1));
	cout << "Составляем уравнения по 2 ЗК\n";
	string equation;
	for (size_t i = 0; i < konturs.size(); i++)
	{
		string rp, lp;
		stringstream number;
		number << i + 1;
		cout << number.str() << ": ";
		for (Branch& br : konturs[i].GetBrnchs()) {
			string N = br.G_N();
			stringstream n;
			n << N;
			n.ignore(1);
			n >> N;//получили номер ветки из названия ветки в надежде, что название корректное
			if (br.GetIsFolow()) {
				if (br.GE() != 0) {
					if (!rp.empty())
						rp += "+ ";
					rp += "E" + N + " ";
				}
				if (br.GR() != 0) {
					if (!lp.empty())
						lp += "+ ";
					lp += "I" + N + "R" + N + " ";
				}
				coefs[i][br.G_NU()] = br.GR();
				coefs[i][UnkCount] += br.GE();
			}
			else {
				coefs[i][br.G_NU()] = -br.GR();
				coefs[i][UnkCount] -= br.GE();
				if (br.GE() != 0)
					rp += "- E" + N + " ";
				if (br.GR() != 0)
					lp += "- I" + N + "R" + N + " ";
			}
		}
		if (rp.empty())
			rp += '0';
		cout << lp + " = " + rp << endl;
	}
	return coefs;
}
vector<vector<Rational>>FirstLKcoefs(const vector<Knot>& knots, const int& CountUnkCarr) {//функция по составлению матрицы по 1ЗК
	cout << "Составляем уравнения по 1 ЗК\n";
	const int countline = knots.size() - 1;
	vector<vector<Rational>> coefs(countline, vector<Rational>(CountUnkCarr + 1));
	for (int i = 0; i < countline; i++) {
		cout << knots[i].GetName() << ": ";
		for (const Branch& b : knots[i].GetUnkBranches()) {
			if (b.GetEnd() == knots[i].GetName()) {
				coefs[i][b.G_NU()] = 1;
				if (b != *(knots[i].GetUnkBranches().begin()))
					cout << "+ ";
				cout << b.G_N() << " ";
			}
			else {
				coefs[i][b.G_NU()] = -1;
				cout << "- " << b.G_N() << " ";
			}
		}
		cout << "= ";
		if (knots[i].GetFamBranches().empty())
			cout << "0";
		for (const Branch& b : knots[i].GetFamBranches()) {
			if (b.GetEnd() == knots[i].GetName()) {
				coefs[i][CountUnkCarr] -= b.GI();
				cout << "- " << b.G_N() << " ";
			}
			else {
				coefs[i][CountUnkCarr] += b.GI();
				if (b.G_N() != knots[i].GetFamBranches()[0].G_N())
					cout << "+ ";
				cout << b.G_N() << " ";
			}
		}
		cout << endl;
	}
	return coefs;
}

vector<vector<Rational>> MakeMatrixLowsKirhgoff(const vector<Branch>& UnkBr, vector<Knot>& UnkKn, vector<Kontur>& Ind) {//Вызывается из main
	const int FLKequationscount = UnkKn.size() - 1, CountUnkCarr = UnkBr.size();
	vector<vector<Rational>>coefsFLK = FirstLKcoefs(UnkKn, CountUnkCarr);
	Ind = SelectKonturs(UnkKn, false);
	vector<vector<Rational>>coefsSLK = SecondLKcoefs(Ind, CountUnkCarr);
	ConcVectors(coefsFLK, coefsSLK);
	for (vector<Rational>& v : coefsSLK) {
		v.clear();
	}
	coefsSLK.clear();
	return coefsFLK;
}