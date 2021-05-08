void draw(TString prefix)
{
    TString c1name = Form("problem%s_pt.gif", prefix.Data());
    TString c2name = Form("problem%s_ptratio.gif", prefix.Data());
    TString c3name = Form("problem%s_ptdiff.gif", prefix.Data());
    TH1::SetDefaultSumw2();
    TFile* f1 = new TFile(Form("problem%s.root", prefix.Data())); 
    TH1F* hgen = (TH1F*) f1->Get("ptgen");
    TH1F* hobs = (TH1F*) f1->Get("ptobs");
    TCanvas *c1 = new TCanvas();
    c1->cd();
    gStyle->SetOptStat(0);
    gPad->SetLeftMargin(0.18);
    gPad->SetBottomMargin(0.18);
    gPad->SetTopMargin(0.15);
    hobs->GetXaxis()->SetRangeUser(2, 10);
    hobs->GetXaxis()->SetLabelSize(0.05);
    hobs->GetXaxis()->SetTitle("p_{t} (GeV)");
    hobs->GetXaxis()->CenterTitle();
    hobs->GetXaxis()->SetLabelOffset(0.005);
    hobs->GetXaxis()->SetTitleSize(0.05);
    hobs->GetYaxis()->SetTitle("counts per 10 Mev");
    hobs->GetYaxis()->SetTitleSize(0.05);
    hobs->GetYaxis()->SetMaxDigits(4);
    hobs->GetYaxis()->SetNdivisions(515);
    hobs->GetYaxis()->SetLabelSize(0.05);
    hobs->GetYaxis()->CenterTitle();
    hobs->SetTitle("p_{t} spectrum");
    hobs->SetLineColor(kRed);
    hobs->SetMarkerStyle(kFullCircle);
    hobs->SetMarkerSize(0.8);
    hobs->SetStats(0);
    hgen->SetLineColor(kBlue);
    hgen->SetMarkerStyle(kOpenSquare);
    hgen->SetMarkerSize(0.8);
    hgen->SetStats(0);
    hobs->Draw("e");
    hgen->Draw("esame");
    TLegend *l = new TLegend(0.6, 0.7, 0.9, 0.9);
    l->AddEntry(hgen, "true spectrum");
    l->AddEntry(hobs, "observed spectrum");
    l->Draw();
    c1->SaveAs(c1name);

    TCanvas* c2 = new TCanvas();
    c2->cd();
    gPad->SetLeftMargin(0.18);
    gPad->SetBottomMargin(0.18);
    gPad->SetTopMargin(0.15);
    TH1F* hdivide = new TH1F(*hobs);
    hdivide->Sumw2();
    hdivide->Divide(hgen);
    hdivide->SetTitle("Ratio of the observed to the true p_{t} spectrum");
    hdivide->GetYaxis()->SetTitle("#frac{dN_{obs}/dp_{t}}{dN_{gen}/dp_{t}}");
    hdivide->Draw("e");
    TLine* line = new TLine();
    line->SetLineStyle(9);
    line->SetLineColor(kBlue);
    line->DrawLine(2, 1, 10, 1);
    c2->SaveAs(c2name);

    TCanvas* c3 = new TCanvas();
    c3->cd();
    gPad->SetLeftMargin(0.18);
    gPad->SetBottomMargin(0.18);
    gPad->SetTopMargin(0.15);
    TH1F* hsubtract = new TH1F(*hobs);
    hsubtract->Sumw2();
    hsubtract->Add(hgen, -1);
    hsubtract->Scale(-1);
    hsubtract->SetTitle("Difference between true and observed p_{t} spectra");
    hsubtract->GetYaxis()->SetMaxDigits(2);
    hsubtract->GetYaxis()->SetTitle("#frac{dN_{gen}}{p_{t}} - #frac{dN_{obs}}{pt}");
    hsubtract->Draw();
    line->DrawLine(2, 0, 10, 0);
    c3->SaveAs(c3name);
}
void drawpictures()
{
    draw("A");
    draw("D");
    draw("E");
    draw("F");
}
