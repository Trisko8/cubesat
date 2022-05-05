#include "detector.hh"


MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{

    G4Track *track = aStep->GetTrack();

//    track->SetTrackStatus(fStopAndKill);

    //Getting exact position of the particle
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector posParticle = preStepPoint->GetPosition();

    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

    //Getting copy number
    G4int copyNo = touchable->GetCopyNumber();

    //G4cout << "Copy Number: " << copyNo << G4endl;
    
    //Getting position of the particle regarding to the Scintillator
    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posScintillator = physVol->GetTranslation();

    //G4cout << "Scintillator position: " << posScintillator << G4endl;

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    //Getting angular positions of the particle regarding to the Scintillator
//    G4ThreeVector up_vector = 
//    G4ThreeVector bottom_vector = 
//    G4Double u = up_vector[0] - bottom_vector[0];
//    G4Double v = up_vector[1] - bottom_vector[1];
//    G4Double w = up_vector[2] - bottom_vector[2];
//    G4Double theta = arctan(w/v);
//    G4Double phi = arctan(u/v);
    
    //Declaración de los valores de las tuplas para el output
    man->FillNtupleIColumn(0, 0, evt);
    man->FillNtupleDColumn(0, 1, posParticle[0]);
    man->FillNtupleDColumn(0, 2, posParticle[1]);
    man->FillNtupleDColumn(0, 3, posParticle[2]);
    man->AddNtupleRow(0);

    man->FillNtupleIColumn(1, 0, evt);
    man->FillNtupleDColumn(1, 1, posScintillator[0]);
    man->FillNtupleDColumn(1, 2, posScintillator[1]);
    man->FillNtupleDColumn(1, 3, posScintillator[2]);
//    man->FillNtupleDColumn(1, 4, theta);
//    man->FillNtupleDColumn(1, 5, phi);
    man->AddNtupleRow(1);

    return true;
}
