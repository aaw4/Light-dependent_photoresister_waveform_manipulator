//PlaySounds.cpp

#include "PlaySounds.h"
#include <DueTimer.h>

PlaySounds::PlaySounds()
{
    digitalWrite(26, HIGH);
    digitalWrite(28, LOW);
    digitalWrite(30, LOW);
}

void PlaySounds::run(bool* PH, bool* BS, int* KN)
{

  if(initial == false)
  {
   
    digitalWrite(26, HIGH);
    digitalWrite(28, LOW);
    digitalWrite(30, LOW);
    waveform = 'q';
    
    initial = true;
  }
  
  if(BS[3])
  {
    BS[3] = 0;
    if(once)
    {
      once = false;
      updateWaveform();
      
    }
  }

  for(int rep = 0; rep<12; rep++)
  {
    
    if(PH[rep])
    {
      playSound(rep);
    }
  }
  
    
}

void PlaySounds::stop()
{
    hertz = 0;
    digitalWrite(26, LOW);
    digitalWrite(28, LOW);
    digitalWrite(30, LOW);
    initial = false;
    
}

void  PlaySounds::updateWaveform()
{

  //done
  Serial.println(waveform);
  if(waveform == 't')
  {
    waveform = 'q';
    digitalWrite(26, HIGH);
    digitalWrite(28, LOW);
    digitalWrite(30, LOW);
    
  }
  else if(waveform == 'q')
  {
    waveform = 's';
    digitalWrite(26, LOW);
    digitalWrite(28, HIGH);
    digitalWrite(30, LOW);
  }
  else if(waveform == 's')
  {
    waveform = 't';
    digitalWrite(26, LOW);
    digitalWrite(28, LOW);
    digitalWrite(30, HIGH);
  }
  once =true;
}

void  PlaySounds::playSound(int rep)
{

  hertz = 440 * pow(1.059463094359, rep - 9);
  delayTime = 1000000 / (hertz * 2);
  
  if(waveform == 'q')
  {
    pulse();
    
  }

  else if(waveform == 's')
  {
    sine(rep);
  }

  else if(waveform == 't')
  {
    sawtooth();
    
  }
  
    
}
                 
void  PlaySounds::sine(int rep)
{ 
  sw.playTone(hertz);
  while(analogRead(rep + A0) < 100){
    
  }
  sw.stopTone();
}

void  PlaySounds::pulse()
{

  //done
  analogWrite(DAC1, volume);
  delayMicroseconds(delayTime);
  analogWrite(DAC1, 0);
  delayMicroseconds(delayTime);
    
}

void  PlaySounds::sawtooth()
{
  /**
   * 
   * LOL FIX THIS SHIT
   *
  if(hertz == 0) hertz = 1;
  
  delayTimeSawtooth = (1000000 / (hertz))/((volume/10) + 1);

  Serial.println(delayTimeSawtooth);
  
  for(int i = 0; i <= (volume/10); i+=10)
  {
    analogWrite(DAC1, i);
    delayMicroseconds(delayTimeSawtooth);
  }
   **/ 
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
