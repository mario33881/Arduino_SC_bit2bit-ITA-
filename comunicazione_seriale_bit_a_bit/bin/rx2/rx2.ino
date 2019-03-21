byte Byterx; // conterra' il byte ricevuto dalla seriale
int n;       // numero utilizzato per i cicli for

void setup() {
  Serial.begin(9600);   // inizia la comunicazione seriale
  
  for(int n=2;n<6;n++){ 
    // loop che viene ripetuto per 4 volte
    
    pinMode(n, OUTPUT); // imposta il pin "n" (dal 2 al 5) come output
  }
}

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
