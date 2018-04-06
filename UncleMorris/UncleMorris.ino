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

//int thermo = A0;
//int photo = A3;

//  messages MUST BE lowercase alphanumeric, these are the task
char message[6][30] = {"255", "31", "250",
                       "32 and 8", "300 and 100", "you did it"
                      };


int task = 0; //which task are we on

int ledPin = 13;
int unitTime = 333;  //in ms
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
  //int avail;
  //int thermoTarget;
  //int incomingByte;
  //int photoTarget;
  //int targetRange;
  int readOutput1; // Output of circuit designed by student, read on pin A5
  int readOutput2; // Output of circuit designed by student, read on pin A4
  int answer1; // Value between 0 and 1024. Task is passed if readOutput1 == answer1
  int answer2; // Value between 0 and 1024. Task is passed if readOutput1 == answer1 && readOutput2 == answer2
  int outPin1 = A5;
  int outPin2 = A4;
  bool printOutput = false; //If = TRUE, print values of readOutput1 and readOutput2
  //Serial.print("task = ");
  //Serial.print(task);

  //Students try to get readOutput = answer. Output1 read on A5, Output2 read on A4
  switch ( task ) {

    //task+=4;
    case 0: //BASIC VOLTAGE DIVISION
      answer1 = 255; // Vmax/4. Only worked when answer1 = 162 for some reason.
      readOutput1 = analogRead(outPin1);
      if (printOutput)
        Serial.println(readOutput1);
      if ((readOutput1 > answer1 - 2) && (readOutput1 < answer1 + 2)) {
        Serial.print("Task 1 passed! :D");
        task++;
        letterIndex = 0;
        letterCount = sizeof(message[task]);
      }
      break;


    case 1: //THERMISTOR TASK
      answer1 = 31;
      readOutput1 = analogRead(outPin1);
      if (printOutput)
        Serial.println(readOutput1);
      if (readOutput1 == answer1) {
        Serial.print("Task 2 passed! XD");
        task++;
        letterIndex = 0;
        letterCount = sizeof(message[task]);
      }
      break;

    case 2: //PHOTORESISTOR TASK - Use green light of arduino or make LED circuit
      answer1 = 250;
      readOutput1 = analogRead(outPin1);
      if (printOutput)
        Serial.println(readOutput1);
      if ((readOutput1 > answer1 - 5) && (readOutput1 < answer1 +5)) {
        Serial.print("Task 3 passed! Nice!!");
        task++;
        letterIndex = 0;
      }
      break;

    case 3: //VOLTAGE DIVISION + THERMISTOR
      answer1 = 32; //Obtain this voltage with thermistor probably
      answer2 = 8;
      readOutput1 = analogRead(outPin1);
      readOutput2 - analogRead(outPin2);
      if (printOutput){
      Serial.print("A5 = ");
      Serial.print(readOutput1);
      Serial.print(", A4 = ");
      Serial.println(readOutput2);
      }
      if (readOutput1 == answer1 && readOutput2 == answer2) {
        Serial.print("Task 4 passed! YOU'RE AWESOME!!!");
        task++;
        letterIndex = 0;
        letterCount = sizeof(message[task]);
      }
      break;

    case 4: //VOLTAGE DIVISION + PHOTORESISTOR
      answer1 = 300;
      answer2 = 100;
      readOutput1 = analogRead(outPin1);
      readOutput2 = analogRead(outPin2);
      if (printOutput){
      Serial.print("A5 = ");
      Serial.print(readOutput1);
      Serial.print(", A4 = ");
      Serial.println(readOutput2);
      }
      if ((readOutput1 > answer1 - 5) && (readOutput1 < answer1 + 5) &&
          (readOutput2 > answer2 - 5) && (readOutput2 > answer2 + 5) ) {
        Serial.print("Task 5 passed! YOU'RE THE GREATEST!!!!");
        task++;
        letterIndex = 0;
      }
      break;
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





