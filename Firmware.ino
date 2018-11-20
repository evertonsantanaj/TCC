#include <SoftwareSerial.h>
#define TxBt 33 //pino 4.0 recebe TX do BT =>33
#define RxBt 34 //pino 4.3 recebe RX do BT=>34
SoftwareSerial Bluetooth(TxBt,RxBt);

int dmax = 100; //ajustável

//Define pinos dos sensores. Trigger é comum a ambos
const int pingTrigger = 32; //32 - pino 3.7
const int Sensor_1 = 40; //31 - pino 8.2 
const int Sensor_2 = 31; //40 - p2.5

char Dist;
  
void setup() {
  
   pinMode(pingTrigger, OUTPUT);
   pinMode(Sensor_1, INPUT);
   pinMode(Sensor_2, INPUT);
   
  // initialize serial communication:
  //Serial.begin(9600);
   Bluetooth.begin(9600);
   Dist='n';
}

void loop()
{
  // variaveis para armazenamento de valores
  long duracao, distancia_cm1, distancia_cm2;

  // SENSOR 1 
  digitalWrite(pingTrigger, LOW); //para assegurar borda de subida
  delayMicroseconds(2);
  digitalWrite(pingTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingTrigger, LOW);

  duracao = pulseIn(Sensor_1, HIGH);  //tempo do envio do sinal pelo tigger até sua recepcao no echo, caso haja

  distancia_cm1 = microsecondsToCentimeters(duracao); //converte duracao em distancia

  delay(100);

  // SENSOR 2
  digitalWrite(pingTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pingTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingTrigger, LOW);

  duracao = pulseIn(Sensor_2, HIGH);

 distancia_cm2 = microsecondsToCentimeters(duracao);

  delay(100);
  
 // para evitar falsos positivos de  obstáculos
if(distancia_cm1==0){
  distancia_cm1=1000;
}

if(distancia_cm2==0){
  distancia_cm2=1000;
}

 if(distancia_cm1<dmax||distancia_cm2<dmax){ // só faz sentido detectar obstáculo mais proximo se houver um
  if(abs(distancia_cm1-distancia_cm2)<2){
  Dist='c';
  //Bluetooth.print("Dist/");
  Bluetooth.print("c/");
  Bluetooth.println((distancia_cm1+distancia_cm2)/2);
  
} else if(distancia_cm1<distancia_cm2){
  Dist='d';
  //Bluetooth.print("Dist/");
  Bluetooth.print("d/");
  Bluetooth.println(distancia_cm1);
  }else  if( distancia_cm2<distancia_cm1){
      Dist='e';
 //   Bluetooth.print("Dist/");
  Bluetooth.print("e/");
  Bluetooth.println(distancia_cm2);
 }}
 
  delay(500);
}

long microsecondsToCentimeters(long microseconds){
//velocidade do som no ar: 340m/s = 34000cm/1000000us
//o fator 2 no denominador ocorre porqueo o valor recebido corresponde ida e volta
  return microseconds*34000 /(1000000*2);
}
