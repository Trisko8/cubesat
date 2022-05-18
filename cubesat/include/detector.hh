#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

#include "g4root.hh"

#include "run.hh"

class MySensitiveDetector : public G4VSensitiveDetector
{
public:
    MySensitiveDetector(G4String);
    ~MySensitiveDetector();

    void AddEdep(G4double edep) {Edep += edep;} 

private:
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);

    G4double Edep;
};

#endif
