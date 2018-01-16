#define EQPulseAnalysis_cxx
// The class definition in EQPulseAnalysis.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("EQPulseAnalysis.C")
// root> T->Process("EQPulseAnalysis.C","some options")
// root> T->Process("EQPulseAnalysis.C+")
//

#include "EQPulseAnalysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <iostream>
#include <fstream>
#include <math.h>

void EQPulseAnalysis::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void EQPulseAnalysis::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   //Define the objects that were declared in the header, and any other
   //object you need
   ifstream fileP;
   ifstream fileT;
   ifstream fileL;
   ifstream tFile;
   ifstream mxFile;
   mxFile.open("flujoMX.lst");
   fileP.open("presion.lst");
   fileL.open("lluvia.lst");
   fileT.open("temperatura.lst");
   tFile.open("time.lst");
   
   double value;
   long int nbin =2556;//falta presion para el corte cargaPico
   long int up, down;
     up = 766800;
     down = 0;
    int c =0;
    int dia = 10;
    count=0;
    j=0;
    diffSum=0;//para la diferencia entre trace y pico
    baseAvg = 0.0;
    cargaAnterior=0.0;
    cargaNetaAnterior=0.0;
    unitW = 1/(pow(1.12,2)*(766800/nbin));
    while ( fileP >> value ) {
       
        presion.push_back(value);
    }
    while(fileT >> value) {
    temp.push_back(value);
    }
    while(fileL>>value){
	lluvia.push_back(value);}
    while(tFile >> value){
	minutos.push_back(value);}
    while (mxFile>>value){
	mxarr.push_back(value*1000);}
   c1 = new TCanvas("c1","hists with different scales",600,400);
  
   myfile = new TFile("lunes03.root","RECREATE");
   hdiffPico = new TH1D("hdiffPico", "Suma dif. Pico",1000, 0,1000);
   hdiffPicoCut1 = new TH1D("hdiffPicoCut1", "Suma dif. Pico1",1000, 0,1000);
   hdiffPicoCut2 = new TH1D("hdiffPicoCut2", "Suma dif. Pico2",1000, 0,1000);
   hdiffPicoCut3 = new TH1D("hdiffPicoCut3", "Suma dif. Pico3",1000, 0,1000);
   hdiffPicoCut4 = new TH1D("hdiffPicoCut4", "Suma dif. Pico4",1000, 0,1000);
   CargaPico = new TH1D("CargaPico", "Carga/Pico",1000,0,100);
   CargaPicoNet = new TH1D("CargaPicoNet", "CargaNet/Pico",1000,-20,100);


   CargaPicoCut1 = new TH1D("CargaPicoCut1", "Carga/Pico cut1",1000,0,100);
   CargaPicoNetCut1 = new TH1D("CargaPicoNetCut1", "CargaNet/Pico cut1",1000,-20,100);
CargaPicoCut2 = new TH1D("CargaPicoCut2", "Carga/Pico cut2",1000,0,100);
   CargaPicoNetCut2 = new TH1D("CargaPicoNetCut2", "CargaNet/Pico cut2",1000,-20,100);
CargaPicoCut3 = new TH1D("CargaPicoCut3", "Carga/Pico cut3",1000,0,100);
   CargaPicoNetCut3 = new TH1D("CargaPicoNetCut3", "CargaNet/Pico cut3",1000,-20,100);
CargaPicoCut4 = new TH1D("CargaPicoCut4", "Carga/Pico cut4",1000,0,100);
   CargaPicoNetCut4 = new TH1D("CargaPicoNetCut4", "CargaNet/Pico cut4",1000,-20,100);

   CargaNet = new TH1D("CargaNet", " Carga neta", 852, -20, 11500);

   h_flujoMX = new TH1D("h_flujoMX", "Flujo de Mexico", nbin,down,up);
   h_baseline = new TH1D("h_baseline", "Baseline",5000,0,450);
  
   h_totcharge = new TH1F("h_totcharge", "Integrated Charge", 852, 0, 11500);
   h_totcharge_cut = new TH1F("h_totcharge_cut", "Integrated Charge_cut", 852, 0, 11500);
   h_time = new TH1D("h_time", "Particle Flux",nbin , down, up);
       h_time->SetMarkerColor(4);
       h_time->SetLineColor(4);
       h_time->SetMarkerSize(0.1);
       h_time->SetMarkerStyle(kFullCircle);
       h_time->GetYaxis()->SetTitle("Particles (m^{-2} s^{-1})");
       h_time->GetYaxis()->CenterTitle();
    
     while(c < nbin){ 
      string r = "April " + to_string(dia);    
      const char* s = r.c_str();
    	 if(c%((nbin/9))==0){
     	  h_time->GetXaxis()->SetBinLabel(c+1, s); dia++;}
         if(c*(766800/nbin)==576000)
          h_time->GetXaxis()->SetBinLabel(c,"Earthquake");
     c++;
}  
    h_time_highE = new TH1D("h_time_highE", "High energy particle Flux",nbin , 0, 766800);
       h_time_highE->SetMarkerColor(28);
       h_time_highE->SetLineColor(28);
       h_time_highE->SetMarkerSize(0.1);
       h_time_highE->SetMarkerStyle(kFullCircle);
       h_time_highE->SetLineWidth(2);
   h_time_blow = new TH1D("h_time_blow", "Low baseline cut",nbin , down, up);
   h_time_bhigh = new TH1D("h_time_bhigh", "High baseline cut",nbin , down, up);
   h_time_segundos = new TH1D("h_time_segundos", "time",766800 , 0, 766800);
   h_time_energy_cut = new TH1D("h_time_energy_cut", "time with E Cut",nbin , down, up);
   h_time_minutos = new TH1D("h_time_minutos", "time",12780 , 0, 766800);
   h_time_horas = new TH1D("h_time_horas", "time",426 , 0, 766800);
   h_time_cut = new TH1D("h_time_cut", "Particle Flux",nbin , 0, 766800);

   h_time_correccion = new TH1D("h_time_correccion", "time_correccion",nbin , 0, 766800);
	h_time_correccion->SetMarkerStyle(kFullCircle);
	h_time_correccion->SetMarkerSize(0.5);
	h_time_correccion->SetLineWidth(2);
	h_time_correccion->SetLineColor(1);
	h_time_correccion->SetMarkerColor(1);
   h_presion = new TH1D ("h_presion","presion", 12780,0,766800);
	h_presion->SetMarkerColor(2);
	h_presion->SetLineColor(2);
	h_presion->SetMarkerSize(0.5);
	h_presion->SetMarkerStyle(kFullCircle);
	h_presion->SetLineWidth(2);
   h_presion2 = new TH1D ("h_presion2","presion2", 12780,0,766800);
	h_presion2->SetMarkerColor(2);
	h_presion2->SetLineColor(2);
	h_presion2->SetMarkerSize(0.5);
	h_presion2->SetMarkerStyle(kFullCircle);
	h_presion2->SetLineWidth(2);
   h_temp = new TH1D ("h_temp","temp",12780,0,766800);
	h_temp->SetMarkerColor(3);
	h_temp->SetLineColor(3);
	h_temp->SetMarkerSize(0.5);
	h_temp->SetMarkerStyle(kFullCircle);
	h_temp->SetLineWidth(2);
   h_lluvia= new TH1D("h_lluvia","Lluvia", 12780,0,766800);
	h_lluvia->SetMarkerColor(1);
	h_lluvia->SetLineColor(1);
	h_lluvia->SetMarkerSize(0.5);
	h_lluvia->SetMarkerStyle(kFullCircle);
	h_lluvia->SetLineWidth(2);
   h_peak = new TH1D("h_peak", "peak",100000 , 0, 1100);
    
     h_time->SetLineWidth(2);
    
   h_peak2 = new TH1D("h_peak2", "peak2",100000 , 0, 1100);
   h_peak2_cut = new TH1D("h_peak2_cut", "peak2_cut",100000 , 0, 1100);
/////////////////////////////////////////////////////////////////////////////////////
 timeIn = new TH1D("timeIn","timeIn",nbin,down,up);
 timeT = new TH1D("timeT","timeT",nbin,down,up);
 timeOut= new TH1D("timeOut","timeOut",nbin,down,up);
 timeL= new TH1D("timeL","timeL",nbin,down,up);
timeInP = new TH1D("timeInP","timeIn pressure corrected",nbin,down,up);
 timeTP = new TH1D("timeTP","timeT pressure corrected",nbin,down,up);
 timeOutP= new TH1D("timeOutP","timeOut pressure corrected",nbin,down,up);
 timeLP= new TH1D("timeLP","timeL pressure corrected",nbin,down,up);
 counterIn= new TH1D("counterIn","counterIn",10,-500000000,14000000000);
 counterOut= new TH1D("counterOut","counterOut",10,-500000000,14000000000);
 counterL= new TH1D("counterL","counterL",10,-500000000,14000000000);
 counterT= new TH1D("counterT","counterT",10,-500000000,14000000000);
 triggerIn= new TH1D("triggerIn","triggerIn",10,-5,5);
 triggerOut= new TH1D("triggerOut","triggerOut",10,-5,5);
 triggerL= new TH1D("triggerL","triggerL",10,-5,5);
 triggerT= new TH1D("triggerT","triggerT",10,-5,5);
 tr1In= new TH1D("tr1In","tr1In",500,-10,1030);
 tr2In= new TH1D("tr2In","tr2In",500,-10,1030);
 tr3In= new TH1D("tr3In","tr3In",500,-10,1030);
 tr4In= new TH1D("tr4In","tr4In",500,-10,1030);
 tr5In= new TH1D("tr5In","tr5In",500,-10,1030);
 tr6In= new TH1D("tr6In","tr6In",500,-10,1030);
 tr7In= new TH1D("tr7In","tr7In",500,-10,1030);
 tr8In= new TH1D("tr8In","tr8In",500,-10,1030);
 tr9In= new TH1D("tr9In","tr9In",500,-10,1030);
 tr10In= new TH1D("tr10In","tr10In",500,-10,1030);
 tr11In= new TH1D("tr11In","tr11In",500,-10,1030);
 tr12In= new TH1D("tr12In","tr12In",500,-10,1030);
 tr1Out= new TH1D("tr1Out","tr1Out",500,-10,1030);
 tr2Out= new TH1D("tr2Out","tr2Out",500,-10,1030);
 tr3Out= new TH1D("tr3Out","tr3Out",500,-10,1030);
 tr4Out= new TH1D("tr4Out","tr4Out",500,-10,1030);
 tr5Out= new TH1D("tr5Out","tr5Out",500,-10,1030);
 tr6Out= new TH1D("tr6Out","tr6Out",500,-10,1030);
 tr7Out= new TH1D("tr7Out","tr7Out",500,-10,1030);
 tr8Out= new TH1D("tr8Out","tr8Out",500,-10,1030);
 tr9Out= new TH1D("tr9Out","tr9Out",500,-10,1030);
 tr10Out= new TH1D("tr10Out","tr10Out",500,-10,1030);
 tr11Out= new TH1D("tr11Out","tr11Out",500,-10,1030);
 tr12Out= new TH1D("tr12Out","tr12Out",500,-10,1030);
 tr1L= new TH1D("tr1L","tr1L",500,-10,1030);
 tr2L= new TH1D("tr2L","tr2L",500,-10,1030);
 tr3L= new TH1D("tr3L","tr3L",500,-10,1030);
 tr4L= new TH1D("tr4L","tr4L",500,-10,1030);
 tr5L= new TH1D("tr5L","tr5L",500,-10,1030);
 tr6L= new TH1D("tr6L","tr6L",500,-10,1030);
 tr7L= new TH1D("tr7L","tr7L",500,-10,1030);
 tr8L= new TH1D("tr8L","tr8L",500,-10,1030);
 tr9L= new TH1D("tr9L","tr9L",500,-10,1030);
 tr10L= new TH1D("tr10L","tr10L",500,-10,1030);
 tr11L= new TH1D("tr11L","tr11L",500,-10,1030);
 tr12L= new TH1D("tr12L","tr12L",500,-10,1030);
 tr1T= new TH1D("tr1T","tr1T",500,-10,1030);
 tr2T= new TH1D("tr2T","tr2T",500,-10,1030);
 tr3T= new TH1D("tr3T","tr3T",500,-10,1030);
 tr4T= new TH1D("tr4T","tr4T",500,-10,1030);
 tr5T= new TH1D("tr5T","tr5T",500,-10,1030);
 tr6T= new TH1D("tr6T","tr6T",500,-10,1030);
 tr7T= new TH1D("tr7T","tr7T",500,-10,1030);
 tr8T= new TH1D("tr8T","tr8T",500,-10,1030);
 tr9T= new TH1D("tr9T","tr9T",500,-10,1030);
 tr10T= new TH1D("tr10T","tr10T",500,-10,1030);
 tr11T= new TH1D("tr11T","tr11T",500,-10,1030);
 tr12T= new TH1D("tr12T","tr12T",500,-10,1030);
 lenIn= new TH1D("lenIn","lenIn",3,5,20);
 lenOut= new TH1D("lenOut","lenOut",3,5,20);
 lenL= new TH1D("lenL","lenL",3,5,20);
 lenT= new TH1D("lenT","lenT",3,5,20);
 peakIn= new TH1D("peakIn","peakIn",500,-20,1030);
 peakOut= new TH1D("peakOut","peakIn",500,-20,1030);
 peakL= new TH1D("peakL","peakL",500,-10,1030);
 peakT= new TH1D("peakT","peakT",500,-10,1030);
 chargeIn= new TH1D("chargeIn","chargeIn",500,0,10000);
 chargeOut= new TH1D("chargeOut","chargeOut",500,0,10000);
 chargeL= new TH1D("chargeL","chargeL",500,0,10000);
 chargeT= new TH1D("chargeT","chargeT",500,0,10000);
 baseIn= new TH1D("baseIn","baseIn",500,0,1000);
 baseOut= new TH1D("baseOut","baseOut",500,0,1000);
 baseL= new TH1D("baseL","baseL",500,0,1000);
 baseT= new TH1D("baseT","baseT",500,0,1000);





