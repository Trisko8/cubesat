#include "event.hh"

MyEventAction::MyEventAction(MyRunAction*)
{}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{}

void MyEventAction::EndOfEventAction(const G4Event*)
{
    G4cout << "Energy deposition: " << fEdep/MeV << G4endl;
    G4cout << "Dose: " << fdose << G4endl;
    G4cout << "Number of photons: " << abs(fcount) << G4endl;
    
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->FillNtupleDColumn(2, 1, fEdep);
    man->FillNtupleDColumn(2, 2, fdose);
    man->FillNtupleDColumn(2, 3, abs(fcount));
    man->AddNtupleRow(2);
}
