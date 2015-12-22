#include <map>

#include "TCut.h"

std::map<std::string, float> GetLumis() {

    const float lumi = 1280.;

    std::map<std::string, float> values;
    // Equivalent lumi = lumi * xsec / counts-with-pu
    // counts-with-pu is ((TH1F*)_file0->Get("CountWeighted"))->GetBinContent(1)
    values["ZH_HToBB_ZToNuNu_M125_13TeV_amcatnloFXFX_madspin_pythia8"                ] = lumi *    0.088154 / 1.16478525000000000e+06; //(0.8696-0.1057)*0.200*0.577
    values["WH_HToBB_WToLNu_M125_13TeV_amcatnloFXFX_madspin_pythia8"                 ] = lumi *     0.25958 / 1.12889112500000000e+06; //1.380 *0.326*0.577
    values["ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8"                                ] = lumi *     0.04837 / 1.86044725000000000e+06;
    values["DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"                  ] = lumi *      6025.2 / 9.04033200000000000e+06;
    values["WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"                       ] = lumi * 60290.*1.23 / 7.16990320000000000e+07;
    values["WW_TuneCUETP8M1_13TeV-pythia8"                                           ] = lumi *       118.7 / 9.92818187500000000e+05;
    values["WZ_TuneCUETP8M1_13TeV-pythia8"                                           ] = lumi *       47.13 / 9.77263625000000000e+05;
    values["ZZ_TuneCUETP8M1_13TeV-pythia8"                                           ] = lumi *      16.523 / 9.18844125000000000e+05;
    values["TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"                    ] = lumi *       87.31 / 5.73427300000000000e+06;
    values["TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"        ] = lumi *      365.35 / 1.14482190000000000e+07;
    values["ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1"        ] = lumi *       10.11 / 6.13390125000000000e+05;
    values["ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1"        ] = lumi *       10.11 / 4.06083400000000000e+06;
    values["ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1"          ] = lumi *       38.09 / 9.01010125000000000e+05;
    values["ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1"      ] = lumi *       38.09 / 9.06457375000000000e+05;

    values["SingleMuon" ]     = 1.000000;
    values["SingleElectron" ] = 1.000000;
    values["DoubleMuon" ]     = 1.000000;
    values["DoubleEG" ]       = 1.000000;
    values["MET" ]            = 1.000000;

    return values;
}

