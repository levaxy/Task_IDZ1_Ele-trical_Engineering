#include<string>
#include<iostream>
#include<vector>
#include<map>
#include<sstream>
#include<exception>
#include <set>
#include<algorithm>
#include<iomanip>
#include"..\Task_IDZ1_Eleсtrical_Engineering\Rational\Rational.h"
#include"..\Task_IDZ1_Eleсtrical_Engineering\Branch\Branch.h"
#include"..\Task_IDZ1_Eleсtrical_Engineering\Knot\Knot.h"
#include"..\Task_IDZ1_Eleсtrical_Engineering\Shared.h"
#include"..\Task_IDZ1_Eleсtrical_Engineering\MKP\MKP.h"
#include"..\Task_IDZ1_Eleсtrical_Engineering\Konturs\Konturs.h"
#include"..\Task_IDZ1_Eleсtrical_Engineering\MKC\MKC.h"
#include"..\Task_IDZ1_Eleсtrical_Engineering\Kirchhgoff's_Lows\KL.h"
using namespace std;

int main(){
	setlocale(LC_ALL ,"rus");
	vector<Branch> UnkCurBranch;//вектор всех неизвестных ветвей
	//узлы, которые могут пригодиться для составления уравнений по 1ЗК
	vector<vector<Rational>> coefsLK,coefsMKC;//матрица коеффициентов
	vector<Knot>AllKnot;
	vector<Branch> AllBrnchs;//вектор всех ветвей
	int qbrch, qknt;//количество ветвей и узлов
	int CountUnknown=0;
	InputChain(AllKnot, AllBrnchs, UnkCurBranch, qbrch,qknt, CountUnknown);
	vector<Knot> KnotsWithUnkBrnchs=holdKnotsWithUnkBrnchs(AllKnot); //построили вектор узлов с неиз. токами
	AllKnot.clear();
	vector<Kontur> Indep,SourCur;
	ClearExcessUnkKnotsAndBranches(KnotsWithUnkBrnchs,UnkCurBranch, AllBrnchs);
	vector<Knot> KnotsMKP=KnotsWithUnkBrnchs;
	vector<Branch> UnkbrMKP=UnkCurBranch, AllbrMKP=AllBrnchs;
	CountUnknown=UnkCurBranch.size();
	cout<<"\t\t1. Рассчёт по правилам Кирхгоффа\n\n";
	coefsLK=MakeMatrixLowsKirhgoff(UnkCurBranch,KnotsWithUnkBrnchs, Indep);
	vector<Rational> UnkLK(CountUnknown),UnkMKC(Indep.size());
	gayss(coefsLK,UnkLK,CountUnknown);
	PrintRes(UnkCurBranch,UnkLK);
	PrintSeparator();
	cout<<"\t\t2. МКТ\n\n";
	cout<<"Были выбраны следующие независимые контуры:\n\n";
	for (size_t i = 0; i < Indep.size(); i++)
	{
		cout<<Indep[i].GetName()<<": ";
		for(const Branch& b:Indep[i].GetBrnchs()){
			cout << b.G_N();
			if(b.G_N()!= (*(Indep[i].GetBrnchs().end()-1)).G_N())
			cout<<" -> ";
		}
		cout<<endl;
	}
	coefsMKC=MakeMatrixMKC(KnotsWithUnkBrnchs,Indep,SourCur);
	gayss(coefsMKC, UnkMKC, Indep.size());
	for (size_t i = 0; i < Indep.size(); i++) {
		cout << "Current I" << Indep[i].GetName() << " = " << UnkMKC[i] << endl<<endl;
	}
	cout<<"////////////////////////\n\n";
	vector<Rational>ResMKC(CountUnknown);
	for(size_t i=0;i<CountUnknown;i++){
		string Ib;
		int j=0;
		for(const Kontur&k:Indep){
			for(const Branch& b:k.GetBrnchs()){
				if(b.G_N()==UnkCurBranch[i].G_N()){
					if(b.GetIsFolow()){
						ResMKC[i]+=UnkMKC[j];
					}
					else{
						ResMKC[i] -= UnkMKC[j];
					}
				}
			}
			j++;
		}
		for (const Kontur& k : SourCur){
			for (const Branch& b : k.GetBrnchs()) {
				if (b.G_N() == UnkCurBranch[i].G_N()) {
					if (b.GetIsFolow()) {
						ResMKC[i] += k.GetBrnchs()[0].GI();
					}
					else {
						ResMKC[i] -= k.GetBrnchs()[0].GI();
					}
				}
			}
		}
	}
	PrintRes(UnkCurBranch, ResMKC);
	PrintSeparator();
	MKP(KnotsMKP,UnkbrMKP,AllbrMKP);
	system("pause");
	return 0;
}
