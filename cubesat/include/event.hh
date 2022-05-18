#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"

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
    void AddDelta(G4double delta) {fdelta += delta;} 
    G4int nAbsPhotons;
    G4double absTime;

private:
    G4double fEdep;
    G4double fdelta;
};

#endif
