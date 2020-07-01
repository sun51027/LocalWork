////////////
//
//      try to draw significance histogram from ntuple as monoNtupleAnalyzer.cc
//      2020 6/14 
//
#include "iostream"
#include "TAttMarker.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TH1F.h"
#include "math.h"
#include <algorithm>
using namespace std;
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
  void print(){
	cout<<"subHits  = "<<subHits_<<endl;
  } 
  bool operator<(const MonoCandidate &mc)const{
  if(dEdXSig_>mc.dEdXSig_) return true;
    else if(dEdXSig_==mc.dEdXSig_){
	if(f51_>mc.f51_) return true;
	else return false;
	}
    else return false;
  }
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
void plot()
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

	TH2D *h_FracSatVNstrips = new TH2D("h_FracSatVNstrips","Fraction of saturated strips vs. no. of strips",100,0,1000,100,0,1);
	TH1D *h_DedXSig = new TH1D("h_DedXSig","dE/dX significant distribution",100,0,30);
	TH1D *h_f51 = new TH1D("h_f51","f51",100,0,1.1);
	
        const unsigned NEvents = tree->GetEntries();
	vector<double> cand_subHits;
        vector<double> cand_subSatHits;
        vector<double> cand_dEdXsig;
        vector<double> cand_f51;
	
	vector<MonoCandidate> cand(10);	
        for(unsigned ev=0; ev<NEvents;ev++){
             tree->GetEntry(ev);
		if(nCandidates>cand.size()) cand.resize(nCandidates);
		for(unsigned i=0;i<nCandidates;i++){
		cand[i] = MonoCandidate(
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
//		cand[0].print();
		sort(cand.begin(),cand.begin()+nCandidates);
		//cut
		//I have to get the member of cand[i]
        	h_FracSatVNstrips->Fill(cand[0].subHits_,cand[0].subSatHits_/cand[0].subHits_);
		h_DedXSig->Fill(cand[0].dEdXSig_);
		h_f51->Fill(cand[0].f51_);

	}

        gStyle->SetOptStat(0);
	h_FracSatVNstrips->SetXTitle("Total No. of Strips");
        h_FracSatVNstrips->SetYTitle("fraction of saturated strips");
//        h_FracSatVNstrips->Draw();        
	h_FracSatVNstrips->SaveAs("h_FracSatVNstrips.pdf");
	h_DedXSig->SetXTitle("dE/dX Significance");
	h_DedXSig->SetYTitle("Entries");
//	h_DedXSig->Draw();
	h_DedXSig->SaveAs("h_DedXSig.pdf");
	
	h_f51->Draw("e");
}

