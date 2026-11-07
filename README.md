# Laboratorio MCS con Pixi

Setup nativo per macOS Intel/Apple Silicon, Linux e Windows con WSL2.
Si assume disponibile una sessione grafica: desktop su Linux, WSLg su Windows.
Su macOS l'esempio Geant4 usa Qt nativo; non richiede XQuartz.

## Cosa viene installato

| Software | Gestione |
|---|---|
| Python 3.12, NumPy, SciPy, Matplotlib, pandas | Pixi, ambiente del progetto |
| ROOT e PyROOT | Pixi, pacchetto `root_base` |
| Geant4 e relativi dati fisici | Pixi, pacchetti conda-forge |
| CMake, Ninja e compilatori C/C++ | Pixi |
| JupyterLab e ipykernel | Pixi |
| Emacs | Pixi, con avvio grafico o nel terminale |
| VS Code desktop | Installazione sul sistema ospite |
| AlphaPlot | Installazione sul sistema ospite, descritta sotto |

`root_base` contiene ROOT/PyROOT e permette di aggiungere esplicitamente gli
strumenti del corso. Non serve installare anche ROOT, Geant4 o Python con
Homebrew/apt. VS Code e AlphaPlot si installano una volta per computer.

Pixi evita il desktop Linux e la VM di Docker su Mac. Non riduce la dimensione
intrinseca di ROOT, Geant4 e dei dataset: prevedere diversi GB di download/spazio.
Per iniziare suggerisco 15–20 GB liberi, come margine operativo, non come misura
dell'ambiente. La prima installazione è molto più onerosa degli avvii successivi.

## 1. Preparazione del Mac del docente

Nel Terminale, se mancano gli strumenti Apple:

```bash
xcode-select --install
```

Con Homebrew già installato:

```bash
brew install pixi
brew install --cask visual-studio-code
pixi --version
uname -m
```