tr1In2= new TH1D("tr1In2","tr1In2",500,-10,1030);
 tr2In2= new TH1D("tr2In2","tr2In2",500,-10,1030);
 tr3In2= new TH1D("tr3In2","tr3In2",500,-10,1030);
 tr4In2= new TH1D("tr4In2","tr4In2",500,-10,1030);
 tr5In2= new TH1D("tr5In2","tr5In2",500,-10,1030);
 tr6In2= new TH1D("tr6In2","tr6In2",500,-10,1030);
 tr7In2= new TH1D("tr7In2","tr7In2",500,-10,1030);
 tr8In2= new TH1D("tr8In2","tr8In2",500,-10,1030);
 tr9In2= new TH1D("tr9In2","tr9In2",500,-10,1030);
 tr10In2= new TH1D("tr10In2","tr10In2",500,-10,1030);
 tr11In2= new TH1D("tr11In2","tr11In2",500,-10,1030);
 tr12In2= new TH1D("tr12In2","tr12In2",500,-10,1030);
 tr1Out2= new TH1D("tr1Out2","tr1Out2",500,-10,1030);
 tr2Out2= new TH1D("tr2Out2","tr2Out2",500,-10,1030);
 tr3Out2= new TH1D("tr3Out2","tr3Out2",500,-10,1030);
 tr4Out2= new TH1D("tr4Out2","tr4Out2",500,-10,1030);
 tr5Out2= new TH1D("tr5Out2","tr5Out2",500,-10,1030);
 tr6Out2= new TH1D("tr6Out2","tr6Out2",500,-10,1030);
 tr7Out2= new TH1D("tr7Out2","tr7Out2",500,-10,1030);
 tr8Out2= new TH1D("tr8Out2","tr8Out2",500,-10,1030);
 tr9Out2= new TH1D("tr9Out2","tr9Out2",500,-10,1030);
 tr10Out2= new TH1D("tr10Out2","tr10Out2",500,-10,1030);
 tr11Out2= new TH1D("tr11Out2","tr11Out2",500,-10,1030);
 tr12Out2= new TH1D("tr12Out2","tr12Out2",500,-10,1030);
 tr1L2= new TH1D("tr1L2","tr1L2",500,-10,1030);
 tr2L2= new TH1D("tr2L2","tr2L2",500,-10,1030);
 tr3L2= new TH1D("tr3L2","tr3L2",500,-10,1030);
 tr4L2= new TH1D("tr4L2","tr4L2",500,-10,1030);
 tr5L2= new TH1D("tr5L2","tr5L2",500,-10,1030);
 tr6L2= new TH1D("tr6L2","tr6L2",500,-10,1030);
 tr7L2= new TH1D("tr7L2","tr7L2",500,-10,1030);
 tr8L2= new TH1D("tr8L2","tr8L2",500,-10,1030);
 tr9L2= new TH1D("tr9L2","tr9L2",500,-10,1030);
 tr10L2= new TH1D("tr10L2","tr10L2",500,-10,1030);
 tr11L2= new TH1D("tr11L2","tr11L2",500,-10,1030);
 tr12L2= new TH1D("tr12L2","tr12L2",500,-10,1030);
 tr1T2= new TH1D("tr1T2","tr1T2",500,-10,1030);
 tr2T2= new TH1D("tr2T2","tr2T2",500,-10,1030);
 tr3T2= new TH1D("tr3T2","tr3T2",500,-10,1030);
 tr4T2= new TH1D("tr4T2","tr4T2",500,-10,1030);
 tr5T2= new TH1D("tr5T2","tr5T2",500,-10,1030);
 tr6T2= new TH1D("tr6T2","tr6T2",500,-10,1030);
 tr7T2= new TH1D("tr7T2","tr7T2",500,-10,1030);
 tr8T2= new TH1D("tr8T2","tr8T2",500,-10,1030);
 tr9T2= new TH1D("tr9T2","tr9T2",500,-10,1030);
 tr10T2= new TH1D("tr10T2","tr10T2",500,-10,1030);
 tr11T2= new TH1D("tr11T2","tr11T2",500,-10,1030);
 tr12T2= new TH1D("tr12T2","tr12T2",500,-10,1030);


peakIn2= new TH1D("peakIn2","peakIn2",500,-10,1030);
 peakOut2= new TH1D("peakOut2","peakIn2",500,-10,1030);
 peakL2= new TH1D("peakL2","peakL2",500,-10,1030);
 peakT2= new TH1D("peakT2","peakT2",500,-10,1030);
 chargeIn2= new TH1D("chargeIn2","chargeIn2",500,0,10000);
 chargeOut2= new TH1D("chargeOut2","chargeOut2",500,0,10000);
 chargeL2= new TH1D("chargeL2","chargeL2",500,0,10000);
 chargeT2= new TH1D("chargeT2","chargeT2",500,0,10000);
 baseIn2= new TH1D("baseIn2","baseIn2",500,0,1000);
 baseOut2= new TH1D("baseOut2","baseOut2",500,0,1000);
 baseL2= new TH1D("baseL2","baseL2",500,0,1000);
 baseT2= new TH1D("baseT2","baseT2",500,0,1000);

/////////////////////////////////////////////////////////////////////////////////////
/*valle1 = new TH1D("valle1", "corte1 noche", 852,0,11500);
valle2 = new TH1D("valle2", "corte2 noche", 852,0,11500);
valle3 = new TH1D("valle3", "corte3 noche", 852,0,11500);
valle4 = new TH1D("valle4", "corte4 noche", 852,0,11500);
valle5 = new TH1D("valle5", "corte5 noche", 852,0,11500);
valle6 = new TH1D("valle6", "corte6 noche", 852,0,11500);
valle7 = new TH1D("valle7", "corte7 noche", 852,0,11500);

pico1 = new TH1D("pico1", "corte1 dia", 852,0,11500);
pico2 = new TH1D("pico2", "corte2 dia", 852,0,11500);
pico3 = new TH1D("pico3", "corte3 dia", 852,0,11500);
pico4 = new TH1D("pico4", "corte4 dia", 852,0,11500);
pico5 = new TH1D("pico5", "corte5 dia", 852,0,11500);
pico6 = new TH1D("pico6", "corte6 dia", 852,0,11500);
pico7 = new TH1D("pico7", "corte7 dia", 852,0,11500);


t1 = new TH1D("t1" , "t",nbin , down, up);
t2 = new TH1D("t2" , "t",nbin , down, up);
t3 = new TH1D("t3" , "t",nbin , down, up);
t4 = new TH1D("t4" , "t",nbin , down, up);
t5 = new TH1D("t5" , "t",nbin , down, up);
t6 = new TH1D("t6" , "t",nbin , down, up);
t7 = new TH1D("t7" , "t",nbin , down, up);
t8 = new TH1D("t8" , "t",nbin , down, up);
t9 = new TH1D("t9" , "t",nbin , down, up);
t10 = new TH1D("t10" , "t",nbin , down, up);
t11 = new TH1D("t11" , "t",nbin , down, up);
t12 = new TH1D("t12" , "t",nbin , down, up);
t13 = new TH1D("t13" , "t",nbin , down, up);
t14 = new TH1D("t14" , "t",nbin , down, up);*/


