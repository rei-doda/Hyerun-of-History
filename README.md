# Hyerun-of-History
## Text adventure game in C

### Benvenuti in Hyerun of History


A causa di un fato mal scritto, le Norne mi hanno condotto per un sentiero pericoloso. Senza una motivazione degna di onore ma solo per la fame di ottenere più ricchezze, iniziai un viaggio inaspettato che mi condusse di fronte ai cancelli di Hyerun, un antico castello in rovina. Quei cancelli in legno di quercia orami invecchiati e le cerniere di ferro arrugginite, avrebbero spaventato chiunque. Uno strano luccichio fuoriesce da una vetrata al terzo piano del castello. Quell’immagine mi incuriosì ed entrai nel castello. Mi ritrovai in una grande sala, in passato questo era il luogo dove il re accoglieva i suoi ospiti.

I comandi di gioco sono brevi frasi da inserire per procedere nel gioco. Se digiti “guardare”, il gioco ti fornisce una descrizione di ciò che ti circonda. Digitando "inventario" ti dice cosa stai trasportando. Comandi come “aprire” o “prendere” ti aiutano a interagire con gli oggetti. Puoi digitare in qualsiasi momento “comandi” per avere la lista dei comandi che puoi utilizzare nel gioco_

# Comandi e operazioni principali 
## Avvio del gioco
All’avvio del gioco, l’utente è presentato con una breve presentazione della trama e del motivo del
gioco, che termina con l’utente che “prende il controllo” del personaggio giocabile. L’utente può
iniziare a giocare, scrivere “comandi”, per avere una breve guida del gioco, contenente i comandi che
possono essere utilizzati. I comandi di base sono utilizzabili in ogni momento della partita ad eccezione
di quando il giocatore si trova immischiato in un conflitto contro un nemico, in quel caso solo un
ristretto elenco di comandi sarà utilizzato, ovvero i comandi di combattimento. Scrivere “continuare”
per riprendere una partita iniziata in precedenza. Inoltre, sarà possibile grazie al comando “salvare”
salvare la propria partita in un qualsiasi momento. 
## Interazione con l’ambiente, parte 1: oggetti
All’arrivo in ogni stanza, viene visualizzata una breve descrizione del luogo in cui si trova il
personaggio. Su richiesta verrà visualizzato un elenco di tutto ciò che il personaggio vede e con il
quale può interagire (comprese porte e scale). Per interagire con qualsiasi oggetto, l’utente dovrà
inserire un verbo “comando” (descritti in seguito) seguito da un oggetto.
I comandi utilizzabili per interagire con gli oggetti sono:
Prendere: permette di aggiungere un oggetto all’inventario;
Aprire: permette di sbloccare le porte chiuse a chiave e di aprire il baule e la cassiera; Usare:
interagire con le scale;
Guardare: permette di visualizzare una descrizione del luogo/stanza o di un dipinto;
Leggere: permette di visualizzare l’interno delle pergamene o libri;
Parlare: per interagire con personaggi non giocabili;
Gli oggetti che si possono trovare all’interno di qualsiasi stanza sono:
- Pozione, che ripristina il 50% dei punti vita del personaggio controllato dall’utente.
Numerabile;
- Armatura (elmo, busto, gambali). All’inizio del gioco il personaggio controllato dall’utente
dispone di una armatura in cuoio, ma è possibile acquisire armature migliori trovando un set
completo di bronzo o di ferro e portandolo al fabbro (vedi “Interazione con l’ambiente, parte
3: personaggi-non-giocabili”). I set di armatura completi e riparati dal fabbro non occupano
spazio nell’inventario;
- Spada (bronzo, ferro, platino). La spada non occupa spazio nell’inventario;
- Monete, sparse per la mappa e utili per acquistare oggetti. Numerabile;
- Chiave a E, per aprire una porta chiusa a chiave del primo piano;
- Chiave ornata, per aprire una porta chiusa a chiave del secondo piano;
- Chiave semplice, per aprire una porta chiusa a chiave del terzo piano;
- Pergamene, richiesta da Arthur (vedi “Interazione con l’ambiente, parte 3:
personagginongiocabili”). Numerabile; 
- Vestito, richiesto da Alleria (vedi “Interazione con l’ambiente, parte 3:
personagginongiocabili”);
- Scarpe, richiesto da Alleria (vedi “Interazione con l’ambiente, parte 3:
personagginongiocabili”);
- Torgard, oggetto del tuo desiderio, per il quale ti trovi in questo castello;
- Baule, al cui interno possono essere presenti degli oggetti. Non raccoglibile;
- Cassiera, al cui interno possono essere presenti degli oggetti. Non raccoglibile; -
Dipinti, sparsi per il castello, ne raccontano la storia. Non raccoglibile; - Libri,
sparsi per il castello, ne raccontano la storia. Non raccoglibile.

Gli oggetti presenti all’interno di altri oggetti non saranno annunciati durante l’entrata in una stanza,
bensì saranno annunciati solo quando sarà usato il comando “Aprire” sull’oggetto che li contiene.
Quando ciò avviene, viene visualizzato l’elenco di tutti gli oggetti presenti nella stanza. 
## Interazione con l’ambiente, parte 2: movimento
L’utente si troverà in ogni istante in una stanza, le cui mura sono posizionate perpendicolarmente ai 4
punti cardinali. In ogni stanza è presente almeno una porta; per muoversi in una stanza adiacente
l’utente deve scrivere il nome del punto cardinale dove si trova la porta:
- Nord;
- Sud;
- Ovest;
- Est;
Al termine del movimento, verrà visualizzato il nome della stanza nella quale si è arrivati. Alcune
porte saranno chiuse a chiave; in tal caso l’utente non si muoverà dalla stanza attuale e sarà
avvisato che non è in possesso della chiave per sbloccare la porta selezionata.
Poiché il gioco prende luogo in un castello a 3 piani, occasionalmente, durante la descrizione di ciò
che il personaggio vede, piuttosto che una porta, verrà presentata una scala. Per interagire con le scale
l’utente deve usare il seguente comando:
- Usare scale.
Dopo aver interagito con una scala, verrà visualizzato il nome della stanza in cui ci si è spostati e il
numero del piano in cui si si trova. 

