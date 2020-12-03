// -------------------------------------------------
// Thermal source of delta's with only Dalitz decays
// -------------------------------------------------

void thermal_L1520()
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

  Int_t pid_newResonanse=makeStaticData()->AddParticle(99,"Temp",2.4);
  makeStaticData()->SetParticleTotalWidth("Temp",0.12);
  makeStaticData()->SetParticleBaryon("Temp",1);
  makeStaticData()->AddAlias("Temp","temp");
  
  //makeStaticData()->AddDecay("Lambda(1520) -->  n + K0bar", "Lambda1520", "n, K0bar", 0.45);
  //makeStaticData()->AddDecay("Lambda(1520) -->  pi + Sigma", "Lambda1520", "pi0, Sigma0", 0.42);
  //makeStaticData()->AddDecay("Lambda(1520) -->  pi + pi + Lambda", "Lambda1520", "pi0, pi0, Lambda", 0.033);
  makeStaticData()->AddDecay("Lambda(1520) -->  pi+ + pi- + Lambda", "Lambda1520", "pi+, pi-, Lambda", 0.066);
  //makeStaticData()->AddDecay("Lambda(1520) -->  pi + pi + Sigma", "Lambda1520", "pi0, pi0, Sigma0", 0.009);
  //makeStaticData()->AddDecay("Lambda(1520) -->  gamma + Lambda", "Lambda1520", "g, Lambda", 0.0085);
  //makeStaticData()->AddDecay("Lambda(1520) -->  Lambda + dilepton", "Lambda1520", "Lambda, dilepton", 0.0085 / 137. );

  //makeStaticData()->AddDecay("Temp-->Lambda(1520) + K0S","Temp","Lambda1520, K0S",1);
  /*
  //makeStaticData()->AddDecay("Xi- -->  Lambda + pi", "Xi-", "Lambda, pi-", 1.);
  newmodel = new PResonanceDalitz("Lambda1520_dalitz@Lambda1520_to_Lambda_dilepton","dgdm from Zetenyi/Wolf", -1);
  newmodel->setGm(0.719);
  makeDistributionManager()->Add(newmodel);    
  */
  cout<<"Load all new data succesfully!!!"<<endl;
  
  int nparts = 100;
  for (int ipart = 0; ipart < nparts; ++ipart)
    {
      int nEvents=10000;
      //Float_t Eb    = 3.5;  // beam energy in GeV/u
      Float_t Eb    = 0.8;
      //Float_t T     = 0.090;  // temperature in GeV
      Float_t T     = 0.04+(double)ipart/(double)nparts*0.1;  // temperature in GeV
      Float_t blast = 0.0;   // radial expansion velocity

      PFireball *source = new PFireball("Lambda(1520)",Eb,T,0,1,blast,0,0,0,0);
      
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
      
      //PReaction *r=new PReaction(cc,Form("./output_L1520/L1520_thermal_%i",ipart),,0,0,0,1); // three particles in the final state
      PReaction *r=new PReaction(cc,Form("./output_pt_fit/L1520_thermal_T_%.3f",T),2,0,0,0,1); // three particles in the final state
     
      r->Print();
      
      r->setHGeant(0);   // set to 1, if PLUTO run from HGeant prompt
      cout<<"Poczatek petli "<<ipart+1<<endl;
      r->Loop(nEvents);
    }
  cout<<"koniec programu"<<endl;
}
