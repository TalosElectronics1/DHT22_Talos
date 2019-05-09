/*
 * Talos Electronics 
 */
 
// Incluir la libreria del LCD
#include <LiquidCrystal.h>
// Incluir la libreria del DHT
#include "DHT.h"
 
#define DHTPIN 8            // Seleccionamos el pin 8 para los datos de dht
 
// LCD Conecciones (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
 
#define DHTTYPE DHT22       // DHT22 en uso
DHT dht(DHTPIN, DHTTYPE);   // Inicias las libreria del dht
 
char temperature[] = "Temp = 00.0 C";
char humidity[]    = "HD   = 00.0 %";
void setup() {
  // Seleccionas las columnas del lcd
  lcd.begin(16, 2);
  dht.begin();
}
 
void loop() {
  delay(1000);               // Esperar un segundo para leer los datos
  // Read humidity
  int RH = dht.readHumidity() * 10;
  //Leer la termperatura en grados celsius
  int Temp = dht.readTemperature() * 10;
  
  // Compruebe si alguna de las lecturas ha fallado y sale antes (para intentarlo de nuevo)
  if (isnan(RH) || isnan(Temp)) {
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Error");
    return;
  }
 
  if(Temp < 0){
    temperature[6] = '-';
    Temp = abs(Temp);
  }
  else
    temperature[6] = ' ';
  temperature[7]   = (Temp / 100) % 10  + 48;
  temperature[8]   = (Temp / 10)  % 10  + 48;
  temperature[10]  =  Temp % 10 + 48;
  temperature[11]  = 223;        // Simbolo de grados ( °)
  if(RH >= 1000)
    humidity[6]    = '1';
  else
    humidity[6]    = ' ';
  humidity[7]      = (RH / 100) % 10 + 48;
  humidity[8]      = (RH / 10) % 10 + 48;
  humidity[10]     =  RH % 10 + 48;
  lcd.setCursor(0, 0);
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  lcd.print(humidity);
}
