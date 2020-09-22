///////////////////////////////////////////////////
//	
//	Draw 2017/2018 mc and compare the different mass
//	put the different mass in a histogram
//	2020/9/9
//	
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
};
void MonoCompareMass()
{
	string file_m[3];
	file_m[0] = "MonoNtuple_MC_2018_1000.root";
	file_m[1] = "MonoNtuple_MC_2018_2000.root";
	file_m[2] = "MonoNtuple_MC_2018_3000.root";

	TCanvas *canvas = new TCanvas("canvas","canvas",800,600);

//  	TH1D *h_DedXSig[3];
        TH1D *h_DedXSig1 = new TH1D("h_DedXSig1","dE/dX significant distribution",100,0,30);
        TH1D *h_DedXSig2 = new TH1D("h_DedXSig2","dE/dX significant distribution",100,0,30);
        TH1D *h_DedXSig3 = new TH1D("h_DedXSig3","dE/dX significant distribution",100,0,30);

	TH1D *h_f51_1 = new TH1D("h_f51_1","f51",100,0.2,1.1);
	TH1D *h_f51_2 = new TH1D("h_f51_2","f51",100,0.2,1.1);
	TH1D *h_f51_3 = new TH1D("h_f51_3","f51",100,0.2,1.1);
	
	TH1D *h_hIso1 = new TH1D("h_hIso1","hIso",100,-1,10);	
	TH1D *h_hIso2 = new TH1D("h_hIso2","hIso",100,-1,10);	
	TH1D *h_hIso3 = new TH1D("h_hIso3","hIso",100,-1,10);	
	
	TH1D *h_RZcurv1 = new TH1D("h_RZcurv1","",100,-0.01,0.01);
	TH1D *h_RZcurv2 = new TH1D("h_RZcurv2","",100,-0.01,0.01);
	TH1D *h_RZcurv3 = new TH1D("h_RZcurv3","",100,-0.01,0.01);
  
        TH1D *HLT_DedXSig1 = new TH1D("HLT_DedXSig1","dE/dX significant distribution",100,0,30);
        TH1D *HLT_RZcurv1 = new TH1D("HLT_RZcurv1","",100,-0.01,0.01);
        TH1D *HLT_f51_1 = new TH1D("HLT_f51_1","f51",100,0.2,1.1);
        TH1D *HLT_hIso1 = new TH1D("HLT_hIso1","hIso",100,-1,10);

        TH1D *HLT_RZcurv2 = new TH1D("HLT_RZcurv2","",100,-0.01,0.01);
        TH1D *HLT_DedXSig2 = new TH1D("HLT_DedXSig2","dE/dX significant distribution",100,0,30);
        TH1D *HLT_f51_2 = new TH1D("HLT_f51_2","f51",100,0.2,1.1);
        TH1D *HLT_hIso2 = new TH1D("HLT_hIso2","hIso",100,-1,10);

        TH1D *HLT_RZcurv3 = new TH1D("HLT_RZcurv3","",100,-0.01,0.01);
        TH1D *HLT_DedXSig3 = new TH1D("HLT_DedXSig3","dE/dX significant distribution",100,0,30);
        TH1D *HLT_f51_3 = new TH1D("HLT_f51_3","f51",100,0.2,1.1);
        TH1D *HLT_hIso3 = new TH1D("HLT_hIso3","hIso",100,-1,10);
 
  for(int m=0;m<3;m++){
	TFile *fin = new TFile(file_m[m].c_str());
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

//	TCanvas *canvas = new TCanvas("canvas","canvas",800,600);
	//NO TRG plot
	TH2D *h_FracSatVNstrips = new TH2D("h_FracSatVNstrips","Fraction of saturated strips vs. no. of strips",100,0,1000,100,0,1);
	TH2D *h_ABCD = new TH2D("h_ABCD","",100,0,1.1,100,0,30);
	TH2D *h_Signal = new TH2D("h_Signal","",100,0,1.1,100,0,30);
	//HLT pass
        TH2D *HLT_FracSatVNstrips = new TH2D("HLT_FracSatVNstrips","Fraction of saturated strips vs. no. of strips",100,0,1000,100,0,1);
        TH2D *HLT_ABCD = new TH2D("HLT_ABCD","",100,0,1.1,100,0,30);
	TH2D *HLT_Signal = new TH2D("HLT_Signal","",100,0,1.1,100,0,30);

	double subHits_count=0;
	double subSatHits_count=0;
	int test=0;
        const unsigned NEvents = tree->GetEntries();
//	MonoCuts Cuts;
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
		//cut
//		Cuts.doAnalysis(cand,passHLT_Photon200);	       		
	 //	Cuts.doAnalysis(cand,false);


		h_FracSatVNstrips->Fill(cand[0].subHits_,cand[0].subSatHits_/cand[0].subHits_);
		
		switch (m){
		case 0:
		h_DedXSig1->Fill(cand[0].dEdXSig_);
		h_f51_1->Fill(cand[0].f51_);
		h_hIso1->Fill(cand[0].hIso_);
		h_RZcurv1->Fill(cand[0].rzp2_);
		break;
		case 1:
		h_DedXSig2->Fill(cand[0].dEdXSig_);
		h_f51_2->Fill(cand[0].f51_);
		h_hIso2->Fill(cand[0].hIso_);
		h_RZcurv2->Fill(cand[0].rzp2_);
                break;
		case 2:
                h_DedXSig3->Fill(cand[0].dEdXSig_);
		h_f51_3->Fill(cand[0].f51_);
		h_hIso3->Fill(cand[0].hIso_);
		h_RZcurv3->Fill(cand[0].rzp2_);
		break;
		}

		h_ABCD->Fill(cand[0].f51_,cand[0].dEdXSig_);

		if( cand[0].xyp0_< 0.6 && cand[0].xyp2_ > 1000
                        && cand[0].dist_ < 0.5  && cand[0].hIso_ < 10
			&& cand[0].f51_>0.85 
			&& cand[0].dEdXSig_>9
			&& cand[0].e55_>200)
		{ h_Signal->Fill(cand[0].f51_,cand[0].dEdXSig_);}


		if(passHLT_Photon200==true){
		switch (m){
		case 0:
		HLT_DedXSig1->Fill(cand[0].dEdXSig_);
		HLT_f51_1->Fill(cand[0].f51_);
		HLT_hIso1->Fill(cand[0].hIso_);
		HLT_RZcurv1->Fill(cand[0].rzp2_);
		break;
		case 1:
		HLT_DedXSig2->Fill(cand[0].dEdXSig_);
		HLT_f51_2->Fill(cand[0].f51_);
		HLT_hIso2->Fill(cand[0].hIso_);
		HLT_RZcurv2->Fill(cand[0].rzp2_);
                break;
		case 2:
                HLT_DedXSig3->Fill(cand[0].dEdXSig_);
		HLT_f51_3->Fill(cand[0].f51_);
		HLT_hIso3->Fill(cand[0].hIso_);
		HLT_RZcurv3->Fill(cand[0].rzp2_);
		break;
		}
  		   if( cand[0].xyp0_< 0.6 && cand[0].xyp2_ > 1000
                        && cand[0].dist_ < 0.5  && cand[0].hIso_ < 10
                        && cand[0].f51_>0.85
                        && cand[0].dEdXSig_>9
                        && cand[0].e55_>200)
                     { HLT_Signal->Fill(cand[0].f51_,cand[0].dEdXSig_);}

                }

		subHits->clear();
                subSatHits->clear();
                dEdXSig->clear();
                tIso->clear();
                xyp0->clear();
                xyp1->clear();
                xyp2->clear();
                rzp0->clear();
                rzp1->clear();
                rzp2->clear();
                dist->clear();
                f51->clear();
                f15->clear();
                e55->clear();
                hIso->clear();
                eta->clear();
                phi->clear();

	     }

	delete fin;
	}//for loop
	

	//Cuts.SignalEff();
        gStyle->SetOptStat(0);
	
	//NO TRG
