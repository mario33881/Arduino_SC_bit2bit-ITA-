# COMUNICAZIONE SERIALE BIT A BIT
---
![](https://i.imgur.com/ub6O7TP.jpg)
#### Autori
* Fraccari Luca ( [Github](https://github.com/Luca5912) )
* Lain Lorenzo
* Morini Martino
* Rossini Andrea
* Vecchiato Alessandro
* Zenaro Stefano ( [Github](https://github.com/mario33881) )
#### Github ![](https://i.imgur.com/ej4EVF6.png)
[Visualizza questo file su github](https://gist.github.com/mario33881/)
#### Video ![](https://i.imgur.com/WCi43wB.png)
---
## Descrizione ![](https://i.imgur.com/wMdaLI0.png)
---
Per questo progetto abbiamo utilizzato **tre arduini**, uno come **trasmettitore** e gli altri **due** come **ricevitori**. 
Grazie a degli **DIP switch** viene creato un **byte** che viene **trasmesso attraverso la comunicazione seriale** agli altri due arduini.

Del byte vengono considerati solo i primi **4 bit** dal **primo ricevitore**, mentre gli ultimi bit dal secondo ricevitore.

Ogni singolo bit viene visualizzato tramite un LED.
> Ogni LED e' in serie ad una resistenza di 330 Ohm
### Hardware
#### Trasmettitore:
Utilizza i pin digitali dal 2 al 9 come INPUT variabili
attraverso uno DIP switch a 8 vie, che puo' portarli a massa o a Vcc.
Il pin 1 / TX viene usato per inviare il byte creato.
#### Ricevitore (1 e 2)
I pin dal 2 al 5 vengono utilizzati come OUTPUT per 
commandare i LED.
Il pin 0 / RX viene usato per ricevere il byte inviato 
dal trasmettitore
#### materiale utilizzato:
* 3 Arduini (Sparkfun)
* 3 Breadboard mini
* 1 DIP switch a 8 vie
* Array di resistenze da 10 K Ohm
* 8 LED (4 per ogni ricevitore)
* 8 resistori 330 Ohm
* Jumper colorati
* 3 cavi USB - micro USB
### Software
La **comunicazione seriale bit a bit** e' svolta attraverso **tre sketch**

#### Trasmettitore
Riceve 8 segnali variabili da 8 dip switch, modifica per ogni
segnale il suo bit corrispondente del byte "Byte" e poi lo invia attraverso la comunicazione seriale

	tx.ino

Lo sketch e' diviso in tre parti principali:
1. INIZIALIZZAZIONE
    ```
    byte Byte; // byte da inviare
    int n;     // variabile da incrementare nei for
    ```
    Inizializza le variabili

2. SETUP
    ```
    void setup() {
      Serial.begin(9600); // inizia la comunicazione seriale
      for (int n = 2; n < 10;n++){
        // ripete il ciclo per 8 volte
        pinMode(n, INPUT); //imposta i pin dal 2 al 9 come INPUT
      }
    }
    ```
    Dopo aver iniziato la comunicazione seriale,
    utilizziamo un ciclo for per impostare i pin
    (collegati allo switch) come input.
3. LOOP
    ```
    void loop() {
      for (int n = 0; n <8;n++){
        // ripeti il ciclo per 8 volte (numero di bit in un byte)
        
        if (digitalRead(n + 2) == HIGH){
          // se sul pin "n + 2" e' presente un segnale alto...
          
          bitWrite(Byte, n, 0); // imposta il bit in posizione "n" come 0
          }
        else{
          // altrimenti, se e' presente un segnale basso...
          
          bitWrite(Byte, n, 1); // imposta il bit in posizione "n" come 1
          }  
      }
    
      Serial.write(Byte); // invia su seriale il byte "Byte"
      delay(50);          // attende 50 ms
    }
    ```
    Un ciclo for si occupa di verificare il livello logico dei pin in input, impostando un bit del byte "Byte" a 0 se il livello logico e' alto, altrimenti lo imposta a 1
    > Se il bit da modificare e' "n", il pin da verificare corrisponde a "n+2", in base a questa tabella:
    
    | BIT da modificare          | PIN da controllare|
    | ------------- |:-------------:| 
    | 0             | 2             | 
    | 1             | 3             | 
    | 2             | 4             | 
    | 3             | 5             | 
    | 4             | 6             | 
    | 5             | 7             | 
    | 6             | 8             | 
    | 7             | 9             | 

#### Ricevitore 1
Il primo ricevitore ottiene il byte "Byterx" dal trasmettitore e
dei suoi bit ne analizza i primi 4, controllando i suoi 4 LED
sui pin digitali dal 2 al 5

    rx1.ino

1. INIZIALIZZIONE
    ```
    byte Byterx; // conterra' il byte ricevuto dalla seriale
    int n;       // numero utilizzato per i cicli for
    ```
    Inizializza le variabili
2. SETUP
    ```
    void setup() {
      Serial.begin(9600);   // inizia la comunicazione seriale
      
      for(int n = 2; n < 6; n++){ 
        // loop che viene ripetuto per 4 volte
        
        pinMode(n, OUTPUT); // imposta il pin "n" (dal 2 al 5) come output
      }
    }
    ```
    Dopo aver iniziato la comunicazione seriale,
    imposta i pin dal 2 al 5 come output (per controllare i LED)
    attraverso un ciclo for.
3. LOOP
    ```
    void loop() {
      if (Serial.available() > 0){ 
        // se c'e' almeno un byte nel buffer
        
        Byterx = Serial.read(); // legge sul seriale il byte e lo mette in Byterx
    
        for(int n = 0; n < 4; n++){
          // loop ripetuto per 4 volte
          
          if(bitRead(Byterx, n) == 0){ 
            // se il bit in posizione "n" (dal 0 al 3) e' uguale a 0
            
            digitalWrite(n + 2, LOW); // imposta sul pin "n+2" il livello logico basso
          }
          else{  
            // altrimenti, se il bit e' uguale a 1
            
            digitalWrite(n + 2, HIGH); // imposta sul pin "n + 2" il livello logico alto
          }
        }
      }
      delay(10); // attendi per 10 ms
    }
    ```
    Dopo essersi assicurato che ci sia almeno un byte nel buffer,
    legge il byte ricevuto e lo mette nella variabile Byterx.
    Poi con un ciclo for legge i primi 4 bit (dal least significant bit)
    e in base ai loro valori vengono accesi o spenti i
    rispettivi LED.
    > Se il bit e' 0, il LED e' spento, altrimenti e' acceso
    >
    > I bit ("n") corrispondono I pin dei LED ("n+2") secondo la seguente tabella: 
    
    | BIT letto     | PIN da controllare|
    | ------------- |:-------------:| 
    | 0             | 2             | 
    | 1             | 3             | 
    | 2             | 4             | 
    | 3             | 5             | 

#### Ricevitore 2
Il secondo ricevitore ottiene il byte "Byterx" dal trasmettitore e
dei suoi bit ne analizza gli ultimi 4, controllando i suoi 4 LED
sui pin digitali dal 2 al 5

    rx2.ino

1. INIZIALIZZIONE
    ```
	byte Byterx; // conterra' il byte ricevuto dalla seriale
	int n;       // numero utilizzato per i cicli for
    ```
    Inizializza le variabili
2. SETUP
    ```
    void setup() {
	  Serial.begin(9600);   // inizia la comunicazione seriale
	  
	  for(int n=2;n<6;n++){ 
		// loop che viene ripetuto per 4 volte
		
		pinMode(n, OUTPUT); // imposta il pin "n" (dal 2 al 6) come output
	  }
	}
    ```
    Dopo aver iniziato la comunicazione seriale,
    imposta i pin dal 2 al 5 come output (per controllare i LED)
    attraverso un ciclo for.
3. LOOP
    ```
	void loop() {
	  if (Serial.available() > 0){ 
		// se c'e' almeno un byte nel buffer
		
		Byterx = Serial.read(); // legge sul seriale il byte e lo mette in Byterx

		for(int n = 4; n < 8; n++){
		  // loop ripetuto per 4 volte
		  
		  if(bitRead(Byterx, n) == 0){ 
			// se il bit in posizione "n" (dal 4 al 7) e' uguale a 0
			
			digitalWrite(n-2,LOW); // imposta sul pin "n-2" il livello logico basso
		  }
		  else{
			// altrimenti, se il bit e' uguale a 1
			
			digitalWrite(n-2,HIGH); // imposta sul pin "n-2" il livello logico alto
		  }
		}
	  }
	  delay(10); // attendi per 10 ms
	}
    ```
    Dopo essersi assicurato che ci sia almeno un byte nel buffer,
    legge il byte ricevuto e lo mette nella variabile Byterx.
    Poi con un ciclo for legge i primi 4 bit (dal least significant bit)
    e in base ai loro valori vengono accesi o spenti i
    rispettivi LED.
    > Se il bit e' 0, il LED e' spento, altrimenti e' acceso
    >
    > I bit ("n") corrispondono ai pin dei LED ("n-2") secondo la seguente tabella: 

    | BIT letto     | PIN da controllare|
    | ------------- |:-------------:| 
    | 4             | 2             | 
    | 5             | 3             | 
    | 6             | 4             | 
    | 7             | 5             | 
    
## Contenuto archivio ![](https://i.imgur.com/FWdiWIM.png)
---
	comunicazione_seriale_bit_a_bit/
		├── bin/
		│   ├── rx1/
		│   │   └─ rx1.ino
		│   ├── rx2/
		│   │    └─ rx2.ino
		│   └── tx/
		│       └─ tx.ino
		└── doc/
			└── README.md