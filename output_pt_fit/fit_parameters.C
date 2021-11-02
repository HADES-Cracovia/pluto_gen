void rescaleHist1(TH1F* h,double scale=1, double shift=0)
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

double fit_parameters(char* name="L1520_thermal_T_0.125_Ek_0.600_pictures.root")
{
  double totalChi2;
  double L1116Chi2;
  double L1520Chi2;
  //open files
  cout<<"Load file: "<<name<<endl;
  TFile *fPluto=new TFile(name,"read");
  //TFile *fPluto=new TFile("sprawdzenie_output.root","read");
  //TFile *fExperiment=new TFile("./../../../PNB/FAT/PPIMPIPPIM/All_analysis/SB_experiment.root","read");
  TFile *fExperiment=new TFile("./../../../PNB/FAT/PPIMPIPPIM/All_analysis_temp_P_PIP/SB_experiment.root","read");

  //open histograms
  TH1F* h_pluto_L1116_pt=(TH1F*)fPluto->Get("hPtL1116");
  TH1F* h_pluto_L1116_w=(TH1F*)fPluto->Get("hYL1116");
  TH1F* h_pluto_L1520_pt=(TH1F*)fPluto->Get("hPtL1520");
  TH1F* h_pluto_L1520_w=(TH1F*)fPluto->Get("hYL1520");

  TH1F* h_exp_L1116_pt=(TH1F*)fExperiment->Get("hL1116_pt");
  TH1F* h_exp_L1116_w=(TH1F*)fExperiment->Get("hL1116_w");
  TH1F* h_exp_L1520_pt=(TH1F*)fExperiment->Get("hL1520_pt");
  TH1F* h_exp_L1520_w=(TH1F*)fExperiment->Get("hL1520_w");

  TH1F* h_exp_L1116_pt_SB=(TH1F*)fExperiment->Get("hL1116_pt_SB");
  TH1F* h_exp_L1116_w_SB=(TH1F*)fExperiment->Get("hL1116_w_SB");
  TH1F* h_exp_L1520_pt_SB=(TH1F*)fExperiment->Get("hL1520_pt_SB");
  TH1F* h_exp_L1520_w_SB=(TH1F*)fExperiment->Get("hL1520_w_SB");

  
  //substract SB
  h_exp_L1116_pt->Add(h_exp_L1116_pt_SB,-1);
  h_exp_L1116_w->Add(h_exp_L1116_w_SB,-1);
  h_exp_L1520_pt->Add(h_exp_L1520_pt_SB,-1);
  h_exp_L1520_w->Add(h_exp_L1520_w_SB,-1);

  //set PLUTO in MeV
  rescaleHist1(h_pluto_L1116_pt,1000);
  rescaleHist1(h_pluto_L1520_pt,1000);
  
  //normalize pluto to experiment
  h_pluto_L1116_pt->Scale(h_exp_L1116_pt->Integral()/h_pluto_L1116_pt->Integral());
  h_pluto_L1116_w->Scale(h_exp_L1116_w->Integral()/h_pluto_L1116_w->Integral());
  h_pluto_L1520_pt->Scale(h_exp_L1520_pt->Integral()/h_pluto_L1520_pt->Integral());
  h_pluto_L1520_w->Scale(h_exp_L1520_w->Integral()/h_pluto_L1520_w->Integral());

  L1520Chi2=1.0/2.0*(h_pluto_L1520_pt->Chi2Test(h_exp_L1520_pt,"CHI2/NDF")+h_pluto_L1520_w->Chi2Test(h_exp_L1520_w,"CHI2/NDF"));
  L1116Chi2=1.0/2.0*(h_pluto_L1116_pt->Chi2Test(h_exp_L1116_pt,"CHI2/NDF")+h_pluto_L1116_w->Chi2Test(h_exp_L1116_w,"CHI2/NDF"));
  totalChi2=1.0/2.0*(L1520Chi2+L1116Chi2);

  cout<<"Chi2 L1520: "<<L1520Chi2<<" Chi2 L1116: "<<L1116Chi2<<endl<<"Total Chi2:"<<totalChi2<<endl;
  //draw the results

  //TFile *out=new TFile("fit_parameters_output.root","recreate");
  
  TCanvas *cL1520=new TCanvas("cL1520","cL1520");
  cL1520->Divide(2);
  cL1520->cd(1);
  h_exp_L1520_pt->Draw();
  h_pluto_L1520_pt->Draw("same");
  h_pluto_L1520_pt->SetLineColor(kRed);
  
  cL1520->cd(2);
  h_exp_L1520_w->Draw();
  h_pluto_L1520_w->Draw("same");
  h_pluto_L1520_w->SetLineColor(kRed);
  h_exp_L1520_w->Draw("same");

  TCanvas *cL1116=new TCanvas("cL1116","cL1116");
  cL1116->Divide(2);
  cL1116->cd(1);
  h_exp_L1116_pt->Draw();
  h_pluto_L1116_pt->Draw("same");
  h_pluto_L1116_pt->SetLineColor(kRed);
  
  cL1116->cd(2);
  h_exp_L1116_w->Draw();
  h_pluto_L1116_w->Draw("same");
  h_pluto_L1116_w->SetLineColor(kRed);
  

  
  //delete fPluto;
  //delete fExperiment;
  //prepare output
  //static
  
  return totalChi2;
}










