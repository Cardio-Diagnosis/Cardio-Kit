// variables
int pulsePin = 1;                 
int blinkPin = 13;                
int fadePin = 5;                  
int fadeRate = 0; 
float locMax = 0;
float locMin = 999999;
int count = 0;               

// volatile variables
volatile int BPM;                   
volatile int Signal;                
volatile int IBI = 600;             
volatile boolean Pulse = false;     
volatile boolean QS = false;       

static boolean serialVisual = true;   

void setup(){
  pinMode(blinkPin,OUTPUT);         
  pinMode(fadePin,OUTPUT);          
  Serial.begin(9600);             
  interruptSetup();                
}

void loop(){
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (18.0 / 1023.0);
  Serial.print(voltage);
  if(count < 19200)
  {
    locMin = 99999;
    locMax = 0;
  }
  else if(locMax < voltage)
    locMax = voltage;
  else if(locMin > voltage)
    locMin = voltage;
    
    serialOutput(locMax-locMin < 4) ;       
    
  if (QS == true){     
        digitalWrite(blinkPin,HIGH);      
        fadeRate = 255;                           
        serialOutputWhenBeatHappens();        
        QS = false;                      
  }
  ledFadeToBeat();                      
  delay(20);                             
}

void ledFadeToBeat(){
    fadeRate -= 15;                         
    fadeRate = constrain(fadeRate,0,255);   
    analogWrite(fadePin,fadeRate);          
}




