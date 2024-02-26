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
/// \file B4/B4b/src/SteppingAction.cc
/// \brief Implementation of the B4b::SteppingAction class

#include "SteppingAction.hh"
#include "RunData.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

#include "G4VProcess.hh"
#include <G4PhysicsModelCatalog.hh>

using namespace B4;

namespace B4b
{

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  SteppingAction::SteppingAction(const DetectorConstruction* detConstruction)
  : fDetConstruction(detConstruction)
  {
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void SteppingAction::UserSteppingAction(const G4Step* step)
  {
    // Collect energy and track length step by step

    // get volume of the current step
    auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

    // energy deposit
    auto edep = step->GetTotalEnergyDeposit();

    // step length
    G4double stepLength = 0.;
    if ( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) {
      stepLength = step->GetStepLength();
    }

    /// Get post-step point
    G4StepPoint * postStepPoint = step->GetPostStepPoint();
    G4StepPoint * preStepPoint = step->GetPreStepPoint();

    G4int NbrHit_Gamma = 0;
    auto PDGcode = step->GetTrack()->GetDynamicParticle()->GetPDGcode();

    const G4VProcess * process = postStepPoint->GetProcessDefinedStep();
    G4String processName = process->GetProcessName();

    const G4VProcess * process_before = preStepPoint->GetProcessDefinedStep();
    G4String processName_before = ((process_before != NULL) ? process_before->GetProcessName() : G4String());

    auto ParentID = step->GetTrack()->GetParentID();
    auto TrackID = step->GetTrack()->GetTrackID();

    G4double Time = step ->GetPreStepPoint()->GetGlobalTime();

    auto Kinetic_Energy = step->GetTrack()->GetKineticEnergy();

    /// Get track creator process name
    const G4VProcess * creatorProcess = step->GetTrack()->GetCreatorProcess();;
    G4String creatorProcessName = ((creatorProcess != NULL) ? creatorProcess->GetProcessName() : G4String());

    /*
     *    if(PDGcode==22){G4cout << "***processName: " << creatorProcessName << G4endl;}
     *    if(PDGcode==22 && processName != "" && processName != " " && processName != "Transportation" ){NbrHit_Gamma = 1;}
     *    G4cout << "***creatorProcess: " << creatorProcessName << " presteppoint " << processName_before << " process " << processName << " Kinetic_Energy " << Kinetic_Energy<< G4endl;*/

    // Get particle info that create hit
    G4String particleName = step->GetTrack()->GetParticleDefinition()->GetParticleName();
    //     if(particleName != "e-") std::cout << particleName << std::endl;
    //     G4cout << "***Time " << Time << G4endl;

    // Recherche des information/step sur la source Ion/Gamma/e-

    auto runData = static_cast<RunData*>
    (G4RunManager::GetRunManager()->GetNonConstCurrentRun());

    if(TrackID == 1){
      runData->SetParticleName(particleName);
    }


    if(particleName == "Cs137"){
      runData->SetCs137();
    }
    if(particleName == "Cs134"){
      runData->SetCs134();
    }

    /// Recherche des particules initiales e- gamma
    if(creatorProcessName=="RadioactiveDecay"){

//       G4cout << "RadioactiveDecay_Check"<< G4endl;

      if(processName_before==""){

//         G4cout << "initStep_Check"<< G4endl;

        if(PDGcode==22){

          std::map< G4String,G4double> map_Info;

          map_Info["Kinetic_Energy"]=Kinetic_Energy;
          map_Info["Time"]=Time;

          runData->fvec_Gamma.push_back(map_Info);

//           G4cout << "Gamma Kinetic_Energy " << Kinetic_Energy << " Time " << Time << G4endl;
        }

        if(PDGcode==11){

          std::map< G4String,G4double> map_Info;
          map_Info["Kinetic_Energy"]=Kinetic_Energy;
          map_Info["Time"]=Time;

          runData->fvec_Electron.push_back(map_Info);
//           G4cout << "e- Kinetic_Energy " << Kinetic_Energy << " Time " << Time << G4endl;
        }
      } // processName == initStep
    } //************************************************************

    if ( volume == fDetConstruction->GetDetector_PV() ){

      runData->Add_1(kGap, edep, NbrHit_Gamma);

      runData->fmap_Data_det["Edep"]+=edep;
      if(PDGcode==22){

        if(runData->fmap_Gamma_det[Kinetic_Energy]["Time"]>0){;}
        else{
          runData->fmap_Gamma_det[Kinetic_Energy]["Time"]=Time;
        }

        runData->fmap_Data_det["NbrHitsGamma"]+=1;
        if(processName=="phot") runData->fmap_Gamma_det[Kinetic_Energy]["phot"]+=1;
      }
    }


    if ( volume == fDetConstruction->GetGap_under_the_Sample_PV() ) {
      //       runData->Add_1(kGap, edep, NbrHit_Gamma);
//        G4cout << "GetGap_under_the_Sample_PV " << edep << G4endl;
      runData->Edep_Gap_under_the_Sample_PV+=edep;
    }

  }

  //   if ( volume == fDetConstruction->GetAbsorberPV() ) {
  //     runData->Add(kAbs, edep, stepLength);
  //   }
  //
  //   if ( volume == fDetConstruction->GetGapPV() ) {
  //     runData->Add(kGap, edep, stepLength);
  //   }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
