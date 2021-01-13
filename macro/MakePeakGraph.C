void MakePeakGraph() {

  ifstream ifs("../data/electric_field_3_peak.txt");
  const Int_t ngraph = 26;
  Double_t cell, field;
  Double_t x[ngraph] = {}, y[ngraph] = {};
  
  for (Int_t igraph = 0; igraph < ngraph; igraph++) {
    ifs >> cell >> field;
    x[igraph] = 1./cell; y[igraph] = field;
  }

  TGraph *g = new TGraph(ngraph, x, y);
  g->SetMarkerStyle(21);
  g->SetTitle("Electric Field;1/cell;E[V/mm]");
  g->Draw("AP");

  TF1 * f = new TF1("f", "[0] + [1] * x");
  g->Fit(f);
  
}
