////////////////////////////////////////
//
//
//      File name: MonoDrawMETPlot.cc
//      author: Shih Lin
//      Content: stack MET vs monopole plots
//               Without HLT
//      Output: /Plots/2016MC1TeV/*.pdf 
//	Date: 2021.5.25
//
///////////////////////////////////////////////////

#include <string>
using namespace std;
void MonoDrawMETPlot()
{

	TCanvas *canvas = new TCanvas("canvas","",800,600);
//	canvas->SetLogy();
		//open file and directory
		TFile *fin = new TFile ("Monopole_MET_analysis_13500.root");
		TDirectory *NOTRG = (TDirectory*)fin->Get("NOTRG");
		NOTRG->cd();
	
	vector<TH1*> METvsMonopole;	
	
	gStyle->SetOptStat(0);

	string PlotName[10] = {"PFMETvsEcalTwoSpike","PFMETvsEcalTwoShower","PFMETvsEcalOneShowerOneSpike","PFMETvsEcalOneShower_TrkOne","PFMETvsEcalOneSpike_TrkOne"
			   	 ,"PFMETvsTrkTwo","PFMETvsEcalOneShower","PFMETvsEcalOneSpike","PFMETvsTrkOne","PFMETvsZeroMono"};
	
	METvsMonopole.push_back((TH1D*)NOTRG->Get("PFMETvsEcalTwoSpike"));
	METvsMonopole.push_back((TH1D*)NOTRG->Get("PFMETvsEcalTwoShower"));
	METvsMonopole.push_back((TH1D*)NOTRG->Get("PFMETvsEcalOneShowerOneSpike"));
	METvsMonopole.push_back((TH1D*)NOTRG->Get("PFMETvsEcalOneShower_TrkOne"));
	METvsMonopole.push_back((TH1D*)NOTRG->Get("PFMETvsEcalOneSpike_TrkOne"));
	METvsMonopole.push_back((TH1D*)NOTRG->Get("PFMETvsTrkTwo"));
	METvsMonopole.push_back((TH1D*)NOTRG->Get("PFMETvsEcalOneShower"));
	METvsMonopole.push_back((TH1D*)NOTRG->Get("PFMETvsEcalOneSpike"));
	METvsMonopole.push_back((TH1D*)NOTRG->Get("PFMETvsTrkOne"));			
	METvsMonopole.push_back((TH1D*)NOTRG->Get("PFMETvsZeroMono"));


/*	TH1D* PFMETvsEcalTwoSpike;
	TH1D* PFMETvsEcalTwoShower;
	TH1D* PFMETvsEcalOneShowerOneSpike;
	TH1D* PFMETvsTrkTwo;
	TH1D* PFMETvsEcalOneShower_TrkOne;
	TH1D* PFMETvsEcalOneSpike_TrkOne;
	TH1D* PFMETvsEcalOneShower;
	TH1D* PFMETvsEcalOneSpike;
	TH1D* PFMETvsTrkOne;
			
	PFMETvsEcalTwoSpike 		= NOTRG->Get("PFMETvsEcalTwoSpike");
	PFMETvsEcalTwoShower		= NOTRG->Get("PFMETvsEcalTwoShower");
	PFMETvsEcalOneShowerOneSpike	= NOTRG->Get("PFMETvsEcalOneShowerOneSpike");
	PFMETvsTrkTwo			= NOTRG->Get("PFMETvsTrkTwo");
	PFMETvsEcalOneShower_TrkOne	= NOTRG->Get("PFMETvsEcalOneShower_TrkOne");
	PFMETvsEcalOneSpike_TrkOne	= NOTRG->Get("PFMETvsEcalOneSpike_TrkOne");
	PFMETvsEcalOneShower		= NOTRG->Get("PFMETvsEcalOneShower");
	PFMETvsEcalOneSpike		= NOTRG->Get("PFMETvsEcalOneSpike");
	PFMETvsTrkOne			= NOTRG->Get("PFMETvsTrkOne");			
	
*/	
	TH1D *GenMET ;
	GenMET =(TH1D*)NOTRG->Get("GenMET");
	TH1D *GenMETminusTwoMonopole ;
	GenMETminusTwoMonopole=(TH1D*)NOTRG->Get("GenMETminusTwoMonopole");
	
//	METvsMonopole[9]->Draw();		
	
	cout<<"size "<<METvsMonopole.size()<<endl;
	for(int i=0;i<METvsMonopole.size();i++){

		cout<<"GenEntries      "<<METvsMonopole[i]->GetEntries()<<endl;
		cout<<"Integral        "<<METvsMonopole[i]->Integral()<<endl;
		cout<<"Integral(width) "<<METvsMonopole[i]->Integral("width")<<endl;
//        	METvsMonopole[i]->Scale(1./METvsMonopole[i]->GetEntries());
		METvsMonopole[i]->SetXTitle("MET(GeV)");
        	METvsMonopole[i]->SetYTitle("Entries");
       // 	METvsMonopole[i]->SetTitle("");
        	METvsMonopole[i]->Draw();
//		METvsMonopole[i]->SetLineColorAlpha(0,1);
        	mgr::SetSinglePad(canvas);
        	mgr::SetAxis(METvsMonopole[i]);
        	mgr::DrawCMSLabelOuter(SIMULATION);
        	mgr::DrawEntryRight("2018 1TeV 13500 Events");
        	canvas->SaveAs(("./Plots/"+PlotName[i]+".pdf").c_str());
	}
/*	METvsMonopole[0]->Draw("same");
	METvsMonopole[2]->Draw("same");
	METvsMonopole[6]->Draw("same");
	METvsMonopole[4]->Draw("same");
	METvsMonopole[8]->Draw("same");
	METvsMonopole[1]->Draw("same");
	METvsMonopole[3]->Draw("same");
	METvsMonopole[5]->Draw("same");
	METvsMonopole[0]->SetFillColorAlpha(kBlack+2, 0.35);	
	METvsMonopole[1]->SetFillColorAlpha(kBlue+2, 0.35);	
	METvsMonopole[2]->SetFillColorAlpha(kViolet+2, 0.35);	
	METvsMonopole[3]->SetFillColorAlpha(kMagenta+2, 0.35);	
	METvsMonopole[4]->SetFillColorAlpha(kPink+2, 0.35);	
	METvsMonopole[5]->SetFillColorAlpha(kRed+2, 0.35);	
	METvsMonopole[6]->SetFillColorAlpha(kOrange+2, 0.35);	
	METvsMonopole[7]->SetFillColorAlpha(kYellow+2, 0.35);	
	METvsMonopole[8]->SetFillColorAlpha(kGreen+2, 0.35);	
	METvsMonopole[9]->SetFillColorAlpha(kCyan+2, 0.35);	
*/	
	
/*	GenMETminusTwoMonopole->SetXTitle("MET(GeV)");
        GenMETminusTwoMonopole->SetYTitle("Entries");
        GenMETminusTwoMonopole->SetTitle("");
        GenMETminusTwoMonopole->Draw();
	GenMET->Draw("same");
        GenMETminusTwoMonopole->SetLineColor(38);
	GenMET->SetLineColor(8);
	TLegend *leg = new TLegend(0.7,0.85,1.00,0.70);
        leg->SetBorderSize( 0 );
        leg->SetFillColorAlpha( 0, 0 );
        leg->AddEntry(GenMET,"GenMET","f");
        leg->AddEntry(GenMETminusTwoMonopole,"GenMET - 2 mono","f");
        leg->Draw();
        canvas->SaveAs("./Plots/GenMETvsMonopoleStack.pdf");
*/
	

}
