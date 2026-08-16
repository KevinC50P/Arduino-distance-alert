/*
 * HC-SR04 Distance Warner
 * ------------------------
 * Misst die Entfernung mit einem Ultraschallsensor (HC-SR04)
 * und steuert je nach Nähe 3 LEDs sowie einen aktiven Buzzer an.
 *
 * LED1 -> weit weg
 * LED2 -> mittlere Entfernung
 * LED3 -> nah (+ Buzzer piept)
 */

const int trigPin = 11;
const int echoPin = 12;
const int buzzerPin = 9;

const int led1 = 2;   // weit weg
const int led2 = 3;   // mittel
const int led3 = 4;   // nah

// Schwellenwerte in cm - bei Bedarf anpassen
const int schwelleWeit = 50;
const int schwelleMittel = 25;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW); // wichtig: sofort auf LOW setzen, sonst Dauerton

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  // Signal-Impuls senden
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Echo-Zeit messen (Timeout 30ms, verhindert Hängenbleiben)
  long dauer = pulseIn(echoPin, HIGH, 30000);

  // In Zentimeter umrechnen (Schallgeschwindigkeit / 2)
  int entfernung = dauer * 0.034 / 2;

  // Im seriellen Monitor ausgeben
  Serial.print("Entfernung: ");
  Serial.print(entfernung);
  Serial.println(" cm");

  // Alle LEDs & Buzzer erstmal aus
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(buzzerPin, LOW);

  // Je nach Entfernung LEDs ansteuern
  if (entfernung > schwelleWeit) {
    digitalWrite(led1, HIGH);
  } else if (entfernung > schwelleMittel) {
    digitalWrite(led2, HIGH);
  } else if (entfernung > 0) {
    // sehr nah -> LED3 + Buzzer
    digitalWrite(led3, HIGH);
    digitalWrite(buzzerPin, HIGH);
  }

  delay(500);
}
