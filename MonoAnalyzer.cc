//////////////////////////////////
//
//	File name: MonoAnalyzer.cc
//	author: Shih Lin
//	Content: the significance plots for every cuts
//		 count efficiency for every cuts 
//	Output: Monopole_Analyzer.root
//	(using MonoDrawPlots.cc to complete the plots)
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
enum PlotName{
  FracSatVNstrips = 0, // fraction of saturated strips vs. number of strips
  DedXSig,             // dE/dX significance
  RZcurv,              // RZ curvature/uncertainty
  F51,                 // frac 51
  HcalIso,             // Hcal Iso
  ABCD
};
static const unsigned nPlot = 6U;
class PlotSet
{
public:
  PlotSet(){plots_.resize(nPlot);}
  ~PlotSet(){}
  void CreatPlot(const PlotName pn, TH1* h){ 
	plots_[pn] = h;
//	cout<<"create successful pn: "<<pn<<endl;
  }
  TH1 * GetPlot(const PlotName pn){ return plots_[pn]; }
  void Print(){ 
	cout<<plots_[0]<<endl;
	cout<<plots_[1]<<endl;}
  void WritePlot(){
	for(int pn=0;pn<nPlot;pn++){
	TH1 *h = plots_[pn];
	if(h){ 
	  h->Write();
	//  cout<<h<<"pass h->Write()"<<endl;
	  }
	}
  }
private:
  vector<TH1*> plots_;
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
  MonoCuts(const string &trName,TFile *openFile):trigName_(trName){
	
	//create a new directory in the output file
	openFile->mkdir(trName.c_str());
	cout<<"create directory "<<trName.c_str()<<endl;	
	//create histrogram N-1 cutf for No trigger
	Plot.resize(1U);
	PlotSet &x = Plot[0];
        x.CreatPlot(FracSatVNstrips,new TH2D("FracSatVNstrips","",100,0,1000,100,0,1));
        x.CreatPlot(DedXSig,new TH1D("DedXSig","",100,0,30));
        x.CreatPlot(RZcurv,new TH1D("RZcurv","",100,-10,10));
        x.CreatPlot(F51,new TH1D("F51","",100,0,1.1));
        x.CreatPlot(HcalIso,new TH1D("HcalIso","",100,0,30));
        x.CreatPlot(ABCD,new TH2D("ABCD","",100,0,1.1,100,0,30));
	
	cout<<"the address of plots x "<<&x<<endl;

	//Name the cut name
	 cutName_[0] = "Quality_";
	 cutName_[1] = "Energy_";
	 cutName_[2] = "F51_";
	 cutName_[3] = "dEdxSig_";
	 cutName_[4] = "HLT_";
	
	//create plot with n-1 cut

        n_1Plot.resize(nCut);
        string trgn1name = "HLT_";
        string name = "N_1_"+trgn1name;         //  N_1_HLT_FracSatVNstrips

	for( int c = 0; c <nCut ;c++){

	string cutn1name = name + cutName_[c];	//N_1_HLT_Quality_FracSatVNstrips
	PlotSet &z = n_1Plot[c];//[1] = Quality,[2]energy, [3] f51, [4]dEdx
	//create the n-1 cut plots
	
	z.CreatPlot(FracSatVNstrips,new TH2D((cutn1name+"FracSatVNstrips").c_str(),"",100,0,1000,100,0,1));
	z.CreatPlot(DedXSig,new TH1D((cutn1name+"DedXSig").c_str(),"",100,0,30));
	z.CreatPlot(RZcurv,new TH1D((cutn1name+"RZcurv").c_str(),"",100,-10,10));
        z.CreatPlot(F51,new TH1D((cutn1name+"F51").c_str(),"",100,0,1.1));
        z.CreatPlot(HcalIso,new TH1D((cutn1name+"HcalIso").c_str(),"",100,0,30));
        z.CreatPlot(ABCD,new TH2D((cutn1name+"ABCD").c_str(),"",100,0,1.1,100,0,30));
	cout<<"good "<<cutn1name<<endl;
	}

	//create plot with cutflow
	CutFlow.resize(nCut); 
	for( int c = 0;c<nCut-1;c++){
	
	PlotSet &y = CutFlow[c];
	string cutflowName = "Flow_HLT_"+cutName_[c];

        y.CreatPlot(FracSatVNstrips,new TH2D((cutflowName+"FracSatVNstrips").c_str(),"",100,0,1000,100,0,1));
        y.CreatPlot(DedXSig,new TH1D((cutflowName+"DedXSig").c_str(),"",100,0,30));
        y.CreatPlot(RZcurv,new TH1D((cutflowName+"RZcurv").c_str(),"",100,-10,10));
        y.CreatPlot(F51,new TH1D((cutflowName+"F51").c_str(),"",100,0,1.1));
        y.CreatPlot(HcalIso,new TH1D((cutflowName+"HcalIso").c_str(),"",100,0,30));
        y.CreatPlot(ABCD,new TH2D((cutflowName+"ABCD").c_str(),"",100,0,1.1,100,0,30));
        cout<<"good cutflow"<<cutflowName<<endl;
	}

  }

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
  	
