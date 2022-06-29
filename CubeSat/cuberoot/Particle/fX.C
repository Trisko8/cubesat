void fX()
{
	TFile *input = new TFile("output.root", "READ");
	
	TTree *tree = (TTree*)input->Get("Particle");

    int entries = tree->GetEntries();

    double fX;

    tree->SetBranchAddress("fX", &fX);

    TH1F *histfX = new TH1F("histfX", "fX", 10, 25, 50);

    for(int i=0; i < entries; i++)
    {
        tree->GetEntry(i);
    
        histfX->Fill(fX);
    }
    tree->ResetBranchAddresses();

    histfX->GetXaxis()->SetTitle("x(mm)");
    histfX->GetYaxis()->SetTitle("Eventos");

    TF1 *fit = new TF1("fit", "gaus", 32, 48);

    TCanvas *c1 = new TCanvas();
    histfX->SetStats(0);
    histfX->Draw();
    histfX->Fit("fit", "R");
}
