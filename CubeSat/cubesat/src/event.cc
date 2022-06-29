#include "event.hh"

MyEventAction::MyEventAction(MyRunAction*)
{}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{}

void MyEventAction::EndOfEventAction(const G4Event*)
{
    G4cout << "Energy deposition: " << fEdep/MeV << " MeV" << G4endl;
    G4cout << "Number of photons: " << abs(fcount) << G4endl;
    G4cout << "Time: " << ftime/s << " s" << G4endl;
    G4cout << "N/Edep: " << abs(fcount)/fEdep << " foton/MeV" << G4endl;

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->FillNtupleDColumn(2, 0, fEdep/MeV);
    man->FillNtupleDColumn(2, 1, abs(fcount));
    man->AddNtupleRow(2);
}
