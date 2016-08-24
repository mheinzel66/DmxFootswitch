
#include <DmxSimple.h>

short SWITCH_PORT = 13;   // pushbutton connected to digital pin 7
short ledRunningPin = 12; 

short SWITCH_ON = 1;   
short SWITCH_OFF = 0;  
volatile short current_switch_state = SWITCH_OFF;

short DMX_CHANNEL = 1; 
short DMX_VALUE_ON = 255; 
short DMX_VALUE_OFF = 0; 


void setup()
{
  pinMode(SWITCH_PORT, INPUT_PULLUP); 
   
  pinMode(ledRunningPin, OUTPUT);      // sets the digital pin as output
   
  Serial.begin(9600);
  
  DmxSimple.usePin(3);
  DmxSimple.maxChannel(1);
   
  stop_effect();
}


void start_effect()
{   
    //Serial.println("start_effect...");  
    
    digitalWrite(ledRunningPin, HIGH);   // sets the LED on
    //this is hardcoded for the foggers in "1 Channel" Mode   
    //0-15 off
    //32 - 255 MAX FOG & COLOR CHANGE
    DmxSimple.write(DMX_CHANNEL, DMX_VALUE_ON);
}

void stop_effect()
{     
    digitalWrite(ledRunningPin, LOW);   // sets the LED on
   // Serial.println("stop_effect"); 
    DmxSimple.write(DMX_CHANNEL, DMX_VALUE_OFF);
}

void loop() {
  
   short new_switch_state = digitalRead(SWITCH_PORT);   // read the input pin
   
   //debounce 
   delay(200); 
   if(digitalRead(SWITCH_PORT) != new_switch_state)
   {
       return;
   }
   
  //Serial.println(new_switch_state);  
  
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
}

