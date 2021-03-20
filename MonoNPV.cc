//////////////////////////////////
//
//    File name: MonoNPV.cc
//	 author: Shih Lin
//	   Date: 2021/2/3
//	Content: Number of Pile up Vertex vs dEdx, e55, f51, Rz curvature
//		 Matched events (contain both monopole and antimonopole) are considered.
//	Purpose: PU dependent check	 
//  	  Input: Signal Ntuple only(2017)
// 
// Result Slide: /slide/vertex vs variable
//
/////////////////////////////////////////////////

#include "iostream"
#include "TAttMarker.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TH1F.h"
#include "math.h"
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;

void DrawPlotsNoTRG();
void DrawPlotsTRG();

enum PlotName{
 dEdxCand=0,
 dEdxMono,
 e55Cand,
 e55Mono,
 f51Mono,
 RZCurvMono, 
// pT;
// f51;
	
};
static const unsigned nPlot = 6U;
class PlotSet
{
public:
  PlotSet(){plots_.resize(nPlot);}
  ~PlotSet(){}
  void CreatPlot(const PlotName pn, TProfile* h){ 
	plots_[pn] = h;
  }
  TProfile * GetPlot(const PlotName pn){ return plots_[pn]; }
  void WritePlot(){
	for(int pn=0;pn<nPlot;pn++){
	TProfile *h = plots_[pn];
	if(h){ 
	   h->Write();
	  }
	}
  }
private:
  vector<TProfile*> plots_;
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
    double phi, double mono_eta, double mono_phi, double amon_eta, double amon_phi, double NPV):
  subHits_(sh),subSatHits_(satsh),dEdXSig_(dedxsig),tIso_(tiso),xyp0_(xyp0),
  xyp1_(xyp1),xyp2_(xyp2),rzp0_(rzp0),rzp1_(rzp1),rzp2_(rzp2),
  dist_(dist),f51_(f51),f15_(f15),e55_(e55),hIso_(hiso),
  eta_(eta),phi_(phi),mono_eta_(mono_eta), mono_phi_(mono_phi),
  amon_eta_(amon_eta), amon_phi_(amon_phi),NPV_(NPV) { }
  //This will be used in comparing with cut
  MonoCandidate(const MonoCandidate &mc) : 
    subHits_(mc.subHits_),subSatHits_(mc.subSatHits_),dEdXSig_(mc.dEdXSig_),tIso_(mc.tIso_),
    xyp0_(mc.xyp0_),xyp1_(mc.xyp1_),xyp2_(mc.xyp2_),
    rzp0_(mc.rzp0_),rzp1_(mc.rzp1_),rzp2_(mc.rzp2_),
    dist_(mc.dist_),f51_(mc.f51_),f15_(mc.f15_),e55_(mc.e55_),
    hIso_(mc.hIso_),eta_(mc.eta_),phi_(mc.phi_),mono_eta_(mc.mono_eta_), mono_phi_(mc.mono_phi_),
  amon_eta_(mc.amon_eta_), amon_phi_(mc.amon_phi_),NPV_(mc.NPV_) { } //{ empty >////<} 
        
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
  double mono_eta_;
  double mono_phi_;
  double amon_eta_;
  double amon_phi_;
  double NPV_;
};	
class MonoCuts:public MonoCandidate
{
public:
  MonoCuts(){}

  MonoCuts(const string &trName,TFile *openFile):trigName_(trName){
	
	openFile->mkdir(trName.c_str());
	cout<<"create directory "<<trName.c_str()<<endl;	
	NPVPlot.resize(1U);
	PlotSet &x = NPVPlot[0];
//        x.CreatPlot(dEdxCand,new TProfile("dEdxCand","",6,0,60,-1,30));
        x.CreatPlot(dEdxMono,new TProfile("dEdxMono","",6,0,60,-1,30));
//        x.CreatPlot(e55Cand,new TProfile("e55Cand","",6,0,60,-1,1200));
        x.CreatPlot(e55Mono,new TProfile("e55Mono","",6,0,60,-1,1200));
        x.CreatPlot(f51Mono,new TProfile("f51Mono","",6,0,60,-0.1,1));
        x.CreatPlot(RZCurvMono,new TProfile("RZCurvMono","",6,0,60,-0.01,0.01));
	

  }

