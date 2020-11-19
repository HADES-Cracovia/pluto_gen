int run_all(void)
{
  gROOT->ProcessLine(".x thermal_Delta_pee.C");

  gROOT->ProcessLine(".x sprawdzenie.C");
  gROOT->ProcessLine("sprawdzenie l");
  gROOT->ProcessLine("l.Loop()");
}
