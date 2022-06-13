#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"

#include "G4SystemOfUnits.hh"
#include "g4root.hh"

#include "run.hh"

class MyEventAction : public G4UserEventAction
{
public:
    MyEventAction(MyRunAction*);
    ~MyEventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

    void AddEdep(G4double edep) {fEdep += edep;} 
    void AddCounter(G4int counter) {fcount += counter;}  

private:
    G4int fcount =0;
    G4double fEdep = 0.;
    G4double fdose = 0.;
};

#endif
