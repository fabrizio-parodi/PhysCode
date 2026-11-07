# Software per lavorare sul proprio PC/laptop come in Aula Informatica

Versione 2.5 - 18/9/2026

Istruzioni comuni per i corsi Lab1 (Calcolo) e LabMCS.

Le istruzioni dipendono dal sistema operativo di cui si dispone.

Installazione dell’ambiente scientifico integrata con Pixi.

[Windows](#windows) · [Linux](#linux) · [Mac OsX](#mac-osx) · [Macchina virtuale](#macchina-virtuale) · **[Note tecniche](NOTE_TECNICHE.md)**

## Windows

### Windows Subsystem for Linux

Assicuratevi che il vostro sistema operativo sia aggiornato (le istruzioni nel seguito sono valide sia per Windows 10 che per Windows11, con piccole varianti)

Assicuratevi che il sistema operativo sia aggiornato all’ultima versione disponibile

Cercare il terminale di comando Command Prompt e aprirlo premendo il tasto destro del mouse Run as Administrator

Aggiornare wsl

```powershell
wsl --update
```

Se il comando non dovesse funzionare:

Controllare di aver accesso alla rete

Eventualmente installata manualmente WSL con il comando

```powershell
wsl --install
```

o se non fosse disponibile sul vostro sistema dando il comando

```powershell
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
```

e poi:

```powershell
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
```

### Scegliere WSL1 o WSL2

#### Windows 10

Sul terminale dare il comando

```powershell
wsl --set-default-version 1
```

#### Windows 11

Sul terminale dare il comando

```powershell
wsl --set-default-version 2
```

Installare Ubuntu24 con il comando

```powershell
wsl --install -d Ubuntu-24.04
```

Riavviare ed accedere al sistema Linux (sotto Ubuntu)

ATTENZIONE ALLA PASSWORD: È NECESSARIO inserire la password richiesta al primo accesso sul sistema Linux.La password NON è visibile durante la digitazione quindi assicurarsi di inserirla correttamente (e annotarla), e solo DOPO premere “Invio”.Se la procedura non viene seguita correttamente, l’utente del sistema Linux risulta essere “root”, cioè l'amministratore di sistema (o super-utente). In questo caso la procedura di installazione va ripetuta.

[solo per Windows 10] Installare un X-server (operazione necessaria per poter usare, sotto WSL1, applicazioni grafiche): scaricate ed installate VcXsrv (disponibile su https://sourceforge.net/projects/vcxsrv)

### Installazione software aggiuntivo

Aprite il terminale di Ubuntu.

Se Pixi non è già installato, date i comandi:

```bash
curl -fsSL https://pixi.sh/install.sh -o /tmp/install-pixi.sh
bash /tmp/install-pixi.sh
```

Chiudete e riaprite il terminale.

Quindi date il comando:

```bash
git clone https://github.com/fabrizio-parodi/CalcoloXFisica.git
```

Il software scientifico è installato tramite Pixi: Python, ROOT, Geant4,
compilatori C/C++, CMake ed Emacs sono inclusi nell’ambiente del corso.
Aprite il terminale nella cartella del progetto che contiene `pixi.toml` e
`pixi.lock`, quindi date il comando:

```bash
pixi install --locked
```

Una volta terminato, solo per il primo anno, date anche il comando, dalla
cartella in cui avete clonato `CalcoloXFisica`:

```bash
source CalcoloXFisica/installAlphaPlot
```

Per eseguire AlphaPlot serve il comando:

```bash
flatpak run io.github.narunlifescience.AlphaPlot
```

A questo punto il software necessario è disponibile.

[Solo per WSL1] Prima di ogni sessione di lavoro fate partire X-server (icona XLaunch) e, nei menù mostrati in partenza, cliccare sulla voce "Disable access control"

### Informazioni importanti

#### Se avete la tastiera italiana e volete che diventi il default su Windows e WSL

Impostate tastiera italiana su Windows

Da WSL date il comando

```bash
sudo dpkg-reconfigure locales
```

selezionate dal menù che comparirà la tastiera italiana

(si fa con la barra spaziatrice) e  de-selezionate

quella inglese

Fate reboot di Windows

<a id="caratteri-speciali"></a>

#### Come produrre facilmente i caratteri ~ e \` con tastiera italiana

Scaricare la "Current Version" di AutoHotKey da https://www.autohotkey.com/

Scaricare lo script [keysetup.ahk](https://drive.google.com/file/d/18K3zTnvYTa_hywJYgyN9gkIX4jaEuT5d/view?usp=sharing), assicurandosi che mantenga .ahk come estensione

Aprire il percorso file alla cartella "Esecuzione Automatica" premendo WIN+R e scrivendo shell:startup nella barra di ricerca

Trasferire lo script "keysetup" in questa cartella, che permetterà la sua attivazione automatica ad ogni accensione di Windows

Riavviare il PC

Per usare i caratteri speciali basterà procedere come segue:

"tilde" (~)                     ---> Premere Alt + -  (trattino della tastiera)

apostrofo per Root (`) ---> Premere Alt + '   (apostrofo normale)

<a id="accesso-ai-file"></a>

#### Come accedere a Windows/Linux da Linux/Windows

Attenzione: si consiglia vivamente di accedere a Windows da Linux

(e non viceversa per evitare  di corrompere il filesystem di Linux)

**Da Linux**

/mnt/c (per disco C), provate ad esempio con il comando per listare i files:

```bash
ls /mnt/c
```

E poi quindi sull’account principale:

```bash
ls /mnt/c/Users/ACCOUNT_PRINCIPALE/Desktop
```

**Da Windows**

Dalla versione 1903 di Windows basta andare su \\wsl$\Ubuntu-24.04\home\user

Per versioni meno recenti invece: da Windows sul File Explorer digitare: C:\[USERNAME]\AppData\Local\Packages quindi entrate nella cartella che inizia con CanonicalGroup…. e poi da questa su LocalState\rootfs

## Linux

La descrizione vale per una qualunque distribuzione Linux. L’ambiente è
equivalente a quello usato in laboratorio (distribuzione Xubuntu).
Non servono configurazioni aggiuntive: gli strumenti di sviluppo quali il
compilatore C++ e l’editor Emacs sono installati nell’ambiente Pixi.

### Software aggiuntivo

Aprite il terminale sulla HOME (si ottiene dando il comando `cd` da terminale).

Se Pixi non è già installato, date i comandi:

```bash
curl -fsSL https://pixi.sh/install.sh -o /tmp/install-pixi.sh
bash /tmp/install-pixi.sh
```

Chiudete e riaprite il terminale.

Date il comando:

```bash
git clone https://github.com/fabrizio-parodi/CalcoloXFisica.git
```

Il software scientifico è installato tramite Pixi: Python, ROOT, Geant4,
compilatori C/C++, CMake ed Emacs sono inclusi nell’ambiente del corso.
Aprite il terminale nella cartella del progetto che contiene `pixi.toml` e
`pixi.lock`, quindi date il comando:

```bash
pixi install --locked
```

La procedura Pixi sostituisce l’installazione del software scientifico su
Ubuntu 24, Ubuntu 22 e sulle altre distribuzioni, inclusi il download e la
configurazione manuale di ROOT. Per attivare l’ambiente date `pixi shell` dalla
cartella del progetto.

Una volta terminato, solo per il primo anno, date anche il comando, dalla
cartella in cui avete clonato `CalcoloXFisica`:

```bash
source CalcoloXFisica/installAlphaPlot
```

Nel caso vi fossero problemi con Flatpak per una certa versione di Linux,
installate AlphaPlot seguendo le istruzioni su
[https://alphaplot.sourceforge.io/](https://alphaplot.sourceforge.io/).

## Mac OsX

Mac OsX è Unix, quindi di fatto molto simile a Linux.

### Software aggiuntivo

Verificare di avere il command line di Xcode funzionante (e, altrimenti,
installatelo) con il comando:

```bash
xcode-select --install
```

Aprite il terminale sulla HOME (si ottiene dando il comando `cd` da terminale)
e date il comando:

```bash
git clone https://github.com/fabrizio-parodi/CalcoloXFisica.git
```

Installate [Homebrew](https://brew.sh/) se non è già presente.
Attenzione ai comandi, spesso Homebrew (che è il primo software che viene
installato, propedeutico per installare software successivo) è da settare con
una serie di comandi! Questi sono riportati dopo la dicitura **“==> Next steps”**.

Installate Pixi con:

```bash
brew install pixi
```

Il software scientifico è installato tramite Pixi: Python, ROOT, Geant4,
compilatori C/C++, CMake ed Emacs sono inclusi nell’ambiente del corso.
Aprite il terminale nella cartella del progetto che contiene `pixi.toml` e
`pixi.lock`, quindi date il comando:

```bash
pixi install --locked
```

### Installazione di ROOT

L’installazione di ROOT avviene insieme all’ambiente Pixi. Questa procedura
sostituisce le opzioni di installazione, download dei binari e ricompilazione
di ROOT. La configurazione si attiva con `pixi shell` dalla cartella del
progetto: non occorre aggiungere `thisroot.sh` ai file di configurazione della shell.

Seguite eventuali messaggi di errore che possono presentarsi durante
l’installazione. Se l’installazione fallisce, confrontatevi con un prof/tutor
con il relativo messaggio di errore, perché possiamo risolvere.

Installate AlphaPlot seguendo le istruzioni su
[https://alphaplot.sourceforge.io/](https://alphaplot.sourceforge.io/).

## Usare l’ambiente Pixi

Dalla cartella del progetto che contiene `pixi.toml`, date:

```bash
pixi shell
```

Nella shell sono disponibili gli strumenti installati per il corso. Date
`exit` per uscire. Potete anche eseguire direttamente i programmi:

```bash
pixi run --locked python
pixi run --locked root -l
pixi run --locked emacs
```

Per compilare un esercizio, dopo essere entrati in `pixi shell`, spostatevi
nella cartella dei suoi sorgenti e date:

```bash
cmake -S . -B build
cmake --build build --parallel 2
```

Per verificare l’ambiente, dalla cartella del progetto:

```bash
pixi run --locked check
pixi run --locked g4-check
pixi run --locked root-gui
pixi run --locked g4-gui
```

<a id="macchina-virtuale"></a>

## If all else fails…

Se nessuna delle procedure illustrate funziona suggeriamo l’installazione di una macchina virtuale.

Ecco i passi da seguire in questo caso:

[Abilitare la virtualizzazione su Windows](https://support.microsoft.com/en-us/windows/enable-virtualization-on-windows-c5578302-6e43-4b4b-a449-8ced115f58e1)

Installare [VirtualBox 7.1.0](https://www.virtualbox.org/)

Installare anche l’ Extension Pack di VirtualBox (sempre versione 7.1.0)

Scaricare la macchina virtuale:

Ubuntu 24.04: [Ubuntu64.ova](https://drive.google.com/file/d/15HLRRobGohfF7JslssCji1r2R16mEvuc/view?usp=drive_link)

Da VirtualBox, selezionare la voce del menù “File → Import appliance” e caricare il file .ova precedentemente scompattato

(attenzione: affinché questa operazione vada a buon fine dovete avere almeno 10 GB di spazio disco liberi).

Collegatevi (username: vboxuser  password: calcolo24 )

### Regolate il display

Sul client Linux  nel menu generale (in alto a sinistra) cercate Settings → Display e regolate una risoluzione simile a quella del vostro schermo.

Potete eventualmente aggiustare ancora il fattore di scala da VirtualBox andando nel menù: View → Virtual Screen 1
