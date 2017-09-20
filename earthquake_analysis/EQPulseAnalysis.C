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
   myfile = new TFile("eqhistos.root","RECREATE");
   h_totcharge = new TH1F("h_totcharge", "Integrated Charge", 900, 0, 9000);
   h_time = new TH1D("h_time", "time",86400 , 0, 86400);
   //h2_rate = new TH2F("h2_rate","h2_rate",);
   
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
    h_totcharge->Fill(channel1_total_charge);
    //cout<<channel1_peak<<"\t"<<time<<"\t"<<counter<<endl;
    h_time->Fill(time-1460257200);
    
    
    return kTRUE;
}

void EQPulseAnalysis::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

//beautify histogram
    //h_totcharge->SetLineColor(kBlue);
    //h_totcharge->SetLineWidth(2);
    //h_totcharge->GetXaxis()->SetTitle("ADC");
    //change canvas pointer to the adequate canvas
    //c_totcharge->cd();
    //draw the histo in the current canvas
    //h_totcharge->Draw();
    //Print an image
    //c_totcharge->Print("h_totcharge.png");
    h_totcharge->Write();
    h_time->Write();
    myfile->Close();

    cout<<"Done slave-terminating...."<<endl;


}

void EQPulseAnalysis::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

    
}
