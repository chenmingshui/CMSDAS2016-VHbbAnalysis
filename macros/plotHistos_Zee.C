#include "plotHistos_Zee.h"

#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"


// To run, do "root -l plotHistos.C+"

void plotHistos_Zee() {
    gROOT->LoadMacro("tdrstyle.C");
    gROOT->ProcessLine("setTDRStyle()");

    TH1::SetDefaultSumw2(1);
    //gROOT->SetBatch(1);

    TString plotdir = "plots/";

    if (gSystem->AccessPathName(plotdir))
        gSystem->mkdir(plotdir);


    ////////////////////////////////////////////////////////////////////////////
    // Task 1 (a)                                                             //
    ////////////////////////////////////////////////////////////////////////////

    // Read from ntuples
    Events * ev = new Events();
    TCut cutmc_all   = "Vtype==1";   // change this to your channel
    TCut cutdata_all = "Vtype==1";   // change this to your channel
    TString process  = "VH";         // can try other processes: VH, WJ, ZJ, TT
    ev->read(cutmc_all, cutdata_all, process);

    TString var      = "H.mass";                // the variable to plot
    TCut cut         = "V.pt>0";                // the selection cut
    TString title    = ";m(jj) [GeV]";          // the title of the histogram
    TString plotname = process + "_Hmass";      // the name of the image file
    int nbinsx       = 15;                      // number of bins
    double xlow      = 30.0;                    // the low edge of x-axis
    double xup       = 255.0;                   // the upper edge of x-axis
    TString option   = "!plotLog:!plotNorm";    // use "plotLog" to plot on log-y scale,
                                                // use "!plotLog" to plot on linear scale;
                                                // use "plotNorm" to plot normalized plots,
                                                // use "!plotNorm" otherwise.

    // Use "ev->ZH" for ZH, or "ev->WjLF", "ev->WjHF", "ev->ZjLF", "ev->ZjHF", "ev->TT" for other processes
    MakePlot(ev->ZH, var, cut, title, nbinsx, xlow, xup, plotname, plotdir, option);

    // You can put in the parameters directly as in the following commented out line:
    //MakePlot(ev->ZH, "H.pt", cut, "; p_{T}(jj) [GeV]", 16, 0, 240., process + "_Hpt", plotdir, option);


    ////////////////////////////////////////////////////////////////////////////
    // Task 1 (b)                                                             //
    ////////////////////////////////////////////////////////////////////////////
/*
    // Read from ntuples
    Events * ev = new Events();
    TCut cutmc_all   = "Vtype==1";   // change this to your channel
    TCut cutdata_all = "Vtype==1";   // change this to your channel
    ev->read(cutmc_all, cutdata_all, "VH:ZJ");  // read both VH and ZJ processes

    TString var      = "H.mass";
    TCut cut         = "V.pt>0";
    TString title    = ";m(jj) [GeV]";
    TString plotname = "ZH_vs_ZJ_Hmass";
    int nbinsx       = 15;
    double xlow      = 30.0;
    double xup       = 255.0;
    TString option   = "!plotLog:plotNorm";

    // Using "ev->ZH" for ZH and "ev->ZjHF" for Z+HF
    MakePlot2(ev->ZH, ev->ZjHF, var, cut, title, nbinsx, xlow, xup, plotname, plotdir, option);
*/

    ////////////////////////////////////////////////////////////////////////////
    // Task 2                                                                 //
    ////////////////////////////////////////////////////////////////////////////
/*
    // Zmm______________________________________________________________________
    //TString channel  = "Zmm";

    // These are loose cuts for all plots in this particular channel
    //TCut cutmc_all   = "Vtype==0 && hJet_pt[0]>20 && hJet_pt[1]>20 && abs(hJet_eta[0])<2.5 && abs(hJet_eta[1])<2.5 && hJet_id[0]==1 && hJet_id[1]==1 && hJet_puJetIdL[0]>0 && hJet_puJetIdL[1]>0 && vLepton_pt[0]>20 && vLepton_pt[1]>20 && abs(vLepton_eta[0])<2.4 && abs(vLepton_eta[1])<2.4 && METtype1corr.et<60 && 75<V.mass && V.mass<105 && H.dR<1.6 && hbhe==1";
    //TCut cutdata_all = cutmc_all;
    //cutmc_all       *= "weightTrig2012";  // apply trigger weight for MC

    // Scale factors in order of: WjLF, WjHF, ZjLF, ZjHF, TT
    // NOTE: WjLF, WjHF are not needed for Zll
    //double scalefactors[5] = {1.00, 1.00, 1.00, 1.00, 1.00};


    // Zee______________________________________________________________________
    TString channel  = "Zee";

    // These are loose cuts for all plots in this particular channel
    TCut cutmc_all   = "Vtype==1 && hJet_pt[0]>20 && hJet_pt[1]>20 && abs(hJet_eta[0])<2.5 && abs(hJet_eta[1])<2.5 && hJet_id[0]==1 && hJet_id[1]==1 && hJet_puJetIdL[0]>0 && hJet_puJetIdL[1]>0 && vLepton_pt[0]>20 && vLepton_pt[1]>20 && abs(vLepton_eta[0])<2.5 && abs(vLepton_eta[1])<2.5 && METtype1corr.et<60 && 75<V.mass && V.mass<105 && H.dR<1.6 && hbhe==1";
    TCut cutdata_all = cutmc_all;
    cutmc_all       *= "weightTrig2012";  // apply trigger weight for MC

    // Scale factors in order of: WjLF, WjHF, ZjLF, ZjHF, TT
    // NOTE: WjLF, WjHF are not needed for Zll
    double scalefactors[5] = {1.00, 1.00, 1.00, 1.00, 1.00};


    // Wmn______________________________________________________________________
    //TString channel  = "Wmn";

    // These are loose cuts for all plots in this particular channel
    //TCut cutmc_all   = "Vtype==2 && hJet_pt[0]>30 && hJet_pt[1]>30 && abs(hJet_eta[0])<2.5 && abs(hJet_eta[1])<2.5 && hJet_id[0]==1 && hJet_id[1]==1 && hJet_puJetIdL[0]>0 && hJet_puJetIdL[1]>0 && vLepton_pt[0]>30 && abs(vLepton_eta[0])<2.4 && METtype1corr.et >45 && Sum$(aJet_pt>20 && abs(aJet_eta)<4.5 && aJet_id==1 && aJet_puJetIdL>0)==0 && hbhe==1";
    //TCut cutdata_all = cutmc_all;
    //cutmc_all       *= "weightTrig2012";  // apply trigger weight for MC

    // Scale factors in order of: WjLF, WjHF, ZjLF, ZjHF, TT
    // NOTE: ZjLF, ZjHF are not needed for Wln
    //double scalefactors[5] = {1.00, 1.00, 1.00, 1.00, 1.00};


    // Wen______________________________________________________________________
    //TString channel  = "Wen";

    // These are loose cuts for all plots in this particular channel
    //TCut cutmc_all   = "Vtype==3 && hJet_pt[0]>30 && hJet_pt[1]>30 && abs(hJet_eta[0])<2.5 && abs(hJet_eta[1])<2.5 && hJet_id[0]==1 && hJet_id[1]==1 && hJet_puJetIdL[0]>0 && hJet_puJetIdL[1]>0 && vLepton_pt[0]>30 && abs(vLepton_eta[0])<2.5 && METtype1corr.et >45 && Sum$(aJet_pt>20 && abs(aJet_eta)<4.5 && aJet_id==1 && aJet_puJetIdL>0)==0 && hbhe==1";
    //TCut cutdata_all = cutmc_all;
    //cutmc_all       *= "weightTrig2012";  // apply trigger weight for MC

    // Scale factors in order of: WjLF, WjHF, ZjLF, ZjHF, TT
    // NOTE: ZjLF, ZjHF are not needed for Wln
    //double scalefactors[5] = {1.00, 1.00, 1.00, 1.00, 1.00};


    // Znn______________________________________________________________________
    //TString channel  = "Znn";

    // These are loose cuts for all plots in this particular channel
    // NOTE: minDeltaPhijetMET finds the minimum azimuthal angle between a jet (of pT>20 and |eta|<2.5) and the missing transverse energy. This definition is slightly different from the one in the final analysis.
    //TCut cutmc_all   = "Vtype==4 && hJet_pt[0]>80 && hJet_pt[1]>30 && abs(hJet_eta[0])<2.5 && abs(hJet_eta[1])<2.5 && hJet_id[0]==1 && hJet_id[1]==1 && hJet_puJetIdL[0]>0 && hJet_puJetIdL[1]>0 && abs(minDeltaPhijetMET)<0.5 && Sum$(aJet_pt>25 && abs(aJet_eta)<4.5 && aJet_id==1 && aJet_puJetIdL>0)==0 && hbhe==1";
    //TCut cutdata_all = cutmc_all;
    //cutmc_all       *= "(triggerFlags[42]==1 || triggerFlags[39]==1 || triggerFlags[41]==1) && hbhe && ecalFlag && cschaloFlag && hcallaserFlag && trackingfailureFlag && eebadscFlag && !isBadHcalEvent"; // apply trigger bits and MET cleaning for MC (they are already applied on data)
    //cutmc_all       *= "triggercorrMET(METtype1corr.et)";

    // Scale factors in order of: WjLF, WjHF, ZjLF, ZjHF, TT
    //double scalefactors[5] = {1.00, 1.00, 1.00, 1.00, 1.00};


    // All channels_____________________________________________________________
    // Read from ntuples
    Events * ev = new Events();
    ev->read(cutmc_all, cutdata_all);

    // Set the scale factors
    ev->set_sf(scalefactors);

    // Optimize these five variables (default: recommendations for Zll)
    double vpt    = 150.;
    double hpt    = 0.;
    double maxcsv = 0.679;
    double mincsv = 0.5;
    double dPhi   = 0.;

    // Optimize these five variables (default: recommendations for Wln)
    //double vpt    = 150.;
    //double hpt    = 100.;
    //double maxcsv = 0.898;
    //double mincsv = 0.5;
    //double dPhi   = 2.95;

    // Optimize these five variables (default: recommendations for Znn)
    //double vpt    = 170.;  // for Znn, pT(V) = MET
    //double hpt    = 190.;
    //double maxcsv = 0.898;
    //double mincsv = 0.5;
    //double dPhi   = 2.95;

    double minhmass = 100;
    double maxhmass = 150;

    // These are tight cuts for this particular plot
    TCut cutmc = Form("V.pt>%.2f && H.pt>%.2f && max(hJet_csv_nominal[0],hJet_csv_nominal[1])>%.3f && min(hJet_csv_nominal[0], hJet_csv_nominal[1])>%.3f && abs(HVdPhi)>%.2f", vpt, hpt, maxcsv, mincsv, dPhi);
    //TCut cutmc = Form("V.pt>%.2f && H.pt>%.2f && max(hJet_csv_nominal[0],hJet_csv_nominal[1])>%.3f && min(hJet_csv_nominal[0], hJet_csv_nominal[1])>%.3f && abs(HVdPhi)>%.2f && %.2f<H.mass && H.mass<%.2f", vpt, hpt, maxcsv, mincsv, dPhi, minhmass, maxhmass);
    TCut cutdata = cutmc;

    TString var      = "H.mass";
    TString title    = ";m(jj) [GeV]";
    TString plotname = channel + "_Hmass";
    int nbinsx       = 15;
    double xlow      = 30.0;
    double xup       = 255.0;
    TString option   = "printStat:printCard:plotUOflow:plotSig:!plotData:!plotLog";

    MakePlots(ev, var, cutmc, cutdata, title, nbinsx, xlow, xup, plotname, plotdir, option);

    // Or, just put in them directly as in the following commented out line:
    //MakePlots(ev, "H.mass", cutmc, cutdata, "m(jj) [GeV]", 15, 30.0, 255.0, "Hmass", plotdir, "printStat:printCard:plotUOflow:plotSig:!plotData:!plotLog");
*/

}
