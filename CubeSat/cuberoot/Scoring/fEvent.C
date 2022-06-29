void fEvent()
{
	TFile *input = new TFile("output.root", "READ");
	
	TTree *tree = (TTree*)input->Get("Hits");

    int entries = tree->GetEntries();

    int fEvent;

    tree->SetBranchAddress("fEvent", &fEvent);

    TH1F *histfEvent = new TH1F("histfEvent", "Eventos simulados", 50, 0, 50);

    for(int i=0; i < entries; i++)
    {
        tree->GetEntry(i);
    
        histfEvent->Fill(fEvent);
    }
    tree->ResetBranchAddresses();

    histfEvent->GetXaxis()->SetTitle("Eventos");
    histfEvent->GetYaxis()->SetTitle("Entradas");

    TCanvas *c1 = new TCanvas();
    histfEvent->SetStats(0);
    histfEvent->Draw();
}
