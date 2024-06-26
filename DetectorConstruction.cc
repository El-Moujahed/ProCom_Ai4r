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
/// \file B2/B2b/src/DetectorConstruction.cc
/// \brief Implementation of the B2b::DetectorConstruction class

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "ChamberParameterisation.hh"
#include "TrackerSD.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"

#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


// Gestion des couleurs pour G4VisAttributes
//   G4Colour  white   ()              ;  // white
G4Colour  white   (1.0, 1.0, 1.0,0.5) ;  // white
G4Colour  gris    (0.5, 0.5, 0.5) ;  // gray confiousing with gray energy unit
G4Colour  black   (0.0, 0.0, 0.0) ;  // black
G4Colour  red     (1.0, 0.0, 0.0) ;  // red
G4Colour  green   (0.0, 1.0, 0.0) ;  // green
G4Colour  blue    (0.0, 0.0, 1.0) ;  // blue
G4Colour  cyan    (0.0, 1.0, 1.0) ;  // cyan
G4Colour  magenta (1.0, 0.0, 1.0) ;  // magenta
G4Colour  yellow  (1.0, 1.0, 0.0) ;  // yellow

using namespace B2;

namespace B2b
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal
G4GlobalMagFieldMessenger* DetectorConstruction::fMagFieldMessenger = nullptr;