////////////////////////////////////////////////////////////////////////////////////
/*
h200 = new TH1D("h200", "cuts", nbin, down,up);
h210 = new TH1D("h210", "cuts", nbin, down,up);
h220 = new TH1D("h220", "cuts", nbin, down,up);
h230 = new TH1D("h230", "cuts", nbin, down,up);
h240 = new TH1D("h240", "cuts", nbin, down,up);
h250 = new TH1D("h250", "cuts", nbin, down,up);
h260 = new TH1D("h260", "cuts", nbin, down,up);
h270 = new TH1D("h270", "cuts", nbin, down,up);
h280 = new TH1D("h280", "cuts", nbin, down,up);
h290 = new TH1D("h290", "cuts", nbin, down,up);
h300 = new TH1D("h300", "cuts", nbin, down,up);
h310 = new TH1D("h310", "cuts", nbin, down,up);
h320 = new TH1D("h320", "cuts", nbin, down,up);
h330 = new TH1D("h330", "cuts", nbin, down,up);
h340 = new TH1D("h340", "cuts", nbin, down,up);
h350 = new TH1D("h350", "cuts", nbin, down,up);
h360 = new TH1D("h360", "cuts", nbin, down,up);
h370 = new TH1D("h370", "cuts", nbin, down,up);
h380 = new TH1D("h380", "cuts", nbin, down,up);
h390 = new TH1D("h390", "cuts", nbin, down,up);
h400 = new TH1D("h400", "cuts", nbin, down,up);
h410 = new TH1D("h410", "cuts", nbin, down,up);
h420 = new TH1D("h420", "cuts", nbin, down,up);
h430 = new TH1D("h430", "cuts", nbin, down,up);
h440 = new TH1D("h440", "cuts", nbin, down,up);
h450 = new TH1D("h450", "cuts", nbin, down,up);
h460 = new TH1D("h460", "cuts", nbin, down,up);
h470 = new TH1D("h470", "cuts", nbin, down,up);
h480 = new TH1D("h480", "cuts", nbin, down,up);
h490 = new TH1D("h490", "cuts", nbin, down,up);
h500 = new TH1D("h500", "cuts", nbin, down,up);
h510 = new TH1D("h510", "cuts", nbin, down,up);
h520 = new TH1D("h520", "cuts", nbin, down,up);
h530 = new TH1D("h530", "cuts", nbin, down,up);
h540 = new TH1D("h540", "cuts", nbin, down,up);
h550 = new TH1D("h550", "cuts", nbin, down,up);
h560 = new TH1D("h560", "cuts", nbin, down,up);
h570 = new TH1D("h570", "cuts", nbin, down,up);
h580 = new TH1D("h580", "cuts", nbin, down,up);
h590 = new TH1D("h590", "cuts", nbin, down,up);
h600 = new TH1D("h600", "cuts", nbin, down,up);
h610 = new TH1D("h610", "cuts", nbin, down,up);
h620 = new TH1D("h620", "cuts", nbin, down,up);
h630 = new TH1D("h630", "cuts", nbin, down,up);
h640 = new TH1D("h640", "cuts", nbin, down,up);
h650 = new TH1D("h650", "cuts", nbin, down,up);
h660 = new TH1D("h660", "cuts", nbin, down,up);
h670 = new TH1D("h670", "cuts", nbin, down,up);
h680 = new TH1D("h680", "cuts", nbin, down,up);
h690 = new TH1D("h690", "cuts", nbin, down,up);
h700 = new TH1D("h700", "cuts", nbin, down,up);
h710 = new TH1D("h710", "cuts", nbin, down,up);
h720 = new TH1D("h720", "cuts", nbin, down,up);
h730 = new TH1D("h730", "cuts", nbin, down,up);
h740 = new TH1D("h740", "cuts", nbin, down,up);
h750 = new TH1D("h750", "cuts", nbin, down,up);
h760 = new TH1D("h760", "cuts", nbin, down,up);
h770 = new TH1D("h770", "cuts", nbin, down,up);
h780 = new TH1D("h780", "cuts", nbin, down,up);
h790 = new TH1D("h790", "cuts", nbin, down,up);
h800 = new TH1D("h800", "cuts", nbin, down,up);
h810 = new TH1D("h810", "cuts", nbin, down,up);
h820 = new TH1D("h820", "cuts", nbin, down,up);
h830 = new TH1D("h830", "cuts", nbin, down,up);
h840 = new TH1D("h840", "cuts", nbin, down,up);
h850 = new TH1D("h850", "cuts", nbin, down,up);
h860 = new TH1D("h860", "cuts", nbin, down,up);
h870 = new TH1D("h870", "cuts", nbin, down,up);
h880 = new TH1D("h880", "cuts", nbin, down,up);
h890 = new TH1D("h890", "cuts", nbin, down,up);
h900 = new TH1D("h900", "cuts", nbin, down,up);
h910 = new TH1D("h910", "cuts", nbin, down,up);
h920 = new TH1D("h920", "cuts", nbin, down,up);
h930 = new TH1D("h930", "cuts", nbin, down,up);
h940 = new TH1D("h940", "cuts", nbin, down,up);
h950 = new TH1D("h950", "cuts", nbin, down,up);
h960 = new TH1D("h960", "cuts", nbin, down,up);
h970 = new TH1D("h970", "cuts", nbin, down,up);
h980 = new TH1D("h980", "cuts", nbin, down,up);
h990 = new TH1D("h990", "cuts", nbin, down,up);
h1000 = new TH1D("h1000", "cuts", nbin, down,up);
h1010 = new TH1D("h1010", "cuts", nbin, down,up);
h1020 = new TH1D("h1020", "cuts", nbin, down,up);
h1030 = new TH1D("h1030", "cuts", nbin, down,up);
h1040 = new TH1D("h1040", "cuts", nbin, down,up);
h1050 = new TH1D("h1050", "cuts", nbin, down,up);
h1060 = new TH1D("h1060", "cuts", nbin, down,up);
h1070 = new TH1D("h1070", "cuts", nbin, down,up);
h1080 = new TH1D("h1080", "cuts", nbin, down,up);
h1090 = new TH1D("h1090", "cuts", nbin, down,up);
h1100 = new TH1D("h1100", "cuts", nbin, down,up);
h1110 = new TH1D("h1110", "cuts", nbin, down,up);
h1120 = new TH1D("h1120", "cuts", nbin, down,up);
h1130 = new TH1D("h1130", "cuts", nbin, down,up);
h1140 = new TH1D("h1140", "cuts", nbin, down,up);
h1150 = new TH1D("h1150", "cuts", nbin, down,up);
h1160 = new TH1D("h1160", "cuts", nbin, down,up);
h1170 = new TH1D("h1170", "cuts", nbin, down,up);
h1180 = new TH1D("h1180", "cuts", nbin, down,up);
h1190 = new TH1D("h1190", "cuts", nbin, down,up);
h1200 = new TH1D("h1200", "cuts", nbin, down,up);
h1210 = new TH1D("h1210", "cuts", nbin, down,up);
h1220 = new TH1D("h1220", "cuts", nbin, down,up);
h1230 = new TH1D("h1230", "cuts", nbin, down,up);
h1240 = new TH1D("h1240", "cuts", nbin, down,up);
h1250 = new TH1D("h1250", "cuts", nbin, down,up);
h1260 = new TH1D("h1260", "cuts", nbin, down,up);
h1270 = new TH1D("h1270", "cuts", nbin, down,up);
h1280 = new TH1D("h1280", "cuts", nbin, down,up);
h1290 = new TH1D("h1290", "cuts", nbin, down,up);
h1300 = new TH1D("h1300", "cuts", nbin, down,up);
h1310 = new TH1D("h1310", "cuts", nbin, down,up);
h1320 = new TH1D("h1320", "cuts", nbin, down,up);
h1330 = new TH1D("h1330", "cuts", nbin, down,up);
h1340 = new TH1D("h1340", "cuts", nbin, down,up);
h1350 = new TH1D("h1350", "cuts", nbin, down,up);
h1360 = new TH1D("h1360", "cuts", nbin, down,up);
h1370 = new TH1D("h1370", "cuts", nbin, down,up);
h1380 = new TH1D("h1380", "cuts", nbin, down,up);
h1390 = new TH1D("h1390", "cuts", nbin, down,up);
h1400 = new TH1D("h1400", "cuts", nbin, down,up);
h1410 = new TH1D("h1410", "cuts", nbin, down,up);
h1420 = new TH1D("h1420", "cuts", nbin, down,up);
h1430 = new TH1D("h1430", "cuts", nbin, down,up);
h1440 = new TH1D("h1440", "cuts", nbin, down,up);
h1450 = new TH1D("h1450", "cuts", nbin, down,up);
h1460 = new TH1D("h1460", "cuts", nbin, down,up);
h1470 = new TH1D("h1470", "cuts", nbin, down,up);
h1480 = new TH1D("h1480", "cuts", nbin, down,up);
h1490 = new TH1D("h1490", "cuts", nbin, down,up);
h1500 = new TH1D("h1500", "cuts", nbin, down,up);
h1510 = new TH1D("h1510", "cuts", nbin, down,up);
h1520 = new TH1D("h1520", "cuts", nbin, down,up);
h1530 = new TH1D("h1530", "cuts", nbin, down,up);
h1540 = new TH1D("h1540", "cuts", nbin, down,up);
h1550 = new TH1D("h1550", "cuts", nbin, down,up);
h1560 = new TH1D("h1560", "cuts", nbin, down,up);
h1570 = new TH1D("h1570", "cuts", nbin, down,up);
h1580 = new TH1D("h1580", "cuts", nbin, down,up);
h1590 = new TH1D("h1590", "cuts", nbin, down,up);
h1600 = new TH1D("h1600", "cuts", nbin, down,up);
h1610 = new TH1D("h1610", "cuts", nbin, down,up);
h1620 = new TH1D("h1620", "cuts", nbin, down,up);
h1630 = new TH1D("h1630", "cuts", nbin, down,up);
h1640 = new TH1D("h1640", "cuts", nbin, down,up);
h1650 = new TH1D("h1650", "cuts", nbin, down,up);
h1660 = new TH1D("h1660", "cuts", nbin, down,up);
h1670 = new TH1D("h1670", "cuts", nbin, down,up);
h1680 = new TH1D("h1680", "cuts", nbin, down,up);
h1690 = new TH1D("h1690", "cuts", nbin, down,up);
h1700 = new TH1D("h1700", "cuts", nbin, down,up);
h1710 = new TH1D("h1710", "cuts", nbin, down,up);
h1720 = new TH1D("h1720", "cuts", nbin, down,up);
h1730 = new TH1D("h1730", "cuts", nbin, down,up);
h1740 = new TH1D("h1740", "cuts", nbin, down,up);
h1750 = new TH1D("h1750", "cuts", nbin, down,up);
h1760 = new TH1D("h1760", "cuts", nbin, down,up);
h1770 = new TH1D("h1770", "cuts", nbin, down,up);
h1780 = new TH1D("h1780", "cuts", nbin, down,up);
h1790 = new TH1D("h1790", "cuts", nbin, down,up);
h1800 = new TH1D("h1800", "cuts", nbin, down,up);
h1810 = new TH1D("h1810", "cuts", nbin, down,up);
h1820 = new TH1D("h1820", "cuts", nbin, down,up);
h1830 = new TH1D("h1830", "cuts", nbin, down,up);
h1840 = new TH1D("h1840", "cuts", nbin, down,up);
h1850 = new TH1D("h1850", "cuts", nbin, down,up);
h1860 = new TH1D("h1860", "cuts", nbin, down,up);
h1870 = new TH1D("h1870", "cuts", nbin, down,up);
h1880 = new TH1D("h1880", "cuts", nbin, down,up);
h1890 = new TH1D("h1890", "cuts", nbin, down,up);
h1900 = new TH1D("h1900", "cuts", nbin, down,up);
h1910 = new TH1D("h1910", "cuts", nbin, down,up);
h1920 = new TH1D("h1920", "cuts", nbin, down,up);
h1930 = new TH1D("h1930", "cuts", nbin, down,up);
h1940 = new TH1D("h1940", "cuts", nbin, down,up);
h1950 = new TH1D("h1950", "cuts", nbin, down,up);
h1960 = new TH1D("h1960", "cuts", nbin, down,up);
h1970 = new TH1D("h1970", "cuts", nbin, down,up);
h1980 = new TH1D("h1980", "cuts", nbin, down,up);
h1990 = new TH1D("h1990", "cuts", nbin, down,up);
h2000 = new TH1D("h2000", "cuts", nbin, down,up);*/

//////////////////////////////////////////////////////////////////////////





i=0;

   
   //h2_rate = new TH2F("h2_rate","h2_rate",);
   //c1->SetLogy();
}

Bool_t EQPulseAnalysis::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either EQPulseAnalysis::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.
    
    //Get a total count of events
    ++eventsCounter;
    
    //inform about progress (comment out if need for speed)
    if (eventsCounter % 10000000 == 0)
      cout << "Next event -----> " << eventsCounter << endl;

    //Need to get the entry as indicated in the instructions above
    GetEntry(entry);
    //Fill a histogram with the total charge
    //if(channel1_total_charge < 3600 && channel1_total_charge > 1600)
/////////////////////////////////////////////////////////////////////////////////////////////////////////
for(int n =0; n<5; n++){diffSum= diffSum+channel1_peak-channel1_trace[n];}
hdiffPico->Fill(diffSum);
for(int n =0; n<5; n++){diffSum1= diffSum1+channel1_peak-channel1_trace[n];}

for(int n =0; n<5; n++){diffSum2= diffSum2+channel1_peak-channel1_trace[n];}

for(int n =0; n<5; n++){diffSum3= diffSum3+channel1_peak-channel1_trace[n];}

