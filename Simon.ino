#define RED 11
#define GREEN 9
#define BLUE 6
#define YELLOW 3
#define RED_BUTTON 10
#define GREEN_BUTTON 8
#define BLUE_BUTTON 5
#define YELLOW_BUTTON 2
//#define BUZZER 13

const int BRIGHTNESS = 80;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //define LED pin modes
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
  pinMode(BLUE_BUTTON, INPUT_PULLUP);
  pinMode(YELLOW_BUTTON, INPUT_PULLUP);

  //define buzzer pin mode
  //pinMode(BUZZER,OUTPUT);

  //ensure LEDs start off
  digitalWrite(RED, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, LOW);

  //makes random() actually random
  randomSeed(analogRead(0));
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int level;
  const int totalLevel = 3;
  int ledSequence[totalLevel];
  int buttonSequence[totalLevel];
  bool levelComplete = true;
  memset(ledSequence, 0, sizeof(ledSequence));
  memset(buttonSequence, 0, sizeof(buttonSequence));
  while (levelComplete == true) {
    for (int clearSpace = 0; clearSpace <= totalLevel; clearSpace++) {
      ledSequence[clearSpace] = 0;
      buttonSequence[clearSpace] = 0;
    }
    //creates random LED sequence
    for (level = 0; level < totalLevel; level ++) {
      //digitalWrite(RED, HIGH);
      Serial.print(ledSequence[level], "\n");
      ledSequence[level] = random(1,5);
      Serial.print(ledSequence[level], "\n");
      for (int i = 0; i < level; i++) {
          Serial.print(ledSequence[level], "\n");
          switch (ledSequence[i]) {
            case 1:
              analogWrite(RED, BRIGHTNESS);
              delay(1000);
              digitalWrite(RED, LOW);
              delay(500);
              Serial.print(ledSequence[i], "\n");
              break;
            case 2:
              analogWrite(GREEN, BRIGHTNESS);
              delay(1000);
              digitalWrite(GREEN, LOW);
              delay(500);
              Serial.print(ledSequence[i], "\n");
              break;
            case 3:
              analogWrite(BLUE, BRIGHTNESS);
              delay(1000);
              digitalWrite(BLUE, LOW);
              delay(500);
              Serial.print(ledSequence[i], "\n");
              break;
            case 4:
              analogWrite(YELLOW, BRIGHTNESS);
              delay(1000);
              digitalWrite(YELLOW, LOW);
              delay(500);
              Serial.print(ledSequence[i], "\n");
              break;
            default:
              Serial.print("This ain't working\n");
          }
      }
      //detects user inputted sequence
      for (int k = 0; k < level; k++) {
        delay(1000);
        if (digitalRead(RED_BUTTON) == LOW) {
          digitalWrite(RED, HIGH);
          delay(500);
          digitalWrite(RED, LOW);
          buttonSequence[k] = 1;
          }
        else if (digitalRead(GREEN_BUTTON) == LOW) {
          digitalWrite(GREEN, HIGH);
          delay(500);
          digitalWrite(GREEN, LOW);
          buttonSequence[k] = 2;
          }
        else if (digitalRead(BLUE_BUTTON) == LOW) {
          digitalWrite(BLUE, HIGH);
          delay(500);
          digitalWrite(BLUE, LOW);
          buttonSequence[k] = 3;
          }
        else if (digitalRead(YELLOW_BUTTON) == LOW) {
          digitalWrite(YELLOW, HIGH);
          delay(500);
          digitalWrite(YELLOW, LOW);
          buttonSequence[k] = 4;
          }
      }
      delay(1500);

      //checks if any part of the user sequence is wrong
      for (int j = 0; j < level; j++) {
        if (ledSequence[j] != buttonSequence[j]) {
          levelComplete = false;
          Serial.print("level fail\n");
          while(true) {
            for (int clearSpace = 0; clearSpace <= totalLevel; clearSpace++) {
              ledSequence[clearSpace] = 0;
              //Serial.print(ledSequence[clearSpace], "\n");
              buttonSequence[clearSpace] = 0;
              //Serial.print(buttonSequence[clearSpace], "\n");
            }
            analogWrite(RED, BRIGHTNESS);
            analogWrite(GREEN, BRIGHTNESS);
            analogWrite(BLUE, BRIGHTNESS);
            analogWrite(YELLOW, BRIGHTNESS);
          }
        }
        else {
          Serial.print("correct\n");
        }
      }
      delay(3000);
      //delay(100);
      //digitalWrite(RED, LOW);
      //delay(100);
      //Serial.print(level, DEC);
    }

    //checks if the total level has been reached
    if (level == totalLevel) {
      while(true) {
        for (int clearSpace = 0; clearSpace <= totalLevel; clearSpace++) {
          ledSequence[clearSpace] = 0;
          //Serial.print(ledSequence[clearSpace], "\n");
          buttonSequence[clearSpace] = 0;
          //Serial.print(buttonSequence[clearSpace], "\n");
        }
        analogWrite(YELLOW, BRIGHTNESS);
        delay(500);
        digitalWrite(YELLOW, LOW);
        analogWrite(BLUE, BRIGHTNESS);
        delay(500);
        digitalWrite(BLUE, LOW);
        analogWrite(GREEN, BRIGHTNESS);
        delay(500);
        digitalWrite(GREEN, LOW);
        analogWrite(RED, BRIGHTNESS);
        delay(500);
        digitalWrite(RED, LOW);
      }
    }
  }
  digitalWrite(RED, LOW);
  while (true) {
  }
}
