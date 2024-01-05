# Evoluzione comportamentale

# Relazione del progetto

### Realizzato da Azzano Michele

[Link per GitHub](https://github.com/SomeItalianGuy/Esame_Azzano)

## Contenuti

- [**Introduzione**](#introduzione)
- [**Metodi implementativi**](#metodi-implementativi)
    - [**Struttura del progetto**](#struttura-del-progetto)
    - [**Implementazione della popolazione**](#implementazione-della-popolazione)
    - [**Implementazione della simulzione**](#implementazione-della-simulzione)
- [**Come compilare**](#come-compilare)
- [**Interazione con il programma**](#interazione-con-il-programma)
    - [**Input**](#input)
    - [**Output**](#output)
    - [**Analisi dati**](#analisi-dati)
- [**Modalità di test**](#modalità-di-test)
- [**Avvertenze**](#avvertenze)
    - [**Framework di ROOT**](#framework-di-root)
    - [**Estensioni consigliate**](#estensioni-consigliate)
    - [**Errori previsiti**](#errori-previsti)
- [**Link Utili**](#link-utili)

## Introduzione

Lo scopo principale del programma da me presentato è quello di simulare l'evoluzione del comportamento di una popolazione di individui.  
In questo contesto si considerano individui capaci di uno solo di tre comportamenti:  

- Passivo, l'individuo eviterà i conflitti per cercare di dividere equamente il cibo;
- Aggressivo, l'individuo tende a prendere la maggior parte del cibo per sè, ma perderà molte energie se dovesse entrare in competizione;
- Adattabile, l'individuo apprezzerà l'altruismo del Passivo, lasciandogli più cibo, se dovesse incontrare un individuo aggressivo prenderà la maggior parte del cibo.

Dato questo setup, simile a "Sasso, Carta, Forbice", dove ciacuna opzione ha una forza e una debolezza, si lasciano passare le generazioni desiderate e si nota come la popolazione sia evoluta.  
In questa simulazione si considera l'assenza di altri esseri viventi e una proporzionailtà diretta tra cibo trovato e possibilità di sopravvivenza/riproduzione.  
Per la relaizzazione del progetto ho considerato un sistema dove, per ogni generazione, viene creata una certa quantità di luoghi, ciascuno dei quali contenenti due unità di cibo.  
A questo punto ciascun individuo, in maniera casuale, si dirige a uno di questi luoghi, se questo individuo fosse solo, allora tornerà a casa con due unità di cibo e sarà sicuro di sopravvivere e riprodursi, se invece incontrasse un altro individuo allora vi sarà un'interazione basata sulle personalità dei due contendenti per decidere come dividersi le vivande.  
Verranno dunque calcolate, su base casuale, la sopravvivenza e la riproduzione di ciascun individuo, dunque vengono stampati a schermo i risultati generazione per generazione.  
Alla fine della raccolta dati verrà data l'opzione di salvare questi su un file di testo e, se l'opzione per usare root fosse abilitata, stampare grafici relativi all'andamento della popolazione. 

## Metodi implementativi

### Struttura del progetto

Per realizzare il progetto ho sfruttato diverse classi: 

- Individual: si occupa di definire i singoli individui;
- Population: gestisce una moltitudine di individui;
- RNGHelper: generazione di numeri pseudo-casuali;
- RootHelper: ha il compito di disegnare grafici;
- Simulation: gestisce le interazioni fra le altre classi.

In più ho aggiunto alcuni namespace con funzioni per rendere più pulito il codice:

- Logic: si occupa di input e generazione di vettori;
- Graphic: si occupa della stampa a schermo

### Implementazione della popolazione

Al fine di rendere questa simulazione più verosimile, ho messo dei limiti alla quantità di individui della popolazione.  
Il primo limite è quello assoluto, si considera un ambiente dove il cibo non è infinito, dunque la popolazione non potrà mai superare una certa soglia, che ho deciso di chiamare `Population::maxPopulation_`.  
Il secondo è la popolaizone massima per ciascuna generazione, calcolata tramite un semplice prodotto tra la popolazione massima sopra citata e una percentuale che varia da generazione a generazione, si ottiene tramite il metodo `Population::Get_genMaxPopulation()`.  
Per imitare la variabilità delle condizioni ambientali, con periodi più prosperi e periodi con meno risorse, ho sfruttato una mappa logistica ([Link se si desiderasse approfondire l'argomento](#mappa-logistica)), nello specifico la parte caotica di tale mappa per calcolare la percentuale utilizzata da `Population::Get_genMaxPopulation()`.

### Implementazione della simulzione

Ritengo sia necessario spendere alcune parole per spiegare alcuni  metodi che potrebbero non essere evidenti a prima vista.  
Il primo di cui parlerò  è `Simulation::SetRandomPlaces`. Questo metodo fa uso del vettore `s_idList`, ovvero il vettore che contiene tutti gli identificativi e per ciascuno di questi viene assegnato a un luogo casuale.

<!-- TODO controllare se c'è altro da aggiungere qui -->

## Come compilare

| Azione | Comando |
|--------|---------|
| Configurare CMake | `cmake -B "path-to-build" -S .` |
| Abilitare/Disabilitare ROOT | `-DUSE_ROOT=ON` / `-DUSE_ROOT=OFF` | 
| Abilitare/Disabilitare i test | `-DBUILD_TESTING=ON` / `-DBUILD_TESTING=OFF` | 
| Buildare i file, creare e linkare l'eseguibile | `cmake --build "path-to-build"` |
| Eseguire il programma principale | `./"path-to-build"/main` |
| Eseguire i test | `./"path-to-build"/main.test` |

Si noti che:

- Il comando per abilitare/disabilitare opzioni deve essere chiamato in contemporanea alla configurazione di CMake;
- In diversi comandi è necessario sostiutire "path-to-build" con il path alla cartella all'interno della quale si desidera avere gli eseguibili.

## Interazione con il programma

### Input

Per l'input sarà sufficiente seguire le istruzioni che verranno date a schermo durante il *runtime*, verranno chiesti, in ordine:

- Seed, necessario alla generazione di numeri pseudo-casuali;
- Numero iniziale di individui passivi;
- Numero iniziale di individui aggressivi;
- Numero iniziale di individui adattabili;
- Comando per far procedere la simulazione;
- Se si desidera salvare i risultati su un file;
- Nome del file in cui salvare i dati;
- Nome da dare alla simulazione, si noti che si può usare lo stesso file più volte;

### Output

A livello di *output* vi è la necessità di distinguere tra il terminale e i file generati.  
Quando vengono fatte girare un certo numero di generazioni, ci si può aspettare un risultato simile a:  

![Esempio output](readme/output-example.PNG)  

Una volta che si è soddsfatti della quantità di dati raccolti, si può passare alla fase di salvataggio della simulazione:  

![Salvataggio dati](readme/Quit-&-Save-example.PNG)  

Oppure, nel caso in cui non si sia utilizzato ROOT, si avrà:  

![Salvare senza root](readme/No-root-save-example.PNG)  

Se invece non si è soddisfatti della quantità di dati raccolti, si può sempre evitare di salvare, in tal caso il programma verrà immediatamente chiuso.  
Una volta salvati i file, questi verranno creati all'interno della cartella `results/`, che verrà creata in automatico se non fosse esistente, nell'esempio seguente ho dato al file il nome "Demo":  

![Esempio file creati](readme/Example-created-files.PNG)  

Consiglio di usare il file `.txt` se si fosse interessati ad un'analisi quantitativa dei dati, se si fosse interessati solo ad una analisi qualitativa allora il file `.root` sarà più che sufficiente, lascio di seguito degli esempi di questi ultimi:  

- File `.txt`  

![Esempio file txt](readme/txt-file-example.PNG)  

- File `.root`  

![Esempio file root](readme/root-file-example.PNG)  

### Analisi dati


## Modalità di test

Per assicurare il corretto funzionamento della maggior parte delle funzioni e dei metodi ho abilitato diversi test fatti con l'utilizzo di docTest.  
I test sono divisi in base alla classe o *namespace*, un'altra suddivisione viene fatta per il singolo pezzo di codice il cui funzionamento è messo alla prova. La maggior parte di questi test sono `CHECK_THROWS`, ovvero controlli che, in determinate condizioni, il codice lanci errori, questo è stato inevitabile, essendo il mio programma un sistema caotico, non è facile prevedere i risultati finali e la maggior parte dei controlli sono da fare al *runtime*.  


## Avvertenze

### Framework di ROOT

Per il corretto funzionamento di questo progetto sarà necessario avere installato il *framework* di ROOT, nel caso in cui non lo si avesse ancora installato, si può trovare una guida [qui](#guida-installazione-root)

### Estensioni consigliate

Dal momento che viene creato un file root, sarà necessaria un'estensione di VSCode, mi sento di raccomandare l'estensione che ho utilizzato durante lo sviluppo di questo progetto, ROOT File Viewer.  

![Estensione root](readme/Estensione-root.PNG)

### Errori previsti

Di seguito lascio un possibile errore che verrà dato nel caso si utilizzi un eseguibile abilitando ROOT, la causa di questo è il framework di ROOT, poiché questo istanzia dei puntatori a oggetti globali la cui memoria non viene deallocata, il codice funziona perfettamente fino al momento della cancellazione degli oggetti, a questo punto darà errore:

![Errore root](readme/ROOT-errror-Example.PNG)  

Se si volesse sfruttare il programma senza ricevere questo tipo di errore allora sarà necessario disabilitare root, il comando atto a questo scopo può essere trovato [qui](#come-compilare).

## Link utili

###### Mappa logistica
- [Pagina wikipedia](https://it.wikipedia.org/wiki/Mappa_logistica)
- [Video youtube consigliato](https://www.youtube.com/watch?v=ovJcsL7vyrk)

###### Guida installazione ROOT
- [Sito ufficiale ROOT](https://root.cern/install/)

[Premi qui](#contenuti) per tornare all'indice.