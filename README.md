# PhysCode - Installazione software per i Corsi di Studio in Fisica

[C. Cardinale, F.Parodi, F.Sforza, M. Sotgia, S. Turchikhin]

Le presenti istruzioni descrivono come installare sul proprio computer portatile il software di base necessario 
per gli insegnamenti dei corsi di laurea in Fisica e di laurea magistrale in Fisica dell’Università di Genova.

La condivisione, il riutilizzo e l’adattamento di questo materiale sono incoraggiati. 
Salvo diversa indicazione, il testo è distribuito con licenza Creative Commons Attribuzione 4.0 Internazionale (CC BY 4.0), 
che consente di copiarlo, distribuirlo e modificarlo, anche per fini commerciali, purché siano riconosciuti gli autori, citata la fonte, fornito un collegamento alla licenza e indicate le eventuali modifiche.

I programmi descritti restano soggetti alle rispettive licenze d’uso. Per il software open source, i diritti di utilizzo, modifica e redistribuzione e i relativi obblighi sono stabiliti dalla licenza di ciascun progetto, secondo i criteri della Open Source Definition dell’Open Source Initiative.

Le istruzioni dipendono dal sistema operativo di cui si dispone e si basano sul gestore di pacchetti Pixi.

[Windows](#windows)

[Linux](#linux)

[Mac OsX](#mac-osx)

Una volta configurato il sistema l'utilizzo  è comune ai vari sistemi operativi

[Usare Pixi](#usare-pixi)

Come installare Alphaplot (per Laboratorio 1)

[Alphaplot](#alphaplot)

Sono inoltre disponibili alcune soluzioni specifiche per problemi tecnici che potreste incontrare su WSL:

[Tastiera italiana](#tastiera-italiana)

[Carattere ~](#caratteri-speciali)

[Copia-Linux-Windows](#copia-linux-windows)

## Windows

### Windows Subsystem for Linux

Assicuratevi che il vostro sistema operativo sia aggiornato all’ultima versione disponibile (le istruzioni nel seguito sono valide sia per Windows 10 che per Windows11, con piccole varianti).

Cercate il terminale di comando Command Prompt e apritelo premendo il tasto destro del mouse e selezionando Run as Administrator

Aggiornare wsl

```powershell
wsl --update
```

Se il comando non viene riconosciuto, aggiornate Windows e seguite la procedura Microsoft per aggiornare WSL. Se invece viene segnalato un errore di download, controllate la connessione Internet.

Sul terminale dare il comando

```powershell
wsl --set-default-version 2
```

Installare Ubuntu24 con il comando

```powershell
wsl --install -d Ubuntu-24.04
```

Riavviare ed accedere al sistema Linux (sotto Ubuntu)

ATTENZIONE ALLA PASSWORD: È NECESSARIO inserire la password richiesta al primo accesso sul sistema Linux.La password NON è visibile durante la digitazione quindi assicurarsi di inserirla correttamente (e annotarla), e solo DOPO premere “Invio”. Se la procedura non viene seguita correttamente, l’utente del sistema Linux risulta essere “root”, cioè l'amministratore di sistema (o super-utente). In questo caso la procedura di installazione va ripetuta.


Aprite il terminale di Ubuntu.

Installate Pixi con i seguenti comandi:

```bash
curl -fsSL https://pixi.sh/install.sh -o /tmp/install-pixi.sh
bash /tmp/install-pixi.sh
```

Chiudete e riaprite il terminale.

Quindi date il comando:

```bash
git clone https://github.com/fabrizio-parodi/PhysCode.git
```
e poi:

```bash
cd PhysCode
```

Il software scientifico è installato tramite Pixi: Python, ROOT, Geant4,
compilatori C/C++, CMake ed Emacs sono inclusi nell’ambiente.
Aprite il terminale nella cartella del progetto che contiene `pixi.toml` e
`pixi.lock`, quindi date il comando:

```bash
pixi install 
```

A questo punto il software necessario è disponibile.


## Linux

La descrizione vale per una qualunque distribuzione Linux. L’ambiente è
equivalente a quello usato in laboratorio.
Non servono configurazioni aggiuntive: gli strumenti di sviluppo quali il
compilatore C++ e l’editor Emacs sono installati nell’ambiente Pixi.


Aprite il terminale sulla HOME (si ottiene dando il comando `cd` da terminale).

Se Pixi non è già installato, date i comandi:

```bash
curl -fsSL https://pixi.sh/install.sh -o /tmp/install-pixi.sh
bash /tmp/install-pixi.sh
```

Chiudete e riaprite il terminale.

Date il comando:

```bash
git clone https://github.com/fabrizio-parodi/PhysCode.git

```
e poi:
```bash

cd PhysCode
```
```bash
pixi install 
```


## Mac OsX

Mac OsX è Unix, quindi di fatto molto simile a Linux.


Verificare di avere il command line di Xcode funzionante (e, altrimenti,
installatelo) con il comando:

```bash
xcode-select --install
```

Aprite il terminale sulla HOME (si ottiene dando il comando `cd` da terminale)
e date il comando:

```bash
git clone https://github.com/fabrizio-parodi/PhysCode.git

```
e poi

```bash
cd PhysCode
```

Installate brew:
```bash
```
Installate Pixi con:

```bash
brew install pixi
```

```bash
pixi install --locked
```


## Usare Pixi (tutti i sistemi operativi)

Dalla cartella del progetto che contiene `pixi.toml`, date:

```bash
pixi shell
```

Nella shell sono disponibili tutti gli strumenti necessari per il corso (g++, emacs, root).
Date `exit` per uscire (attenzione quando uscite dalla shell di Pixi perdete tutte le configurazioni).


## Alphaplot

AlphaPlot è utilizzato per Laboratorio 1 e si installa separatamente
all’ambiente Pixi.

### WSL, Linux e OsX (Intel)

Lo script di installazione è nel repository PhysCode (che avete scaricato nei passi precedenti). 

Installate AlphaPlot con:

```bash
source "$HOME/PhysCode/installAlphaPlot"
```

Per eseguire AlphaPlot serve il comando:

```bash
flatpak run io.github.narunlifescience.AlphaPlot
```

### Mac OsX

Se avete un Macbook con chip M o in generale se avete problemi con le istruzioni precedenti
vi forniamo un container Docker che permette di usarne una versione containerizzata su Linux/Ubuntu 24.04 LTS.

#### Installazione di Docker Desktop

Per utilizzare il container è necessario avere Docker Desktop installato e
avviato sul Mac. Con Homebrew già disponibile, date:

```bash
brew install --cask docker-desktop
```

Aprite quindi **Docker** dalla cartella Applicazioni e completate il primo
avvio. Questa operazione potrebbe richiedere qualche tempo e qualche GB di
spazio sul disco. Per i dettagli consultate
[l’installazione ufficiale per Mac](https://docs.docker.com/desktop/setup/install/mac-install/).

#### Installazione di XQuartz

Per utilizzare l’interfaccia grafica è necessaria anche una versione
installata di XQuartz, ottenibile con:

```bash
brew install --cask xquartz
```

Dopo l’installazione, aprite XQuartz e andate nelle impostazioni con la
scorciatoia **⌘+,**. Nella sezione **Security** assicuratevi che sia attivata
l’opzione **Allow connections from network clients**. Chiudete e riaprite
XQuartz dopo la modifica e lasciatelo in esecuzione mentre utilizzate AlphaPlot.

#### Costruzione del container

I file del container sono nella cartella `alphaplot` del repository PhysCode. 

Una volta avviato Docker Desktop, dalla directory `CalcoloXFisica` lanciate:

```bash
cd "$HOME/PhysCode"
docker build -t alphaplot alphaplot/
```

A questo punto, per aprire l’applicazione, eseguite lo script
`alphaplot/start.sh`:

```bash
./alphaplot/start.sh
```

#### Rendere il comando disponibile da qualunque cartella

Per poter eseguire lo script in qualunque momento, aggiungete al `PATH` la
posizione della sua directory. Da dentro `CalcoloXFisica/alphaplot/`, eseguite
una volta:

```bash
cd "$HOME/PhysCode/alphaplot"
printf '\nexport PATH="$PATH:%s"\n' "$PWD" >> "$HOME/.zshrc"
```

Aprite un nuovo terminale. Il comando `start.sh` sarà raggiungibile da qualunque
cartella:

```bash
start.sh
```

Docker Desktop e XQuartz devono essere in esecuzione prima di avviare lo script.

#### Utilizzo e salvataggio dei progetti

Poiché state utilizzando un container, il filesystem — dove vengono salvati i
file — non è lo stesso del vostro computer.

Quando volete **salvare** un progetto di AlphaPlot, è **FONDAMENTALE**, per non
perdere i progressi, scegliere **Home** (in alto a sinistra) e poi la sottocartella
**AlphaPlot**, nella finestra che compare selezionando
**File → Save Project (Ctrl+S)**.

![Cartella AlphaPlot da usare per salvare i progetti](assets/alphaplot/fig.png)

Questa cartella corrisponde alla cartella `alphaplot-data` sul vostro computer,
raggiungibile con:

```bash
cd ~/alphaplot-data
```

Salvate lì i progetti da conservare anche dopo la chiusura del container.


## Tastiera italiana

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

## Carattere ~
### (su tastiera italiana)

Scaricare la "Current Version" di AutoHotKey da https://www.autohotkey.com/

Scaricare lo script [keysetup.ahk](https://drive.google.com/file/d/18K3zTnvYTa_hywJYgyN9gkIX4jaEuT5d/view?usp=sharing), assicurandosi che mantenga .ahk come estensione

Aprire il percorso file alla cartella "Esecuzione Automatica" premendo WIN+R e scrivendo shell:startup nella barra di ricerca

Trasferire lo script "keysetup" in questa cartella, che permetterà la sua attivazione automatica ad ogni accensione di Windows

Riavviare il PC

Per usare i caratteri speciali basterà procedere come segue:

"tilde" (~)                     ---> Premere Alt + -  (trattino della tastiera)

apostrofo per Root (`) ---> Premere Alt + '   (apostrofo normale)

<a id="accesso-ai-file"></a>

## Copia Linux Windows
### (come accedere a Windows/Linux da Linux/Windows)

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
