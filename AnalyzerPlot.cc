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
#include <string>
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
  void doAnalysis(vector<MonoCandidate> &cand, bool TRG)
  {
	//get all cuts and draw plots
	//NoCuts+1Cuts+...4Cuts
	//passing Trigger cuts
	MonoCandidate &cands = cand[0];
	
	bool QualCut = evalQuality(cands);
	bool ECut = evalE(cands);
	bool F51Cut = evalF51(cands);
	bool dEdXCut = evaldEdX(cands);
	//count for total events without TRG
	
	count++;
	if(QualCut) Qual++;
	if(ECut) E++;
	if(F51Cut) f51++;
	if(dEdXCut) dEdX++;
	//signal efficiency
	if(QualCut) Qual_count++;
	if(QualCut && ECut ) E_count++;		
	if(QualCut && ECut && F51Cut) f51_count++;
	if(QualCut && ECut && F51Cut && dEdXCut) dEdX_count++;
	//relative efficiency
	if( QualCut && ECut && F51Cut ) NodEdXCut++;
	if( QualCut && F51Cut && dEdXCut ) NoE++;
	if( QualCut && ECut && dEdXCut ) NoF51++;
	if( ECut && F51Cut && dEdXCut )  NoQual++;
	if( QualCut && ECut & F51Cut && dEdXCut) NoTRG++;
	
	//Apply HLT
	if(TRG)
	{
   	  count_TRG++;
          //signal efficiency
          if(QualCut) Qual_count_TRG++;
          if(QualCut && ECut ) E_count_TRG++;
          if(QualCut && ECut && F51Cut) f51_count_TRG++;
          if(QualCut && ECut && F51Cut && dEdXCut) dEdX_count_TRG++;
          //relative efficiency
          if( QualCut && ECut && F51Cut ) No_TRGdEdXCut++;
          if( QualCut && F51Cut && dEdXCut ) No_TRGE++;
          if( QualCut && ECut && dEdXCut ) No_TRGF51++;
          if( ECut && F51Cut && dEdXCut )  No_TRGQual++;
	}
	  if( QualCut && ECut && F51Cut && dEdXCut) No_TRGTRG++;

		
  }
  void SignalEff()
  {
	//signal efficiency = no. of events after all selection cuts/all events
	cout<<"No TRG ==================================="<<endl;
	cout<<"        TRG "<<count<<endl;
	cout<<"QualityCuts "<<Qual_count<<endl;
	cout<<"       ECut "<<E_count<<endl;
	cout<<"     F51Cut "<<f51_count<<endl;
	cout<<" dEdXSigCut "<<dEdX_count<<endl;
	cout<<"------------------------------------------"<<endl;
	cout<<"Relative effciency count------------------"<<endl;
        cout<<"------------------------------------------"<<endl;	
	cout<<"     No TRG "<<NoTRG<<endl;
        cout<<" No Quality "<<NoQual<<endl;
        cout<<"    No ECut "<< NoE <<endl;
        cout<<"  No F51Cut "<<NoF51<<endl;
        cout<<" No dEdXSig "<<NodEdXCut<<endl;
	cout<<"=========================================="<<endl;
	cout<<"Signal efficiency = "<<(double)dEdX_count/(double)count<<endl;
        cout<<"------------------------------------------"<<endl;
	cout<<"Relative efficiency-----------------------"<<endl;
        cout<<"------------------------------------------"<<endl;
	cout<<"        TRG "<<(double)dEdX_count/(double)NoTRG<<endl;
        cout<<"QualityCuts "<<(double)dEdX_count/(double)NoQual<<endl;
        cout<<"       ECut "<<(double)dEdX_count/(double)NoE<<endl;
        cout<<"     F51Cut "<<(double)dEdX_count/(double)NoF51<<endl;
        cout<<" dEdXSigCut "<<(double)dEdX_count/(double)NodEdXCut<<endl;

	cout<<endl;
	cout<<"TRG pass ================================="<<endl;
	cout<<"        TRG "<<count_TRG<<endl;
        cout<<"QualityCuts "<<Qual_count_TRG<<endl;
        cout<<"       ECut "<<E_count_TRG<<endl;
        cout<<"     F51Cut "<<f51_count_TRG<<endl;
        cout<<" dEdXSigCut "<<dEdX_count_TRG<<endl;
        cout<<"------------------------------------------"<<endl;
        cout<<"Relative effciency -----------------------"<<endl;
        cout<<"------------------------------------------"<<endl;
        cout<<"     No TRG "<<No_TRGTRG<<endl;
        cout<<" No Quality "<<No_TRGQual<<endl;
        cout<<"    No ECut "<< No_TRGE <<endl;
        cout<<"  No F51Cut "<<No_TRGF51<<endl;
        cout<<" No dEdXSig "<<No_TRGdEdXCut<<endl;
	cout<<"==========================================="<<endl;
	cout<<"Signal efficiency = "<<(double)dEdX_count_TRG/(double)count<<endl;
	cout<<"------------------------------------------"<<endl;
        cout<<"Relative efficiency-----------------------"<<endl;
        cout<<"------------------------------------------"<<endl;
        cout<<"        TRG "<<(double)dEdX_count_TRG/(double)No_TRGTRG<<endl;
        cout<<"QualityCuts "<<(double)dEdX_count_TRG/(double)No_TRGQual<<endl;
        cout<<"       ECut "<<(double)dEdX_count_TRG/(double)No_TRGE<<endl;
        cout<<"     F51Cut "<<(double)dEdX_count_TRG/(double)No_TRGF51<<endl;
        cout<<" dEdXSigCut "<<(double)dEdX_count_TRG/(double)No_TRGdEdXCut<<endl;
	
  }



  //Cuts parameters
  static const double xyp0Cut_ ;
  static const double xyp2Cut_ ;
  static const double rzp0Cut_ ;
  static const double rzp1Cut_ ;
  static const double rzp2Cut_ ;
  static const double distCut_ ;
  static const double hIsoCut_ ;
  static const double dEdXSigCut_ ;
  static const double e55Cut_ ;
  static const double f51Cut_ ;
   // if you want to set parameter in the class, you should add constexpr
  //  ex. constexpr static const double x=1;

	
