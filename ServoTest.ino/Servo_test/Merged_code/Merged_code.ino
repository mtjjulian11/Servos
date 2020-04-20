



// ------------------------------------------- Libraries -----------------------------------------------------------

#include <Servo.h>
#include "ThingSpeak.h"
#include <WiFiNINA.h>
#include "secrets.h"

// ------------------------------------------- Internet concction keys --------------------------------------------


char ssid[] = SECRET_SSID;   // your network SSID (name)
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

// -------------------------------------------  Channel details ------------------------------------------------------

// ***** sgitChannel Matching Number

unsigned long readChannelNumber = SECRET_CH_ID;

// ***** Field names

unsigned int Xdata = 1;
unsigned int Ydata = 2;
unsigned int Zdata = 3;

// ***** API read Key

const char * readAPIKey = SECRET_READ_APIKEY;

// ------------------------------------------------- Range Variables -------------------------------------------------

int RangeX;
int RangeY;
int RangeZ;

// ------------------------------------------------- Case Variable --------------------------------------------
char var;


// ------------------------------------------------- Servo Objects ----------------------------------------------------


Servo myservo1;
Servo myservo2;

int pos = 90;
int pos2 = 90;

int Time = 10;
int Time1 = 50;



//_________________________________________________ SETUP ______________________________________________________________


void setup() {

  Serial.begin(115200);      // Initialize serial
  ThingSpeak.begin(client);  // Initialize ThingSpeak

  // Servo pinMode

  myservo1.attach(2),
                  myservo2.attach(3);

  // Set servos to initial position

  myservo1.write(pos);
  myservo2.write(pos2);

  delay(5000);

}





//_________________________________________________ LOOP ______________________________________________________________


void loop() {

  int statusCode = 0;


  // -------------------------------------- Connect or reconnect to WiFi

  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected");
  }

  // --------------------------------------- Obtain values for field X ---------------------------------------------------

  long x = ThingSpeak.readIntField(readChannelNumber, Xdata, readAPIKey);
  // Check the status of the read operation to see if it was successful
  statusCode = ThingSpeak.getLastReadStatus();

  //---------------- Mapping of the Read Field parameter

  float mapX = map(x, -4.0, 4.0, 1.0, 10.0); // Im not sure of the max a mins values for the mapping.

  //----------------- Generate range of X

  if (mapX >= 1.0 && mapX <= 5.0) {
    RangeX == 1;
  } else if (mapX >= 6.0 && mapX >= 10.0) {
    RangeX == 2;
  }



  //---------------- Print Values of reading plus MAP

  if (statusCode == 200) {
    Serial.println("Value X: " + String(x) + ", " + String(mapX) + ", " + String(RangeX));
    //Servo.write(inclinacionX);

  }
  else {
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode));
  }



  // --------------------------------------- Obtain values for field Y ---------------------------------------------------

  long y = ThingSpeak.readIntField(readChannelNumber, Ydata, readAPIKey);
  // Check the status of the read operation to see if it was successful
  statusCode = ThingSpeak.getLastReadStatus();

  //---------------- Mapping of the Read Field parameter

  float mapY = map(y, -10.0, 4.0, 1.0, 10.0);

  //----------------- Generate range of X

  if (mapY >= 1.0 && mapY <= 5.0) {
    RangeY == 1;
  } else if (mapY >= 6.0 && mapY >= 10.0) {
    RangeY == 2;
  }


  //---------------- Print Values of reading plus MAP

  if (statusCode == 200) {
    Serial.println("Value Y: " + String(y) + ", " + String(mapY) + ", " + String(RangeY));
  }
  else {
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode));
  }

  // --------------------------------------- Obtain values for field Z -----------------------------------------------------

  long z = ThingSpeak.readIntField(readChannelNumber, Zdata, readAPIKey);
  // Check the status of the read operation to see if it was successful
  statusCode = ThingSpeak.getLastReadStatus();

  //---------------- Mapping of the Read Field parameter

  float mapZ = map(z, -4.0, 4.0, 1.0, 10.0);

  //----------------- Generate range of Z

  if (mapZ >= 1.0 && mapZ <= 5.0) {
    RangeZ == 1;
  } else if (mapZ >= 6.0 && mapZ >= 10.0) {
    RangeZ == 2;
  }

  //---------------- Print Values of reading plus MAP

  if (statusCode == 200) {
    Serial.println("Value Z:" + String(z) + ", " + String(mapZ ) + ", " + String(RangeZ));
    //Servo.write(inclingit statuacionZ);
  }
  else {
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode));
  }


  // -------------------------------------- Crating Case Variable -------------------------------------------------------

  if (RangeX == 1 && RangeY == 1 && RangeZ == 1) {
    var == 1;
  } else if (RangeX == 1 && RangeY == 2 && RangeZ == 1) {
    var == 2;
  } else if (RangeX == 2 && RangeY == 2 && RangeZ == 2) {
    var == 3;
  } else if (RangeX == 2 && RangeY == 2 && RangeZ == 1) {
    var == 4;
  } else {
    var == 5;
  }
  delay(3000); // No need to read the temperature too often.


  // ----------------------------------------------- CASES ----------------------------------------------------------------

  switch (var) {

        case 1:
          ClockWise();
          Serial.println("case 1");
          break;
    
        case 2:
          AntiClockWise();
          Serial.println("case 2");
          break;
    
        case 3:
          CompleteTurn();
          Serial.println("case 3");
          break;
    
        case 4:
          Diagonal_1();
          Trans2_3 ();
          Serial.println("case 4");
          break;

        case 5:
          Diagonal_2();
          Trans1_4 ();
          reSet
          Serial.println("case 5");
          break;

    }

  }


