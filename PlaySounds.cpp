//PlaySounds.cpp

#include "PlaySounds.h"
#include <DueTimer.h>

PlaySounds::PlaySounds()
{
  /*
    digitalWrite(26, HIGH);
    digitalWrite(28, LOW);
    digitalWrite(30, LOW);
    */
}

void PlaySounds::updatePHR(bool * PHR)
{
  //different than main, adds debounce
 
  for(int rep = 0; rep< 12; rep++)
  {
    //something like this
    PHR[rep] = (analogRead(rep + A0) < 100);

    if(PHR[rep] == 1 && temp[rep] == 0)
    {
       PHR[rep] = 1;
       temp[rep] = 1;
    }

    else if(PHR[rep] == 1 && temp[rep] == 1)
    {
       PHR[rep] = 0;
       temp[rep] = 1;
    }
    else if(PHR[rep] == 0 && temp[rep] == 1)
    {
       delay(200);
       PHR[rep] = 0;
       temp[rep] = 0;
    }
    else if(BS[rep] == 0 && temp[rep] == 0)
    {
       BS[rep] = 0;
       temp[rep] = 0;
    }
   
  }
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
  
  if(BS[2])
  {
    
    digitalWrite(32, HIGH);
    keysRecord.clear();
    delay(200);
    BS[2] = 0;
    
    while(!BS[2])
    {
      updatePHR(PH);

      for(int rep = 0; rep<12; rep++)
      {
        if(PH[rep])
        {
          bool * temp = new bool[12];
          for(int x = 0; x<12; x++)
          {
            temp[x] = (PH[x]); 
              
          }
                  
          keysRecord.add(temp);
          rep = 12; 
        }
      }
      
      BS[2] = digitalRead(4);
    }    
    digitalWrite(32, LOW);
    
  }
  

  if(BS[1])
  {

    digitalWrite(34, HIGH);
    playing  = true;
    //play recording code

    delay(200);
    BS[1] = 0;

    while(!BS[1])
    {
    
      for(int rep = 0 ; rep< keysRecord.size(); rep++)
      {
        for(int y = 0; y<12; y++)
        {
          Serial.print(keysRecord.get(rep)[y]);
          Serial.print(" ");
          
          int n = 0;

          
          while(n < tempo && keysRecord.get(rep)[y])
          {
            digitalWrite(2, HIGH);
            if(digitalRead(2))
            {
              delay(200);
              if(tempo >= 200)
              {
                tempo = 10;
              }
              else 
                tempo+=30;
            }
           playSound(y);
           delayMicroseconds(1);
           BS[1] = digitalRead(3);
           n++;
 
          }

          digitalWrite(2,LOW);
        }
        Serial.println("");
      }
      BS[1] = digitalRead(3);
    }
    digitalWrite(34, LOW);
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
  once = true;
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
    delay(1);
    //maybe delete this delay
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

  /*
  if(hertz == 0) hertz = 1;
  
  delayTimeSawtooth = (1000000 / (hertz))/((volume/10) + 1);

  Serial.println(delayTimeSawtooth);
  
  for(int i = 0; i <= (volume/10); i+=10)
  {
    analogWrite(DAC1, i);
    delayMicroseconds(delayTimeSawtooth);
  }
  */

  //wow!!! will this workkkk?!?!?!
  delayTime*=2;
  

  for(int rep = 0; rep<delayTime; rep+=11)
  {
    analogWrite(DAC1, volume * ( (float) rep / delayTime));
    delayMicroseconds(1);
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
