
// 10-11-2018
// @c!d€ v2.0


// Cablage 

// Capteur --> Carte Arduino Uno
// Vcc --> +5V Arduino
// GND --> GND Arduino
// A0 (sortie analogique) --> pin A0 Arduino
// D0 (sortie digitale) --> pin 3 digitale Arduino

// Ralais --> Carte Arduino Uno
// Vcc --> Vcc Arduino
// GND --> GND Arduino
// COM (sortie digitale) --> pin 5 digitale Arduino

#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display( OLED_RESET );

#if( SSD1306_LCDHEIGHT != 64 )
#error( "Height incorrect, please fix Adafruit_SSD1306.h!" );
#endif


int PinHumidite = 0;
int humid;

void setup() {
Serial.begin(9600);
pinMode(PinHumidite, INPUT); // Capteur humidité
pinMode(5, OUTPUT); // Relais
digitalWrite(5, LOW); // Pompe off

// Initialise la communication I²C à l’adresse 0x3C.
display.begin( SSD1306_SWITCHCAPVCC, 0x3C );
display.clearDisplay();
 }
 
void loop() {

    affiche(); 
    capteur();
}

void affiche() {
humid= analogRead(PinHumidite); // Lecture capteur humidité
Serial.println(humid); // Affichage humidité dans la consolle Arduino

  
  display.setTextSize( 2 );
  display.setTextColor( WHITE );
  display.clearDisplay();

  display.setCursor( 4, 0 );
  display.println( "HUMIDITE" );

  display.setCursor( 35, 16 );
  display.println(humid);

  display.setCursor( 4, 32 );
  display.println( "POMPE OFF" );

  display.setCursor( 35, 40 );
  display.println( "" );

  display.setCursor( 35, 48 );
  display.println( "" );

  display.display();

}


void capteur() {
if (humid>600) // Seuil de déclangement INFO : (dans l'air : 1023, dans l'eau 0)
  {
  humid= analogRead(PinHumidite); // Lecture capteur humidité

  display.setTextSize( 2 );
  display.setTextColor( WHITE );
  display.clearDisplay();

  display.setCursor( 4, 0 );
  display.println( "HUMIDITE" );

  display.setCursor( 35, 16 );
  display.println(humid);

  display.setCursor( 4, 32 );
  display.println( "POMPE ON" );

  display.display();
  
 digitalWrite(5, HIGH); // Allumage de la pompe
  Serial.println("==== Pompe en marche ====");
  delay(5000); // Temps arrosage 
 digitalWrite(5, LOW); // Arret pompe
  Serial.println("==== Pompe à l'arret ====");
  }

Serial.println(" ");
delay(600); // Temps entre chaque mesure 

}