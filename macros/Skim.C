#include <iostream>

#include "TFile.h"
#include "TChain.h"
#include "TChainElement.h"
#include "TString.h"
#include "TCut.h"
#include "TH1.h"
#include "TSystem.h"
#include "TROOT.h"

//#include "XSec_8TeV19invfb.h"

const TCut skimZll      = "(Vtype==0||Vtype==1) && V_pt>120 && Jet_pt[hJCidx[0]]>20 && Jet_pt[hJCidx[1]]>20";
const TCut skimWln      = "(Vtype==2||Vtype==3) && V_pt>130 && Jet_pt[hJCidx[0]]>30 && Jet_pt[hJCidx[1]]>30";
const TCut skimZnn      = "(Vtype==2||Vtype==3||Vtype==4) && met_et>150 && Jet_pt[hJCidx[0]]>30 && Jet_pt[hJCidx[1]]>30"; //< Znn includes single lepton channels to use for control regions
const TCut skimHbb      = "H.HiggsFlag==1 && abs(Jet_eta[hJCidx[0]])<2.5 && abs(Jet_eta[hJCidx[1]])<2.5 && Jet_btagCSV[hJCidx[0]]>0 && Jet_btagCSV[hJCidx[1]]>0"; // removed id

void Skim(TString process="ZnnH125")
{
    gROOT->SetBatch(1);

    TString fname   = "";
    TString outdir  = "skim/";
    TString prefix  = "Step2_";
    TString suffix  = ".root";
    TString dijet   = "DiJetPt_";

    TChain * chain  = new TChain("tree");

    //Add to chain

    // Make selection
    TCut selection = (skimZll || skimWln || skimZnn);
    selection += skimHbb;
    //add trigger cuts for data?

    selection.Print();


    // Sum Count, CountWithPU, CountWithPUP, CountWithPUM, ...
    TObjArray * files = chain->GetListOfFiles();
    TIter next(files);
    TChainElement * chainElem = 0;
    TFile * f2 = 0;

    TH1F * count = new TH1F("Count", "Count", 1, 0, 2);
    TH1F * countWeighted = new TH1F("CountWeighted", "Count with gen weight and pu weight", 1, 0, 2);
    TH1F * countPosWeight = new TH1F("CountPosWeight", "Count genWeight>0", 1, 0, 2);
    TH1F * countNegWeight = new TH1F("CountNegWeight", "Count genWeight<0", 1, 0, 2);

    TH1F * htemp = 0;
    while ((chainElem = (TChainElement*) next())) {
        f2 = TFile::Open("dcache:" + TString(chainElem->GetTitle()));
        htemp = (TH1F*) f2->Get("Count");
        count->SetBinContent(1, count->GetBinContent(1)+htemp->GetBinContent(1));
        htemp = (TH1F*) f2->Get("CountWithPU");
        countWeighted->SetBinContent(2, countWeighted->GetBinContent(2)+htemp->GetBinContent(1));
        htemp = (TH1F*) f2->Get("CountWithPUP");
        CountPosWeight->SetBinContent(3, CountPosWeight->GetBinContent(3)+htemp->GetBinContent(1));
        htemp = (TH1F*) f2->Get("CountWithPUM");
        CountNegWeight->SetBinContent(4, CountNegWeight->GetBinContent(4)+htemp->GetBinContent(1));
        htemp = (TH1F*) f2->Get("CountWithMCProd");

        std::clog << process << ": skimmed from " << chainElem->GetTitle() << std::endl;
    }

    // Make output directory if it doesn't exist
    if (gSystem->AccessPathName(outdir))
        gSystem->mkdir(outdir);
    TString outname = outdir + prefix + Form("%s.root", process.Data());

    TFile* f1 = TFile::Open(outname, "RECREATE");
    TTree* t1 = (TTree*) chain->CopyTree(selection);
    std::clog << process << ": skimmed from " << chain->GetEntriesFast() << " to " << t1->GetEntriesFast() << " entries." << std::endl;

    t1->Write();
    count->Write();
    countWeighted->Write();
    CountPosWeight->Write();
    CountNegWeight->Write();
    f1->Close();

    return;
}

// To run:
//root -l -b -q Skim.C+\(\"ZnnH125\"\)

