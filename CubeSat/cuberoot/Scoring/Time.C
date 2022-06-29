void Time()
{
	TFile *input = new TFile("output.root", "READ");
	
	TTree *tree = (TTree*)input->Get("Hits");

    int entries = tree->GetEntries();

    double Time;

    tree->SetBranchAddress("Time", &Time);

    TH1F *histTime = new TH1F("histTime", "Tiempo", 20, 0, 20);

    for(int i=0; i < entries; i++)
    {
        tree->GetEntry(i);
    
        histTime->Fill(Time);
    }
    tree->ResetBranchAddresses();

    histTime->GetXaxis()->SetTitle("t (ns)");
    histTime->GetYaxis()->SetTitle("Entradas");

    TF1 *fit = new TF1("fit", "pol9");

    TCanvas *c1 = new TCanvas();
    histTime->SetStats(0);
    histTime->Draw();
    histTime->Fit("fit");
}
