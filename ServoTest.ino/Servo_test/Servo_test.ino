#include <Servo.h>

Servo myservo1;
Servo myservo2;


  int pos;
  int pos2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Servo pinMode

  myservo1.attach(2),
  myservo2.attach(3);

  // Set servos to position 0

  myservo1.write(90);
  myservo2.write(90);

  delay(5000);

}

void reSet () { 
   delay(1000);

   myservo1.write(90);
   myservo2.write(90);

   delay(1000);
}


//transición a etapa 1

void Etapa1(){
      for(pos=10; pos<=180;pos++){
        myservo1.write(pos);
        myservo2.write(180-pos);
        delay(50);
        
      }
}
// transición a etapa 3

void Etapa3(){
      for(pos=180; pos>=10;pos--){
        myservo1.write(pos);
        myservo2.write(170+pos);
        delay(50);
           
      }
}

// transición a etapa 2
void Etapa2(){
      for(pos2=10;pos2<=180;pos2++){
        myservo1.write(10);
        myservo2.write(pos2);
               
      }
}

//transición etapa 4

void Etapa4(){
      for(pos=10; pos<=180;pos++){
        myservo1.write(pos);
        myservo2.write(pos);
        
      }

}
void loop() {
  Etapa4();
  reSet();
  Etapa1();
  reSet();
  Etapa3();
  reSet();
  Etapa2();
  reSet();
  
 
}





//    myservo1.write(180);
//    myservo2.write(180);
//
//    delay(1000);
//
//    myservo1.write(180);
//    myservo2.write(10);
//
//     delay(1000);
//
//    myservo1.write(10);
//    myservo2.write(180);
//
//     delay(1000);
//
//    myservo1.write(10);
//    myservo2.write(10);
//
//    delay(3000);
   
//  // put your main code here, to run repeatedly:
//
//    for (pos=0; pos<=180; pos++){
//    
//    myservo1.write(pos);
//    delay(20);
//    myservo2.write(180-pos);
//    Serial.println(pos);
//    delay(20);
//      }
//
//    for (pos=180; pos>=0;pos--){
//    myservo1.write(pos);
//    delay(20);
//    myservo2.write(0+pos);
//    Serial.println(pos);
//    delay(20);
//    }
  //
