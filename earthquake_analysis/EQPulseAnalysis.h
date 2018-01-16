//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Mar 23 23:14:00 2017 by ROOT version 6.04/14
// from TTree pulse/pulse from ascii file
// found on file: ESPOCH_nogps_2016_04_10_12h00v5.root
//////////////////////////////////////////////////////////

#ifndef EQPulseAnalysis_h
#define EQPulseAnalysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TCanvas.h>

#include <iostream>
#include <fstream>
#include <string>

// Header file for the classes stored in the TTree if any.
using namespace std;

class EQPulseAnalysis : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        time;
   ULong64_t       counter;
   Int_t           trigger;
   Int_t           length;
   Int_t           channel1_trace[12];
   Int_t           channel1_peak;
   Int_t           channel1_total_charge;
   Int_t           channel1_charge;
   Float_t         channel1_get_baseline;
   Int_t           channel2_trace[12];
   Int_t           channel2_peak;
   Int_t           channel2_total_charge;
   Int_t           channel2_charge;
   Float_t         channel2_get_baseline;
   Int_t           channel3_trace[12];
   Int_t           channel3_peak;
   Int_t           channel3_total_charge;
   Int_t           channel3_charge;
   Float_t         channel3_get_baseline;

   // List of branches
   TBranch        *b_time;   //!
   TBranch        *b_counter;   //!
   TBranch        *b_trigger;   //!
   TBranch        *b_length;   //!
   TBranch        *b_channel1;   //!
   TBranch        *b_channel2;   //!
   TBranch        *b_channel3;   //!

   EQPulseAnalysis(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~EQPulseAnalysis() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   //Here we can declare all our histograms, etc.
   int i;// para la temperatura y la presion
   int count;// para baseline
   int j;//para la correccion de presion
 
   double unitW;
   int eventsCounter;
   int diffSum,diffSum1,diffSum2,diffSum3,diffSum4;
   double baseAvg;
   double cargaAnterior;
   double cargaNetaAnterior;
   vector<double> presion;
   vector<double> temp;
   vector<double> lluvia;
   vector<double> minutos;
   vector<double> mxarr;
  TH1D* hdiffPico;
  TH1D* hdiffPicoCut1;
  TH1D* hdiffPicoCut2;
  TH1D* hdiffPicoCut3;
  TH1D* hdiffPicoCut4;
  TH1D* CargaNet;
  TH1D* CargaPicoNet;  
  TH1D* CargaPico;
   TH1D* CargaPicoNetCut;  
  TH1D* CargaPicoCut;
  TH1D* CargaPicoNetCut1;  
  TH1D* CargaPicoCut1;
TH1D* CargaPicoNetCut2;  
  TH1D* CargaPicoCut2;
TH1D* CargaPicoNetCut3;  
  TH1D* CargaPicoCut3;
TH1D* CargaPicoNetCut4;  
  TH1D* CargaPicoCut4;
 

  TH1D* Carga_cut;
  TH1D* CargaNet_cut;
   TH1D* h_baseline1;
   TH1D* h_baseline2;
   TH1D* h_baseline_mid;
   TH1D* h_flujoMX;
   TH1D* h_presion2;
   TH1D* h_presion;
   TH1D* h_temp;
   TH1D* h_lluvia;
   TH1F* h_totcharge;
   TH1D* h_time;
   TH1D* h_time_energy_cut;
   TH1D* h_time_segundos;
   TH1D* h_time_minutos;
   TH1D* h_time_horas;
   TH1F* h_totcharge_cut;
   TH1D* h_time_correccion;
   TH1D* h_time_highE;
   TH1D* h_time_blow;
   TH1D* h_time_bhigh;
   TH1D* h_baseline;
   TH1D* h_time_0_604;
   TH1D* h_time_0_608;
   TH1D* h_time_0_612;
   TH1D* h_time_0_616;
   TH1D* h_time_0_690;
   TH1D* h_time_0_620;
   TH1D* h_time_0_640;
   TH1D* h_time_0_660;
   TH1D* h_time_0_680;
   TH1D* h_time_0_600;
   TH1D* h_time_0_700;
   TH1D* h_time_0_800;
   TCanvas* c1;









//////////////////////////////////
TH1D* timeIn;
TH1D* timeOut;
TH1D* timeL;
TH1D* timeT;
TH1D* timeInP;
TH1D* timeOutP;
TH1D* timeLP;
TH1D* timeTP;
TH1D* counterIn;
TH1D* counterOut;
TH1D* counterL;
TH1D* counterT;
TH1D* triggerIn;
TH1D* triggerOut;
TH1D* triggerL;
TH1D* triggerT;
TH1D* tr1In;
TH1D* tr2In;
TH1D* tr3In;
TH1D* tr4In;
TH1D* tr5In;
TH1D* tr6In;
TH1D* tr7In;
TH1D* tr8In;
TH1D* tr9In;
TH1D* tr10In;
TH1D* tr11In;
TH1D* tr12In;
TH1D* tr1Out;
TH1D* tr2Out;
TH1D* tr3Out;
TH1D* tr4Out;
TH1D* tr5Out;
TH1D* tr6Out;
TH1D* tr7Out;
TH1D* tr8Out;
TH1D* tr9Out;
TH1D* tr10Out;
TH1D* tr11Out;
TH1D* tr12Out;
TH1D* tr1L;
TH1D* tr2L;
TH1D* tr3L;
TH1D* tr4L;
TH1D* tr5L;
TH1D* tr6L;
TH1D* tr7L;
TH1D* tr8L;
TH1D* tr9L;
TH1D* tr10L;
TH1D* tr11L;
TH1D* tr12L;
TH1D* tr1T;
TH1D* tr2T;
TH1D* tr3T;
TH1D* tr4T;
TH1D* tr5T;
TH1D* tr6T;
TH1D* tr7T;
TH1D* tr8T;
TH1D* tr9T;
TH1D* tr10T;
TH1D* tr11T;
TH1D* tr12T;
TH1D* lenIn;
TH1D* lenOut;
TH1D* lenL;
TH1D* lenT;
TH1D* peakIn;
TH1D* peakOut;
TH1D* peakL;
TH1D* peakT;
TH1D* chargeIn;
TH1D* chargeOut;
TH1D* chargeL;
TH1D* chargeT;
TH1D* baseIn;
TH1D* baseOut;
TH1D* baseL;
TH1D* baseT;




TH1D* tr1In2;
TH1D* tr2In2;
TH1D* tr3In2;
TH1D* tr4In2;
TH1D* tr5In2;
TH1D* tr6In2;
TH1D* tr7In2;
TH1D* tr8In2;
TH1D* tr9In2;
TH1D* tr10In2;
TH1D* tr11In2;
TH1D* tr12In2;
TH1D* tr1Out2;
TH1D* tr2Out2;
TH1D* tr3Out2;
TH1D* tr4Out2;
TH1D* tr5Out2;
TH1D* tr6Out2;
TH1D* tr7Out2;
TH1D* tr8Out2;
TH1D* tr9Out2;
TH1D* tr10Out2;
TH1D* tr11Out2;
TH1D* tr12Out2;
TH1D* tr1L2;
TH1D* tr2L2;
TH1D* tr3L2;
TH1D* tr4L2;
TH1D* tr5L2;
TH1D* tr6L2;
TH1D* tr7L2;
TH1D* tr8L2;
TH1D* tr9L2;
TH1D* tr10L2;
TH1D* tr11L2;
TH1D* tr12L2;
TH1D* tr1T2;
TH1D* tr2T2;
TH1D* tr3T2;
TH1D* tr4T2;
TH1D* tr5T2;
TH1D* tr6T2;
TH1D* tr7T2;
TH1D* tr8T2;
TH1D* tr9T2;
TH1D* tr10T2;
TH1D* tr11T2;
TH1D* tr12T2;

TH1D* peakIn2;
TH1D* peakOut2;
TH1D* peakL2;
TH1D* peakT2;
TH1D* chargeIn2;
TH1D* chargeOut2;
TH1D* chargeL2;
TH1D* chargeT2;
TH1D* baseIn2;
TH1D* baseOut2;
TH1D* baseL2;
TH1D* baseT2;

//////////////////////////////////
TH1D* valle1;
TH1D* valle2;
TH1D* valle3;
TH1D* valle4;
TH1D* valle5;
TH1D* valle6;
TH1D* valle7;
TH1D* pico1;
TH1D* pico2;
TH1D* pico3;
TH1D* pico4;
TH1D* pico5;
TH1D* pico6;
TH1D* pico7;

TH1D* t1;
TH1D* t2;
TH1D* t3;
TH1D* t4;
TH1D* t5;
TH1D* t6;
TH1D* t7;
TH1D* t8;
TH1D* t9;
TH1D* t10;
TH1D* t11;
TH1D* t12;
TH1D* t13;
TH1D* t14;

/////////////////////////////////////

//////////////////////////////////////////


TH1D* h200;
TH1D* h210;
TH1D* h220;
TH1D* h230;
TH1D* h240;
TH1D* h250;
TH1D* h260;
TH1D* h270;
TH1D* h280;
TH1D* h290;
TH1D* h300;
TH1D* h310;
TH1D* h320;
TH1D* h330;
TH1D* h340;
TH1D* h350;
TH1D* h360;
TH1D* h370;
TH1D* h380;
TH1D* h390;
TH1D* h400;
TH1D* h410;
TH1D* h420;
TH1D* h430;
TH1D* h440;
TH1D* h450;
TH1D* h460;
TH1D* h470;
TH1D* h480;
TH1D* h490;
TH1D* h500;
TH1D* h510;
TH1D* h520;
TH1D* h530;
TH1D* h540;
TH1D* h550;
TH1D* h560;
TH1D* h570;
TH1D* h580;
TH1D* h590;
TH1D* h600;
TH1D* h610;
TH1D* h620;
TH1D* h630;
TH1D* h640;
TH1D* h650;
TH1D* h660;
TH1D* h670;
TH1D* h680;
TH1D* h690;
TH1D* h700;
TH1D* h710;
TH1D* h720;
TH1D* h730;
TH1D* h740;
TH1D* h750;
TH1D* h760;
TH1D* h770;
TH1D* h780;
TH1D* h790;
TH1D* h800;
TH1D* h810;
TH1D* h820;
TH1D* h830;
TH1D* h840;
TH1D* h850;
TH1D* h860;
TH1D* h870;
TH1D* h880;
TH1D* h890;
TH1D* h900;
TH1D* h910;
TH1D* h920;
TH1D* h930;
TH1D* h940;
TH1D* h950;
TH1D* h960;
TH1D* h970;
TH1D* h980;
TH1D* h990;
TH1D* h1000;
TH1D* h1010;
TH1D* h1020;
TH1D* h1030;
TH1D* h1040;
TH1D* h1050;
TH1D* h1060;
TH1D* h1070;
TH1D* h1080;
TH1D* h1090;
TH1D* h1100;
TH1D* h1110;
TH1D* h1120;
TH1D* h1130;
TH1D* h1140;
TH1D* h1150;
TH1D* h1160;
TH1D* h1170;
TH1D* h1180;
TH1D* h1190;
TH1D* h1200;
TH1D* h1210;
TH1D* h1220;
TH1D* h1230;
TH1D* h1240;
TH1D* h1250;
TH1D* h1260;
TH1D* h1270;
TH1D* h1280;
TH1D* h1290;
TH1D* h1300;
TH1D* h1310;
TH1D* h1320;
TH1D* h1330;
TH1D* h1340;
TH1D* h1350;
TH1D* h1360;
TH1D* h1370;
TH1D* h1380;
TH1D* h1390;
TH1D* h1400;
TH1D* h1410;
TH1D* h1420;
TH1D* h1430;
TH1D* h1440;
TH1D* h1450;
TH1D* h1460;
TH1D* h1470;
TH1D* h1480;
TH1D* h1490;
TH1D* h1500;
TH1D* h1510;
TH1D* h1520;
TH1D* h1530;
TH1D* h1540;
TH1D* h1550;
TH1D* h1560;
TH1D* h1570;
TH1D* h1580;
TH1D* h1590;
TH1D* h1600;
TH1D* h1610;
TH1D* h1620;
TH1D* h1630;
TH1D* h1640;
TH1D* h1650;
TH1D* h1660;
TH1D* h1670;
TH1D* h1680;
TH1D* h1690;
TH1D* h1700;
TH1D* h1710;
TH1D* h1720;
TH1D* h1730;
TH1D* h1740;
TH1D* h1750;
TH1D* h1760;
TH1D* h1770;
TH1D* h1780;
TH1D* h1790;
TH1D* h1800;
TH1D* h1810;
TH1D* h1820;
TH1D* h1830;
TH1D* h1840;
TH1D* h1850;
TH1D* h1860;
TH1D* h1870;
TH1D* h1880;
TH1D* h1890;
TH1D* h1900;
TH1D* h1910;
TH1D* h1920;
TH1D* h1930;
TH1D* h1940;
TH1D* h1950;
TH1D* h1960;
TH1D* h1970;
TH1D* h1980;
TH1D* h1990;
TH1D* h2000;

////////////////////////////////////////////////////////////



   TH1D* h_time_cut;
   TH1D* h_time_cut_sup;
   TH1D* h_totcharge_cut_sup;
   TH1D* h_peak;
   TH1D* h_peak2;
   TH1D* h_peak2_cut;
   //TH2D* h2_rate;
   
   //root file for storage
   TFile* myfile;
   
   //This next line needs to be commented out in order to compile the code
   //a la C++
   //  ClassDef(EQPulseAnalysis,0);
};

#endif

#ifdef EQPulseAnalysis_cxx
void EQPulseAnalysis::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("time", &time, &b_time);
   fChain->SetBranchAddress("counter", &counter, &b_counter);
   fChain->SetBranchAddress("trigger", &trigger, &b_trigger);
   fChain->SetBranchAddress("length", &length, &b_length);
   fChain->SetBranchAddress("channel1", channel1_trace, &b_channel1);
   fChain->SetBranchAddress("channel2", channel2_trace, &b_channel2);
   fChain->SetBranchAddress("channel3", channel3_trace, &b_channel3);

   eventsCounter = 0;
   
}

Bool_t EQPulseAnalysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef EQPulseAnalysis_cxx
