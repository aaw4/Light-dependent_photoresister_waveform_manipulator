#include <DueTimer.h>
#include <SineWaveDue.h>

int lightCal;
int lightVal;

int buttonState = 0;
int lastButtonState = buttonState;

int state = 0; // 0 = square, 1 = sine, 2 = sawtooth
const int ph1 = A0;
int sensitivity = 100;

int hertz = 400;
double delayTime = 1000000 / (hertz * 2);
int playHertz = hertz;
      
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
  hertz = analogRead(A1);
  delayTime = 1000000 / (hertz * 2);

  // DETERMINE BUTTON PUSH
  if(buttonState != lastButtonState){
    if(buttonState == 1){
      if(state == 2)
        state = 0;
      else
        state++; 
    }
    lastButtonState = buttonState;
    delay(50);
  }
  
  // PLAY SOUNDS
  if(state == 0){
    if(lightVal < lightCal - sensitivity){
      analogWrite(DAC0, 1023);
      delayMicroseconds(delayTime);
      analogWrite(DAC0, 0);
      delayMicroseconds(delayTime);
    }
  }
  else if(state == 1){
    if(lightVal < lightCal - sensitivity){
      sw.playTone(hertz);
      playHertz = hertz;
      
      while(lightVal < lightCal - sensitivity && hertz <= playHertz + 10 && hertz >= playHertz - 10){
        lightVal = analogRead(ph1);
        hertz = analogRead(A1);
      }
      sw.stopTone();
    }
  }
  else if(state == 2){
    Serial.println("Sawtooth");
    while(lightVal < lightCal - sensitivity){
      hertz = analogRead(A1);
      if(hertz == 0) hertz = 1;
      int soundPeak = 1023;
      int delayTime = (1000000 / (hertz))/(soundPeak + 1);
      Serial.println(delayTime);
      
      for(int i = 0; i <= soundPeak; i++){
        analogWrite(DAC0, i);
        delayMicroseconds(delayTime);
      }
      lightVal = analogRead(ph1);
    }
  }
} 


  
