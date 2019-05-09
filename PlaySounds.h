//PlaySounds.h

#ifndef PLAY_SOUNDS_H_
#define PLAY_SOUNDS_H_


#include <DueTimer.h>    // use the DueTimer library for timing
#include <SineWaveDue.h>
#include <LinkedList.h>
#define OUTPIN  DAC1


class PlaySounds
{
    public:
            void run(bool* PH, bool* BS, int* KN);
            void stop();
            PlaySounds();
            ~PlaySounds(){}
            
         
    
    private:
            bool* PHR = new bool[2];
            bool* BS = new bool[2];
            int* KN = new int[10];
    
            char waveform = 'q';

            bool initial = false;

            bool * temp = new bool[12];

            int tempo = 50;

            bool playing = false;
            bool recording = false;

            LinkedList<bool*> keysRecord = LinkedList<bool*>();


            bool recordPressed = false;
            int record = 0;

            bool once = true;
            
            int volume = 1023;

            int hertz = 100;

            int delayTime = 1000000 / (hertz * 2);

            int delayTimeSawtooth;
    
            void updateWaveform();
            void playSound(int rep); // will play sound according to which phr is activated
                              // and ADSR settings and filter settings and waveform settings
            void sine(int rep);
            void pulse();
            void sawtooth();

            void updatePHR(bool * PHR);

            
    
            void lpf(); // appends the filter to the wave code
            void outputWave();// takes signal as input and outputs it to the aux/bluetooth
            void adder(); // adds the waves of the different PHRS
            void mult(); // maybe epic
            void ADSR();

            
            
    
};

#endif
