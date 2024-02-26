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
  TString filename = "simuCs134.root";
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
  TH1F* hEdep_Detecteur_EdepBeta = new TH1F("hEdep_Detecteur_EdepBeta", "Edep Detecteur with EdepGap>0 ; Edep [MeV] ; Count", 200, 0, 2 );
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

  if (filename == "simuCs134.root") {
    Edep_Min = 0.785;     //pour Cs134 : 796 keV - 11 keV
    Edep_Max = 0.806;     //796 keV + 10 keV
  }

  // Initialisation de compteurs pour le calcul d'efficacité

  long Cpt_Photoelec_Peak = 0;            //compteur du nb d'event dans le pic photoélectrique (autour de 662 keV pour Cs137, autour de 796 keV pour Cs134)
  long Cpt_Photoelec_Peak_coinc_beta = 0; //pareil mais en rajoutant la condition sur la coincidence beta
  long Cpt_tot = 0;                       //compteur du nombre total d'évènements



  while(myReader_det.Next()){
    //         inputTree->GetEntry(i);
    ///////////////////
    // Warning : Vec_Gamma_det_Time is a table. You have to select a position in the table to print the value. By default Vec_Gamma_det_Time is the address of the table.
    // Example :
    // cout << "Vec_Gamma_det_Time value : " << Vec_Gamma_det_Time[0] << "table address "<< Vec_Gamma_det_Time << endl;
    ///////////////////
    
    Cpt_tot+=1;


    float Edep_smear = *Edep ;//**************************** une fois que la fonctione smear sera implémentée, il faudra remplacer par smear(*Edep)


    if(Edep_smear >0){

      cout << " Edep " << Edep_smear << endl;


      if (Edep_smear>Edep_Min && Edep_smear<Edep_Max ) {
        Cpt_Photoelec_Peak +=1;
      }

    }

    hEdep_Detecteur->Fill(Edep_smear);

    int EventID_Detector = *EventID_det;

    while(*EventID< EventID_Detector)myReader.Next();
      
    if(Test >0) cout << "EventID_Detector " << EventID_Detector << "  EventID source " << *EventID << endl;

    if(*Detection_Beta_Gap>0) {

      hEdep_Detecteur_EdepBeta->Fill(Edep_smear);

      if (Edep_smear>Edep_Min && Edep_smear<Edep_Max ) {
        Cpt_Photoelec_Peak_coinc_beta +=1;

      }
    }

    if(myReader.GetCurrentEntry() > 1000 && Test >0) break;
  }


  cout << "**********************************************************" << endl;
  cout << "   Statistiques    " << endl;
  cout << "Compteur pic photoélectrique : " << Cpt_Photoelec_Peak <<" / " << Cpt_tot << " - efficacité 1 = " << Cpt_Photoelec_Peak/(float)Cpt_tot*100 << "%"<< endl;
  cout << "Compteur pic photoélectrique + coincidence beta : " << Cpt_Photoelec_Peak_coinc_beta <<" / " << Cpt_tot << " - efficacité 2 = " << Cpt_Photoelec_Peak_coinc_beta/(float)Cpt_tot*100 << "%"<< endl;
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
  hEdep_Detecteur->Draw("HIST");
  hEdep_Detecteur->SetLineColor(2);
  gPad->SetLogy();

          C_temp->cd(2);
  hEdep_Detecteur_EdepBeta->Draw("same");
    gPad->SetLogy();

          C_temp->cd(3);
 hEdep_Detecteur->Draw("HIST");
  hEdep_Detecteur_EdepBeta->Draw("same");
      gPad->SetLogy();
  gPad->SetGridx();
        gPad->SetGridy();

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
