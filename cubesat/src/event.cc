#include "event.hh"

MyEventAction::MyEventAction(MyRunAction*)
{
    fEdep = 0.;
    fdelta=0.;
}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
    fEdep = 0.;
    fdelta=0.;
	nAbsPhotons = 0.;
    absTime=0.;
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
    G4cout << "Energy deposition: " << fEdep << G4endl;
    G4cout << "Delta: " << fdelta << G4endl;

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->FillNtupleDColumn(2, 1, fEdep);
    man->FillNtupleDColumn(2, 2, nAbsPhotons);
    man->FillNtupleDColumn(2, 3, absTime);
    man->FillNtupleDColumn(2, 4, fdelta);
    man->AddNtupleRow(2);
}
