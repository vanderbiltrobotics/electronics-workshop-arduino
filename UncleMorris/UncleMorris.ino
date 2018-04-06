/*
  Great Uncle Morris' Great Morse Mystery
  Morse code info: https://en.wikipedia.org/wiki/Morse_code#/media/File:International_Morse_Code.svg

  this program outputs a certain task on the LED light in morse code,
  it takes in a certain input on the pins,
  and moves onto the next task if the input is satisfied

  International Morse code is composed of five elements:

  short mark, dot or "dit" (▄): "dot duration" is one time unit long
  longer mark, dash or "dah" (▄▄▄): three time units long
  inter-element gap between the dots and dashes within a character: one dot duration or one unit long
  short gap (between letters): three time units long
  medium gap (between words): seven time units long
*/

//36 alphanumeric numbers, 0 for dot, 1 for dash, letters then numbers
char morseCodeKey [36][7] = {"01 ", "1000 ", "1010 ", "100 ", "0 ", "0010 ", // abcdef
                             "110 ", "0000 ", "00 ", "0111 ", "101 ", "0100 ", // ghijkl
                             "11 ", "10 ", "111 ", "0110 ", "1101 ", "010 ", // mnopqr
                             "000 ", "1 ", "001 ", "0001 ", "011 ", "1001 ", // stuvwx
                             "1011 ", "1100 ", // yz
                             "01111 ", "00111 ", "00011 ", "00001 ", "00000 ", // 01234
                             "10000 ", "11000 ", "11100 ", "11110 ", "11111 "
                            };// 56789

int thermo = A0;
int photo = A3;

//  messages MUST BE lowercase alphanumeric, these are the task
char message[6][30] = {"task1 do this", "task2", "task3",
                       "task4", "task5", "you did it"
                      };


int task = 0; //which task are we on

int ledPin = 13;
int unitTime = 1000;  //in ms
int bufferTime = 50;  //in ms
size_t letterCount = sizeof(message[task]); //amount of letters in current message
int letterIndex = 0; // index  of current letter in message

void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  //index for morse code letter in key
  int keyIndex;

  //current character
  char morseChar = message[task][letterIndex];

  Serial.print(morseChar); //print for debugging
  //checks if space of alphabetic
  if (morseChar == ' ') {
    //the space between each word
    //sums to 7 time units when added to the letter space in program
    delayTime(4, LOW);
  } else if (morseChar < '9') {
    keyIndex = morseChar - '0' + 26;//offset for 26 letters first
  } else {
    keyIndex = morseChar - 'a';
  }

  //for every dot/dash, light the led accordingly checking the input each time
  for (int i = 0; i < 5 && morseChar != ' '; ++i) {
    if (morseCodeKey[keyIndex][i] == ' ') {
      i = 5;
    } else if (morseCodeKey[keyIndex][i] == '1') {
      Serial.print("-");

      //makes led dash for 3 time units
      //makes a small flash and checks sensors between each time unit
      delayTime(3, HIGH);

      //the space between each dot/dash in a letter
      //lasts one time unit
      delayTime(1, LOW);

    } else {
      Serial.print(".");
      //makes led dot for 1 time unit, checking sensors in the process
      delayTime(1, HIGH);

      //the space between each dot/dash in a letter
      //lasts one time unit
      delayTime(1, LOW);
    }
  }

  //increment to next letter in message
  letterIndex = (letterIndex + 1) % letterCount;

  //the space between each letter
  //lasts 3 time units
  delayTime(3, LOW);
  Serial.println();
}

void checkSensors() {

  //initialize case variables outside of case
  int avail;
  int thermoTarget;
  int incomingByte;
  int photoTarget;
  int targetRange;

  //Serial.print("task = ");
  //Serial.print(task);

  switch ( task ) {

    case 0:// change this if you need to
      avail = Serial.available();
      //Serial.print("avail = ");
      //Serial.println(avail);
      if (avail > 0) {
        // read the incoming byte:
        incomingByte = Serial.read();

        // say what you got:
        Serial.print("I received: ");
        Serial.println(incomingByte, DEC);
        task++;
      }
      break;


    case 1:
      thermoTarget = 1234;
      targetRange = 5;
      if ((analogRead(thermo) > thermoTarget - targetRange) && (analogRead(thermo) < thermoTarget + targetRange)) {
        task++;
        letterIndex = 0;
        letterCount = sizeof(message[task]);
      }
      break;

    case 2:
      photoTarget = 1234;
      targetRange = 5;
      if ((analogRead(photo) > photoTarget + targetRange) && (analogRead(photo) < photoTarget + targetRange)) {
        task++;
        letterIndex = 0;
        break;
      }
  }
}

void delayTime(size_t times, int logicLevel) {
  for (size_t j = 0; j < times; j++) {
    checkSensors();
    digitalWrite(ledPin, logicLevel);
    delay(unitTime - bufferTime);
    digitalWrite(ledPin, LOW);
    delay(bufferTime);
  }
}





