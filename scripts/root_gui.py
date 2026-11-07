"""Finestra ROOT nativa, per il collaudo della grafica."""
import ROOT

ROOT.gROOT.SetBatch(False)
canvas = ROOT.TCanvas("lab_canvas", "Collaudo ROOT", 800, 600)
hist = ROOT.TH1D("gauss", "ROOT;Valore;Conteggi", 80, -4, 4)
ROOT.gRandom.SetSeed(12345)
hist.FillRandom("gaus", 10000)
hist.Draw()
canvas.Update()
print("Chiudere la finestra per terminare il test.")
canvas.Connect("Closed()", "TApplication", ROOT.gApplication, "Terminate()")
ROOT.gApplication.Run(True)
