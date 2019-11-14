// Powered by Mice_Eff https://youtu.be/7z2vXxELKN0                   
            #include <SPI.h> 
            #include <ESP8266WiFi.h> // https://github.com/blynkkk/blynk-library/releases/tag/v0.6.1
            #include <BlynkSimpleEsp8266.h>
            #include <SimpleTimer.h>    
            #include <NewPing.h> // https://github.com/e-Gizmo/NewPing
#define BLYNK_PRINT Serial           
#define PIN_TRIG 14// пин триг дальномера
#define PIN_ECHO 12// пин эхо дальномера
#define MAX_DISTANCE 200// макс расстояние измеряемое дальномером
char auth[] = "токен";// название токена
char ssid[] = "сеть";  //название wi-fi
char pass[] = "пароль";  //пароль от wi-fi
  int lo = 72; // длина до дна мусорки
  int lm = 40; // длина до края мусорки ( в видео я затупил и сказал херню, ничего отнимать не надо);
  NewPing sonar(PIN_TRIG, PIN_ECHO, MAX_DISTANCE);
  SimpleTimer timer;



void setup(){
  Serial.begin(9600); 
  Blynk.begin(auth, ssid, pass);
  pinMode(PIN_TRIG, OUTPUT); 
  pinMode(PIN_ECHO, INPUT);
}


void loop(){
  
  Blynk.run(); 
  timer.run(); 
     unsigned int y = sonar.ping_cm();
     Blynk.virtualWrite(V7, y); // выводим расстояние на 7 виртуальный пин на виртуальный дисплей
     int b =(lo-y)*100/(lo-lm);
     if ( b>-1 && b<101  ){
     Blynk.virtualWrite(V8, b); // выводим проценты на 8 виртуальный пин на виртуальный дисплей
     if ( b>=95 ){
     Blynk.notify("Вынеси мусор"); // текст уведомления
      }
     }
     if(y>lo){
       Blynk.virtualWrite(V8, 0);
     }
       if(b>101){
       Blynk.virtualWrite(V8, 100);
     }
     
}
    