  ~MonoCuts(){}
  void doAnalysis(vector<MonoCandidate> &cand, unsigned nCandidates, bool TRG, unsigned ev)
  {
	CutFlowCand_TRG.clear();	
	CutFlowCand_Dedx.clear();

     for(unsigned c=0;c<nCandidates;c++){
	MonoCandidate &cands = cand[c];
	bool QualCut = evalQuality(cands);
	bool ECut = evalE(cands);
	bool F51Cut = evalF51(cands);
	bool dEdXCut = evaldEdX(cands);

	if(TRG) CutFlowCand_TRG.push_back(cands);
	
	if(TRG && QualCut && ECut && F51Cut && dEdXCut) CutFlowCand_Dedx.push_back(cands);
	
        }

        sort(CutFlowCand_TRG.begin(),CutFlowCand_TRG.begin()+CutFlowCand_TRG.size());
/*	PlotSet &y = NPVPlot[0];
	for(int i=0;i<CutFlowCand_TRG.size();i++){
		y.GetPlot(dEdxCand)->Fill(CutFlowCand_TRG[i].NPV_,CutFlowCand_TRG[i].dEdXSig_,1);
		y.GetPlot(e55Cand)->Fill(CutFlowCand_TRG[i].NPV_,CutFlowCand_TRG[i].e55_,1);
	}
*/

	if(CutFlowCand_Dedx.size()==1) 	MonoNum1++;
	else if(CutFlowCand_Dedx.size()==2) MonoNum2++;
	else if(CutFlowCand_Dedx.size()==3) MonoNum3++;
	
	sort(CutFlowCand_Dedx.begin(),CutFlowCand_Dedx.begin()+CutFlowCand_Dedx.size());
	if(CutFlowCand_Dedx.size()>=1&&CutFlowCand_Dedx.size()<=3){
		cout<<"ev "<<ev<<"  ,no. of cand "<<CutFlowCand_Dedx.size()<<endl;
		bool RealMono=0;
		bool RealAnti=0;

		for(int i=0; i<CutFlowCand_Dedx.size();i++){

		double m_deltaR=0;
		double am_deltaR=0;
		m_deltaR = sqrt(pow(CutFlowCand_Dedx[i].eta_-CutFlowCand_Dedx[0].mono_eta_,2)+
				pow(CutFlowCand_Dedx[i].phi_-CutFlowCand_Dedx[0].mono_phi_,2));
		am_deltaR= sqrt(pow(CutFlowCand_Dedx[i].eta_-CutFlowCand_Dedx[0].amon_eta_,2)+
                                pow(CutFlowCand_Dedx[i].phi_-CutFlowCand_Dedx[0].amon_phi_,2));

		if(m_deltaR<0.1) 
		{
			cout<<i+1<<" monopole match "<<endl;
			RealNum++;
			RealMono=true;
		}
		else if(am_deltaR<0.1) 
		{
			cout<<i+1<<" anti monopole match"<<endl;
			RealAntiNum++;
			RealAnti=true;
		}
		else 
		{
			cout<<ev<<" ";
			cout<<i+1<<" FAKE"<<endl;
			FakeNum++;
		}

		cout<<"          candidate           monoGen         antimonoGen"<<endl;
		cout<<"eta      "<<setprecision(5)<<CutFlowCand_Dedx[i].eta_<<setw(20)<<CutFlowCand_Dedx[i].mono_eta_
				 <<setw(20)<<CutFlowCand_Dedx[i].amon_eta_<<endl;
		cout<<"phi      "<<setprecision(5)<<CutFlowCand_Dedx[i].phi_<<setw(20)<<CutFlowCand_Dedx[i].mono_phi_
				 <<setw(20)<<CutFlowCand_Dedx[i].amon_phi_<<endl;
		cout<<"m deltaR "<<m_deltaR<<endl;
		cout<<"a deltaR "<<am_deltaR<<endl;
		cout<<"----------------------------"<<endl;
		}
		if(RealMono==true && RealAnti==true){
			RealEvNum++;
			PlotSet &x = NPVPlot[0];
			for(int i=0;i<CutFlowCand_Dedx.size();i++){
			x.GetPlot(dEdxMono)->Fill(CutFlowCand_Dedx[i].NPV_,CutFlowCand_Dedx[i].dEdXSig_,1);
			x.GetPlot(e55Mono)->Fill(CutFlowCand_Dedx[i].NPV_,CutFlowCand_Dedx[i].e55_,1);	
                        x.GetPlot(f51Mono)->Fill(CutFlowCand_Dedx[i].NPV_,CutFlowCand_Dedx[i].f51_,1);
                        x.GetPlot(RZCurvMono)->Fill(CutFlowCand_Dedx[i].NPV_,CutFlowCand_Dedx[i].rzp2_,1);
	
			}
			cout<<"YES----------!"<<endl;
		}
		cout<<"============================"<<endl;
	}

  }  
  bool operator<(const MonoCandidate &mc)const{
   if(dEdXSig_>mc.dEdXSig_) return true;
   else if(dEdXSig_==mc.dEdXSig_){
        if(f51_>mc.f51_) return true;
        else return false;
        }
    else return false;
  }

