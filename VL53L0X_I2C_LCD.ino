/*
   Dr.Tronik. YouTube Nisan 2022
   I²C LCD ekran için
   VL53L0X kütüphanesinin düzenlenmesi mm/cm
   Dr.TRonik>>> YouTube

            Hardware Connections:
          ------I²C LCD------                     ------VL53L0X ------
            
            SCL -----  A5                             SCL -----  A5
            SDA -----  A4                             SDA -----  A4
            Vcc  ----- 5 V                            Vcc  ----- 5 V
            Gnd  ----- Gnd                            Gnd  ----- Gnd
            
          -------------------                      -------------------
*/

/********************************************************************
  GLOBALS___GLOBALS___GLOBALS___GLOBALS___GLOBALS___GLOBALS___
 ********************************************************************/
#include <Wire.h> // I²C iletişim için gerekli..
#include <VL53L0X.h> //Sensör kütüphanesi
VL53L0X sensor; //sensor adında bir sensör objesi oluşturuldu...

#include <LiquidCrystal_I2C.h> //I²C li LCD için gerekli...
LiquidCrystal_I2C lcd(0x3F, 16, 2);  //Kullandığımız LCD I²C adres ve karakter satır sayısı tanımlama
float cm;

/********************************************************************
  SETUP___SETUP___SETUP___SETUP___SETUP___SETUP___SETUP___SETUP___
 ********************************************************************/
void setup()
{
  Serial.begin(9600);

  Wire.begin(); //

  lcd.begin();  //LCD başlasın
  lcd.clear();  // ve ekran temizlensin
  lcd.backlight(); //lcd arka plan yansın

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).

  sensor.startContinuous();//Sensör, continious modda başlatıldı...
}

/********************************************************************
  LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__
 ********************************************************************/
void loop()
{
  Serial.print(sensor.readRangeContinuousMillimeters()); //"sensor.readRangeContinuousMillimeters()" değerin atandığı fonksiyon...
  if (sensor.timeoutOccurred()) {
    Serial.print(" TIMEOUT");
  }

  Serial.println();
  cm = sensor.readRangeContinuousMillimeters() / (float) 10;
  //LCD kodları
  lcd.setCursor(0, 0);
  lcd.print("Olculen Mesafe:  ");
  lcd.setCursor(0, 1);
  lcd.print(sensor.readRangeContinuousMillimeters()); 
  lcd.setCursor(4, 1);
  lcd.print("mm");
  lcd.setCursor(8, 1);
  lcd.print(cm,1);
  lcd.setCursor(13, 1);
  lcd.print("cm");
  delay(1000); // Saniyede bir okuma ve lcd ye yazma
  lcd.clear(); // LCD clear edilmezse değerler üst üse binebilir...
}
/********************************************************************
  VOIDs__VOIDs__VOIDs__VOIDs__VOIDs__VOIDs__VOIDs__VOIDs__VOIDs__VOIDs
********************************************************************/
//No extra voids...

// Dr.TRonik>>> YouTube
