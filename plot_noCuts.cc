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
class MonoCuts
{
public:
  MonoCuts(){}
  ~MonoCuts(){}
  void doAnalysis(vector<MonoCandidate> &cand)
  {
	//get all cuts and draw plots
	//NoCuts+1Cuts+...4Cuts
	//passing Trigger cuts
	MonoCandidate &cands = cand[0];
	bool QualCut = evalQuality(cands);
	bool ECut = evalE(cands);
	bool F51Cut = evalF51(cands);
	bool dEdXCut = evaldEdX(cands);
	
	if(QualCut)
	{
//		count++;
//		cout<<"count = "<<count<<endl;
	}
	if(QualCut && ECut )
	{};
		
  }

private:
  //cuts analysis
  bool evalQuality(MonoCandidate &mc) { return mc.xyp0_ < xyp0Cut_&& mc.xyp2_ > xyp2Cut_ 
			&& mc.dist_ < distCut_  && mc.hIso_ <hIsoCut_;  }
  bool evalE(MonoCandidate &mc) { return mc.e55_ > e55Cut_; }
  bool evalF51(MonoCandidate &mc) { return mc.f51_ > f51Cut_ ; }
  bool evaldEdX(MonoCandidate &mc) { return mc.dEdXSig_ > dEdXSigCut_ ;}
  //count for cutting events
  int Qual_count=0;
  int E_count=0; 
  //Cuts parameters
  const double xyp0Cut_=0.6;
  const double xyp2Cut_=1000;
  const double rzp0Cut_=10;
  const double rzp1Cut_=999;
  const double rzp2Cut_=0.005;
  const double distCut_ = 0.5;
  const double hIsoCut_= 10;
  const double dEdXSigCut_ = 9;
  const double e55Cut_ = 175;
  const double f51Cut_ = 0.85;
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

	TCanvas *canvas = new TCanvas("canvas","canvas",800,600);
	TH2D *h_FracSatVNstrips = new TH2D("h_FracSatVNstrips","Fraction of saturated strips vs. no. of strips",100,0,1000,100,0,1);
	TH1D *h_DedXSig = new TH1D("h_DedXSig","dE/dX significant distribution",100,0,30);
	TH1D *h_f51 = new TH1D("h_f51","f51",100,0.2,1.1);
	TH1D *h_hIso = new TH1D("h_hIso","hIso",100,-1,15);	
	TH1D *h_Energy = new TH1D("h_Energy","Energy",100,0,1500);
	TH1D *h_RZcurv = new TH1D("h_RZcurv","",100,-0.1,0.1);
	TH2D *h_ABCD = new TH2D("h_ABCD","",100,0,1.1,100,0,30);
	
        const unsigned NEvents = tree->GetEntries();
	MonoCuts Cuts;
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
//                cout<<"subHits["<<ev<<"]["<<i<<"] = "<<cand[i].subHits_<<endl;

		}
		sort(cand.begin(),cand.begin()+nCandidates);
//		cout<<"sort result: "<<endl;
//		cout<<"subHits["<<i<<cand[i].subHits_
		//cut
//		Cuts.doAnalysis(cand);	       		
	 	//draw plot with no cuts(which are significance in Mai's thesis)
//		if(passHLT_Photon200==true){
		h_FracSatVNstrips->Fill(cand[2].subHits_,cand[2].subSatHits_/cand[2].subHits_);
		h_DedXSig->Fill(cand[0].dEdXSig_);
		h_f51->Fill(cand[0].f51_);
		h_hIso->Fill(cand[0].hIso_);
		h_Energy->Fill(cand[0].e55_);
		h_RZcurv->Fill(cand[0].rzp2_);
//		if(passHLT_Photon200==true&&cand[0].e55_>200)
		//After calculating the efficiency
//		h_ABCD->Fill(cand[0].f51_,cand[0].dEdXSig_);
//		}
	}

        gStyle->SetOptStat(0);

	h_FracSatVNstrips->SetXTitle("Total No. of Strips");
        h_FracSatVNstrips->SetYTitle("fraction of saturated strips");
	h_FracSatVNstrips->SetTitle("");
        h_FracSatVNstrips->Draw();        
	h_FracSatVNstrips->SetMarkerStyle(7);
	mgr::SetSinglePad(canvas);
        mgr::SetAxis(h_FracSatVNstrips);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("1000 Entires");
//	canvas->SaveAs("h_FracSatVNstrips.pdf");

