#include "QUARZO_.h"

void TEST_quarzo() {
  long startTime = millis();  // Tempo di inizio
  long counter = 0;           // Contatore per il numero di loop
  long runTime;               // Durata dell'esecuzione

  // Eseguire il loop finché runTime non raggiunge 1000 ms
  do {
    counter++;                       // Incrementa il contatore per ogni ciclo
    runTime = millis() - startTime;  // Calcola il tempo trascorso
  } while (runTime < 1000);

  // Restituisce il numero di loop eseguiti in 1000 ms
  long loopCount = counter;  // Chiama la funzione quarzo() e ottiene il risultato
  Serial.print("Looped ");
  Serial.print(loopCount);
  Serial.print(" times in 1000 ms");
}