private:
  //cuts analysis
  bool evalQuality(MonoCandidate &mc) { return mc.xyp0_ < xyp0Cut_&& mc.xyp2_ > xyp2Cut_ 
			&& mc.dist_ < distCut_  && mc.hIso_ <hIsoCut_;  }
  bool evalE(MonoCandidate &mc) { return mc.e55_ > e55Cut_; }
  bool evalF51(MonoCandidate &mc) { return mc.f51_ > f51Cut_ ; }
  bool evaldEdX(MonoCandidate &mc) { return mc.dEdXSig_ > dEdXSigCut_ ;}
  //no. of every selections 
  int Qual=0;
  int E=0;
  int f51=0;
  int dEdX=0;
  //count for cutflow 
  int count=0;
  int Qual_count=0;
  int E_count=0;
  int f51_count=0;
  int dEdX_count=0; 
  //relative eff without HLT
  int NoTRG=0;
  int NoQual=0;
  int NoE=0;
  int NoF51=0;
  int NodEdXCut=0;
  //Apply TRG 
  int count_TRG=0;
  int Qual_count_TRG=0;
  int E_count_TRG=0;
  int f51_count_TRG=0;
  int dEdX_count_TRG=0;
  //relative eff with HLT
  int No_TRGTRG=0;
  int No_TRGQual=0;
  int No_TRGE=0;
  int No_TRGF51=0;
  int No_TRGdEdXCut=0;

