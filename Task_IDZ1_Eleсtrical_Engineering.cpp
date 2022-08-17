#include<string>
#include<iostream>
#include<vector>
#include<map>
#include<sstream>
#include<exception>
#include <set>
#include<algorithm>
#include<iomanip>
using namespace std; 
class Branch
{
public:
	Branch(const string& numb,const string& begkn, const string& endkn, const double& e, const double& j, const double& r) {
		number=numb;
		E = e;
		J = j;
		R = r;

		if(J!=0){
			I = J;
			SourseCurrent=true;
		}
		beg = begkn;
		end = endkn;
	}
	Branch(){}
	Branch(const Branch& other){
		this->beg=other.beg;
		this->CountUse = other.CountUse;
		this->E = other.E;
		this->end = other.end;
		this->I = other.I;
		this->J=other.J;
		this->IsFolowKontur = other.IsFolowKontur;
		this->knotnext = other.knotnext;
		this->number = other.number;
		this->NumberUnk = other.NumberUnk;
		this->R = other.R;
		this->SourseCurrent = other.SourseCurrent;
	}
	string GetBegin()const {
		return beg;
	}
	string GetEnd()const{
		return end;
	}
	double GE()const{
	return E;
	}
	double GJ()const{
	return J;
	}
	double GR()const{
	return R;
	}
	double GI()const{
	return I;
	}
	int G_NU()const{
		return NumberUnk;
	}
	string G_N()const{
	return number;
	}
	bool G_SC()const{
	return SourseCurrent;}
	void SetNumberUnk(const int& n){
	 NumberUnk=n;
	}
	void ChangeI(const double& new_I){
		I=new_I;
	}
	void IncrUse(){
		CountUse++;
	}
	bool GetIsFolow(){
		return IsFolowKontur;
	}
	void SetIsFollow(const bool& b){
		IsFolowKontur=b;
	}
	int GetCountUse(){
		return CountUse;
	}
	string knotnext;	
private:
	double E=0;
	double J=0;
	double R=0;
	double I=0;
	string end;
	string beg;
	bool SourseCurrent=false;
	int NumberUnk=0;
	string number="";
	bool IsFolowKontur=false;
	int CountUse=0;

};
void EnsureNextSymbolAndSkip(istream& input){
	if (input.peek() != ',') {
		stringstream ss;
		ss << "excepted ',' but has: " << input.peek() << ' ' << "branch has not created!";
		throw runtime_error(ss.str());
	}
	input.ignore(1);
}
istream& operator>>(istream& input, Branch& branch) {
	if(input){
		string begin, end;
		double e,j,r;
		string number;
		input >> number;
		EnsureNextSymbolAndSkip(input);
		getline(input, begin, ',');
		getline(input,end,',');
		input>>e;
		EnsureNextSymbolAndSkip(input);
		input >> j;
		EnsureNextSymbolAndSkip(input);
		input >> r;
		if(input){
			branch=Branch(number,begin,end,e,j,r);
		}else{
			stringstream ss;
			ss << "The input data does not match format! "<< "Branch has not created!";
			throw runtime_error(ss.str());
		}

	}
	return input;
}
bool operator<(Branch& lhs, Branch& rhs){
return lhs.G_NU()<rhs.G_NU();
}
bool operator==(const Branch& lhs, const Branch& rhs){
	return lhs.G_N()==rhs.G_N();
}
class Knot
{
public:
	Knot(const Knot& Other){
		this->name=Other.name;
		this->branches=Other.branches;
		this->Unkbrnchs=Other.Unkbrnchs;
		this->FamBrnchs = Other.FamBrnchs;
	}
	Knot(){}
	Knot(const string& design){
	name=design;
	}
	string GetName()const{
	return name;
	}
	void SetBranches(const Branch& new_branch){
		branches.push_back(new_branch);
	}
	void SetUnkBranches(const Branch& new_unk_branch) {
		Unkbrnchs.push_back(new_unk_branch);
	}
	void SetFamBranches(const Branch& new_fam_branch) {
		FamBrnchs.push_back(new_fam_branch);
	}
	void EraseUnk(const string& namebr){
		vector<Branch>::iterator unk;
		for(unk = Unkbrnchs.begin();unk!=Unkbrnchs.end();unk++){
			if((*unk).G_N()==namebr){
				Unkbrnchs.erase(unk);
				break;
			}
		}	
	}
	vector<Branch> GetBranches()const{
		return branches;
	}
	vector<Branch> GetUnkBranches()const {
		return Unkbrnchs;
	}
	vector<Branch> GetFamBranches()const {
		return FamBrnchs;
	}
	~Knot(){
		name.clear();
		branches.clear();
		Unkbrnchs.clear();
		FamBrnchs.clear();
	}
	const Knot& operator = (const Knot& Other){
		this->name =Other.name;
		this->branches = Other.branches;
		this->Unkbrnchs = Other.Unkbrnchs;
		this->FamBrnchs = Other.FamBrnchs;
		return *this;
	}
	vector<Branch> Unkbrnchs;
private:
	string name;
	vector<Branch> branches;
	
