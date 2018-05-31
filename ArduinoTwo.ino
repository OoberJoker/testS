#include <Wire.h>

const int analogIn = A0;
int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
int RawValue= 0;
int ACSoffset = 2500; 
double Voltage = 0;
double Amps = 0;
int actuatorRuntime=0;
char messageType;


void messageReceived(int bytes){
  if(Wire.available()){
    messageType = Wire.read(); 
  }  
}

void transmitMessage(){
  Wire.write(actuatorRuntime);
  delay(3);
}

void setup() {
  // put your setup code here, to run once:
Wire.begin(5);
Wire.onReceive(messageReceived);
Serial.begin(9600);

 // put your main code here, to run repeatedly:
 if(messageType=='F'){
             RawValue = analogRead(analogIn);
             Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
             Amps = ((Voltage - ACSoffset) / mVperAmp);

             while(Amps < -0.7){
                 RawValue = analogRead(analogIn);
                 Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
                 Amps = ((Voltage - ACSoffset) / mVperAmp);             
                 
                 actuatorRuntime++;             
                 Serial.print("\t Amps= "); // shows the voltage measured 
                 Serial.println(Amps,3); // the '3' after voltage allows you to display 3 digits after decimal point
                 delay(1000);              
            }

  }

 else if(messageType=='R'){
               RawValue = analogRead(analogIn);
               Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
               Amps = ((Voltage - ACSoffset) / mVperAmp);

              while(Amps>0.8){
                 RawValue = analogRead(analogIn); 
                 Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
                 Amps = ((Voltage - ACSoffset) / mVperAmp);
                 
                 actuatorRuntime++;           
                 Serial.print("\t Amps = "); // shows the voltage measured 
                 Serial.println(Amps,3); // the '3' after voltage allows you to display 3 digits after decimal point                         
                 delay(1000);                       
            }
  }
  
  
  else if(messageType=='E'){
    actuatorRuntime=0;
  }
   Wire.onRequest(transmitMessage);    
 
            
}

void loop() {
 
         
}




