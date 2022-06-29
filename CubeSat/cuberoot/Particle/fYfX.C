void fYfX()
{
	TFile *input = new TFile("output.root", "READ");
	
	TTree *tree = (TTree*)input->Get("Particle");

    int entries = tree->GetEntries();

    double fX, fY;

    tree->SetBranchAddress("fX", &fX);
    tree->SetBranchAddress("fY", &fY);

    TH2F *histfYfX = new TH2F("histfYfX","fY-fX", 100, -50, 50, 100, -90, 90);

    for(int i=0; i < entries; i++)
    {
        tree->GetEntry(i);
    
        histfYfX->Fill(fX, fY);
    }
    tree->ResetBranchAddresses();

    histfYfX->GetXaxis()->SetTitle("x (mm)");
    histfYfX->GetYaxis()->SetTitle("y (mm)");
    histfYfX->GetZaxis()->SetTitle("Entradas");

    TCanvas *c1 = new TCanvas();
    histfYfX->SetStats(0);
    histfYfX->Draw("CONT4Z");
}
