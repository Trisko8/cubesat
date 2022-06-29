void fEdep()
{
	TFile *input = new TFile("output.root", "READ");
	
	TTree *tree = (TTree*)input->Get("Scoring");

    int entries = tree->GetEntries();

    double fEdep;

    tree->SetBranchAddress("fEdep", &fEdep);

    TH1F *histfEdep = new TH1F("histfEdep", "Energia depositada", 100, 0, 300);

    for(int i=0; i < entries; i++)
    {
        tree->GetEntry(i);
    
        histfEdep->Fill(fEdep);
    }
    tree->ResetBranchAddresses();

    histfEdep->GetXaxis()->SetTitle("Energia (MeV)");
    histfEdep->GetYaxis()->SetTitle("Entradas");

    TCanvas *c1 = new TCanvas();
    histfEdep->SetStats(0);
    histfEdep->Draw();
}
