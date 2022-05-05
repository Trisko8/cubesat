#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);
    
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle("chargedgeantino");
    
    G4ThreeVector pos(0.25*m,0.25*m,0.25*m);
    G4ThreeVector dir(-1.,-1.,-1.);
    G4double momentum = 10000.*MeV;

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(dir);
    fParticleGun->SetParticleMomentum(momentum);
    fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    G4ParticleDefinition* particle = fParticleGun->GetParticleDefinition();
    
    if(particle == G4ChargedGeantino::ChargedGeantino())
    {
        G4int Z =1;
        G4int A = 1;
        
//        G4double mass = (938*Z+939*(A-Z)).*MeV;
        G4double charge = 1.*eplus;
//        G4double energy = sqrt((mass**2)+(momentum**2)).*GeV;
        G4double energy = 0.*MeV;
        
        G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z,A,energy);
        fParticleGun->SetParticleDefinition(ion);
        fParticleGun->SetParticleCharge(charge);
    }

//    G4double envSizeXY = 80.*km;
//    G4double envSizeZ = 40.*km;

//    G4double n = 2.7;
//    G4double rand = G4UniformRand();
//    G4double E = 8/pow(rand,1/(n-1));
//    fParticleGun->SetParticleEnergy(E*GeV);
//    G4ThreeVector dir = G4ThreeVector(0.,0.,1.);
//    G4double theta = acos(G4UniformRand());
//    G4double phi = 2*CLHEP::pi*G4UniformRand();
//    dir.setTheta(theta);
//    dir.setPhi(phi);
//    fParticleGun->SetParticleMomentumDirection(dir);
//    G4double x0 = -envSizeXY/2 + envSizeXY*G4UniformRand();
//    G4double y0 = -envSizeXY/2 + envSizeXY*G4UniformRand();
//    G4double z0 = -0.5*envSizeZ;
//    fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));


    fParticleGun->GeneratePrimaryVertex(anEvent);
}
