#include"Konturs.h"


Kontur::Kontur(const Kontur& other) {
		this->brn = other.brn;
		this->name = other.name;
	}
Kontur::Kontur(const vector<Branch>& brn, const string& Name) {
		this->brn = brn;
		this->name = Name;
	}
	vector<Branch>Kontur::GetBrnchs()const {
		return brn;
	}
	string Kontur::GetName()const {
		return name;
	}

vector<Kontur> SelectKonturs(vector<Knot>& knots, const bool& IsCurSourse) {
	vector<Kontur> Konturs;
	for (size_t i = 0; i < knots.size(); i++) {
		if (IsCurSourse && (knots[i].GetFamBranches().size() == 0 || knots[i].GetName() != knots[i].GetFamBranches()[0].GetBegin()))
			continue;
		else if (!IsCurSourse && Count(knots[i].GetUnkBranches()) == 0)
			continue;
		string name_sourse_knot = knots[i].GetName(), knotnext = knots[i].GetName();
		vector<Branch> AnyKontur;
		vector<string> Useknot;// ��������� ����, ��� ���� ��� ������������� 
		Useknot.push_back(knots[i].GetName());
		if (IsCurSourse) {
			string knotnextLocal = knots[i].GetFamBranches()[0].GetEnd();
			AnyKontur.push_back(knots[i].GetFamBranches()[0]);
			Useknot.push_back(knotnextLocal);
			for (Knot& k : knots) {
				if (k.GetName() == knotnext || k.GetName() == knotnextLocal) {
					vector<Branch>::iterator b = k.FamBrnchs.begin();
					for (b; b != k.FamBrnchs.end(); b++) {
						if ((*b).G_N() == AnyKontur[0].G_N()) {
							k.FamBrnchs.erase(b);
							break;
						}
					}
				}
			}
			knotnext = knotnextLocal;
		}
		do
		{
			bool Norm = false;
			Knot* knj = &knots[i];
			//����� ������� ��������� �� ���� �������������, ����� ����� ���� ����� ���� ������ ���������
			vector<Branch> Pr2;//2 ���������
			vector<Branch> Resid;
			for (Knot& kn : knots) {
				if (kn.GetName() == knotnext) {
					knj = &kn;//������� ������ �� ���� �� ���������� ������
				}
			}
			//���� ��������� ������ �� ������ � ���� ���� �� � ��� ������ 
			string knotnextLocal;
			for (Branch& UB : (*knj).Unkbrnchs) {
				if (knotnext == UB.GetBegin()) {
					knotnextLocal = UB.GetEnd();
					UB.SetIsFollow(true);
				}
				else {
					knotnextLocal = UB.GetBegin();
					UB.SetIsFollow(false);
				}
				if (count(Useknot.begin(), Useknot.end(), knotnextLocal) > 0 && knotnextLocal != name_sourse_knot)
					continue;
				if (knotnextLocal == name_sourse_knot || (UB.GetCountUse() == 0 && AnyKontur.size() == 0)) {
					bool Indep = AnyKontur.empty();
					string UN = UB.G_N();
					Norm = true;
					AnyKontur.push_back(UB);
					Useknot.push_back(knotnextLocal);
					for (Knot& k : knots) {
						if (k.GetName() == knotnext || k.GetName() == knotnextLocal) {
							vector<Branch>::iterator b = k.Unkbrnchs.begin();
							for (b; b != k.Unkbrnchs.end(); b++) {
								if ((*b).G_N() == UN) {
									if (Indep)
										k.Unkbrnchs.erase(b);
									else
										(*b).IncrUse();
									break;
								}
							}
						}
					}
					knotnext = knotnextLocal;
					Pr2.clear();
					Resid.clear();
					break;
				}
				if (UB.GetCountUse() == 0) {
					UB.knotnext = knotnextLocal;
					Pr2.push_back(UB);
				}
				else {
					UB.knotnext = knotnextLocal;
					Resid.push_back(UB);
				}
			}
			if (Pr2.size() != 0) {
				AnyKontur.push_back(Pr2[0]);
				for (Branch& b : (*knj).Unkbrnchs) {
					if (b.G_N() == Pr2[0].G_N()) {
						b.IncrUse();
						break;
					}
				}
				knotnext = Pr2[0].knotnext;
				Useknot.push_back(knotnext);
				for (Knot& k : knots) {
					if (k.GetName() == knotnext) {
						for (Branch& b : k.Unkbrnchs) {
							if (b.G_N() == Pr2[0].G_N()) {
								b.IncrUse();
								break;
							}
						}
						break;
					}
				}
			}
			else if (Resid.size() != 0) {
				AnyKontur.push_back(Resid[0]);
				for (Branch& b : (*knj).Unkbrnchs) {
					if (b.G_N() == Resid[0].G_N())
						b.IncrUse();
				}
				knotnext = Resid[0].knotnext;
				Useknot.push_back(knotnext);
				for (Knot& k : knots) {
					if (k.GetName() == knotnext) {
						for (Branch& b : k.Unkbrnchs) {
							if (b.G_N() == Resid[0].G_N())
								b.IncrUse();
						}
					}
				}
			}
			else if (!Norm) {
				AnyKontur.erase(AnyKontur.end() - 1);
				knotnext = *(Useknot.end() - 2);
			}
		} while (name_sourse_knot != knotnext);
		stringstream ss;
		ss << Konturs.size() + 1;
		Konturs.push_back({ AnyKontur,(IsCurSourse) ? AnyKontur[0].G_N() : "k" + ss.str() });
	}
	return Konturs;
}
//������� ��� ������ ��������. ��������� ����(�����), ����� ������ �� ����� �����, ���������� ���������. ������ ��� �� �����, ����� ���������� ������� ������ ������� ���������� � ������ ����. ��� ������ �������� ������� ����� ��������� ������ �����, � ������� ��������������� ��������� �����. �� �������� ������� �������� ���� do while, � ����� ������ �������� �������� ���������� knotnext ��������� �������� ����� ���� �����, ������� �������� � ������ �� ���� ��������. � ������ Branch ���� ������� ���������� ��������, � ������� ������ �����. ��� ���� ����������������, ����� ����� ����������� � ������ ��� �������� �������. ����� ����������� � ������ ��� �������, ��� � �������������� ��������� ��� �� ���������� � ������� ������ �����. ���� ������ ����� ��������� ������ �������� �����, �� ��������� � �������� �������. ��� �� ���� ��������� � ������ �����. ������� ��������� ��� ��� �������� ���� ����� ����� ��������� � knots[i], ��������� ��������� ��� ��� ����� ��� �� ������ �� � ���� �����. ����� ������������ ��� ���������� ���� � ������ �������� while ��������� ������ �����-����������, ���� ����� ����������� �����, ������� �� �������� �� ������� ��������, �� �������� �� �������, � ��� �� ������ ���������� �����, ������� �� ����� ����������. � ����� ���� ����������� ����� � ������ �����������, ��� ����� ����������� � ������, �������� ��������� ��������� ���� ����� � �����. �� ��������� ����� ������ ����� ����������� ������� ����� � ������� ��������� �����������, ��� ������� ����������� ������ �������, ��� ������� ����������������, � �������� ���������� � ������. ������. ��� �������� ������� ��������� � ��������� �����, ���� ��������� ����� ��������� � ���������� ������ �����, ��� ������ ����� �� ���������� 