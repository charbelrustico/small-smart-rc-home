#include <SoftwareSerial.h>
#include <Servo.h>
Servo servo;
int i;
int D2 = A0;
int D3 = A1;





void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  servo.attach(13);
  Serial.begin(9600);
  digitalWrite(9, HIGH);
  ouverture();

}

void loop() {
  // put your main code here, to run repeatedly:
  char command = 'o';
  if(Serial.available()){
    command = (char)Serial.read();

    switch(command){

      case 'V':
        digitalWrite(9, LOW);
        Serial.println("Démarrage de la ventillation");
        break;

        
      case 'v':
        digitalWrite(9, HIGH);
        Serial.println("Arrêt de la ventillation");
        break;

        
      case 'S':
        fermeture();
        Serial.println("Ouverture de la porte");
        break;

        
      case 's':
        ouverture();
        Serial.println("Fermerture de la porte");
        break;

        
       case 'L':
        analogWrite(D2, 255);
        Serial.println("Eclairage de la coure activé");
        break;

        
      case 'l':
        analogWrite(D2, LOW);
        Serial.println("Eclairage de la coure désactivé");
        break;

        
      case 'I':
        analogWrite(D3, 255);
        Serial.println("Eclairage de la intérieur activé");
        break;

        
      case 'i':
        digitalWrite(D3, LOW);
        Serial.println("Eclairage de la intérieur désactivé");
        break;

        
      default:
        Serial.println("Commande inconnue");
        break;
      
      

      
    }

    
    }

}




void ouverture(){

  for(i = 0; i <= 180; i++){

    servo.write(i);
    delay(25);
    }
  }


  void fermeture(){

  for(i = 180; i >= 0; i--){

    servo.write(i);
    delay(25);
    }
  }
