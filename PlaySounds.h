//PlaySounds.h

#ifndef PLAY_SOUNDS_H_
#define PLAY_SOUNDS_H_


#include <DueTimer.h>    // use the DueTimer library for timing
#include <SineWaveDue.h>
#define OUTPIN  DAC0

class PlaySounds
{
    public:
            void run(bool* PH, bool* BS, int* KN);
            void stop();
         
    
    private:
            bool* PHR = new bool[2];
            bool* BS = new bool[2];
            int* KN = new int[10];
    
            char waveform = 'q';

            int hertz = 400;
            int volume = 0; // from 0 to 1023

            double delayTime = 1000000 / (hertz * 2);
            int soundPeak = 4095;
            double delayTimeSaw = (1000000 / (2*hertz))/(soundPeak + 1);

            int sustainTime = 1.0 * 1000000; //in seconds
            
    
            void updateWaveform();
            void playSound(int note); // will play sound according to which phr is activated
                              // and ADSR settings and filter settings and waveform settings
                              // int note will be which note on the scale to play
            void sine();
            void pulse();
            void sawtooth();
            
    
            void lpf(); // appends the filter to the wave code
            void outputWave();// takes signal as input and outputs it to the aux/bluetooth
            void adder(); // adds the waves of the different PHRS
            void mult(); // maybe epic
            void ADSR();

            void sequencerStartStop();
            void sequencerRecord();

            void secret();

            void clearPHR();
            void clearBS();
            void clearKN();

            
            
    
};

#endif