Per installare Homebrew seguire [brew.sh](https://brew.sh/).
Su Apple Silicon usare un Terminale nativo: `uname -m` deve restituire `arm64`.
Non eseguire Pixi sotto Rosetta per questo progetto. Su Intel è atteso `x86_64`.

Estrarre questa cartella in una posizione stabile, ad esempio
`Documenti/labmcs-pixi`, e aprirla nel terminale:

```bash
cd /percorso/della/cartella/labmcs-pixi
pixi install
pixi run check
pixi run g4-check
pixi run root-gui
pixi run g4-gui
```

I primi due test controllano Python/PyROOT e compilano/eseguono una simulazione
Geant4 di tre eventi. Gli ultimi due devono aprire finestre interattive.
Per terminare Geant4 usare `exit` nella sua interfaccia.

`pixi install` risolve tutte le piattaforme dichiarate, crea `pixi.lock` e installa
solo i binari per il computer corrente. Se una piattaforma non ha una soluzione,
la risoluzione può fermarsi anche lavorando su Mac: leggere il nome della
piattaforma nell'errore. Non rimuoverla per poi dichiararla supportata agli studenti.

### Controllo importante: Geant4 con Qt

Esistono anche build di Geant4 senza Qt. La presenza di un desktop o del solo
pacchetto Qt non aggiunge il supporto a un Geant4 compilato senza Qt.
Il progetto grafico usa `find_package(Geant4 REQUIRED qt)` proprio per verificarlo.

Se `pixi run g4-gui` segnala che il componente `qt` manca:

```bash
pixi list
pixi search geant4
```

Verificare nel [feedstock ufficiale conda-forge](https://github.com/conda-forge/geant4-feedstock)
quale variante Qt è disponibile per la versione e le piattaforme del corso.
Vincolarla nel manifest con versione/build effettivamente presenti nel catalogo,
oppure scegliere una release che includa Qt, poi rigenerare il lock e ripetere i
test. Non considerare superato il collaudo grafico se funziona solo `g4-check`.
Il manifest fornito lascia scegliere la release al solver: la compatibilità Qt
va confermata durante questo primo collaudo, prima della distribuzione.

## 2. Installazione degli studenti: macOS

Installare gli strumenti Apple, Pixi e gli editor come nella sezione 1.
Scaricare ed estrarre la cartella fornita dal docente, che deve includere
`pixi.lock`. Nella cartella eseguire:

```bash
pixi install --locked
pixi run --locked check
pixi run --locked g4-check
pixi run --locked root-gui
pixi run --locked g4-gui
```

`--locked` verifica che il manifest corrisponda al lock e impedisce di cambiarne
le risoluzioni. Non copiare l'ambiente `.pixi` dal computer del docente.

## 3. Installazione degli studenti: Windows con WSL2

Se WSL2/WSLg sono già funzionanti, non reinstallarli.
Per una nuova configurazione, da PowerShell come amministratore:

```powershell
wsl --install -d Ubuntu
wsl --update
```

Riavviare se richiesto e completare la creazione dell'utente Ubuntu.
Usare una versione di Windows supportata da WSLg.

Installare VS Code **su Windows**, con l'estensione **WSL** di Microsoft.
Aprire Ubuntu/WSL e installare gli strumenti di sistema:

```bash
sudo apt update
sudo apt install -y curl ca-certificates libgl1-mesa-dri mesa-utils
curl -fsSL https://pixi.sh/install.sh -o /tmp/install-pixi.sh
bash /tmp/install-pixi.sh
```

Riaprire il terminale Ubuntu e verificare `pixi --version`.
Conservare il progetto nel filesystem Linux, ad esempio `~/labmcs-pixi`,
per evitare la lentezza dei file di compilazione sotto `/mnt/c`.
Estrarre o clonare lì la cartella distribuita e lanciare:

```bash
cd ~/labmcs-pixi
pixi install --locked
pixi run --locked check
pixi run --locked g4-check
pixi run --locked root-gui
pixi run --locked g4-gui
code .
```

La finestra VS Code deve indicare una connessione WSL. I comandi Pixi vanno
eseguiti nel suo terminale Linux, non nel PowerShell Windows.
Emacs grafico si avvia dal terminale WSL con `pixi run editor`.

In una sessione WSLg funzionante `echo "$DISPLAY"` ha un valore. Non sostituirlo
con l'indirizzo IP di Windows. Se le finestre si aprono ma OpenGL fallisce,
provare temporaneamente:

```bash
LIBGL_ALWAYS_SOFTWARE=1 pixi run --locked g4-gui
```

## 4. Installazione degli studenti: Linux

Esempio per Ubuntu/Debian con grafica già disponibile:

```bash
sudo apt update
sudo apt install -y curl ca-certificates libgl1-mesa-dri mesa-utils
curl -fsSL https://pixi.sh/install.sh -o /tmp/install-pixi.sh
bash /tmp/install-pixi.sh
```

Riaprire il terminale. Installare VS Code dal
[pacchetto ufficiale per la distribuzione](https://code.visualstudio.com/docs/setup/linux).
Su altre distribuzioni usare i rispettivi gestori per i driver grafici.

Entrare nella cartella del corso e lanciare gli stessi cinque comandi della
sezione 2. Per questo manifest Linux deve usare glibc, come Ubuntu; Alpine/musl
non è una piattaforma prevista. Su Wayland, per le applicazioni X11 serve XWayland.

## 5. AlphaPlot

AlphaPlot resta un'applicazione separata dall'ambiente Pixi. Installarlo e
avviarlo dal sistema ospite evita di mescolare i suoi plugin Qt con quelli del
laboratorio. Condividere i dati mediante file CSV/TSV.

### macOS

Scaricare il file **`alphaplot_v1.02_x64_clang.dmg`** dalla
[release ufficiale 1.02](https://sourceforge.net/projects/alphaplot/files/1.02/),
aprire il DMG e copiare l'applicazione in Applicazioni.
È un pacchetto Intel `x64`: su Apple Silicon richiede Rosetta; macOS può proporne
l'installazione all'avvio. Non è un binario ARM nativo e la compatibilità sui Mac
del corso va provata. In caso di blocco consultare il messaggio di macOS e le
impostazioni Privacy e sicurezza; non disabilitare globalmente Gatekeeper.

Collaudo: aprire un CSV, creare un grafico 2D ed esportarlo in PDF; se il corso
usa grafici 3D, provarli esplicitamente. L'eventuale uso di Rosetta per AlphaPlot
non richiede di eseguire sotto Rosetta anche Pixi, ROOT o Geant4.

### Windows/WSL

La via più semplice è installare AlphaPlot **su Windows**, usando l'installer
`alphaplot_v1.02_x64_msvc2019.exe` dalla stessa release ufficiale.
Per aprire i dati prodotti in WSL, nella cartella dati eseguire:

```bash
explorer.exe .
```

Si apre la posizione in Esplora file. AlphaPlot su Windows può accedere ai file
della distribuzione attraverso `\\wsl.localhost\Ubuntu\home\NOMEUTENTE\...`.
Il nome della distribuzione può differire: verificarlo con `wsl -l -v`.
Se si desidera anche AlphaPlot dentro WSL, usare la compilazione Linux seguente.

### Linux, oppure AlphaPlot dentro WSL

Per compilare la release 1.02 su Ubuntu/Debian, eseguire questi comandi in un
terminale normale, fuori da `pixi shell` o da ambienti Conda:

```bash
sudo apt install -y git build-essential qtbase5-dev qttools5-dev \
  qttools5-dev-tools qtscript5-dev libqt5svg5-dev libqt5opengl5-dev \
  libqt5datavisualization5-dev libgsl-dev
git clone --depth 1 --branch 1.02 \
  https://github.com/narunlifescience/AlphaPlot.git alphaplot-src
cd alphaplot-src
qmake alphaplot.pro
make -j2
sudo make install
alphaplot
```

Questa procedura usa le librerie Qt5 della distribuzione, non quelle di Pixi.
Per un'installazione senza compilazione su un desktop Linux si può usare il
[pacchetto Flathub ufficialmente collegato dal progetto](https://flathub.org/apps/io.github.narunlifescience.AlphaPlot),
tenendo conto che il runtime Flatpak occupa spazio aggiuntivo.

## 6. Uso quotidiano

Tutti i comandi Pixi si eseguono dalla cartella del progetto:

```bash
pixi run --locked python
pixi run --locked python mio_script.py
pixi run --locked root -l
pixi run --locked notebook
pixi shell
```

`pixi shell` apre una shell con l'ambiente attivo; `exit` torna alla shell normale.
Non aggiungere `source thisroot.sh` o `source geant4.sh`: usare l'attivazione di
Pixi e gli hook dei pacchetti. Non impostare globalmente `LD_LIBRARY_PATH`,
`DYLD_LIBRARY_PATH` o `QT_PLUGIN_PATH` nel profilo dell'utente.

### VS Code e Jupyter

Aprire la cartella con `code .` oppure dal menu di VS Code.
Installare le estensioni consigliate dal progetto.
In **Python: Select Interpreter**, scegliere:

```text
<cartella-progetto>/.pixi/envs/default/bin/python
```

Lo stesso interprete va scelto come kernel dei notebook. Su Windows questo
percorso va selezionato nella finestra VS Code collegata a WSL.
I normali comandi `python` nel terminale non sono automaticamente quelli del
progetto: usare `pixi run python ...` oppure entrare prima in `pixi shell`.

### Emacs

Emacs è incluso nell'ambiente Pixi; non occorre installarlo separatamente.
Su macOS, Linux e WSL2, dalla cartella del progetto:

```bash
pixi run --locked editor
```

Per la versione nel terminale:

```bash
pixi run --locked editor-term
```

Entrambi ereditano l'ambiente Pixi, incluso il Python e la configurazione CMake.
In Emacs si può avviare Python con `M-x run-python`. Se una configurazione
personale seleziona un Python esterno, impostare per il laboratorio:

```elisp
(setq python-shell-interpreter
      (expand-file-name "bin/python" (getenv "CONDA_PREFIX")))
```

Su Linux/WSL la finestra richiede la sessione grafica disponibile come previsto.
Per aggiornare una copia precedente del progetto, il docente può eseguire
`pixi add "emacs>=30,<32"`, aggiornare il lock e distribuirlo agli studenti.

## 7. Distribuzione del corso: compito del docente

1. Eseguire `pixi install` e i quattro test della sezione 1 sul Mac.
2. Provare AlphaPlot sul Mac, inclusa l'eventuale esecuzione con Rosetta.
3. Ripetere installazione, test batch e test grafici su almeno un computer
   Linux/WSL e sulle architetture che si intendono dichiarare supportate.
4. Conservare il `pixi.lock` generato insieme a `pixi.toml`, esempi e guida.
5. Distribuire questi file via Git o ZIP. Escludere `.pixi/`, `build/` e file
   temporanei. Il lock contiene risoluzioni specifiche per ciascuna piattaforma;
   non implica binari identici né risultati numerici identici tra architetture.
6. Agli studenti far usare `pixi install --locked`. Non far rigenerare loro il
   lock come rimedio automatico agli errori.

Per aggiornare il corso, lavorare su una copia o un ramo, eseguire `pixi update`,
ripetere i collaudi e distribuire una nuova revisione del lock.
Registrare anche la versione di Pixi usata dal docente (`pixi --version`).

## Errore HDF5 thread-safe durante la configurazione

La configurazione del laboratorio è ora applicata automaticamente a tutti i
progetti CMake avviati tramite `pixi run` o dentro `pixi shell`:

- `pixi.toml` carica `scripts/activate.sh`;
- lo script imposta `CMAKE_TOOLCHAIN_FILE` a `cmake/pixi-toolchain.cmake`;
- il toolchain preferisce l'ambiente Pixi e disabilita la ricerca dei file di
  configurazione HDF5 esterni.

Distribuire anche questi due file. Non occorre aggiungere opzioni HDF5 ai comandi
degli studenti né modificare ogni pacchetto Geant4. Per un pacchetto esterno,
aprire `pixi shell` dalla cartella del laboratorio, poi spostarsi nei suoi
sorgenti e usare normalmente `cmake -S . -B build`.
La correzione vale per nuove build senza un toolchain esplicitamente diverso.
Per le build già configurate dal docente occorre ricreare una volta la cache
con `cmake --fresh`; dopo la modifica al manifest riaprire `pixi shell` e
aggiornare il lock con `pixi install` prima di distribuirlo.

Se CMake trova un HDF5 esterno, ad esempio `/usr/local/lib/cmake/hdf5`, può
segnalare che manca il supporto thread-safe anche se l'HDF5 di Pixi lo include.
Il `CMakeLists.txt` aggiornato abilita C e C++, imposta `HDF5_ROOT` sull'ambiente
attivo e usa il modulo FindHDF5 evitando la configurazione esterna.
Dopo aver sostituito il file, ricreare la cache (non serve reinstallare i pacchetti):

```bash
pixi run cmake --fresh -S examples/geant4 -B build/geant4 -G Ninja -DCMAKE_BUILD_TYPE=Release
pixi run g4-check
pixi run cmake --fresh -S examples/geant4 -B build/geant4-gui -G Ninja -DCMAKE_BUILD_TYPE=Release -DLAB_GUI=ON
pixi run g4-gui
```

Nel log verificare `H5_HAVE_THREADSAFE - found` e il percorso HDF5 sotto
`.pixi/envs/default`. Non aggirare il controllo forzando a vero il risultato del
test e non modificare i file installati di Geant4.

## Stato di questo kit

Il manifest, gli script e gli esempi sono predisposti per il collaudo.
Il kit iniziale non include un lock generato. Una successiva verifica con
l'ambiente Pixi installato dal docente su macOS Intel e Geant4 11.4.2 ha
confermato la configurazione CMake e il riconoscimento dell'HDF5 thread-safe
dopo la correzione sopra. Le finestre native e le altre piattaforme restano da
collaudare. Il lock del docente va conservato e validato prima della distribuzione.

## Riferimenti

- [Installazione Pixi](https://pixi.prefix.dev/latest/installation/)
- [Manifest e piattaforme Pixi](https://pixi.prefix.dev/latest/reference/pixi_manifest/)
- [Pacchetto ROOT conda-forge](https://anaconda.org/conda-forge/root)
- [Pacchettizzazione Geant4 conda-forge](https://github.com/conda-forge/geant4-feedstock)
- [Grafica WSLg](https://learn.microsoft.com/en-us/windows/wsl/tutorials/gui-apps)
- [AlphaPlot: sorgenti e dipendenze](https://github.com/narunlifescience/AlphaPlot)
- [AlphaPlot: download 1.02](https://sourceforge.net/projects/alphaplot/files/1.02/)