/*  //Cuts parameters
  static const double xyp0Cut_ ;
  static const double xyp2Cut_ ;
  static const double rzp0Cut_ ;
  static const double rzp1Cut_ ;
  static const double rzp2Cut_ ;
  static const double distCut_ ;
  static const double hIsoCut_ ;
  static const double dEdXSigCut_ ;
  static const double e55Cut_ ;
  static const double f51Cut_ ;
   // if you want to set parameter in the class, you should add constexpr
  //  ex. constexpr static const double x=1;
*/
};



  //Cuts parameters
  const double MonoCuts::xyp0Cut_=0.6;
  const double MonoCuts::xyp2Cut_=1000;
  const double MonoCuts::rzp0Cut_=10;
  const double MonoCuts::rzp1Cut_=999;
  const double MonoCuts::rzp2Cut_=0.005;
  const double MonoCuts::distCut_ = 0.5;
  const double MonoCuts::hIsoCut_= 10;
  const double MonoCuts::dEdXSigCut_ = 9;
  const double MonoCuts::e55Cut_ = 200;
  const double MonoCuts::f51Cut_ = 0.85;

  const string Mass = "1000 GeV(DeltaRay off)";


void AnalyzerPlot()
{
//	TFile *fin = new TFile("MonoNtuple_MC_2018_1000_DeltaRayOff.root");
//	TFile *fin = new TFile("MonoNtuple_MC_2018_1000.root");
        TFile *fin = new TFile("MonoNtuple_MC_2018_3000.root");
// 	TFile *fin = new TFile("MonopoleNtuple1000_2017_20evt.root");
        TTree *tree = (TTree*)fin->Get("monopoles");
        Bool_t passHLT_Photon200;
	Bool_t passHLT_Photon175;
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
	tree->SetBranchAddress("passHLT_Photon175" , &passHLT_Photon175);
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
	//NO TRG plot
	TH2D *h_FracSatVNstrips = new TH2D("h_FracSatVNstrips","Fraction of saturated strips vs. no. of strips",100,0,1000,100,0,1);
	TH1D *h_DedXSig = new TH1D("h_DedXSig","dE/dX significant distribution",100,0,30);
	TH1D *h_f51 = new TH1D("h_f51","f51",100,0.2,1.1);
	TH1D *h_hIso = new TH1D("h_hIso","hIso",100,-1,15);	
	TH1D *h_Energy = new TH1D("h_Energy","Energy",100,100,800);
	TH1D *h_RZcurv = new TH1D("h_RZcurv","",100,-0.01,0.01);
	TH2D *h_ABCD = new TH2D("h_ABCD","",100,0,1.1,100,0,30);
	//HLT pass
        TH2D *HLT_FracSatVNstrips = new TH2D("HLT_FracSatVNstrips","Fraction of saturated strips vs. no. of strips",100,0,1000,100,0,1);
        TH1D *HLT_DedXSig = new TH1D("HLT_DedXSig","dE/dX significant distribution",100,0,30);
        TH1D *HLT_f51 = new TH1D("HLT_f51","f51",100,0.2,1.1);
        TH1D *HLT_hIso = new TH1D("HLT_hIso","hIso",100,-1,15);
        TH1D *HLT_Energy = new TH1D("HLT_Energy","Energy",100,100,800);
        TH1D *HLT_RZcurv = new TH1D("HLT_RZcurv","",100,-0.01,0.01);
        TH2D *HLT_ABCD = new TH2D("HLT_ABCD","",100,0,1.1,100,0,30);

	double subHits_count=0;
	double subSatHits_count=0;
	int test=0;
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
		
//		cout<<"Trigger  "<<(*trigNames)[ev]<<endl;
		cout<<"subHits["<<ev<<"] "<<cand[0].subHits_<<endl;		
		cout<<"SatSubHits["<<ev<<"]"<<cand[0].subSatHits_<<endl;
		sort(cand.begin(),cand.begin()+nCandidates);
		//cut
		Cuts.doAnalysis(cand,passHLT_Photon200);	       		
	 	//draw plot with no cuts(which are significance in Mai's thesis)
//		cout<<"e5x5["<<ev<<"] "<<cand[0].e55_<<endl;
//		if(cand[0].e55_>200) test++;
		subHits_count+=cand[0].subHits_;
		subSatHits_count+=cand[0].subSatHits_;
		h_FracSatVNstrips->Fill(cand[0].subHits_,cand[0].subSatHits_/cand[0].subHits_);
		h_DedXSig->Fill(cand[0].dEdXSig_);
		h_f51->Fill(cand[0].f51_);
		h_hIso->Fill(cand[0].hIso_);
		h_Energy->Fill(cand[0].e55_);
		h_RZcurv->Fill(cand[0].rzp2_);
		h_ABCD->Fill(cand[0].f51_,cand[0].dEdXSig_);

		if(passHLT_Photon200==true){
                HLT_FracSatVNstrips->Fill(cand[0].subHits_,cand[0].subSatHits_/cand[0].subHits_);
                HLT_DedXSig->Fill(cand[0].dEdXSig_);
                HLT_f51->Fill(cand[0].f51_);
                HLT_hIso->Fill(cand[0].hIso_);
                HLT_Energy->Fill(cand[0].e55_);
                HLT_RZcurv->Fill(cand[0].rzp2_);
                HLT_ABCD->Fill(cand[0].f51_,cand[0].dEdXSig_);
                }


	}

	cout<<"subHits_count = "<<subHits_count<<endl;
	cout<<"subSatHits_count = "<< subSatHits_count<<endl;
