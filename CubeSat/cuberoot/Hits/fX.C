void fX()
{
	TFile *input = new TFile("output.root", "READ");
	
	TTree *tree = (TTree*)input->Get("Hits");

    int entries = tree->GetEntries();

    double fX;

    tree->SetBranchAddress("fX", &fX);

    TH1F *histfX = new TH1F("histfX", "fX", 100, -50, 50);

    for(int i=0; i < entries; i++)
    {
        tree->GetEntry(i);
    
        histfX->Fill(fX);
    }
    tree->ResetBranchAddresses();

    histfX->GetXaxis()->SetTitle("x(mm)");
    histfX->GetYaxis()->SetTitle("Entradas");

    TCanvas *c1 = new TCanvas();
    histfX->SetStats(0);
    histfX->Draw();
}
