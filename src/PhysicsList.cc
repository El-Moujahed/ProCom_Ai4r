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
/// \file B4/B4b/src/PhysicsList.cc
/// \brief Implementation of the B4::PhysicsList class

#include "PhysicsList.hh"

#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4PhysListFactory.hh"
#include "G4VPhysicsConstructor.hh"
#include "G4ProductionCuts.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

// Local physic directly implemented in the Hadronthrapy directory
// Physic dedicated to the ion-ion inelastic processes
//

#include "G4HadronPhysicsQGSP_BIC_AllHP.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmExtraPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4LossTableManager.hh"
#include "G4UnitsTable.hh"
#include "G4ProcessManager.hh"
#include "G4IonFluctuations.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4ParallelWorldPhysics.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4AutoDelete.hh"

#include "G4UAtomicDeexcitation.hh"
#include "G4EmParameters.hh"

#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include <G4Triton.hh>

#include "G4StepLimiterPhysics.hh"
#include <G4GenericIon.hh>

namespace B4
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::PhysicsList()
{
  SetVerboseLevel(1);

  // Default physics
  RegisterPhysics(new G4DecayPhysics());
  // Radioactive decay
  RegisterPhysics(new G4RadioactiveDecayPhysics());
  // EM physics
  //   RegisterPhysics(new G4EmStandardPhysics());
  //   RegisterPhysics(new G4EmPenelopePhysics());
  RegisterPhysics(new G4EmStandardPhysics_option4());


  RegisterPhysics( new G4HadronPhysicsQGSP_BIC()); // hadron -> proton + neutron + He G4 or can use G4HadronPhysicsQGSP_BIC_HP
  //Warning G4 underestimate neutron rate
  RegisterPhysics( new G4EmExtraPhysics());
  RegisterPhysics( new G4HadronElasticPhysics());
  RegisterPhysics( new G4StoppingPhysics());
  RegisterPhysics( new G4IonBinaryCascadePhysics()); // ions > He other hadron modele QGSP B8 C10_11
  RegisterPhysics( new G4NeutronTrackingCut());

  RegisterPhysics(new G4StepLimiterPhysics());

//   G4RunManager::GetRunManager() -> PhysicsHasBeenModified();


  G4EmParameters* param = G4EmParameters::Instance();
  param->SetUseMottCorrection(true);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