for(int n =0; n<5; n++){diffSum4= diffSum4+channel1_peak-channel1_trace[n];}


CargaPico->Fill((float)channel1_total_charge/channel1_peak);
CargaPicoNet->Fill((float)channel1_charge/(channel1_peak-50));
CargaNet->Fill(channel1_charge);
h_totcharge->Fill(channel1_total_charge);

j= (int)((time-1460257200)/60);//para la correccion de presion
/////////////////////////////////////////////////////////////////////////////////////////////////////////


//if(((float)channel1_total_charge/channel1_peak)>8&&((float)channel1_total_charge/channel1_peak)<=12){

//if(((float)channel1_charge/(channel1_peak-50))>1&&((float)channel1_charge/(channel1_peak-50))<=12){
//if(trigger==1){ 
//if(cargaAnterior<channel1_total_charge){
//if(channel1_trace[3]>=63){
//if(diffSum<90){
if(1==1){
timeIn->Fill(time-1460257200);
timeInP->Fill(time-1460257200,exp(0.05*(presion[j]-729.2289)));

 counterIn->Fill(counter);
 
 triggerIn->Fill(trigger);

 //tr1In->Fill(channel1_trace[0]);
 tr2In->Fill(channel1_trace[1]);
 tr3In->Fill(channel1_trace[2]);
 tr4In->Fill(channel1_trace[3]);
 tr5In->Fill(channel1_trace[4]);
 tr6In->Fill(channel1_trace[5]);
 tr7In->Fill(channel1_trace[6]);
 tr8In->Fill(channel1_trace[7]);
 tr9In->Fill(channel1_trace[8]);
 tr10In->Fill(channel1_trace[9]);
 tr11In->Fill(channel1_trace[10]);
 tr12In->Fill(channel1_trace[11]);


hdiffPicoCut1->Fill(diffSum1);

 
 lenIn->Fill(length);
 
 peakIn->Fill(channel1_charge);
 
 chargeIn->Fill(channel1_total_charge);
 
 baseIn->Fill(channel1_get_baseline);


CargaPicoCut1->Fill((float)channel1_total_charge/channel1_peak);
CargaPicoNetCut1->Fill((float)channel1_charge/(channel1_peak-50));


 tr1In2->Fill(channel2_trace[1]);
 tr2In2->Fill(channel2_trace[2]);
 tr3In2->Fill(channel2_trace[3]);
 tr4In2->Fill(channel2_trace[4]);
 tr5In2->Fill(channel2_trace[5]);
 tr6In2->Fill(channel2_trace[6]);
 tr7In2->Fill(channel2_trace[7]);
 tr8In2->Fill(channel2_trace[8]);
 tr9In2->Fill(channel2_trace[9]);
 tr10In2->Fill(channel2_trace[10]);
 tr11In2->Fill(channel2_trace[11]);
 //tr12In2->Fill(channel2_trace[0]);
 
 peakIn2->Fill(channel2_peak);
 
 chargeIn2->Fill(channel2_total_charge);
 
 baseIn2->Fill(channel2_get_baseline);
 


}

//if(!(channel1_total_charge>650 && channel1_total_charge<850)){\
 timeOut->Fill(time-1460257200);
//if(!(((float)channel1_total_charge/channel1_peak)>8&&((float)channel1_total_charge/channel1_peak)<=12)){
//if(((float)channel1_total_charge/channel1_peak)>8&&((float)channel1_total_charge/channel1_peak)<=12){
if(trigger==1){
//if((cargaAnterior<channel1_total_charge)){
//if(channel1_trace[3]>(channel1_trace[2]-4)){
if(channel1_trace[3]>63){
//if(((float)channel1_charge/(channel1_peak-50))>1&&((float)channel1_charge/(channel1_peak-50))<=12){
// if(diffSum<85){
//if(1==1){ 
timeOut->Fill(time-1460257200);
timeOutP->Fill(time-1460257200,exp(0.002*(presion[j]-729.2289)));
 counterOut->Fill(counter);
 
 triggerOut->Fill(trigger);

 tr1Out->Fill(channel1_trace[1]);
 tr2Out->Fill(channel1_trace[2]);
 tr3Out->Fill(channel1_trace[3]);
 tr4Out->Fill(channel1_trace[4]);
 tr5Out->Fill(channel1_trace[5]);
 tr6Out->Fill(channel1_trace[6]);
 tr7Out->Fill(channel1_trace[7]);
 tr8Out->Fill(channel1_trace[8]);
 tr9Out->Fill(channel1_trace[9]);
 tr10Out->Fill(channel1_trace[10]);
 tr11Out->Fill(channel1_trace[11]);
 //tr12Out->Fill(channel1_trace[0]);
 
 lenOut->Fill(length);
 
 peakOut->Fill(channel1_charge);
 
 chargeOut->Fill(channel1_total_charge);
 
 baseOut->Fill(channel1_get_baseline);
 CargaPicoCut2->Fill((float)channel1_total_charge/channel1_peak);
CargaPicoNetCut2->Fill((float)channel1_charge/(channel1_peak-50));



hdiffPicoCut2->Fill(diffSum2);

tr1Out2->Fill(channel2_trace[1]);
 tr2Out2->Fill(channel2_trace[2]);
 tr3Out2->Fill(channel2_trace[3]);
 tr4Out2->Fill(channel2_trace[4]);
 tr5Out2->Fill(channel2_trace[5]);
 tr6Out2->Fill(channel2_trace[6]);
 tr7Out2->Fill(channel2_trace[7]);
 tr8Out2->Fill(channel2_trace[8]);
 tr9Out2->Fill(channel2_trace[9]);
 tr10Out2->Fill(channel2_trace[10]);
 tr11Out2->Fill(channel2_trace[11]);
 //tr12Out2->Fill(channel2_trace[0]);
 
 peakOut2->Fill(channel2_peak);
 
 chargeOut2->Fill(channel2_total_charge);
 
 baseOut2->Fill(channel2_get_baseline);


}}
//if((channel1_trace[3]>65)){
//if(channel1_total_charge<650 ){
if(((float)channel1_charge/(channel1_peak-50))>2&&((float)channel1_charge/(channel1_peak-50))<=12){
if(trigger==1){
//if(cargaNetaAnterior<channel1_charge){ 
//if(channel1_trace[3]>channel1_trace[2]-10){
//if(channel1_trace[3]>57){
//if(diffSum<80){
//if(1==1){
timeL->Fill(time-1460257200);
timeLP->Fill(time-1460257200,exp(0.02*(presion[j]-729.2289)));
 
 counterL->Fill(counter);
 
 triggerL->Fill(trigger);

 //tr1L->Fill(channel1_trace[0]);
 tr2L->Fill(channel1_trace[1]);
 tr3L->Fill(channel1_trace[2]);
 tr4L->Fill(channel1_trace[3]);
 tr5L->Fill(channel1_trace[4]);
 tr6L->Fill(channel1_trace[5]);
 tr7L->Fill(channel1_trace[6]);
 tr8L->Fill(channel1_trace[7]);
 tr9L->Fill(channel1_trace[8]);
 tr10L->Fill(channel1_trace[9]);
 tr11L->Fill(channel1_trace[10]);
 tr12L->Fill(channel1_trace[11]);
 
 lenL->Fill(length);
 
 peakL->Fill(channel1_peak);
 
 chargeL->Fill(channel1_total_charge);
 hdiffPicoCut3->Fill(diffSum3);
 baseL->Fill(channel1_get_baseline);
 
 //tr1L2->Fill(channel2_trace[0]);
 tr2L2->Fill(channel2_trace[1]);
 tr3L2->Fill(channel2_trace[2]);
 tr4L2->Fill(channel2_trace[3]);
 tr5L2->Fill(channel2_trace[4]);
 tr6L2->Fill(channel2_trace[5]);
 tr7L2->Fill(channel2_trace[6]);
 tr8L2->Fill(channel2_trace[7]);
 tr9L2->Fill(channel2_trace[8]);
 tr10L2->Fill(channel2_trace[9]);
 tr11L2->Fill(channel2_trace[10]);
 tr12L2->Fill(channel2_trace[11]);
 
 peakL2->Fill(channel2_peak);
 
 chargeL2->Fill(channel2_total_charge);
 
 baseL2->Fill(channel2_get_baseline);
CargaPicoCut3->Fill((float)channel1_total_charge/channel1_peak);
CargaPicoNetCut3->Fill((float)channel1_charge/(channel1_peak-50));

}}


 if(  (((float)channel1_charge/(channel1_peak-50))>2.2&&((float)channel1_charge/(channel1_peak-50))<=12)  ){
 if (trigger==1){
//if(channel1_trace[3]>channel1_trace[2]-20){
 //if(diffSum<75){
//if(!(channel1_trace[3]>65)){
timeT->Fill(time-1460257200);
 counterT->Fill(counter);
 
 triggerT->Fill(trigger);

 tr1T->Fill(channel1_trace[1]);
 tr2T->Fill(channel1_trace[2]);
 tr3T->Fill(channel1_trace[3]);
 tr4T->Fill(channel1_trace[4]);
 tr5T->Fill(channel1_trace[5]);
 tr6T->Fill(channel1_trace[6]);
 tr7T->Fill(channel1_trace[7]);
 tr8T->Fill(channel1_trace[8]);
 tr9T->Fill(channel1_trace[9]);
 tr10T->Fill(channel1_trace[10]);
 tr11T->Fill(channel1_trace[11]);
// tr12T->Fill(channel1_trace[0]);
 
 lenT->Fill(length);
 
 peakT->Fill(channel1_peak);
 
 chargeT->Fill(channel1_total_charge);
 
 baseT->Fill(channel1_get_baseline);

hdiffPicoCut4->Fill(diffSum4);
CargaPicoCut4->Fill((float)channel1_total_charge/channel1_peak);
CargaPicoNetCut4->Fill((float)channel1_charge/(channel1_peak-50));

tr1T2->Fill(channel2_trace[1]);
 tr2T2->Fill(channel2_trace[2]);
 tr3T2->Fill(channel2_trace[3]);
 tr4T2->Fill(channel2_trace[4]);
 tr5T2->Fill(channel2_trace[5]);
 tr6T2->Fill(channel2_trace[6]);
 tr7T2->Fill(channel2_trace[7]);
 tr8T2->Fill(channel2_trace[8]);
 tr9T2->Fill(channel2_trace[9]);
 tr10T2->Fill(channel2_trace[10]);
 tr11T2->Fill(channel2_trace[11]);
 //tr12T2->Fill(channel2_trace[0]);
 
 peakT2->Fill(channel2_peak);
 
 chargeT2->Fill(channel2_total_charge);
 
 baseT2->Fill(channel2_get_baseline);
 
}}
cargaAnterior=channel1_total_charge;
cargaNetaAnterior=channel1_charge;
diffSum=0;
diffSum1=0;
diffSum2=0;
diffSum3=0;
diffSum4=0;
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*if((time-1460257200)<115000){valle1->Fill(channel1_total_charge);
t1->Fill(time-1460257200);
}
if((time-1460257200)>170000&&(time-1460257200)<200000){valle2->Fill(channel1_total_charge);
t3->Fill(time-1460257200);
}
if((time-1460257200)>250000&&(time-1460257200)<290000){valle3->Fill(channel1_total_charge);
t5->Fill(time-1460257200);
}
if((time-1460257200)>330000&&(time-1460257200)<375000){valle4->Fill(channel1_total_charge);
t7->Fill(time-1460257200);
}
if((time-1460257200)>425000&&(time-1460257200)<460000){valle5->Fill(channel1_total_charge);
t9->Fill(time-1460257200);
}
if((time-1460257200)>500000&&(time-1460257200)<550000){valle6->Fill(channel1_total_charge);
t11->Fill(time-1460257200);
}
if((time-1460257200)>595000&&(time-1460257200)<635000){valle7->Fill(channel1_total_charge);
t13->Fill(time-1460257200);
}

