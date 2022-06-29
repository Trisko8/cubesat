void fCount()
{
	TFile *input = new TFile("output.root", "READ");
	
	TTree *tree = (TTree*)input->Get("Scoring");

    int entries = tree->GetEntries();

    double fCount;

    tree->SetBranchAddress("fCount", &fCount);

    TH1F *histfCount = new TH1F("histfCount", "Centelleo", 100, 0, 2300000000);

    for(int i=0; i < entries; i++)
    {
        tree->GetEntry(i);
    
        histfCount->Fill(fCount);
    }
    tree->ResetBranchAddresses();

    histfCount->GetXaxis()->SetTitle("Numero de fotones");
    histfCount->GetYaxis()->SetTitle("Numero de eventos");

    TCanvas *c1 = new TCanvas();
    histfCount->SetStats(0);
    histfCount->Draw();
}
