#include <DueTimer.h>
#include <SineWaveDue.h>

int lightCal;
int lightVal;

int buttonState = 0;
int lastButtonState = buttonState;

int state = 0; // 0 = square, 1 = sine, 2 = sawtooth
const int ph1 = A0;
int sensitivity = 100;

void setup()  { 
  analogReadResolution(10);
  analogWriteResolution(10);
  Serial.begin(9600);
  lightCal = analogRead(ph1);
  pinMode(7, INPUT);
}

void loop()  {
  lightVal = analogRead(ph1);
  buttonState = digitalRead(7);
  Serial.println(digitalRead(7));
  
  // DETERMINE BUTTON PUSH
  if(buttonState != lastButtonState){
    if(buttonState == HIGH){
      if(state = 3)
        state = 0;
      else
        state++; 
    }
    delay(50);
  }
  
  // PLAY SOUNDS
  if(state == 0){
    if(lightVal < lightCal - sensitivity){
      analogWrite(A1, 512);
      delay(10);
      analogWrite(A1, 0);
      delay(10);
    }
  }
  else if(state == 1){
    if(lightVal < lightCal - sensitivity){
      sw.playTone(400);
      while(lightVal < lightCal - sensitivity){
        delay(10);
        lightVal = analogRead(ph1);
      }
      sw.stopTone();
    }
  }
  else if(state == 2){
    
  }
} 


  
