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
/// \file B4/B4b/src/RunData.cc
/// \brief Implementation of the B4b::RunData class

#include "RunData.hh"

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "RunAction.hh"

namespace B4b
{

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void RunData::FillPerEvent()
  {

    // Traitement des données par événements :
    // Gap sous le porte échantillon

//     G4cout << "Edep_Gap_under_the_Sample_PV " << Edep_Gap_under_the_Sample_PV << G4endl;
    G4int Detection_Beta=0; if(Edep_Gap_under_the_Sample_PV>0)Detection_Beta=1;

    //

/*
    // For Print test
    std::cout << "\n Bilan Event " << fparticleName << std::endl;

    // Source
    std::cout << "Ne- " << fvec_Electron.size() << " Ngamma " << fvec_Gamma.size() << std::endl;
    std::cout << "*** e- " << std::endl;
    for ( auto x : fvec_Electron ){

      std::cout << "Kinetic Energie " << x["Kinetic_Energy"] << " [MeV] Time " << G4BestUnit(x["Time"],"Time") << std::endl;

    }

    std::cout << "\n*** Gamma " << std::endl;
    for ( auto x : fvec_Gamma ){

      std::cout << "Kinetic Energie " << x["Kinetic_Energy"] << " [MeV] Time " << G4BestUnit(x["Time"],"Time") << " Delta B- "<< G4BestUnit(x["Time"]-fvec_Electron[0]["Time"],"Time")  << std::endl;

    }
    // Grid

    if(Detection_Beta>0)std::cout << "*** Detection_Beta ! ***" << std::endl;

    //Detecteur

    if(fmap_Gamma_det.size()>0){

    std::cout << "\n Data detecteur ! " << std::endl;


    // Edep - NbrHitsGamma
     for ( auto x : fmap_Data_det ){
        std::cout << "***" << x.first << " " << x.second << std::endl;
    }

    for ( auto x : fmap_Gamma_det ){
        std::cout << "***" << x.first << " " << x.second["Time"] << " " << x.second["phot"]  << std::endl;
    }

    }*/

    // ************************
    // Sauvegarde des données
    // ************************


    // get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();

    G4int counter = 0;
    analysisManager->FillNtupleIColumn(0,counter++, Event_Number);
//    analysisManager->FillNtupleSColumn(0,counter++, fparticleName);

    analysisManager->FillNtupleIColumn(0,counter++, fvec_Electron.size());
    analysisManager->FillNtupleIColumn(0,counter++, fvec_Gamma.size());
    analysisManager->FillNtupleFColumn(0,counter++, Edep_Gap_under_the_Sample_PV);

    // POur les tab on remplit le tableau (vector associée et c'est Ok !)

    const RunAction* constRunAction = static_cast<const RunAction*>(G4RunManager::GetRunManager()->GetUserRunAction());
    RunAction* runAction = const_cast<RunAction*>(constRunAction);

    runAction->fVec_Electron_Kinetic.clear();
    runAction->fVec_Electron_Time.clear();
    runAction->fVec_Gamma_Kinetic.clear();
    runAction->fVec_Electron_Time.clear();

    for ( auto x : fvec_Electron ){
    runAction->fVec_Electron_Kinetic.push_back(x["Kinetic_Energy"]);
    runAction->fVec_Electron_Time.push_back(x["Time"]);
    break;
    }
    for ( auto x : fvec_Gamma ){
    runAction->fVec_Gamma_Kinetic.push_back(x["Kinetic_Energy"]);
    runAction->fVec_Gamma_Time.push_back(x["Time"]);
    }

    analysisManager->AddNtupleRow(0);

    //
    counter = 0;
    analysisManager->FillNtupleIColumn(1,counter++, Event_Number);
    analysisManager->FillNtupleFColumn(1,counter++, fmap_Data_det["Edep"]);
    analysisManager->FillNtupleIColumn(1,counter++, fmap_Data_det["NbrHitsGamma"]);


    runAction->fVec_Gamma_det_Kinetic.clear();
    runAction->fVec_Gamma_det_Time.clear();
    runAction->fVec_Photo.clear();


    for ( auto x : fmap_Gamma_det ){
      runAction->fVec_Gamma_det_Kinetic.push_back(x.first);
      runAction->fVec_Gamma_det_Time.push_back( x.second["Time"]);
      runAction->fVec_Photo.push_back(x.second["phot"]);
    }


    analysisManager->AddNtupleRow(1);



    // accumulate statistic
    // in the order od the histograms, ntuple columns declarations

    for ( auto edep : fEdep ) {
      analysisManager->FillH1(counter, edep);
//       analysisManager->FillNtupleDColumn(counter++, edep);
    }
//     for ( auto trackLength : fTrackLength ) {
//       analysisManager->FillH1(counter, trackLength);
// //       analysisManager->FillNtupleDColumn(counter++, trackLength);
//     }

  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void RunData::Reset()
  {
    for ( auto& edep : fEdep ) {
      edep = 0.;
    }
    for ( auto& x : fNbrHits_Gamma ) {
      x = 0.;
    }


    for ( auto& trackLength : fTrackLength ) {
      trackLength = 0.;
    }


    kCs137 = 0;
    kmBa137 = 0;

    kCs134 = 0;

    // Data à sauvegarder
    // Source
    fvec_Gamma.clear();
    fvec_Electron.clear();

    // Detecteur
    fmap_Gamma_det.clear();
    fmap_Data_det.clear(); // Edep sum + nbr Hits^

    //Grille haute - check presence electrons
    Edep_Gap_under_the_Sample_PV = 0;





  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
