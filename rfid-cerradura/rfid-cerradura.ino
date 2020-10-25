#define BLANCO 0XFFFF
#define NEGRO 0
#define ROJO 0xF800
#define VERDE 0x07E0
#define AZUL 0x001F
#include <SPI.h>
#include <MFRC522.h>
#include <M5Stack.h>
#define RST_PIN 2 //Pin 9 para el reset del RC522 no es necesario conctarlo
#define SS_PIN 21 //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); ///Creamos el objeto para el RC522
MFRC522::StatusCode status; //variable to get card status

const uint8_t cerradura = 25;

void setup() {

  M5.begin();
  Serial.begin(9600);
  SPI.begin(); //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos el MFRC522 - Cuando pone PCD se refiere al modulo lector
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(90, 10);
  M5.Lcd.setTextColor(BLANCO);
  M5.Lcd.println("BIENVENIDO");
  
  pinMode(cerradura, OUTPUT);
  digitalWrite(cerradura, LOW);
}

byte ActualUID[7]; //almacenará el código del Tag leído
byte cliente1[4]= {0x8E, 0xEC, 0x5F, 0xD3} ; //código del CLIENTE 1
byte cliente2[4]= {0x71, 0x34, 0x0D, 0x08} ; //código del CLIENTE 2
byte cliente3[7]= {0x04, 0x4D, 0x49, 0x22, 0xEE, 0x64, 0x80} ; //código del CLIENTE 3

void loop() {
  if ( mfrc522.PICC_IsNewCardPresent())
  {
    //Seleccionamos una tarjeta
    if ( mfrc522.PICC_ReadCardSerial())
    {
      
      M5.Lcd.setTextSize(2);
      M5.Lcd.setCursor(0, 30);
      M5.Lcd.fillScreen(NEGRO); // Pone la pantalla toda en negro (Limpia la pantalla)
      M5.Lcd.setTextColor(AZUL);
      M5.Lcd.print(F("CLIENTE:"));

      // Enviamos serialemente su UID
      // lo podemos descomentar para saber el ID de la tarjeta RFID
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        //M5.Lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        //M5.Lcd.print(mfrc522.uid.uidByte[i], HEX);
        ActualUID[i]=mfrc522.uid.uidByte[i];
      }

      // Comprobamos si el UID de la tarjeta insertada es el cliente 1
      if(compareArray(ActualUID,cliente1,4)) // El cuatro lo ponemos para que se sepa las casillas que tiene el array de esa llave.
      {
        // Ponemos el color en verde
        M5.Lcd.setTextColor(VERDE);
        // Y escribimos
        M5.Lcd.print("Alfonso");
        si();
        // Encendemos la cerradura (Abrimos)
        digitalWrite(cerradura, HIGH);
        
        // Comprobamos si el UID de la tarjeta insertada es el cliente 2
      }else if(compareArray(ActualUID,cliente2,4))
      {
        M5.Lcd.setTextColor(VERDE);
        M5.Lcd.print("Pedro");
        si();
        digitalWrite(cerradura, HIGH);

        // Comprobamos si el UID de la tarjeta insertada es el cliente 3
      }else if(compareArray(ActualUID,cliente3,7))
      {
        M5.Lcd.setTextColor(VERDE);
        M5.Lcd.print("Pepito");
        si();
        digitalWrite(cerradura, HIGH);
      }else
      {
        M5.Lcd.setTextColor(ROJO);
        M5.Lcd.println("NO REGISTRADO");
        no();
      }
      
      // Terminamos la lectura de la tarjeta tarjeta actual
      mfrc522.PICC_HaltA();
      M5.Lcd.setCursor(50, 150);
      M5.Lcd.setTextColor(BLANCO);
      M5.Lcd.println("SIGUIENTE CLIENTE");
      delay(1000);
      digitalWrite(cerradura, LOW);
    } 
  }
}


//Función para comparar dos vectores
// Compara si la tarjeta introducida es la misma que la que le pasamos
boolean compareArray(byte array1[],byte array2[], int n_byte)
{
  for (int i=0; i<n_byte; i++)
  {
    if(array1[i] != array2[i])return(false);
  }
  
  return(true);
}

// Escribe SI en medio de la pantalla
void si ()
{
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(20, 90);
  M5.Lcd.setTextColor(VERDE);
  M5.Lcd.println("TAQUILLA ABIERTA");
  M5.Lcd.setTextSize(2);
}

// Escribe NO en medio de la pantalla
void no ()
{
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(10, 90);
  M5.Lcd.setTextColor(ROJO);
  M5.Lcd.println("INTENTAR OTRA VEZ");
  M5.Lcd.setTextSize(2);
}
