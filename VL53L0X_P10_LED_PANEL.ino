/*
 * Dr.Tronik. YouTube KASIM 2021 
 * https://youtu.be/zcWIq5iGcFs
 * P10 16*32 LEd Panel Gösterge için
 * VL53L0X kütüphanesinin düenlenmesi
 */

//Kütüphane ve diğer genel tanımlamalar:

#include <SPI.h>      //SPI kütüphanesi ekleme
#include<DMD.h>       //DMD kütüphanesi ekleme
#include<TimerOne.h> //TimerOne kütüphanesi ekleme
#include"SystemFont5x7.h" //Panele yazdıracağımız font ekleme

#include <Wire.h>
#include <VL53L0X.h>
VL53L0X sensor;

#define DISPLAY_ACROSS 1 // Yatayda 1 panel
#define DISPLAY_DOWN 1 //Dikeyde 1 panel
DMD dmd(DISPLAY_ACROSS, DISPLAY_DOWN); // Yani tek panel...

void ScanDMD() // DMD kütüphanesi ile birlikte gelen ve Timer1 kesmesine attac edilen fonksiyon...
{
  dmd.scanDisplayBySPI();
}
//___SET UP___
void setup()
{
  Timer1.initialize(5000); //3000 - 5000 arasında ideal, bu değerlerin dışında özellikle çoklu panellerde titreşim olabiliyor...
  Timer1.attachInterrupt(ScanDMD); // Timer1 kesmesine ScanDMD fonksiyonunu attach etme...
  dmd.clearScreen(true); // Paneli bir temizleyelim...
  
  
  Serial.begin(9600);
  Wire.begin();

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
  sensor.startContinuous();
}
//___VOID LOOP___
void loop()
{
  Serial.print(sensor.readRangeContinuousMillimeters());
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();

  //___DMD KODLARI___
  dmd.clearScreen(true);
  dmd.drawString (10,8,"Mm.", 3 ,GRAPHICS_NORMAL);
  dmd.selectFont(System5x7);
  char buffer[10];
  dmd.drawString(2, 0, dtostrf(sensor.readRangeContinuousMillimeters(), 4 ,0, buffer), 4, GRAPHICS_NORMAL);
  delay(500); //Sensör hızlı, delay vermezsek led panel hep yanar söner...

  //>>> dtostrf(float_değer, min string değeri, noktadan sonra istenen basamak sayısı, çıktının depolanacağı arabellek)
  // Sensörden gelen veri, data to string float komutu ile 4 haneli bir string verisine çevrilerek, char buffer vasıtası ile
  //dmd.drawString fonksiyonu içinde yorumlanıp, istenilen x ve y koordinatlarına yazdırılır...
}

// Dr.TRonik>>> YouTube
