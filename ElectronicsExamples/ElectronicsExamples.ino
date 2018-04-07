
// pin declarations
int photoRead = A0;
int ledPin = 13;
int thermoRead = A1;
int optionPin = 8;

void setup() {
  // put your setup code here, to run once:
  pinMode(photoRead, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(thermoRead, INPUT);
  pinMode(optionPin, INPUT_PULLUP);
  Serial.begin(9600);
}

// value declarations
int photoVal;
int thermoVal;

int calcDelay;

void loop() {
  if (digitalRead(optionPin))
  {
    photoVal = analogRead(photoRead);
    Serial.println(photoVal);
    calcDelay = ((photoVal/10-10)*(photoVal/10-10) - 300) / 20;
    calcDelay = (calcDelay > 5)? calcDelay : 5;
    delay(calcDelay);
    digitalWrite(ledPin, HIGH);
    delay(calcDelay);
    digitalWrite(ledPin, LOW);
  }
  else
  {
    thermoVal = analogRead(thermoRead);
    Serial.println(thermoVal);
    calcDelay = (thermoVal-450)*2;
    calcDelay = (calcDelay > 5)? calcDelay : 5;
    delay(calcDelay);
    digitalWrite(ledPin, HIGH);
    delay(calcDelay);
    digitalWrite(ledPin, LOW);
  }
}