if((time-1460257200)>115000 && (time-1460257200)<170000){pico1->Fill(channel1_total_charge);
t2->Fill(time-1460257200);
}
if((time-1460257200)>200000 && (time-1460257200)<250000){pico2->Fill(channel1_total_charge);
t4->Fill(time-1460257200);
}
if((time-1460257200)>290000 && (time-1460257200)<330000){pico3->Fill(channel1_total_charge);
t6->Fill(time-1460257200);
}
if((time-1460257200)>375000 && (time-1460257200)<425000){pico4->Fill(channel1_total_charge);
t8->Fill(time-1460257200);
}
if((time-1460257200)>460000 && (time-1460257200)<500000){pico5->Fill(channel1_total_charge);
t10->Fill(time-1460257200);
}
if((time-1460257200)>635000 && (time-1460257200)<680000){pico6->Fill(channel1_total_charge);
t12->Fill(time-1460257200);
}
if((time-1460257200)>720000){pico7->Fill(channel1_total_charge);
t14->Fill(time-1460257200);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
if(channel1_total_charge >0&& channel1_total_charge  <200){h200->Fill(time-1460257200);}
if(channel1_total_charge >10&& channel1_total_charge  <210){h210->Fill(time-1460257200);}
if(channel1_total_charge >20&& channel1_total_charge  <220){h220->Fill(time-1460257200);}
if(channel1_total_charge >30&& channel1_total_charge  <230){h230->Fill(time-1460257200);}
if(channel1_total_charge >40&& channel1_total_charge  <240){h240->Fill(time-1460257200);}
if(channel1_total_charge >50&& channel1_total_charge  <250){h250->Fill(time-1460257200);}
if(channel1_total_charge >60&& channel1_total_charge  <260){h260->Fill(time-1460257200);}
if(channel1_total_charge >70&& channel1_total_charge  <270){h270->Fill(time-1460257200);}
if(channel1_total_charge >80&& channel1_total_charge  <280){h280->Fill(time-1460257200);}
if(channel1_total_charge >90&& channel1_total_charge  <290){h290->Fill(time-1460257200);}
if(channel1_total_charge >100&& channel1_total_charge  <300){h300->Fill(time-1460257200);}
if(channel1_total_charge >110&& channel1_total_charge  <310){h310->Fill(time-1460257200);}
if(channel1_total_charge >120&& channel1_total_charge  <320){h320->Fill(time-1460257200);}
if(channel1_total_charge >130&& channel1_total_charge  <330){h330->Fill(time-1460257200);}
if(channel1_total_charge >140&& channel1_total_charge  <340){h340->Fill(time-1460257200);}
if(channel1_total_charge >150&& channel1_total_charge  <350){h350->Fill(time-1460257200);}
if(channel1_total_charge >160&& channel1_total_charge  <360){h360->Fill(time-1460257200);}
if(channel1_total_charge >170&& channel1_total_charge  <370){h370->Fill(time-1460257200);}
if(channel1_total_charge >180&& channel1_total_charge  <380){h380->Fill(time-1460257200);}
if(channel1_total_charge >190&& channel1_total_charge  <390){h390->Fill(time-1460257200);}
if(channel1_total_charge >200&& channel1_total_charge  <400){h400->Fill(time-1460257200);}
if(channel1_total_charge >210&& channel1_total_charge  <410){h410->Fill(time-1460257200);}
if(channel1_total_charge >220&& channel1_total_charge  <420){h420->Fill(time-1460257200);}
if(channel1_total_charge >230&& channel1_total_charge  <430){h430->Fill(time-1460257200);}
if(channel1_total_charge >240&& channel1_total_charge  <440){h440->Fill(time-1460257200);}
if(channel1_total_charge >250&& channel1_total_charge  <450){h450->Fill(time-1460257200);}
if(channel1_total_charge >260&& channel1_total_charge  <460){h460->Fill(time-1460257200);}
if(channel1_total_charge >270&& channel1_total_charge  <470){h470->Fill(time-1460257200);}
if(channel1_total_charge >280&& channel1_total_charge  <480){h480->Fill(time-1460257200);}
if(channel1_total_charge >290&& channel1_total_charge  <490){h490->Fill(time-1460257200);}
if(channel1_total_charge >300&& channel1_total_charge  <500){h500->Fill(time-1460257200);}
if(channel1_total_charge >310&& channel1_total_charge  <510){h510->Fill(time-1460257200);}
if(channel1_total_charge >320&& channel1_total_charge  <520){h520->Fill(time-1460257200);}
if(channel1_total_charge >330&& channel1_total_charge  <530){h530->Fill(time-1460257200);}
if(channel1_total_charge >340&& channel1_total_charge  <540){h540->Fill(time-1460257200);}
if(channel1_total_charge >350&& channel1_total_charge  <550){h550->Fill(time-1460257200);}
if(channel1_total_charge >360&& channel1_total_charge  <560){h560->Fill(time-1460257200);}
if(channel1_total_charge >370&& channel1_total_charge  <570){h570->Fill(time-1460257200);}
if(channel1_total_charge >380&& channel1_total_charge  <580){h580->Fill(time-1460257200);}
if(channel1_total_charge >390&& channel1_total_charge  <590){h590->Fill(time-1460257200);}
if(channel1_total_charge >400&& channel1_total_charge  <600){h600->Fill(time-1460257200);}
if(channel1_total_charge >410&& channel1_total_charge  <610){h610->Fill(time-1460257200);}
if(channel1_total_charge >420&& channel1_total_charge  <620){h620->Fill(time-1460257200);}
if(channel1_total_charge >430&& channel1_total_charge  <630){h630->Fill(time-1460257200);}
if(channel1_total_charge >440&& channel1_total_charge  <640){h640->Fill(time-1460257200);}
if(channel1_total_charge >450&& channel1_total_charge  <650){h650->Fill(time-1460257200);}
if(channel1_total_charge >460&& channel1_total_charge  <660){h660->Fill(time-1460257200);}
if(channel1_total_charge >470&& channel1_total_charge  <670){h670->Fill(time-1460257200);}
if(channel1_total_charge >480&& channel1_total_charge  <680){h680->Fill(time-1460257200);}
if(channel1_total_charge >490&& channel1_total_charge  <690){h690->Fill(time-1460257200);}
if(channel1_total_charge >500&& channel1_total_charge  <700){h700->Fill(time-1460257200);}
if(channel1_total_charge >510&& channel1_total_charge  <710){h710->Fill(time-1460257200);}
if(channel1_total_charge >520&& channel1_total_charge  <720){h720->Fill(time-1460257200);}
if(channel1_total_charge >530&& channel1_total_charge  <730){h730->Fill(time-1460257200);}
if(channel1_total_charge >540&& channel1_total_charge  <740){h740->Fill(time-1460257200);}
if(channel1_total_charge >550&& channel1_total_charge  <750){h750->Fill(time-1460257200);}
if(channel1_total_charge >560&& channel1_total_charge  <760){h760->Fill(time-1460257200);}
if(channel1_total_charge >570&& channel1_total_charge  <770){h770->Fill(time-1460257200);}
if(channel1_total_charge >580&& channel1_total_charge  <780){h780->Fill(time-1460257200);}
if(channel1_total_charge >590&& channel1_total_charge  <790){h790->Fill(time-1460257200);}
if(channel1_total_charge >600&& channel1_total_charge  <800){h800->Fill(time-1460257200);}
if(channel1_total_charge >610&& channel1_total_charge  <810){h810->Fill(time-1460257200);}
if(channel1_total_charge >620&& channel1_total_charge  <820){h820->Fill(time-1460257200);}
if(channel1_total_charge >630&& channel1_total_charge  <830){h830->Fill(time-1460257200);}
if(channel1_total_charge >640&& channel1_total_charge  <840){h840->Fill(time-1460257200);}


if(channel1_total_charge >650&& channel1_total_charge  <850){h850->Fill(time-1460257200,exp(0.003*(presion[j]-729.2289)));}
j= (int)((time-1460257200)/60);

if(channel1_total_charge >650&& channel1_total_charge  <850){h860->Fill(time-1460257200);}
if(channel1_total_charge >670&& channel1_total_charge  <870){h870->Fill(time-1460257200);}
if(channel1_total_charge >680&& channel1_total_charge  <880){h880->Fill(time-1460257200);}
if(channel1_total_charge >690&& channel1_total_charge  <890){h890->Fill(time-1460257200);}
if(channel1_total_charge >700&& channel1_total_charge  <900){h900->Fill(time-1460257200);}
if(channel1_total_charge >710&& channel1_total_charge  <910){h910->Fill(time-1460257200);}
if(channel1_total_charge >720&& channel1_total_charge  <920){h920->Fill(time-1460257200);}
if(channel1_total_charge >730&& channel1_total_charge  <930){h930->Fill(time-1460257200);}
if(channel1_total_charge >740&& channel1_total_charge  <940){h940->Fill(time-1460257200);}
if(channel1_total_charge >750&& channel1_total_charge  <950){h950->Fill(time-1460257200);}
if(channel1_total_charge >760&& channel1_total_charge  <960){h960->Fill(time-1460257200);}
if(channel1_total_charge >770&& channel1_total_charge  <970){h970->Fill(time-1460257200);}
if(channel1_total_charge >780&& channel1_total_charge  <980){h980->Fill(time-1460257200);}
if(channel1_total_charge >790&& channel1_total_charge  <990){h990->Fill(time-1460257200);}
if(channel1_total_charge >800&& channel1_total_charge  <1000){h1000->Fill(time-1460257200);}
if(channel1_total_charge >810&& channel1_total_charge  <1010){h1010->Fill(time-1460257200);}
if(channel1_total_charge >820&& channel1_total_charge  <1020){h1020->Fill(time-1460257200);}
if(channel1_total_charge >830&& channel1_total_charge  <1030){h1030->Fill(time-1460257200);}
if(channel1_total_charge >840&& channel1_total_charge  <1040){h1040->Fill(time-1460257200);}
if(channel1_total_charge >850&& channel1_total_charge  <1050){h1050->Fill(time-1460257200);}
if(channel1_total_charge >860&& channel1_total_charge  <1060){h1060->Fill(time-1460257200);}
if(channel1_total_charge >870&& channel1_total_charge  <1070){h1070->Fill(time-1460257200);}
if(channel1_total_charge >880&& channel1_total_charge  <1080){h1080->Fill(time-1460257200);}
if(channel1_total_charge >890&& channel1_total_charge  <1090){h1090->Fill(time-1460257200);}
if(channel1_total_charge >900&& channel1_total_charge  <1100){h1100->Fill(time-1460257200);}
if(channel1_total_charge >910&& channel1_total_charge  <1110){h1110->Fill(time-1460257200);}
if(channel1_total_charge >920&& channel1_total_charge  <1120){h1120->Fill(time-1460257200);}
if(channel1_total_charge >930&& channel1_total_charge  <1130){h1130->Fill(time-1460257200);}
if(channel1_total_charge >940&& channel1_total_charge  <1140){h1140->Fill(time-1460257200);}
if(channel1_total_charge >950&& channel1_total_charge  <1150){h1150->Fill(time-1460257200);}
if(channel1_total_charge >960&& channel1_total_charge  <1160){h1160->Fill(time-1460257200);}
if(channel1_total_charge >970&& channel1_total_charge  <1170){h1170->Fill(time-1460257200);}
if(channel1_total_charge >980&& channel1_total_charge  <1180){h1180->Fill(time-1460257200);}
if(channel1_total_charge >990&& channel1_total_charge  <1190){h1190->Fill(time-1460257200);}
if(channel1_total_charge >1000&& channel1_total_charge  <1200){h1200->Fill(time-1460257200);}
if(channel1_total_charge >1010&& channel1_total_charge  <1210){h1210->Fill(time-1460257200);}
if(channel1_total_charge >1020&& channel1_total_charge  <1220){h1220->Fill(time-1460257200);}
if(channel1_total_charge >1030&& channel1_total_charge  <1230){h1230->Fill(time-1460257200);}
if(channel1_total_charge >1040&& channel1_total_charge  <1240){h1240->Fill(time-1460257200);}
if(channel1_total_charge >1050&& channel1_total_charge  <1250){h1250->Fill(time-1460257200);}
if(channel1_total_charge >1060&& channel1_total_charge  <1260){h1260->Fill(time-1460257200);}
if(channel1_total_charge >1070&& channel1_total_charge  <1270){h1270->Fill(time-1460257200);}
if(channel1_total_charge >1080&& channel1_total_charge  <1280){h1280->Fill(time-1460257200);}
if(channel1_total_charge >1090&& channel1_total_charge  <1290){h1290->Fill(time-1460257200);}
if(channel1_total_charge >1100&& channel1_total_charge  <1300){h1300->Fill(time-1460257200);}
if(channel1_total_charge >1110&& channel1_total_charge  <1310){h1310->Fill(time-1460257200);}
if(channel1_total_charge >1120&& channel1_total_charge  <1320){h1320->Fill(time-1460257200);}
if(channel1_total_charge >1130&& channel1_total_charge  <1330){h1330->Fill(time-1460257200);}
if(channel1_total_charge >1140&& channel1_total_charge  <1340){h1340->Fill(time-1460257200);}
if(channel1_total_charge >1150&& channel1_total_charge  <1350){h1350->Fill(time-1460257200);}
if(channel1_total_charge >1160&& channel1_total_charge  <1360){h1360->Fill(time-1460257200);}
if(channel1_total_charge >1170&& channel1_total_charge  <1370){h1370->Fill(time-1460257200);}
if(channel1_total_charge >1180&& channel1_total_charge  <1380){h1380->Fill(time-1460257200);}
if(channel1_total_charge >1190&& channel1_total_charge  <1390){h1390->Fill(time-1460257200);}
if(channel1_total_charge >1200&& channel1_total_charge  <1400){h1400->Fill(time-1460257200);}
if(channel1_total_charge >1210&& channel1_total_charge  <1410){h1410->Fill(time-1460257200);}
if(channel1_total_charge >1220&& channel1_total_charge  <1420){h1420->Fill(time-1460257200);}
if(channel1_total_charge >1230&& channel1_total_charge  <1430){h1430->Fill(time-1460257200);}
if(channel1_total_charge >1240&& channel1_total_charge  <1440){h1440->Fill(time-1460257200);}
if(channel1_total_charge >1250&& channel1_total_charge  <1450){h1450->Fill(time-1460257200);}
if(channel1_total_charge >1260&& channel1_total_charge  <1460){h1460->Fill(time-1460257200);}
if(channel1_total_charge >1270&& channel1_total_charge  <1470){h1470->Fill(time-1460257200);}
if(channel1_total_charge >1280&& channel1_total_charge  <1480){h1480->Fill(time-1460257200);}
if(channel1_total_charge >1290&& channel1_total_charge  <1490){h1490->Fill(time-1460257200);}
if(channel1_total_charge >1300&& channel1_total_charge  <1500){h1500->Fill(time-1460257200);}
if(channel1_total_charge >1310&& channel1_total_charge  <1510){h1510->Fill(time-1460257200);}
if(channel1_total_charge >1320&& channel1_total_charge  <1520){h1520->Fill(time-1460257200);}
if(channel1_total_charge >1330&& channel1_total_charge  <1530){h1530->Fill(time-1460257200);}
if(channel1_total_charge >1340&& channel1_total_charge  <1540){h1540->Fill(time-1460257200);}
if(channel1_total_charge >1350&& channel1_total_charge  <1550){h1550->Fill(time-1460257200);}
if(channel1_total_charge >1360&& channel1_total_charge  <1560){h1560->Fill(time-1460257200);}
if(channel1_total_charge >1370&& channel1_total_charge  <1570){h1570->Fill(time-1460257200);}
if(channel1_total_charge >1380&& channel1_total_charge  <1580){h1580->Fill(time-1460257200);}
if(channel1_total_charge >1390&& channel1_total_charge  <1590){h1590->Fill(time-1460257200);}
if(channel1_total_charge >1400&& channel1_total_charge  <1600){h1600->Fill(time-1460257200);}
if(channel1_total_charge >1410&& channel1_total_charge  <1610){h1610->Fill(time-1460257200);}
if(channel1_total_charge >1420&& channel1_total_charge  <1620){h1620->Fill(time-1460257200);}
if(channel1_total_charge >1430&& channel1_total_charge  <1630){h1630->Fill(time-1460257200);}
if(channel1_total_charge >1440&& channel1_total_charge  <1640){h1640->Fill(time-1460257200);}
if(channel1_total_charge >1450&& channel1_total_charge  <1650){h1650->Fill(time-1460257200);}
if(channel1_total_charge >1460&& channel1_total_charge  <1660){h1660->Fill(time-1460257200);}
if(channel1_total_charge >1470&& channel1_total_charge  <1670){h1670->Fill(time-1460257200);}
if(channel1_total_charge >1480&& channel1_total_charge  <1680){h1680->Fill(time-1460257200);}
if(channel1_total_charge >1490&& channel1_total_charge  <1690){h1690->Fill(time-1460257200);}
if(channel1_total_charge >1500&& channel1_total_charge  <1700){h1700->Fill(time-1460257200);}
if(channel1_total_charge >1510&& channel1_total_charge  <1710){h1710->Fill(time-1460257200);}
if(channel1_total_charge >1520&& channel1_total_charge  <1720){h1720->Fill(time-1460257200);}
if(channel1_total_charge >1530&& channel1_total_charge  <1730){h1730->Fill(time-1460257200);}
if(channel1_total_charge >1540&& channel1_total_charge  <1740){h1740->Fill(time-1460257200);}
if(channel1_total_charge >1550&& channel1_total_charge  <1750){h1750->Fill(time-1460257200);}
if(channel1_total_charge >1560&& channel1_total_charge  <1760){h1760->Fill(time-1460257200);}
if(channel1_total_charge >1570&& channel1_total_charge  <1770){h1770->Fill(time-1460257200);}
if(channel1_total_charge >1580&& channel1_total_charge  <1780){h1780->Fill(time-1460257200);}
if(channel1_total_charge >1590&& channel1_total_charge  <1790){h1790->Fill(time-1460257200);}
if(channel1_total_charge >1600&& channel1_total_charge  <1800){h1800->Fill(time-1460257200);}
if(channel1_total_charge >1610&& channel1_total_charge  <1810){h1810->Fill(time-1460257200);}
if(channel1_total_charge >1620&& channel1_total_charge  <1820){h1820->Fill(time-1460257200);}
if(channel1_total_charge >1630&& channel1_total_charge  <1830){h1830->Fill(time-1460257200);}
if(channel1_total_charge >1640&& channel1_total_charge  <1840){h1840->Fill(time-1460257200);}
if(channel1_total_charge >1650&& channel1_total_charge  <1850){h1850->Fill(time-1460257200);}
if(channel1_total_charge >1660&& channel1_total_charge  <1860){h1860->Fill(time-1460257200);}
if(channel1_total_charge >1670&& channel1_total_charge  <1870){h1870->Fill(time-1460257200);}
if(channel1_total_charge >1680&& channel1_total_charge  <1880){h1880->Fill(time-1460257200);}
if(channel1_total_charge >1690&& channel1_total_charge  <1890){h1890->Fill(time-1460257200);}
if(channel1_total_charge >1700&& channel1_total_charge  <1900){h1900->Fill(time-1460257200);}
if(channel1_total_charge >1710&& channel1_total_charge  <1910){h1910->Fill(time-1460257200);}
if(channel1_total_charge >1720&& channel1_total_charge  <1920){h1920->Fill(time-1460257200);}
if(channel1_total_charge >1730&& channel1_total_charge  <1930){h1930->Fill(time-1460257200);}
if(channel1_total_charge >1740&& channel1_total_charge  <1940){h1940->Fill(time-1460257200);}
if(channel1_total_charge >1750&& channel1_total_charge  <1950){h1950->Fill(time-1460257200);}
if(channel1_total_charge >1760&& channel1_total_charge  <1960){h1960->Fill(time-1460257200);}
if(channel1_total_charge >1770&& channel1_total_charge  <1970){h1970->Fill(time-1460257200);}
if(channel1_total_charge >1780&& channel1_total_charge  <1980){h1980->Fill(time-1460257200);}
if(channel1_total_charge >1790&& channel1_total_charge  <1990){h1990->Fill(time-1460257200);}
if(channel1_total_charge >1800&& channel1_total_charge  <2000){h2000->Fill(time-1460257200);}
//////////////////////////////////////////////////*/




if(i<12780){
	float pres =(-presion[i]+727)*(300/48)+313;
        
	// pres= ((pres -285)*160)+16000;
	h_temp->Fill(i*60, (temp[i]-11)*(230/8) +270);
	h_presion->Fill(i*60,((732.01-presion[i])*(25.0/6.8333))+80);
	h_presion2->Fill(i*60,((pres -285)*320)+136000);
	h_lluvia->Fill(i*60, lluvia[i]*5*400);
	h_flujoMX->Fill(i*60, mxarr[i]);
     
              i++; }
  /* if((((int)time-1460257200)%3600)==0&&i<213){
    h_temp->Fill(i*3600,(570000+(temp[i]-10)*60000)*unitW);
    h_presion->Fill(i*3600,unitW*2.3*(presion[i]-721)*52174);
   
    i++;}*/
    
   
    h_baseline->Fill(channel1_get_baseline);
  

    

if (  (!( (time-1460257200) >=33423 && (time-1460257200) <= 33424))&& (!( (time-1460257200) >=33607 && (time-1460257200) <= 33608))&& (!( (time-1460257200) >=36030 && (time-1460257200) <= 36031))&& (!( (time-1460257200) >=36527 && (time-1460257200) <= 36528))&& (!( (time-1460257200) >=50327 && (time-1460257200) <= 50328))&& (!( (time-1460257200) >=51643 && (time-1460257200) <= 51644))&& (!( (time-1460257200) >=51820 && (time-1460257200) <= 51821))&& (!( (time-1460257200) >=52141 && (time-1460257200) <= 52142))&& (!( (time-1460257200) >=54280 && (time-1460257200) <= 54281))&& (!( (time-1460257200) >=118949 && (time-1460257200) <= 118950))&& (!( (time-1460257200) >=118958 && (time-1460257200) <= 118959))&& (!( (time-1460257200) >=118959 && (time-1460257200) <= 118960))&& (!( (time-1460257200) >=118960 && (time-1460257200) <= 118961))&& (!( (time-1460257200) >=126513 && (time-1460257200) <= 126514))&& (!( (time-1460257200) >=126520 && (time-1460257200) <= 126521))&& (!( (time-1460257200) >=132243 && (time-1460257200) <= 132244))&& (!( (time-1460257200) >=133508 && (time-1460257200) <= 133509))&& (!( (time-1460257200) >=135438 && (time-1460257200) <= 135439))&& (!( (time-1460257200) >=135439 && (time-1460257200) <= 135440))&& (!( (time-1460257200) >=135440 && (time-1460257200) <= 135441))&& (!( (time-1460257200) >=138545 && (time-1460257200) <= 138546))&& (!( (time-1460257200) >=139346 && (time-1460257200) <= 139347))&& (!( (time-1460257200) >=140898 && (time-1460257200) <= 140899))&& (!( (time-1460257200) >=142658 && (time-1460257200) <= 142659))&& (!( (time-1460257200) >=142659 && (time-1460257200) <= 142660))&& (!( (time-1460257200) >=149210 && (time-1460257200) <= 149211))&& (!( (time-1460257200) >=151935 && (time-1460257200) <= 151936))&& (!( (time-1460257200) >=153189 && (time-1460257200) <= 153190))&& (!( (time-1460257200) >=153190 && (time-1460257200) <= 153191))&& (!( (time-1460257200) >=153191 && (time-1460257200) <= 153192))&& (!( (time-1460257200) >=153192 && (time-1460257200) <= 153193))&& (!( (time-1460257200) >=153193 && (time-1460257200) <= 153194))&& (!( (time-1460257200) >=174988 && (time-1460257200) <= 174989))&& (!( (time-1460257200) >=207947 && (time-1460257200) <= 207948))&& (!( (time-1460257200) >=209028 && (time-1460257200) <= 209029))&& (!( (time-1460257200) >=209758 && (time-1460257200) <= 209759))&& (!( (time-1460257200) >=209759 && (time-1460257200) <= 209760))&& (!( (time-1460257200) >=209760 && (time-1460257200) <= 209761))&& (!( (time-1460257200) >=210154 && (time-1460257200) <= 210155))&& (!( (time-1460257200) >=211955 && (time-1460257200) <= 211956))&& (!( (time-1460257200) >=216907 && (time-1460257200) <= 216908))&& (!( (time-1460257200) >=217955 && (time-1460257200) <= 217956))&& (!( (time-1460257200) >=222946 && (time-1460257200) <= 222947))&& (!( (time-1460257200) >=223307 && (time-1460257200) <= 223308))&& (!( (time-1460257200) >=230751 && (time-1460257200) <= 230752))&& (!( (time-1460257200) >=230752 && (time-1460257200) <= 230753))&& (!( (time-1460257200) >=246894 && (time-1460257200) <= 246895))&& (!( (time-1460257200) >=246895 && (time-1460257200) <= 246896))&& (!( (time-1460257200) >=291547 && (time-1460257200) <= 291548))&& (!( (time-1460257200) >=296054 && (time-1460257200) <= 296055))&& (!( (time-1460257200) >=296055 && (time-1460257200) <= 296056))&& (!( (time-1460257200) >=310247 && (time-1460257200) <= 310248))&& (!( (time-1460257200) >=317502 && (time-1460257200) <= 317503))&& (!( (time-1460257200) >=378589 && (time-1460257200) <= 378590))&& (!( (time-1460257200) >=378590 && (time-1460257200) <= 378591))&& (!( (time-1460257200) >=379936 && (time-1460257200) <= 379937))&& (!( (time-1460257200) >=399332 && (time-1460257200) <= 399333))&& (!( (time-1460257200) >=399580 && (time-1460257200) <= 399581))&& (!( (time-1460257200) >=400869 && (time-1460257200) <= 400870))&& (!( (time-1460257200) >=401571 && (time-1460257200) <= 401572))&& (!( (time-1460257200) >=419276 && (time-1460257200) <= 419277))&& (!( (time-1460257200) >=419277 && (time-1460257200) <= 419278))&& (!( (time-1460257200) >=467976 && (time-1460257200) <= 467977))&& (!( (time-1460257200) >=489345 && (time-1460257200) <= 489346))&& (!( (time-1460257200) >=489504 && (time-1460257200) <= 489505))&& (!( (time-1460257200) >=513625 && (time-1460257200) <= 513626))&& (!( (time-1460257200) >=514946 && (time-1460257200) <= 514947))&& (!( (time-1460257200) >=515040 && (time-1460257200) <= 515041))&& (!( (time-1460257200) >=555774 && (time-1460257200) <= 555775))&& (!( (time-1460257200) >=555775 && (time-1460257200) <= 555776))&& (!( (time-1460257200) >=565632 && (time-1460257200) <= 565633))&& (!( (time-1460257200) >=723769 && (time-1460257200) <= 723770))&& (!( (time-1460257200) >=747535 && (time-1460257200) <= 747536))&& (!( (time-1460257200) >=747536 && (time-1460257200) <= 747537))&& (!( (time-1460257200) >=747537 && (time-1460257200) <= 747538)) ){
  /*if(channel1_total_charge<610){  
	h_time_correccion->Fill(time-1460257200, unitW);}*/
    
   /* h_time_horas->Fill(time-1460257200);
    h_time_minutos->Fill(time-1460257200);*/
  
  //h_time_correccion->Fill(time-1460257200, ((float)unitW)*exp(5.7*(presion[j]-729.2289)));
   //j= (int)((time-1460257200)/60);


}

if (  (( (time-1460257200) >=33423.0 && (time-1460257200) <= 33424.0))|| (( (time-1460257200) >=33607.0 && (time-1460257200) <= 33608.0))|| (( (time-1460257200) >=36030.0 && (time-1460257200) <= 36031.0))|| (( (time-1460257200) >=36527.0 && (time-1460257200) <= 36528.0))|| (( (time-1460257200) >=50327.0 && (time-1460257200) <= 50328.0))|| (( (time-1460257200) >=51643.0 && (time-1460257200) <= 51644.0))|| (( (time-1460257200) >=51820.0 && (time-1460257200) <= 51821.0))|| (( (time-1460257200) >=52141.0 && (time-1460257200) <= 52142.0))|| (( (time-1460257200) >=54280.0 && (time-1460257200) <= 54281.0))|| (( (time-1460257200) >=118949.0 && (time-1460257200) <= 118950.0))|| (( (time-1460257200) >=118958.0 && (time-1460257200) <= 118959.0))|| (( (time-1460257200) >=118959.0 && (time-1460257200) <= 118960.0))|| (( (time-1460257200) >=118960.0 && (time-1460257200) <= 118961.0))|| (( (time-1460257200) >=126513.0 && (time-1460257200) <= 126514.0))|| (( (time-1460257200) >=126520.0 && (time-1460257200) <= 126521.0))|| (( (time-1460257200) >=132243.0 && (time-1460257200) <= 132244.0))|| (( (time-1460257200) >=133508.0 && (time-1460257200) <= 133509.0))|| (( (time-1460257200) >=135438.0 && (time-1460257200) <= 135439.0))|| (( (time-1460257200) >=135439.0 && (time-1460257200) <= 135440.0))|| (( (time-1460257200) >=135440.0 && (time-1460257200) <= 135441.0))|| (( (time-1460257200) >=138545.0 && (time-1460257200) <= 138546.0))|| (( (time-1460257200) >=139346.0 && (time-1460257200) <= 139347.0))|| (( (time-1460257200) >=140898.0 && (time-1460257200) <= 140899.0))|| (( (time-1460257200) >=142658.0 && (time-1460257200) <= 142659.0))|| (( (time-1460257200) >=142659.0 && (time-1460257200) <= 142660.0))|| (( (time-1460257200) >=149210.0 && (time-1460257200) <= 149211.0))|| (( (time-1460257200) >=151935.0 && (time-1460257200) <= 151936.0))|| (( (time-1460257200) >=153189.0 && (time-1460257200) <= 153190.0))|| (( (time-1460257200) >=153190.0 && (time-1460257200) <= 153191.0))|| (( (time-1460257200) >=153191.0 && (time-1460257200) <= 153192.0))|| (( (time-1460257200) >=153192.0 && (time-1460257200) <= 153193.0))|| (( (time-1460257200) >=153193.0 && (time-1460257200) <= 153194.0))|| (( (time-1460257200) >=174988.0 && (time-1460257200) <= 174989.0))|| (( (time-1460257200) >=207947.0 && (time-1460257200) <= 207948.0))|| (( (time-1460257200) >=209028.0 && (time-1460257200) <= 209029.0))|| (( (time-1460257200) >=209758.0 && (time-1460257200) <= 209759.0))|| (( (time-1460257200) >=209759.0 && (time-1460257200) <= 209760.0))|| (( (time-1460257200) >=209760.0 && (time-1460257200) <= 209761.0))|| (( (time-1460257200) >=210154.0 && (time-1460257200) <= 210155.0))|| (( (time-1460257200) >=211955.0 && (time-1460257200) <= 211956.0))|| (( (time-1460257200) >=216907.0 && (time-1460257200) <= 216908.0))|| (( (time-1460257200) >=217955.0 && (time-1460257200) <= 217956.0))|| (( (time-1460257200) >=222946.0 && (time-1460257200) <= 222947.0))|| (( (time-1460257200) >=223307.0 && (time-1460257200) <= 223308.0))|| (( (time-1460257200) >=230751.0 && (time-1460257200) <= 230752.0))|| (( (time-1460257200) >=230752.0 && (time-1460257200) <= 230753.0))|| (( (time-1460257200) >=246894.0 && (time-1460257200) <= 246895.0))|| (( (time-1460257200) >=246895.0 && (time-1460257200) <= 246896.0))|| (( (time-1460257200) >=291547.0 && (time-1460257200) <= 291548.0))|| (( (time-1460257200) >=296054.0 && (time-1460257200) <= 296055.0))|| (( (time-1460257200) >=296055.0 && (time-1460257200) <= 296056.0))|| (( (time-1460257200) >=310247.0 && (time-1460257200) <= 310248.0))|| (( (time-1460257200) >=317502.0 && (time-1460257200) <= 317503.0))|| (( (time-1460257200) >=378589.0 && (time-1460257200) <= 378590.0))|| (( (time-1460257200) >=378590.0 && (time-1460257200) <= 378591.0))|| (( (time-1460257200) >=379936.0 && (time-1460257200) <= 379937.0))|| (( (time-1460257200) >=399332.0 && (time-1460257200) <= 399333.0))|| (( (time-1460257200) >=399580.0 && (time-1460257200) <= 399581.0))|| (( (time-1460257200) >=400869.0 && (time-1460257200) <= 400870.0))|| (( (time-1460257200) >=401571.0 && (time-1460257200) <= 401572.0))|| (( (time-1460257200) >=419276.0 && (time-1460257200) <= 419277.0))|| (( (time-1460257200) >=419277.0 && (time-1460257200) <= 419278.0))|| (( (time-1460257200) >=467976.0 && (time-1460257200) <= 467977.0))|| (( (time-1460257200) >=489345.0 && (time-1460257200) <= 489346.0))|| (( (time-1460257200) >=489504.0 && (time-1460257200) <= 489505.0))|| (( (time-1460257200) >=513625.0 && (time-1460257200) <= 513626.0))|| (( (time-1460257200) >=514946.0 && (time-1460257200) <= 514947.0))|| (( (time-1460257200) >=515040.0 && (time-1460257200) <= 515041.0))|| (( (time-1460257200) >=555774.0 && (time-1460257200) <= 555775.0))|| (( (time-1460257200) >=555775.0 && (time-1460257200) <= 555776.0))|| (( (time-1460257200) >=565632.0 && (time-1460257200) <= 565633.0))|| (( (time-1460257200) >=723769.0 && (time-1460257200) <= 723770.0))|| (( (time-1460257200) >=747535.0 && (time-1460257200) <= 747536.0))|| (( (time-1460257200) >=747536.0 && (time-1460257200) <= 747537.0))|| (( (time-1460257200) >=747537.0 && (time-1460257200) <= 747538.0))){
//h_totcharge_cut->Fill(channel1_total_charge);


}
//if(!(channel1_total_charge>=565 && channel1_total_charge<=620) && !(channel1_total_charge>=180 && channel1_total_charge<=300)){
h_time_energy_cut->Fill(time-1460257200);

 
  if(channel1_get_baseline>80){
  h_time_bhigh->Fill(time-1460257200,17500);}
  if(channel1_get_baseline<45){
  h_time_blow->Fill(time-1460257200);}
  
     //temporal
  //h_time_segundos->Fill(time-1460257200);
                 //temporal
  // h_time_correccion->Fill(time-1460257200, unitW*pow (presion[(int)((time-1460257200)/(3600))]/(729.2136150235),1));




   if(channel1_total_charge>0){
	//h_time_highE->Fill(time-1460257200, unitW*63/17);
         h_time_highE->Fill(time-1460257200, unitW);
         
 }
 h_time->Fill(time-1460067742);
   

    return kTRUE;
}

