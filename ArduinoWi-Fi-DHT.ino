  #include <SoftwareSerial.h>  //NodeMCU ile bağlantı için
  #include <DHT.h>  //Sıcaklık/Nem sensörü
  #include "HX711.h" //Ağırlık sensörü
  #include <Servo.h>


  #define DHTPIN 10  //ısı/nem
  #define DHTTYPE DHT11

  #define DOUT 5  //ağırlık
  #define CLK 4

  #define fan A0
  #define pompa A3

  int hareket = 8; //Hareket sensörü input

  int alev = 6;  //Alev ve buzzer
  #define buzzer A4

  int siteFanKontrolDegeri = 0;
    
  int kontrolDegeri = 0;
  
  int suSeviye = A5; //Su seviyesi sensörü 

  int zamanSayac=0;

  int servoKontrol =0;

  int alarmKontrol=0;

  SoftwareSerial ArduinoUno(3,2);  //Gönderici
  SoftwareSerial ArduinoUnoR(11,12); //Alıcı
  
  DHT dht(DHTPIN,DHTTYPE);
  HX711 scale;

  float calibration_factor = -8460.00; //gram için değer

  Servo sg90; //Servo motor
  
  void setup(){

    
    
    sg90.attach(9); //servoyu 9. ayağa bağla
    
    Serial.begin(9600);
    
    ArduinoUno.begin(4800); //Nodemcu ile konnuşması için 
    ArduinoUnoR.begin(4800);

     pinMode(hareket,INPUT);

     pinMode(alev,INPUT);
     pinMode(buzzer,OUTPUT);
     pinMode(fan,OUTPUT);
     pinMode(pompa,OUTPUT);
    
     dht.begin();

         
     scale.begin(DOUT, CLK);
     scale.set_scale();
     scale.tare();
     scale.set_scale(calibration_factor);

    sg90.write(60);
     
    }

    void loop(){

      //Firebase ten gelenler 
      float val = ArduinoUnoR.parseFloat();
         
      float h = dht.readHumidity(); //nem
      float t = dht.readTemperature();   //sıcaklık
      float w = scale.get_units() * (-10); //Gram için 10 la çarp
      float m;   //hareket
      float f;   //yangin
      float wl =analogRead(suSeviye); // su seviyesi sonrdan bidaha ayar yap

      //Alarm
      if(val == -2)
      {
        digitalWrite(buzzer,HIGH);
        alarmKontrol = 1;
        }
      if(val == -1)
      {
        digitalWrite(buzzer,LOW);
        alarmKontrol = 0;
        }
        

      //Su
      if(wl < 100 || val == -4 )
      {
          digitalWrite(pompa,HIGH);
        }
      if(wl > 250 )
      {
        digitalWrite(pompa,LOW);
        }  
      
      //Ağırlık ve servo kontrol
      if(w < 50 || val == -6 )
      {
          sg90.write(60);
        }
      if(w > 200 )
      {
        sg90.write(0);
        }  

      
      //Sıcaklık kontrol
      if(t>25)
      {
        digitalWrite(fan,HIGH);
        }
      if(t<25 && kontrolDegeri == 0)
      {
        digitalWrite(fan,LOW);
        
        }  
      
      if(val>1000)
      {
        
        val = val -1000;
        Serial.print(val);
        if(val >= t){siteFanKontrolDegeri = 0; kontrolDegeri = 0; ;}
        if(val < t && siteFanKontrolDegeri == 0){
          
        digitalWrite(fan,HIGH);
        kontrolDegeri == 1;
        siteFanKontrolDegeri == 1;
        }
        }

       
      
      if(digitalRead(hareket)==HIGH){m = 5;}  //Hareket kontrolü
      else{m=4;}
      Serial.print('\n');
      if(digitalRead(alev)==LOW && alarmKontrol == 0){f=7; digitalWrite(buzzer,HIGH);}
      if(digitalRead(alev)==HIGH && alarmKontrol == 0){digitalWrite(buzzer,LOW); f=6;}

      if(w<0){w = 0;}
      if(w>999){w=999;}
      if(t>99){t=99;}

      if(wl<240){wl=240;} //Su seviyesi
      if(wl>340){wl=340;}
      
      h=h+100;
      w=w+1000;
      m = m*(-1);
      f = f*(-1);
      wl=wl*(-1);

      zamanSayac++;

     if(zamanSayac==20){
      ArduinoUno.print(t);
      ArduinoUno.println("\n");
      ArduinoUno.print(h);
      ArduinoUno.println("\n");
      ArduinoUno.print(w);
      ArduinoUno.println("\n");
      ArduinoUno.print(m);
      ArduinoUno.println("\n");
      ArduinoUno.print(f);
      ArduinoUno.println("\n");
      ArduinoUno.print(wl);
      ArduinoUno.println("\n");
      zamanSayac = 0;
      }
      
      }
