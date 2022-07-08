#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

     G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }

    virtual G4VPhysicalVolume *Construct();

private:
    G4Box *solidWorld, *solidScintillator;
    G4LogicalVolume *logicWorld, *logicScintillator;
    G4VPhysicalVolume *physWorld, *physScintillator;

    G4Material *worldMat, *ScintillatorMat;

    void DefineMaterials();

    void ConstructScintillator();

    virtual void ConstructSDandField();

    G4LogicalVolume *fScoringVolume;

    G4double xWorld, yWorld, zWorld;

    G4OpticalSurface *BC_620;
};

#endif