DetectorConstruction::DetectorConstruction()
{
  fMessenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{
  delete fStepLimit;
  delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Define materials
  DefineMaterials();

  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{
  // Material definition

  G4NistManager* nistManager = G4NistManager::Instance();

  // Air defined using NIST Manager
  nistManager->FindOrBuildMaterial("G4_AIR");

  // Glass defined using  NISR Manager
  nistManager->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
  
  // Lead defined using NIST Manager
  fTargetMaterial  = nistManager->FindOrBuildMaterial("G4_Pb");
  
  // Aluminium defined using NIST Manager
  fBoxMaterial  = nistManager->FindOrBuildMaterial("G4_Al");

  // Xenon gas defined using NIST Manager
  fChamberMaterial = nistManager->FindOrBuildMaterial("G4_Xe");

  fNaI_scint = nistManager->FindOrBuildMaterial("G4_SODIUM_IODIDE");
  
  G4String Gaz = fGaz_detector;
  G4double temperature = fGaz_temperature;
  G4double pressure = fGaz_pressure;
  
  G4bool isotopes = false;
  G4Element* Ne = nistManager->FindOrBuildElement("Ne", isotopes);
  G4Material* CO2 = nistManager->FindOrBuildMaterial("G4_CARBON_DIOXIDE");
  G4double density_Ne90Co210 = (0.000838505*0.9 + 0.00184212*0.1)*g/cm3; // 90 10 en volume !
  auto Ne_90_CO2_10 = new G4Material("Ne_90_CO2_10", density_Ne90Co210, 2, kStateGas, temperature, pressure);
  Ne_90_CO2_10->AddElement(Ne, 90*perCent);
  Ne_90_CO2_10->AddMaterial(CO2, 10*perCent);
  fGasMaterial = Ne_90_CO2_10;

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  G4Material* air  = G4Material::GetMaterial("G4_AIR");
  
  G4Material* glass = G4Material::GetMaterial("G4_SILICON_DIOXIDE");

  
  

  // Sizes of the principal geometrical components (solids)

  G4int NbOfChambers = 5;
  G4double chamberSpacing = 80*cm; // from chamber center to center!

  G4double chamberWidth = 20.0*cm; // width of the chambers
  G4double targetLength =  5.0*cm; // full length of Target

  G4double trackerLength = (NbOfChambers+1)*chamberSpacing;

  G4double worldLength = 800*mm;
                                                                                                                                //1.2 * (2*targetLength + trackerLength);

  G4double targetRadius  = 20*cm;   // Radius of Target
  targetLength = 0.5*targetLength;             // Half length of the Target
  G4double trackerSize   = 0.5*trackerLength;  // Half length of the Tracker
  
  
  G4double L_plaques = 330;
  G4double l_plaques = 278;
  
  G4double e_bas = 20*mm ;
  G4double e_haut= 20*mm ;
  G4double e_murs = 30*mm ;
  
  G4double L_int = 330*mm - e_murs;
  G4double l_int = 278*mm - e_murs;
  
  G4double h_int = 50*mm;

  G4double e_cap = 2*mm ;

  G4double r_scint = 58/2 * mm ;
  G4double h_scint = 250*mm ;
  
  G4double e_lame = 1*mm ;
  G4double L_lame = 76*mm ;
  G4double l_lame = 26*mm ;
  G4double d_lame = 12*mm ; //la distance entre le bas de la boite et la la lame de verre

  
  

  // Definitions of Solids, Logical Volumes, Physical Volumes

  // World

  G4GeometryManager::GetInstance()->SetWorldMaximumExtent(worldLength);

  G4cout << "Computed tolerance = "
         << G4GeometryTolerance::GetInstance()->GetSurfaceTolerance()/mm
         << " mm" << G4endl;

  auto worldS = new G4Box("world",                       // its name
    worldLength / 2, worldLength / 2, worldLength / 2);  // its size
  auto worldLV = new G4LogicalVolume(worldS,             // its solid
    air,                                                 // its material
    "World");                                            // its name

  //  Must place the World Physical volume unrotated at (0,0,0).
  //
  auto worldPV = new G4PVPlacement(nullptr,  // no rotation
    G4ThreeVector(),                         // at (0,0,0)
    worldLV,                                 // its logical volume
    "World",                                 // its name
    nullptr,                                 // its mother  volume
    false,                                   // no boolean operations
    0,                                       // copy number
    fCheckOverlaps);                         // checking overlaps


  // Volume intérieur = gaz (Ne90Co210): 
  
  G4VSolid* Vol_int = new G4Box("Vol_int", L_int/2, h_int/2, l_int/2);
  
  auto Vol_int_LV = new G4LogicalVolume(Vol_int, fGasMaterial , "gaz");
  
  G4ThreeVector Gaz_Position = G4ThreeVector(0,e_bas/2,0);
  
  auto Vol_int_PV = new G4PVPlacement(nullptr,  // no rotation
    Gaz_Position,                         // position
    Vol_int_LV,                                 // its logical volume
    "Gaz",                                 // its name
    worldLV,                                 // its mother  volume
    false,                                   // no boolean operations
    0,                                       // copy number
    fCheckOverlaps);
    
    
  // Volume extérieur = l'armature en aluminium
  
  G4VSolid* Vol_ext = new G4Box("Vol_ext", L_plaques/2, (h_int+e_bas)/2, l_plaques/2);
  
  //G4RotationMatrix* rotMatrix = new G4RotationMatrix();  //this is how to create a null rotation matrix
  
  G4VSolid* Box_solid = new G4SubtractionSolid("Box_solid", Vol_ext, Vol_int, nullptr, G4ThreeVector(0,e_bas/2,0) );
  
  auto Box_LV = new G4LogicalVolume(Box_solid, fBoxMaterial, "Box");
  
  auto Box_PV = new G4PVPlacement(nullptr,  // no rotation
    G4ThreeVector(),                         // at (0,0,0)
    Box_LV,                                 // its logical volume
    "Box",                                 // its name
    worldLV,                                 // its mother  volume
    false,                                   // no boolean operations
    0,                                       // copy number
    fCheckOverlaps);

  // Target

  auto targetS = new G4Tubs("target", 0., r_scint, h_scint/2, 0. * deg, 360. * deg);
  fLogicTarget = new G4LogicalVolume(targetS, fNaI_scint, "Target", nullptr, nullptr, nullptr);
  
  G4double phi = 45*deg;
  G4RotationMatrix* rot_Target = new G4RotationMatrix(); 
  rot_Target->rotateX(90*deg);
  
  G4ThreeVector positionTarget = G4ThreeVector(0,(h_int+e_bas+h_scint)/2+e_cap,0);
  
  new G4PVPlacement(rot_Target,  // no rotation
    positionTarget,           // at (x,y,z)
    fLogicTarget,             // its logical volume
    "Target",                 // its name
    worldLV,                  // its mother volume
    false,                    // no boolean operations
    0,                        // copy number
    fCheckOverlaps);          // checking overlaps


  // Plafond de la boîte, constituée d'un volume rectangulaire auquel on retire le cylindre pour le scintillateur.
  
  G4VSolid* Roof_boite = new G4Box("Roof_boite", L_plaques/2, e_haut/2, l_plaques/2);
  
  G4VSolid* Roof_cyl = new G4Tubs("Roof_cyl", 0., r_scint, (e_haut-e_cap)/2, 0. * deg, 360. * deg);
  
  G4VSolid* Roof_solid = new G4SubtractionSolid("Roof_solid", Roof_boite, Roof_cyl, rot_Target, G4ThreeVector(0,e_cap/2,0) );

  auto Roof_LV = new G4LogicalVolume(Roof_solid, fBoxMaterial, "Roof");
  
  G4ThreeVector Roof_Position = G4ThreeVector(0,(h_int+e_bas+e_haut)/2,0);
  
  auto Roof_PV = new G4PVPlacement(nullptr,  // no rotation
    Roof_Position,                         // at (0,0,0)
    Roof_LV,                                 // its logical volume
    "Roof",                                 // its name
    worldLV,                                 // its mother  volume
    false,                                   // no boolean operations
    0,                                       // copy number
    fCheckOverlaps);


  //Lame de verre : 
  
  
  G4VSolid* Lame_solid = new G4Box("Lame_solid", L_lame/2, e_lame/2, l_lame/2);
  
  auto Lame_LV = new G4LogicalVolume(Lame_solid, glass, "Lame");
  
  G4ThreeVector Lame_Position = G4ThreeVector(0,(-h_int)/2+d_lame,0);
  
  auto Lame_PV = new G4PVPlacement(nullptr,  // no rotation
    Lame_Position,                         // at (0,0,0)
    Lame_LV,                                 // its logical volume
    "Lame",                                 // its name
    Vol_int_LV,                                 // its mother  volume
    false,                                   // no boolean operations
    0,                                       // copy number
    fCheckOverlaps);

  








  // Tracker

  G4ThreeVector positionTracker = G4ThreeVector(0,0,0);

  auto trackerS = new G4Tubs("tracker", 0, trackerSize, trackerSize, 0. * deg, 360. * deg);
  auto trackerLV = new G4LogicalVolume(trackerS, air, "Tracker", nullptr, nullptr, nullptr);
  //new G4PVPlacement(nullptr,  // no rotation
  //  positionTracker,          // at (x,y,z)
  //  trackerLV,                // its logical volume
  //  "Tracker",                // its name
  //  worldLV,                  // its mother  volume
  //  false,                    // no boolean operations
  //  0,                        // copy number
  //  fCheckOverlaps);          // checking overlaps

  // Tracker segments

  // An example of Parameterised volumes
  // Dummy values for G4Tubs -- modified by parameterised volume

  auto chamberS = new G4Tubs("tracker", 0, 100 * cm, 100 * cm, 0. * deg, 360. * deg);
  fLogicChamber =
    new G4LogicalVolume(chamberS, fChamberMaterial, "Chamber", nullptr, nullptr, nullptr);

  //G4double firstPosition = -trackerSize + chamberSpacing;
  //G4double firstLength   = trackerLength/10;
  //G4double lastLength    = trackerLength;

  //G4VPVParameterisation* chamberParam =
  //  new ChamberParameterisation(
    //                             NbOfChambers,   // NoChambers
      //                            firstPosition,  // Z of center of first
        //                          chamberSpacing, // Z spacing of centers
          //                        chamberWidth,  // chamber width
            //                      firstLength,    // initial length
              //                    lastLength);    // final length

  // dummy value : kZAxis -- modified by parameterised volume

  //new G4PVParameterised("Chamber",       // their name
    //                    fLogicChamber,   // their logical volume
      //                  trackerLV,       // Mother logical volume
        //                kZAxis,          // Are placed along this axis
          //              NbOfChambers,    // Number of chambers
            //            chamberParam,    // The parametrisation
              //          fCheckOverlaps); // checking overlaps

  G4cout << "There are " << NbOfChambers << " chambers in the tracker region. "
         << G4endl
         << "The chambers are " << chamberWidth/cm << " cm of "
         << fChamberMaterial->GetName() << G4endl
         << "The distance between chamber is " << chamberSpacing/cm << " cm"
         << G4endl;

  // Visualization attributes

  auto boxVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
  worldLV   ->SetVisAttributes(boxVisAtt);
  
  auto gasVisAtt = new G4VisAttributes(magenta);
  Vol_int_LV ->SetVisAttributes(gasVisAtt);
  
  auto targetVisAtt = new G4VisAttributes(G4Colour(0, 0, 1.0));
  fLogicTarget ->SetVisAttributes(targetVisAtt);
  
  
  trackerLV ->SetVisAttributes(boxVisAtt);

  auto chamberVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0));
  fLogicChamber->SetVisAttributes(chamberVisAtt);


  // Example of User Limits
  //
  // Below is an example of how to set tracking constraints in a given
  // logical volume
  //
  // Sets a max step length in the tracker region, with G4StepLimiter

  G4double maxStep = 0.5*chamberWidth;
  fStepLimit = new G4UserLimits(maxStep);
  trackerLV->SetUserLimits(fStepLimit);

  /// Set additional contraints on the track, with G4UserSpecialCuts
  ///
  /// G4double maxLength = 2*trackerLength, maxTime = 0.1*ns, minEkin = 10*MeV;
  /// trackerLV->SetUserLimits(new G4UserLimits(maxStep,
  ///                                           maxLength,
  ///                                           maxTime,
  ///                                           minEkin));

  // Always return the physical world

  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
  // Sensitive detectors

  G4String trackerChamberSDname = "B2/TrackerChamberSD";
  auto aTrackerSD = new TrackerSD(trackerChamberSDname, "TrackerHitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);
  SetSensitiveDetector( fLogicChamber,  aTrackerSD );

  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue = G4ThreeVector();
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);

  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetTargetMaterial(G4String materialName)
{
  G4NistManager* nistManager = G4NistManager::Instance();

  G4Material* pttoMaterial =
              nistManager->FindOrBuildMaterial(materialName);

  if (fTargetMaterial != pttoMaterial) {
     if ( pttoMaterial ) {
        fTargetMaterial = pttoMaterial;
        if (fLogicTarget) fLogicTarget->SetMaterial(fTargetMaterial);
        G4cout
          << G4endl
          << "----> The target is made of " << materialName << G4endl;
     } else {
        G4cout
          << G4endl
          << "-->  WARNING from SetTargetMaterial : "
          << materialName << " not found" << G4endl;
     }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetChamberMaterial(G4String materialName)
{
  G4NistManager* nistManager = G4NistManager::Instance();

  G4Material* pttoMaterial =
              nistManager->FindOrBuildMaterial(materialName);

  if (fChamberMaterial != pttoMaterial) {
     if ( pttoMaterial ) {
        fChamberMaterial = pttoMaterial;
        if (fLogicChamber) fLogicChamber->SetMaterial(fChamberMaterial);
        G4cout
          << G4endl
          << "----> The chambers are made of " << materialName << G4endl;
     } else {
        G4cout
          << G4endl
          << "-->  WARNING from SetChamberMaterial : "
          << materialName << " not found" << G4endl;
     }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetMaxStep(G4double maxStep)
{
  if ((fStepLimit)&&(maxStep>0.)) fStepLimit->SetMaxAllowedStep(maxStep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
