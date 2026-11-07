# Software per Lab1 Calcolo e LabMCS

Questa guida permette di preparare il proprio PC o laptop per lavorare con gli
strumenti dei corsi **Lab1 (Calcolo)** e **LabMCS**, come in Aula Informatica.
Include Python, ROOT/PyROOT, Geant4, JupyterLab, Emacs, VS Code e AlphaPlot.
Usa poi i programmi indicati per il tuo corso: AlphaPlot è previsto in particolare
per Lab1, mentre gli esempi Geant4 riguardano LabMCS.

Pixi installa l'ambiente scientifico del corso nella cartella del progetto.
VS Code e AlphaPlot si installano separatamente sul computer.

## Prima di iniziare

Servono una connessione Internet e diversi GB di spazio libero. Come margine
per installazione, compilazioni ed esercizi, prepara circa 15–20 GB liberi.
Il primo download può richiedere tempo, soprattutto per i dati di Geant4.

Scegli le istruzioni per il tuo sistema:

- [macOS](#macos)
- [Windows con WSL2](#windows-con-wsl2)
- [Linux](#linux)
- [Note tecniche: WSL1/WSL2, tastiera, file e macchina virtuale](NOTE_TECNICHE.md)

Non occorre installare separatamente Python, ROOT, Geant4 o Emacs.
Per account WSL, tastiera italiana, scambio di file e macchina virtuale consulta
le [note tecniche](NOTE_TECNICHE.md).

## Installare Pixi e preparare il computer

### macOS

Apri il Terminale. Se non hai già i Command Line Tools di Apple, esegui:

```bash
xcode-select --install
```

Completa la procedura nella finestra che si apre. Se gli strumenti sono già
installati, puoi proseguire.

Con [Homebrew](https://brew.sh/) installato, esegui:

```bash
brew install pixi
brew install --cask visual-studio-code
pixi --version
```

Se stai installando Homebrew per la prima volta, completa i comandi mostrati
dall'installer sotto **Next steps** prima di proseguire: servono a rendere
disponibile `brew` nel terminale.

Su Mac Apple Silicon usa un Terminale nativo. Per verificare:

```bash
uname -m
```

Il risultato atteso è `arm64` su Apple Silicon e `x86_64` su Intel.
Prosegui con [Scaricare il progetto](#scaricare-il-progetto).

### Windows con WSL2

I comandi del laboratorio si eseguono in **Ubuntu/WSL**, mentre VS Code si
installa su Windows. Il percorso principale descritto qui usa WSL2 con WSLg;
la procedura alternativa WSL1 con server X esterno è nelle note tecniche.
Prima di iniziare aggiorna Windows. Per questo setup usa WSL2 sia su Windows 11
sia sulle versioni di Windows 10 compatibili con WSLg; non serve un X-server
separato. Se hai già WSL1, oppure devi scegliere tra le due versioni, leggi
[Verificare la versione di WSL](NOTE_TECNICHE.md#verificare-la-versione-di-wsl).
Le note includono i comandi di selezione e conversione, l'abilitazione manuale
dei componenti Windows e la [grafica WSL1 con VcXsrv/XLaunch](NOTE_TECNICHE.md#grafica-su-wsl1-con-vcxsrv-e-xlaunch).

Se Ubuntu/WSL2 è già configurato e le applicazioni grafiche funzionano, passa
direttamente all'installazione di Pixi. Altrimenti apri PowerShell come
amministratore ed esegui:

```powershell
wsl --install -d Ubuntu-24.04
wsl --update
```

Riavvia se richiesto, apri Ubuntu e completa la creazione dell'utente Linux.
Scegli un nome utente e una password: durante la digitazione della password
non vengono mostrati caratteri né asterischi. Digita la password, premi Invio
e ripetila quando richiesto. Questa è la password dell'utente Ubuntu, usata
anche per i comandi `sudo`; può essere diversa da quella di Windows.
Per informazioni consulta la [guida Microsoft a WSLg](https://learn.microsoft.com/en-us/windows/wsl/tutorials/gui-apps).

Installa [VS Code per Windows](https://code.visualstudio.com/download) e
l'estensione **WSL** di Microsoft.

Nel terminale **Ubuntu**, esegui:

```bash
sudo apt update
sudo apt install -y curl ca-certificates libgl1-mesa-dri mesa-utils
curl -fsSL https://pixi.sh/install.sh -o /tmp/install-pixi.sh
bash /tmp/install-pixi.sh
```

Chiudi e riapri il terminale Ubuntu, poi verifica:

```bash
pixi --version
```

Conserva la cartella del corso nel filesystem Linux, ad esempio `~/labmcs-pixi`.
Le compilazioni sotto `/mnt/c` possono essere più lente.
Per aprire la cartella da Esplora file o accedere ai documenti Windows, vedi
[Scambiare file tra Windows e Ubuntu](NOTE_TECNICHE.md#scambiare-file-tra-windows-e-ubuntu).

### Linux

Su Ubuntu/Debian, nel terminale della tua sessione grafica:

```bash
sudo apt update
sudo apt install -y curl ca-certificates libgl1-mesa-dri mesa-utils
curl -fsSL https://pixi.sh/install.sh -o /tmp/install-pixi.sh
bash /tmp/install-pixi.sh
```

Chiudi e riapri il terminale, poi esegui `pixi --version`.
Installa VS Code seguendo le [istruzioni per Linux](https://code.visualstudio.com/docs/setup/linux).
Su altre distribuzioni usa il gestore del sistema per installare le librerie
grafiche equivalenti. Su Wayland deve essere disponibile anche XWayland per
le applicazioni X11. Questo ambiente è destinato a distribuzioni con glibc.

## Scaricare il progetto

Apri il repository indicato per il corso. Puoi scaricarlo con **Code → Download
ZIP**, se disponibile, ed estrarre l'archivio, oppure clonarlo con Git:

```bash
git clone URL_DEL_REPOSITORY labmcs-pixi
```

Sostituisci `URL_DEL_REPOSITORY` con l'indirizzo fornito per il corso.
Per usare `git clone` deve essere installato Git; su Ubuntu puoi installarlo con
`sudo apt install git`. Il download ZIP non richiede Git.

Apri il terminale nella cartella estratta o clonata. Ad esempio, se si trova
nella tua cartella personale:

```bash
cd ~/labmcs-pixi
```

La cartella deve contenere `pixi.toml`, `pixi.lock`, `scripts/`, `cmake/` ed
`examples/`. Se manca `pixi.lock`, chiedi la copia completa del progetto.

## Installare l'ambiente del laboratorio

Dalla cartella del progetto esegui:

```bash
pixi install --locked
```

Attendi il completamento. Pixi scarica i pacchetti adatti al tuo computer.
Non occorrono privilegi di amministratore per questo comando.

Mantieni `pixi.toml` e `pixi.lock` come forniti per il corso: definiscono
l'ambiente da usare negli esercizi.

## Verificare l'installazione

Esegui un comando alla volta, aspettando che termini:

| Comando | Risultato atteso |
|---|---|
| `pixi run --locked check` | Controllo Python/PyROOT completato |
| `pixi run --locked g4-check` | Compilazione Geant4 ed esecuzione di tre eventi |
| `pixi run --locked root-gui` | Finestra con un istogramma ROOT |
| `pixi run --locked g4-gui` | Interfaccia grafica con la geometria Geant4 |

Chiudi la finestra ROOT per terminare il relativo test. Per uscire
dall'interfaccia Geant4 usa `exit` nella sua console.

Se un comando termina con un errore, conserva il messaggio completo e consulta
[Se qualcosa non funziona](#se-qualcosa-non-funziona).

## Usare gli strumenti del laboratorio

Apri il terminale nella cartella del progetto. I comandi seguenti usano
l'ambiente scientifico del corso:

| Attività | Comando |
|---|---|
| Aprire Python | `pixi run --locked python` |
| Eseguire uno script | `pixi run --locked python mio_script.py` |
| Aprire ROOT | `pixi run --locked root -l` |
| Aprire JupyterLab | `pixi run --locked notebook` |
| Aprire Emacs grafico | `pixi run --locked editor` |
| Aprire Emacs nel terminale | `pixi run --locked editor-term` |

Per JupyterLab apri nel browser l'indirizzo mostrato nel terminale, se non si
apre automaticamente. Per arrestare il server premi `Ctrl+C` nel terminale.
Per uscire da Emacs usa `Ctrl+x`, poi `Ctrl+c`.
Per riconoscere i caratteri speciali usati nei comandi, come `~`, l'apostrofo e
l'accento grave, consulta la [nota sulla tastiera italiana](NOTE_TECNICHE.md#tastiera-italiana-e-caratteri-speciali).

### Compilare un esercizio Geant4

Dalla cartella del laboratorio entra nell'ambiente:

```bash
pixi shell
```

Poi spostati nella cartella dei sorgenti dell'esercizio ed esegui:

```bash
cmake -S . -B build
cmake --build build --parallel 2
```

Usa il nome dell'eseguibile indicato nell'esercizio per avviare la simulazione.
La configurazione delle dipendenze viene caricata automaticamente.
Per uscire dalla shell del laboratorio esegui `exit`.

## Usare VS Code

Apri la cartella del progetto con **File → Open Folder** oppure, se il comando
è disponibile nel terminale:

```bash
code .
```

Su Windows lancia `code .` da Ubuntu. La finestra deve indicare una connessione
**WSL**. Installa le estensioni consigliate quando VS Code le propone.

Per Python, apri la palette dei comandi e scegli **Python: Select Interpreter**.
Seleziona l'interprete del progetto:

```text
.pixi/envs/default/bin/python
```

Scegli lo stesso ambiente come kernel dei notebook.
Per compilare dal terminale integrato di VS Code, entra prima in `pixi shell`.
La sola selezione dell'interprete Python non attiva l'ambiente per CMake.

## Installare e usare AlphaPlot

Per Lab1 installa anche AlphaPlot, come richiesto dalle attività di Calcolo.
AlphaPlot si avvia dal sistema operativo. Puoi scambiare i dati con Python,
ROOT e Geant4 mediante file CSV o TSV.

### Su macOS

Scarica `alphaplot_v1.02_x64_clang.dmg` dalla
[release ufficiale 1.02](https://sourceforge.net/projects/alphaplot/files/1.02/).
Apri il DMG e copia l'applicazione in Applicazioni.

Il pacchetto è per Intel: su Apple Silicon può essere richiesta l'installazione
di Rosetta. Questa riguarda AlphaPlot; continua a usare Pixi nel Terminale nativo.
Se macOS blocca l'avvio o l'applicazione non funziona, conserva il messaggio e
chiedi assistenza per il corso.

### Su Windows

Scarica e installa `alphaplot_v1.02_x64_msvc2019.exe` dalla
[stessa release ufficiale](https://sourceforge.net/projects/alphaplot/files/1.02/).

Per raggiungere da Windows i dati salvati in WSL, apri il terminale Ubuntu nella
cartella dei dati ed esegui:

```bash
explorer.exe .
```

Esplora file mostrerà la posizione da usare anche in AlphaPlot.
Se AlphaPlot è stato installato dentro Ubuntu tramite Flatpak, il comando di
avvio è indicato nella [nota dedicata](NOTE_TECNICHE.md#alphaplot-installato-con-flatpak).

### Su Linux

Puoi installare AlphaPlot dalla
[pagina Flathub dell'applicazione](https://flathub.org/apps/io.github.narunlifescience.AlphaPlot)
se Flatpak è configurato sul tuo sistema.

In alternativa, su Ubuntu/Debian, apri un terminale fuori da `pixi shell` e compila
la release con questi comandi:

```bash
sudo apt update
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

## Ricevere gli aggiornamenti del corso

Se hai scaricato il progetto con Git, dalla sua cartella esegui quando viene
annunciato un aggiornamento:

```bash
git pull
pixi install --locked
```

Se Git segnala modifiche locali o conflitti, conserva il tuo lavoro e chiedi
assistenza prima di proseguire. Salva gli esercizi con nomi e cartelle dedicati.
Se usi lo ZIP, scarica la nuova versione in una cartella separata e conserva
i tuoi file prima di spostarli.

## Se qualcosa non funziona

Le [note tecniche](NOTE_TECNICHE.md) raccolgono le procedure dettagliate per
WSL1/WSL2, account e password, tastiera italiana e scambio dei file.

Se le difficoltà persistono, chiedi assistenza a un docente o tutor. Una macchina
virtuale può essere un'alternativa concordata per il corso: vedi
[Usare una macchina virtuale](NOTE_TECNICHE.md#usare-una-macchina-virtuale).

| Problema | Cosa fare |
|---|---|
| `pixi: command not found` | Chiudi e riapri il terminale dopo l'installazione di Pixi. |
| Pixi non trova il progetto | Entra nella cartella che contiene `pixi.toml`. |
| `import ROOT` non funziona in uno script | Eseguilo con `pixi run --locked python mio_script.py`. In VS Code verifica l'interprete selezionato. |
| Su Windows i comandi Linux non funzionano | Usa Ubuntu/WSL o il terminale WSL di VS Code. |
| Errore di lock o pacchetti incompatibili | Controlla di avere tutti i file della stessa versione del progetto e segnala l'errore. |
| Errore HDF5 o percorsi Xcode inesistenti | Ripeti la configurazione dentro `pixi shell` usando una nuova cartella di build. Se persiste, segnala l'errore completo. |

Se su WSL le finestre si aprono ma la visualizzazione Geant4 fallisce, puoi
provare il rendering software:

```bash
LIBGL_ALWAYS_SOFTWARE=1 pixi run --locked g4-gui
```

Quando chiedi assistenza, indica il sistema operativo, il comando eseguito e
l'output completo dell'errore. Aggiungi anche l'output di:

```bash
pixi --version
pixi info
```
