//PlaySounds.cpp

#include "PlaySounds.h"
#include <DueTimer.h>


void PlaySounds::run(bool* PH, bool* BS, int* KN)
{
    
}

void PlaySounds::stop()
{
    hertz = 0;
}

void  PlaySounds::updateWaveform()
{

  //done

  if(waveform == 't')
  {
    waveform = 'q';
  }
  else if(waveform == 's')
  {
    waveform = 't';
  }
  else
    waveform = 's';
}

void  PlaySounds::playSound()
{
    
}
                 
void  PlaySounds::sine()
{
  //could be better
  sw.playTone(hertz);
    
}

void  PlaySounds::pulse()
{

  //done
  analogWrite(DAC0, 1023);
  delayMicroseconds(delayTime);
  analogWrite(DAC0, 0);
  delayMicroseconds(delayTime);
    
}

void  PlaySounds::sawtooth()
{
  //maybe done

  hertz = analogRead(A1);
  
  if(hertz == 0) hertz = 1;
  int soundPeak = 1023;
  int delayTime = (1000000 / (hertz))/(soundPeak + 1);
  Serial.println(delayTime);
  
  for(int i = 0; i <= soundPeak; i++)
  {
    analogWrite(DAC0, i);
    delayMicroseconds(delayTime);
  }
    
}

void  PlaySounds::lpf()
{
    
}

void  PlaySounds::outputWave()
{
    
}

void  PlaySounds::adder()
{
    
}

void  PlaySounds::mult()
{
    
}

void  PlaySounds::ADSR()
{
    
}
