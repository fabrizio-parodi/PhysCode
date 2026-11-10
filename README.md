# PhysCode - Installazione software per i Corsi di Studio in Fisica

[C. Cardinale, F.Parodi, F.Sforza, M. Sotgia, S. Turchikhin]

Le presenti istruzioni descrivono come installare sul proprio computer il software di base necessario 
per gli insegnamenti dei corsi di Laurea in Fisica e di Laurea Magistrale in Fisica dell’Università di Genova.

La condivisione, il riutilizzo e l’adattamento di questo materiale sono incoraggiati. 
Salvo diversa indicazione, il testo è distribuito con licenza Creative Commons Attribuzione 4.0 Internazionale (CC BY 4.0), 
che consente di copiarlo, distribuirlo e modificarlo, anche per fini commerciali, purché siano riconosciuti gli autori, citata la fonte, fornito un collegamento alla licenza e indicate le eventuali modifiche.

I programmi descritti restano soggetti alle rispettive licenze d’uso. Per il software open source, i diritti di utilizzo, modifica e redistribuzione e i relativi obblighi sono stabiliti dalla licenza di ciascun progetto, secondo i criteri della Open Source Definition dell’Open Source Initiative.

Le istruzioni usano lo script [`setup_physcode.sh`](setup_physcode.sh), incluso nel repository, per installare Pixi e preparare l’ambiente PhysCode.

Scegliete il vostro sistema operativo:

- [Windows con WSL](#windows)
- [Linux](#linux)
- [macOS](#macos)

Poi seguite [Configurazione di PhysCode](#configurazione-di-physcode) e [Usare PhysCode](#usare-physcode).

Per Laboratorio di Fisica 1 consultate anche [AlphaPlot](#alphaplot). In fondo trovate indicazioni sulla [tastiera italiana](#tastiera-italiana), sul [carattere ~](#caratteri-speciali) e sullo [scambio di file tra Linux e Windows](#accesso-ai-file).

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

Al termine dovrebbe avviarsi Ubuntu automaticamente.

Se non fosse così avviatelo con

```powershell
wsl -d Ubuntu-24.04

```
Al primo avvio, attendete il completamento della configurazione e create il vostro account Linux, scegliendo un nome utente e una password.

ATTENZIONE ALLA PASSWORD: la password NON è visibile durante la digitazione quindi assicurarsi di inserirla correttamente (e annotarla), e solo DOPO premere “Invio”. Se la procedura non viene seguita correttamente, l’utente del sistema Linux risulta essere “root”, cioè l'amministratore di sistema (o super-utente). In questo caso la procedura di installazione va ripetuta.

Aprite il terminale di Ubuntu e installate Git:

```bash
sudo apt update
sudo apt install -y git
```

Proseguite con [Configurazione di PhysCode](#configurazione-di-physcode), eseguendo i comandi nel terminale di Ubuntu.

## Linux

Lo script supporta distribuzioni con `apt`, come Ubuntu e Debian, e shell Bash o Zsh.

Aprite il terminale e installate Git:

```bash
sudo apt update
sudo apt install -y git
```

Proseguite con [Configurazione di PhysCode](#configurazione-di-physcode).

## macOS

Aprite **Terminale** e verificate che siano disponibili i Command Line Tools di Apple:

```bash
xcode-select -p
```

Se il comando restituisce un errore, avviate l’installazione con:

```bash
xcode-select --install
```

Completate l’installazione nella finestra che si apre prima di continuare. I Command Line Tools includono Git; potete verificarlo con:

```bash
git --version
```

Proseguite con [Configurazione di PhysCode](#configurazione-di-physcode). Lo script installerà Homebrew, se necessario, e Pixi; supporta sia Mac Intel sia Mac con chip Apple Silicon.

## Configurazione di PhysCode

Scaricate il repository nella vostra cartella personale:

```bash
git clone https://github.com/fabrizio-parodi/PhysCode.git "$HOME/PhysCode"
```

Se avete già scaricato il repository in quella posizione, aggiornate invece la copia esistente:

```bash
git -C "$HOME/PhysCode" pull --ff-only
```

Eseguite lo script incluso nel repository:

```bash
bash "$HOME/PhysCode/setup_physcode.sh"
```

Usate `bash`, senza `source` e senza anteporre `sudo`. Lo script chiederà la password quando necessaria; durante la digitazione la password non viene mostrata.

Lo script:

- installa Pixi se non è già disponibile e, su macOS, Homebrew se necessario;
- installa l’ambiente definito nel file `pixi.toml`;
- configura l’avvio automatico dell’ambiente PhysCode nei nuovi terminali Bash o Zsh.

Git e il repository vengono preparati nei passaggi precedenti: lo script non li installa né li aggiorna.

La prima installazione può richiedere diversi minuti. Attendete il messaggio **«Fatto: chiudi e riapri il terminale.»**, quindi chiudete e riaprite il terminale (Ubuntu, su Windows).

Se lo script richiede l’installazione dei Command Line Tools, completatela e rilanciate lo stesso comando. In caso di errore, correggete il problema segnalato e rieseguite lo script.

La configurazione viene salvata in `~/.zshrc` per Zsh, in `~/.bash_profile` per Bash su macOS e in `~/.bashrc` per Bash su Linux/WSL. Prima della modifica viene creata una copia con estensione `.bak`, sovrascritta a ogni esecuzione. Per Bash, l’avvio automatico richiede che il terminale legga il file indicato.

## Usare PhysCode

Nei nuovi terminali l’ambiente PhysCode viene attivato automaticamente. Sono disponibili Python con NumPy, SciPy, Matplotlib, pandas e JupyterLab, oltre a compilatori C/C++, CMake, Emacs e ROOT.

Se volete attivare l’ambiente manualmente, usate:

```bash
pixi shell --manifest-path "$HOME/PhysCode/pixi.toml"
```

Eseguite questo comando soltanto quando non siete già nell’ambiente. Per uscire, digitate `exit`: i programmi installati e i file salvati restano disponibili, mentre si disattivano le impostazioni dell’ambiente nella shell corrente.

Per aggiornare PhysCode:

```bash
git -C "$HOME/PhysCode" pull --ff-only
bash "$HOME/PhysCode/setup_physcode.sh"
```

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

Una volta avviato Docker Desktop, lanciate:

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
posizione della sua directory. Da dentro `PhysCode/alphaplot/`, eseguite
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
