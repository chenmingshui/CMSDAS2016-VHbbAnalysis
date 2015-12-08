{
  gROOT->SetStyle("Plain");
  gROOT->ProcessLine(".L tdrstyle.C");
  setTDRStyle();

  bool addElec=1;
  bool addLooseCSV=1;

  TFile *fMu1 = new TFile("FinalShapes_muOld.root");
  TH1F* histMuSig_cat1 = (TH1F*) fMu1->Get("Wmn/VH"); 
  TH1F* histMuWLF_cat1 = (TH1F*) fMu1->Get("Wmn/WjLF"); 
  TH1F* histMuWHF_cat1 = (TH1F*) fMu1->Get("Wmn/WjHF"); 
  TH1F* histMuZLF_cat1 = (TH1F*) fMu1->Get("Wmn/ZjLF"); 
  TH1F* histMuZHF_cat1 = (TH1F*) fMu1->Get("Wmn/ZjHF"); 
  TH1F* histMuTTbar_cat1 = (TH1F*) fMu1->Get("Wmn/TT"); 
  TH1F* histMuST_cat1 = (TH1F*) fMu1->Get("Wmn/s_Top"); 
  TH1F* histMuVV_cat1 = (TH1F*) fMu1->Get("Wmn/VV"); 
  TH1F* histMuData_cat1 = (TH1F*) fMu1->Get("Wmn/data_obs"); 
  histMuData_cat1->Sumw2();
  //  histMuSig_cat1->SetFillColor(2);
  //histMuVV_cat1->SetFillColor(1);

 

  //  TFile *fElec1 = new TFile("FinalShapes_ele.root");
  TFile *fElec1 = new TFile("H.massCorrWen_Data.root");
  TH1F* histElecSig_cat1 = (TH1F*) fElec1->Get("Wmn/VH");
  TH1F* histElecWLF_cat1 = (TH1F*) fElec1->Get("Wmn/WjLF");
  TH1F* histElecWHF_cat1 = (TH1F*) fElec1->Get("Wmn/WjHF");
  TH1F* histElecZLF_cat1 = (TH1F*) fElec1->Get("Wmn/ZjLF");
  TH1F* histElecZHF_cat1 = (TH1F*) fElec1->Get("Wmn/ZjHF");
  TH1F* histElecTTbar_cat1 = (TH1F*) fElec1->Get("Wmn/TT");
  TH1F* histElecST_cat1 = (TH1F*) fElec1->Get("Wmn/s_Top");
  TH1F* histElecVV_cat1 = (TH1F*) fElec1->Get("Wmn/VV");
  TH1F* histElecData_cat1 = (TH1F*) fElec1->Get("Wmn/data_obs");
  histElecData_cat1->Sumw2();
  //  histElecSig_cat1->SetFillColor(2);
  //histElecVV_cat1->SetFillColor(1);


  histMuData_cat1->Add(histMuData_cat1,histMuWLF_cat1,1,-1);
  histMuData_cat1->Add(histMuData_cat1,histMuWHF_cat1,1,-1);
  histMuData_cat1->Add(histMuData_cat1,histMuZLF_cat1,1,-1);
  histMuData_cat1->Add(histMuData_cat1,histMuZHF_cat1,1,-1);
  histMuData_cat1->Add(histMuData_cat1,histMuTTbar_cat1,1,-1);
  histMuData_cat1->Add(histMuData_cat1,histMuST_cat1,1,-1);


  histElecData_cat1->Add(histElecData_cat1,histElecWLF_cat1,1,-1);
  histElecData_cat1->Add(histElecData_cat1,histElecWHF_cat1,1,-1);
  histElecData_cat1->Add(histElecData_cat1,histElecZLF_cat1,1,-1);
  histElecData_cat1->Add(histElecData_cat1,histElecZHF_cat1,1,-1);
  histElecData_cat1->Add(histElecData_cat1,histElecTTbar_cat1,1,-1);
  histElecData_cat1->Add(histElecData_cat1,histElecST_cat1,1,-1);



  histMuData_cat1->Add(histMuData_cat1,histElecData_cat1,1,1);
  histMuSig_cat1->Add(histMuSig_cat1,histElecSig_cat1,1,1);
  histMuVV_cat1->Add(histMuVV_cat1,histElecVV_cat1,1,1);
  

  histMuSig_cat1->SetFillColor(kRed);
  histMuVV_cat1->SetFillColor(kGray);
  histMuVV_cat1->SetLineColor(kGray);
  histMuVV_cat1->SetLineWidth(3);


  THStack *hsMassMC= new THStack("hsMassMC"," ");
  hsMassMC->SetTitle("");
  hsMassMC->Add(histMuSig_cat1);
  hsMassMC->Add(histMuVV_cat1);
  TCanvas c1;
  c1.cd();

  

  histMuVV_cat1->Draw();

 
  histMuData_cat1->Draw("");
  hsMassMC->Draw("HISTsame");
  histMuData_cat1->SetMarkerStyle(kFullCircle);
  histMuData_cat1->Draw("PE1SAME");


  TLegend * leg =new TLegend(0.7,0.62,0.90,0.92);
  leg->AddEntry(histMuData_cat1,"Data","p");
   leg->AddEntry(histMuSig_cat1,"WH(bb)","l");
   leg->AddEntry(histMuVV_cat1,"WZ(bb)","l");

  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->SetTextFont(62);
  leg->SetTextSize(0.03);
 
  leg->Draw();


  TLatex l;
  l.SetNDC();
  l.SetTextAlign(12);
  l.SetTextSize(0.04);
  l.DrawLatex(0.17,0.89,"CMS Preliminary");
  l.SetTextSize(0.03);
  l.DrawLatex(0.17,0.84,"#sqrt{s} = 8 TeV, L = 12 fb^{-1}");
  l.DrawLatex(0.17,0.79,"W(l#nu)H(b#bar{b})");

  



}
