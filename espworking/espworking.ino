#define ag_ismi "Onpeta2"
#define ag_sifresi "nxLk=p.Ajtk"
#define IP "192.168.2.118"
 
void setup()
{
  Serial.begin(9600);
  Serial2.begin(115200); //Seriport'u açıyoruz. Güncellediğimiz 
                        //ESP modülünün baudRate değeri 115200 olduğu için bizde Seriport'u 115200 şeklinde seçiyoruz
  
  Serial2.println("AT"); //ESP modülümüz ile bağlantı kurulup kurulmadığını kontrol ediyoruz.
  Serial.println("AT komutu gonderildi");
  
  delay(5); //ESP ile iletişim için 3 saniye bekliyoruz.
  while (Serial2.available() > 0)
  Serial.write(Serial2.read());
 
  if(Serial2.find("OK")){         //esp modülü ile bağlantıyı kurabilmişsek modül "AT" komutuna "OK" komutu ile geri dönüş yapıyor.
     Serial2.println("AT+CWMODE=1"); //esp modülümüzün WiFi modunu STA şekline getiriyoruz. Bu mod ile modülümüz başka ağlara bağlanabilecek.
     delay(5);
       
     String baglantiKomutu=String("AT+CWJAP=\"")+ag_ismi+"\",\""+ag_sifresi+"\"";
    Serial2.println(baglantiKomutu);
    delay(5);
      
     
 }
}

String runUrl(String link){
  String text="";
  delay(1000);

 Serial2.println(String("AT+CIPSTART=\"TCP\",\"") + IP + "\",8080");  //thingspeak sunucusuna bağlanmak için bu kodu kullanıyoruz. 
                                                                   //AT+CIPSTART komutu ile sunucuya bağlanmak için sunucudan izin istiyoruz. 
                                                                   //TCP burada yapacağımız bağlantı çeşidini gösteriyor. 80 ise bağlanacağımız portu gösteriyor
 delay(5);//beklemesi lazım
 
  if(Serial2.find("Error")){     //sunucuya bağlanamazsak ESP modülü bize "Error" komutu ile dönüyor.
  Serial2.println("AT+CIPSTART Error");
  return "";
  }
  
 String yollanacakkomut = "GET /Project/"+link;   // Burada 64T0OS3R1OEAYUML yazan kısım bizim API Key den aldığımız Key. Siz buraya kendi keyinizi yazacaksınız.
                                                  // ESP modülümüz ile seri iletişim kurarken yazdığımız komutların modüle iletilebilmesi için Enter komutu yani
  delay(5);                                                                                // /r/n komutu kullanmamız gerekiyor.
 
 Serial2.print("AT+CIPSEND=");                    //veri yollayacağımız zaman bu komutu kullanıyoruz. Bu komut ile önce kaç tane karakter yollayacağımızı söylememiz gerekiyor.
 Serial2.println(yollanacakkomut.length()+2);       // +2yollanacakkomut değişkeninin kaç karakterden oluştuğunu .length() ile bulup yazırıyoruz.
 
 delay(5);
 
 if(Serial2.find(">")){                           //eğer sunucu ile iletişim sağlayıp komut uzunluğunu gönderebilmişsek ESP modülü bize ">" işareti ile geri dönüyor.
                                                 // arduino da ">" işaretini gördüğü anda sıcaklık verisini esp modülü ile thingspeak sunucusuna yolluyor.
 Serial2.print(yollanacakkomut);
 Serial2.print("\r\n");
delay(5);

boolean stt=false;
while (Serial2.available()) {
char c = (char)Serial2.read();
if(c=='&'){
  if(stt==true){
    stt=false;
  }else{
    stt=true;
  }
}else{
  if(stt==true){
 text=text+c;
  }
}


delay(5);
}
 }
 else{
 Serial2.println("AT+CIPCLOSE");
 }
delay(5);
Serial.println("data");
Serial.println(text);
return text;
}
 
void loop(){


String temp=runUrl("xindex.txt");
if(temp.equalsIgnoreCase("YOK")){
  
}else{
  
  int sira =0;
  String sure="";
  String hiz="";
  String yon="";

for(int i=0; i<temp.length(); i++) {
     char c = temp.charAt(i);
     if(c==';'){
          sira++;
          c=' ';
     }
  if(sira==0){
     sure= sure+c;
  }
  else if(sira==1){
     hiz=hiz+c;
  } 
  else{
     yon=yon+c;
  }
}
Serial.println(sure);
Serial.println(hiz);
Serial.println(yon);
 //runUrl("silme.jsp");
}






}
