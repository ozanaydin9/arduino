int p=0; boolean s=false;
void setup() {
 pinMode(2,OUTPUT);
}

void loop() {

      if(s==false){
           analogWrite(2, p);
           p=p+25;
           delay(1000);
           if(p>200){
              s=true;
            }
      }else{
        p=p-25;
        analogWrite(2, p);
        delay(1000);
        if(p>200){
            s=true;
          }
    }
    
  }