void EQPulseAnalysis::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.


///////////////////////////////////////////////////////////////////////////////////////////////
hdiffPico->Write(); 
hdiffPicoCut1->Write(); 
hdiffPicoCut2->Write(); 
hdiffPicoCut3->Write(); 
hdiffPicoCut4->Write(); 
 
CargaPico->Write();
CargaPicoCut1->Write();
CargaPicoCut2->Write();
CargaPicoCut3->Write();
CargaPicoCut4->Write();
 CargaPicoNet->Write();
CargaPicoNetCut1->Write();
CargaPicoNetCut2->Write();
CargaPicoNetCut3->Write();
CargaPicoNetCut4->Write();
 CargaNet->Write();
 h_totcharge->Write();
 
 timeIn->Write();
 timeInP->Write();
 timeOut->Write();
 timeOutP->Write();
 timeL->Write();
 timeLP->Write();
 timeT->Write();
 timeTP->Write();
 counterIn->Write();
 counterOut->Write();
 counterL->Write();
 counterT->Write();
 triggerIn->Write();
 triggerOut->Write();
 triggerL->Write();
 triggerT->Write();
tr1In->Write();
 tr1Out->Write();
 tr1L->Write();
 tr1T->Write();
tr2In->Write();
 tr2Out->Write();
 tr2L->Write();
 tr2T->Write();
