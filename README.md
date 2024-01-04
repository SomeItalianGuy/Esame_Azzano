# Contents

- [*Abstract*](#abstract)

# Abstract

Lo scopo principale del programma da me presentato è quello di simulare l'evoluzione del comportamento di una popolazione di individui.  
In questo contesto si considerano individui capaci di uno solo di tre comportamenti:  

- Passivo, l'individuo eviterà i conflitti per cercare di dividere equamente il cibo;
- Aggressivo, l'individuo tende a prendere la maggior parte del cibo per sè, ma perderà molte energie se dovesse entrare in competizione;
- Adattabile, l'individuo apprezzerà l'altruismo del Passivo, lasciandogli più cibo, se dovesse incontrare un individuo aggressivo prenderà la maggior parte del cibo.

Dato questo setup, simile a "Sasso, Carta, Forbice", dove ciacuna opzione ha forza e debolezza, si lasciano passare le generazioni desiderate e si nota come la popolazione sia evoluta.  
In questa simulazione si considera l'assenza di altri esseri viventi e una proporzionailtà diretta tra cibo trovato e possibilità di sopravvivenza/riproduzione.  
Si noti che non è davvero possibile prevedere a priori uno sviluppo preciso della distribuzione di individui, è tuttavia possibile fare tale previsione una volta date le condizioni iniziali della popolazione, è sufficiente fare un calcolo del cibo medio ottenuto da ciascun tipo di individuo in funzione della quantità di individui con altri tipi di personalità, questa darà luogo a tre funzioni, sarà dunque sufficiente metterle a sistema e trovare quale percentuale di ciascun individuo risulta in una popolazione stabile.