/*	h_FracSatVNstrips->SetXTitle("Total No. of Strips");
        h_FracSatVNstrips->SetYTitle("fraction of saturated strips");
	h_FracSatVNstrips->SetTitle("");
        h_FracSatVNstrips->Draw();        
	mgr::SetSinglePad(canvas);
        mgr::SetAxis(h_FracSatVNstrips);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
	canvas->SaveAs("FracSatVNstrips_15k.pdf");
*/
	
	gStyle->SetHatchesSpacing(3005); 	
	h_DedXSig3->Draw();
	h_DedXSig3->SetXTitle("dE/dX Significance");
	h_DedXSig3->SetYTitle("Entries");
	h_DedXSig3->SetTitle("");
/*	h_DedXSig1->SetFillColorAlpha(46, 0.5);
	h_DedXSig2->SetFillColorAlpha(9, 0.7);
	h_DedXSig3->SetFillColorAlpha(8, 0.9);
*/      h_DedXSig1->SetLineColorAlpha(46,2);//red for 1000
        h_DedXSig2->SetLineColorAlpha(9,2);//blue for 2000
        h_DedXSig3->SetLineColorAlpha(8,2);//green for 3000
	h_DedXSig1->Draw("same");
	h_DedXSig2->Draw("same");
	mgr::SetSinglePad(canvas);
        mgr::SetAxis(h_DedXSig3);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
	TLegend *leg = new TLegend(0.18,0.75,0.33,0.85); 
	leg->SetBorderSize( 0 );
        leg->SetFillColorAlpha( 0, 0 );
        leg->AddEntry(h_DedXSig1,"1000 GeV(2018)","f");
        leg->AddEntry(h_DedXSig2,"2000 GeV(2018)","f");
        leg->AddEntry(h_DedXSig3,"3000 GeV(2018)","f");
	leg->Draw();
	canvas->SaveAs("DedXSig 2018.pdf");
	
	h_f51_3->SetXTitle("f51(E5x1/E5x5)");
	h_f51_3->SetYTitle("Entries");
	h_f51_3->SetLineColorAlpha(28,0.5);
	h_f51_3->SetTitle("");
        h_f51_1->SetLineColorAlpha(46,2);//red for 1000
        h_f51_2->SetLineColorAlpha(9,2);//blue for 2000
        h_f51_3->SetLineColorAlpha(8,2);//green for 3000
	h_f51_3->Draw();
	h_f51_1->Draw("same");
	h_f51_2->Draw("same");
	mgr::SetSinglePad(canvas);
        mgr::SetAxis(h_f51_3);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
	TLegend *leg2 = new TLegend(0.18,0.77,0.43,0.87);
        leg2->SetBorderSize( 0 );
        leg2->SetFillColorAlpha( 0, 0 );
        leg2->AddEntry(h_f51_1,"1000 GeV(2018)","f");
        leg2->AddEntry(h_f51_2,"2000 GeV(2018)","f");
        leg2->AddEntry(h_f51_3,"3000 GeV(2018)","f");
	leg2->Draw();
	canvas->SaveAs("f51 2018.pdf");
	
	h_hIso3->SetXTitle("Energy(GeV)");
	h_hIso3->SetYTitle("Entries");
	h_hIso3->SetLineColorAlpha(28,0.5);
	h_hIso3->SetTitle("");
        h_hIso1->SetLineColorAlpha(46,2);//red for 1000
        h_hIso2->SetLineColorAlpha(9,2);//blue for 2000
        h_hIso3->SetLineColorAlpha(8,2);//green for 3000
	h_hIso3->Draw();
	h_hIso2->Draw("same");
	h_hIso1->Draw("same");
	mgr::SetSinglePad(canvas);
        mgr::SetAxis(h_hIso3);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
	TLegend *leg3 = new TLegend(0.7,0.77,0.95,0.87);
        leg3->SetBorderSize( 0 );
        leg3->SetFillColorAlpha( 0, 0 );
        leg3->AddEntry(h_hIso1,"1000 GeV(2018)","f");
        leg3->AddEntry(h_hIso2,"2000 GeV(2018)","f");
        leg3->AddEntry(h_hIso3,"3000 GeV(2018)","f");
        leg3->Draw();
	canvas->SaveAs("hIso 2018.pdf");

	h_RZcurv3->SetXTitle("R-Z curvature");
        h_RZcurv3->SetYTitle("Entries");
        h_RZcurv3->SetLineColorAlpha(28,0.5);
        h_RZcurv3->SetTitle("");
        h_RZcurv1->SetLineColorAlpha(46,2);//red for 1000
        h_RZcurv2->SetLineColorAlpha(9,2);//blue for 2000
        h_RZcurv3->SetLineColorAlpha(8,2);//green for 3000
	h_RZcurv3->Draw();
	h_RZcurv1->Draw("same");
	h_RZcurv2->Draw("same");
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(h_RZcurv3);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
        TLegend *leg4 = new TLegend(0.7,0.77,0.95,0.87);
        leg4->SetBorderSize( 0 );
        leg4->SetFillColorAlpha( 0, 0 );
        leg4->AddEntry(h_RZcurv1,"1000 GeV(2018)","f");
        leg4->AddEntry(h_RZcurv2,"2000 GeV(2018)","f");
        leg4->AddEntry(h_RZcurv3,"3000 GeV(2018)","f");
	leg4->Draw();
        canvas->SaveAs("RZcurv 2018.pdf");


