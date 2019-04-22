#include <SineWaveDue.h>

int bitrate = 10;
int maxBits = pow(2, bitrate) - 1;

char audioOut = DAC1;

unsigned long runtime = 0;
char photos[] = {A0,A1,A2,A3,A4,A5,A6};
int initalLightVal[7];
double keyHertz[] = {440.0,493.8833,523.2511,587.3295,659.2551,698.4565,783.9909};

void setup() {
  analogReadResolution(bitrate);
  analogWriteResolution(bitrate);
  Serial.begin(9600);
  for(int i = 0; i < 7; i++){
    initalLightVal[i] = analogRead(photos[i]);
  }
}

void loop() {
  for(int i = 0; i < 7; i++){
    if(analogRead(photos[i]) <= initalLightVal[i] - 50){
      int hertz = keyHertz[i];
      int delayTime = 1000000 / hertz;

      analogWrite(audioOut, maxBits);
      delayMicroseconds(delayTime/2);
      analogWrite(audioOut, 0);
      delayMicroseconds(delayTime/2);
    }
  }
}
