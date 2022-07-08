#include "event.hh"

MyEventAction::MyEventAction(MyRunAction*)
{}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
    fEdep=0.;
    ftime=0.;
    fcount=0.;
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
    G4cout << "Energy deposition: " << fEdep/MeV << " MeV" << G4endl;
    G4cout << "Number of photons: " << abs(fcount) << G4endl;
    G4cout << "Time: " << ftime/s << " s" << G4endl;

    G4AnalysisManager *man = G4AnalysisManager::Instance();
}
