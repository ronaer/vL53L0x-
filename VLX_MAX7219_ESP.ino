/*    ____       __________              _ __  
   / __ \_____/_  __/ __ \____  ____  (_) /__
  / / / / ___/ / / / /_/ / __ \/ __ \/ / //_/
 / /_/ / /  _ / / / _, _/ /_/ / / / / / ,<   
/_____/_/  (_)_/ /_/ |_|\____/_/ /_/_/_/|_|  

 * KASIM 2024, İzmir, MAX7219 & VL530L0X sensör ile "Mesafe Ölçümü"
 * https://youtu.be/s2D4T0fUq5I
 */

/********************************************************************
  GLOBALS___GLOBALS___GLOBALS___GLOBALS___GLOBALS___GLOBALS___
 ********************************************************************/
//Kütüphane ve diğer genel tanımlamalar:
//VL53L0X
#include <Wire.h>
#include <VL53L0X.h>
VL53L0X sensor;

//MAX7219 led matrix ile ilgili kütüphaneler / tanımlar
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
/*MAX7219 Led Matrix Donanım Tipleri:
  1 GENERIC_HW
  2 FC16_HW 
  3 PAROLA_HW
  4 ICSTATION_HW 
*/
#define MAX_DEVICES 4
#define CLK_PIN 14   // D5 or SCK
#define DATA_PIN 13  // D7 or MOSI
#define CS_PIN 12    // D6 or SS

// SPI hardware interface
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

int distance_mm;


/********************************************************************
  SETUP___SETUP___SETUP___SETUP___SETUP___SETUP___SETUP___SETUP___
 ********************************************************************/
void setup() {
  Serial.begin(9600);
  P.begin();
  Wire.begin(2,0);// VLX senxör için: GPIO 2 / D4 / SDA ___ GPIO 0 / D3 / SCL olarak wire kütüphanesi başlatıldı...

  P.print("   ^_^");
  delay(1000);
  P.print("  TEST");                                              //Açılış mesajı
  P.displayText("", PA_CENTER, 0, 0, PA_NO_EFFECT, PA_NO_EFFECT);  //Max7219 gösterim ilk ayarlar...

  sensor.setTimeout(500);
  if (!sensor.init()) {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
}

/********************************************************************
  LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__
 ********************************************************************/
void loop() {
  P.displayAnimate();
  P.setIntensity(15);  //Ekran parlaklığı, 0 min / 15 max
  delay(10);           //!..


  //___SENSOR OKUMA / READ___
  distance_mm = sensor.readRangeContinuousMillimeters();
  Serial.print(distance_mm);
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();

  //___MAX7219 YAZDIRMA / PRINT___
  char buffer[25];
  sprintf(buffer, "%3d%s" , ((distance_mm/10)),"cm.");
  P.print(buffer);
  delay(500);  //Sensör hızlı...  
}

/*___:
bilgi@ronaer.com
https://www.instagram.com/dr.tronik2023/   
YouTube: Dr.TRonik: www.youtube.com/c/DrTRonik
PCBWay: https://www.pcbway.com/project/member/shareproject/?bmbno=A0E12018-0BBC-4C
*/
