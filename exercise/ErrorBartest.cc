{
   c1 = new TCanvas("c1","A Simple GraphErrors Example",200,10,700,500);
   const Int_t n = 20;
   Double_t x[n], y[n], ex[n], ey[n];
   for (Int_t i=0;i<n;i++) {
     x[i]  = i*0.1;
     y[i]  = 10*sin(x[i]+0.2);
     ex[i] = 0.08;
     ey[i] = 0.1*i;
   }
   TGraphErrors *gr = new TGraphErrors(n,x,y,ex,ey);
   gr->SetLineStyle(1);
   gr->Draw("AP");
                                                                                
   TGraphErrors *gr2 = new TGraphErrors(n,x,y,ex,ey);
   gr2->SetLineStyle(4);
   gr2->Draw("L");
}
