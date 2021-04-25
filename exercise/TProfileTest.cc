{
        TFile *f1 = new TFile("MonoNtuple_MC_2017_1000.root");
        TTree *tree1 = (TTree*)f1->Get("monopoles");

        double pT;
        unsigned NPV;
        unsigned nCandidates;
        vector<double> * e55 = 0;
        vector<double> Et;
        vector<double> * eta = 0;
        tree1->SetBranchAddress("mono_p",&pT);
        tree1->SetBranchAddress("NPV",&NPV);
        tree1->SetBranchAddress("cand_e55",&e55);
        tree1->SetBranchAddress("cand_N",&nCandidates);
        tree1->SetBranchAddress("cand_eta",&eta);

        vector<double> *subHits=0;
        vector<double> *subSatHits=0;
        vector<double> *dEdXSig=0;
        tree1->SetBranchAddress("cand_SubHits",&subHits);
        tree1->SetBranchAddress("cand_SatSubHits",&subSatHits);
        tree1->SetBranchAddress("cand_dEdXSig",&dEdXSig);

  auto c1 = new TCanvas("c1","Profile histogram example",200,10,700,500);
  auto hprof  = new TProfile("hprof","Profile of NPV versus dEdX",7,0,70,-1,30);
  
  for ( unsigned ev=0; ev<tree1->GetEntries();ev++) {
                tree1->GetEntry(ev);
                for(unsigned i=0;i<nCandidates;i++){
		    hprof->Fill(NPV,(*dEdXSig)[i],1);
  	/*	    if(NPV>0&&NPV<10){
			hprof0*/
		}
  }
  hprof->Draw();
  c1->SaveAs("TProfile test.pdf");
}
