#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include <SoildSensor.h>


LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

SensorSuelo suelo(1,2,3);
void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("H:");
  Serial.begin(9600);
}

float humedad;
int n,p,k;
void loop()
{
//   lcd.setCursor(0,0);
//   lcd.print("H:");
//   lcd.print(suelo.getHumedad());
//   lcd.print("%");
//   lcd.print("PH:");
//   lcd.print(suelo.getPh());
  humedad=suelo.getHumedad();
  n=suelo.getNitrogeno();
  p=suelo.getFosforo();
  k=suelo.getPotasio();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("H:");
  lcd.print(humedad);
  lcd.setCursor(6,0);
  lcd.print("N:");
  lcd.print(n);
  lcd.setCursor(0,1);
  lcd.print("P:");
  lcd.print(p);
  lcd.setCursor(6,1);
  lcd.print("K:");
  lcd.print(k);
  Serial.println();
  delay(1000);

}
