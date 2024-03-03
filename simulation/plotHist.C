#include <TString.h>
#include <TTree.h>
#include <TFile.h>
#include <TClonesArray.h> 
#include <TROOT.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TVector3.h>
#include <TGraph.h>
#include <TCanvas.h>
#include "TH1F.h"
#include "TH2F.h"
#include "TRandom.h"
#include <iostream>
#include <TF1.h>
#include <TMath.h>

void plotHist()
{
  // TIme of code execution
  TStopwatch timer;
  timer.Start();



  // OPening the root and accessing to the TTree
  TString filename = "simuCs134_10000.root";
  TFile *f = TFile::Open(filename);

  TTree *inputTree = (TTree*) f->Get("Source");
  int nEntries = inputTree->GetEntriesFast();
  cout << "nEntries = " << nEntries << endl; // Nombre de particule lancées

  inputTree->Print(); // Print File informations ~ TBrowser

  /////////////////////////
  // Remarks & Comments
  /*double fMeanX;
   *    double fMeanY;
   *    double fMeanChargeX;
   *    double fMeanChargeY;
   */
  // Changes : fMeanX to meanX[1000] for clarity in order to distinguish between the data and the copy. fMeanX is a table of double.
  // Each value of the table corresponds to an identified cluster. For your analysis you have to select the first cluster -> 0, i.e. meanX[0];
  /////////////////////////
  /*
   *    double meanX[1000];
   *    double meanY[1000];
   *    double meanChargeX[1000];
   *    double meanChargeY[1000];
   *
   *    inputTree->SetBranchAddress("fMeanX",&meanX);
   *    inputTree->SetBranchAddress("fMeanY",&meanY);
   *    inputTree->SetBranchAddress("fMeanChargeX",&meanChargeX);
   *    inputTree->SetBranchAddress("fMeanChargeY",&meanChargeY);*/


  TTreeReader myReader("Source",f);
  TTreeReaderValue<int> EventID(myReader, "EventID");
  TTreeReaderValue<int> Detection_Beta_Gap(myReader, "Detection_Beta_Gap");


  TTreeReaderArray<float> Vec_Gamma_Kinetic(myReader, "Vec_Gamma_Kinetic"); // mean of channel number
  TTreeReaderArray<double> Vec_Gamma_Time(myReader, "Vec_Gamma_Time");
  TTreeReaderArray<double> Vec_Electron_Time(myReader, "Vec_Electron_Time");


  TTreeReader myReader_det("Detector",f);
  TTreeReaderValue<int> EventID_det(myReader_det, "EventID");
  TTreeReaderValue<float> Edep(myReader_det, "Edep");

  TTreeReaderArray<float> vec_Gamma_det_Kinetic(myReader_det, "Vec_Gamma_det_Kinetic"); // mean of channel number
  TTreeReaderArray<double> Vec_Gamma_det_Time(myReader_det, "Vec_Gamma_det_Time");




  //     double meanChargeX; // not necessary
  //     double meanChargeY;


  /////////////////////////
  // Creates a ROOT file to store data
  TFile *outPutFile = new TFile("20220216-164239_Clusterisation_output.root","RECREATE");
  /////////////////////////

  //

  //     TH2F* hxy = new TH2F("hxy", "Scatterplot ; x / mm ; y / mm", 576, -0.5, 575.5, 576, -0.5, 575.5);


  // MeanX or Y is a number of channel. To convert in mm -> Number of channel x 0.4 mm (space between each channel)
  TH1F* hEdep_Detecteur = new TH1F("hEdep_Detecteur", "Edep Detecteur ; Edep [MeV] ; Count", 200, 0, 2 );
  TH1F* hEdep_Detecteur_Smear = new TH1F("hEdep_Detecteur_Smear", "Edep Detecteur with Smear ; Edep [MeV] ; Count", 200, 0, 2 );
  TH1F* hEdep_Detecteur_EdepBeta = new TH1F("hEdep_Detecteur_EdepBeta", "Edep Detecteur with EdepGap>0 ; Edep [MeV] ; Count", 200, 0, 2 );
  TH1F* hEdep_Detecteur_Smear_EdepBeta = new TH1F("hEdep_Detecteur_Smear_EdepBeta", "Edep Detecteur with smear and EdepGap>0 ; Edep [MeV] ; Count", 200, 0, 2 );
  //TH1F* hDelta_temps = new TH1F("hDelta_temps", "Edep Detecteur with EdepGap>0 ; Edep [MeV] ; Count", 200, 0, 2 );

  // Remarks : you can maybe reduce the ROI : see the hxy TCanvas after macro execution
  double upperX = 300.0;
  double lowerX = 200.0;
  double upperY = 450.0;
  double lowerY = 350.0;

  long Cpt_Event_Not_Good = 0;

  int Test = 0; // Test -> 1

  ofstream Fichier_Save("./SaveTxt", ios::out | ios::trunc);

  myReader.Next(); // initialisation evenement source

  // Défition de Edep_Min et Edep_Max :
  // Les bornes de l'intervalle sur laquelle on considère que les évenements sont "dans le pic photoélectrique"
  
  float Edep_Min = 0.650; //pour Cs137 : 662 keV - 12 keV
  float Edep_Max = 0.680; //662 keV + 18 keV

  if (filename == "simuCs134_10000.root") {
    Edep_Min = 0.785;     //pour Cs134 : 796 keV - 11 keV
    Edep_Max = 0.806;     //796 keV + 10 keV
  }

  // Initialisation de compteurs pour le calcul d'efficacité

  long Cpt_Photoelec_Peak = 0;                  //compteur du nb d'event dans le pic photoélectrique (autour de 662 keV pour Cs137, autour de 796 keV pour Cs134)
  long Cpt_Photoelec_Peak_coinc_beta = 0;       //pareil mais en rajoutant la condition sur la coincidence beta
  long Cpt_tot = 0;                             //compteur du nombre total d'évènements
  long Cpt_Photoelec_Peak_smear = 0;            //compteur du nb d'event dans le pic photoelec en prenant en compte la résolution en énergie du detecteur (smear)
  long Cpt_Photoelec_Peak_coinc_beta_smear = 0; //compteur du nb d'event dans le pic photoelec en coincidence avec un beta en prenant en compte la résolution en énergie du detecteur (smear)
  long Cpt_coinc_beta_tps = 0;                  //compteur du nb d'event dans le pic photoelec en coincidence temporelle
  long Cpt_coinc_beta_tps_smear = 0;            //compteur du nb d'event dans le pic photoelec en coincidence temporelle



  while(myReader_det.Next()){
    //         inputTree->GetEntry(i);
    ///////////////////
    // Warning : Vec_Gamma_det_Time is a table. You have to select a position in the table to print the value. By default Vec_Gamma_det_Time is the address of the table.
    // Example :
    // cout << "Vec_Gamma_det_Time value : " << Vec_Gamma_det_Time[0] << "table address "<< Vec_Gamma_det_Time << endl;
    ///////////////////
    
    Cpt_tot+=1;
    
    // comptage pour l'efficacité 1 : pic photoélectrique
    
    if(*Edep >0){

      cout << " Edep " << *Edep << endl;


      if (*Edep>Edep_Min && *Edep<Edep_Max ) {
        Cpt_Photoelec_Peak +=1;
      }

    }

    hEdep_Detecteur->Fill(*Edep);
    
    // Smearing de l'énergie déposée (pour l'efficacité 3) 
    
    Double_t ResolutionEnergy = 0.075; // 7.5%
    Double_t electronicNoise = 0;
//  Double_t electronicNoise = gRandom->Gaus(0.,SigmaNoise()); // MeV // unknown at 20/03/2017  
      
    Double_t energyResNoise = gRandom->Gaus(0.,ResolutionEnergy * *Edep); 
    float Edep_smear = *Edep + electronicNoise + energyResNoise; 

    //comptage de l'efficacité sans coincidence en tenant compte de la résolution en énergie
        
    if(Edep_smear >0){

      cout << " Edep smear " << Edep_smear << endl;


      if (Edep_smear>Edep_Min && Edep_smear<Edep_Max ) {
        Cpt_Photoelec_Peak_smear +=1;
      }

    }
    
    hEdep_Detecteur_Smear->Fill(Edep_smear);
    
    
    int EventID_Detector = *EventID_det;
    
    // comptage du nombre de coincidence avec la detection d'un beta (efficacité 2)

    while(*EventID< EventID_Detector)myReader.Next();
      
    if(Test >0) cout << "EventID_Detector " << EventID_Detector << "  EventID source " << *EventID << endl;

    if(*Detection_Beta_Gap>0) {
    
      hEdep_Detecteur_EdepBeta->Fill(*Edep);
          
      hEdep_Detecteur_Smear_EdepBeta->Fill(Edep_smear);

      if (*Edep>Edep_Min && *Edep<Edep_Max ) {
        Cpt_Photoelec_Peak_coinc_beta +=1;
        // comptage du nombre de coincidences temporelles (efficacité 4)  
        if (Vec_Electron_Time.GetSize()>0 && Vec_Gamma_det_Time.GetSize()>0) {
          long tps_gamma = Vec_Gamma_det_Time[0];
          long tps_beta = Vec_Electron_Time[0];
          float delta_t = (tps_gamma - tps_beta)/1e9;

          cout << "t gamma : "<< tps_gamma << ", t beta : " << tps_beta <<", delta t : " <<  delta_t << endl;
         }

      }
      
      if (Edep_smear>Edep_Min && Edep_smear<Edep_Max ) {
        Cpt_Photoelec_Peak_coinc_beta_smear +=1;

      }
      
      
    }

    if(myReader.GetCurrentEntry() > 1000 && Test >0) break;
  }


  cout << "**********************************************************" << endl;
  cout << "File : "<<filename << endl;
  cout << "   Statistiques    " << endl;
  cout << "Compteur pic photoélectrique : " << Cpt_Photoelec_Peak <<" / " << Cpt_tot << " - efficacité 1 = " << Cpt_Photoelec_Peak/(float)Cpt_tot*100 << "%"<< endl;
  cout << "Compteur pic photoélectrique + coincidence beta : " << Cpt_Photoelec_Peak_coinc_beta <<" / " << Cpt_tot << " - efficacité 2 = " << Cpt_Photoelec_Peak_coinc_beta/(float)Cpt_tot*100 << "%"<< endl;
  cout << "**********************************************************" << endl;
  cout << "   Smear    " << endl;
  cout << "Compteur pic photoélectrique avec smear : " << Cpt_Photoelec_Peak_smear <<" / " << Cpt_tot << " - efficacité 3 = " << Cpt_Photoelec_Peak_smear/(float)Cpt_tot*100 << "%"<< endl;
  cout << "Compteur pic photoélectrique avec smear + coincidence beta : " << Cpt_Photoelec_Peak_coinc_beta_smear <<" / " << Cpt_tot << " - efficacité 4 = " << Cpt_Photoelec_Peak_coinc_beta_smear/(float)Cpt_tot*100 << "%"<< endl;
  //     cout << "   GoodEvent " << nEntries - Cpt_Event_Not_Good << " / " << nEntries  << " ~ " << double(nEntries - Cpt_Event_Not_Good)/(double)nEntries *100 << " %" << endl;
  //     cout << "   NOT GoodEvent " << Cpt_Event_Not_Good << " / " << nEntries  << "    ~ " << double(Cpt_Event_Not_Good)/(double)nEntries *100 << " %" << endl;
  cout << "**********************************************************" << endl;

  ///////////////////
  //     zax->SetMaxDigits(1); // Limit digit

//   auto ptstats= (TPaveStats*)hxy->GetListOfFunctions()->FindObject("stats");
//   ptstats->SetX1NDC(0.665275);
//   ptstats->SetY1NDC(0.551297);
//   ptstats->SetX2NDC(0.865609);
//   ptstats->SetY2NDC(0.851184);

  //     c1->Modified();

  // Implémentation d'une autre manière de compter le nombre d'event dans le pic photoélectrique :
  // A partir de l'histogramme des énergies, à l'aide de la fonction Integral entre nos deux bornes.

  // La fonction Integral prend en entrée des valeurs de bin et non d'énergies
  // Donc il faut commencer par trouver les bin min et max correspondant à nos énergies min et max, à l'aide de FindBin
  int Bin_Min = hEdep_Detecteur->FindBin(Edep_Min);
  int Bin_Max = hEdep_Detecteur->FindBin(Edep_Max);

  double Integral_Edep_Min_Max = hEdep_Detecteur->Integral(Bin_Min, Bin_Max);
  cout << Integral_Edep_Min_Max <<endl;


  //     outPutFile->WriteObject(c1,"c1"); // You can use this option if especially if you use TGraph objects and if you use option like "colz". It's easier to reopen via the TBrowser
  TCanvas* C_temp = new TCanvas("hEdep","hchargex",0,25,1920,1024);
  C_temp->Divide(2,2);

  C_temp->cd(1);
  hEdep_Detecteur->Draw();
  hEdep_Detecteur->SetLineColor(1);
  hEdep_Detecteur_Smear->Draw("same");
  hEdep_Detecteur_Smear->SetLineColor(4);
  gPad->SetLogy();

          C_temp->cd(2);
  hEdep_Detecteur_EdepBeta->Draw();
  hEdep_Detecteur_EdepBeta->SetLineColor(1);
  hEdep_Detecteur_Smear_EdepBeta->Draw("same");
  hEdep_Detecteur_Smear_EdepBeta->SetLineColor(4);
    gPad->SetLogy();

          C_temp->cd(3);
  hEdep_Detecteur->Draw();
  hEdep_Detecteur_EdepBeta->Draw("same");
  hEdep_Detecteur->SetLineColor(4);
  hEdep_Detecteur_EdepBeta->SetLineColor(2);
      gPad->SetLogy();
  gPad->SetGridx();
        gPad->SetGridy();
        
          C_temp->cd(4);
  hEdep_Detecteur_Smear->Draw();
  hEdep_Detecteur_Smear_EdepBeta->Draw("same");
  hEdep_Detecteur_Smear->SetLineColor(3);
  hEdep_Detecteur_Smear_EdepBeta->SetLineColor(6);
      gPad->SetLogy();
  gPad->SetGridx();
        gPad->SetGridy();


//    Black: 1
//    Red: 2
//    Green: 3
//    Blue: 4
//    Yellow: 5
//    Magenta: 6
//    Cyan: 7
//    Orange: 8
//    Spring: 9
//    White: 10
//    Azure: 11
//    Violet: 12
//    Teal: 13
//    Gold: 28
//    Silver: 30
//    Gray: 920


//   outPutFile->WriteObject(c2,"c2");
/*
  TCanvas* c3 = new TCanvas("hchargey","hchargey",0,25,1920,1024);
  c3->cd();
  hchargey->Draw("HIST");
  outPutFile->WriteObject(c3,"c3");
  outPutFile->Write();*/
  ///////////////////

  timer.Stop();
  cout << "**** plotHisto.C , timer" <<endl;
  timer.Print();
}
