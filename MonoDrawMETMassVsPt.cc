////////////////////////////////////////
//
//
//      File name: MonoDrawMETMassVsPt.cc
//      author: Shih Lin
//      Content: Higher mass have lower pt and hardly reach Ecal
//              
//      Output: /Plots/2016MC1TeV/*.pdf 
//	Date: 2021.5.29
//
///////////////////////////////////////////////////

#include <string>
using namespace std;
void MonoDrawMETMassVsPt()
{
        gStyle->SetOptStat(0);

	TCanvas *canvas = new TCanvas("canvas","",800,600);
		TFile *fin1 = new TFile ("Monopole_MET_analysis_13500.root");
		TFile *fin3 = new TFile ("Monopole_METAnalysis_3000.root");
		TDirectory *NOTRG1 = (TDirectory*)fin1->Get("NOTRG");
		TDirectory *NOTRG3 = (TDirectory*)fin3->Get("NOTRG");
		NOTRG1->cd();
		NOTRG3->cd();
	TH1D *MonoPtInTrackerVsMass1;
	MonoPtInTrackerVsMass1 = (TH1D*)NOTRG1->Get("MonoPtvsTracker");
	TH1D *MonoPtInTrackerVsMass3;
	MonoPtInTrackerVsMass3 = (TH1D*)NOTRG3->Get("MonoPtvsTracker");

	TH1D *MonoPtInEcalVsMass1;
	MonoPtInEcalVsMass1 = (TH1D*)NOTRG1->Get("MonoPtvsEcal");
	TH1D *MonoPtInEcalVsMass3;
	MonoPtInEcalVsMass3 = (TH1D*)NOTRG3->Get("MonoPtvsEcal");

	
	
	MonoPtInEcalVsMass1->SetXTitle("pT(GeV)");
        MonoPtInEcalVsMass1->SetYTitle("Entries");
        MonoPtInEcalVsMass1->SetTitle("");
        MonoPtInEcalVsMass1->Draw();
	MonoPtInEcalVsMass3->Draw("same");
        MonoPtInEcalVsMass1->SetLineColor(38);
	MonoPtInEcalVsMass1->SetLineColor(8);
	TLegend *leg = new TLegend(0.7,0.85,0.85,0.70);
        leg->SetBorderSize( 0 );
        leg->SetFillColorAlpha( 0, 0 );
        leg->AddEntry(MonoPtInEcalVsMass1,"1000GeV","f");
        leg->AddEntry(MonoPtInEcalVsMass3,"3000GeV","f");
        leg->Draw();
        canvas->SaveAs("./Plots/MonoPtInEcalvsMass.pdf");

	
	MonoPtInTrackerVsMass1->SetXTitle("pT(GeV)");
        MonoPtInTrackerVsMass1->SetYTitle("Entries");
        MonoPtInTrackerVsMass1->SetTitle("");
        MonoPtInTrackerVsMass1->Draw();
	MonoPtInTrackerVsMass3->Draw("same");
        MonoPtInTrackerVsMass1->SetLineColor(38);
	MonoPtInTrackerVsMass1->SetLineColor(8);
	TLegend *leg2 = new TLegend(0.7,0.85,0.85,0.70);
        leg2->SetBorderSize( 0 );
        leg2->SetFillColorAlpha( 0, 0 );
        leg2->AddEntry(MonoPtInTrackerVsMass1,"1000GeV","f");
        leg2->AddEntry(MonoPtInTrackerVsMass3,"3000GeV","f");
        leg2->Draw();
        canvas->SaveAs("./Plots/MonoPtInTrackervsMass.pdf");


}
