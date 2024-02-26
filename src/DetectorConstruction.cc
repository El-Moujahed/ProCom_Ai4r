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
/// \file B4/B4b/src/DetectorConstruction.cc
/// \brief Implementation of the B4:DetectorConstruction class

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
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

#include "G4GenericMessenger.hh"

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


namespace B4
{


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
{
  fMessenger = new DetectorMessenger(this);

//   fGaz_detector = "Ne-90-CO2-10";
//   fGaz_temperature = 293.17 *kelvin;
//   fGaz_pressure = 1.1 *bar;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{
  delete fMessenger;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal
G4GlobalMagFieldMessenger* DetectorConstruction::fMagFieldMessenger = nullptr;

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
  // Lead material defined using NIST Manager
  auto nistManager = G4NistManager::Instance();
  //   https://geant4-forum.web.cern.ch/t/g4tessellatedsolid-transportation-exceptions/2561
  nistManager->FindOrBuildMaterial("G4_Pb");
  nistManager->FindOrBuildMaterial("G4_WATER");
  nistManager->FindOrBuildMaterial("G4_AIR");

//   nistManager->FindOrBuildMaterial("G4_Al");
//   nistManager->FindOrBuildMaterial("G4_Pu");
//   nistManager->FindOrBuildMaterial("G4_Pt");

  nistManager->FindOrBuildMaterial("G4_SILICON_DIOXIDE");

  nistManager->FindOrBuildMaterial("G4_SODIUM_IODIDE");
  
  
  fBodyMaterial  = nistManager->FindOrBuildMaterial("G4_Al");

  // Liquid argon material
  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;
  G4double density;
  new G4Material("liquidArgon", z=18., a= 39.95*g/mole, density= 1.390*g/cm3);
  // The argon by NIST Manager is a gas with a different density

  // Vacuum
  new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
                 kStateGas, 2.73*kelvin, 3.e-18*pascal);

  // ************************************************************************************
  // Projet Ai4R
  //***********************************************************************************
  //     Conditions nominal BeaQuant
  //     G4String Gaz = "Ne-90-CO2-10";
  //     G4double temperature = 293.15*kelvin;
  //     G4double pressure = 1.1*bar;
  G4String Gaz = fGaz_detector;
  G4double temperature = fGaz_temperature;
  G4double pressure = fGaz_pressure;
  //***********************************************************************************

  G4bool isotopes = false;
  G4Element* Ne = nistManager->FindOrBuildElement("Ne", isotopes);
  G4Material* G4_CARBON_DIOXIDE = nistManager->FindOrBuildMaterial("G4_CARBON_DIOXIDE");
  G4double density_Ne90Co210 = (0.000838505*0.9 + 0.00184212*0.1)*g/cm3; // 90 10 en volume !
  auto Ne_90_CO2_10 = new G4Material("Ne_90_CO2_10", density_Ne90Co210, 2, kStateGas, temperature, pressure);
  Ne_90_CO2_10->AddElement(Ne, 90*perCent);
  Ne_90_CO2_10->AddMaterial(G4_CARBON_DIOXIDE, 10*perCent);
  fGasMaterial = Ne_90_CO2_10;


  // Method pour calculer le mélange gazeux à partir du messenger

  std::map < G4String , std::map < G4String , G4double >> map_Caracteristique_Messenger;

  G4String s = Gaz;

  // On decouple / split  G4String Gaz.
  std::istringstream ss( s );
  std::vector <G4String> v_record;
  // 	cout << "s  "<< s << endl;
  while (ss){G4String s; if ((!getline( ss, s, '-' ))) break; v_record.push_back( s );}
  G4int i =0; G4String Gaz_Name = "";

