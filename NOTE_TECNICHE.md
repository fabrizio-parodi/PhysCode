# Note tecniche per gli studenti

Queste note completano il [README](README.md). Consultale quando serve un
chiarimento su WSL, tastiera, file o configurazioni alternative.

## Verificare la versione di WSL

In **PowerShell**, esegui:

```powershell
wsl -l -v
```

La colonna `VERSION` della distribuzione usata per il laboratorio deve indicare
`2`. Il nome può essere `Ubuntu-24.04`, `Ubuntu` o un altro nome già presente.
Non reinstallare la distribuzione soltanto perché il nome è diverso.

Se la distribuzione è ancora WSL1, salva il lavoro e chiedi assistenza per la
conversione a WSL2. Se WSLg non è disponibile, segui la
[guida Microsoft](https://learn.microsoft.com/en-us/windows/wsl/tutorials/gui-apps).
Il supporto grafico richiede Windows 10 build 19044 o successiva, oppure
Windows 11, con i requisiti descritti nella guida.

Questo laboratorio usa WSLg: le procedure per WSL1 con VcXsrv/XLaunch non
servono. Non è necessario disabilitare il controllo degli accessi di un server X.

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
