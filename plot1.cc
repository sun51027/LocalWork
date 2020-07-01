////////////
//
//	try to draw a histogram from ntuple as monoNtupleAnalyzer.cc
//	2020 6/14 
//
#include "iostream"
#include "TAttMarker.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TH1F.h"
#include "math.h"
using namespace std;
class Plot
{
public:
	Plot(){}
	void AddPlot(TH2D *h){plot[0] = h;}//assign h into plot	
	TH2D *GetPlot(){return plot[0];}//when GetPlot is called, the created plot will be return to calling function and fill data into the plots
	~Plot(){}
private:
	vector<TH2D*> plot;
};
class MonoCandidate
{
public:
  MonoCandidate(){}
  //This will be used in main function and to absord the data in root file
  MonoCandidate(double sh, double satsh, double dedxsig,double tiso, double xyp0, double xyp1, double xyp2,
    double rzp0, double rzp1, double rzp2,
    double dist, double f51, double f15,
    double e55, double hiso, double eta,
    double phi ):
  subHits_(sh),subSatHits_(satsh),dEdXSig_(dedxsig),tIso_(tiso),xyp0_(xyp0),
  xyp1_(xyp1),xyp2_(xyp2),rzp0_(rzp0),rzp1_(rzp1),rzp2_(rzp2),
  dist_(dist),f51_(f51),f15_(f15),e55_(e55),hIso_(hiso),
  eta_(eta),phi_(phi) { }
  //This will be used in comparing with cut
  MonoCandidate(const MonoCandidate &mc) : 
    subHits_(mc.subHits_),subSatHits_(mc.subSatHits_),dEdXSig_(mc.dEdXSig_),tIso_(mc.tIso_),
    xyp0_(mc.xyp0_),xyp1_(mc.xyp1_),xyp2_(mc.xyp2_),
    rzp0_(mc.rzp0_),rzp1_(mc.rzp1_),rzp2_(mc.rzp2_),
    dist_(mc.dist_),f51_(mc.f51_),f15_(mc.f15_),
    hIso_(mc.hIso_),eta_(mc.eta_),phi_(mc.phi_) { } //{ empty >////<} 
	
  ~MonoCandidate() {}
  //All candidates variable
  double subHits_;
  double subSatHits_;
  double dEdXSig_;
  double tIso_;
  double xyp0_;
  double xyp1_;
  double xyp2_;
  double rzp0_;
  double rzp1_;
  double rzp2_;

  double dist_;
  double f51_;
  double f15_;
  double e55_;
  double hIso_;
  double eta_;
  double phi_;
};
//build a cut class, use bool to check whether you want to use this cut
class MonoCut
{
public:
  //create plot
  MonoCut(){};
  ~MonoCut(){};
  //create plots
  MonoCut(string & plotname){
  cout<<"hi"<<endl; 
	Plot &z = test[0];
	z.AddPlot(new TH2D("h_FracSatVNstrips","Fraction of saturated strips vs. no. of strips",100,0,1000,100,0,1));
 }
  //note: doAnalysis is in a loop(for 1000 events
  //so the h->Fill() will run for 1000 times
  void doAnalysis(const vector<MonoCandidate> &cands){ //, string h){
	
	//get the results of the cuts
	const MonoCandidate &cand = cands[0];//only take the first candidate group?(for 1000 events)
	// what is  cands[0]??
	const bool qualRes = evalQuality(cand);
	const bool eRes = evalE(cand);
        const bool f51Res = evalF51(cand);
        const bool dEdXRes = evaldEdX(cand);
//	if(qualRes && eRes && f51Res && dEdXRes){
	Plot &z = test[0];
	z.GetPlot()->Fill(cand.subHits_,cand.subSatHits_/cand.subHits_);

//	h_FracSatVNstrips->Fill(cand.subHits_,cand.subSatHits_/cand.subHits_);
	
	
  }	

private:  

  vector<Plot> test;
  constexpr static const double dCut_=0.5;
  constexpr static const double hIsoCut_=10;
  constexpr static const double xyp0Cut_=0.6;
  constexpr static const double xyp2Cut_=1000;
  constexpr static const double rzp0Cut_=10;
  constexpr static const double rzp1Cut_ = 999; 
  constexpr static const double rzp2Cut_ = 0.005;
  constexpr static const double eCut_ = 200.;
  constexpr static const double f51Cut_ = 0.85;
  constexpr static const double dEdXSigCut_ = 10;
  constexpr static const double f51LooseCut_ = 0.7;
  constexpr static const double dEdXSigLooseCut_ = 7;