	vector<Branch> FamBrnchs;
};
bool operator==(const Knot& lhs, const Knot& rhs){
return lhs.GetName()==rhs.GetName();
}
bool operator<(const Knot& lhs, const Knot& rhs){
	return lhs.GetName() < rhs.GetName();
}
class Kontur
{
public:
	Kontur(const Kontur& other){
		this->brn=other.brn;
	}
	Kontur(const vector<Branch>& brn){
		this->brn=brn;
	}
	vector<Branch>GetBrnchs()const{
		return brn;
	}
private:
	vector<Branch> brn;
};
void PrintVector(const vector<vector<double>>&coefs){
	cout<<left<<fixed<<setprecision(5);
	for(const vector<double>& Eq: coefs){
		for(const double& c: Eq){
			cout<<setw(10)<<c<<" ";
		}
		cout<<endl;
	}
	cout<<"//////////////////////////////////////////////////////\n";
}
void gayss(vector<vector<double>>&arrkoef, vector<Branch>&Branches, const int& n){
	PrintVector(arrkoef);
	double p, gyy;
	int i, l, g, h = n, j;
	for (g = 0; g < n - 1; g++){
		j = g + 1;//фактический номер строки
		while (arrkoef[g][g] == 0){
			for (i = 0; i <= n; i++){//идём по строке
				p = arrkoef[g][i];//меняем местами строку с нулём на диаганали со строкой без нуля на диаганали. 
				arrkoef[g][i] = arrkoef[j][i];
				arrkoef[j][i] = p;
			}
			j++;
		}
		PrintVector(arrkoef);
		for (i = g + 1; i < n; i++){//сводим к треугольному виду
			gyy = arrkoef[i][g] / arrkoef[g][g];
			for (l = g; l <= n; l++){
				arrkoef[i][l] -= arrkoef[g][l] * gyy;
			}
			PrintVector(arrkoef);
		}
	}
	for (i = 0; i < n; i++){// обратный ход
		for (l = h; l < n; l++){
			arrkoef[n - 1 - i][n] -= arrkoef[n - 1 - i][l] * Branches[l].GI();
		}
		Branches[n-1-i].ChangeI(arrkoef[n - 1 - i][n] / arrkoef[n - 1 - i][n - 1 - i]);
		cout<<"Carrent "<<Branches[n-i-1].G_N()<<" = "<<Branches[n-i-1].GI()<<endl;
		h--;
	}
}
//Функция для выбора контуров. Принимает узлы(копию), конст ссылку на неизв ветки, количество уравнений. Циклом идём по узлам, чтобы построение каждого нового контура начиналось с нового узла. При выборе текущего контура нужно создавать вектор веток, в который последовательно добавлять ветки. За создание контура отвечает цикл do while, к концу каждой итерации которого переменная knotnext принимает значение имени узла ветки, которую добавили в вектор на этой итерации. В классе Branch есть счётчик количества контуров, в которые входит ветка. Его надо инкрементировать, когда ветка добавляется в вектор при создании контура. Ветка добавляется в контур при условии, что её предполагаемый кпотпехст ещё не содержится в векторе юзаных узлов. Этот вектор нужно создавать внутри верхнего цикла, он относится к текущему контуру. Так же есть приоритет в выборе ветки. Главный приоритет это что кнотнехт этой ветки будет совпадать с knots[i], следующий приоритет это что ветка ещё не входит ни в один котур. Чтобы организовать эти приоритеты надо в каждой итерации while создавать вектор веток-кандидатов, куда будут добавляться ветки, которые не подходят по первому признаку, но подходят по второму, а так же вектор остаточных веток, которые не имеют приоритета. В цикле если встречается ветка с первым приоритетом, она сразу добавляется в контур, делается инкремент юзанности этой ветки и брэйк. По окончании цикла поиска ветки проверяется наличие веток в вектора следующих приоритетов, при наличии добавляется первый элемент, его счётчик инкрементируется, а кнотнехт добаляется в вектор. Задача. Как грамотно сделать инкремент у выбранной ветки, ведь выбранная ветка относится к локальному выбору ветки, при выборе ветки мы используем 
vector<Kontur> SelectKonturs(vector<Knot> knots, const vector<Branch>& Branchs, const int& CountEquations){
	cout<<"I go to SelectKonturs\n";
	vector<Kontur> Konturs;
	for(int i =0;i<CountEquations;i++){
		string name_sourse_knot=knots[i].GetName(), knotnext=knots[i].GetName();
		int l=0;
		vector<Branch> AnyKontur;
		vector<string> Useknot;// индикатор того, что узел уже использовался 
		Useknot.push_back(knots[i].GetName());
		do
		{   
			cout<<"I go to do while\n";
			Knot* knj=&knots[i];
			 //хотим сделать указатель на узел общедоступный, чтобы можно было через него делать инкремент

			vector<Branch> Pr2;//2 приоритет
			vector<Branch> Resid;
			for(Knot& kn:knots){
				if(kn.GetName()==knotnext){
					knj=&kn;//создали ссылку на узел из глобальных данных
				}
			}
			//надо инкремент делать не только в узле этом но и ещё другом 
			string knotnextLocal;
			cout<<"I go to for selectBranch\n";
			for( Branch& UB: (*knj).Unkbrnchs){
				if(knotnext==UB.GetBegin()){
					knotnextLocal=UB.GetEnd();
					UB.SetIsFollow(true);
				}
				else{
					knotnextLocal=UB.GetBegin();
					UB.SetIsFollow(false);
				}
				if(knotnextLocal==name_sourse_knot&&AnyKontur.size()>1){
					AnyKontur.push_back(UB);
					UB.IncrUse();
					knotnext=knotnextLocal;
					for(Knot&k: knots){
						if(k.GetName()==knotnext){
							for(Branch&b:k.Unkbrnchs){
								if(b.G_N()==UB.G_N()){
									b.IncrUse();
								}
							}
							break;
						}
					}
					break;
				}
				if (count(Useknot.begin(), Useknot.end(), knotnextLocal) == 0&&UB.GetCountUse()==0){
					UB.knotnext=knotnextLocal;
					Pr2.push_back(UB);
				}
				else if(count(Useknot.begin(), Useknot.end(), knotnextLocal) == 0){
					UB.knotnext=knotnextLocal;
					Resid.push_back(UB);
				}
			}
			if(name_sourse_knot != knotnext||AnyKontur.size()==0){
				if(Pr2.size()!=0){
					AnyKontur.push_back(Pr2[0]);
					for (Branch& b : (*knj).Unkbrnchs) {
						if (b.G_N() == Pr2[0].G_N()){
							b.IncrUse();
							break;
						}
					}
					knotnext=Pr2[0].knotnext;
					Useknot.push_back(knotnext);
					for (Knot& k : knots) {
						if (k.GetName() == knotnext) {
							for (Branch& b : k.Unkbrnchs) {
								if (b.G_N() == Pr2[0].G_N()){
									b.IncrUse();
									break;
								}
							}
							break;
						}
					}
				}
				else if(Resid.size()!=0){
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
				else{
					AnyKontur.erase(AnyKontur.end()-1);
					knotnext=*(Useknot.end()-2);
				}
			}
		}while(name_sourse_knot != knotnext);
		Konturs.push_back(AnyKontur);
	}
	return Konturs;
}
vector<vector<double>>SecondLKcoefs(const vector<Kontur>& konturs, const int& UnkCount){
	cout<<"I go to SecondLKcoefs\n";
	vector<vector<double>> coefs(konturs.size(), vector<double>(UnkCount + 1, 0));
	for (size_t i = 0; i < konturs.size(); i++)
	{
		for( Branch& br: konturs[i].GetBrnchs()){
			if(br.GetIsFolow()){
				coefs[i][br.G_NU()]=br.GR();
				coefs[i][UnkCount]+=br.GE();
			}
			else{
				coefs[i][br.G_NU()] = -br.GR();
				coefs[i][UnkCount] -= br.GE();
			}
		}
	}
	return coefs;
}
vector<vector<double>>FirstLKcoefs(const vector<Knot>&knots, const int& CountUnkCarr){//функция по составлению матрицы по 1ЗК
	cout<<"I go to FirstLKcoefs\n";
	const int countline= knots.size() - 1;
	vector<vector<double>> coefs(countline,vector<double>(CountUnkCarr+1,0));
	for(int i=0;i<countline;i++){
		for(const Branch& b:knots[i].GetUnkBranches()){
			if(b.GetEnd()==knots[i].GetName())
				coefs[i][b.G_NU()] = 1;
			else
				coefs[i][b.G_NU()] = -1;
		}
		for(const Branch& b : knots[i].GetFamBranches()){
			if (b.GetEnd() == knots[i].GetName())
				coefs[i][CountUnkCarr] -= b.GI();
			else
				coefs[i][CountUnkCarr] += b.GI();
		}
	}
	return coefs;
}
void ConcVectors(vector<vector<double>>& v1,const vector<vector<double>>& v2){
	v1.insert(v1.end(),v2.begin(),v2.end());
}
vector<vector<double>> MakeMatrixLowsKirhgoff(const vector<Branch>& UnkBr, const vector<Knot>& UnkKn){
	const int FLKequationscount = UnkKn.size()-1, CountUnkCarr= UnkBr.size();
	vector<vector<double>>coefsFLK=FirstLKcoefs(UnkKn,CountUnkCarr);
	vector<vector<double>>coefsSLK=SecondLKcoefs(SelectKonturs(UnkKn,UnkBr,CountUnkCarr-FLKequationscount),CountUnkCarr);
	ConcVectors(coefsFLK,coefsSLK);
	for(vector<double>& v:coefsSLK){
		v.clear();
	}
	coefsSLK.clear();
	return coefsFLK;
}
void Compute1UnkCurrentbyFLK(Knot& knot,vector<Knot>& knots,vector<Branch>& UnkBr,vector<Branch>& Allbr){
	vector<Branch>::iterator ad, n;
	for(ad=UnkBr.begin();ad!=UnkBr.end();ad++){
		if(knot.GetUnkBranches()[0]==*ad){   //если это та неизвестная ветка, которая принадлежит этому узлу
			double I = 0;// вычисляем ток с учётом направления ветки
			if((*ad).GetEnd()==knot.GetName()){
				for(Branch& J: knot.GetFamBranches()){
					if (J.GetEnd() == knot.GetName())
						I-=J.GI();
					else
						I+=J.GI();
				}
			}else{
				for (Branch& J : knot.GetFamBranches()) {
					if (J.GetEnd() == knot.GetName())
						I+=J.GI();
					else
						I-=J.GI();
				}
			}
			for(Branch& br: Allbr){//в общем векторе веток ищем эту ветку и записываем туда значение тока
				if(*ad==br){
					br.ChangeI(I);
					int Num = br.G_NU();
					br.SetNumberUnk(0);
					knot.SetFamBranches(br);
					knot.EraseUnk((*ad).G_N());
					cout<<"According to Kirchhoff's first law, a current I"<<br.G_N()<< " was found"<<endl;
					string oppknot;
					if(knot.GetName()==br.GetBegin())//в другом узле удаляем эту ветку из неизвестных и добавляем в известные 
						oppknot=br.GetEnd();
					else
						oppknot=br.GetBegin();
					vector<Knot>::iterator kn= knots.begin();
					for(kn;kn!=knots.end();kn++){//ищем узел, обновляем, проверяем 
						if(oppknot==(*kn).GetName()){
							(*kn).EraseUnk(br.G_N());
							(*kn).SetFamBranches(br);
							if((*kn).GetUnkBranches().size()==1){
								Compute1UnkCurrentbyFLK(*kn, knots, UnkBr, Allbr);
								kn = knots.erase(kn);
							}
							else if((*kn).GetUnkBranches().size() == 0)
								kn = knots.erase(kn);
							for(Branch& b:(*kn).GetUnkBranches()){
								if(b.G_NU()>Num){
									b.SetNumberUnk(b.G_NU()-1);
									(*kn).EraseUnk(b.G_N());
									(*kn).SetUnkBranches(b);
								}
							}
							break;
						}

					}
				}
				break;
			}
			ad = UnkBr.erase(ad);
			n=ad;
			for(n;n!=UnkBr.end();n++){
				(*n).SetNumberUnk((*n).G_NU()-1);
			}
			ad--;
		}
		break;
	}
}
void ClearExcessUnkKnotsAndBranches(vector<Knot>& knots, vector<Branch>& unkbr,vector<Branch>& Allbr){//сюда передаём вектор с неизвестными узлами
	vector<Knot>::iterator k;
	for(k=knots.begin();k!=knots.end();k++){
		if((*k).GetUnkBranches().size()==1){
			Compute1UnkCurrentbyFLK(*k,knots,unkbr,Allbr);//передаём узел и вектора веток
			k=knots.erase(k);// затираем лишний узел 
			k--;
		}
	}
}
vector<Knot> holdKnotsWithUnkBrnchs(const vector<Knot>& AllKnots){
	vector<Knot> withunkbr;
	for (const Knot& k : AllKnots) {
		if(k.GetUnkBranches().size()>0)
			withunkbr.push_back(k);
	}
	return withunkbr;
}
int main(){
	int qbrch, qknt;//количество ветвей и узлов
	int CountUnknown=0;
	vector<Branch> UnkCurBranch;//вектор всех неизвестных ветвей
	//узлы, которые могут пригодиться для составления уравнений по 1ЗК
	vector<vector<double>> coefs;//матрица коеффициентов
	vector<Knot>AllKnot;
	cout << "Enter the quantity branches: ";
	cin >> qbrch;
	cout << "Enter the quantity knots: ";
	cin >> qknt;
	vector<Branch> AllBrnchs(qbrch);//вектор всех ветвей
	cout << "Enter the parameters for an each branches now, and set the direction of the current." << endl;//<<"Input format: number(string)',''start_knot_name','end_knot_name',E,R,J\nFirst of all input branchs without Current Sourse!";
	//Получение всех необходимых данных
	for (int i = 0; i < qbrch; i++)
	{
		string name, begink,endk;
		double E,R,J;
		cout<<"name: ";
		cin>>name;
		cout<<" begin knot: ";
		cin>>begink;
		cout<<" end knot: ";
		cin>>endk;
		cout<<" E = ";
		cin>>E;
		cout<<" R = ";
		cin>>R;
		cout<<" J = ";
		cin>>J;
		cout<<endl;
		AllBrnchs.push_back({name,begink,endk,E,J,R});  
	//	cin>>AllBrnchs[i];
		Knot kn1(AllBrnchs[i].GetBegin()),kn2(AllBrnchs[i].GetEnd());
		if(!AllBrnchs[i].G_SC()){
			AllBrnchs[i].SetNumberUnk(CountUnknown);//присваиваем  номер неизвестному току
			CountUnknown++; 
			if(count(AllKnot.begin(),AllKnot.end(),kn1.GetName())==0){
				kn1.SetUnkBranches(AllBrnchs[i]);
				AllKnot.push_back(kn1);
			}
			else
				for(Knot&k:AllKnot){
					if(k.GetName()==kn1.GetName())
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
		}else{
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
	vector<Knot> KnotsWithUnkBrnchs=holdKnotsWithUnkBrnchs(AllKnot); //построили вектор узлов с неиз. токами
	AllKnot.clear();
	ClearExcessUnkKnotsAndBranches(KnotsWithUnkBrnchs,UnkCurBranch, AllBrnchs);
	coefs=MakeMatrixLowsKirhgoff(UnkCurBranch,KnotsWithUnkBrnchs);
	gayss(coefs,UnkCurBranch,UnkCurBranch.size());
}
