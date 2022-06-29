void fY()
{
	TFile *input = new TFile("output.root", "READ");
	
	TTree *tree = (TTree*)input->Get("Particle");

    int entries = tree->GetEntries();

    double fY;

    tree->SetBranchAddress("fY", &fY);

    TH1F *histfY = new TH1F("histfY", "fY", 100, 60, 80);

    for(int i=0; i < entries; i++)
    {
        tree->GetEntry(i);
    
        histfY->Fill(fY);
    }
    tree->ResetBranchAddresses();

    histfY->GetXaxis()->SetTitle("y(mm)");
    histfY->GetYaxis()->SetTitle("Entradas");

    TF1 *fit = new TF1("fit", "gaus", 60, 80);

    TCanvas *c1 = new TCanvas();
    histfY->SetStats(0);
    histfY->Draw();
    histfY->Fit("fit", "R");

}