  for(auto& x: v_record){
    G4cout << "v_record " << x << G4endl;
    if(i%2 == true){
      map_Caracteristique_Messenger[Gaz_Name]["Proportion"]= G4UIcommand::ConvertToDouble(x);
      G4cout << "map_Caracteristique_Messenger " << map_Caracteristique_Messenger[Gaz_Name]["Proportion"] << " Gaz_Name " << Gaz_Name << G4endl;
    }
    else{
      Gaz_Name = x;
      G4cout << "Gaz_Name " << Gaz_Name << G4endl;
    }
    i++;
  }
  G4int NbrGazMelangeGazeux = map_Caracteristique_Messenger.size();
  G4cout << "NbrGazMelangeGazeux " << NbrGazMelangeGazeux << G4endl;

  // calcul de la density / densité
  G4double R = 8.3145; // Pa*m3/mol/K
  G4double density_melange =0;

  for(auto& x: map_Caracteristique_Messenger){

    G4String Element_Name = x.first;
    G4double Element_Proportion = x.second["Proportion"] ; // en %
    G4cout << "Element_Name " << Element_Name << " -> " << Element_Proportion << " % " << G4endl;
    if(Element_Name == "Co2" || Element_Name == "CO2"){
      Element_Name = "G4_CARBON_DIOXIDE";
    }
    if(Element_Name == "G4_CARBON_DIOXIDE"){

      // material is different from element !
      G4Material* Gaz_Element = nistManager->FindOrBuildMaterial(Element_Name);
      G4double Element_Density;
      G4double P = 0 * pascal ;
      P = pressure;
      G4double T = temperature *kelvin;
      G4double AtomicMassAmu = 44.01; // g_mol
      G4cout << " GetChemicalFormula " << Gaz_Element->GetChemicalFormula () << G4endl;
      Element_Density = 0 *(g/m3);
      Element_Density = ((P/(pascal) * AtomicMassAmu  ) / (R * T/(kelvin)))  ;
      G4double Element_Proportion_pourcent = Element_Proportion/100 ;

      density_melange += (Element_Proportion_pourcent * Element_Density) ;

      G4cout << "P "  << G4BestUnit(P, "Pressure") << " pressure " << G4BestUnit(pressure, "Pressure")
      << " T " << T
      << " AtomicMassAmu " <<  AtomicMassAmu
      << " Element_Density " << Element_Density /*G4BestUnit(Element_Density, "speudoVolume") */
      << " density_melange " << density_melange << " g/m3"
      << G4endl;
    }
    else{
      G4Element* Gaz_Element = nistManager->FindOrBuildElement(Element_Name, isotopes);
      G4double Element_Density;
      G4double P = 0 * pascal ;
      P = pressure;
      G4double T = temperature *kelvin;
      G4double AtomicMassAmu = Gaz_Element->GetAtomicMassAmu();
      Element_Density = 0 *(g/m3);
      Element_Density = ((P/(pascal) * AtomicMassAmu  ) / (R * T/(kelvin)))  ;
      G4double Element_Proportion_pourcent = Element_Proportion/100 ;
      density_melange += (Element_Proportion_pourcent * Element_Density) ;
      G4cout << "P "  << G4BestUnit(P, "Pressure") << " pressure " << G4BestUnit(pressure, "Pressure")
      << " T " << T
      << " AtomicMassAmu " <<  AtomicMassAmu
      << " Element_Density " << Element_Density /*G4BestUnit(Element_Density, "speudoVolume") */
      << " density_melange " << density_melange << " g/m3"
      << G4endl;
    }
  }

  G4double density_melange_final = density_melange *(g/m3);

