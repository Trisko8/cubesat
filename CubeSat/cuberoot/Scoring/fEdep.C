void fEdep()
{
	TFile *input = new TFile("output.root", "READ");
	
	TTree *tree = (TTree*)input->Get("Scoring");

    int entries = tree->GetEntries();

    double fEdep;

    tree->SetBranchAddress("fEdep", &fEdep);

    TH1F *histfEdep = new TH1F("histfEdep", "Energia depositada", 200, 20, 1000);

    for(int i=0; i < entries; i++)
    {
        tree->GetEntry(i);
    
        histfEdep->Fill(fEdep);
    }
    tree->ResetBranchAddresses();

    histfEdep->GetXaxis()->SetTitle("Energia (keV)");
    histfEdep->GetYaxis()->SetTitle("Entradas");

    TF1 *fit = new TF1("fit", "pol4", 20, 660);

    TCanvas *c1 = new TCanvas();
    histfEdep->SetStats(0);
    histfEdep->Draw();
    histfEdep->SetAxisRange(0., 40.,"Y");
    histfEdep->Fit("fit", "R");
}
