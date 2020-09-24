void DppPPimPipPim()
{
  //TFile *out = new TFile("output_Dpp.root","recreate");
  //TH1F * histo1 = new TH1F ("histo1","#Delta^{++}; M^{inv}_{#Delta^{++}} " ,400,0,2);
  //TH1F * histo2 = new TH1F ("histo2","#Lambda #pi^{+} #pi^{-} invariant mass from #rho decay; M^{inv}_{#Lambda #pi^{+} #pi^{-}} " ,500,1,2);
  makeDistributionManager();
  //gSystem->CompileMacro("PHadesAcc.C");
  //makeDistributionManager()->Disable("helicity_angles");
  makeDistributionManager()->Exec("elementary");

  /*
  makeStaticData()->AddParticle(-1,"K0",0.497614);
  makeStaticData()->SetParticleMeson("K0");
  makeStaticData()->SetParticleTotalWidth("K0",0.05);

  makeStaticData()->AddParticle(-1,"K0bar",0.497614);
  makeStaticData()->SetParticleMeson("K0bar");
  makeStaticData()->SetParticleTotalWidth("K0bar",0.05);
  */

  //Int_t pid_lambda1502 = makeStaticData()->AddParticle(-1,"Lambda1520", 1.5195);
  //makeStaticData()->AddAlias("Lambda1520","Lambda(1520)");
  //makeStaticData()->SetParticleTotalWidth("Lambda1520", 0.0156);
  //makeStaticData()->SetParticleBaryon("Lambda1520", 1);
  //makeStaticData()->SetParticleSpin("Lambda1520", 3);
  //makeStaticData()->SetParticleParity("Lambda1520", 1);

  //makeStaticData()->AddDecay("Lambda(1520) -->  n + K0bar", "Lambda1520", "n, K0bar", 0.216);//EPJ A47 47F. Wielandet  al
  //makeStaticData()->AddDecay("Lambda(1520) -->  p + K-", "Lambda1520", "p, K-", 0.234);//EPJ A47 47F. Wielandet  al
  //cout<<"load n antiK0 and p K+ decay channels"<<endl;
  //makeStaticData()->AddDecay("Lambda(1520) -->  pi0 + Sigma", "Lambda1520", "pi0, Sigma0", 0.42);
  //makeStaticData()->AddDecay("Lambda(1520) -->  pi0 + pi0 + Sigma", "Lambda1520", "pi0, pi0, Sigma0", 0.009);
  //cout<<"load Sigma decay channel"<<endl;
  //makeStaticData()->AddDecay("Lambda(1520) -->  pi + pi + Lambda", "Lambda1520", "pi+, pi-, Lambda", 0.066);
  //makeStaticData()->AddDecay("Lambda(1520) -->  rho0 + Lambda", "Lambda1520", "rho0, Lambda", 0.066);
  cout<<"load pion decays channels"<<endl;
  //makeStaticData()->AddDecay("Lambda(1520) -->  gamma + Lambda", "Lambda1520", "g, Lambda", 0.0085);
  //makeStaticData()->AddDecay("Lambda(1520) -->  Lambda + dilepton", "Lambda1520", "Lambda, dilepton", 0.0085 / 137. );
  //cout<<"load all decay channels"<<endl;

  //makeStaticData()->AddDecay("Xi- -->  Lambda + pi", "Xi-", "Lambda, pi-", 1.);
  //newmodel = new PResonanceDalitz("Lambda1520_dalitz@Lambda1520_to_Lambda_dilepton","dgdm from Zetenyi/Wolf", -1);
  //newmodel->setGm(0.719);
  //makeDistributionManager()->Add(newmodel);

  /*                                                                                                                                                                                                        
  //============this block sets up the angular distribution of L1520 particle============                                                                                                                   
  PAngularDistribution *angL1520 = new PAngularDistribution("angL1520","angL1520 distribution");                                                                                                            
  TF1 *dNdOL1520 = new TF1("dNdOL1520","([0]*x*x+[1])/([0]+[1])",-1,1);                                                                                                                                     
  //TF1 *dNdOL1520_fake = new TF1("dNdOL1520","0",-1,1);                                                                                                                                                    
  dNdOL1520->SetParameters(2.57, 2.88);                                                                                                                                                                     
  angL1520->Add("q,parent,reference");                                                                                                                                                                      
  angL1520->Add("p,daughter");                                                                                                                                                                              
  angL1520->Add("K+,daughter");                                                                                                                                                                             
  angL1520->Add("Lambda1520,daughter,primary");                                                                                                                                                             
  angL1520->SetAngleFunction(dNdOL1520);                                                                                                                                                                    
  angL1520->Print();//TODO remove                                                                                                                                                                           
  angL1520->Draw();//TODO remove                                                                                                                                                                            
  makeDistributionManager()->Add(angL1520);                                                                                                                                                                 
                                                                                                                                                                                                            
  //=================================================================                                                                                                                                       
  */

  //proton beam has optimal properties at 5 GeV of kinetic energy. It corresponds to 5.86 GeV of momentum
  //PReaction my_reaction1("_T1=3.5","p","p","p K+ Lambda1520", "ppLam", 1, 0, 1, 1);
  //PReaction my_reaction1("_T1=3.5","p","p","p K+ Lambda1520 [pi+ pi- Lambda]", "ppLam", 0, 0, 1, 1);
  //out->cd();
  //PReaction my_reaction1("_T1=3.5","p","p","p K+ Lambda1520 [rho0 [pi+ pi-] Lambda]", "ppK+L1520", 0, 0, 1, 1);
  //PReaction my_reaction1("_T1=3.5","p","p","D++ [p pi+] pi+ pi- p pi-", "DppPPimPipPim", 0, 0, 1, 1);
  PReaction my_reaction1("_T1=3.5","p","p","p pi+ pi+ pi- p pi-", "PPipPPimPipPim", 0, 0, 1, 1);

  /*PDecayManager *pdm = new PDecayManager;
  pdm->SetVerbose(1);          // Print really useful info
  pdm->SetDefault("Lambda1520");
  PParticle *p = new PParticle("p",3.5);  // proton beam
  PParticle *t = new PParticle("p");      // proton target
  PParticle *s = new PParticle(*p +*t);  // composite quasiparticle

  c = new PDecayChannel;
  c->AddChannel(1,"p","K+","Lambda1520");
  
  pdm->InitReaction(s,c);
  pdm->loop(100000,0,"pK+L1520",0,0,1,1,1);
  */
  
  //my_reaction1.Do(histo1,"_p=[p];_pip=[pi+]; _x=(_p+_pip)->M();");
  //my_reaction1.Do(histo2,"_pip=[pi+]; _pim=[pi-]; _lambda=[Lambda]; q1=(_pip+_pim+_lambda); _x=(_pip+_pim+_lambda)->M();");
  
  //cout<<"II-cond reaction start"<<endl;
  //my_reaction2.Loop(10000);
  cout<<"I-st reaction start"<<endl;
  my_reaction1.Loop(200000);
  
  //out->cd();
  //histo1->Write();
  //histo2->Write();
  //out->Write();
  //out->Close();
}
