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
    for(int rep = 0; rep< 1; rep++)
    {
      if(PH[rep])
        playSound(rep); // which phr it is; for which note on the scale it is
      
        
    }
}

void PlaySounds::stop()
{
    hertz = 0;
    volume = 0;
    clearPHR();
    clearBS();
    clearKN();
}

void PlaySounds::clearPHR()
{
  for(int rep = 0; rep<12; rep++)
  {
    PHR[rep] = false;
  }
}

void PlaySounds::clearBS()
{
  for(int rep = 0; rep<4; rep++)
  {
    BS[rep] = false;
  }
}

void PlaySounds::clearKN()
{
  for(int rep = 0; rep<4; rep++)
  {
    KN[rep] = 0;
  }
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
    else if (waveform == 'q')
      pulse();
}
                 
void  PlaySounds::sine()
{
  //kind of working
  sw.playTone(800);
  
  
    
}

void  PlaySounds::pulse()
{
  //done
  for(int rep = 0; rep< sustainTime; rep+= delayTime*3)
  {
    delayTime = 1000000 / (200 * 2);
    analogWrite(DAC1, 4095);
    delayMicroseconds(delayTime);
    analogWrite(DAC1, 0);
    delayMicroseconds(delayTime);
    //Serial.println("test");
  }
  
    
}

void  PlaySounds::sawtooth()
{
//maybe done
  
  for(int i = 0; i <= soundPeak; i++)
  {
    analogWrite(DAC1, i);
    delayMicroseconds(delayTimeSaw);
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
