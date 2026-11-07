"""Verifica ambiente, PyROOT e dati Geant4; eseguire con pixi run check."""
import os
import platform
from pathlib import Path
import subprocess
import sys

import ROOT
import numpy as np
import scipy
import matplotlib
import pandas

ROOT.gROOT.SetBatch(True)
hist = ROOT.TH1D("check", "check", 10, 0, 10)
hist.Fill(2.0)
if hist.Integral() != 1:
    raise RuntimeError("PyROOT: istogramma non valido")
np.testing.assert_allclose(np.linalg.solve([[2.0]], [4.0]), [2.0])
print("Sistema:", platform.system(), platform.machine())
print("Python:", sys.version.split()[0], sys.executable)
print("ROOT:", ROOT.gROOT.GetVersion())
subprocess.run(["geant4-config", "--version"], check=True)
data_vars = {key: value for key, value in os.environ.items()
             if key.startswith("G4") and key.endswith("DATA")}
for key, value in sorted(data_vars.items()):
    if not Path(value).is_dir():
        raise RuntimeError(f"Dataset non trovato: {key}={value}")
print("Variabili dataset Geant4 trovate:", len(data_vars))
print("Controllo Python/PyROOT completato. Eseguire anche pixi run g4-check e i test grafici.")
