//final synthesizer codesss
//XD lmao hahha epix gamers momemtns
//finalcode.cpp

/*
    
    Jace Bayless
    Markus Becerra
    Max Goad
    Tri Pham
    Apurva Rai
    Minye Wu
    
*/

#include <DueTimer.h>
#include <SineWaveDue.h>
#include "PlaySounds.h"


bool *PHR = new bool[12];   // photoresistor value array
bool *BS  = new bool [4];   // button value array
int  *KN  = new int  [6];   // knob value array

int lightCal;   // PHR calibration value
const int sensitivity = 100;    // PHR activation sensitivity

bool on = false;

//main exec function for sounds
PlaySounds exec;

int STARTLEDPIN = 24;
int STARTLEDPINOFF = 22;
int STARTSWITCHPIN = 12;


int STARTPHRPIN = A0;
int STARTBSPIN = 2;
int STARTKNPIN = -1;


bool temp[4] = {0,0,0,0};






void updatePHR(bool* PHR)
{
    for(int rep = 0; rep< 12; rep++)
    {
        //something like this
        PHR[rep] = (analogRead(rep + STARTPHRPIN) < lightCal - sensitivity);
     
    }
}

void updateBS(bool* BS)
{
    for(int rep = 0; rep< 4; rep++)
    {
        //something like this
        BS[rep] = digitalRead(2 + rep);
        
        if(BS[rep] == 1 && temp[rep] == 0)
        {
           BS[rep] = 1;
           temp[rep] = 1;
        }

        else if(BS[rep] == 1 && temp[rep] == 1)
        {
           BS[rep] = 0;
           temp[rep] = 1;
        }
        else if(BS[rep] == 0 && temp[rep] == 1)
        {
           delay(200);
           BS[rep] = 0;
           temp[rep] = 0;
        }
        else if(BS[rep] == 0 && temp[rep] == 0)
        {
           BS[rep] = 0;
           temp[rep] = 0;
        }

    }
}

void updateKN(int* KN)
{
    for(int rep = 0; rep< 6; rep++)
    {
        //something like this
        //BS[rep] = analogRead(STARTKNPIN + rep);
    }
}


void setup()
{

    analogReadResolution(10);
    analogWriteResolution(10);
    Serial.begin(9600);

    pinMode(22, OUTPUT); // off led
    pinMode(24, OUTPUT); // on led

    pinMode(26, OUTPUT); // square
    pinMode(28, OUTPUT); // saw 
    pinMode(30, OUTPUT); // sine


    pinMode(12, INPUT_PULLUP); // start switch
    pinMode(2, INPUT_PULLUP); // start switch
    pinMode(3, INPUT_PULLUP); // start switch
    pinMode(4, INPUT_PULLUP); // start switch
    pinMode(5, INPUT_PULLUP); // start switch
    

    lightCal = analogRead(STARTPHRPIN); //initialized light calibration value at first PHR
    //maybe change this to an average of all of them at startup

    sw.setPin(DAC1);
}

void loop()
{
    //change switch pin
    on = digitalRead(STARTSWITCHPIN);
    if(on)
    {
        //ON led
        digitalWrite(STARTLEDPIN, HIGH);
        digitalWrite(STARTLEDPINOFF, LOW);
            
        //update input values
        updatePHR(PHR);
        updateBS(BS);
        updateKN(KN);
        
        //This exec function will update output values given the input
        //output values : leds, aux, bluetooth
        
        exec.run(PHR, BS, KN);
        
        
        
    }
    
    else if(!on)
    {
        //ON led
        digitalWrite(STARTLEDPIN, LOW);
        digitalWrite(STARTLEDPINOFF, HIGH);
        exec.stop();
    }
    
    
}
