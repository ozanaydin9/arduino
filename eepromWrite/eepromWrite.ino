
#include <EEPROM.h>
#include <LiquidCrystal.h>



String x="";

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  String r="";
   
    for(int i=0; i<1024; i++){
        char cc=EEPROM.read(i);
        if(cc=='\n'){
          
           lcd.print(r);
           Serial.println(r);
           break;
        }
          
           r=r+cc;
    }  
   
}
void loop() {
 
    if(Serial.available()){
    char c=(char) Serial.read();
        if(c!='\n'){
           x=x+c;
        }else{
           lcd.print(x);  
           x=x+"\n";
           for(int i=0; i<x.length(); i++){
             EEPROM.write(i,x.charAt(i));
           }
           lcd.setCursor(0,0); 
           
           x="";
         
         }
        
    }
}


