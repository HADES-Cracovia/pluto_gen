// -------------------------------------------------
// Thermal source of delta's with only Dalitz decays
// -------------------------------------------------

void thermal_Delta_pee()
{
  //gSystem->Load("/cvmfs/hades.gsi.de/install/5.34.01/pluto/v5_37/libPluto.so");

  /*
  makeStaticData()->AddParticle(90,"K0",0.497614);
  makeStaticData()->SetParticleMeson("K0");
  makeStaticData()->SetParticleTotalWidth("K0",0.05);

  makeStaticData()->AddParticle(91,"K0bar",0.497614);
  makeStaticData()->SetParticleMeson("K0bar");
  makeStaticData()->SetParticleTotalWidth("K0bar",0.05);
  */

  Int_t pid_lambda1502 = makeStaticData()->AddParticle(92,"Lambda1520", 1.5195);
  makeStaticData()->AddAlias("Lambda1520","Lambda(1520)");
  makeStaticData()->SetParticleTotalWidth("Lambda1520", 0.0156);
  makeStaticData()->SetParticleBaryon("Lambda1520", 1);
  makeStaticData()->SetParticleSpin("Lambda1520", 3);
  makeStaticData()->SetParticleParity("Lambda1520", 1);
  
  //makeStaticData()->AddDecay("Lambda(1520) -->  n + K0bar", "Lambda1520", "n, K0bar", 0.45);
  //makeStaticData()->AddDecay("Lambda(1520) -->  pi + Sigma", "Lambda1520", "pi0, Sigma0", 0.42);
  //makeStaticData()->AddDecay("Lambda(1520) -->  pi + pi + Lambda", "Lambda1520", "pi0, pi0, Lambda", 0.033);
  makeStaticData()->AddDecay("Lambda(1520) -->  pi+ + pi- + Lambda", "Lambda1520", "pi+, pi-, Lambda", 0.066);
  //makeStaticData()->AddDecay("Lambda(1520) -->  pi + pi + Sigma", "Lambda1520", "pi0, pi0, Sigma0", 0.009);
  //makeStaticData()->AddDecay("Lambda(1520) -->  gamma + Lambda", "Lambda1520", "g, Lambda", 0.0085);
  //makeStaticData()->AddDecay("Lambda(1520) -->  Lambda + dilepton", "Lambda1520", "Lambda, dilepton", 0.0085 / 137. );
    
  /*
  //makeStaticData()->AddDecay("Xi- -->  Lambda + pi", "Xi-", "Lambda, pi-", 1.);
  newmodel = new PResonanceDalitz("Lambda1520_dalitz@Lambda1520_to_Lambda_dilepton","dgdm from Zetenyi/Wolf", -1);
  newmodel->setGm(0.719);
  makeDistributionManager()->Add(newmodel);    
  */
  cout<<"Load all new data succesfully!!!"<<endl;
  
  int nparts = 1;
  for (int ipart = 0; ipart < nparts; ++ipart)
    {
      cout<<"Begining of a part no. "<<ipart<<endl;
      Int_t nEvents = 100000;

      Float_t Eb    = 3.5;  // beam energy in GeV/u
      Float_t T     = 0.090;  // temperature in GeV
      Float_t blast = 0.0;   // radial expansion velocity

      PFireball *source = new PFireball("Lambda(1520)",Eb,T,0,1,blast,0,0,0,0);
      //source->setRandomB(1,93);//projectal mass, target mass, probability of interaction
      source->setTrueThermal(kTRUE);
      source->Print();

      PParticle *Ls=new PParticle("Lambda(1520)");
      PParticle *s[]={source,Ls};

      PChannel  *c1=new PChannel(s,1,1,1);
      PParticle *pip = new PParticle("pi+");
      PParticle *pim = new PParticle("pi-");
      PParticle *Lz = new PParticle("Lambda");
      c1->Print();
      
      PParticle *pidecay[] = {Ls,pip,pim,Lz};

      PChannel *c2 = new PChannel(pidecay,3,1,1);
      c2->Print();

      cout<<endl<<"Print all channels"<<endl<<endl;
      PChannel  *cc[]={c1,c2};
      cc[0]->Print();
      cc[1]->Print();
      
      PReaction *r=new PReaction(cc,"output.root",2,0,0,0,1); // three particles in the final state
      r->Print();
      
      r->setHGeant(0);   // set to 1, if PLUTO run from HGeant prompt
      r->Loop(nEvents);
    }
}
