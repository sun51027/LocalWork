#include <string>
using namespace std;
void MonoDrawCompareMassTRG()
{
	//create a canvas
        string Mass[3] = { "1TeV","2TeV","3TeV"};
	string GeV[3] = {"1000","2000","3000"};
        string Year[2] = { "2017","2018"};

	TCanvas *canvas = new TCanvas("canvas","",800,600);

	for(int y=0;y<2;y++){
//	  for(int m=0;m<3;m++){
		//open file and directory
		TFile *fin_1 = new TFile (("Monopole_Analyzer_"+Year[y]+"_1000.root").c_str());
		TFile *fin_2 = new TFile (("Monopole_Analyzer_"+Year[y]+"_2000.root").c_str());
		TFile *fin_3 = new TFile (("Monopole_Analyzer_"+Year[y]+"_3000.root").c_str());
		TDirectory *dir_1 = (TDirectory*)fin_1->Get("HLT_Photon200");
		TDirectory *dir_2 = (TDirectory*)fin_2->Get("HLT_Photon200");
		TDirectory *dir_3 = (TDirectory*)fin_3->Get("HLT_Photon200");
	 
		dir_1->cd();
		dir_2->cd();
		dir_3->cd();
		
		gStyle->SetOptStat(0);
		const int plotNum = 5;
		//string plotName[10] = { "NoCut_","N1_Quality_","N1_Energy_","N1_F51_","N1_dEdxSig_","N1_HLT_"
		string plotName[5] = { "NoCut_","Flow_Quality_","Flow_Energy_","Flow_F51_","Flow_dEdxSig_"};	
/*		string histogram[10] = { "","N_1_HLT_Quality_","N_1_HLT_Energy_","N_1_HLT_F51_",
					"N_1_HLT_dEdxSig_","N_1_HLT_HLT_","Flow_HLT_Quality_",
					"Flow_HLT_Energy_","Flow_HLT_F51_","Flow_HLT_dEdxSig_"};
					,"Flow_Quality_","Flow_Energy_","Flow_F51_","Flow_dEdxSig_"};	
*/		string histogram[5] = { "","Flow_HLT_Quality_",
					"Flow_HLT_Energy_","Flow_HLT_F51_","Flow_HLT_dEdxSig_"};
		string plotCut[6] = {"FracSatVNstrips","DedXSig","RZcurv","F51","HcalIso","ABCD"};
		vector<TH1*> FracSatVNstrips;
		vector<TH1*> DedXSig1;
		vector<TH1*> DedXSig2;
		vector<TH1*> DedXSig3;
		vector<TH1*> RZcurv1;
		vector<TH1*> RZcurv2;
		vector<TH1*> RZcurv3;
		vector<TH1*> F511;
		vector<TH1*> F512;
		vector<TH1*> F513;
		vector<TH1*> HcalIso1;
		vector<TH1*> HcalIso2;
		vector<TH1*> HcalIso3;
		vector<TH1*> Energy1;
		vector<TH1*> Energy2;
		vector<TH1*> Energy3;
		vector<TH1*> ABCD;
		for(int i=0;i<plotNum;i++){
	
	// create FracSatVNstrips
/*	FracSatVNstrips.push_back((TH2D*)dir->Get((histogram[i]+"FracSatVNstrips").c_str()));
        FracSatVNstrips[i]->SetXTitle("Total No. of Strips");
        FracSatVNstrips[i]->SetYTitle("fraction of saturated strips");
        FracSatVNstrips[i]->SetTitle("");
        FracSatVNstrips[i]->Draw();
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(FracSatVNstrips[i]);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight((Year[y]+" Mass "+Mass[m]).c_str());
        canvas->SaveAs(("./Plots/"+Year[y]+" MC 15k "+Mass[m]+"/NoTRG/"+plotName[i]+"FracSatVNstrips.pdf").c_str());
*/	
	//create dedx
	DedXSig1.push_back((TH1D*)dir_1->Get((histogram[i]+"DedXSig").c_str()));
	DedXSig2.push_back((TH1D*)dir_2->Get((histogram[i]+"DedXSig").c_str()));
	DedXSig3.push_back((TH1D*)dir_3->Get((histogram[i]+"DedXSig").c_str()));
        DedXSig3[i]->SetXTitle("dE/dX Significance");
        DedXSig3[i]->SetYTitle("Entries");
        DedXSig3[i]->SetTitle("");
        DedXSig1[i]->SetLineColorAlpha(46,2);//red
        DedXSig2[i]->SetLineColorAlpha(9,2);//blue
        DedXSig3[i]->SetLineColorAlpha(8,2);//green
        DedXSig3[i]->Draw();
        DedXSig1[i]->Draw("same");
        DedXSig2[i]->Draw("same");
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(DedXSig3[i]);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight((Year[y]+" 15000 Entries").c_str());
        TLegend *leg = new TLegend(0.18,0.75,0.33,0.85); 
        leg->SetBorderSize( 0 );
        leg->SetFillColorAlpha( 0, 0 );
//        leg->AddEntry(DedXSig[i],Mass[m].c_str(),"f");
        leg->AddEntry(DedXSig1[i],("1000 GeV("+Year[y]+")").c_str(),"f");
        leg->AddEntry(DedXSig2[i],("2000 GeV("+Year[y]+")").c_str(),"f");
        leg->AddEntry(DedXSig3[i],("3000 GeV("+Year[y]+")").c_str(),"f");
        leg->Draw();
        canvas->SaveAs(("./Plots/TRG/"+Year[y]+" "+plotName[i]+"DedXSig.pdf").c_str());
	
	//create f51
	F511.push_back((TH1D*)dir_1->Get((histogram[i]+"F51").c_str()));
	F512.push_back((TH1D*)dir_2->Get((histogram[i]+"F51").c_str()));
	F513.push_back((TH1D*)dir_3->Get((histogram[i]+"F51").c_str()));
        F512[i]->SetXTitle("F51(E5x1/E5x5)");
        F513[i]->SetYTitle("Entries");
        F511[i]->SetLineColorAlpha(46,2);
        F512[i]->SetLineColorAlpha(9,2);
        F513[i]->SetLineColorAlpha(8,2);
        F512[i]->SetTitle("");
        F512[i]->Draw();
        F511[i]->Draw("same");
        F513[i]->Draw("same");
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(F512[i]);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight((Year[y]+" 15000 Entries").c_str());
        TLegend *leg2 = new TLegend(0.18,0.77,0.43,0.87);
        leg2->SetBorderSize( 0 );
        leg2->SetFillColorAlpha( 0, 0 );
        leg2->AddEntry(F511[i],("1000 GeV("+Year[y]+")").c_str(),"f");
        leg2->AddEntry(F512[i],("2000 GeV("+Year[y]+")").c_str(),"f");
        leg2->AddEntry(F513[i],("3000 GeV("+Year[y]+")").c_str(),"f");
        leg2->Draw();
        canvas->SaveAs(("./Plots/TRG/"+Year[y]+" "+plotName[i]+"f51.pdf").c_str());
	

	//create hiso
	HcalIso1.push_back((TH1D*)dir_1->Get((histogram[i]+"HcalIso").c_str()));
	HcalIso2.push_back((TH1D*)dir_2->Get((histogram[i]+"HcalIso").c_str()));
	HcalIso3.push_back((TH1D*)dir_3->Get((histogram[i]+"HcalIso").c_str()));
        HcalIso3[i]->SetXTitle("Energy(GeV)");
        HcalIso3[i]->SetYTitle("Entries");
        HcalIso1[i]->SetLineColorAlpha(46,2);
        HcalIso2[i]->SetLineColorAlpha(9,2);
        HcalIso3[i]->SetLineColorAlpha(8,2);
        HcalIso3[i]->SetTitle("");
        HcalIso3[i]->Draw();
        HcalIso1[i]->Draw("same");
        HcalIso2[i]->Draw("same");
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(HcalIso3[i]);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight((Year[y]+" 15000 Entries").c_str());
        TLegend *leg3 = new TLegend(0.7,0.77,0.95,0.87);
        leg3->SetBorderSize( 0 );
        leg3->SetFillColorAlpha( 0, 0 );
        leg3->AddEntry(HcalIso1[i],("1000 GeV("+Year[y]+")").c_str(),"f");
        leg3->AddEntry(HcalIso2[i],("2000 GeV("+Year[y]+")").c_str(),"f");
        leg3->AddEntry(HcalIso3[i],("3000 GeV("+Year[y]+")").c_str(),"f");
        leg3->Draw();
        canvas->SaveAs(("./Plots/TRG/"+Year[y]+" "+plotName[i]+"HcalIso.pdf").c_str());

	//Energy(e55)
        Energy1.push_back((TH1D*)dir_1->Get((histogram[i]+"E55").c_str()));
        Energy2.push_back((TH1D*)dir_2->Get((histogram[i]+"E55").c_str()));
        Energy3.push_back((TH1D*)dir_3->Get((histogram[i]+"E55").c_str()));
        Energy3[i]->SetXTitle("Energy(GeV)");
        Energy3[i]->SetYTitle("Entries");
        Energy1[i]->SetLineColorAlpha(46,2);
        Energy2[i]->SetLineColorAlpha(9,2);
        Energy3[i]->SetLineColorAlpha(8,2);
        Energy3[i]->SetTitle("");
        Energy3[i]->Draw();
        Energy1[i]->Draw("same");
        Energy2[i]->Draw("same");
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(Energy3[i]);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight((Year[y]+" 15000 Entries").c_str());
        TLegend *leg4 = new TLegend(0.7,0.77,0.95,0.87);
        leg4->SetBorderSize( 0 );
        leg4->SetFillColorAlpha( 0, 0 );
        leg4->AddEntry(Energy1[i],("1000 GeV("+Year[y]+")").c_str(),"f");
        leg4->AddEntry(Energy2[i],("2000 GeV("+Year[y]+")").c_str(),"f");
        leg4->AddEntry(Energy3[i],("3000 GeV("+Year[y]+")").c_str(),"f");
        leg4->Draw();
        canvas->SaveAs(("./Plots/TRG/"+Year[y]+" "+plotName[i]+"Energy.pdf").c_str());


	//Rz curv
	RZcurv1.push_back((TH1D*)dir_1->Get((histogram[i]+"RZcurv").c_str()));
	RZcurv2.push_back((TH1D*)dir_2->Get((histogram[i]+"RZcurv").c_str()));
	RZcurv3.push_back((TH1D*)dir_3->Get((histogram[i]+"RZcurv").c_str()));
        RZcurv2[i]->SetXTitle("R-Z curvature");
        RZcurv2[i]->SetYTitle("Entries");
        RZcurv1[i]->SetLineColorAlpha(46,2);
        RZcurv2[i]->SetLineColorAlpha(9,2);
        RZcurv2[i]->SetLineColorAlpha(8,2);
        RZcurv2[i]->SetTitle("");
        RZcurv2[i]->Draw();
        RZcurv1[i]->Draw("same");
        RZcurv3[i]->Draw("same");
        mgr::SetSinglePad(canvas);
        mgr::SetAxis(RZcurv2[i]);
        mgr::DrawCMSLabelOuter(SIMULATION);
        mgr::DrawEntryRight((Year[y]+" 15000 Entries").c_str());
        TLegend *leg5 = new TLegend(0.7,0.77,0.95,0.87);
        leg5->SetBorderSize( 0 );
        leg5->SetFillColorAlpha( 0, 0 );
        leg5->AddEntry(RZcurv1[i],("1000 GeV("+Year[y]+")").c_str(),"f");
        leg5->AddEntry(RZcurv2[i],("2000 GeV("+Year[y]+")").c_str(),"f");
        leg5->AddEntry(RZcurv3[i],("3000 GeV("+Year[y]+")").c_str(),"f");
        leg5->Draw();
        canvas->SaveAs(("./Plots/TRG/"+Year[y]+" "+plotName[i]+"RZcurv.pdf").c_str());
	

/*	double dEdXSigCut_ = 9;
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
        mgr::DrawEntryRight((Year[y]+" Mass "+Mass[m]+" 15000 Entries").c_str());
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
        canvas->SaveAs(("./Plots/"+Year[y]+" MC 15k "+Mass[m]+"/NoTRG/"+plotName[i]+"ABCD.pdf").c_str());
	
*/
	}
//     }//mass
    }//year
	
}
