void xyz()
{
	TFile *input = new TFile("output.root", "READ");
	
	TTree *tree = (TTree*)input->Get("Particle");

    int entries = tree->GetEntries();

    double fX, fY, fZ;

    tree->SetBranchAddress("fX", &fX);
    tree->SetBranchAddress("fY", &fY);
    tree->SetBranchAddress("fZ", &fZ);

    TH3D *xyz = new TH3D("xyz","xyz",100,-50.,50.,100,-50,50,100,-50,50);

    for(int i=0; i < entries; i++)
    {
        tree->GetEntry(i);
    
        xyz->Fill(fX, fY, fZ);
    }

    Int_t nx = xyz->GetNbinsX();
    Int_t ny = xyz->GetNbinsY();
    Int_t nz = xyz->GetNbinsZ();

    tree->ResetBranchAddresses();

    xyz->GetXaxis()->SetTitle("x (mm)");
    xyz->GetYaxis()->SetTitle("y (mm)");
    xyz->GetZaxis()->SetTitle("z (mm)");
    xyz->GetXaxis()->SetLabelOffset(999);
    xyz->GetXaxis()->SetLabelSize(0);
    xyz->GetYaxis()->SetLabelOffset(999);
    xyz->GetYaxis()->SetLabelSize(0);
    xyz->Draw("LEGO2 Z FB BB");
}
