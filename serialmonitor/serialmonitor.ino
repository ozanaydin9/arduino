
String x="";

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(9600);
}

void loop() {

   if(Serial.available()){
    char c=(char) Serial.read();
     if(c!='\n'){
      x=x+c;
     }else{
       if(x=="ozan"){
        
         digitalWrite(2,HIGH);
       }else{
         digitalWrite(2,LOW);
       }
        x="";
     }
   }
 
 


}
