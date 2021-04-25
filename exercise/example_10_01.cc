#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TH1F.h"
#include "BParticle.h"
#include "BEvent.h"
#include "math.h"
void example_10_01()
{
	TFile *fin = new TFile("hadron-1.root");
//	TTree *T;
//	fin->GetObject("T",T);//
	BEvent *Event = new BEvent();//create a activepointer Event in class's constructor BEvemt
	TTree *T = (TTree*)fin->Get("T");

	T->SetBranchAddress("BEvent",&Event);//let T pointer poinet to the branch"Event"

	TH1F *h_neutral = new TH1F("h_neutral","no. of neutral particles",31,-0.5,30.5);
	TH1F *h_charged = new TH1F ( "h_charged", "No. of charged particles", 31, -0.5, 30.5 );
	int NEvents =(int)T->GetEntries();
	cout<<"NEvents = "<<NEvents<<endl;
	for(int idx=0;idx<NEvents;idx++){
		if(idx%10000==0) cout<<"At Event "<<idx<<"/"<<NEvents<<endl;
		T->GetEntry(idx);
		//how many particles in each event 
		int NParticles = Event->NParticles();//let Event(branch BEvent) point to the function which save the pointer of every entries
		//cout<<NParticles<<endl;
		//to distinct every particle's property(charge)
		// TClonesArray allows you to "reuse" the same portion of memory for new/delete avoiding memory fragmentation and memory growth and improving the performance by orders of magnitude. 	
		TClonesArray& Plist = *(Event->GetParticleList());
		int n_neutral =0, n_charged=0;
		for(int i=0;i<NParticles;i++){
			BParticle *P1 = (BParticle*)Plist[i];
//			cout<<*P1<<endl;
			if(fabs(P1->charge())<0.5) n_neutral++;
			else n_charged++;
		}
//		cout<<"no. neutral: "<<n_neutral<<endl;
//		cout<<"no. charged: "<<n_charged<<endl;			
		h_neutral->Fill(n_neutral);
		h_charged->Fill(n_charged);
 	}

 	TCanvas* c1 = new TCanvas("c1","c1",1200,400);
	 c1->Divide(2,1);
	 c1->cd(1);
	 h_neutral->Draw("bar");
	 c1->cd(2);
	 h_charged->Draw("bar");
	
}
