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

const TCut skim_13TeV = "V_pt>100";// && Jet_pt[hJCidx[0]]>20 && Jet_pt[hJCidx[1]]>20";

void Skim(TString process)
{
    gROOT->SetBatch(1);

    TChain * chain  = new TChain("tree");

    //Add to chain
    TString add_str = "/eos/uscms/store/user/lpchbb/HeppyNtuples/V14/";
    add_str += process;
    add_str += "*.root";
    cout << "add_str = " << add_str << endl;
    chain->Add(add_str);

    // Make selection
    TCut selection = skim_13TeV;
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
    cout << "1" << endl;
    while ((chainElem = (TChainElement*) next())) {
        f2 = TFile::Open(TString(chainElem->GetTitle()));
        htemp = (TH1F*) f2->Get("Count");
        count->SetBinContent(1, count->GetBinContent(1)+htemp->GetBinContent(1));
        htemp = (TH1F*) f2->Get("CountWeighted");
        countWeighted->SetBinContent(2, countWeighted->GetBinContent(2)+htemp->GetBinContent(1));
        htemp = (TH1F*) f2->Get("CountPosWeight");
        countPosWeight->SetBinContent(3, countPosWeight->GetBinContent(3)+htemp->GetBinContent(1));
        htemp = (TH1F*) f2->Get("CountNegWeight");
        countNegWeight->SetBinContent(4, countNegWeight->GetBinContent(4)+htemp->GetBinContent(1));

        std::clog << process << ": skimmed from " << chainElem->GetTitle() << std::endl;
    }

    // Make output directory if it doesn't exist
    TString outdir = "/eos/uscms/store/user/cmsdas/2016/Hbb/heppy_v14/skims/";
    if (gSystem->AccessPathName(outdir))
        gSystem->mkdir(outdir);
    TString outname = outdir + "skim_" + Form("%s.root", process.Data());

    TFile* f1 = TFile::Open(outname, "RECREATE");
    TTree* t1 = (TTree*) chain->CopyTree(selection);
    std::clog << process << ": skimmed from " << chain->GetEntriesFast() << " to " << t1->GetEntriesFast() << " entries." << std::endl;

    t1->Write();
    count->Write();
    countWeighted->Write();
    countPosWeight->Write();
    countNegWeight->Write();
    f1->Close();

    return;
}

// To run:
//root -l -b -q Skim.C+\(\"ZnnH125\"\)

