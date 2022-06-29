void fZ()
{
	TFile *input = new TFile("output.root", "READ");
	
	TTree *tree = (TTree*)input->Get("Particle");

    int entries = tree->GetEntries();

    double fZ;

    tree->SetBranchAddress("fZ", &fZ);

    TH1F *histfZ = new TH1F("histfZ", "fZ", 100, -50, 0);

    for(int i=0; i < entries; i++)
    {
        tree->GetEntry(i);

        histfZ->Fill(fZ);
    }
    tree->ResetBranchAddresses();

    histfZ->GetXaxis()->SetTitle("z(mm)");
    histfZ->GetYaxis()->SetTitle("Entradas");

    TF1 *fit = new TF1("fit", "gaus", -31, -48);

    TCanvas *c1 = new TCanvas();
    histfZ->SetStats(0);
    histfZ->Draw();
    histfZ->Fit("fit", "R");
}
