#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();

    //Getting exact position of the photons
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector posParticle = preStepPoint->GetPosition();

    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

    //Photon wavelength
const G4String particleName = aStep->GetTrack()->GetDefinition()->GetParticleName();
	if (particleName == "opticalphoton"){
    G4ThreeVector momPhoton = preStepPoint->GetMomentum();
    wlen = (1.239841939*eV/momPhoton.mag())*1E+03;
    }

    //Getting current event
    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    //Time
    G4double time = preStepPoint->GetGlobalTime();
    
    //Declaración de los valores de las tuplas para el output
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->FillNtupleIColumn(0, 0, evt);
    man->FillNtupleDColumn(0, 1, posParticle[0]);
    man->FillNtupleDColumn(0, 2, posParticle[1]);
    man->FillNtupleDColumn(0, 3, posParticle[2]);
    man->FillNtupleDColumn(0, 4, time);
    man->FillNtupleDColumn(0, 5, wlen);
    man->AddNtupleRow(0);

    return true;
}
