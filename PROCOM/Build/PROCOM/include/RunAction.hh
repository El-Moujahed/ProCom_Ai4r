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
/// \file B4/B4b/include/RunAction.hh
/// \brief Definition of the B4b::RunAction class

#ifndef B4bRunAction_h
#define B4bRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

class G4Run;

namespace B4b
{

  /// Run action class
  ///
  /// It accumulates statistic and computes dispersion of the energy deposit
  /// and track lengths of charged particles with use of analysis tools:
  /// H1D histograms are created in BeginOfRunAction() for the following
  /// physics quantities:
  /// - Edep in absorber
  /// - Edep in gap
  /// - Track length in absorber
  /// - Track length in gap
  /// The same values are also saved in the ntuple.
  /// The histograms and ntuple are saved in the output file in a format
  /// according to a specified file extension.
  ///
  /// In EndOfRunAction(), the accumulated statistic and computed
  /// dispersion is printed.
  ///

  class RunAction : public G4UserRunAction
  {
  public:
    RunAction();
    ~RunAction() override = default;

    G4Run* GenerateRun() override;

    void BeginOfRunAction(const G4Run*) override;
    void   EndOfRunAction(const G4Run*) override;



    std::vector<G4float>  fVec_World_PosX;

    std::vector<G4float> fVec_DeltaTime;
    std::vector<G4String> fVec_ParticleName;
    std::vector<G4int> fVec_PDGCode;

    std::vector<G4float> fVec_Ekine;
    std::vector<G4String> fVec_CreatorModel;
    std::vector<G4int> fVec_CreatorModelID;

    std::vector<G4int> fVec_ParentID;
    std::vector<G4int> fVec_TrackID;

    std::vector<G4float> fVec_Edep_G;
    std::vector<G4float> fVec_Ekine_G;


    std::vector<G4float> fVec_DeltaTime_G;
    std::vector<G4int> fVec_CreatorModelID_G;
    std::vector<G4int> fVec_ParentID_G;
    std::vector<G4int> fVec_TrackID_G;

    std::vector<G4float> fVec_X_G;
    std::vector<G4float> fVec_Y_G;
    std::vector<G4float> fVec_Z_G;

    std::vector<G4float> fVec_Electron_Kinetic;
    std::vector<G4double> fVec_Electron_Time;
    std::vector<G4float> fVec_Gamma_Kinetic;
    std::vector<G4double> fVec_Gamma_Time;

    std::vector<G4float> fVec_Gamma_det_Kinetic;
    std::vector<G4double> fVec_Gamma_det_Time;
    std::vector<G4int> fVec_Photo;


  private:

    void CreateCollumn(G4String TypeColumn, G4int Ntuple_ID,G4int & Column_ID,  G4String CategoryName,G4AnalysisManager *analysisManager  ){

      Column_ID+=1;

      std::cout << "TypeColumn " << TypeColumn << " Ntuple_ID " << Ntuple_ID << " CategoryName " << CategoryName << " Column_ID " << Column_ID << std::endl;

      if(TypeColumn == "F") analysisManager->CreateNtupleFColumn(Ntuple_ID,CategoryName);
      else if(TypeColumn == "D") analysisManager->CreateNtupleDColumn(Ntuple_ID,CategoryName);
      else if(TypeColumn == "I") analysisManager->CreateNtupleIColumn(Ntuple_ID,CategoryName);
      else if(TypeColumn == "S") analysisManager->CreateNtupleSColumn(Ntuple_ID,CategoryName);
      else G4cout << "FATAL ERROR Unknow TypeColumn Please check Runaction.cc" << G4endl;


      //         fmap_NTuple[Ntuple_ID][CategoryName] =Column_ID;
      //         fmap_NTuple_TypeColumn[Ntuple_ID][CategoryName] =TypeColumn;

    }

