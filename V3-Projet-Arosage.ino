
// 10-11-2018
// @c!d€ V3.0


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

// Ecran --> Carte Arduino Uno
// Vcc --> 3v Arduino
// GND --> GND 
// SCK --> pin A5
// SDA --> pin A4

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

  display.setCursor( 15, 0 );
  display.println( "HUMIDITE" );

  display.setCursor( 35, 16 );
  display.println(humid);

  display.setCursor( 4, 32 );
  display.println( "POMPE OFF" );

  display.setCursor( 15, 48 );
  display.println( "== OK ==" );

  display.display();

}


void capteur() {
if (humid>800) // Si >800 
  {
  humid= analogRead(PinHumidite); // Lecture capteur humidité

  display.setTextSize( 2 );
  display.setTextColor( WHITE );
  display.clearDisplay();

  display.setCursor( 15, 0 );
  display.println( "HUMIDITE" );

  display.setCursor( 35, 16 );
  display.println(humid);

  display.setCursor( 4, 32 );
  display.println( "POMPE ON" );

  display.setCursor( 15, 48 );
  display.println( "+ SEC +" );
  display.display();

  // Commande de la pompe
 digitalWrite(5, HIGH); // Allumage de la pompe
  Serial.println("==== Pompe en marche ====");
  delay(5000); // Temps arrosage 
 digitalWrite(5, LOW); // Arret pompe
  Serial.println("==== Pompe à l'arret ====");
  }

if (humid<200) // Si <200
  {
  humid= analogRead(PinHumidite); // Lecture capteur humidité

  display.setTextSize( 2 );
  display.setTextColor( WHITE );
  display.clearDisplay();

  display.setCursor( 15, 0 );
  display.println( "HUMIDITE" );

  display.setCursor( 35, 16 );
  display.println(humid);

  display.setCursor( 4, 32 );
  display.println( "POMPE OFF" );

  display.setCursor( 5, 48 );
  display.println( "+ HUMIDE +" );
  display.display();
  delay(5000);

  }
delay(600); // Temps entre chaque mesure dans la console si valeur ok
}