  void WritePlots(TFile *oFile){
	oFile->cd(trigName_.c_str());
	NPVPlot[0].WritePlot();
	
//	for(unsigned c=0; c<nCut; c++) NPV[c].WritePlot();
	cout<<"cutflow pass writeplots func"<<endl;
	
  }
  
  void SignalEff(const string trName)
  {
 	cout<<" 1 monopole "<<MonoNum1<<endl;
 	cout<<" 2 monopole "<<MonoNum2<<endl;
 	cout<<" 3 monopole "<<MonoNum3<<endl;
	cout<<"------------------------"<<endl;
	cout<<"Real monopole "<<RealNum<<endl;
	cout<<"Real antimono "<<RealAntiNum<<endl;
	cout<<"Real Event    "<<RealEvNum<<endl;
	  
      cout<<endl;
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
  string trigName_;
  vector<PlotSet> Plot;
  //N-1 cut plot box
  vector<PlotSet> n_1Plot;
  //cutflow plot box
  vector<PlotSet> NPVPlot;
  static const unsigned nCut = 5U;
  string cutName_[nCut];
  


  //cuts analysis
  bool evalQuality(MonoCandidate &mc) { return mc.xyp0_ < xyp0Cut_&& mc.xyp2_ > xyp2Cut_ 
			&& mc.dist_ < distCut_  && mc.hIso_ <hIsoCut_;  }
  bool evalE(MonoCandidate &mc) { return mc.e55_ > e55Cut_; }
  bool evalF51(MonoCandidate &mc) { return mc.f51_ > f51Cut_ ; }
  bool evaldEdX(MonoCandidate &mc) { return mc.dEdXSig_ > dEdXSigCut_ ;}
  int TotalEvents = 15000;
 
  vector<MonoCandidate> CutFlowCand_TRG;
  vector<MonoCandidate> CutFlowCand_Qual;
  vector<MonoCandidate> CutFlowCand_Energy;
  vector<MonoCandidate> CutFlowCand_F51;
  vector<MonoCandidate> CutFlowCand_Dedx;

  vector<MonoCandidate> N1CutCand_TRG;
  vector<MonoCandidate> N1CutCand_Qual;
  vector<MonoCandidate> N1CutCand_Energy;
  vector<MonoCandidate> N1CutCand_F51;
  vector<MonoCandidate> N1CutCand_Dedx;
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
  
  int MonoNum1=0;
  int MonoNum2=0;
  int MonoNum3=0;
  int FakeNum=0;
  int RealNum=0;
  int RealAntiNum=0;
  int RealEvNum=0;
  int count_test=0;
  int TRGminitest=0;
  int Qualminitest=0;
  //relative eff without HLT
  int NoTRG=0;
  int NoQual=0;
  int NoQualCand=0;
  int NoE=0;
  int NoECand=0;
  int NoF51=0;
  int NoF51Cand=0;
  int NodEdXCut=0;
  int NodEdXCutCand=0;
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

};
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

void NPV()
{
        TFile *oFile = new TFile("NPV.root","recreate");
	TFile *f1 = new TFile("MonoNtuple_MC_2017_1000.root");
        TTree *tree = (TTree*)f1->Get("monopoles");

        double pT;
        unsigned NPV;
        unsigned nCandidates;
        tree->SetBranchAddress("mono_p",&pT);
        tree->SetBranchAddress("NPV",&NPV);
        Bool_t passHLT_Photon200;
        Bool_t passHLT_Photon175;
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
	double mono_eta;
	double mono_phi;
	double amon_eta;
	double amon_phi;
      	vector<double> Et; 

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
        tree->SetBranchAddress("mono_eta",&mono_eta);
        tree->SetBranchAddress("mono_phi",&mono_phi);
        tree->SetBranchAddress("amon_eta",&amon_eta);
        tree->SetBranchAddress("amon_phi",&amon_phi);

	MonoCuts noTrgAnalysis("NO TRG",oFile);
	MonoCuts TrgAnalysis("HLT_Photon200",oFile);

  vector<MonoCandidate> cand(10);	
  for ( unsigned ev=0; ev < tree->GetEntries();ev++) {
                tree->GetEntry(ev);
 
                if(nCandidates>Et.size()) Et.resize(nCandidates);

  		if(nCandidates>cand.size()) cand.resize(nCandidates);
                for(unsigned i=0;i<nCandidates;i++){

        	Et[i]= (*e55)[i]/(TMath::CosH(TMath::Abs((*eta)[i])));
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
		Et[i],
//	        (*e55)[i],
	        (*hIso)[i],
	        (*eta)[i],
	        (*phi)[i],
		mono_eta,
	        mono_phi,
	        amon_eta,
		amon_phi,
		NPV// test variable
     		 );
		}
		TrgAnalysis.doAnalysis(cand,nCandidates,passHLT_Photon200,ev);
		noTrgAnalysis.doAnalysis(cand,nCandidates,true,ev);			


	}//for every event loop
	TrgAnalysis.WritePlots(oFile);
	TrgAnalysis.SignalEff("HLT_Photon200");

