#include "detector.hh"


MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();

    //Getting exact position of the particle
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector posParticle = preStepPoint->GetPosition();

    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
    
    //Getting position of the particle regarding to the Scintillator
    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posScintillator = physVol->GetTranslation();

    //Getting current event
    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    //Declaración de los valores de las tuplas para el output
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->FillNtupleIColumn(2, 0, evt);
    man->AddNtupleRow(2);

    man->FillNtupleIColumn(0, 0, evt);
    man->FillNtupleDColumn(0, 1, posParticle[0]);
    man->FillNtupleDColumn(0, 2, posParticle[1]);
    man->FillNtupleDColumn(0, 3, posParticle[2]);
    man->AddNtupleRow(0);

    man->FillNtupleIColumn(1, 0, evt);
    man->FillNtupleDColumn(1, 1, posScintillator[0]);
    man->FillNtupleDColumn(1, 2, posScintillator[1]);
    man->FillNtupleDColumn(1, 3, posScintillator[2]);
    man->AddNtupleRow(1);

    return true;
}