	//Get plot without any cut (I put this in the first array in n-1 cut....
	if(TRG){
	PlotSet &x = Plot[0];
        x.GetPlot(FracSatVNstrips)->Fill(cands.subHits_,cands.subSatHits_/cands.subHits_);
	x.GetPlot(DedXSig)->Fill(cands.dEdXSig_);
        x.GetPlot(RZcurv)->Fill(cands.rzp2_);
        x.GetPlot(F51)->Fill(cands.f51_);
        x.GetPlot(HcalIso)->Fill(cands.hIso_);
        x.GetPlot(ABCD)->Fill(cands.f51_,cands.dEdXSig_);

	count++;
	}
	if(QualCut) Qual++;
	if(ECut) E++;
	if(F51Cut) f51++;
	if(dEdXCut) dEdX++;
	
	//N-1 cut and relative efficiency
	
        if( ECut && F51Cut && dEdXCut &&TRG)  
	{
        PlotSet &z = n_1Plot[0];
        z.GetPlot(FracSatVNstrips)->Fill(cands.subHits_,cands.subSatHits_/cands.subHits_);
        z.GetPlot(DedXSig)->Fill(cands.dEdXSig_);
        z.GetPlot(RZcurv)->Fill(cands.rzp2_);
        z.GetPlot(F51)->Fill(cands.f51_);
        z.GetPlot(HcalIso)->Fill(cands.hIso_);
        z.GetPlot(ABCD)->Fill(cands.f51_,cands.dEdXSig_);

	NoQual++;
	}
        if( QualCut && F51Cut && dEdXCut &TRG) 
	{
        PlotSet &z = n_1Plot[1];
        z.GetPlot(FracSatVNstrips)->Fill(cands.subHits_,cands.subSatHits_/cands.subHits_);
        z.GetPlot(DedXSig)->Fill(cands.dEdXSig_);
        z.GetPlot(RZcurv)->Fill(cands.rzp2_);
        z.GetPlot(F51)->Fill(cands.f51_);
        z.GetPlot(HcalIso)->Fill(cands.hIso_);
        z.GetPlot(ABCD)->Fill(cands.f51_,cands.dEdXSig_);


	NoE++;
	}
        if( QualCut && ECut && dEdXCut &&TRG ) 
	{
        PlotSet &z = n_1Plot[2];
        z.GetPlot(FracSatVNstrips)->Fill(cands.subHits_,cands.subSatHits_/cands.subHits_);
        z.GetPlot(DedXSig)->Fill(cands.dEdXSig_);
        z.GetPlot(RZcurv)->Fill(cands.rzp2_);
        z.GetPlot(F51)->Fill(cands.f51_);
        z.GetPlot(HcalIso)->Fill(cands.hIso_);
        z.GetPlot(ABCD)->Fill(cands.f51_,cands.dEdXSig_);

	NoF51++;
	}
	if( QualCut && ECut && F51Cut &&TRG){

	PlotSet &z = n_1Plot[3];
        z.GetPlot(FracSatVNstrips)->Fill(cands.subHits_,cands.subSatHits_/cands.subHits_);
        z.GetPlot(DedXSig)->Fill(cands.dEdXSig_);
        z.GetPlot(RZcurv)->Fill(cands.rzp2_);
        z.GetPlot(F51)->Fill(cands.f51_);
        z.GetPlot(HcalIso)->Fill(cands.hIso_);
        z.GetPlot(ABCD)->Fill(cands.f51_,cands.dEdXSig_);

	NodEdXCut++;
	}
	if( QualCut && ECut & F51Cut && dEdXCut){
	
        PlotSet &z = n_1Plot[4];
        z.GetPlot(FracSatVNstrips)->Fill(cands.subHits_,cands.subSatHits_/cands.subHits_);
        z.GetPlot(DedXSig)->Fill(cands.dEdXSig_);
        z.GetPlot(RZcurv)->Fill(cands.rzp2_);
        z.GetPlot(F51)->Fill(cands.f51_);
        z.GetPlot(HcalIso)->Fill(cands.hIso_);
        z.GetPlot(ABCD)->Fill(cands.f51_,cands.dEdXSig_);
 
	NoTRG++;
	}
	//-----------------------------------------------------------------	
	//---Cutflow histograms--------------------------------------------
	//-----------------------------------------------------------------

