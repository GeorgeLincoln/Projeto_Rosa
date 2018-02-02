#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);  // conecta na porta 11

byte rud = 3;
byte ele = 9;
byte thr = 5;
byte ail = 6;
 
int rud_max=0,rud_min=2000;
int ele_max=0,ele_min=2000;
int thr_max=0,thr_min=2000;
int ail_max=0,ail_min=2000;

void calibracao(){

  int tempo=0;
  
  while(tempo<5){
  
    int aux=pulseIn(rud,HIGH);
    
    if(aux<rud_min)
      rud_min=aux;
    
    if(aux>rud_max)
      rud_max=aux;

        aux=pulseIn(ele,HIGH);
    
    if(aux<ele_min)
      ele_min=aux;
    
    if(aux>ele_max)
      ele_max=aux;

      
        aux=pulseIn(thr,HIGH);
    
    if(aux<thr_min)
      thr_min=aux;
    
    if(aux>thr_max)
      thr_max=aux;

  
        aux=pulseIn(ail,HIGH);
    
    if(aux<ail_min)
      ail_min=aux;
    
    if(aux>ail_max)
      ail_max=aux;
    
    tempo++;
    
    digitalWrite(13,HIGH);
    delay(500);
    digitalWrite(13,LOW);
    delay(500); 
  }
  
  }
 
void setup() {
  
  pinMode(13,  OUTPUT);
  pinMode(rud, INPUT);
  pinMode(ele, INPUT);
  pinMode(thr, INPUT);
  pinMode(ail, INPUT);
  
  Serial.begin(9600);
  mySerial.begin(9600);
  
  //calibracao(); não é necessario
}
 
void loop() {

  
  
  int ele_ = map(pulseIn(ele,HIGH),ele_min,0,ele_max,100);

  Serial.print('E');
  Serial.print(ele_);
  mySerial.print('E');
  mySerial.print(ele_);
  

  int rud_ = map(pulseIn(rud,HIGH),rud_min,0,rud_max,100);
  

  Serial.print('R');
  Serial.print(rud_);
  mySerial.print('R');
  mySerial.print(rud_);
  
 
  int thr_ = map(pulseIn(thr,HIGH),thr_min,0,thr_max,100);
  
  Serial.print('T');
  Serial.print(thr_);
  mySerial.print('T');
  mySerial.print(thr_);
  
  
  int ail_ = map(pulseIn(ail,HIGH),ail_min,0,ail_max,100);
  
  Serial.print('A');
  Serial.println(ail_);
  mySerial.print('A');
  mySerial.println(ail_);
  
  
}

