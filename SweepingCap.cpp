/* SweepingCap.cpp Library for Sweeping Frequency Capacitance Touch Sensing
 Based on DZL's Arduino port of the Touche project.
 Library Created by Colin Honigman. November 2013
 Released into the public domain.
 */

#include "Arduino.h"
#include "SweepingCap.h"

#define SET(x,y) (x |=(1<<y))				//-Bit set/clear macros
#define CLR(x,y) (x &= (~(1<<y)))       	// |
#define CHK(x,y) (x & (1<<y))           	// |
#define TOG(x,y) (x^=(1<<y))            	//-+

SweepingCap::SweepingCap(unsigned char howManyFrequencies)
{
    timer = 0;
    allTimers = true;
    numFrequencies = howManyFrequencies;
}

SweepingCap::SweepingCap(int whichTimer, unsigned char howManyFrequencies)
{
    timer = whichTimer;
    allTimers = false;
    numFrequencies = howManyFrequencies;
}

void SweepingCap::setup()
{
  if( allTimers )
    {


	  
            TCCR1A=0b10000010;        //-Set up frequency generator (clear OC1A on compare match)
            TCCR1B=0b00011001;        //-+ (no prescaling; ctc mode on ICR1A)
            ICR1=110;
            OCR1A=55;
            pinMode(9, OUTPUT);
	    
    }
    else {
        if(timer == 1)
        {

  
            TCCR1A=0b10000010;        //-Set up frequency generator (clear OC1A on compare match)
            TCCR1B=0b00011001;        //-+ (no prescaling; ctc mode on ICR1A)
            ICR1=110;
            OCR1A=55;
            pinMode(9, OUTPUT);
   
        }

}

void SweepingCap::sweep(int freq)
{
    if( allTimers )
    {      
        CLR(TCCR1B, 0);
        TCNT1 = 0;
        ICR1 = freq;
        OCR1A = freq/2;
        SET(TCCR1B, 0);
        
    }
    else {
        if(timer == 1)
        {
            CLR(TCCR1B, 0);
            TCNT1 = 0;
            ICR1 = freq;
            OCR1A = freq/2;
            SET(TCCR1B, 0);
        }
    }
	
	delayMicroseconds(1);
	
}

unsigned char SweepingCap::getNumFrequencies()
{
    return numFrequencies;
}
