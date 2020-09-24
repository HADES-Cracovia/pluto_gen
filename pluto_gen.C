{
  /*  makeDistributionManager();
  gSystem->CompileMacro("PHadesAcc.C");
  makeDistributionManager()->Disable("helicity_angles");
  makeDistributionManager()->Exec("elementary");

  */

  makeStaticData()->AddParticle(-1,"K0",0.497614);
  makeStaticData()->SetParticleMeson("K0");
  makeStaticData()->SetParticleTotalWidth("K0",0.05);

  makeStaticData()->AddParticle(-1,"K0bar",0.497614);
  makeStaticData()->SetParticleMeson("K0bar");
  makeStaticData()->SetParticleTotalWidth("K0bar",0.05);


  Int_t pid_lambda1502 = makeStaticData()->AddParticle(-1,"Lambda1520", 1.5195);
  makeStaticData()->AddAlias("Lambda1520","Lambda(1520)");
  makeStaticData()->SetParticleTotalWidth("Lambda1520", 0.0156);
  makeStaticData()->SetParticleBaryon("Lambda1520", 1);
  makeStaticData()->SetParticleSpin("Lambda1520", 3);
  makeStaticData()->SetParticleParity("Lambda1520", 1);

  makeStaticData()->AddDecay("Lambda(1520) -->  n + K0bar", "Lambda1520", "n, K0bar", 0.45);
  makeStaticData()->AddDecay("Lambda(1520) -->  pi + Sigma", "Lambda1520", "pi0, Sigma0", 0.42);
  makeStaticData()->AddDecay("Lambda(1520) -->  pi + pi + Lambda", "Lambda1520", "pi0, pi0, Lambda", 0.033);
  makeStaticData()->AddDecay("Lambda(1520) -->  pi + pi + Lambda", "Lambda1520", "pi+, pi-, Lambda", 0.066);
  makeStaticData()->AddDecay("Lambda(1520) -->  pi + pi + Sigma", "Lambda1520", "pi0, pi0, Sigma0", 0.009);
  makeStaticData()->AddDecay("Lambda(1520) -->  gamma + Lambda", "Lambda1520", "g, Lambda", 0.0085);
  makeStaticData()->AddDecay("Lambda(1520) -->  Lambda + dilepton", "Lambda1520", "Lambda, dilepton", 0.0085 / 137. );
  //makeStaticData()->AddDecay("Xi- -->  Lambda + pi", "Xi-", "Lambda, pi-", 1.);
  newmodel = new PResonanceDalitz("Lambda1520_dalitz@Lambda1520_to_Lambda_dilepton","dgdm from Zetenyi/Wolf", -1);
  newmodel->setGm(0.719);
  makeDistributionManager()->Add(newmodel);

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
  PReaction my_reaction1("_T1=3.5","p","p","p K+ Lambda1520", "ppLam", 1, 0, 1, 1);

  my_reaction1.Loop(100);
}
