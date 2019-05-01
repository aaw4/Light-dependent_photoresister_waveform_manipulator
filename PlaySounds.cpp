//PlaySounds.cpp

#include "PlaySounds.h"
#include <DueTimer.h>


void PlaySounds::run(bool* PH, bool* BS, int* KN)
{
    //BS[0] will be the waveform cycle button
    if(BS[0] == HIGH)
      updateWaveform();
      
    //BS[1] will be the sequencer start/stop button, BS[2] will be the sequencer record button
    if(BS[1] == HIGH)
      sequencerStartStop();
    else if(BS[2] == HIGH)
      sequencerRecord();

    //BS[3] will be the secret function, whatever that may be
    if(BS[3] == HIGH)
      secret();

    //play sound for each phr that is activated
    for(int rep = 0; rep< 12; rep++)
    {
      if(PH[rep])
        playSound(rep); // which phr it is; for which note on the scale it is
        
    }
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

void  PlaySounds::playSound(int note)
{
    if(waveform == 's')
      sine();
    else if(waveform == 't')
      sawtooth();
    else
      pulse();
    //if(note == 0)
      //Serial.println("test");
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

void PlaySounds::sequencerStartStop() {}

void PlaySounds::sequencerRecord(){}

void PlaySounds::secret() {}
