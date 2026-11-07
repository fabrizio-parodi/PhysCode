# Note tecniche per gli studenti

Queste note completano il [README](README.md). Consultale quando serve un
chiarimento su WSL, tastiera, file o configurazioni alternative.

## Indice

- [Verificare la versione di WSL](#verificare-la-versione-di-wsl)
- [Scegliere WSL1 o WSL2](#scegliere-wsl1-o-wsl2)
- [Installare o aggiornare WSL](#installare-o-aggiornare-wsl)
- [Selezionare la versione e convertire una distribuzione](#selezionare-la-versione-e-convertire-una-distribuzione)
- [Abilitazione manuale dei componenti Windows](#abilitazione-manuale-dei-componenti-windows)
- [Grafica WSL2 con WSLg](#grafica-wsl2-con-wslg)
- [Grafica WSL1 con VcXsrv e XLaunch](#grafica-su-wsl1-con-vcxsrv-e-xlaunch)
- [Account Ubuntu e password](#account-ubuntu-e-password)
- [Tastiera italiana e caratteri speciali](#tastiera-italiana-e-caratteri-speciali)
- [Scambiare file tra Windows e Ubuntu](#scambiare-file-tra-windows-e-ubuntu)
- [AlphaPlot con Flatpak](#alphaplot-installato-con-flatpak)
- [Macchina virtuale](#usare-una-macchina-virtuale)

## Verificare la versione di WSL

In **PowerShell**, esegui:

```powershell
wsl -l -v
```

La colonna `VERSION` indica `1` o `2` per ogni distribuzione installata.
Non indica la release di Ubuntu: `Ubuntu-24.04` può essere eseguito con WSL1 o
WSL2. Il nome può anche essere `Ubuntu` o un altro nome già presente; nei comandi
successivi usa esattamente quello mostrato nell'elenco.

Per vedere la versione di Windows premi `Win+R`, digita `winver` e premi Invio.
Per informazioni sul componente WSL puoi usare `wsl --version`, se disponibile.
Quest'ultimo comando non sostituisce `wsl -l -v`: descrive il software WSL,
non la modalità della singola distribuzione.

## Scegliere WSL1 o WSL2

| Configurazione | Caratteristiche | Grafica |
|---|---|---|
| WSL2 | Kernel Linux in una macchina virtuale gestita da Windows; modalità prevista per il setup Pixi del corso. Richiede supporto alla virtualizzazione. | WSLg, quando disponibile. |
| WSL1 | Livello di compatibilità per le chiamate Linux; può essere utile su configurazioni che non consentono WSL2. | Server X esterno, ad esempio VcXsrv. |

**Windows 10 non obbliga a usare WSL1.** Può usare WSL2 se la versione di Windows
e il computer ne soddisfano i requisiti. Anche Windows 11 può ospitare
distribuzioni WSL1, se il relativo componente è abilitato. Per il confronto
vedi la [documentazione Microsoft](https://learn.microsoft.com/en-us/windows/wsl/compare-versions).

Per il laboratorio scegli WSL2 con WSLg quando possibile. Le istruzioni WSL1
qui sotto mantengono il percorso alternativo con server X esterno, ma la
compatibilità dell'intero ambiente Pixi e della grafica Geant4 su WSL1 va
verificata con le prove del README. Un server X risolve il collegamento grafico,
non le eventuali incompatibilità delle librerie o delle chiamate di sistema.

## Installare o aggiornare WSL

Apri **PowerShell come amministratore**: cerca PowerShell nel menu Start,
premi il tasto destro e scegli **Esegui come amministratore**. Aggiorna Windows
prima di procedere e verifica la connessione Internet.

Se WSL è già presente:

```powershell
wsl --update
```

Per una nuova installazione con Ubuntu 24.04:

```powershell
wsl --install -d Ubuntu-24.04
```

Riavvia se richiesto. Se il nome della distribuzione non è riconosciuto,
controlla l'elenco disponibile con `wsl --list --online`.
Se questi comandi non sono supportati dalla tua installazione di Windows,
consulta l'[abilitazione manuale](#abilitazione-manuale-dei-componenti-windows).

## Selezionare la versione e convertire una distribuzione

Per scegliere la modalità delle **nuove distribuzioni**, esegui uno dei seguenti
comandi in PowerShell, secondo la configurazione scelta:

```powershell
# WSL2, percorso previsto per il laboratorio
wsl --set-default-version 2
```

Oppure, se hai concordato l'uso di WSL1:

```powershell
wsl --set-default-version 1
```

Questi comandi non convertono le distribuzioni già installate.
Per convertire Ubuntu 24.04 da WSL1 a WSL2:

```powershell
wsl --set-version Ubuntu-24.04 2
wsl -l -v
```

La conversione inversa, quando prevista dalla configurazione scelta, usa:

```powershell
wsl --set-version Ubuntu-24.04 1
```

Sostituisci `Ubuntu-24.04` con il tuo nome di distribuzione. Prima della
conversione salva il lavoro e una copia dei file importanti; l'operazione può
richiedere tempo. Per un backup completo puoi usare, da PowerShell:

```powershell
wsl --export Ubuntu-24.04 "$env:USERPROFILE\Desktop\ubuntu-backup.tar"
```

Verifica di avere spazio per il file di backup. Le modalità di selezione,
conversione ed esportazione sono descritte nei
[comandi WSL di Microsoft](https://learn.microsoft.com/en-us/windows/wsl/basic-commands).

## Abilitazione manuale dei componenti Windows

Questa procedura serve quando l'installazione automatica non è disponibile o
quando manca un componente Windows richiesto. Da PowerShell come amministratore,
per abilitare il componente necessario a WSL1:

```powershell
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
```

Per WSL2 abilita anche la piattaforma di virtualizzazione:

```powershell
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
```

Riavvia Windows. WSL2 richiede inoltre che la virtualizzazione del processore
sia disponibile e abilitata nel BIOS/UEFI. Nelle installazioni meno recenti
può essere necessario anche il pacchetto di aggiornamento del kernel Linux:
segui la [procedura manuale Microsoft](https://learn.microsoft.com/en-us/windows/wsl/install-manual),
che distingue requisiti e passaggi per WSL1 e WSL2.

Completata la preparazione, seleziona la versione predefinita e installa Ubuntu
con il comando disponibile sul tuo sistema o dal Microsoft Store. Al primo
accesso crea l'[account personale Ubuntu](#account-ubuntu-e-password), poi torna
al [README](README.md#installare-lambiente-del-laboratorio) per Pixi.

## Grafica WSL2 con WSLg

WSLg integra le finestre Linux nel desktop Windows. Richiede Windows 10 build
19044 o successiva, oppure Windows 11, oltre ai requisiti indicati nella
[guida Microsoft](https://learn.microsoft.com/en-us/windows/wsl/tutorials/gui-apps).
La disponibilità di WSL2, da sola, non dimostra che WSLg sia disponibile.

Aggiorna WSL con `wsl --update`. Per applicare l'aggiornamento, dopo aver salvato
il lavoro in tutte le sessioni WSL, esegui da PowerShell:

```powershell
wsl --shutdown
```

Riapri Ubuntu. Non occorre avviare XLaunch né impostare manualmente `DISPLAY`:
WSLg configura il collegamento grafico. Non aggiungere alla shell le
impostazioni `DISPLAY` della procedura WSL1 qui sotto.

## Grafica su WSL1 con VcXsrv e XLaunch

WSL1 non include WSLg. Per usare Emacs grafico, ROOT o altre applicazioni X11,
installa su Windows [VcXsrv](https://github.com/marchaesen/vcxsrv), disponibile
anche dalla [pagina SourceForge](https://sourceforge.net/projects/vcxsrv/).

Prima di ogni sessione di lavoro:

1. Avvia **XLaunch** dal menu Start.
2. Scegli **Multiple windows**, display `0`, poi **Start no client**.
3. Completa la configurazione del server X. La procedura del materiale del
   corso indica l'opzione **Disable access control**: se viene usata, disabilita
   l'autenticazione dei client X; limita l'accesso al computer locale e mantieni
   le restrizioni del firewall, senza consentire connessioni da reti pubbliche.
4. Lascia VcXsrv in esecuzione mentre usi le applicazioni grafiche Linux.
5. Nel terminale **Ubuntu su WSL1**, prima di avviare l'applicazione, imposta:

```bash
export DISPLAY=localhost:0.0
```

Se il profilo del server usa un altro numero di display, adegua il valore.
Avvia quindi, dalla cartella del laboratorio, `pixi run --locked editor` oppure
una delle prove grafiche del README. Se compare `cannot open display`, controlla
che VcXsrv sia avviato, che il display corrisponda e che il firewall non blocchi
il collegamento locale. Se le finestre si aprono ma Geant4 fallisce, il problema
può riguardare OpenGL: conserva l'errore e chiedi assistenza.

Questa impostazione `DISPLAY` riguarda WSL1. WSL2 con server X esterno può
richiedere un indirizzo diverso in base alla rete; non applicare automaticamente
`localhost:0.0` a WSL2. Se WSLg funziona, usa il percorso WSLg sopra.

## Account Ubuntu e password

Al primo avvio di Ubuntu crea il tuo utente Linux e scegli una password.
La password non compare durante la digitazione: è il comportamento normale
del terminale. Anche `sudo` richiede la password dell'utente Linux.

Per vedere con quale utente stai lavorando, nel terminale Ubuntu esegui:

```bash
whoami
```

Se compare `root`, sei nell'account amministratore Linux. Usa l'account personale
per le attività del corso. Se non sai come accedervi, chiedi assistenza:
non occorre reinstallare automaticamente Ubuntu.

Se hai dimenticato la password, è possibile reimpostarla senza cancellare i
file. Segui la procedura Microsoft per
[configurare l'account e recuperare la password WSL](https://learn.microsoft.com/en-us/windows/wsl/setup/environment).

## Tastiera italiana e caratteri speciali

Prima di lavorare controlla che nelle impostazioni di Windows sia selezionato
il layout della tua tastiera. Se i caratteri non corrispondono ai tasti, verifica
il layout anche nell'applicazione o nella sessione Linux che stai usando.
Le impostazioni delle *locales* riguardano lingua e formati: non sostituiscono
la scelta del layout della tastiera.

I seguenti caratteri hanno significati diversi nei comandi:

| Carattere | Nome | Esempio di utilizzo |
|---|---|---|
| `~` | Tilde | `cd ~` torna alla cartella personale. |
| `'` | Apostrofo semplice | Delimita una stringa nella shell. |
| `` ` `` | Accento grave o backtick | Compare in alcuni esempi di comandi; è diverso dall'apostrofo. |

Puoi copiare questi caratteri dal testo. Nel terminale Ubuntu puoi normalmente
incollare con `Ctrl+Shift+V`; nel terminale di Windows usa la scorciatoia
configurata nell'applicazione.

### Scorciatoie con AutoHotkey su Windows

Il materiale del corso include uno
[script per la tastiera `keysetup.ahk`](https://drive.google.com/file/d/18K3zTnvYTa_hywJYgyN9gkIX4jaEuT5d/view?usp=sharing)
da usare con [AutoHotkey](https://www.autohotkey.com/).
Se scegli questa soluzione, usa una versione AutoHotkey compatibile con lo
script: uno script scritto per la versione 1 non è automaticamente compatibile
con la versione 2. Se compare un errore, conserva il messaggio e chiedi assistenza.

La configurazione descritta nel materiale del corso associa:

- `Alt` + `-` alla tilde `~`;
- `Alt` + `'` all'accento grave `` ` ``.

Queste combinazioni dipendono dallo script; non sono scorciatoie standard di
Windows. Dopo averlo scaricato, controlla che il nome termini con `.ahk` e non
con `.ahk.txt`. Provalo prima di impostare l'avvio automatico.

Per eseguirlo a ogni accesso, premi `Win+R`, digita `shell:startup` e premi Invio;
inserisci nella cartella un collegamento allo script. Mantieni disponibile lo
script nella posizione a cui punta il collegamento.

## Scambiare file tra Windows e Ubuntu

Per compilare ed eseguire gli esercizi in WSL, conserva progetto e risultati
nella cartella personale Linux, ad esempio `~/labmcs-pixi`.

### Da Ubuntu ai file Windows

Il disco Windows `C:` è normalmente disponibile in `/mnt/c`:

```bash
ls /mnt/c
ls "/mnt/c/Users/NOME_UTENTE_WINDOWS/Desktop"
```

Sostituisci `NOME_UTENTE_WINDOWS` con il nome della tua cartella utente Windows.
Le virgolette sono utili per percorsi contenenti spazi.

### Da Windows ai file Ubuntu

Nel terminale Ubuntu, entra nella cartella da aprire ed esegui:

```bash
explorer.exe .
```

Oppure inserisci `\\wsl$` nella barra degli indirizzi di Esplora file e scegli
la distribuzione. Un percorso tipico è:

```text
\\wsl.localhost\Ubuntu-24.04\home\NOME_UTENTE_LINUX
```

Usa il nome di distribuzione mostrato da `wsl -l -v` e il tuo nome utente Linux.
Queste modalità di accesso sono supportate da WSL. Evita di aprire direttamente
i file interni della distribuzione sotto `AppData`, `LocalState` o `rootfs`.
Per i dettagli consulta la
[guida Microsoft ai filesystem Windows e Linux](https://learn.microsoft.com/en-us/windows/wsl/filesystems).

## AlphaPlot installato con Flatpak

Se hai scelto l'installazione Flatpak su Linux o dentro WSL, avvia AlphaPlot con:

```bash
flatpak run io.github.narunlifescience.AlphaPlot
```

Questo comando richiede che Flatpak e l'applicazione siano già installati nel
sistema da cui lo esegui. Non si usa per il pacchetto Windows o per l'app macOS.
Per informazioni sull'applicazione vedi
[AlphaPlot su Flathub](https://flathub.org/apps/io.github.narunlifescience.AlphaPlot).

## Usare una macchina virtuale

Se il setup principale non funziona sul tuo computer, concorda con un docente
o tutor l'uso della macchina virtuale del corso. Scaricare una VM non è un
passaggio necessario per usare Pixi.

Nel materiale del corso è indicata un'immagine
[Ubuntu 24.04 `Ubuntu64.ova`](https://drive.google.com/file/d/15HLRRobGohfF7JslssCji1r2R16mEvuc/view?usp=drive_link).
Prima di scaricarla verifica con il tutor che sia quella prevista per il tuo
computer. La compatibilità dipende anche dall'architettura: in VirtualBox un
sistema guest x86 non può essere eseguito su un host ARM, come un Mac Apple
Silicon. Vedi i [requisiti ufficiali di VirtualBox](https://docs.oracle.com/en/virtualization/virtualbox/7.2/user/installation.html).

Se l'immagine è adatta al tuo computer:

1. Installa la versione di [VirtualBox](https://www.virtualbox.org/) indicata
   per il corso. Se è richiesto anche l'Extension Pack, usa la versione
   corrispondente a quella di VirtualBox.
2. Su Windows verifica che la virtualizzazione sia disponibile e abilitata,
   seguendo le [istruzioni Microsoft](https://support.microsoft.com/en-us/windows/enable-virtualization-on-windows-c5578302-6e43-4b4b-a449-8ced115f58e1).
3. Riserva spazio per l'immagine e per i tuoi file. Il materiale indica almeno
   10 GB; verifica anche lo spazio richiesto dalla VM effettivamente fornita.
4. In VirtualBox scegli **File → Import Appliance**, seleziona il file `.ova`
   scaricato e completa l'importazione.
5. Avvia la VM. Per l'immagine citata nel materiale, le credenziali iniziali
   riportate sono utente `vboxuser` e password `calcolo24`. Se la versione
   distribuita è diversa, usa le credenziali comunicate con quella versione.
6. Nel desktop Linux apri **Settings → Display** per scegliere una risoluzione
   adatta allo schermo. Puoi regolare la scala anche dal menu di VirtualBox
   **View → Virtual Screen 1**.

Mantieni copie dei tuoi esercizi anche fuori dalla VM. Per le modalità di
condivisione dei file e l'ambiente già presente nell'immagine segui le
indicazioni date per il corso.
