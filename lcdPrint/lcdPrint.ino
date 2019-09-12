#include <LiquidCrystal.h>

String x="";

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  
  lcd.begin(16, 2);
  Serial.begin(9600);
 
}
void loop() {
 
    lcd.setCursor(0,0);
  
    if(Serial.available()){
        char c=(char) Serial.read();
        if(c!='\n'){
           x=x+c;
       }else{
      //Serial.println(x);
       lcd.print(x);   
        
       delay(4000);
         
        
       lcd.clear();       
       x="";
    }
}
}

