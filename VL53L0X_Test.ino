/*
   Dr.Tronik. YouTube MART 2022
   https:https://youtu.be/RlMtYuKVOT4
   İki adet VL53L0X Sensör kullanımı,
   Örnek üzerinden sensör sayısı çoğaltılabilir
*/

/********************************************************************
  GLOBALS___GLOBALS___GLOBALS___GLOBALS___GLOBALS___GLOBALS___
 ********************************************************************/
//Kütüphane ve diğer genel tanımlamalar:

#include <Wire.h> //I²C protokol için
#include <VL53L0X.h> // Sensör kütüphanesi

VL53L0X sensor1; //sensor1
VL53L0X sensor2; //sensor2 nesneleri oluşturuldu

/********************************************************************
  SETUP___SETUP___SETUP___SETUP___SETUP___SETUP___SETUP___SETUP___
 ********************************************************************/
void setup()
{
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(4, LOW); // sensor1 xshut LOW a çekilerek kapatıldı...
  digitalWrite(5, LOW); // sensor2 xshut LOW a çekilerek kapatıldı...

  delay(500);
  Wire.begin(); //SENSÖRLER KAPATILDIKTAN SONRA iletişim başlatıldı...

  Serial.begin(9600);

  digitalWrite(4, HIGH);            //İlk sensörümüz açıldı/pasifte
  delay(100);
  sensor1.setAddress((uint8_t)00);  //Adresi değiştirildi
  Serial.println("00");             //Değiştirilen adres bilgisi seri porta yazdırıldı
  sensor1.init(true);               //Sensör çalışmaya başladı/aktif


  digitalWrite(5, HIGH);
  delay(100);
  sensor2.setAddress((uint8_t)01);
  Serial.println("01");
  sensor2.init(true);


  Serial.println("Adresler ayarlandı");

  sensor1.startContinuous(); //Sensör1 devamlı mod çalışmasına alındı
  sensor2.startContinuous(); //Sensör2 devamlı mod çalışmasına alındı
}
/********************************************************************
  LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__
 ********************************************************************/
void loop()
{
  Serial.print("1.Sensör:");
  Serial.print(sensor1.readRangeContinuousMillimeters());


  Serial.print("--------");


  Serial.print("2.Sensör:");
  Serial.print(sensor2.readRangeContinuousMillimeters());


  Serial.println();
  delay(500);
}

// Dr.TRonik>>> YouTube