/*	h_DedXSig->SetXTitle("dE/dX Significance");
	h_DedXSig->SetYTitle("Entries");
	h_DedXSig->SetTitle("");
	h_DedXSig->SetLineColorAlpha(28,0.5);
        h_DedXSig->SetFillColor(42);
	h_DedXSig->Draw();
	mgr::SetSinglePad(canvas);
        mgr::SetAxis(h_DedXSig);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("1000 Entires");
	TLegend *leg = new TLegend(0.18,0.77,0.43,0.82); 
	leg->SetBorderSize( 0 );
        leg->SetFillColorAlpha( 0, 0 );
	leg->AddEntry(h_DedXSig,"1000 GeV","f");
	leg->Draw();
	canvas->SaveAs("h_DedXSig.pdf");
	
	h_f51->SetXTitle("f51(Ecystal/E5x5)");
	h_f51->SetYTitle("Entries");
	h_f51->SetLineColorAlpha(28,0.5);
        h_f51->SetFillColor(42);
	h_f51->SetTitle("");
	h_f51->Draw();
	mgr::SetSinglePad(canvas);
        mgr::SetAxis(h_f51);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("1000 Entires");
	TLegend *leg2 = new TLegend(0.18,0.77,0.43,0.82);
        leg2->SetBorderSize( 0 );
        leg2->SetFillColorAlpha( 0, 0 );
        leg2->AddEntry(h_f51,"1000 GeV","f");
        leg2->Draw();
	canvas->SaveAs("h_f51.pdf");
	
	h_hIso->SetXTitle("Energy(GeV)");
	h_hIso->SetYTitle("Entries");
	h_hIso->SetLineColorAlpha(28,0.5);
        h_hIso->SetFillColor(42);
	h_hIso->SetTitle("");
	h_hIso->Draw();
	mgr::SetSinglePad(canvas);
        mgr::SetAxis(h_hIso);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("1000 Entires");
	TLegend *leg3 = new TLegend(0.7,0.77,0.95,0.82);
        leg3->SetBorderSize( 0 );
        leg3->SetFillColorAlpha( 0, 0 );
        leg3->AddEntry(h_hIso,"1000 GeV","f");
        leg3->Draw();
	canvas->SaveAs("h_hIso.pdf");

	h_RZcurv->SetXTitle("R-Z curvature");
        h_RZcurv->SetYTitle("Entries");
        h_RZcurv->SetLineColorAlpha(28,0.5);
        h_RZcurv->SetFillColor(42);
        h_RZcurv->SetTitle("");
        h_RZcurv->Draw();
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(h_RZcurv);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("1000 Entires");
        TLegend *leg4 = new TLegend(0.7,0.77,0.95,0.82);
        leg4->SetBorderSize( 0 );
        leg4->SetFillColorAlpha( 0, 0 );
        leg4->AddEntry(h_RZcurv,"1000 GeV","f");
        leg4->Draw();
        canvas->SaveAs("h_RZcurv.pdf");

	h_Energy->SetXTitle("E5x5(GeV)");
        h_Energy->SetYTitle("Entries");
        h_Energy->SetLineColorAlpha(28,0.5);
        h_Energy->SetFillColor(42);
        h_Energy->SetTitle("");
        h_Energy->Draw();
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(h_Energy);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("1000 Entires");
        TLegend *leg5 = new TLegend(0.7,0.77,0.95,0.82);
        leg5->SetBorderSize( 0 );
        leg5->SetFillColorAlpha( 0, 0 );
        leg5->AddEntry(h_Energy,"1000 GeV","f");
        leg5->Draw();
        canvas->SaveAs("h_Energy.pdf");


	h_ABCD->SetXTitle("f51");
        h_ABCD->SetYTitle("dE/dX significance");
        h_ABCD->SetTitle("");
	h_ABCD->SetMarkerStyle(7);
        h_ABCD->Draw();
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(h_ABCD);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("1000 Entires");
	TLine *TightY = new TLine(0,9,1.1,9);
	TightY->SetLineColor(4);
	TightY->SetLineStyle(7);
	TightY->SetLineWidth(3);
	TightY->Draw("same");
	TLine *TightX = new TLine(0.85,0,0.85,30);
        TightX->SetLineColor(4);
        TightX->SetLineStyle(7);
        TightX->SetLineWidth(3);
        TightX->Draw("same");
        TLine *LooseY = new TLine(0,7,1.1,7);
        LooseY->SetLineColor(38);
        LooseY->SetLineStyle(7);
        LooseY->Draw("same");
        TLine *LooseX = new TLine(0.6,0,0.6,30);
        LooseX->SetLineColor(38);
        LooseX->SetLineStyle(7);
        LooseX->Draw("same");
        canvas->SaveAs("h_ABCD.pdf");
*/
}

