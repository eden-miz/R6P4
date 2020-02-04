#include<SoftwareSerial.h>

//-- MOTEUR A -- // Direction du Moteur A
byte ENA=10; 
byte IN1=8; 
int IN2=7; 

int forcePin = 0; // analog pin 0 connected to force sensor
int valF;  // value of force sensor
int thresHold = 500; // defines force sensor pressure threshold


const int bouton=5;
int val=1;
int etat=1;
int ancien_val=1;

SoftwareSerial BlueT(11, 3);
char Data;
int PWM;

void avancer();
void reculer();
void stopMvt();

void avancer() {
  analogWrite(ENA, 200);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  
}
void stopMvt() {
  analogWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}
void reculer() {
  analogWrite(ENA, 200);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void setup() {
  Serial.begin(9600);
  BlueT.begin(9600);

  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  digitalWrite(ENA,LOW);// Moteur A - Ne pas tourner
  //Direction du moteur A
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

}
void loop() {
  val=digitalRead(bouton);
  valF = analogRead(forcePin); // read value of force sensor
  if( (val==LOW)&&(ancien_val==HIGH)){
    etat=1-etat;}
    ancien_val=val;
  if (etat==HIGH){
      if (valF>=thresHold) { // waits for force sensor to equal or pass pressure threshold and then:
      // Tourne dans le sens direct 
         if (BlueT.available()){
            Data=BlueT.read();
            if (Data=='1') {
                Serial.println("Avancer");
                avancer();
                delay(3000);
                stopMvt();
            }
            if (Data=='2') {
               Serial.println("Avancer");
               avancer();
               delay(5000);
               stopMvt();
            }
            if (Data=='3') {
               Serial.println("Avancer");
               avancer();
               delay(7000);
               stopMvt();
          }
   else {
    reculer();
    delay(7000);
    stopMvt();  
   }
    }
      }
  }
}
