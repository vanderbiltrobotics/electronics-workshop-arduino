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

// https://google.github.io/styleguide/cppguide.html

// But thanks anyway for doing this. I love you.
// - Josh

int thermo = A0;
int photo = A3;
int thermoTarget = 1234;
int photoTarget = 4321;
int targetRange = 5;
char message[] = "abcdefghijklmnopqrstuvwxyz0123456789"; // MUST BE lowercase alphanumeric
 //36 alphanumeric numbers, 0 for dot, 1 for dash, letters then numbers
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
  // Set a true result for a range of values instead.
  return (analogRead(thermo) > thermoTarget-targetRange) && (analogRead(photo) > photoTarget-targetRange) &&
  (analogRead(thermo) < thermoTarget+targetRange) && (analogRead(photo) < photoTarget+targetRange);
}

void displayNextLetter() {
  int keyIndex;
  char morseChar = message[letterIndex];
  //Serial.print(morseChar); //print for debugging

  if (morseChar == ' ') {
    wordSpace();
  } else if (morseChar < '9') {
    keyIndex = morseChar - '0' + 26;//offset for 26 letters first
  } else {
    keyIndex = morseChar - 'a';
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
// number of times delayStep() needs to be called for the current state?


/*International Morse code is composed of five elements:

short mark, dot or "dit" (▄): "dot duration" is one time unit long
longer mark, dash or "dah" (▄▄▄): three time units long
inter-element gap between the dots and dashes within a character: one dot duration or one unit long
short gap (between letters): three time units long
medium gap (between words): seven time units long*/


//makes led dot for 1 time unit
void dot() {
  //Serial.print(1); //print for debugging
  digitalWrite(ledPin, HIGH);
  delay(unitTime - bufferTime);
  digitalWrite(ledPin, LOW);
  delay(bufferTime);
}

//makes led dash for 3 time units
//flashes dark for bufferTime ms durring each time unit to indicate seperate time units
void dash(){
  //Serial.print(3); //print for debugging
  for(int i = 0; i < 3; ++i) {
    digitalWrite(ledPin, HIGH);
    delay(unitTime - bufferTime);
    digitalWrite(ledPin, LOW);
    delay(bufferTime);
  }
}

//the space between each dot/dash in a letter
//lasts one time unit
void interSpace(){
  delay(unitTime);
}

//the space between each letter
//lasts 3 time units
void letterSpace(){
  delay(unitTime*3);
}


//the space between each word 
//sums to 7 time units when added to the letter space in program
void wordSpace(){
  delay(unitTime*4);
}