  auto Gaz_detector = new G4Material("Gaz_detector", density_melange_final, NbrGazMelangeGazeux, kStateGas, temperature, pressure);
  for(auto& x: map_Caracteristique_Messenger){
    G4String Element_Name = x.first; G4double Element_Proportion = x.second["Proportion"] ;
    if(Element_Name == "Co2" || Element_Name == "CO2"){Element_Name = "G4_CARBON_DIOXIDE";}
    if(Element_Name == "G4_CARBON_DIOXIDE"){
      G4Material* Gaz_Element = nistManager->FindOrBuildMaterial(Element_Name);
      Gaz_detector->AddMaterial(Gaz_Element, Element_Proportion*perCent);
    }
    else{
      G4Element* Gaz_Element = nistManager->FindOrBuildElement(Element_Name);
      Gaz_detector->AddElement(Gaz_Element, Element_Proportion*perCent);
    }
  }


  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{

  // Get materials // https://www.fe.infn.it/u/paterno/Geant4_tutorial/slides_further/Geometry/G4_Nist_Materials.pdf
  auto defaultMaterial = G4Material::GetMaterial("G4_AIR");
  auto env_mat = G4Material::GetMaterial("Gaz_detector");
  
  G4Material* air  = G4Material::GetMaterial("G4_AIR");
  
  G4Material* glass = G4Material::GetMaterial("G4_SILICON_DIOXIDE");


  if ( ! defaultMaterial || !env_mat ) {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined.";
    G4Exception("DetectorConstruction::DefineVolumes()",
                "MyCode0001", FatalException, msg);
  }
  
    //
    // Geometry parameters
    //
    
    
  G4double worldLength = 800*mm;
  
  G4double L_plaques = 330; //longueur plaques
  G4double l_plaques = 278; //largeur plaques
  
  G4double e_bas = 20*mm ; //épaisseur "sol" du système
  G4double e_haut= 20*mm ; //épaisseur "plafond" du système
  G4double e_murs = 30*mm ; //épaisseur "murs" du système
  
  G4double L_int = 330*mm - e_murs; //longueur de l'espace à l'intérieur de la boîte
  G4double l_int = 278*mm - e_murs; //largeur de l'espace à l'intérieur de la boîte
  
  G4double h_int = 50*mm; //hauteur de l'espace à l'intérieur de la boîte

  G4double e_cap = 2*mm ; //épaisseur du capot (fine partie d'aluminium entre le gaz du dispositif et le scintillateur)

  G4double r_scint = 58/2 * mm ; //rayon scintillateur
  G4double h_scint = 250*mm ; //hauteur scintillateur
  
  G4double e_lame = 1*mm ; //épaisseur lame de verre (sample holder)
  G4double L_lame = 76*mm ; //longueur lame de verre (sample holder)
  G4double l_lame = 26*mm ; //largeur lame de verre (sample holder)
  G4double d_lame = 12*mm ; //la distance entre le bas de la boite et la la lame de verre


  // *************************************************************************
  // World
  // *************************************************************************

  G4GeometryManager::GetInstance()->SetWorldMaximumExtent(worldLength);

  auto worldS = new G4Box("world",                       // its name
    worldLength / 2, worldLength / 2, worldLength / 2);  // its size
    
  auto worldLV = new G4LogicalVolume(
  			worldS,             // its solid
    			air,                // its material
    			"World");           // its name

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



  //
  // Visualization attributes
  //
//   worldLV->SetVisAttributes (G4VisAttributes::GetInvisible());
/*
  auto simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(true);
  calorLV->SetVisAttributes(simpleBoxVisAtt);*/


  std::cout << "******************************************************" << std::endl;
  std::cout << "                      Setup Geometry                  " << std::endl;
  std::cout << "******************************************************" << std::endl;


  //****************************************************************
  //Volume intérieur de la boîte
  //****************************************************************
  
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
    
  //****************************************************************
  // Volume extérieur = l'armature en aluminium
  //****************************************************************

  
  G4VSolid* Vol_ext = new G4Box("Vol_ext", L_plaques/2, (h_int+e_bas)/2, l_plaques/2);
  
  G4VSolid* Body_S = new G4SubtractionSolid("Body_S", Vol_ext, Vol_int, nullptr, G4ThreeVector(0,e_bas/2,0) );
  
  auto Body_LV = new G4LogicalVolume(Body_S, fBodyMaterial, "Body");
  
  auto Body_PV = new G4PVPlacement(nullptr,  // no rotation
    G4ThreeVector(),                         // at (0,0,0)
    Body_LV,                                 // its logical volume
    "Body",                                 // its name
    worldLV,                                 // its mother  volume
    false,                                   // no boolean operations
    0,                                       // copy number
    fCheckOverlaps);
    
  // Visualisation attributes of the detector
  auto Cosmetic = new G4VisAttributes(gray);
  Cosmetic -> SetVisibility(true);
  Cosmetic -> SetForceSolid(false);
  //skyBlue -> SetForceWireframe(true);
  Body_LV -> SetVisAttributes(Cosmetic);

  
  // //****************************************************************
  // Plafond de la boîte, constituée d'un volume rectangulaire auquel on retire le cylindre pour le scintillateur (encoche).
  // //****************************************************************
    
  G4VSolid* Roof_boite = new G4Box("Roof_boite", L_plaques/2, e_haut/2, l_plaques/2);
  
  G4VSolid* Roof_cyl = new G4Tubs("Roof_cyl", 0., r_scint, (e_haut-e_cap)/2, 0. * deg, 360. * deg);
  
  G4RotationMatrix* rot_scint = new G4RotationMatrix(); 
  rot_scint->rotateX(90*deg);
  
  G4VSolid* Roof_solid = new G4SubtractionSolid("Roof_solid", Roof_boite, Roof_cyl, rot_scint, G4ThreeVector(0,e_cap/2,0) );

  auto Roof_LV = new G4LogicalVolume(Roof_solid, fBodyMaterial, "Roof");
  
  G4ThreeVector Roof_Position = G4ThreeVector(0,(h_int+e_bas+e_haut)/2,0);
  
  auto Roof_PV = new G4PVPlacement(nullptr,  // no rotation
    Roof_Position,                         // at (0,0,0)
    Roof_LV,                                 // its logical volume
    "Roof",                                 // its name
    worldLV,                                 // its mother  volume
    false,                                   // no boolean operations
    0,                                       // copy number
    fCheckOverlaps);


  Roof_LV -> SetVisAttributes(Cosmetic);

  // //****************************************************************
  //Lame de verre (Sample Holder) : 
  // //****************************************************************
  
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
    
  // Visualisation attributes of the detector
  Cosmetic = new G4VisAttributes( red);
  Cosmetic -> SetVisibility(true);
  Cosmetic -> SetForceSolid(false);
  //skyBlue -> SetForceWireframe(true);
  Lame_LV -> SetVisAttributes(Cosmetic);



  // //****************************************************************
  // // Gap_under_the_Sample
  // //****************************************************************


  G4ThreeVector Gap_under_the_Sample_S_Size(L_int/2,200*um,l_int/2);

  auto Gap_under_the_Sample_S =  new G4Box("Gap_under_the_Sample_S", 0.5* Gap_under_the_Sample_S_Size.getX(), 0.5*Gap_under_the_Sample_S_Size.getY(),
                                           0.5* Gap_under_the_Sample_S_Size.getZ());

  auto Gap_under_the_Sample_LV = new G4LogicalVolume( Gap_under_the_Sample_S, fGasMaterial,"Gap_under_the_Sample_LV");

  G4double Gap_under_the_Sample = -(e_lame/2+0.5*200*um);

  fGap_under_the_Sample_PV = new G4PVPlacement(0,	//no rotation
    G4ThreeVector(0, (-h_int)/2+d_lame+Gap_under_the_Sample , 0),		//at(0,0,0)
    Gap_under_the_Sample_LV,				//its logical volume
    "Gap_under_the_Sample", 				//its name
    Vol_int_LV, 					//its mother  volume
    false, 						//no boolean operation
    0, 							//copy number
    fCheckOverlaps); 					//overlaps checking


    // Visualisation attributes of the detector
  Cosmetic = new G4VisAttributes( blue);
  Cosmetic -> SetVisibility(true);
  Cosmetic -> SetForceSolid(true);
  //skyBlue -> SetForceWireframe(true);
  Gap_under_the_Sample_LV -> SetVisAttributes(Cosmetic);



  //Build_Detector("NaI");
  
  auto detector_mat = G4Material::GetMaterial("G4_SODIUM_IODIDE"); // NaI = SODIUM_IODIDE Tl à ajouter si besoin
  
  // dimensions utiles

  auto Detector_S = new G4Tubs("Detector_S", 0., r_scint, h_scint/2, 0. * deg, 360. * deg);
  
  auto Detector_LV = new G4LogicalVolume(Detector_S, detector_mat, "Detector_LV");
  
  
  G4ThreeVector positionScint = G4ThreeVector(0,(h_int+e_bas+h_scint)/2+e_cap,0);
  
  fDetector_PV = new G4PVPlacement(rot_scint,  // rotation de 90deg autour de l'axe X
    positionScint,          // position
    Detector_LV,                // its logical volume
    "Detector",                // its name
    worldLV,                  // its mother  volume
    false,                    // no boolean operations
    0,                        // copy number
    fCheckOverlaps);          // checking overlaps


    // Visualisation attributes of the detector
  Cosmetic = new G4VisAttributes( yellow);
  Cosmetic -> SetVisibility(true);
  Cosmetic -> SetForceSolid(true);
  //skyBlue -> SetForceWireframe(true);
  Detector_LV -> SetVisAttributes(Cosmetic);





    //
  // print parameters
  //
//   G4cout
//     << G4endl
//     << "------------------------------------------------------------" << G4endl
//     << "---> The calorimeter is " << nofLayers << " layers of: [ "
//     << absoThickness/mm << "mm of " << absorberMaterial->GetName()
//     << " + "
//     << gapThickness/mm << "mm of " << gapMaterial->GetName() << " ] " << G4endl
//     << "------------------------------------------------------------" << G4endl;
//


  //
  // Always return the physical World
  //
  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::Build_Detector(G4String Name){

  G4cout<<"*********************************detecteur construit*****************************************************"<<G4endl;

  if(Name == "NaI"){

  // *************************************************************************
  // Détecteur Gamma !!! cristal scintillant
  // *************************************************************************

  
  auto detector_mat = G4Material::GetMaterial("G4_SODIUM_IODIDE"); // NaI = SODIUM_IODIDE Tl à ajouter si besoin
  
  // dimensions utiles
  G4double r_scint = 58/2 * mm ;
  G4double h_scint = 250*mm ;
  G4double h_int = 50*mm;
  G4double e_bas = 20*mm ;
  G4double e_cap = 2*mm ;

  auto Detector_S = new G4Tubs("Detector_S", 0., r_scint, h_scint/2, 0. * deg, 360. * deg);
  
  auto Detector_LV = new G4LogicalVolume(Detector_S, detector_mat, "Detector_LV");
  
  G4RotationMatrix* rot_scint = new G4RotationMatrix(); 
  rot_scint->rotateX(90*deg);
  
  G4ThreeVector positionScint = G4ThreeVector(0,(h_int+e_bas+h_scint)/2+e_cap,0);
  
  fDetector_PV = new G4PVPlacement(rot_scint,  // rotation de 90deg autour de l'axe X
    positionScint,          // position
    Detector_LV,                // its logical volume
    "Detector",                // its name
    worldLV,                  // its mother  volume
    false,                    // no boolean operations
    0,                        // copy number
    fCheckOverlaps);          // checking overlaps


    // Visualisation attributes of the detector
  auto Cosmetic = new G4VisAttributes( yellow);
  Cosmetic -> SetVisibility(true);
  Cosmetic -> SetForceSolid(true);
  //skyBlue -> SetForceWireframe(true);
  Detector_LV -> SetVisAttributes(Cosmetic);


  }





}


  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue;
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);

  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}

