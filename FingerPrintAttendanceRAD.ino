 /*
 * This is the Arduino code for 4 keys Keypad.
 * watch the video for details and demo https://youtu.be/BiOh_Z2N7kk
 *  * 
 * Written by Ahmad Nejrabi for Robojax Video channel www.Robojax.com
 * Date: Dec 28, 2017, in Ajax, Ontario, Canada
 * Permission granted to share this code given that this
 * note is kept with the code.
 * Disclaimer: this code is "AS IS" and for educational purpose only.
 * this code has been downloaded from http://robojax.com/learn/arduino/
// Recorded Dec 28, 2017 for Robojax.com*/

#define key1 14 //connect wire 1 to pin 2
#define key2 15 //connect wire 2 to pin 3
#define key3 16 //connect wire 3 to pin 4
#define key4 17 //connect wire 4 to pin 5


#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
LiquidCrystal_I2C lcd(0x27,18,4); //LiquidCrystal_I2C lcd(0x27,20,4); 
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);  
uint8_t id;

void setup() {
 Serial.begin(9600);
 pinMode(key1, INPUT_PULLUP);// set pin as input
 pinMode(key2, INPUT_PULLUP);// set pin as input
 pinMode(key3, INPUT_PULLUP);// set pin as input
 pinMode(key4, INPUT_PULLUP);// set pin as input   

 Serial.println("Finger Print Test");
 lcd.init();  // initialize the lcd 
 lcd.init();
 // Print a message to the LCD.
 lcd.backlight();
 lcd.clear();
 lcd.setCursor(1,0);
 lcd.print("Attendents System");
 lcd.setCursor(8,1);
 lcd.print("DCS");
 lcd.setCursor(1,2);
 lcd.print("Faculty of Science");
 lcd.setCursor(8,3);
 lcd.print("UOJ");
 delay(5000);
finger.begin(57600);
 if (finger.verifyPassword()) {
  Serial.println("Found fingerprint sensor!");
 }
 else {
  Serial.println("Did not find fingerprint sensor :(");
  while (1) { delay(1); }
  
 }
      finger.getTemplateCount();
      Serial.print("Sensor contains "); 
      Serial.print(finger.templateCount); 
      Serial.println(" templates");
      Serial.println("Waiting for valid finger...");


      
lcd.clear();
 lcd.setCursor(1,0);
 lcd.print("Green to enroll");
  lcd.setCursor(1,1);
  lcd.print("yellow to match");
   lcd.setCursor(1,2);
 lcd.print("Yellw to delete");
   lcd.setCursor(1,3);
  lcd.print("red to nothing");

 
}
uint8_t readnumber(void) {
  uint8_t num = 0;
  
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

void loop() {
  boolean yes=true;
  int key1S = digitalRead(key1);// read if key1 is pressed
  int key2S = digitalRead(key2);// read if key1 is pressed
  int key3S = digitalRead(key3);// read if key1 is pressed
  int key4S = digitalRead(key4);// read if key1 is pressed 
 // Code written for Robojax.com video Tutorial
     if(!key1S){
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Ready to Enroll!");
      lcd.setCursor(1,1);
      lcd.print("Assign ID 1-127");
      Serial.println("key 1 is pressed");
      Serial.println("Ready to enroll a fingerprint!");
      Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
      id = readnumber();
      if (id == 0) {// ID #0 not allowed, try again!
        return;
      }
      lcd.clear();
      Serial.print("Enrolling ID #");
      lcd.setCursor(1,1);
      lcd.print("Enrolling ID #"+id);
      Serial.println(id);
      
      while (!  getFingerprintEnroll() );

delay(1000);
lcd.clear();
 lcd.setCursor(1,0);
 lcd.print("Green to enroll");
  lcd.setCursor(1,1);
  lcd.print("yellow to match");
   lcd.setCursor(1,2);
 lcd.print("Yellw to delete");
   lcd.setCursor(1,3);
  lcd.print("red to nothing");

      
     }
     if(!key2S){
      int iii=0;
      Serial.println("key 2 is pressed");
      while(iii<50){
        getFingerprintIDez();
        delay(5);  //don't ned to run this at full speed. 
        iii++;      
      }

      lcd.clear();
 lcd.setCursor(1,0);
 lcd.print("Green to enroll");
  lcd.setCursor(1,1);
  lcd.print("yellow to match");
   lcd.setCursor(1,2);
 lcd.print("Yellw to delete");
   lcd.setCursor(1,3);
  lcd.print("red to nothing");
      
     }


     
     if(!key3S){
      Serial.println("key 3 is pressed");

      Serial.println("Please type in the ID # (from 1 to 127) you want to delete...");
      uint8_t id = readnumber();
      if (id == 0) {// ID #0 not allowed, try again!
        return;
      }

      Serial.print("Deleting ID #");
      Serial.println(id);
  
      deleteFingerprint(id);
      lcd.clear();
 lcd.setCursor(1,0);
 lcd.print("Green to enroll");
  lcd.setCursor(1,1);
  lcd.print("yellow to match");
   lcd.setCursor(1,2);
 lcd.print("Yellw to delete");
   lcd.setCursor(1,3);
  lcd.print("red to nothing");
      
     }
     if(!key4S){
      Serial.println("key 4 is pressed");

      lcd.clear();
 lcd.setCursor(1,0);
 lcd.print("Green to enroll");
  lcd.setCursor(1,1);
  lcd.print("yellow to match");
   lcd.setCursor(1,2);
 lcd.print("Yellw to delete");
   lcd.setCursor(1,3);
  lcd.print("red to nothing");
     }          
     delay(100);
}

uint8_t getFingerprintEnroll() {

  int p = -1;

lcd.clear();
      lcd.setCursor(1,1);
      lcd.print("Waiting for valid");
      lcd.setCursor(1,2);
    lcd.print("finger as #"+id);

  
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");

lcd.clear();
      lcd.setCursor(1,1);
      lcd.print("Image taken");
      
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  Serial.println("Remove finger");

lcd.clear();
      lcd.setCursor(1,1);
      lcd.print("Remove finger");
  
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");

lcd.clear();
      lcd.setCursor(1,1);
      lcd.print("Place same finger again");
      lcd.setCursor(1,2);
      lcd.print("again");
  
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");

lcd.clear();
      lcd.setCursor(1,1);
      lcd.print("Image taken");


      
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");

lcd.clear();
      lcd.setCursor(1,1);
      lcd.print("Prints matched!");
    
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  Serial.print("ID "); Serial.println(id);

lcd.clear();
      lcd.setCursor(1,1);
      lcd.print("ID "+id);
  
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");

    
lcd.clear();
      lcd.setCursor(1,2);
      lcd.print("Stored!");
      delay(2000);


    
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
}

///////////////////////////// Match
uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); 
  Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 

  lcd.clear();
      lcd.setCursor(1,1);
      lcd.print("ID # "+finger.fingerID);
      lcd.setCursor(1,2);
      lcd.print("Attended");
      delay(1000);

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); 
  Serial.print(finger.fingerID); 

  Serial.print(" with confidence of "); Serial.println(finger.confidence);

 lcd.clear();
      lcd.setCursor(1,1);
      lcd.print("ID # ");
      lcd.setCursor(1,2);
      lcd.print(finger.fingerID);
      lcd.setCursor(1,3);
      lcd.print("Attended");
      delay(1000);
      lcd.clear();

  
  return finger.fingerID; 
}
//////////////////////////////////////////////////////Delete
uint8_t deleteFingerprint(uint8_t id) {
  uint8_t p = -1;
  
  p = finger.deleteModel(id);

  if (p == FINGERPRINT_OK) {
    Serial.println("Deleted!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not delete in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
    return p;
  }   
}
