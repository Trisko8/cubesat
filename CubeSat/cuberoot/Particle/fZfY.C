void fZfY()
{
	TFile *input = new TFile("output.root", "READ");
	
	TTree *tree = (TTree*)input->Get("Particle");

    int entries = tree->GetEntries();

    double fY, fZ;

    tree->SetBranchAddress("fY", &fY);
    tree->SetBranchAddress("fZ", &fZ);

    TH2F *histfZfY = new TH2F("histfZfY","fZ-fY", 100, -90, 90, 100, -50, 50);

    for(int i=0; i < entries; i++)
    {
        tree->GetEntry(i);
    
        histfZfY->Fill(fY, fZ);
    }
    tree->ResetBranchAddresses();

    histfZfY->GetXaxis()->SetTitle("y (mm)");
    histfZfY->GetYaxis()->SetTitle("z (mm)");
    histfZfY->GetZaxis()->SetTitle("Entradas");

    TCanvas *c1 = new TCanvas();
    histfZfY->SetStats(0);
    histfZfY->Draw("CONT4Z");
}
