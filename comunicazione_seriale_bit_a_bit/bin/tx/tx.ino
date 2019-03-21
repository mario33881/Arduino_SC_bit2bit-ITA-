byte Byte; // byte da inviare
int n;     // variabile da incrementare nei for

void setup() {
  Serial.begin(9600);          // inizia la comunicazione seriale
  for (int n = 2; n < 10;n++){
    // ripete il ciclo per 8 volte
    pinMode(n, INPUT); // imposta i pin dal 2 al 9 come INPUT
  }
}

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
  
