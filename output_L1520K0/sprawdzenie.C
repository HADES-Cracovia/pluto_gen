#define sprawdzenie_cxx
#include "sprawdzenie.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

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
  TFile* output=new TFile("sprawdzenie_output.root","RECREATE");
  TH1F* hMinvL1520=new TH1F("hMinvL1520","Reconstructed #Lambda(1520) mass;M^{inv}_{#Lambda #pi^{+} #pi^{-}}[GeV]",1000,1,2);
  TH1F* hPtL1520=new TH1F("hPtL1520","P_{T} for #Lambda(1520);P_{T}[GeV]",500,0,1.7);
  TH1F* hYL1520=new TH1F("hYL1520","Rapidity for #Lambda(1520)",500,0,2);

  TH1F* hMinvL1116=new TH1F("hMinvL1116","Reconstructed #Lambda(1116) mass;M^{inv}_{#Lambda #pi^{+} #pi^{-}}[GeV]",1000,1,2);
  TH1F* hPtL1116=new TH1F("hPtL1116","P_{T} for #Lambda(1116); P_{T}[GeV]",500,0,1.7);
  TH1F* hYL1116=new TH1F("hYL1116","Rapidity for #Lambda(11116)",500,0,2);

  TH1F* hMinvK0=new TH1F("hMinvK0","A K^{0} invariant mass; K^{0}_{mass}[GeV]",1000,0,1);
  TH1F* hMinvRes=new TH1F("hMinvRes","Reconstructed primary resonance mass;M^{inv}_{#Lambda #pi^{+} #pi^{-} K^{0}}[GeV]",1500,1.5,3.0);

  
  TH1F* hPipMomentum= new TH1F("hPipMomentum","p_{#pi^{+}}; p_{#pi^{+}} [GeV/c]",200,0,1);
  TH1F* hPimMomentum= new TH1F("hPimMomentum","p_{#pi^{-}}; p_{#pi^{-}} [GeV/c]",200,0,1);

  TH1F* hPipTheta= new TH1F("hPipTheta","#theta_{#pi^{+}};#theta_{#pi^{+}}",200,0,3.14);
  TH1F* hPimTheta= new TH1F("hPimTheta","#theta_{#pi^{-}};#theta_{#pi^{-}}",200,0,3.14);

  TH2F* h2PipMomentumTheta=new TH2F("h2PipMomentumTheta","p_{#pi^{+}} vs #theta_{#pi^{+}};#theta_{#pi^{+}};p_{#pi^{+}}[GeV/c]",50,0,3.14,50,0,1);
  TH2F* h2PimMomentumTheta=new TH2F("h2PimMomentumTheta","p_{#pi^{-}} vs #theta_{#pi^{-}};#theta_{#pi^{-}};p_{#pi^{-}}[GeV/c]",50,0,3.14,50,0,1);
  
  Long64_t nentries = fChain->GetEntries();

  Long64_t nbytes = 0, nb = 0;
  for(Long64_t jentry=0; jentry<nentries;jentry++)
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%500==0)
	std::cout<<"Event no "<<jentry<<" from "<<nentries<<", "<<100.*jentry/nentries<<"% analyzed"<<endl;
      
      TLorentzVector Lz, Ls, pip, pim,K0,rez;
      bool isLz=0;
      bool ispip=0;
      bool ispim=0;
      bool isK0=0;
      
      
      for(int j=0; j<Npart; j++)
	{
	  //std::cout<<"particle no "<<j<<" ID: "<<Particles_pid[j]<<endl;
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
	      ispim=true;
	      pim.SetPxPyPzE(Particles_fP_fX[j],Particles_fP_fY[j],Particles_fP_fZ[j],Particles_fE[j]);
	      break;
	    case 16://K0S
	      isK0=true;
	      K0.SetPxPyPzE(Particles_fP_fX[j],Particles_fP_fY[j],Particles_fP_fZ[j],Particles_fE[j]);
	      break;
	    }
	  if(isLz && ispip && ispim && isK0)
	    {
	      Ls=Lz+pip+pim;
	      rez=Lz+pip+pim+K0;
	      hMinvL1520->Fill(Ls.M());
	      hPtL1520->Fill(Ls.Pt());
	      hYL1520->Fill(Ls.Rapidity());
	      hMinvK0->Fill(K0.M());
	      hMinvRes->Fill(rez.M());

	      hPimTheta->Fill(pim.Theta());
	      hPipTheta->Fill(pip.Theta());
	      hPimMomentum->Fill(pim.P());
	      hPipMomentum->Fill(pip.P());

	      h2PimMomentumTheta->Fill(pim.Theta(), pim.P());
	      h2PipMomentumTheta->Fill(pip.Theta(), pip.P());

	    }
	}
      // if (Cut(ientry) < 0) continue;
    }//end of the event loop
  TCanvas *cM=new TCanvas("cM");
  hMinvL1520->Draw();
  TCanvas *cPtY=new TCanvas("cPtY");
  cPtY->Divide(2);
  cPtY->cd(1);
  hYL1520->Draw();
  cPtY->cd(2);
  hPtL1520->Draw();

  TCanvas *cM_L1116=new TCanvas("cM_L1116");
  hMinvL1116->Draw();
  TCanvas *cPtY_L1116=new TCanvas("cPtY_L1116");
  cPtY_L1116->Divide(2);
  cPtY_L1116->cd(1);
  hYL1116->Draw();
  cPtY_L1116->cd(2);
  hPtL1116->Draw();

  TCanvas *cK0=new TCanvas("cK0");
  hMinvK0->Draw();

  TCanvas *cTotal=new TCanvas("cTotal");
  hMinvRes->Draw();

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
  cM_L1116->Write();
  cPtY_L1116->Write();
  cK0->Write();
  cTotal->Write();
  cPions->Write();
  cPvsTheta->Write();
  
  output->Write();
}