    void CreateTabCollumn(G4String TypeColumn, G4int Ntuple_ID,  G4String CategoryName,G4AnalysisManager *analysisManager  ){

      std::cout << "TypeColumn " << TypeColumn << " Ntuple_ID " << Ntuple_ID << " CategoryName " << CategoryName  << std::endl;


      if(TypeColumn == "F"){

        if(CategoryName == "Vec_Ekine") analysisManager->CreateNtupleFColumn(Ntuple_ID,CategoryName,fVec_Ekine);
        else if(CategoryName == "Vec_DeltaTime") analysisManager->CreateNtupleFColumn(Ntuple_ID,CategoryName,fVec_DeltaTime);
        else if(CategoryName == "Vec_Electron_Kinetic") analysisManager->CreateNtupleFColumn(Ntuple_ID,CategoryName,fVec_Electron_Kinetic);
        else if(CategoryName == "Vec_Gamma_Kinetic") analysisManager->CreateNtupleFColumn(Ntuple_ID,CategoryName,fVec_Gamma_Kinetic);
        else if(CategoryName == "Vec_Gamma_det_Kinetic") analysisManager->CreateNtupleFColumn(Ntuple_ID,CategoryName,fVec_Gamma_det_Kinetic);
        else G4cout << "[CreateTabCollumn] Not implemented for " << CategoryName << " " << TypeColumn << G4endl;
      }
      else if(TypeColumn == "D"){
        if(CategoryName == "Vec_Electron_Time") analysisManager->CreateNtupleDColumn(Ntuple_ID,CategoryName,fVec_Electron_Time);
        else if(CategoryName == "Vec_Gamma_Time") analysisManager->CreateNtupleDColumn(Ntuple_ID,CategoryName,fVec_Gamma_Time);
        else if(CategoryName == "Vec_Gamma_det_Time") analysisManager->CreateNtupleDColumn(Ntuple_ID,CategoryName,fVec_Gamma_det_Time);
        else G4cout << "[CreateTabCollumn] Not implemented for " << CategoryName << " " << TypeColumn << G4endl;
        //             analysisManager->CreateNtupleDColumn(Ntuple_ID,CategoryName);
      }
      else if(TypeColumn == "I"){

        if(CategoryName == "Vec_PDGCode") analysisManager->CreateNtupleIColumn(Ntuple_ID,CategoryName,fVec_PDGCode);
        else if(CategoryName == "Vec_CreatorModelID") analysisManager->CreateNtupleIColumn(Ntuple_ID,CategoryName,fVec_CreatorModelID);
        else if(CategoryName == "Vec_ParentID") analysisManager->CreateNtupleIColumn(Ntuple_ID,CategoryName,fVec_ParentID);
        else if(CategoryName == "Vec_TrackID") analysisManager->CreateNtupleIColumn(Ntuple_ID,CategoryName,fVec_TrackID);
        else if(CategoryName == "Vec_Photo") analysisManager->CreateNtupleIColumn(Ntuple_ID,CategoryName,fVec_Photo);
        else G4cout << "[CreateTabCollumn] Not implemented for " << CategoryName << " " << TypeColumn << G4endl;
      }
      else if(TypeColumn == "S"){

        G4cout << "[CreateTabCollumn] FATAL ERROR Geant4 don't accept vector of String Please check Runaction.cc" << G4endl;
      }
      else{
        G4cout << "[CreateTabCollumn] FATAL ERROR Unknow TypeColumn Please check Runaction.cc" << G4endl;
      }

      //         fmap_NTuple[Ntuple_ID][CategoryName] =Column_ID;
      //         fmap_NTuple_TypeColumn[Ntuple_ID][CategoryName] =TypeColumn;

    }


    void CreateTabCollumn_general(G4String TypeColumn, G4int Ntuple_ID,  G4String CategoryName,G4AnalysisManager *analysisManager  ){
      // ***
      // Goal to create Tuples with defined vectors in a general way. Vectors are only to be used at the time of registration.
      // ***

      std::cout << "TypeColumn " << TypeColumn << " Ntuple_ID " << Ntuple_ID << " CategoryName " << CategoryName  << std::endl;


      if(TypeColumn == "F"){

        if(CategoryName == "Vec_Edep") analysisManager->CreateNtupleFColumn(Ntuple_ID,CategoryName,fVec_Edep_G);
        else if(CategoryName == "Vec_Ekine") analysisManager->CreateNtupleFColumn(Ntuple_ID,CategoryName,fVec_Ekine_G);
        else if(CategoryName == "Vec_DeltaTime") analysisManager->CreateNtupleFColumn(Ntuple_ID,CategoryName,fVec_DeltaTime_G);
        else if(CategoryName == "Vec_X") analysisManager->CreateNtupleFColumn(Ntuple_ID,CategoryName,fVec_X_G);
        else if(CategoryName == "Vec_Y") analysisManager->CreateNtupleFColumn(Ntuple_ID,CategoryName,fVec_Y_G);
        else if(CategoryName == "Vec_Z") analysisManager->CreateNtupleFColumn(Ntuple_ID,CategoryName,fVec_Z_G);
        else G4cout << "[CreateTabCollumn] Not implemented for " << CategoryName << " " << TypeColumn << G4endl;
      }
      else if(TypeColumn == "D"){
        ;
        //             analysisManager->CreateNtupleDColumn(Ntuple_ID,CategoryName);
      }
      else if(TypeColumn == "I"){

        //             if(CategoryName      == "Vec_PDGCode") analysisManager->CreateNtupleIColumn(Ntuple_ID,CategoryName,fVec_PDGCode);
        if(CategoryName == "Vec_CreatorModelID") analysisManager->CreateNtupleIColumn(Ntuple_ID,CategoryName,fVec_CreatorModelID_G);
        else if(CategoryName == "Vec_ParentID") analysisManager->CreateNtupleIColumn(Ntuple_ID,CategoryName,fVec_ParentID_G);
        else if(CategoryName == "Vec_TrackID") analysisManager->CreateNtupleIColumn(Ntuple_ID,CategoryName,fVec_TrackID_G);
        else G4cout << "[CreateTabCollumn] Not implemented for " << CategoryName << " " << TypeColumn << G4endl;
      }
      else if(TypeColumn == "S"){

        G4cout << "[CreateTabCollumn] FATAL ERROR Geant4 don't accept vector of String Please check Runaction.cc" << G4endl;
      }
      else{
        G4cout << "[CreateTabCollumn] FATAL ERROR Unknow TypeColumn Please check Runaction.cc" << G4endl;
      }
    }

  };

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

