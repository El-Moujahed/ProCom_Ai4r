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
/// \file B4/B4/src/DetectorMessenger.cc
/// \brief Implementation of the B4::DetectorMessenger class

#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"

#include "G4UIdirectory.hh"

#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4ThreeVector.hh"
#include "G4UIcmdWith3Vector.hh"

#include "G4UIcmdWithABool.hh"


namespace B4
{

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  DetectorMessenger::DetectorMessenger(DetectorConstruction* detector)
  : fDetectorConstruction(detector)
  {
    fDirectory = new G4UIdirectory("/B4/");
    fDirectory->SetGuidance("UI commands specific to this example.");

    fDetDirectory = new G4UIdirectory("/B4/detector/");
    fDetDirectory->SetGuidance("Detector construction control");

    fGazName_ProportionCmd = new G4UIcmdWithAString("/B4/detector/GazName_Proportion",this);
    fGazName_ProportionCmd->SetGuidance("Define a gaz mixture with the form Ne-90-CO2-10");
    fGazName_ProportionCmd->SetParameterName("GazName_Proportion",false);
    fGazName_ProportionCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fGaz_Temperature_Cmd = new G4UIcmdWithADoubleAndUnit("/B4/detector/Gaz_Temperature",this);
    fGaz_Temperature_Cmd->SetGuidance("Define a temperature for the gaz detector Default unit -> kelvin");
    fGaz_Temperature_Cmd->SetParameterName("Gaz_Temperature",false);
    fGaz_Temperature_Cmd->SetUnitCategory("Temperature");
    fGaz_Temperature_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    fGaz_Temperature_Cmd->SetDefaultUnit("kelvin");

    fGaz_PressureCmd = new G4UIcmdWithADoubleAndUnit("/B4/detector/Gaz_Pressure",this);
    fGaz_PressureCmd->SetGuidance("Define a pressure for the gaz detector Default unit -> bar");
    fGaz_PressureCmd->SetParameterName("Gaz_Pressure",false);
    fGaz_PressureCmd->SetUnitCategory("Pressure");
    fGaz_PressureCmd->SetRange("Gaz_Pressure > 0");
    fGaz_PressureCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    fGaz_PressureCmd->SetDefaultUnit("bar");

    //   fTargMatCmd = new G4UIcmdWithAString("/B4/detector/setTargetMaterial",this);
    //   fTargMatCmd->SetGuidance("Select Material of the Target.");
    //   fTargMatCmd->SetParameterName("choice",false);
    //   fTargMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    //
    //   fChamMatCmd = new G4UIcmdWithAString("/B4/detector/setChamberMaterial",this);
    //   fChamMatCmd->SetGuidance("Select Material of the Chamber.");
    //   fChamMatCmd->SetParameterName("choice",false);
    //   fChamMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    //
    //   fStepMaxCmd = new G4UIcmdWithADoubleAndUnit("/B4/detector/stepMax",this);
    //   fStepMaxCmd->SetGuidance("Define a step max");
    //   fStepMaxCmd->SetParameterName("stepMax",false);
    //   fStepMaxCmd->SetUnitCategory("Length");
    //   fStepMaxCmd->AvailableForStates(G4State_Idle);
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  DetectorMessenger::~DetectorMessenger()
  {
    //   delete fTargMatCmd;
    //   delete fChamMatCmd;
    //   delete fStepMaxCmd;
    //   delete fDirectory;
    //   delete fDetDirectory;

    delete fGazName_ProportionCmd;
    delete fGaz_Temperature_Cmd;
    delete fGaz_PressureCmd;
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
  {
    //   if( command == fTargMatCmd )
    //    { fDetectorConstruction->SetTargetMaterial(newValue);}
    //
    //   if( command == fChamMatCmd )
    //    { fDetectorConstruction->SetChamberMaterial(newValue);}
    //
    //   if( command == fStepMaxCmd ) {
    //     fDetectorConstruction
    //       ->SetMaxStep(fStepMaxCmd->GetNewDoubleValue(newValue));
    //   }

    if(command == fGazName_ProportionCmd ){ fDetectorConstruction->SetGazName_Proportion(newValue);}
    if(command == fGaz_Temperature_Cmd ){fDetectorConstruction->SetGaz_Temperature(fGaz_Temperature_Cmd->GetNewDoubleValue(newValue));}
    if(command == fGaz_PressureCmd ){fDetectorConstruction->SetGaz_Pressure(fGaz_PressureCmd->GetNewDoubleValue(newValue));}

  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
