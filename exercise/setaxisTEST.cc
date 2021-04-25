#include "iostream"
#include "TAttMarker.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TH1F.h"
#include "math.h"
#include <algorithm>

using namespace std;
void setaxisTEST(){

	TCanvas *canvas = new TCanvas("canvas","canvas",800,600);
	TH1D *h = new TH1D("h","h",100,0,100);
	TFile *fin = new TFile("MonoNtuple_MC_2018_1000.root");
        TTree *tree = (TTree*)fin->Get("monopoles");

	vector<double> * hIso = 0;
	unsigned nCandidates;

	tree->SetBranchAddress("cand_HIso",&hIso);
        tree->SetBranchAddress("cand_N",&nCandidates);

	vector<double> cand;
	for(unsigned ev=0; ev<tree->GetEntries();ev++){
             tree->GetEntry(ev);
         //       if(nCandidates>cand.size()) cand.resize(nCandidates);
                //for(unsigned i=0;i<nCandidates;i++){
		h->Fill((*hIso)[ev]);
	}
	
	h->SetYTitle("Entries");
	mgr::SetAxis(h);
	h->Draw();

}

