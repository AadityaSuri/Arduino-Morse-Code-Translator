#include<ctype.h>

const int pinNum = 10;
const int dotTime = 150;
const int dashTime = 3*dotTime;
const int spaceTime = 7*dotTime;

//1 denotes dot, 0 denotes dash
int morseAlphaKey[26][5] = {
  {1,0,0,0,0}, //a
  {0,1,1,1,0}, //b
  {0,1,0,1,0}, //c
  {0,1,1,0,0}, //d
  {1,0,0,0,0}, //e
  {1,1,0,1,0}, //f
  {0,0,1,0,0}, //g
  {1,1,1,1,0}, //h
  {1,1,0,0,0}, //i
  {1,0,0,0,0}, //j
  {0,1,0,0,0}, //k
  {1,0,1,1,0}, //l
  {0,0,0,0,0}, //m
  {0,1,0,0,0}, //n
  {0,0,0,0,0}, //o
  {1,0,0,1,0}, //p
  {0,0,1,0,0}, //q
  {1,0,1,0,0}, //r
  {1,1,1,0,0}, //s
  {0,0,0,0,0}, //t
  {1,1,0,0,0}, //u
  {1,1,1,0,0}, //v
  {1,0,0,0,0}, //w
  {0,1,1,0,0}, //x
  {0,1,0,0,0}, //y
  {0,0,1,1,0}  //z
};

int morseNumKey[10][5] = {
  {0,0,0,0,0}, //0
  {1,0,0,0,0}, //1
  {1,1,0,0,0}, //2
  {1,1,1,0,0}, //3
  {1,1,1,1,0}, //4
  {1,1,1,1,1}, //5
  {0,1,1,1,1}, //6
  {0,0,1,1,1}, //7
  {0,0,0,1,1}, //8
  {0,0,0,0,1}  //9
};

int morseAlphaLength[26] = {2,4,4,3,1,4,3,4,2,4,3,4,2,2,3,4,4,3,3,1,3,4,3,4,4,4};  //length of morse code sequences of the ith alphabet 


void morseWrite(int morseKeyArray[][5], int traversalLength, int rowIndex){
  for(int i = 0; i < traversalLength; i++){
    int dotOrDash = morseKeyArray[rowIndex][i];
    if(dotOrDash){    //if dot is to be produced on LED
      digitalWrite(pinNum, HIGH);
      delay(dotTime);
      digitalWrite(pinNum, LOW);
      delay(dotTime);
    }

    if(!dotOrDash){   //if dash is to be produced on LED
      digitalWrite(pinNum, HIGH);
      delay(dashTime);
      digitalWrite(pinNum, LOW);
      delay(dashTime);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinNum, OUTPUT);
  Serial.println("enter text to be converted to morse code above (do not use punctuations or any special characters)");
}

void loop() {
  // put your main code here, to run repeatedly:
  char userInput = 0;
  if(Serial.available() > 0){
    userInput = Serial.read();
  }

  if(userInput == ' '){  //in case of a space
    digitalWrite(pinNum, LOW);
    delay(7*spaceTime);
  }else{
    int rowIndex, traversalLength;
    if(isalpha(userInput)){  //if userInput is an alphabet
      rowIndex = tolower(userInput) - 97;
      traversalLength = morseAlphaLength[rowIndex];
      morseWrite(morseAlphaKey, traversalLength, rowIndex);
    }
    if(isdigit(userInput)){  //if userInput is an digit
      rowIndex = userInput - 48;
      traversalLength = 5;
      morseWrite(morseNumKey, traversalLength, rowIndex);
    }
  }
}