	noTrgAnalysis.WritePlots(oFile);
	noTrgAnalysis.SignalEff("NO TRG");

	oFile->Close();	
	cout<<"end of the code"<<endl;
	
	DrawPlotsNoTRG();
	DrawPlotsTRG();
}
void DrawPlotsNoTRG()
{	
  	TCanvas * c1 = new TCanvas("c1","Profile histogram ",800,600);
        TFile *f2 = new TFile("NPV.root");
	TDirectory *dir = (TDirectory*)f2->Get("NO TRG");
	dir->cd();
		
	gStyle->SetOptStat(0);

	TProfile* dEdxCutNPV = (TProfile*)dir->Get("dEdxMono");
        dEdxCutNPV->SetXTitle("NPV");
        dEdxCutNPV->SetYTitle("#LT dE/dx #GT > 9");
        dEdxCutNPV->SetMarkerStyle(9);
        dEdxCutNPV->Draw("E1");
        mgr::SetSinglePad(c1);
        mgr::SetAxis(dEdxCutNPV);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("2017 1TeV 15000 Entries");
        c1->SaveAs("./Plots/NPV vs dEdx(cut).pdf");
	
        TProfile* e55CutNPV = (TProfile*)dir->Get("e55Mono");
	e55CutNPV->SetXTitle("NPV");
        e55CutNPV->SetYTitle("#LT e55 #GT > 200");
        e55CutNPV->SetMarkerStyle(9);
        e55CutNPV->Draw("E1");
        mgr::SetSinglePad(c1);
        mgr::SetAxis(e55CutNPV);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("2017 1TeV 15000 Entries");
        c1->SaveAs("./Plots/NPV vs e55(cut).pdf");
      
        TProfile* f51CutNPV = (TProfile*)dir->Get("f51Mono");
        f51CutNPV->SetXTitle("NPV");
        f51CutNPV->SetYTitle("#LT f51 #GT");
        f51CutNPV->SetMarkerStyle(9);
        f51CutNPV->Draw("E1");
        mgr::SetSinglePad(c1);
        mgr::SetAxis(f51CutNPV);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("2017 1TeV 15000 Entries");
        c1->SaveAs("./Plots/NPV vs f51.pdf");
      
        TProfile* RZCutNPV = (TProfile*)dir->Get("RZCurvMono");
        RZCutNPV->SetXTitle("NPV");
        RZCutNPV->SetYTitle("#LT RZ curvature #GT");
        RZCutNPV->SetMarkerStyle(9);
        RZCutNPV->Draw("E1");
        mgr::SetSinglePad(c1);
        mgr::SetAxis(RZCutNPV);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("2017 1TeV 15000 Entries");
        c1->SaveAs("./Plots/NPV vs RZCurv.pdf");

	
}
void DrawPlotsTRG()
{
        TCanvas * c1 = new TCanvas("c1","Profile histogram ",800,600);
        TFile *f2 = new TFile("NPV.root");
        TDirectory *dir = (TDirectory*)f2->Get("HLT_Photon200");
        dir->cd();
                
        gStyle->SetOptStat(0);

        TProfile* dEdxCutNPV = (TProfile*)dir->Get("dEdxMono");
        dEdxCutNPV->SetXTitle("NPV");
        dEdxCutNPV->SetYTitle("#LT dE/dx #GT > 9");
        dEdxCutNPV->SetMarkerStyle(9);
        dEdxCutNPV->Draw("E1");
        mgr::SetSinglePad(c1);
        mgr::SetAxis(dEdxCutNPV);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("2017 1TeV 15000 Entries");
        c1->SaveAs("./Plots/NPV vs dEdx(cut) HLT.pdf");

        TProfile* e55CutNPV = (TProfile*)dir->Get("e55Mono");
        e55CutNPV->SetXTitle("NPV");
        e55CutNPV->SetYTitle("#LT e55 #GT > 200");
        e55CutNPV->SetMarkerStyle(9);
        e55CutNPV->Draw("E1");
        mgr::SetSinglePad(c1);
        mgr::SetAxis(e55CutNPV);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("2017 1TeV 15000 Entries");
        c1->SaveAs("./Plots/NPV vs e55(cut) HLT.pdf");

        TProfile* f51CutNPV = (TProfile*)dir->Get("f51Mono");
        f51CutNPV->SetXTitle("NPV");
        f51CutNPV->SetYTitle("#LT f51 #GT");
        f51CutNPV->SetMarkerStyle(9);
        f51CutNPV->Draw("E1");
        mgr::SetSinglePad(c1);
        mgr::SetAxis(f51CutNPV);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("2017 1TeV 15000 Entries");
        c1->SaveAs("./Plots/NPV vs f51 HLT.pdf");
      
        TProfile* RZCutNPV = (TProfile*)dir->Get("RZCurvMono");
        RZCutNPV->SetXTitle("NPV");
        RZCutNPV->SetYTitle("#LT RZ curvature #GT");
        RZCutNPV->SetMarkerStyle(9);
        RZCutNPV->Draw("E1");
        mgr::SetSinglePad(c1);
        mgr::SetAxis(RZCutNPV);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("2017 1TeV 15000 Entries");
        c1->SaveAs("./Plots/NPV vs RZCurv HLT.pdf");

}

