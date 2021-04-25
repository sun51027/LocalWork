#include "iostream"
#include "TAttMarker.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TH1F.h"
#include "math.h"
#include <algorithm>
#include <string>
//#include<vector>
using namespace std;
enum PlotType{
	Random = 0,
	Uniform,
	Gauss
};
class PlotSet
{
public:
  PlotSet(){plots_.resize(3);};
  ~PlotSet(){};
  void AddPlot(PlotType pt,TH1 *h){ plots_.push_back(h);}
  //pt is enum,not TH1, it just a codename,usually we use 012...in a 
  TH1 * GetPlot(PlotType pt){return plots_[pt];}
private:
  vector<TH1*> plots_;
};

void histrograms(){

	TRandom3 rnd(1234);
	string h_name;
	TCanvas *c = new TCanvas("c","",800,600);
	vector<PlotSet> test;
	PlotSet z;
	test.push_back(z);
	z.AddPlot(Random,new TH1D("test","",100,-0.1,1.1));
	z.AddPlot(Uniform,new TH1D("test2","",100,-0.1,1.1));	

	PlotSet y;
	test.push_back(y);
//	y.AddPlot(
//	for(int k=0;k<2;k++){
	if(!test.empty()){
	        for(int i=0;i<10000;i++){ 
		z.GetPlot(Random)->Fill(rnd.Rndm());
		z.GetPlot(Random)->Draw();
		z.GetPlot(Uniform)->Fill(rnd.Uniform());
		z.GetPlot(Uniform)->Draw("same");
		}
	}
	       // Draw();
		

	
//	for(int i=0;i<10000;i++) h1->Fill(rnd.Rndm());
//	h1->Draw();

}

