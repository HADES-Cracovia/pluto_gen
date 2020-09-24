#define sprawdzenie_cxx
#include "sprawdzenie.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

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
  TH1F* hMinvL1520=new TH1F("hMinvL1520","Reconstructed #Lambda(1520) mass;M^{inv}_{#Lambda #pi^{+} # pi^{-}}[GeV]",1000,1,2);
  TH1F* hPtL1520=new TH1F("hPtL1520","P_{T} for #Lambda(1520);P_{T}[GeV]",500,0,1.7);
  TH1F* hYL1520=new TH1F("hYL1520","Rapidity for #Lambda(1520)",500,0,2);

  
  Long64_t nentries = fChain->GetEntries();

  Long64_t nbytes = 0, nb = 0;
  for(Long64_t jentry=0; jentry<nentries;jentry++)
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%500==0)
	cout<<"Event no "<<jentry<<" from "<<nentries<<", "<<100.*jentry/nentries<<"% analyzed"<<endl;
      
      TLorentzVector Lz, Ls, pip, pim,;
      bool isLz=0;
      bool ispip=0;
      bool ispim=0;
      
      for(int j=0; j<Npart; j++)
	{
	  switch(Particles_pid[j])
	    {
	    case 18://L0
	      isLz=true;
	      Lz.SetPxPyPzE(Particles_fP_fX[j],Particles_fP_fY[j],Particles_fP_fZ[j],Particles_fE[j]);
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
	      hMinvL1520->Fill(Ls.M());
	      hPtL1520->Fill(Ls.Pt());
	      hYL1520->Fill(Ls.Rapidity());
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

  cM->Write();
  cPtY->Write();
  
  output->Write();
}
