void MakeGraph() {
  const int number_of_graphs = 21;
  TGraph *g[number_of_graphs];
  TCanvas *c = new TCanvas("c", "c");
  for(int igraph = 0; igraph < number_of_graphs; igraph++) {
    Int_t number_of_cells = 600 +  igraph * 60;
    TString filename = Form("../data/electric_field_3_%d.txt", number_of_cells);
    g[igraph] = new TGraph(filename);
    g[igraph]->SetMarkerColor(igraph);
    if (igraph == 0) {
      g[igraph]->Draw("A*");
      g[igraph]->GetYaxis()->SetRangeUser(0., 2e5);
      g[igraph]->SetTitle("ElectricField;z[mm];E_x[V/mm]");
    }
    else
      g[igraph]->Draw("SAME*");
  }
  c->Update();
}
