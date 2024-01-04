# Relazione del progetto

### Realizzato da Azzano Michele

## Contents

- [**Introduzione**](#introduzione)
- [**Metodi implementativi**](#metodi-implementativi)
    - [**Implementazione della popolazione**](#implementazione-della-popolazione)

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

### Implementazione della popolazione

Al fine di rendere questa simulazione più verosimile, ho messo dei limiti alla quantità di individui della popolazione.  
Il primo limite è quello assoluto, si considera un ambiente dove il cibo non è infinito, dunque la popolazione non potrà mai superare una certa soglia, che ho deciso di chiamare `Population::maxPopulation_`.  
Il secondo è la popolaizone massima per ciascuna generazione, per imitare la variabilità delle condizioni ambientali, con periodi più prosperi e periodi con meno risorse, ho sfruttato una mappa logistica ([Link se si desiderasse approfondire l'argomento](#mappa-logistica)), nello specifico la parte caotica di tale mappa.

## Link utili

###### Mappa logistica :
- [Pagina wikipedia](https://it.wikipedia.org/wiki/Mappa_logistica)
- [Video youtube consigliato](https://www.youtube.com/watch?v=ovJcsL7vyrk)