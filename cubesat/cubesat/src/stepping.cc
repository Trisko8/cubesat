#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
    fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
    G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

    const MyDetectorConstruction *ScintillatorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

    G4LogicalVolume *fScoringVolume = ScintillatorConstruction->GetScoringVolume();

    if(volume != fScoringVolume)
        return;

const G4String particleName
= step->GetTrack()->GetDefinition()->GetParticleName();
	if (particleName == "opticalphoton"){
    counter++;
    fEventAction->AddCounter(counter);
    }

    G4double edep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edep);
}