//_________________________________________________ VOIDS ______________________________________________________________

void reSet () {
  delay(1000);

  myservo1.write(90);
  myservo2.write(90);
  Serial.println ("Estapa reset");

  delay(1000);
}

// ____________________________________________ ClorckWise ________________________________________
void ClockWise() {

  // Trant to 1
  //  for(pos=90;pos<=180;pos++){
  myservo1.write(180);
  myservo2.write(180);
  Serial.println(pos);
  delay(Time);
  //  }

  // TRANS to 1-2
  for (pos = 180; pos >= 10; pos--) {
    pos2 = 180;
    myservo1.write(pos);
    myservo2.write(pos2);
    Serial.println(pos);
    Serial.println(pos2);
    delay(Time);
  }

  // TRANS to 2- 3

  for (pos2 = 180; pos2 >= 10; pos2--) {
    pos = 10;
    myservo2.write(pos2);
    myservo1.write(pos);

    Serial.println(pos);
    Serial.println(pos2);
    delay(Time);
  }

  // TRANS to 3-4

  for (pos = 10; pos <= 180; pos++) {
    pos2 = 10;
    myservo1.write(pos);
    myservo2.write(pos2);
    Serial.println(pos);
    Serial.println(pos2);
    delay(Time);
  }



  // Trans to 4-1

  for (pos2 = 10; pos2 <= 180; pos2++) {
    myservo1.write(180);
    myservo2.write(pos2);
    Serial.println(pos);
    Serial.println(pos2);
    delay(Time);

  }
}

// ________________________________________ AntiClockWise ________________________________________

void AntiClockWise () {

  //  Trans to 4-3
  pos = 180;
  for (pos = 180; pos >= 10; pos--) {
    myservo1.write(pos);
    myservo2.write(10);
    Serial.println(pos);
    Serial.println(pos2);
    delay(Time);

  }

  //  Trans to 3-2

  for (pos2 = 10; pos2 <= 180; pos2++) {
    myservo1.write(10);
    myservo2.write(pos2);
    Serial.println(pos);
    Serial.println(pos2);
    delay(Time);
  }


  //  Trans to 2-1

  for (pos = 10; pos <= 180; pos++) {
    myservo1.write(pos);
    myservo2.write(180);
    Serial.println(pos);
    Serial.println(pos2);
    delay(Time);
  }

  //  Trans to 1-4

  for (pos2 = 180; pos2 >= 10; pos2--) {
    myservo1.write(180);
    myservo2.write(pos2);
    Serial.println(pos);
    Serial.println(pos2);
    delay(Time);
  }

}