 //cut because eval are private, so you have to draw plots in this class
  inline bool evalQuality(const MonoCandidate &c ){ return (c.dist_< dCut_ &&c.hIso_ < hIsoCut_ && c.xyp0_ < xyp0Cut_ && c.xyp2_ > xyp2Cut_ ); }
  inline bool evalE(const MonoCandidate & c ) { return c.e55_ > eCut_; }
  inline bool evalF51(const MonoCandidate & c) { return c.f51_ > f51Cut_ ; }
  inline bool evaldEdX(const MonoCandidate & c) { return c.dEdXSig_ > dEdXSigCut_; }
};
void plot1()
{
        TFile *fin = new TFile("MonopoleNtuple1000_2017_20evt.root");
        TTree *tree = (TTree*)fin->Get("monopoles");
	
	Bool_t passHLT_Photon200;
  	vector<bool> * trigResults = 0;
  	vector<string> * trigNames = 0;

	unsigned nCandidates;
	vector<double> *subHits=0;
	vector<double> *subSatHits=0;
	vector<double> *dEdXSig=0;
	vector<double> * tIso = 0;
  	vector<double> * xyp0 = 0;
  	vector<double> * xyp1 = 0;
  	vector<double> * xyp2 = 0;
  	vector<double> * rzp0 = 0;
  	vector<double> * rzp1 = 0;
  	vector<double> * rzp2 = 0;
	
	vector<double> * dist = 0;
	vector<double> * f51 = 0;
	vector<double> * f15 = 0;
	vector<double> * e55 = 0;
	vector<double> * hIso = 0;
	vector<double> * eta = 0;
	vector<double> * phi = 0;

	tree->SetBranchAddress("trigResult",&trigResults);
  	tree->SetBranchAddress("trigNames",&trigNames);
 	tree->SetBranchAddress("passHLT_Photon200" , &passHLT_Photon200);
	tree->SetBranchAddress("cand_N",&nCandidates);
        tree->SetBranchAddress("cand_SubHits",&subHits);
	tree->SetBranchAddress("cand_SatSubHits",&subSatHits);
	tree->SetBranchAddress("cand_dEdXSig",&dEdXSig);
	tree->SetBranchAddress("cand_TIso",&tIso);
	tree->SetBranchAddress("cand_f51",&f51);
  	tree->SetBranchAddress("cand_f15",&f15);
  	tree->SetBranchAddress("cand_e55",&e55);
  	tree->SetBranchAddress("cand_HIso",&hIso);
  	tree->SetBranchAddress("cand_XYPar0",&xyp0);
  	tree->SetBranchAddress("cand_XYPar1",&xyp1);
  	tree->SetBranchAddress("cand_XYPar2",&xyp2);
  	tree->SetBranchAddress("cand_RZPar0",&rzp0);
  	tree->SetBranchAddress("cand_RZPar1",&rzp1);
  	tree->SetBranchAddress("cand_RZPar2",&rzp2);
  	tree->SetBranchAddress("cand_eta",&eta);
  	tree->SetBranchAddress("cand_phi",&phi);
	tree->SetBranchAddress("cand_dist",&dist);	
	
//	TH2D *h_FracSatVNstrips = new TH2D("h_FracSatVNstrips","Fraction of saturated strips vs. no. of strips",100,0,1000,100,0,1);
	const unsigned NEvents = tree->GetEntries();
//	cout<<"No. events = "<<NEvents<<endl;

	//SetPlot
	MonoCut NoTRG;

	vector<double> cand_x;
	vector<double> cand_y;
	vector<string> TriggerNameList;
	TriggerNameList.push_back("HLT_Photon200_v");
	const unsigned nTrigs = trigNames->size();	
	int count_evt;
	vector<MonoCandidate> candVec(10);//default the length of candVec(including all of physical component)	
	for(unsigned ev=0; ev<NEvents;ev++){
//		int test_HLT=0;
		tree->GetEntry(ev);
//		cout<<nCandidates<<endl;
		//the number of candidates of every entries is different, so resize the default size(10) to the real size in every entries
		if(nCandidates>candVec.size()) candVec.resize(nCandidates);
		//get the candidates of all branch
//		cout<<"trigNames-= "<<trigNames<<endl;
		for(unsigned i=0;i<nCandidates;i++){
			//put every candidate information into the function 
			candVec[i] = MonoCandidate(
			        (*subHits)[i],
			        (*subSatHits)[i],
			        (*dEdXSig)[i],
			        (*tIso)[i],
			        (*xyp0)[i],
			        (*xyp1)[i],
			        (*xyp2)[i],
			        (*rzp0)[i],
 			        (*rzp1)[i],
			        (*rzp2)[i],
			        (*dist)[i],
			        (*f51)[i],
			        (*f15)[i],
			        (*e55)[i],
			        (*hIso)[i],
			        (*eta)[i],
				(*phi)[i]
      				);
		}
	NoTRG.doAnalysis(candVec);
//			if((*trigNames)[i]==TriggerNameList[i])
//			cout<<"triggernamelist = "<<TriggerNameList[i]<<endl;
//			cout<<"Trigger name"<<(*trigNames)[i]<<endl;
			/*if(passHLT_Photon200 == true&&(*e55)[i]>200&&
				(*dEdXSig)[i]>10&&(*f51)[i]>0.85&&(*xyp0)[i]<0.6&&(*xyp2)[i]<1000
				&&(*rzp0)[i]<10&&(*rzp1)[i]<999&&(*rzp2)[i]<0.005
				&&(*hIso)[i]<10&&(*dist)[i]<0.5){*/
//			cand_x.push_back((*subHits)[i]);
//			cand_y.push_back((*subSatHits)[i]); 
//			h_FracSatVNstrips->Fill(cand_x[i],cand_y[i]/cand_x[i]);
//			cout<<"Entries = "<<cand_y[i]/cand_x[i]<<endl;
			//count_evt++;
			//}

		}
//			cout<<"test_HLT = "<<test_HLT<<endl;

//	}
//	h_FracSatVNstrips->SetMarkerColor(kRed);
//	gStyle->SetOptStat(0);
/*	h_FracSatVNstrips->SetXTitle("Total No. of Strips");
	h_FracSatVNstrips->SetYTitle("fraction of saturated strips");
	h_FracSatVNstrips->Draw();			
*/
}
