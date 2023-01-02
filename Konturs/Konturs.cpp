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
		vector<string> Useknot;// индикатор того, что узел уже использовался 
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
			//хотим сделать указатель на узел общедоступный, чтобы можно было через него делать инкремент
			vector<Branch> Pr2;//2 приоритет
			vector<Branch> Resid;
			for (Knot& kn : knots) {
				if (kn.GetName() == knotnext) {
					knj = &kn;//создали ссылку на узел из глобальных данных
				}
			}
			//надо инкремент делать не только в узле этом но и ещё другом 
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
//Функция для выбора контуров. Принимает узлы(копию), конст ссылку на неизв ветки, количество уравнений. Циклом идём по узлам, чтобы построение каждого нового контура начиналось с нового узла. При выборе текущего контура нужно создавать вектор веток, в который последовательно добавлять ветки. За создание контура отвечает цикл do while, к концу каждой итерации которого переменная knotnext принимает значение имени узла ветки, которую добавили в вектор на этой итерации. В классе Branch есть счётчик количества контуров, в которые входит ветка. Его надо инкрементировать, когда ветка добавляется в вектор при создании контура. Ветка добавляется в контур при условии, что её предполагаемый кпотпехст ещё не содержится в векторе юзаных узлов. Этот вектор нужно создавать внутри верхнего цикла, он относится к текущему контуру. Так же есть приоритет в выборе ветки. Главный приоритет это что кнотнехт этой ветки будет совпадать с knots[i], следующий приоритет это что ветка ещё не входит ни в один котур. Чтобы организовать эти приоритеты надо в каждой итерации while создавать вектор веток-кандидатов, куда будут добавляться ветки, которые не подходят по первому признаку, но подходят по второму, а так же вектор остаточных веток, которые не имеют приоритета. В цикле если встречается ветка с первым приоритетом, она сразу добавляется в контур, делается инкремент юзанности этой ветки и брэйк. По окончании цикла поиска ветки проверяется наличие веток в вектора следующих приоритетов, при наличии добавляется первый элемент, его счётчик инкрементируется, а кнотнехт добаляется в вектор. Задача. Как грамотно сделать инкремент у выбранной ветки, ведь выбранная ветка относится к локальному выбору ветки, при выборе ветки мы используем 