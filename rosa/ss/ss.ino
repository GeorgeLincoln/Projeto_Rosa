#include <SoftwareSerial.h>

SoftwareSerial mySerial(12, 10); // conecta na porta 12

//Canais de comunicação
// A = potência de todos os motores
// Outros são para movimentação
int E=0,R=0,T=0,A=0;

//Para receber o valor do canal
String numero="";

// Calibragem dos canais
int e_min,e_max;
int r_min,r_max;
int t_min,t_max;
int a_min,a_max;

// nome dos motores do circuito
int um = 5;
int dois = 6;
int tres = 3;
int quatro = 10;
int cinco = 11;
int seis = 9;
  pinMode(tres,OUTPUT);
  pinMode(um,OUTPUT);
  pinMode(dois,OUTPUT);
void setup() {
  Serial.begin(9600);
  
  //esperando Serial virtual(RX, TX)
  while (!Serial) {
    ; 
  }

  mySerial.begin(9600);
  pinMode(tres,OUTPUT);
  pinMode(um,OUTPUT);
  pinMode(dois,OUTPUT);
}

void loop() { 
  //controle de movimento
  int c_um;
  int c_dois;
  int c_tres;
  int c_quatro;
  int c_cinco;
  int c_seis;
  
  // Tratamento para coleta dos dados seriais.
  if (mySerial.available()) {
   
    char c = mySerial.read();
    //Serial.write(c);

    // Calibra e envia a potência para os motores
    switch(c){
               
      case 'E': A = numero.toInt();
                numero="";
                if(A > a_max)
                  a_max = A;
                if(A < a_min)
                  a_min = A;
                
                // Reduz a capacidade dos motores em 25%
                A = map(A,a_max,192,a_min,255);
                A += (192-(255-192));

                // Limitar o mínimo
                if(A > 255)
                  A = 255;
                // Limitar o máximo  
                if(A < 129)
                  A = 129;
                
                // liga todos os motores depois de seta a potência
                analogWrite(um,A);
                analogWrite(dois,A);
                analogWrite(tres,A);
                analogWrite(quatro,A);
                analogWrite(cinco,A);
                analogWrite(seis,A);
                break;
                
      case 'R': E = numero.toInt(); // canal x
                if(E > e_max)
                  e_max = E;
                if(E < e_min)
                  e_min = E;
                E = map(E,e_max,100,e_min,-100);
                E += -100;
                numero="";
                break;
                
      case 'T': R = numero.toInt();
      
                R= map(R,r_max,192,r_min,255);
                R += 129;
                
                numero="";
                break;
                
      case 'A': T = numero.toInt();

                T = map(T,t_max,192,t_min,255);
                T += 129;
                
                numero="";
                break;
                
      default:
                numero+=c;
    }
  }

    // Acionamento dos motores.

    


  
}
