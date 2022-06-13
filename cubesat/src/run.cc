#include "run.hh"

//class PrimaryGeneratorAction;

MyRunAction::MyRunAction()
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    
    //Definición de las tuplas
    man->CreateNtuple("Particle", "Particle");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->FinishNtuple(0);

    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->FinishNtuple(1);

    man->CreateNtuple("Scoring", "Scoring");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("fEdep");
    man->CreateNtupleDColumn("fDose");
    man->CreateNtupleDColumn("fCount");
    man->FinishNtuple(2);
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{   
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    
    G4int runID = run->GetRunID();
    
    std::stringstream strRunID;
    strRunID << runID;

    man->OpenFile("output"+strRunID.str()+".root");
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    
    man->Write();
    man->CloseFile();
}