tr3In->Write();
 tr3Out->Write();
 tr3L->Write();
 tr3T->Write();
tr4In->Write();
 tr4Out->Write();
 tr4L->Write();
 tr4T->Write();
tr5In->Write();
 tr5Out->Write();
 tr5L->Write();
 tr5T->Write();
tr6In->Write();
 tr6Out->Write();
 tr6L->Write();
 tr6T->Write();
tr7In->Write();
 tr7Out->Write();
 tr7L->Write();
 tr7T->Write();
tr8In->Write();
 tr8Out->Write();
 tr8L->Write();
 tr8T->Write();
tr9In->Write();
 tr9Out->Write();
 tr9L->Write();
 tr9T->Write();
tr10In->Write();
 tr10Out->Write();
 tr10L->Write();
 tr10T->Write();
tr11In->Write();
 tr11Out->Write();
 tr11L->Write();
 tr11T->Write();
tr12In->Write();
 tr12Out->Write();
 tr12L->Write();
 tr12T->Write();
 lenIn->Write();
 lenOut->Write();
 lenL->Write();
 lenT->Write();
 peakIn->Write();
 peakOut->Write();
 peakL->Write();
 peakT->Write();
 chargeIn->Write();
 chargeOut->Write();
 chargeL->Write();
 chargeT->Write();
 baseIn->Write();
 baseOut->Write();
 baseL->Write();
 baseT->Write();