/*
  dEdxNPV->SetXTitle("NPV");
  dEdxNPV->SetYTitle("#LT dE/dx #GT");
  dEdxNPV->SetMarkerStyle(9);
  dEdxNPV->Draw("E1");
  mgr::SetSinglePad(c1);
  mgr::SetAxis(dEdxNPV);
  mgr::DrawCMSLabelOuter(SIMULATION);
  mgr::DrawEntryRight("2017 1TeV 15000 Entries");
  c1->SaveAs("NPV vs dEdx.pdf");

  e55NPV->SetXTitle("NPV");
  e55NPV->SetYTitle("#LT e55 #GT");
  e55NPV->SetMarkerStyle(9);
  e55NPV->Draw("E1");
  mgr::SetSinglePad(c1);
  mgr::SetAxis(e55NPV);
  mgr::DrawCMSLabelOuter(SIMULATION);
  mgr::DrawEntryRight("2017 1TeV 15000 Entries");
  c1->SaveAs("NPV vs e55.pdf");


  dEdxCutNPV->SetXTitle("NPV");
  dEdxCutNPV->SetYTitle("#LT dE/dx #GT > 9");
  dEdxCutNPV->SetMarkerStyle(9);
  dEdxCutNPV->Draw("E1");
  mgr::SetSinglePad(c1);
  mgr::SetAxis(dEdxCutNPV);
  mgr::DrawCMSLabelOuter(SIMULATION);
  mgr::DrawEntryRight("2017 1TeV 15000 Entries");
  c1->SaveAs("NPV vs dEdx(cut).pdf");

  e55CutNPV->SetXTitle("NPV");
  e55CutNPV->SetYTitle("#LT e55 #GT > 200");
  e55CutNPV->SetMarkerStyle(9);
  e55CutNPV->Draw("E1");
  mgr::SetSinglePad(c1);
  mgr::SetAxis(e55CutNPV);
  mgr::DrawCMSLabelOuter(SIMULATION);
  mgr::DrawEntryRight("2017 1TeV 15000 Entries");
  c1->SaveAs("NPV vs e55(cut).pdf");
  
  pTNPV->SetXTitle("NPV");
  pTNPV->SetYTitle("#LT pT #GT");
  pTNPV->Draw("E1");
  mgr::SetSinglePad(c1);
  mgr::SetAxis(pTNPV);
  mgr::DrawCMSLabelOuter(SIMULATION);
  mgr::DrawEntryRight("2017 1TeV 15000 Entries");
  c1->SaveAs("NPV vs pT.pdf");

  f51NPV->SetXTitle("NPV");
  f51NPV->SetYTitle("#LT f51 #GT");
  f51NPV->SetMarkerStyle(9);
  f51NPV->Draw("E1");
  mgr::SetSinglePad(c1);
  mgr::SetAxis(f51NPV);
  mgr::DrawCMSLabelOuter(SIMULATION);
  mgr::DrawEntryRight("2017 1TeV 15000 Entries");
  c1->SaveAs("NPV vs f51.pdf");
}

*/
