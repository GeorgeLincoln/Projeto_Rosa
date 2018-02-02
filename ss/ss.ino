#include <SoftwareSerial.h>

SoftwareSerial mySerial(12, 10); // conecta na porta 12

//Canais de comunicação
// A = potência de todos os motores
// Outros são para movimentação
int R=0,A=0;
float E = 0.0, T = 0.0;
float Y = 0.0, X = 0.0;

//Para receber o valor do canal
String numero="";

// Calibragem dos canais
int e_min,e_max;
int r_min,r_max;
int t_min,t_max;
int a_min,a_max;

// nome dos motores do circuito
int um = 3;
int dois = 5;
int tres = 9;
int quatro = 11;
int cinco = 10;
int seis = 6;
  
void setup() {

  pinMode(tres,OUTPUT);
  pinMode(um,OUTPUT);
  pinMode(dois,OUTPUT);
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
  
  
  // Tratamento para coleta dos dados seriais.
  if (mySerial.available()) {
   
    char c = mySerial.read();
    //Serial.write(c);
    
    //Setando potência
    float cont1 = 1;
    float cont2 = 1;
    float cont3 = 1;
    float cont4 = 1;
    float cont5 = 1;
    float cont6 = 1;

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
                
                                  
                if(E > 0 && T == 0 ){// Ir para Frente
                  Y = E;
                  cont1 = 1-(Y/100);
                  cont2 = 1-(Y/100);
                  cont3 = 1-(Y/100);
                  cont4 = 1-(Y/100);
                }
                if(E < 0 && T == 0){// Ir para atras
                   Y = E*(-1);
                  cont3 = 1-(Y/100);
                  cont4 = 1-(Y/100);
                  cont5 = 1-(Y/100);
                  cont6 = 1-(Y/100);
                 
                }
                if(T > 0 && E == 0){//Ir para DIREITA
                  X = T;
                  cont2 = 1-(X/100);
                  cont4 = 1-(X/100);
                  cont6 = 1-(X/100);
                }
                if(T < 0 && E == 0){//Ir para ESQUERDA
                  X = T * (-1);
                  cont1 = 1-(X/100);
                  cont3 = 1-(X/100);
                  cont5 = 1-(X/100);
                }
                if(E>0 && T>0){// Dioagonal Superior Direita
                  X = T;
                  Y = E;
                 cont1 = 1-((X+Y)/2/100);
                 cont2 = 1-((X+Y)/2/100);
                 cont3 = 1;
                 cont4 = 1-((X+Y)/2/100);
                 cont5 = 1;
                 cont6 = 1;
               }
               if(E>0 && T<0){//diagonal Superior esquerda
                 X = T*(-1);
                 Y = E;
                 cont1 = 1-((X+Y)/2/100);
                 cont2 = 1-((X+Y)/2/100);
                 cont3 = 1-((X+Y)/2/100);
                 cont4 = 1;
                 cont5 = 1;
                 cont6 = 1;
               }
               if(E<0 && T>0){// Dioagonal Inferior Direita
                  X = T;
                  Y = E*(-1);
                 cont1 = 1;
                 cont2 = 1;
                 cont3 = 1;
                 cont4 = 1-((X+Y)/2/100);
                 cont5 = 1-((X+Y)/2/100);
                 cont6 = 1-((X+Y)/2/100);
               }
               if(E<0 && T<0){//diagonal Inferior esquerda
                 X = T*(-1);
                 Y = E*(-1);
                 cont1 = 1;
                 cont2 = 1;
                 cont3 = 1-((X+Y)/2/100);
                 cont4 = 1;
                 cont5 = 1-((X+Y)/2/100);
                 cont6 = 1-((X+Y)/2/100);
               }
                

                
                
                
                Serial.println();
                Serial.println();
                Serial.print(cont1);
                Serial.print("====");
                Serial.println(cont2);
                Serial.print(cont3);
                Serial.print("====");
                Serial.println(cont4);
                Serial.print(cont5);
                Serial.print("====");
                Serial.println(cont6);
                Serial.println();
                Serial.println();
                
                // liga todos os motores depois de seta a potência
                
                analogWrite(um,A*cont1);
                analogWrite(dois,A*cont2);
                analogWrite(tres,A*cont3);
                analogWrite(quatro,A*cont4);
                analogWrite(cinco,A*cont5);
                analogWrite(seis,A*cont6);
                break;
                
      case 'R': E = numero.toInt(); // canal y direito 
                if(E > e_max)
                  e_max = E;
                if(E < e_min)
                  e_min = E;
                E = map(E,e_min,e_max,-350,100);
                numero="";
                if(E > 95){ // Truncamento para o máximo
                  E = 100;
                }
                if(E > -6 && E < 6){// Truncamento para 0
                  E = 0 ;
                }
                
                if(E < -95){ // Truncamento para o mínimo
                  E = -100;
                }
                break;
                
      case 'T': R = numero.toInt(); // canal x esquerdo 
                if(R > r_max)
                  r_max = R;
                if(R < r_min)
                  r_min = R;
                R = map(R,r_min,r_max,-350,100);
                numero="";
                if(R > 95){// Truncamento para o máximo
                  R = 100;
                }
                if(R > -5 && R < 5){ // Truncamento para 0
                  R = 0 ;
                }
                if(R < -95){ // Truncamento para o mínimo
                  R = -100;
                }
                break;
                
      case 'A': T = numero.toInt(); // canal x direito
                if(T > t_max)
                  t_max = T;
                if(T < r_min)
                  t_min = T;
                T = map(T,t_min,t_max,-350,100);// invertendo valor para fins de leitura
                T *= -1;
                numero="";
                if(T > 95){ // Truncamento para o máximo
                  T = 100;
                }
                if(T > -6 && T < 6){ // Truncamento para 0
                  T = 0 ;
                }
                if(T < -95){ // Truncamento para o mínimo
                  T = -100;
                }
                break;
                
      default:
                numero+=c;
    }
  }

    // Acionamento dos motores.

    


  
}