/*	h_ABCD->SetXTitle("f51");
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

	h_Signal->SetXTitle("f51");
        h_Signal->SetYTitle("dE/dX significance");
        h_Signal->SetTitle("");
        h_Signal->SetMarkerStyle(7);
        h_Signal->Draw();
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(h_Signal);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
        TLine *Tight2Y = new TLine(0,MonoCuts::dEdXSigCut_,1.1,MonoCuts::dEdXSigCut_);
        Tight2Y->SetLineColor(4);
        Tight2Y->SetLineStyle(7);
        Tight2Y->SetLineWidth(3);
        Tight2Y->Draw("same");
        TLine *Tight2X = new TLine(MonoCuts::f51Cut_,0,MonoCuts::f51Cut_,30);
        Tight2X->SetLineColor(4);
        Tight2X->SetLineStyle(7);
        Tight2X->SetLineWidth(3);
        Tight2X->Draw("same");
        TLine *Loose2Y = new TLine(0,7,1.1,7);
        Loose2Y->SetLineColor(38);
        Loose2Y->SetLineStyle(7);
        Loose2Y->Draw("same");
        TLine *Loose2X = new TLine(0.6,0,0.6,30);
        Loose2X->SetLineColor(38);
        Loose2X->SetLineStyle(7);
        Loose2X->Draw("same");
        canvas->SaveAs("Signal_15k.pdf");
*/

	//HLT pass-----------------------------------------------------------------------------------------



	HLT_DedXSig3->Draw();
	HLT_DedXSig3->SetXTitle("dE/dX Significance");
	HLT_DedXSig3->SetYTitle("Entries");
	HLT_DedXSig3->SetTitle("");