// ______________________________________ CompleteTurn ____________________________________________


void CompleteTurn () {

  //Trant to 1
  for (pos = 90; pos <= 180; pos++) {
    myservo1.write(180);
    myservo2.write(180);
    Serial.println(pos);
    delay(Time);
  }

  // TRANS to 1-2
  for (pos = 180; pos >= 10; pos--) {
    pos2 = 180;
    myservo1.write(pos);
    myservo2.write(pos2);
    Serial.println(pos);
    Serial.println(pos2);
    delay(Time);
  }

  // TRANS to 2- 3

  for (pos2 = 180; pos2 >= 10; pos2--) {
    pos = 10;
    myservo2.write(pos2);
    myservo1.write(pos);

    Serial.println(pos);
    Serial.println(pos2);
    delay(Time);
  }

  // TRANS to 3-4

  for (pos = 10; pos <= 180; pos++) {
    pos2 = 10;
    myservo1.write(pos);
    myservo2.write(pos2);
    Serial.println(pos);
    Serial.println(pos2);
    delay(Time);
  }


  //  Trans to 4-3

  for (pos = 180; pos >= 10; pos--) {
    myservo1.write(pos);
    myservo2.write(10);
    Serial.println(pos);
    Serial.println(pos2);
    delay(Time);
  }


  //  Trans to 3-2

  for (pos2 = 10; pos2 <= 180; pos2++) {
    myservo1.write(10);
    myservo2.write(pos2);
    Serial.println(pos);
    Serial.println(pos2);
    delay(Time);
  }


  //  Trans to 2-1

  for (pos = 10; pos <= 180; pos++) {
    myservo1.write(pos);
    myservo2.write(180);
    Serial.println(pos);
    Serial.println(pos2);
    delay(Time);
  }

  //  Trans to 1-4

  for (pos2 = 180; pos2 >= 10; pos2--) {
    myservo1.write(180);
    myservo2.write(pos2);
    Serial.println(pos);
    Serial.println(pos2);
    delay(Time);
  }

  // Trans to 4-1

  for (pos2 = 10; pos2 <= 180; pos2++) {
    myservo1.write(180);
    myservo2.write(pos2);
    Serial.println(pos);
    Serial.println(pos2);
    delay(Time);

  }

}


// ______________________________________ Diagonals _______________________________________________


void Diagonal_1() {

  for (pos = 10; pos <= 90; pos++) {
    myservo1.write(pos);
    myservo2.write(100 - pos);
    Serial.println(pos);
    Serial.println("tatus 1");
    delay(Time1);

  }

  for (pos = 90; pos >= 10; pos--) {
    myservo1.write(pos);
    myservo2.write(10 + (90 - pos));
    Serial.println(pos);
    Serial.println("tatus 2");
    delay(Time1);

  }
}

void Diagonal_2(){
  
  for (pos = 10; pos <= 90; pos++) {
    myservo1.write(pos);
    myservo2.write(pos);
    Serial.println(pos);
    Serial.println("tatus 1");
    delay(Time1);

  }

  for (pos = 90; pos >= 10; pos--) {
    myservo1.write(pos);
    myservo2.write(pos);
    Serial.println(pos);
    Serial.println("tatus 2");
    delay(Time1);

  }
  
}

// ____________________________________ Transitions _____________________________________________

void Trans1_4 () {

  for (pos = 180; pos >= 10; pos--) {
    myservo1.write(pos);
    myservo2.write(180);
    Serial.println(pos);
    Serial.println("tatus 1");
    delay(Time1);
 }

  for (pos = 10; pos <= 180; pos++) {
    myservo1.write(pos);
    myservo2.write(180);
    Serial.println(pos);
    Serial.println("tatus 2");
    delay(Time1);
 }

}

void Trans2_3 () {

  for (pos = 180; pos >= 10; pos--) {
    myservo1.write(pos);
    myservo2.write(10);
    Serial.println(pos);
    Serial.println("tatus 3");
    delay(Time1);
 }

  for (pos = 10; pos <= 180; pos++) {
    myservo1.write(pos);
    myservo2.write(10);
    Serial.println(pos);
    Serial.println("tatus 4");
    delay(Time1);
 }

}
