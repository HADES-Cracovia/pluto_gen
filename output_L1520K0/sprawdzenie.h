//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Oct 30 15:45:33 2020 by ROOT version 5.34/34
// from TTree data/event branch
// found on file: L1520_thermal_925.root
//////////////////////////////////////////////////////////

#ifndef sprawdzenie_h
#define sprawdzenie_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TClonesArray.h>
#include <TObject.h>
#include <TVector3.h>
#include <TLorentzVector.h>

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxParticles = 4;

class sprawdzenie {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           Npart;
   Double_t        Impact;
   Double_t        Phi;
   Int_t           Particles_;
   UInt_t          Particles_fUniqueID[kMaxParticles];   //[Particles_]
   UInt_t          Particles_fBits[kMaxParticles];   //[Particles_]
   UInt_t          Particles_fP_fUniqueID[kMaxParticles];   //[Particles_]
   UInt_t          Particles_fP_fBits[kMaxParticles];   //[Particles_]
   Double_t        Particles_fP_fX[kMaxParticles];   //[Particles_]
   Double_t        Particles_fP_fY[kMaxParticles];   //[Particles_]
   Double_t        Particles_fP_fZ[kMaxParticles];   //[Particles_]
   Double_t        Particles_fE[kMaxParticles];   //[Particles_]
   Int_t           Particles_pid[kMaxParticles];   //[Particles_]
   Int_t           Particles_sourceId[kMaxParticles];   //[Particles_]
   Int_t           Particles_parentId[kMaxParticles];   //[Particles_]
   Int_t           Particles_parentIndex[kMaxParticles];   //[Particles_]
   Int_t           Particles_decayModeIndex[kMaxParticles];   //[Particles_]
   Int_t           Particles_destroyDecayModeIndex[kMaxParticles];   //[Particles_]
   Int_t           Particles_daughterIndex[kMaxParticles];   //[Particles_]
   Int_t           Particles_siblingIndex[kMaxParticles];   //[Particles_]
   Double_t        Particles_decayTime[kMaxParticles];   //[Particles_]
   Double_t        Particles_wt[kMaxParticles];   //[Particles_]
   UInt_t          Particles_fV_fUniqueID[kMaxParticles];   //[Particles_]
   UInt_t          Particles_fV_fBits[kMaxParticles];   //[Particles_]
   Double_t        Particles_fV_fX[kMaxParticles];   //[Particles_]
   Double_t        Particles_fV_fY[kMaxParticles];   //[Particles_]
   Double_t        Particles_fV_fZ[kMaxParticles];   //[Particles_]
   Double_t        Particles_fT[kMaxParticles];   //[Particles_]

   // List of branches
   TBranch        *b_Npart;   //!
   TBranch        *b_Impact;   //!
   TBranch        *b_Phi;   //!
   TBranch        *b_Particles_;   //!
   TBranch        *b_Particles_fUniqueID;   //!
   TBranch        *b_Particles_fBits;   //!
   TBranch        *b_Particles_fP_fUniqueID;   //!
   TBranch        *b_Particles_fP_fBits;   //!
   TBranch        *b_Particles_fP_fX;   //!
   TBranch        *b_Particles_fP_fY;   //!
   TBranch        *b_Particles_fP_fZ;   //!
   TBranch        *b_Particles_fE;   //!
   TBranch        *b_Particles_pid;   //!
   TBranch        *b_Particles_sourceId;   //!
   TBranch        *b_Particles_parentId;   //!
   TBranch        *b_Particles_parentIndex;   //!
   TBranch        *b_Particles_decayModeIndex;   //!
   TBranch        *b_Particles_destroyDecayModeIndex;   //!
   TBranch        *b_Particles_daughterIndex;   //!
   TBranch        *b_Particles_siblingIndex;   //!
   TBranch        *b_Particles_decayTime;   //!
   TBranch        *b_Particles_wt;   //!
   TBranch        *b_Particles_fV_fUniqueID;   //!
   TBranch        *b_Particles_fV_fBits;   //!
   TBranch        *b_Particles_fV_fX;   //!
   TBranch        *b_Particles_fV_fY;   //!
   TBranch        *b_Particles_fV_fZ;   //!
   TBranch        *b_Particles_fT;   //!