/*        HLT_DedXSig1->SetFillColorAlpha(46, 0.5);
        HLT_DedXSig2->SetFillColorAlpha(9, 0.7);
        HLT_DedXSig3->SetFillColorAlpha(8, 0.9);
*/      HLT_DedXSig1->SetLineColorAlpha(46,2);//red for 1000
        HLT_DedXSig2->SetLineColorAlpha(9,2);//blue for 2000
        HLT_DedXSig3->SetLineColorAlpha(8,2);//green for 3000
	HLT_DedXSig1->Draw("same");
	HLT_DedXSig2->Draw("same");
	mgr::SetSinglePad(canvas);
        mgr::SetAxis(HLT_DedXSig3);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
	TLegend *HLT_leg = new TLegend(0.18,0.75,0.33,0.85); 
	HLT_leg->SetBorderSize( 0 );
        HLT_leg->SetFillColorAlpha( 0, 0 );
        HLT_leg->AddEntry(HLT_DedXSig1,"1000 GeV(2018)","f");
        HLT_leg->AddEntry(HLT_DedXSig2,"2000 GeV(2018)","f");
        HLT_leg->AddEntry(HLT_DedXSig3,"3000 GeV(2018)","f");
	HLT_leg->Draw();
	canvas->SaveAs("DedXSig HLT 2018.pdf");
	
	HLT_f51_2->SetXTitle("f51(E5x1/E5x5)");
	HLT_f51_2->SetYTitle("Entries");
	HLT_f51_2->SetLineColorAlpha(28,0.5);
	HLT_f51_2->SetTitle("");
        HLT_f51_1->SetLineColorAlpha(46,2);//red for 1000
        HLT_f51_2->SetLineColorAlpha(9,2);//blue for 2000
        HLT_f51_3->SetLineColorAlpha(8,2);//green for 3000
	HLT_f51_2->Draw();
	HLT_f51_1->Draw("same");
	HLT_f51_3->Draw("same");
	mgr::SetSinglePad(canvas);
        mgr::SetAxis(HLT_f51_2);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
	TLegend *HLT_leg2 = new TLegend(0.18,0.77,0.43,0.87);
        HLT_leg2->SetBorderSize( 0 );
        HLT_leg2->SetFillColorAlpha( 0, 0 );
        HLT_leg2->AddEntry(HLT_f51_1,"1000 GeV(2018)","f");
        HLT_leg2->AddEntry(HLT_f51_2,"2000 GeV(2018)","f");
        HLT_leg2->AddEntry(HLT_f51_3,"3000 GeV(2018)","f");
	HLT_leg2->Draw();
	canvas->SaveAs("f51 HLT 2018.pdf");
	
	HLT_hIso2->SetXTitle("Energy(GeV)");
	HLT_hIso2->SetYTitle("Entries");
	HLT_hIso2->SetLineColorAlpha(28,0.5);
	HLT_hIso2->SetTitle("");
        HLT_hIso1->SetLineColorAlpha(46,2);//red for 1000
        HLT_hIso2->SetLineColorAlpha(9,2);//blue for 2000
        HLT_hIso3->SetLineColorAlpha(8,2);//green for 3000
	HLT_hIso2->Draw();
	HLT_hIso1->Draw("same");
	HLT_hIso3->Draw("same");
	mgr::SetSinglePad(canvas);
        mgr::SetAxis(HLT_hIso2);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
	TLegend *HLT_leg3 = new TLegend(0.7,0.77,0.95,0.87);
        HLT_leg3->SetBorderSize( 0 );
        HLT_leg3->SetFillColorAlpha( 0, 0 );
        HLT_leg3->AddEntry(HLT_hIso1,"1000 GeV(2018)","f");
        HLT_leg3->AddEntry(HLT_hIso2,"2000 GeV(2018)","f");
        HLT_leg3->AddEntry(HLT_hIso3,"3000 GeV(2018)","f");
        HLT_leg3->Draw();
	canvas->SaveAs("hIso HLT 2018.pdf");

	HLT_RZcurv2->SetXTitle("R-Z curvature");
        HLT_RZcurv2->SetYTitle("Entries");
        HLT_RZcurv2->SetLineColorAlpha(28,0.5);
        HLT_RZcurv2->SetTitle("");
        HLT_RZcurv1->SetLineColorAlpha(46,2);//red for 1000
        HLT_RZcurv2->SetLineColorAlpha(9,2);//blue for 2000
        HLT_RZcurv3->SetLineColorAlpha(8,2);//green for 3000
	HLT_RZcurv2->Draw();
	HLT_RZcurv1->Draw("same");
	HLT_RZcurv3->Draw("same");
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(HLT_RZcurv2);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("15000 Entires");
        TLegend *HLT_leg4 = new TLegend(0.7,0.77,0.95,0.87);
        HLT_leg4->SetBorderSize( 0 );
        HLT_leg4->SetFillColorAlpha( 0, 0 );
        HLT_leg4->AddEntry(HLT_RZcurv1,"1000 GeV(2018)","f");
        HLT_leg4->AddEntry(HLT_RZcurv2,"2000 GeV(2018)","f");
        HLT_leg4->AddEntry(HLT_RZcurv3,"3000 GeV(2018)","f");
	HLT_leg4->Draw();
        canvas->SaveAs("RZcurv HLT 2018.pdf");

}
