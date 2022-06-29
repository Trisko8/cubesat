void Wavelength()
{
	TFile *input = new TFile("output.root", "READ");
	
	TTree *tree = (TTree*)input->Get("Hits");

    int entries = tree->GetEntries();

    double Wavelength;

    tree->SetBranchAddress("Wavelength", &Wavelength);

    TH1F *histWavelength = new TH1F("histWavelength", "Longitud de onda", 600, 0, 600);

    for(int i=0; i < entries; i++)
    {
        tree->GetEntry(i);
    
        histWavelength->Fill(Wavelength);
    }
    tree->ResetBranchAddresses();

    histWavelength->GetXaxis()->SetTitle("Longitud de onda (nm)");
    histWavelength->GetYaxis()->SetTitle("Entradas");

    TF1 *fit = new TF1("fit", "gaus");

    TCanvas *c1 = new TCanvas();
    histWavelength->SetStats(0);
    histWavelength->Draw();
    histWavelength->Fit("fit");
}
