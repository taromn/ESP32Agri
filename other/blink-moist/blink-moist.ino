
const int analogPin = 32;
const int drypin = 25;
const int moistpin = 26;

int blinkStat = false;

void setup() {
  pinMode(drypin, OUTPUT);
  pinMode(moistpin, OUTPUT);
  Serial.begin(115200);  // monitor display
}

void toggleLED(int analogValue) {
  if (analogValue > 4000 && blinkStat == false) {
    digitalWrite(drypin, HIGH);
    blinkStat = true;
    digitalWrite(moistpin, LOW);

  } else if (analogValue > 4000 && blinkStat == true) {
    digitalWrite(drypin, LOW);
    blinkStat = false;
    digitalWrite(moistpin, LOW);

  } else {
    digitalWrite(moistpin, HIGH);
    digitalWrite(drypin, LOW);
    
  }
}

void loop() {
  int analogValue = analogRead(analogPin);  // read analogPin
  Serial.println(analogValue);  // show analogValue (0-4095)
  
  toggleLED(analogValue);

  delay(1000);  // delay(ms)
}
