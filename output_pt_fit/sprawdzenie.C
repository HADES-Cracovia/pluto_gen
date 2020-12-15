#define sprawdzenie_cxx
#include "sprawdzenie.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
void rescaleHist(TH1F* h,double scale=1, double shift=0)
{
  TH1F* temp=(TH1F*)h->Clone("temp");
  int nbins=temp->GetNbinsX();
  h->Reset();
  h->SetBins(temp->GetNbinsX(),temp->GetXaxis()->GetBinLowEdge(1)*scale+shift, temp->GetXaxis()->GetBinUpEdge(nbins)*scale+shift);

  for(int i=0;i<=nbins;i++)
    {
      //h->SetBins(i,temp->GetXaxis()->GetBinLowEdge(i)*scale+shift,temp->GetXaxis()->GetBinUpEdge(i)*scale+shift);
      h->SetBinContent(i,temp->GetBinContent(i));
    }
  delete temp;
}
  

void sprawdzenie::Loop()
{
  //   In a ROOT session, you can do:
  //      Root > .L sprawdzenie.C
  //      Root > sprawdzenie t
  //      Root > t.GetEntry(12); // Fill t data members with entry number 12
  //      Root > t.Show();       // Show values of entry 12
  //      Root > t.Show(16);     // Read and show values of entry 16
  //      Root > t.Loop();       // Loop on all entries
  //

  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;
  TFile* fEff=new TFile("/lustre/hades/user/knowakow/PNB/FAT/PPIMPIPPIM/All_analysis/eff_output.root","read");
  TFile* output=new TFile("sprawdzenie_output.root","RECREATE");

  TH2F* h2Eff=(TH2F*)fEff->Get("h2PtvsYEff");
  
  TH1F* hMinvL1520=new TH1F("hMinvL1520","Reconstructed #Lambda(1520) mass;M^{inv}_{#Lambda #pi^{+} #pi^{-}}[GeV]",1000,1,2);
  TH1F* hPtL1520=new TH1F("hPtL1520","P_{T} for #Lambda(1520);P_{T}[GeV]",32,0,1.6);
  TH1F* hYL1520=new TH1F("hYL1520","Rapidity for #Lambda(1520)",40,0,2);

  TH1F* hMinvL1116=new TH1F("hMinvL1116","Reconstructed #Lambda(1116) mass;M^{inv}_{#Lambda #pi^{+} #pi^{-}}[GeV]",1000,1,2);
  TH1F* hPtL1116=new TH1F("hPtL1116","P_{T} for #Lambda(1116); P_{T}[GeV]",32,0,1.6);
  TH1F* hYL1116=new TH1F("hYL1116","Rapidity for #Lambda(11116)",40,0,2);

  TH1F* hPipMomentum= new TH1F("hPipMomentum","p_{#pi^{+}}; p_{#pi^{+}} [GeV/c]",200,0,1);
  TH1F* hPimMomentum= new TH1F("hPimMomentum","p_{#pi^{-}}; p_{#pi^{-}} [GeV/c]",200,0,1);

  TH1F* hPipTheta= new TH1F("hPipTheta","#theta_{#pi^{+}};#theta_{#pi^{+}}",200,0,3.14);
  TH1F* hPimTheta= new TH1F("hPimTheta","#theta_{#pi^{-}};#theta_{#pi^{-}}",200,0,3.14);

  TH2F* h2PipMomentumTheta=new TH2F("h2PipMomentumTheta","p_{#pi^{+}} vs #theta_{#pi^{+}};#theta_{#pi^{+}};p_{#pi^{+}}[GeV/c]",50,0,3.14,50,0,1);
  TH2F* h2PimMomentumTheta=new TH2F("h2PimMomentumTheta","p_{#pi^{-}} vs #theta_{#pi^{-}};#theta_{#pi^{-}};p_{#pi^{-}}[GeV/c]",50,0,3.14,50,0,1);

  TH1F* hMinvL1520_corrected=new TH1F("hMinvL1520_corrected","Reconstructed #Lambda(1520) mass;M^{inv}_{#Lambda #pi^{+} #pi^{-}}[GeV]",1000,1,2);
  TH1F* hMinvL1116_corrected=new TH1F("hMinvL1116_corrected","Reconstructed #Lambda(1116) mass;M^{inv}_{#Lambda #pi^{+} #pi^{-}}[GeV]",1000,1,2);
   
  TH1F* hPtL1520_corrected=new TH1F("hPtL1520_corrected","P_{T} for #Lambda(1520);P_{T}[GeV]",32,0,1.6);
  TH1F* hYL1520_corrected=new TH1F("hYL1520_corrected","Rapidity for #Lambda(1520)",40,0,2);

  TH1F* hPtL1116_corrected=new TH1F("hPtL1116_corrected","P_{T} for #Lambda(1116); P_{T}[GeV]",32,0,1.6);
  TH1F* hYL1116_corrected=new TH1F("hYL1116_corrected","Rapidity for #Lambda(11116)",40,0,2);
  
  TH2F* h2PtvsY=new TH2F("h2PtvsY","P_{T} vs Y for events in #\Lambda(1520) window;P_{t} [MeV]; Y",17,0,1700,20,0,2);
  
  Long64_t nentries = fChain->GetEntries();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%100==0)
	std::cout<<"Event no "<<jentry<<" from "<<nentries<<", "<<100.*jentry/nentries<<"% analyzed"<<endl;
      
      TLorentzVector Lz, Ls, pip, pim;
      bool isLz=0;
      bool ispip=0;
      bool ispim=0;
      
      for(int j=0; j<Npart; j++)
	{
	  //std::cout<<"particle no "<<j<<" particle PID "<<Particles_pid[j]<<endl;
	  switch(Particles_pid[j])
	    {
	    case 18://L0
	      isLz=true;
	      Lz.SetPxPyPzE(Particles_fP_fX[j],Particles_fP_fY[j],Particles_fP_fZ[j],Particles_fE[j]);
	      hMinvL1116->Fill(Lz.M());
	      hPtL1116->Fill(Lz.Pt());
	      hYL1116->Fill(Lz.Rapidity());
	      break;
	    case 8://pi+
	      ispip=true;
	      pip.SetPxPyPzE(Particles_fP_fX[j],Particles_fP_fY[j],Particles_fP_fZ[j],Particles_fE[j]);
	      break;
	    case 9://pi-
	      ispim-=true;
	      pim.SetPxPyPzE(Particles_fP_fX[j],Particles_fP_fY[j],Particles_fP_fZ[j],Particles_fE[j]);
	      break;
	    }
	  if(isLz && ispip && ispim)
	    {
	      Ls=Lz+pip+pim;
	      double ww=h2Eff->GetBinContent(h2Eff->FindBin(Ls.Pt()*1000,Ls.Rapidity()));
	      /*     if(jentry<100)
		{
		  cout<<"bin number "<<h2Eff->FindBin(Ls.Pt()*1000,Ls.Rapidity())<<endl;
		  cout<<"Pt "<<Ls.Pt()*1000<<endl;
		  cout<<"Y  "<<Ls.Rapidity()<<endl;
		  cout<<"ww "<<ww<<endl;
		  }*/

	      hMinvL1520->Fill(Ls.M());
	      hPtL1520->Fill(Ls.Pt());
	      hYL1520->Fill(Ls.Rapidity());
	      hPtL1116->Fill(Lz.Pt());
	      hYL1116->Fill(Lz.Rapidity());

	      hMinvL1520_corrected->Fill(Ls.M(),ww);
	      hPtL1520_corrected->Fill(Ls.Pt(),ww);
	      hYL1520_corrected->Fill(Ls.Rapidity(),ww);
	      hPtL1116_corrected->Fill(Lz.Pt(),ww);
	      hYL1116_corrected->Fill(Lz.Rapidity(),ww);
	    
	      hPimTheta->Fill(pim.Theta());
	      hPipTheta->Fill(pip.Theta());
	      hPimMomentum->Fill(pim.P());
	      hPipMomentum->Fill(pip.P());

	      h2PimMomentumTheta->Fill(pim.Theta(), pim.P());
	      h2PipMomentumTheta->Fill(pip.Theta(), pip.P());
	    }

	}
    }
  int rebin=1;
  TCanvas *cEff=new TCanvas("cEff");
  h2Eff->Draw("lego");
  
  TCanvas *cM=new TCanvas("cM");
  cM->Divide(2);
  cM->cd(1);
  hMinvL1520->Draw();
  cM->cd(2);
  hMinvL1520_corrected->Draw();
  
  TCanvas *cPtY=new TCanvas("cPtY");
  cPtY->Divide(2);
  cPtY->cd(1);
  hYL1520->Draw();
  hYL1520->Rebin(rebin);
  cPtY->cd(2);
  hPtL1520->Draw();
  hPtL1520->Rebin(rebin);

  TCanvas *cPtY_corrected=new TCanvas("cPtY_corrected");
  cPtY_corrected->Divide(2);
  cPtY_corrected->cd(1);
  hYL1520_corrected->Draw();
  hYL1520_corrected->Rebin(rebin);
  cPtY_corrected->cd(2);
  hPtL1520_corrected->Draw();
  hPtL1520_corrected->Rebin(rebin);
  
  TCanvas *cM_L1116=new TCanvas("cM_L1116");
  hMinvL1116->Draw();

  TCanvas *cPtY_L1116=new TCanvas("cPtY_L1116");
  cPtY_L1116->Divide(2);
  cPtY_L1116->cd(1);
  hYL1116->Draw();
  hYL1116->Rebin(rebin);
  cPtY_L1116->cd(2);
  hPtL1116->Draw();
  hPtL1116->Rebin(rebin);

  TCanvas *cPtY_L1116_corrected=new TCanvas("cPtY_L1116_corrected");
  cPtY_L1116_corrected->Divide(2);
  cPtY_L1116_corrected->cd(1);
  hYL1116_corrected->Draw();
  hYL1116_corrected->Rebin(rebin);
  cPtY_L1116_corrected->cd(2);
  hPtL1116_corrected->Draw();
  hPtL1116_corrected->Rebin(rebin);
  
  TCanvas *cPions=new TCanvas("cPions","cPions");
  cPions->Divide(2);
  cPions->cd(1);
  hPipMomentum->Draw();
  hPimMomentum->Draw("same");
  hPimMomentum->SetLineColor(kRed);
  cPions->cd(2);
  hPipTheta->Draw();
  hPimTheta->Draw("same");
  hPimTheta->SetLineColor(kRed);

  TCanvas *cPvsTheta=new TCanvas("cPvsTheta","cPvsTheta");
  cPvsTheta->Divide(2);
  cPvsTheta->cd(1);
  h2PipMomentumTheta->Draw("colz");
  cPvsTheta->cd(2);
  h2PimMomentumTheta->Draw("colz");
  
  cM->Write();
  cPtY->Write();
  cPtY_corrected->Write();
  cM_L1116->Write();
  cPtY_L1116->Write();
  cPtY_L1116_corrected->Write();
  cPions->Write();
  cPvsTheta->Write();
  
  output->Write();
}
