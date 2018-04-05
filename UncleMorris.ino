/*
  Great Uncle Morris' Great Morse Mystery
  Morse code info:https://en.wikipedia.org/wiki/Morse_code#/media/File:International_Morse_Code.svg
*/

char morseCodeKey [36][7]={"01 ","1000 ","1010 ","100 ","0 ","0010 ",
                "110 ","0000 ","00 ","0111 ","101 ","0100 ",
               "11 ","10 ","111 ","0110 ","1101 ","010 ",
               "000 ","1 ","001 ","0001 ","011 ","1001 ",
               "1011 ","1100 ","01111 ","00111 ","00011 ","00001 ",
               "00000 ","10000 ","11000 ","11100 ","11110 ","11111 ",};


int thermo = A0;
int photo = A3;
int thermoTarget = 1234;
int photoTarget = 4321;
char message[] = "abcdefghijklmnopqrstuvwxyz0123456789";// MUST BE lowercase alphanumeric
 //36 alphanumeric numbers, 0 for dot,1 for dash letters then numbers
int ledPin= 13;
int unitTime=1000;//in ms
int bufferTime=50;//in ms
bool found= false;

 

int letterCount= sizeof(message);
int letterIndex=0;

void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  
  
  if(checkSensors()){
  	found=true;
  }
  displayNextLetter();
  

}

bool checkSensors(){
  //boolean zen ;)
	return (analogRead(thermo)==thermo)&&(analogRead(photo)==photoTarget);
}

void displayNextLetter(){
  
  int keyIndex;
  char morseChar = message[letterIndex];
  Serial.print(morseChar);
  if(morseChar==32){
    wordSpace();
  }else if(morseChar<58){
  	keyIndex= morseChar-48+26;
  }else{
    keyIndex= morseChar-97;
  }
  
  for(int i=0;i<5&&morseChar!=32;i++){
    if(morseCodeKey[keyIndex][i]==' '){
      i=5;
    }else if(morseCodeKey[keyIndex][i]=='1'){
      dash();
      interSpace();
    }else{
    	dot();
      	interSpace();
    }
  }
  
  
  letterIndex=(letterIndex+1)%letterCount;
  
  letterSpace();
	
}

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
  Serial.print(3);
  for(int i=0;i<3;i++){
  	digitalWrite(ledPin,HIGH);
  	delay(unitTime-bufferTime);
    digitalWrite(ledPin,LOW);
  	delay(bufferTime);
  }

}

void dot(){
  	Serial.print(1);
	digitalWrite(ledPin,HIGH);
  	delay(unitTime-bufferTime);
  	digitalWrite(ledPin,LOW);
  	delay(bufferTime);
}

