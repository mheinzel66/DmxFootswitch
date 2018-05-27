#include <DmxSimple.h>
//https://code.google.com/archive/p/tinkerit/wikis/DmxSimple.wiki

#define SWITCH_PORT  13   // pushbutton connected to digital pin 7
#define DMX_CHANNEL  1 
#define DMX_VALUE_ON  255 
#define DMX_VALUE_OFF  0 
#define SWITCH_ON  0   
#define SWITCH_OFF 1  

//#define DEBUG_ON

short ledRunningPin = 12; 
volatile short current_switch_state = SWITCH_OFF;

////////////////////////////////////
//Method:setup
//Description:initialization
////////////////////////////////////
void setup()
{
  pinMode(SWITCH_PORT, INPUT_PULLUP);    //use pullups so the port doesn't float
  pinMode(ledRunningPin, OUTPUT);      // sets the digital pin as output
  
  #ifdef DEBUG_ON
    Serial.begin(9600);  
  #endif
  
  DmxSimple.usePin(3);//Set the output pin. DmxSimple defaults to using pin 3
  DmxSimple.maxChannel(1);   //Set the number of DMX channels in the DMX system.  
}

/////////////////////////////////////////////////
//Method:start_effect
//Description: activates the dmx channel with 
//            the given value
//////////////////////////////////////////////////
void start_effect()
{   
  #ifdef DEBUG_ON
    Serial.println("start_effect...");  
  #endif
  
  digitalWrite(ledRunningPin, HIGH);   // sets the LED on
  
  //this is hardcoded for the foggers in "1 Channel" Mode   
  //0-15 off
  //32 - 255 MAX FOG & COLOR CHANGE
  DmxSimple.write(DMX_CHANNEL, DMX_VALUE_ON);
}


////////////////////////////////////
//Method:stop_effect
//Description: deactivates the dmx channel 
////////////////////////////////////
void stop_effect()
{     
  digitalWrite(ledRunningPin, LOW);   // sets the LED off
  
  #ifdef DEBUG_ON
    Serial.println("stop_effect"); 
  #endif
  
  DmxSimple.write(DMX_CHANNEL, DMX_VALUE_OFF);
}

////////////////////////////////////
//Method:loop
//Description: The main loop
////////////////////////////////////
void loop() {
      
  // read the input pin
  short new_switch_state = digitalRead(SWITCH_PORT);   
   
 //-----------
 //debounce 
 //-------------
  delay(200); 
  if(digitalRead(SWITCH_PORT) != new_switch_state)
  {
    return;
  }
  
  #ifdef DEBUG_ON
    Serial.println(new_switch_state);  
  #endif
  
  //if the switch state changed then control the device
  if(new_switch_state != current_switch_state)
  {  
    if (new_switch_state == SWITCH_ON)
    {            
      start_effect();
    }
    else
    {
      stop_effect();
    }
  
    current_switch_state = new_switch_state;     
  }   
   
  delay(300); 
}

