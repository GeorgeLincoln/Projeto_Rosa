#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);  // conecta na porta 11

//Variaveis dos canais
byte rud = 3;
byte ele = 9;
byte thr = 5;
byte ail = 6;
 
void setup() 
{
  // Setando as portas de Entrada
  pinMode(rud, INPUT);
  pinMode(ele, INPUT);
  pinMode(thr, INPUT);
  pinMode(ail, INPUT);
  
  Serial.begin(9600);
  mySerial.begin(9600);
}
 
void loop() {
  
  //Pegando o pulso da variável e printando as variáveis
  int ele_ = pulseIn(ele,HIGH);

  Serial.print('E');
  Serial.print(ele_);
  mySerial.print('E');
  mySerial.print(ele_);

  int rud_ = pulseIn(rud,HIGH);

  Serial.print('R');
  Serial.print(rud_);
  mySerial.print('R');
  mySerial.print(rud_);
  
  int thr_ = pulseIn(thr,HIGH);
  
  Serial.print('T');
  Serial.print(thr_);
  mySerial.print('T');
  mySerial.print(thr_);
  
  int ail_ = pulseIn(ail,HIGH);
  
  Serial.print('A');
  Serial.println(ail_);
  mySerial.print('A');
  mySerial.println(ail_);
  
  
}

