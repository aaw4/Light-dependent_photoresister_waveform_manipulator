#include <DueTimer.h>
#include <SineWaveDue.h>

void setup()  { 
  analogReadResolution(10);
  analogWriteResolution(10);
  pinMode(A0, OUTPUT);
  sw.playTone(100);

} 
int x =0;

void loop()  {
  analogWrite(A0, 512);
  delay(10);
  analogWrite(A0,0);
  delay(10);
    
} 


  
