#include <ESP8266WebServer.h>
#include <Servo.h>
#include <Wire.h> 
#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2);

const char* ssid = "SMART PARK";
const char* password = "12345678";

Servo myservo;
int pos = 0;

#define SP1 13  //s3
#define SP2 16  //d0
#define SP3 0   //d3
#define SP4 2   //d4 

#define SPin 14    //d5
#define SPout 12   //d6

ESP8266WebServer server(80);

void work1(){
      int P1= digitalRead(SP1);
       
      if(P1 ==LOW){
      server.send(200,"text/plain","P1OFF");
      }else if (P1 ==HIGH){
      server.send(200,"text/plain","P1ON "); 
      }
     }
void work2(){ 
    int P2= digitalRead(SP2);

    if(P2 ==LOW){
      server.send(200,"text/plain","P2OFF");
      }else if (P2 ==HIGH){
      server.send(200,"text/plain","P2ON ");
      }
     }
void work3(){
    int P3= digitalRead(SP3); 

    if(P3 ==LOW){
      server.send(200,"text/plain","P3OFF");
      }else if (P3 ==HIGH){
      server.send(200,"text/plain","P3ON ");
      }
     } 
void work4(){
     int P4= digitalRead(SP4);

      if(P4 ==LOW){
      server.send(200,"text/plain","P4OFF");
      }else if (P4 ==HIGH){
      server.send(200,"text/plain","P4ON ");
      }
     }
      
void setup() {
  
Serial.begin(115200);

lcd.begin();
lcd.backlight();
lcd.clear();
lcd.setCursor(2,0);
lcd.print("SMART PARKING");
lcd.setCursor(0,1);
lcd.print("PARK IS:");

WiFi.disconnect();

WiFi.softAP(ssid, password);
WiFi.setOutputPower(20.5);

myservo.attach(15);   //d8

pinMode(SP1,INPUT);   
pinMode(SP2,INPUT); 
pinMode(SP3,INPUT);
pinMode(SP4,INPUT);   

pinMode(SPin,INPUT);
pinMode(SPout,INPUT);
 
server.on("/work1",work1); 
server.on("/work2",work2); 
server.on("/work3",work3);
server.on("/work4",work4);  
   
server.begin();

Serial.println(ssid);
IPAddress myIP = WiFi.softAPIP();
Serial.print("AP IP address: ");
Serial.println(myIP); 
}

void loop() {
server.handleClient();

 if(digitalRead(SP1)==HIGH || digitalRead(SP2)==HIGH || digitalRead(SP3)==HIGH || digitalRead(SP4)==HIGH ){
   lcd.setCursor(8,1);    
   lcd.print("Empty");
  if(digitalRead(SPin)== LOW || digitalRead(SPout)== LOW){
  for (pos = 0; pos <= 135; pos += 1) { 
    myservo.write(pos);              
    delay(15);                       
  }
  delay(3000);
  for (pos = 135; pos >= 0; pos -= 1) { 
    myservo.write(pos);              
    delay(15);                       
  }
   }
  }else if(digitalRead(SP1) ==LOW && digitalRead(SP2) ==LOW && digitalRead(SP3) ==LOW && digitalRead(SP4) ==LOW){
    delay(10);
    lcd.setCursor(8,1);    
    lcd.print("Full ");
   }
}
