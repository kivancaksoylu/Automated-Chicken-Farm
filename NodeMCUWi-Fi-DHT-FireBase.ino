#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "arduino-afb8e.firebaseio.com" //Buraya tam Link koyma 
#define FIREBASE_AUTH "Rs1oLkt5fsfBfUKUJA7ZwsOdqcsCBhdn7fN1dlQc"
#define WIFI_SSID "internet"
#define WIFI_PASSWORD "YN3KH7LYWNEX"
SoftwareSerial ESPA(D2,D3); //Alıcı
SoftwareSerial ESPAS(D0,D1); //Gönderici



void setup(){
  Serial.begin(9600);
   ESPA.begin(4800);
   ESPAS.begin(4800);
   WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
   Serial.print(WIFI_SSID);
   while(WiFi.status()!= WL_CONNECTED)
   {
    Serial.print(".");
    delay(500);
    }
    Serial.print("IP Address is: ");
    Serial.println(WiFi.localIP());
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    
  pinMode(D2,INPUT);
  pinMode(D3,OUTPUT);
  pinMode(D0,INPUT);
  pinMode(D1,OUTPUT);
  }

  void loop(){

        //Arduino ya gönder  
        String bilgi = Firebase.getString("GidenDegerler");              
        
        ESPAS.print(bilgi);
       
       
        //Arduino dan al
        float val= ESPA.parseFloat();
        Serial.println(val);
        if(val == -4){Firebase.setFloat("Hareket",0);}
        if(val == -5){Firebase.setFloat("Hareket",1);}
        if(val == -6){Firebase.setFloat("Yangin",0);}
        if(val == -7){Firebase.setFloat("Yangin",1);}
        if(val < 100 && val >0){Firebase.setFloat("Sicaklik",val);}
        if(val < 1000 && val >99 ){Firebase.setFloat("Nem",val-100);}
        if(val >999){Firebase.setFloat("Agirlik",val-1000);}
        if(val<-200){Firebase.setFloat("SuSeviyesi",(val+240)*(-1));} //Su seviyesi
 
        //Firebase Fonksiyonları = https://firebase-arduino.readthedocs.io/en/latest/
       }
