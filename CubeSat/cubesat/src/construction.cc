#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{ 
    DefineMaterials();

    xWorld = 0.25*m;
    yWorld = 0.25*m;
    zWorld = 0.25*m;
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterials()
{
    G4NistManager *nist = G4NistManager::Instance();
    
    //World Material
    G4double density = 1e-10 *g/cm3;
    G4Element* N = new G4Element("Nitrogen", "N", 7., 14.01*g/mole);
    G4Element* O = new G4Element("Oxygen", "O", 8., 16.00*g/mole);

    worldMat = new G4Material("worldMat", density, 2);
    worldMat->AddElement(N, 70.0*perCent);
    worldMat->AddElement(O, 30.0*perCent);

    //Scintillator Material
    ScintillatorMat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");

    G4double energy[12] = {3.44*eV, 3.26*eV, 3.1*eV, 3.02*eV, 2.95*eV, 2.92*eV, 2.82*eV, 2.76*eV, 2.7*eV, 2.58*eV, 2.38*eV, 2.08*eV};

    G4MaterialPropertiesTable *mptScintillator = new G4MaterialPropertiesTable();

    G4double rindex[12] = {1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58};
    mptScintillator->AddProperty("RINDEX", energy, rindex, 12);

    G4double absorption[12] = {380*cm, 380*cm, 380*cm, 380*cm, 380*cm, 380*cm, 380*cm, 380*cm, 380*cm, 380*cm, 380*cm, 380*cm};

    G4double scintillation[12] = {0.04, 0.07, 0.20, 0.49, 0.84, 1.00, 0.83, 0.55, 0.40, 0.17, 0.03, 0};

    mptScintillator->AddProperty("FASTCOMPONENT", energy, scintillation, 12); //Photons for each wavelength intervalue
    mptScintillator->AddProperty("ABSLENGTH", energy, absorption, 12); 
    mptScintillator->AddConstProperty("SCINTILLATIONYIELD", 12800./MeV); //Photons per energy loss of the particle created
    mptScintillator->AddConstProperty("FASTTIMECONSTANT", 2.1*ns); //Decay time of the scintillation
    //mptScintillator->AddConstProperty("SLOWTIMECONSTANT",1.*ns);
    mptScintillator->AddConstProperty("RESOLUTIONSCALE", 1.); 
    mptScintillator->AddConstProperty("YIELDRATIO", 1.); //Distribution of the photons (sigma value)


    ScintillatorMat->SetMaterialPropertiesTable(mptScintillator);

    ScintillatorMat->GetIonisation()->SetBirksConstant(0.126 * mm / MeV); //Saturation of signal in sensitive detector in dense ionisation

    //Envelope Material
    Al_6061 = new G4Material("Al_6061", 2.7*g/cm3, 1);
    Al_6061->AddElement(nist->FindOrBuildElement("Al"), 1);

    //Mirror Material
    BC_620 = new G4OpticalSurface("BC_620");

    BC_620->SetType(dielectric_metal);
    BC_620->SetFinish(ground);
    BC_620->SetModel(unified);

    G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();
    G4double reflectivity[12] = {0.6, 0.65, 0.9, 0.92, 0.93, 0.94, 0.95, 0.95, 0.95, 0.95, 0.95, 0.95};
    G4double QE[12] = {0.3, 0.35, 0.38, 0.4, 0.41, 0.41, 0.4, 0.4, 0.38, 0.35, 0.25, 0.16};
    mptMirror->AddProperty("REFLECTIVITY", energy, reflectivity, 12);
    mptMirror->AddProperty("EFFICIENCY", energy, QE, 12);

    BC_620->SetMaterialPropertiesTable(mptMirror);
}

void MyDetectorConstruction::ConstructScintillator()
{
    //Scintillator Volume
    solidScintillator = new G4Box("solidScintillator", 0.5*cm, 0.5*cm, 2*cm);

    logicScintillator = new G4LogicalVolume(solidScintillator, ScintillatorMat, "logicScintillator");

    G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin", logicScintillator, BC_620);

    fScoringVolume = logicScintillator;

    G4RotationMatrix* rotationMatrix = new G4RotationMatrix();
    rotationMatrix->rotateY(90.*deg);

    for(G4int i = 0; i <= 6; i=i+2)
    {    
        for(G4int j = 0; j <= 6; j=j+2)
        {
             for(G4int k = 0; k < 16; k++)
             {
                physScintillator = new G4PVPlacement(0, G4ThreeVector(-2.5*cm+j*cm,-2.5*cm+i*cm ,-2.5*cm), logicScintillator, "physScintillator", logicWorld, false, k, true);

                physScintillatorT = new G4PVPlacement(0, G4ThreeVector(-3.5*cm+j*cm,-2.5*cm+i*cm ,2.5*cm), logicScintillator, "physScintillatorT", logicWorld, false, k+16, true);

                physScintillatorR = new G4PVPlacement(rotationMatrix, G4ThreeVector(-2.5*cm,-3.5*cm+i*cm ,-2.5*cm+j*cm), logicScintillator, "physScintillatorR", logicWorld, false, k+32, true);

                physScintillatorRT = new G4PVPlacement(rotationMatrix, G4ThreeVector(2.5*cm,-3.5*cm+i*cm ,-3.5*cm+j*cm), logicScintillator, "physScintillatorRT", logicWorld, false, k+48, true);
            }
        }
    }
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    //World Volume
    solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);

    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

    physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    //Supporting Structure
    solidLayer = new G4Box("solidLayer", 4.5*cm, 0.5*cm, 4.5*cm);
    logicLayer = new G4LogicalVolume(solidLayer, Al_6061, "logicLayer");
    physLayerUp = new G4PVPlacement(0, G4ThreeVector(0.*cm, 4.5*cm, 0.*cm), logicLayer, "physLayerUp", logicWorld, false, 0, true);
    physLayerDown = new G4PVPlacement(0, G4ThreeVector(0.*cm, -4.5*cm, 0.*cm), logicLayer, "physLayerDown", logicWorld, false, 0, true);

    solidWallz = new G4Box("solidWallz", 0.5*cm, 5.*cm, 4.5*cm);
    logicWallz = new G4LogicalVolume(solidWallz, Al_6061, "logicWallz");
    physWallzLeft = new G4PVPlacement(0, G4ThreeVector(-5.*cm, 0.*cm, 0.*cm), logicWallz, "physWallzLeft", logicWorld, false, 0, true);
    physWallzRight = new G4PVPlacement(0, G4ThreeVector(5.*cm, 0.*cm, 0.*cm), logicWallz, "physWallzRight", logicWorld, false, 0, true);

    solidWallx = new G4Box("solidWallx", 5.5*cm, 5.*cm, 0.5*cm);
    logicWallx = new G4LogicalVolume(solidWallx, Al_6061, "logicWallx");
    physWallxLeft = new G4PVPlacement(0, G4ThreeVector(0*cm, 0.*cm, -5.*cm), logicWallx, "physWallxLeft", logicWorld, false, 0, true);
    physWallxRight = new G4PVPlacement(0, G4ThreeVector(0*cm, 0.*cm, 5.*cm), logicWallx, "physWallxRight", logicWorld, false, 0, true);

    ConstructScintillator();

    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

    logicScintillator->SetSensitiveDetector(sensDet);

}

