#include <iostream>

#include "TFile.h"
#include "TChain.h"
#include "TChainElement.h"
#include "TString.h"
#include "TTree.h"
#include "TCut.h"
#include "TH1.h"
#include "TSystem.h"
#include "TROOT.h"

const TCut skim_13TeV = "V_pt>100";// && Jet_pt[hJCidx[0]]>20 && Jet_pt[hJCidx[1]]>20";

void SimpleSkim(TString process)
{
    gROOT->SetBatch(1);

    //TString add_str = "/eos/uscms/store/user/lpchbb/HeppyNtuples/V14/";//mc
    //TString add_str = "/eos/uscms/store/user/lpchbb/HeppyNtuples/V15/";//data
    //TString add_str = "root://cmsxrootd.fnal.gov///store/user/lpchbb/HeppyNtuples/V15/";//data
    //TString add_str = "root://cmseos.fnal.gov///store/user/lpchbb/HeppyNtuples/V15/";//data
    TString add_str = "root://cmseos.fnal.gov///store/user/lpchbb/HeppyNtuples/V14/";//MC
    add_str += process;
    add_str += ".root";
    cout << "add_str = " << add_str << endl;
    TFile * treeFile = TFile::Open(add_str);
    TTree* mytree = (TTree*)treeFile->Get("tree");

    TCut selection = skim_13TeV;
    selection.Print();

    // Make output directory if it doesn't exist
    //TString outdir = "/eos/uscms/store/user/cmsdas/2016/Hbb/heppy_v14/skims/";
    //TString outdir = "root://cmsxrootd.fnal.gov///store/user/cmsdas/2016/Hbb/heppy_v14/skims/";
    TString outdir = "root://cmseos.fnal.gov///store/user/cmsdas/2016/Hbb/heppy_v14/skims/";
    //TString outdir = "/uscms_data/d2/kreis/";
    if (gSystem->AccessPathName(outdir))
        gSystem->mkdir(outdir);
    TString outname = outdir + "skim_" + Form("%s.root", process.Data());
    cout << "out file is " << outname << endl;

    TFile* f1 = TFile::Open(outname, "RECREATE");
    TTree* t1 = (TTree*) mytree->CopyTree(selection);
    std::clog << process << ": skimmed from " << mytree->GetEntriesFast() << " to " << t1->GetEntriesFast() << " entries." << std::endl;

    TH1F* count          = (TH1F*) treeFile->Get("Count");
    TH1F* countWeighted  = (TH1F*) treeFile->Get("CountWeighted");
    TH1F* countPosWeight = (TH1F*) treeFile->Get("CountPosWeight");
    TH1F* countNegWeight = (TH1F*) treeFile->Get("CountNegWeight");

    t1->Write();
    count->Write();
    countWeighted->Write();
    countPosWeight->Write();
    countNegWeight->Write();

    f1->Close();
    treeFile->Close();

    return;
}

// To run:
//root -l -b -q Skim.C+\(\"SingleMuon\"\)

