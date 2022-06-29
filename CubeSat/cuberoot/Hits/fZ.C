void fZ()
{
	TFile *input = new TFile("output.root", "READ");
	
	TTree *tree = (TTree*)input->Get("Hits");

    int entries = tree->GetEntries();

    double fZ;

    tree->SetBranchAddress("fZ", &fZ);

    TH1F *histfZ = new TH1F("histfZ", "fZ", 100, -50, 50);

    for(int i=0; i < entries; i++)
    {
        tree->GetEntry(i);

        histfZ->Fill(fZ);
    }
    tree->ResetBranchAddresses();

    histfZ->GetXaxis()->SetTitle("z(mm)");
    histfZ->GetYaxis()->SetTitle("Entradas");

    TCanvas *c1 = new TCanvas();
    histfZ->SetStats(0);
    histfZ->Draw();
}