   sprawdzenie(TTree *tree=0);
   virtual ~sprawdzenie();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef sprawdzenie_cxx
sprawdzenie::sprawdzenie(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("L1520_thermal_16.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("L1520_thermal_16.root");
      }
      f->GetObject("data",tree);

   }
   Init(tree);
}

sprawdzenie::~sprawdzenie()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t sprawdzenie::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t sprawdzenie::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void sprawdzenie::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Npart", &Npart, &b_Npart);
   fChain->SetBranchAddress("Impact", &Impact, &b_Impact);
   fChain->SetBranchAddress("Phi", &Phi, &b_Phi);
   fChain->SetBranchAddress("Particles", &Particles_, &b_Particles_);
   fChain->SetBranchAddress("Particles.fUniqueID", Particles_fUniqueID, &b_Particles_fUniqueID);
   fChain->SetBranchAddress("Particles.fBits", Particles_fBits, &b_Particles_fBits);
   fChain->SetBranchAddress("Particles.fP.fUniqueID", Particles_fP_fUniqueID, &b_Particles_fP_fUniqueID);
   fChain->SetBranchAddress("Particles.fP.fBits", Particles_fP_fBits, &b_Particles_fP_fBits);
   fChain->SetBranchAddress("Particles.fP.fX", Particles_fP_fX, &b_Particles_fP_fX);
   fChain->SetBranchAddress("Particles.fP.fY", Particles_fP_fY, &b_Particles_fP_fY);
   fChain->SetBranchAddress("Particles.fP.fZ", Particles_fP_fZ, &b_Particles_fP_fZ);
   fChain->SetBranchAddress("Particles.fE", Particles_fE, &b_Particles_fE);
   fChain->SetBranchAddress("Particles.pid", Particles_pid, &b_Particles_pid);
   fChain->SetBranchAddress("Particles.sourceId", Particles_sourceId, &b_Particles_sourceId);
   fChain->SetBranchAddress("Particles.parentId", Particles_parentId, &b_Particles_parentId);
   fChain->SetBranchAddress("Particles.parentIndex", Particles_parentIndex, &b_Particles_parentIndex);
   fChain->SetBranchAddress("Particles.decayModeIndex", Particles_decayModeIndex, &b_Particles_decayModeIndex);
   fChain->SetBranchAddress("Particles.destroyDecayModeIndex", Particles_destroyDecayModeIndex, &b_Particles_destroyDecayModeIndex);
   fChain->SetBranchAddress("Particles.daughterIndex", Particles_daughterIndex, &b_Particles_daughterIndex);
   fChain->SetBranchAddress("Particles.siblingIndex", Particles_siblingIndex, &b_Particles_siblingIndex);
   fChain->SetBranchAddress("Particles.decayTime", Particles_decayTime, &b_Particles_decayTime);
   fChain->SetBranchAddress("Particles.wt", Particles_wt, &b_Particles_wt);
   fChain->SetBranchAddress("Particles.fV.fUniqueID", Particles_fV_fUniqueID, &b_Particles_fV_fUniqueID);
   fChain->SetBranchAddress("Particles.fV.fBits", Particles_fV_fBits, &b_Particles_fV_fBits);
   fChain->SetBranchAddress("Particles.fV.fX", Particles_fV_fX, &b_Particles_fV_fX);
   fChain->SetBranchAddress("Particles.fV.fY", Particles_fV_fY, &b_Particles_fV_fY);
   fChain->SetBranchAddress("Particles.fV.fZ", Particles_fV_fZ, &b_Particles_fV_fZ);
   fChain->SetBranchAddress("Particles.fT", Particles_fT, &b_Particles_fT);
   Notify();
}

Bool_t sprawdzenie::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void sprawdzenie::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t sprawdzenie::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef sprawdzenie_cxx
