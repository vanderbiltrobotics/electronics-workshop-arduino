/*
  Great Uncle Morris' Great Morse Mystery
  Morse code info: https://en.wikipedia.org/wiki/Morse_code#/media/File:International_Morse_Code.svg
*/

char morseCodeKey [36][7] = {"01 ","1000 ","1010 ","100 ","0 ","0010 ", // abcdef
                           "110 ","0000 ","00 ","0111 ","101 ","0100 ", // ghijkl
                             "11 ","10 ","111 ","0110 ","1101 ","010 ", // mnopqr
                             "000 ","1 ","001 ","0001 ","011 ","1001 ", // stuvwx
                                                       "1011 ","1100 ", // yz
                          "01111 ","00111 ","00011 ","00001 ","00000 ", // 01234
                          "10000 ","11000 ","11100 ","11110 ","11111 "};// 56789

// Danny,
// Do NOT indent with tabs. Ever. If you do it again, I will do something mean to you in return.
// Also, make sure your code is readable. If it looks semantically different than what I have written 
//  below, it is probably difficult to understand to most people. Please read Google's Style Guides
//  for C++; your previous code made some pretty bad sins.
// https://google.github.io/styleguide/cppguide.html

// But thanks anyway for doing this. 
// - Josh

int thermo = A0;
int photo = A3;
int thermoTarget = 1234;
int photoTarget = 4321;
char message[] = "abcdefghijklmnopqrstuvwxyz0123456789"; // MUST BE lowercase alphanumeric
 //36 alphanumeric numbers, 0 for dot, 1 for dash letters then numbers
int ledPin = 13;
int unitTime = 1000;  //in ms
int bufferTime = 50;  //in ms
bool found = false;

 

size_t letterCount = sizeof(message);
int letterIndex = 0;

void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if(checkSensors()) {
    found = true;
  }
  displayNextLetter();
}

bool checkSensors() {
  // NO. DO NOT DO THIS. Will only read true if the analog read is EXACTLY the designated target value.
  // Set a true result for a range of values instead.
  return (analogRead(thermo) == thermoTarget) && (analogRead(photo) == photoTarget);
}

void displayNextLetter() {
  int keyIndex;
  char morseChar = message[letterIndex];
  Serial.print(morseChar);

  // WTF are these values???? Are they ASCII? I can't tell; you didn't even comment your code
  // Compare your chars to other chars; e.g. morseChar == ' '; or morseChar < 'a';.
  if (morseChar == 32) {
    wordSpace();
  } else if (morseChar < 58) {
    keyIndex = morseChar - 48 + 26;
  } else {
    keyIndex = morseChar - 97;
  }
  
  for (int i = 0; i < 5 && morseChar != 32; ++i) {
    if (morseCodeKey[keyIndex][i] == ' ') {
      i = 5;
    } else if (morseCodeKey[keyIndex][i] == '1') {
      dash();
      interSpace();
    } else {
      dot();
      interSpace();
    }
  }
  letterIndex = (letterIndex + 1) % letterCount;
  letterSpace();
}


// I get the feeling there is a cleaner way to code these functions...
// Maybe have a delayStep() function and then have a counter for the 
//  number of times delayStep() needs to be called for the current state?
// int delayCount;
// dot  -> delayCount = 1;
// dash -> delayCount = 3;
// charSpace -> delaycount = 1;
// wordSpace -> delayCount = 3;
// etc.
// btw, there are standards for how long these delays are supposed to be. 
void interSpace(){
  delay(unitTime);
}

void letterSpace(){
  delay(unitTime*3);
}

void wordSpace(){
  delay(unitTime*4);
}

void dash(){
  // What is this print() supposed to do
  Serial.print(3);
  for(int i = 0; i < 3; ++i) {
    digitalWrite(ledPin, HIGH);
    delay(unitTime - bufferTime);
    digitalWrite(ledPin, LOW);
    delay(bufferTime);
  }
}

void dot() {
  Serial.print(1);
  digitalWrite(ledPin, HIGH);
  delay(unitTime - bufferTime);
  digitalWrite(ledPin, LOW);
  delay(bufferTime);
}

