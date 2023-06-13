{
#include "TAxis.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TNtupleD.h"
#include <stdio.h>
#include <stdlib.h>
//#include <vector.h>



	TFile * input1 = new TFile ("ntuple_ZZZ-1TeV-llvl.root");
        input1->cd("");
        TTree *Outtree1 = (TTree*)input1->Get("tree");

        TFile * input2 = new TFile ("ntuple_back1-llll.root");
        input2->cd("");
        TTree *Outtree2 = (TTree*)input2->Get("tree");

        TFile * input3 = new TFile ("ntuple_back2-wwz.root");
        input3->cd("");
        TTree *Outtree3 = (TTree*)input3->Get("tree");
       
       	TFile * input4 = new TFile ("ntuple_back3-mumuww.root");
        input4->cd("");
        TTree *Outtree4 = (TTree*)input4->Get("tree");
        
	TFile * input5 = new TFile ("ntuple_back4-mumuzz.root");
        input5->cd("");
        TTree *Outtree5 = (TTree*)input5->Get("tree");

        TFile * input6 = new TFile ("ntuple_back5-mumuwwz.root");
        input6->cd("");
        TTree *Outtree6 = (TTree*)input6->Get("tree");

       	TFile * input7 = new TFile ("selectionZZZ-full.root");
        input7->cd("");
        TTree *Outtree7 = (TTree*)input7->Get("tree1");
     
       int nentries1 = (int)Outtree1->GetEntries();
       cout<<"nentries1 = "<<nentries1<<endl;
   
       int nentries2 = (int)Outtree2->GetEntries();
       cout<<"nentries2 = "<<nentries2<<endl;
   
       int nentries3 = (int)Outtree3->GetEntries();
       cout<<"nentries3 = "<<nentries3<<endl;
   
       int nentries4 = (int)Outtree4->GetEntries();
       cout<<"nentries4 = "<<nentries4<<endl;

       int nentries5 = (int)Outtree5->GetEntries();
       cout<<"nentries5 = "<<nentries5<<endl;

       int nentries6 = (int)Outtree6->GetEntries();
       cout<<"nentries6 = "<<nentries6<<endl;

       int nentries7 = (int)Outtree7->GetEntries();
       cout<<"nentries7 = "<<nentries7<<endl;

       TH1D *PTA1   = new TH1D("a"," ",20,0,600);
//       PTA1->Sumw2();
       TH1D *PTA2   = new TH1D("b"," ",20,0,600);
  //     PTA2->Sumw2();
       TH1D *PTA3   = new TH1D("c"," ",20,0,600);
  //     PTA3->Sumw2();
       TH1D *PTA4   = new TH1D("d"," ",20,0,600);
       TH1D *PTA5   = new TH1D("e"," ",20,0,600);
       TH1D *PTA6   = new TH1D("f"," ",20,0,600);
       TH1D *PTA7   = new TH1D("g"," ",20,0,600);
       double mll1,mll2,mll3,mll4,mll5,mll6;
       float mll7;
       Outtree1->SetBranchAddress("met"    ,&mll1);
       Outtree2->SetBranchAddress("met"    ,&mll2);
       Outtree3->SetBranchAddress("met"    ,&mll3);
       Outtree4->SetBranchAddress("met"    ,&mll4);
       Outtree5->SetBranchAddress("met"    ,&mll5);
       Outtree6->SetBranchAddress("met"    ,&mll6);
       Outtree7->SetBranchAddress("MET"    ,&mll7);
    
       double L=1000.;
       for(int i=0; i<nentries1; i++)
     {
         Outtree1->GetEntry(i);
         PTA1->Fill(mll1,1.026e-3*L/float(nentries1));
     } 

      for(int i=0; i<nentries2; i++)
     {
         Outtree2->GetEntry(i);
         PTA2->Fill(mll2,5.093*L/float(nentries2));
     } 

       for(int i=0; i<nentries3; i++)
     {
         Outtree3->GetEntry(i);
         PTA3->Fill(mll3,7.067e-2*L/float(nentries3));
     }   

       for(int i=0; i<nentries4; i++)
     {
         Outtree4->GetEntry(i);
         PTA4->Fill(mll4,0.4023*L/float(nentries4));
     }

       for(int i=0; i<nentries5; i++)
     {
         Outtree5->GetEntry(i);
         PTA5->Fill(mll5,2.278e-3*L/float(nentries5));
     }


       for(int i=0; i<nentries6; i++)
     {
         Outtree6->GetEntry(i);
         PTA6->Fill(mll6,7.993e-2*L/float(nentries6));
     }

       for(int i=0; i<nentries7; i++)
     {
         Outtree7->GetEntry(i);
         PTA7->Fill(mll7,1.026e-3*L/float(nentries7));
     }
     
     
       TCanvas *c01 = new TCanvas("c01","",700,600);
      c01->SetLogy();
//      PTA3->SetTitle("the  distribution of mu+");
      PTA2->GetXaxis()->SetTitle("MET[GeV]");
      PTA2->GetYaxis()->SetTitle("Number of Entries");
    //  PTA2->GetXaxis()->CenterTitle();
     // PTA2->GetYaxis()->CenterTitle();
      PTA2->SetStats(false);
      PTA2->SetMinimum(0.005);
      PTA2->SetMaximum(100000);
      PTA2->SetLineColor(2);
      PTA2->SetLineWidth(3);
      PTA2->SetMarkerStyle(20);
      PTA2->GetXaxis()->SetTitleOffset(1.4);
      PTA2->Draw("HIST e");

      PTA3->SetLineColor(3);
      PTA3->SetLineWidth(3);
      PTA3->SetMarkerStyle(21);
      PTA3->SetStats(false);
  //    PTA3->Draw("HIST e sames");
  
      PTA1->SetLineColor(1);
      PTA1->SetLineWidth(3);
      PTA1->SetMarkerStyle(22);
      PTA1->SetStats(false);
      PTA1->Draw("HIST e sames");

      PTA4->SetLineColor(4);
      PTA4->SetLineWidth(3);
      PTA4->SetMarkerStyle(23);
      PTA4->SetStats(false);
      PTA4->Draw("HIST e sames");

      PTA5->SetLineColor(5);
      PTA5->SetLineWidth(3);
    //  PTA5->SetLineStyle(9);
      PTA5->SetMarkerStyle(23);
      PTA5->SetStats(false);
      PTA5->Draw("HIST e sames");


      PTA6->SetLineColor(6);
      PTA6->SetLineWidth(3);
      PTA6->SetMarkerStyle(23);
      PTA6->SetStats(false);
      PTA6->Draw("HIST e sames");

      PTA7->SetLineColor(28);
      PTA7->SetLineWidth(3);
      PTA7->SetLineStyle(9);
      PTA7->SetMarkerStyle(23);
      PTA7->SetStats(false);
      PTA7->Draw("HIST e sames");


     TLegend *l1 = new TLegend(0.76,0.74,0.89,0.89);
     l1->SetNColumns(2);
     l1->SetBorderSize(1);
     l1->SetFillColor(0);
     l1->AddEntry(PTA1,"ZZZ-1TeV");
     l1->AddEntry(PTA2,"bkg1-l^{+}l^{-}l^{+}l^{-}");
     l1->AddEntry(PTA3,"bkg2-W^{+}W^{-}Z");
     l1->AddEntry(PTA4,"bkg3-#mu^{+}#mu^{-}W^{+}W^{-}");
     l1->AddEntry(PTA5,"bkg4-#mu^{+}#mu^{-}ZZ");
     l1->AddEntry(PTA6,"bkg5-#mu^{+}#mu^{-}W^{+}W^{-}Z");
     l1->AddEntry(PTA7,"ZZZ-full-simulation");
     l1->Draw("Sames");

      TLatex *t = new TLatex();
     t->SetNDC();
     t->SetTextAlign(23);
     t->SetTextFont(64);
     t->SetTextSizePixels(20);
     t->DrawLatex(0.55,0.90,"the distribution of MET");
     t->Draw();

     c01->SaveAs("compare-pthh.png");

}
