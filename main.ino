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

int STARTLEDPIN = 12;
int STARTSWITCHPIN = 11;

int STARTPHRPIN = A0;
int STARTBSPIN = 0;
int STARTKNPIN = A11;


void updatePHR(bool* PHR)
{
    for(int rep = 0; rep< 12; rep++)
    {
        //something like this
        PHR[rep] = (analogRead(rep + STARTPHRPIN) < (lightCal - sensitivity));
        Serial.println(PHR[0]);
     
    }
}

void updateBS(bool* BS)
{
    for(int rep = 0; rep< 4; rep++)
    {
        //something like this
        BS[rep] = digitalRead(STARTBSPIN + rep);
    }
}

void updateKN(int* KN)
{
    for(int rep = 0; rep< 6; rep++)
    {
        //something like this
        BS[rep] = analogRead(STARTKNPIN + rep);
    }
}


void setup()
{
    analogReadResolution(10);
    analogWriteResolution(10);
    Serial.begin(9600);

    pinMode(STARTSWITCHPIN, INPUT_PULLUP); // sets start pin mode. i think PULLUP does automatic debouncing
    pinMode(STARTLEDPIN, OUTPUT); // DECLARE THAT FIRST SUCKA AS OUTPUT !!!!!!!!!!!!
    
    lightCal = analogRead(STARTPHRPIN); //initialized light calibration value at first PHR
    //maybe change this to an average of all of them at startup
}

void loop()
{
    //change switch pin
    //on = digitalRead(STARTSWITCHPIN);
    on = true;
    if(on)
    {
        //ON led
        digitalWrite(STARTLEDPIN, HIGH); 
        
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

        //stop will stop all sounds from being output. This essentially sets the volume to 0.
        exec.stop();
    }
    
    
}