![Mappa livello 1](https://user-images.githubusercontent.com/82885391/142662128-47457a26-7307-4f33-af70-33f2f43154f3.JPG)
![Mappa livello 2](https://user-images.githubusercontent.com/82885391/142662161-082bcf89-af92-407d-a86b-635d56321f56.JPG)
![Mappa livello 3](https://user-images.githubusercontent.com/82885391/142662214-706df1ac-a0ac-4638-a6e5-62588ce406a5.JPG)

## Interazione con l’ambiente, parte 3: personaggi-non-giocabili
In alcune delle stanze sono presenti dei personaggi non controllabili con i quali è possibile interagire
tramite il comando:
Parlare + “occupazione”.
La loro presenza in una stanza sarà annunciata ogni qualvolta ci si muove al suo interno, come per gli
oggetti. I personaggi-non-giocabili sono:
- Fabbro (Ferthdoc), presente al primo piano del castello. Ad interazione compiuta, se il
personaggio controllato dall’utente è in possesso di un set di armatura completo di un livello
maggiore dell’armatura che si sta attualmente indossando, verrà presentata all’utente la
possibilità di pagare 9 monete per far riparare dal fabbro e poter indossare quel set di
armatura. Questa possibilità è proposta all’utente con una domanda sì/no. In caso in cui non
si possegga un set di armatura completo di un livello maggiore dell’armatura che si sta
attualmente indossando, il fabbro avviserà il personaggio controllato dall’utente che non
possiede un set di armatura completo di un livello maggiore dell’armatura che si sta
attualmente indossando.
- Alchimista (Ley’isum), presente al secondo piano del castello. Ad interazione compiuta,
verrà presentata all’utente la possibilità di comprare una pozione al costo di 2 monete. Questa
possibilità è proposta all’utente con una domanda sì/no;
- Dama di corte (Alleria), presente al secondo piano del castello. Ad interazione compiuta,
chiederà al personaggio controllato dall’utente di recuperare il suo vestito e le sue scarpe, 

sparsi per il castello. Dopo aver recuperato i suoi vestiti, ad interazione compiuta, verrà
donato all’utente una serie di potenziamenti che lo aiuteranno nella sua avventura;
- Re (Arthur), presente al terzo piano del castello. Ad interazione compiuta, chiederà al
personaggio controllato dall’utente di recuperare 3 pergamene. Dopo aver recuperato le 3
pergamene, ad interazione compiuta, una sorpresa avrà evento. 

## Interazione con l’ambiente, parte 4: combattimento 
Oltre ai personaggi-non-giocabili, in alcune stanze del castello sono presenti dei personaggi ostili.
Quando il giocatore entra in una stanza con un personaggio ostile al suo interno, viene attivato un
sistema a turni per il combattimento.
Questo sistema prevede l’attacco del nemico ostile, seguito da una iniziativa difensiva da parte del
giocatore, che dopo ave parato o schivato l’attacco del nemico avrà la possibilità di sferrare un
‘attacco offensivo sul nemico o curarsi. Questo ciclo continua finché uno dei due combattenti non
raggiunge 0 punti vita.
All’inizio del gioco il giocatore è in possesso di un’armatura di cuoio che conferisce 16 Hp, con in
ritrovamento delle armature nel gioco ci sarà un incremento di 8 Hp alla volta. Inoltre, nel gioco si
possono ritrovare anche delle pozioni che serviranno per curarsi in combattimento. Durante il gioco
non troveremo solo armature ma anche alcune particolari spade, la prima è la spada di bronzo che
conferisce una Capacità di Danno al giocatore pari a 4, trovando le successive ci sarà un incremento
di 2 CdD al giocatore.
Il personaggio ostile con cui il nostro personaggio controllato dall’utente saranno categorizzati in tre
diversi tipi. I primi sono i mostriciattoli o mostri (Imp, Segugi infernali, Goblin, Corvi Putrefatti). Al
secondo posto troviamo i boss di medio livello (NecomT, Sephiroth, Raphaim, Asmodeo),
sconfiggendoli otterremo oggetti rari che ci aiuteranno nell’esplorazione. Gli ultimi sono i boss di alto
livello (Astaroth, Leviatano, Samael), loro sono i protettori dei livelli successivi. Gli Hp e i CdD sono
organizzati in base ai livelli in cui si trovano.
Durante la fase di combattimento, il set di comandi utilizzabili, è temporaneamente disabilitato,
mentre si possono usare comandi specifici per il combattimento. Questi sono:
- In caso di attacco: attaccare usare pozione
- In caso di difesa:
schivare
parare 

## Inventario 
Quando non in fase di combattimento, l’utente può inserire il comando “Inventario” per sapere il
contenuto del proprio inventario, che sarà visualizzato come un elenco degli oggetti in possesso e del
loro numero (per gli oggetti numerabili). 

## Gestione dei comandi
L’utente può decidere se inserire i comandi interamente in minuscolo, interamente in maiuscolo o con
una qualsiasi capitalizzazione.
Nel caso in cui il comando sia stato inserito incorrettamente, l’utente ne sarà avvisato e nessuna
azione sarà perseguita. 
