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
/// \file B4/B4b/include/DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class

#ifndef B4DetectorConstruction_h
#define B4DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4Region.hh"
#include "G4RegionStore.hh"

#include "G4RunManager.hh"
#include "G4GenericMessenger.hh"

#include "G4UserLimits.hh"
#include "G4Tubs.hh"

#include <G4UnitsTable.hh>


class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;

class G4VisAttributes;
class G4Material;
class DetectorMessenger;
class G4UserLimits;

namespace B4
{

  /// Detector construction class to define materials and geometry.
  /// The calorimeter is a box made of a given number of layers. A layer consists
  /// of an absorber plate and of a detection gap. The layer is replicated.
  ///
  /// Four parameters define the geometry of the calorimeter :
  ///
  /// - the thickness of an absorber plate,
  /// - the thickness of a gap,
  /// - the number of layers,
  /// - the transverse size of the calorimeter (the input face is a square).
  ///
  /// In addition a transverse uniform magnetic field is defined
  /// via G4GlobalMagFieldMessenger class.

  class DetectorMessenger;

  class DetectorConstruction : public G4VUserDetectorConstruction
  {
  public:
    DetectorConstruction();
    ~DetectorConstruction() override;

  public:
    G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;

    // For apply some command from detector messenger
    void RG(){G4RunManager::GetRunManager()->ReinitializeGeometry();};

    // get methods
    //
    const G4VPhysicalVolume* GetAbsorberPV() const;
    const G4VPhysicalVolume* GetGapPV() const;
    const G4VPhysicalVolume* GetBody_PV() const;

    const G4VPhysicalVolume* GetGap_under_the_Sample_PV() const;
    const G4VPhysicalVolume* GetDetector_PV() const;


    // gaz detector
    void SetGazName_Proportion(G4String val){fGaz_detector =val;RG();};
    void SetGaz_Temperature(G4double val){fGaz_temperature =val;RG();};
    void SetGaz_Pressure(G4double val){fGaz_pressure =val;RG();};

  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
    void Build_Detector(G4String Name="NaI");
    // data members
    //
    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger;
    // magnetic field messenger

    G4VPhysicalVolume* fAbsorberPV = nullptr; // the absorber physical volume
    G4VPhysicalVolume* fGapPV = nullptr;      // the gap physical volume

    G4bool fCheckOverlaps = true; // option to activate checking of volumes overlaps

    G4String fGaz_detector = "Ne-90-CO2-10";  //;
    G4double fGaz_temperature = 293.17 *kelvin;  //;
    G4double fGaz_pressure= 1.1 *bar;  //;
    
    G4Material*       fBodyMaterial = nullptr; // pointer to the Body material
    G4Material*       fGasMaterial = nullptr; // pointer to the material of the gas inside the box

    DetectorMessenger* fMessenger = nullptr; // messenger

    G4VPhysicalVolume*   fBody_PV = nullptr;      // Body of BeaQUant
    G4VPhysicalVolume*   fSample_Holder_PV = nullptr; // Sample Holder by default fill with environment material
    G4VPhysicalVolume*   fGap_under_the_Sample_PV = nullptr; // Gap under the sample

    G4VPhysicalVolume*   fDetector_PV = nullptr; // Gap under the sample

    G4LogicalVolume*   worldLV = nullptr;

  };

  // inline functions

  inline const G4VPhysicalVolume* DetectorConstruction::GetAbsorberPV() const {
    return fAbsorberPV;
  }

  inline const G4VPhysicalVolume* DetectorConstruction::GetGapPV() const  {
    return fGapPV;
  }

  inline const G4VPhysicalVolume* DetectorConstruction::GetBody_PV() const  {
    return fBody_PV;
}

  inline const G4VPhysicalVolume* DetectorConstruction::GetGap_under_the_Sample_PV() const  {
    return fGap_under_the_Sample_PV;
}

  inline const G4VPhysicalVolume* DetectorConstruction::GetDetector_PV() const  {
    return fDetector_PV;
}

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

