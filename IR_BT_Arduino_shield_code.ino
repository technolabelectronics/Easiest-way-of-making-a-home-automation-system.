
#include <IRremote.h>
//Define PIN constant
const int switch_1 = 7;
const int switch_2 = 8;



int RECV_PIN = 11;

int toggleState_1 = 0; //Define integer to remember the toggle state for switch 1
int toggleState_2 = 0; //Define integer to remember the toggle state for switch 2




//Define IR receiver and Result Objects
IRrecv irrecv(RECV_PIN);
decode_results results;



void all_Switch_ON(){
 digitalWrite(switch_1, HIGH);
 digitalWrite(switch_2, HIGH);
  

}

void all_Switch_OFF(){
digitalWrite(switch_1, LOW);
digitalWrite(switch_2, LOW);
  

}

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Enable the IR receiver
   pinMode(switch_1, OUTPUT);
   pinMode(switch_2, OUTPUT);
  
  

}

void loop() {

if(Serial.available()>0)
   {     
      char data= Serial.read(); // reading the data received from the bluetooth module
      switch(data)
      {
        case 'a': digitalWrite(switch_1, HIGH);break; // when Z is pressed on the app Turn on Pin 12
        case 'A': digitalWrite(switch_1, LOW);break; // when z is pressed on the app Turn off Pin 12
        case 'b': digitalWrite(switch_2, HIGH);break; // when Y is pressed on the app Turn on Pin 11
        case 'B': digitalWrite(switch_2, LOW);break; // when y is pressed on the app Turn off Pin 11
        case 'c': all_Switch_ON(); break;  // if 'Z' received Turn on all Relays
        case 'C': all_Switch_OFF(); break; // if 'z' received Turn off all Relays
        
        default : break;
      }
      //Serial.println(data);
   }
   delay(100);

 
  if (irrecv.decode(&results)) {

    switch(results.value){
      case 14517: 
                if(toggleState_1 == 0){
                  digitalWrite(switch_1, HIGH); // turn on switch 1
                  toggleState_1 = 1;
                  }
                else{
                  digitalWrite(switch_1, LOW); // turn off switch 1
                  toggleState_1 = 0;
                  }
                  delay(100);
                  break;
      case 14488: 
                if(toggleState_2 == 0){
                  digitalWrite(switch_2, HIGH); // turn on switch 2
                  toggleState_2 = 1;
                  }
                else{
                  digitalWrite(switch_2, LOW); // turn off switch 2
                  toggleState_2 = 0;
                  }
                  delay(100);
                  break;
      
                
         default : break;      
      }
    
    irrecv.resume(); // Receive the next value
  }

}