	//signal efficiency
	if(TRG && QualCut ){ 
	
	PlotSet &y = CutFlow[0];
        y.GetPlot(FracSatVNstrips)->Fill(cands.subHits_,cands.subSatHits_/cands.subHits_);
        y.GetPlot(DedXSig)->Fill(cands.dEdXSig_);
        y.GetPlot(RZcurv)->Fill(cands.rzp2_);
        y.GetPlot(F51)->Fill(cands.f51_);
        y.GetPlot(HcalIso)->Fill(cands.hIso_);
        y.GetPlot(ABCD)->Fill(cands.f51_,cands.dEdXSig_);

	   Qual_count++;
	}
	if(TRG && QualCut && ECut ){
	 
        PlotSet &y = CutFlow[1];
        y.GetPlot(FracSatVNstrips)->Fill(cands.subHits_,cands.subSatHits_/cands.subHits_);
        y.GetPlot(DedXSig)->Fill(cands.dEdXSig_);
        y.GetPlot(RZcurv)->Fill(cands.rzp2_);
        y.GetPlot(F51)->Fill(cands.f51_);
        y.GetPlot(HcalIso)->Fill(cands.hIso_);
        y.GetPlot(ABCD)->Fill(cands.f51_,cands.dEdXSig_);

	 E_count++;		
	}
	if(TRG && QualCut && ECut && F51Cut){
	
        PlotSet &y = CutFlow[2];
        y.GetPlot(FracSatVNstrips)->Fill(cands.subHits_,cands.subSatHits_/cands.subHits_);
        y.GetPlot(DedXSig)->Fill(cands.dEdXSig_);
        y.GetPlot(RZcurv)->Fill(cands.rzp2_);
        y.GetPlot(F51)->Fill(cands.f51_);
        y.GetPlot(HcalIso)->Fill(cands.hIso_);
        y.GetPlot(ABCD)->Fill(cands.f51_,cands.dEdXSig_);

		
	 f51_count++;
	}
	if( TRG && QualCut && ECut && F51Cut && dEdXCut){
	
        PlotSet &y = CutFlow[3];
        y.GetPlot(FracSatVNstrips)->Fill(cands.subHits_,cands.subSatHits_/cands.subHits_);
        y.GetPlot(DedXSig)->Fill(cands.dEdXSig_);
        y.GetPlot(RZcurv)->Fill(cands.rzp2_);
        y.GetPlot(F51)->Fill(cands.f51_);
        y.GetPlot(HcalIso)->Fill(cands.hIso_);
        y.GetPlot(ABCD)->Fill(cands.f51_,cands.dEdXSig_);

	dEdX_count++;
	}
  }
  void WritePlots(TFile *oFile){
	oFile->cd(trigName_.c_str());
	Plot[0].WritePlot();
	for(unsigned c=0; c<nCut; c++) n_1Plot[c].WritePlot();
        cout<<"n-1cut pass writeplots func"<<endl;

	for(unsigned c=0; c<nCut; c++) CutFlow[c].WritePlot();
	cout<<"cutflow pass writeplots func"<<endl;
	
  }
  
  void SignalEff(const string trName)
  {
        //signal efficiency = no. of events after all selection cuts/all events
	cout<<trName<<" ================================="<<endl;
//        cout<<"No TRG ==================================="<<endl;
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
        cout<<"Signal efficiency = "<<(double)dEdX_count/(double)TotalEvents<<endl;
        cout<<"------------------------------------------"<<endl;
        cout<<"Relative efficiency-----------------------"<<endl;
        cout<<"------------------------------------------"<<endl;
        cout<<"        TRG "<<(double)dEdX_count/(double)NoTRG<<endl;
        cout<<"QualityCuts "<<(double)dEdX_count/(double)NoQual<<endl;
        cout<<"       ECut "<<(double)dEdX_count/(double)NoE<<endl;
        cout<<"     F51Cut "<<(double)dEdX_count/(double)NoF51<<endl;
        cout<<" dEdXSigCut "<<(double)dEdX_count/(double)NodEdXCut<<endl;

        cout<<endl;
/*        cout<<"TRG pass ================================="<<endl;
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
*/
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
  vector<PlotSet> CutFlow;
  static const unsigned nCut = 5U;
  string cutName_[nCut];
  


  //cuts analysis
  bool evalQuality(MonoCandidate &mc) { return mc.xyp0_ < xyp0Cut_&& mc.xyp2_ > xyp2Cut_ 
			&& mc.dist_ < distCut_  && mc.hIso_ <hIsoCut_;  }
  bool evalE(MonoCandidate &mc) { return mc.e55_ > e55Cut_; }
  bool evalF51(MonoCandidate &mc) { return mc.f51_ > f51Cut_ ; }
  bool evaldEdX(MonoCandidate &mc) { return mc.dEdXSig_ > dEdXSigCut_ ;}
  int TotalEvents = 15000;
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

 // const string Mass = "3000 GeV";
void histrogram()
{
	TFile *oFile = new TFile("Monopole_Analyzer.root","recreate");
	TFile *fin = new TFile("MonoNtuple_MC_2018_1000.root");
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

	double subHits_count=0;
	double subSatHits_count=0;
	int test=0;
        const unsigned NEvents = tree->GetEntries();
	
	MonoCuts noTrgAnalysis("NO TRG",oFile);
	MonoCuts TrgAnalysis("HLT_Photon200",oFile);
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
		
		sort(cand.begin(),cand.begin()+nCandidates);
		if(cand[0].eta_>-1&&cand[0].eta_<1){
		}
		//cut
		TrgAnalysis.doAnalysis(cand,passHLT_Photon200);	       	
		noTrgAnalysis.doAnalysis(cand,true);			
	}
	TrgAnalysis.WritePlots(oFile);
	TrgAnalysis.SignalEff("HLT_Photon200");

	noTrgAnalysis.WritePlots(oFile);
	noTrgAnalysis.SignalEff("NO TRG");

	oFile->Close();	
	cout<<"end of the code"<<endl;
}
