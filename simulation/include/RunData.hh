//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B4/B4b/include/RunData.hh
/// \brief Definition of the B4b::RunData class

#ifndef B4bRunData_h
#define B4bRunData_h 1

#include "G4Run.hh"
#include "globals.hh"

#include <array>

namespace B4b
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// const G4int kAbs = 0;
// const G4int kGap = 1;

const G4int kGap = 0;

const G4int kDim = 1;



///  Run data class
///
/// It defines data members to hold the energy deposit and track lengths
/// of charged particles in Absober and Gap layers.
///
/// In order to reduce the number of data members a 2-dimensions array
/// is introduced for each quantity:
/// - fEdep[], fTrackLength[].
///
/// The data are collected step by step in SteppingAction, and
/// the accumulated values are filled in histograms and entuple
/// event by event in EventAction.

class RunData : public G4Run
{
public:
  RunData() = default;
  ~RunData() override = default;

  void Add(G4int id, G4double de, G4double dl);

  void Add_1(G4int id, G4double de, G4double nhg);

  void FillPerEvent();

  void Reset();

  void  SetCs137();
  void  SetCs134();

  void SetParticleName(G4String particleName);

  // Get methods
  G4String  GetVolumeName(G4int id) const;
  G4double  GetEdep(G4int id) const;
  G4double  GetTrackLength(G4int id) const;

  G4int  GetCs137(void) const;
  G4int  GetCs134(void) const;


  // Data à sauvegarder
  // Source
  std::vector< std::map< G4String,G4double  >> fvec_Gamma;
  std::vector< std::map< G4String,G4double  >> fvec_Electron;

  // Detecteur
  std::map< G4double,std::map < G4String, G4double  >> fmap_Gamma_det;
  std::map< G4String,G4double  > fmap_Data_det; // Edep sum + nbr Hits^

  //Grille haute - check presence electrons -> Edep > 0 dans le volume Gap
  G4float Edep_Gap_under_the_Sample_PV = 0;

  G4int Event_Number;

private:
// Detector Gap_under_the_Sample + TODO

  std::array<G4String, kDim>  fVolumeNames = {"Detector" };

  std::array<G4double, kDim>  fEdep = { 0. };
  std::array<G4double, kDim>  fNbrHits_Gamma = { 0.};

  std::array<G4double, kDim>  fTrackLength = { 0.};

  G4int kCs137 = 0;
  G4int kmBa137 = 0;

  G4int kCs134 = 0;

  G4String fparticleName = "";



};

// inline functions

inline void RunData::Add_1(G4int id, G4double de, G4double nhg) {
  fEdep[id] += de;
  fNbrHits_Gamma[id] += nhg;
}


inline G4String  RunData::GetVolumeName(G4int id) const {
  return fVolumeNames[id];
}

inline G4double  RunData::GetEdep(G4int id) const {
  return fEdep[id];
}

inline G4double  RunData::GetTrackLength(G4int id) const {
  return fTrackLength[id];
}


inline void RunData::Add(G4int id, G4double de, G4double dl) {
  fEdep[id] += de;
  fTrackLength[id] += dl;
}


inline G4int RunData::GetCs137(void) const{
  return kCs137;
}

inline void RunData::SetCs137(){
  kCs137+=1;
}
inline void RunData::SetCs134(){
  kCs134+=1;
}

inline void RunData::SetParticleName(G4String particleName){
  fparticleName=particleName;
}


inline G4int RunData::GetCs134(void) const{
  return kCs134;
}

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