tr1In2->Write();
 tr1Out2->Write();
 tr1L2->Write();
 tr1T2->Write();
tr2In2->Write();
 tr2Out2->Write();
 tr2L2->Write();
 tr2T2->Write();
tr3In2->Write();
 tr3Out2->Write();
 tr3L2->Write();
 tr3T2->Write();
tr4In2->Write();
 tr4Out2->Write();
 tr4L2->Write();
 tr4T2->Write();
tr5In2->Write();
 tr5Out2->Write();
 tr5L2->Write();
 tr5T2->Write();
tr6In2->Write();
 tr6Out2->Write();
 tr6L2->Write();
 tr6T2->Write();
tr7In2->Write();
 tr7Out2->Write();
 tr7L2->Write();
 tr7T2->Write();
tr8In2->Write();
 tr8Out2->Write();
 tr8L2->Write();
 tr8T2->Write();
tr9In2->Write();
 tr9Out2->Write();
 tr9L2->Write();
 tr9T2->Write();
tr10In2->Write();
 tr10Out2->Write();
 tr10L2->Write();
 tr10T2->Write();
tr11In2->Write();
 tr11Out2->Write();
 tr11L2->Write();
 tr11T2->Write();
tr12In2->Write();
 tr12Out2->Write();
 tr12L2->Write();
 tr12T2->Write();



peakIn2->Write();
 peakOut2->Write();
 peakL2->Write();
 peakT2->Write();
 chargeIn2->Write();
 chargeOut2->Write();
 chargeL2->Write();
 chargeT2->Write();
 baseIn2->Write();
 baseOut2->Write();
 baseL2->Write();
 baseT2->Write();
///////////////////////////////////////////////////////////////////////////////////////////////




//h_flujoMX->Write();
///////////////////////////////////////////////
////////////////////////////////////////////
/*pico1->Write();
valle1->Write();
pico2->Write();
valle2->Write();
pico3->Write();
valle3->Write();
pico4->Write();
valle4->Write();
pico5->Write();
valle5->Write();
pico6->Write();
valle6->Write();
pico7->Write();
valle7->Write();
t1->Write();
t2->Write();
t3->Write();
t4->Write();
t5->Write();
t6->Write();
t7->Write();
t8->Write();
t9->Write();
t10->Write();
t11->Write();
t12->Write();
t13->Write();
t14->Write();*/


/////////////////////////////////////////////
/*h200->Write();
h210->Write();
h220->Write();
h230->Write();
h240->Write();
h250->Write();
h260->Write();
h270->Write();
h280->Write();
h290->Write();
h300->Write();
h310->Write();
h320->Write();
h330->Write();
h340->Write();
h350->Write();
h360->Write();
h370->Write();
h380->Write();
h390->Write();
h400->Write();
h410->Write();
h420->Write();
h430->Write();
h440->Write();
h450->Write();
h460->Write();
h470->Write();
h480->Write();
h490->Write();
h500->Write();
h510->Write();
h520->Write();
h530->Write();
h540->Write();
h550->Write();
h560->Write();
h570->Write();
h580->Write();
h590->Write();
h600->Write();
h610->Write();
h620->Write();
h630->Write();
h640->Write();
h650->Write();
h660->Write();
h670->Write();
h680->Write();
h690->Write();
h700->Write();
h710->Write();
h720->Write();
h730->Write();
h740->Write();
h750->Write();
h760->Write();
h770->Write();
h780->Write();
h790->Write();
h800->Write();
h810->Write();
h820->Write();
h830->Write();
h840->Write();
h850->Write();
h860->Write();
h870->Write();
h880->Write();
h890->Write();
h900->Write();
h910->Write();
h920->Write();
h930->Write();
h940->Write();
h950->Write();
h960->Write();
h970->Write();
h980->Write();
h990->Write();
h1000->Write();
h1010->Write();
h1020->Write();
h1030->Write();
h1040->Write();
h1050->Write();
h1060->Write();
h1070->Write();
h1080->Write();
h1090->Write();
h1100->Write();
h1110->Write();
h1120->Write();
h1130->Write();
h1140->Write();
h1150->Write();
h1160->Write();
h1170->Write();
h1180->Write();
h1190->Write();
h1200->Write();
h1210->Write();
h1220->Write();
h1230->Write();
h1240->Write();
h1250->Write();
h1260->Write();
h1270->Write();
h1280->Write();
h1290->Write();
h1300->Write();
h1310->Write();
h1320->Write();
h1330->Write();
h1340->Write();
h1350->Write();
h1360->Write();
h1370->Write();
h1380->Write();
h1390->Write();
h1400->Write();
h1410->Write();
h1420->Write();
h1430->Write();
h1440->Write();
h1450->Write();
h1460->Write();
h1470->Write();
h1480->Write();
h1490->Write();
h1500->Write();
h1510->Write();
h1520->Write();
h1530->Write();
h1540->Write();
h1550->Write();
h1560->Write();
h1570->Write();
h1580->Write();
h1590->Write();
h1600->Write();
h1610->Write();
h1620->Write();
h1630->Write();
h1640->Write();
h1650->Write();
h1660->Write();
h1670->Write();
h1680->Write();
h1690->Write();
h1700->Write();
h1710->Write();
h1720->Write();
h1730->Write();
h1740->Write();
h1750->Write();
h1760->Write();
h1770->Write();
h1780->Write();
h1790->Write();
h1800->Write();
h1810->Write();
h1820->Write();
h1830->Write();
h1840->Write();
h1850->Write();
h1860->Write();
h1870->Write();
h1880->Write();
h1890->Write();
h1900->Write();
h1910->Write();
h1920->Write();
h1930->Write();
h1940->Write();
h1950->Write();
h1960->Write();
h1970->Write();
h1980->Write();
h1990->Write();
h2000->Write();*/
/////////////////////////////////////////////////////







h_baseline->Write();  

h_time_blow->Write();
h_time_bhigh->Write();  

   
    //h_time_segundos->Write();
  //h_time_minutos->Write();
  //h_time_horas->Write();
  h_totcharge_cut->Write();
  




//h_time_845->Write();
/*h_time_840->Write();
h_time_835->Write();
h_time_830->Write();
h_time_825->Write();
h_time_820->Write();
h_time_815->Write();
h_time_810->Write();
h_time_805->Write();
h_time_800->Write();
h_time_795->Write();
h_time_790->Write();
h_time_785->Write();
h_time_780->Write();
h_time_775->Write();
h_time_770->Write();
h_time_765->Write();
h_time_760->Write();
h_time_755->Write();
h_time_750->Write();
h_time_745->Write();
h_time_740->Write();
h_time_735->Write();
h_time_730->Write();
h_time_725->Write();
h_time_720->Write();
h_time_715->Write();
h_time_710->Write();
h_time_705->Write();
h_time_700->Write();
h_time_695->Write();
h_time_690->Write();
h_time_685->Write();
h_time_680->Write();
h_time_675->Write();
h_time_670->Write();
h_time_665->Write();
h_time_660->Write();
h_time_655->Write();
h_time_650->Write();
h_time_645->Write();
h_time_640->Write();
h_time_635->Write();
h_time_630->Write();
h_time_625->Write();
h_time_620->Write();
h_time_615->Write();*/
//h_time_610->Write();
//h_time_605->Write();
//h_time_600->Write();
//h_time_595->Write();
//h_time_590->Write();
/*h_time_585->Write();
h_time_580->Write();
h_time_575->Write();
h_time_570->Write();
h_time_565->Write();
h_time_560->Write();
h_time_555->Write();
h_time_550->Write();*/

/*h_time_0_620->Write();
h_time_0_640->Write();
h_time_0_660->Write();
h_time_0_680->Write();
h_time_0_616->Write();
h_time_0_612->Write();
h_time_0_608->Write();
h_time_0_604->Write();
h_time_0_600->Write();*/
   // h_totcharge_cut->Write();
 h_lluvia->Write();
 h_temp->Write();
 h_presion->Write();
 h_presion2->Write();
 h_time->Write();
 h_time_correccion->Write();
 h_time_energy_cut->Write();
 h_time_highE->Write();
   
    myfile->Close();

    cout<<"Done slave-terminating...."<<endl;


}

void EQPulseAnalysis::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

    
}
