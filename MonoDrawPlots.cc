#include <string>
using namespace std;
void MonoDrawPlots()
{
	//create a canvas
	TCanvas *canvas = new TCanvas("canvas","",800,600);

	//open file and directory
	TFile *fin = new TFile ("Monopole_Analyzer.root");
	TDirectory *dir = (TDirectory*)fin->Get("NO TRG");
 	dir->cd();
	
	gStyle->SetOptStat(0);
	const int plotNum = 10;
	string plotName[10] = { "NoCut_","N1_Quality_","N1_Energy_","N1_F51_","N1_dEdxSig_","N1_HLT_"
				,"Flow_Quality_","Flow_Energy_","Flow_F51_","Flow_dEdxSig_"};	
	string histogram[10] = { "","N_1_HLT_Quality_","N_1_HLT_Energy_","N_1_HLT_F51_",
				"N_1_HLT_dEdxSig_","N_1_HLT_HLT_","Flow_HLT_Quality_",
				"Flow_HLT_Energy_","Flow_HLT_F51_","Flow_HLT_dEdxSig_"};
	string plotCut[6] = {"FracSatVNstrips","DedXSig","RZcurv","F51","HcalIso","ABCD"};
	string Mass[3] = { "1TeV","2TeV","3TeV"};
	vector<TH1*> FracSatVNstrips;
	vector<TH1*> DedXSig;
	vector<TH1*> RZcurv;
	vector<TH1*> F51;
	vector<TH1*> HcalIso;
	vector<TH1*> ABCD;
	for(int i=0;i<plotNum;i++){
	
	// create FracSatVNstrips
	FracSatVNstrips.push_back((TH2D*)dir->Get((histogram[i]+"FracSatVNstrips").c_str()));
        FracSatVNstrips[i]->SetXTitle("Total No. of Strips");
        FracSatVNstrips[i]->SetYTitle("fraction of saturated strips");
        FracSatVNstrips[i]->SetTitle("");
        FracSatVNstrips[i]->Draw();
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(FracSatVNstrips[i]);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("2018 Mass 1TeV");
        canvas->SaveAs((plotName[i]+"FracSatVNstrips.pdf").c_str());
	
	//create dedx
	DedXSig.push_back((TH1D*)dir->Get((histogram[i]+"DedXSig").c_str()));
        DedXSig[i]->SetXTitle("dE/dX Significance");
        DedXSig[i]->SetYTitle("Entries");
        DedXSig[i]->SetTitle("");
        DedXSig[i]->SetLineColorAlpha(28,0.5);
        DedXSig[i]->SetFillColor(42);
        DedXSig[i]->Draw();
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(DedXSig[i]);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("2018 Mass 1TeV 15000 Entries");
        TLegend *leg = new TLegend(0.18,0.77,0.43,0.82); 
        leg->SetBorderSize( 0 );
        leg->SetFillColorAlpha( 0, 0 );
        leg->AddEntry(DedXSig[i],Mass[0].c_str(),"f");
        leg->Draw();
        canvas->SaveAs((plotName[i]+"DedXSig.pdf").c_str());
	
	//create f51
	F51.push_back((TH1D*)dir->Get((histogram[i]+"F51").c_str()));
        F51[i]->SetXTitle("F51(E5x1/E5x5)");
        F51[i]->SetYTitle("Entries");
        F51[i]->SetLineColorAlpha(28,0.5);
        F51[i]->SetFillColor(42);
        F51[i]->SetTitle("");
        F51[i]->Draw();
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(F51[i]);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("2018 Mass 1TeV 15000 Entires");
        TLegend *leg2 = new TLegend(0.18,0.77,0.43,0.82);
        leg2->SetBorderSize( 0 );
        leg2->SetFillColorAlpha( 0, 0 );
        leg2->AddEntry(F51[i],Mass[0].c_str(),"f");
        leg2->Draw();
        canvas->SaveAs((plotName[i]+"F51.pdf").c_str());
	
	//create hiso
	HcalIso.push_back((TH1D*)dir->Get((histogram[i]+"HcalIso").c_str()));
        HcalIso[i]->SetXTitle("Energy(GeV)");
        HcalIso[i]->SetYTitle("Entries");
        HcalIso[i]->SetLineColorAlpha(28,0.5);
        HcalIso[i]->SetFillColor(42);
        HcalIso[i]->SetTitle("");
        HcalIso[i]->Draw();
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(HcalIso[i]);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("2018 Mass 1TeV 15000 Entires");
        TLegend *leg3 = new TLegend(0.7,0.77,0.95,0.82);
        leg3->SetBorderSize( 0 );
        leg3->SetFillColorAlpha( 0, 0 );
        leg3->AddEntry(HcalIso[i],Mass[0].c_str(),"f");
        leg3->Draw();
        canvas->SaveAs((plotName[i]+"HcalIso.pdf").c_str());

	//Rz curv
	RZcurv.push_back((TH1D*)dir->Get((histogram[i]+"RZcurv").c_str()));
        RZcurv[i]->SetXTitle("R-Z curvature");
        RZcurv[i]->SetYTitle("Entries");
        RZcurv[i]->SetLineColorAlpha(28,0.5);
        RZcurv[i]->SetFillColor(42);
        RZcurv[i]->SetTitle("");
        RZcurv[i]->Draw();
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(RZcurv[i]);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("2018 Mass 1TeV 15000 Entires");
        TLegend *leg4 = new TLegend(0.7,0.77,0.95,0.82);
        leg4->SetBorderSize( 0 );
        leg4->SetFillColorAlpha( 0, 0 );
        leg4->AddEntry(RZcurv[i],Mass[0].c_str(),"f");
        leg4->Draw();
        canvas->SaveAs((plotName[i]+"RZcurv.pdf").c_str());
	

	double dEdXSigCut_ = 9;
	double f51Cut_ = 0.85;
	ABCD.push_back((TH2D*)dir->Get((histogram[i]+"ABCD").c_str()));
        ABCD[i]->SetXTitle("f51");
        ABCD[i]->SetYTitle("dE/dX significance");
        ABCD[i]->SetTitle("");
        ABCD[i]->SetMarkerStyle(7);
        ABCD[i]->Draw();
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(ABCD[i]);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight("2018 Mass 1TeV 15000 Entires");
        TLine *TightY = new TLine(0,dEdXSigCut_,1.1,dEdXSigCut_);
        TightY->SetLineColor(4);
        TightY->SetLineStyle(7);
        TightY->SetLineWidth(3);
        TightY->Draw("same");
        TLine *TightX = new TLine(f51Cut_,0,f51Cut_,30);
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
        canvas->SaveAs((plotName[i]+"ABCD.pdf").c_str());
	

	}

	
}