//	cout<<"e55>200 = "<<test<<endl;
	Cuts.SignalEff();
        gStyle->SetOptStat(0);
	
/*	//NO TRG
	h_FracSatVNstrips->SetXTitle("Total No. of Strips");
        h_FracSatVNstrips->SetYTitle("fraction of saturated strips");
	h_FracSatVNstrips->SetTitle("");
        h_FracSatVNstrips->Draw();        
//	h_FracSatVNstrips->SetMarkerStyle(7);
	mgr::SetSinglePad(canvas);
        mgr::SetAxis(h_FracSatVNstrips);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
	canvas->SaveAs("FracSatVNstrips_15k.pdf");

	h_DedXSig->SetXTitle("dE/dX Significance");
	h_DedXSig->SetYTitle("Entries");
	h_DedXSig->SetTitle("");
	h_DedXSig->SetLineColorAlpha(28,0.5);
        h_DedXSig->SetFillColor(42);
	h_DedXSig->Draw();
	mgr::SetSinglePad(canvas);
        mgr::SetAxis(h_DedXSig);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
	TLegend *leg = new TLegend(0.18,0.77,0.43,0.82); 
	leg->SetBorderSize( 0 );
        leg->SetFillColorAlpha( 0, 0 );
	leg->AddEntry(h_DedXSig,Mass.c_str(),"f");
	leg->Draw();
	canvas->SaveAs("DedXSig_15k.pdf");
	
	h_f51->SetXTitle("f51(E5x1/E5x5)");
	h_f51->SetYTitle("Entries");
	h_f51->SetLineColorAlpha(28,0.5);
        h_f51->SetFillColor(42);
	h_f51->SetTitle("");
	h_f51->Draw();
	mgr::SetSinglePad(canvas);
        mgr::SetAxis(h_f51);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
	TLegend *leg2 = new TLegend(0.18,0.77,0.43,0.82);
        leg2->SetBorderSize( 0 );
        leg2->SetFillColorAlpha( 0, 0 );
        leg2->AddEntry(h_f51,Mass.c_str(),"f");
        leg2->Draw();
	canvas->SaveAs("f51_15k.pdf");
	
	h_hIso->SetXTitle("Energy(GeV)");
	h_hIso->SetYTitle("Entries");
	h_hIso->SetLineColorAlpha(28,0.5);
        h_hIso->SetFillColor(42);
	h_hIso->SetTitle("");
	h_hIso->Draw();
	mgr::SetSinglePad(canvas);
        mgr::SetAxis(h_hIso);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
	TLegend *leg3 = new TLegend(0.7,0.77,0.95,0.82);
        leg3->SetBorderSize( 0 );
        leg3->SetFillColorAlpha( 0, 0 );
        leg3->AddEntry(h_hIso,Mass.c_str(),"f");
        leg3->Draw();
	canvas->SaveAs("hIso_15k.pdf");

	h_RZcurv->SetXTitle("R-Z curvature");
        h_RZcurv->SetYTitle("Entries");
        h_RZcurv->SetLineColorAlpha(28,0.5);
        h_RZcurv->SetFillColor(42);
        h_RZcurv->SetTitle("");
        h_RZcurv->Draw();
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(h_RZcurv);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
        TLegend *leg4 = new TLegend(0.7,0.77,0.95,0.82);
        leg4->SetBorderSize( 0 );
        leg4->SetFillColorAlpha( 0, 0 );
        leg4->AddEntry(h_RZcurv,Mass.c_str(),"f");
        leg4->Draw();
        canvas->SaveAs("RZcurv_15k.pdf");

/*	h_Energy->SetXTitle("E5x5(GeV)");
        h_Energy->SetYTitle("Entries");
        h_Energy->SetLineColorAlpha(28,0.5);
        h_Energy->SetFillColor(42);
        h_Energy->SetTitle("");
        h_Energy->Draw();
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(h_Energy);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("2000 Entires");
        TLegend *leg5 = new TLegend(0.7,0.77,0.95,0.82);
        leg5->SetBorderSize( 0 );
        leg5->SetFillColorAlpha( 0, 0 );
        leg5->AddEntry(h_Energy,Mass.c_str(),"f");
        leg5->Draw();
        canvas->SaveAs("Energy.pdf");



	h_ABCD->SetXTitle("f51");
        h_ABCD->SetYTitle("dE/dX significance");
        h_ABCD->SetTitle("");
	h_ABCD->SetMarkerStyle(7);
        h_ABCD->Draw();
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(h_ABCD);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
	TLine *TightY = new TLine(0,MonoCuts::dEdXSigCut_,1.1,MonoCuts::dEdXSigCut_);
	TightY->SetLineColor(4);
	TightY->SetLineStyle(7);
	TightY->SetLineWidth(3);
	TightY->Draw("same");
	TLine *TightX = new TLine(MonoCuts::f51Cut_,0,MonoCuts::f51Cut_,30);
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
        canvas->SaveAs("ABCD_15k.pdf");


	//HLT pass-----------------------------------------------------------------------------------------


	HLT_FracSatVNstrips->SetXTitle("Total No. of Strips");
        HLT_FracSatVNstrips->SetYTitle("fraction of saturated strips");
	HLT_FracSatVNstrips->SetTitle("");
        HLT_FracSatVNstrips->Draw();        
//	HLT_FracSatVNstrips->SetMarkerStyle(7);
	mgr::SetSinglePad(canvas);
        mgr::SetAxis(HLT_FracSatVNstrips);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
	canvas->SaveAs("HLT_FracSatVNstrips_15k.pdf");

	HLT_DedXSig->SetXTitle("dE/dX Significance");
	HLT_DedXSig->SetYTitle("Entries");
	HLT_DedXSig->SetTitle("");
	HLT_DedXSig->SetLineColorAlpha(28,0.5);
        HLT_DedXSig->SetFillColor(42);
	HLT_DedXSig->Draw();
	mgr::SetSinglePad(canvas);
        mgr::SetAxis(HLT_DedXSig);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
	TLegend *HLT_leg = new TLegend(0.18,0.77,0.43,0.82); 
	HLT_leg->SetBorderSize( 0 );
        HLT_leg->SetFillColorAlpha( 0, 0 );
	HLT_leg->AddEntry(HLT_DedXSig,Mass.c_str(),"f");
	HLT_leg->Draw();
	canvas->SaveAs("HLT_DedXSig_15k.pdf");
	
	HLT_f51->SetXTitle("f51(E5x1/E5x5)");
	HLT_f51->SetYTitle("Entries");
	HLT_f51->SetLineColorAlpha(28,0.5);
        HLT_f51->SetFillColor(42);
	HLT_f51->SetTitle("");
	HLT_f51->Draw();
	mgr::SetSinglePad(canvas);
        mgr::SetAxis(HLT_f51);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
	TLegend *HLT_leg2 = new TLegend(0.18,0.77,0.43,0.82);
        HLT_leg2->SetBorderSize( 0 );
        HLT_leg2->SetFillColorAlpha( 0, 0 );
        HLT_leg2->AddEntry(HLT_f51,Mass.c_str(),"f");
        HLT_leg2->Draw();
	canvas->SaveAs("HLT_f51_15k.pdf");
	
	HLT_hIso->SetXTitle("Energy(GeV)");
	HLT_hIso->SetYTitle("Entries");
	HLT_hIso->SetLineColorAlpha(28,0.5);
        HLT_hIso->SetFillColor(42);
	HLT_hIso->SetTitle("");
	HLT_hIso->Draw();
	mgr::SetSinglePad(canvas);
        mgr::SetAxis(HLT_hIso);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
	TLegend *HLT_leg3 = new TLegend(0.7,0.77,0.95,0.82);
        HLT_leg3->SetBorderSize( 0 );
        HLT_leg3->SetFillColorAlpha( 0, 0 );
        HLT_leg3->AddEntry(HLT_hIso,Mass.c_str(),"f");
        HLT_leg3->Draw();
	canvas->SaveAs("HLT_hIso_15k.pdf");

	HLT_RZcurv->SetXTitle("R-Z curvature");
        HLT_RZcurv->SetYTitle("Entries");
        HLT_RZcurv->SetLineColorAlpha(28,0.5);
        HLT_RZcurv->SetFillColor(42);
        HLT_RZcurv->SetTitle("");
        HLT_RZcurv->Draw();
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(HLT_RZcurv);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
        TLegend *HLT_leg4 = new TLegend(0.7,0.77,0.95,0.82);
        HLT_leg4->SetBorderSize( 0 );
        HLT_leg4->SetFillColorAlpha( 0, 0 );
        HLT_leg4->AddEntry(HLT_RZcurv,Mass.c_str(),"f");
        HLT_leg4->Draw();
        canvas->SaveAs("HLT_RZcurv_15k.pdf");

/*	HLT_Energy->SetXTitle("E5x5(GeV)");
        HLT_Energy->SetYTitle("Entries");
        HLT_Energy->SetLineColorAlpha(28,0.5);
        HLT_Energy->SetFillColor(42);
        HLT_Energy->SetTitle("");
        HLT_Energy->Draw();
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(HLT_Energy);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("2000 Entires");
        TLegend *HLT_leg5 = new TLegend(0.7,0.77,0.95,0.82);
        HLT_leg5->SetBorderSize( 0 );
        HLT_leg5->SetFillColorAlpha( 0, 0 );
        HLT_leg5->AddEntry(HLT_Energy,Mass.c_str(),"f");
        HLT_leg5->Draw();
        canvas->SaveAs("HLT_Energy.pdf");



	HLT_ABCD->SetXTitle("f51");
        HLT_ABCD->SetYTitle("dE/dX significance");
        HLT_ABCD->SetTitle("");
	HLT_ABCD->SetMarkerStyle(7);
        HLT_ABCD->Draw();
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(HLT_ABCD);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
	TLine *HLT_TightY = new TLine(0,MonoCuts::dEdXSigCut_,1.1,MonoCuts::dEdXSigCut_);
	HLT_TightY->SetLineColor(4);
	HLT_TightY->SetLineStyle(7);
	HLT_TightY->SetLineWidth(3);
	HLT_TightY->Draw("same");
	TLine *HLT_TightX = new TLine(MonoCuts::f51Cut_,0,MonoCuts::f51Cut_,30);
        HLT_TightX->SetLineColor(4);
        HLT_TightX->SetLineStyle(7);
        HLT_TightX->SetLineWidth(3);
        HLT_TightX->Draw("same");
        TLine *HLT_LooseY = new TLine(0,7,1.1,7);
        HLT_LooseY->SetLineColor(38);
        HLT_LooseY->SetLineStyle(7);
        HLT_LooseY->Draw("same");
        TLine *HLT_LooseX = new TLine(0.6,0,0.6,30);
        HLT_LooseX->SetLineColor(38);
        HLT_LooseX->SetLineStyle(7);
        HLT_LooseX->Draw("same");
        canvas->SaveAs("HLT_ABCD_15k.pdf");
*/

}

