////Autores: Anthonny Michael e Luiz Vinicius/////////////
//Sensor de temperatura!/////////////////////////////////

#include <DHT.h> //Biblioteca do sensor de temperatura//
#include <Wire.h> //Biblioteca do sensor LCD I2C//
#include <LiquidCrystal_I2C.h> //Biblioteca do sensor LCD I2C//
#define DHTPIN A1 //Definindo a porta analógica A1 para o sensor DHT11//
#define DHTTYPE DHT11 //Definindo o tipo de sensor DHT//

DHT dht(DHTPIN, DHTTYPE); //Definindo o pino e o tipo de sensor DHT//
LiquidCrystal_I2C lcd(0x27,20,4); //Definindo as variáveis do sensor LCD I2C//

byte grau[8] ={ B00001100,
                B00010010,
                B00010010,
                B00001100,
                B00000000,
                B00000000,
                B00000000,
                B00000000,}; //Armazena a array do símbolo do grau Celsius//
                
byte sorriso[8] ={ 
  B01010,
  B01010,
  B01010,
  B01010,
  B00000,
  B10001,
  B11111,
  B00000,};
                
void setup()
{
  lcd.init(); //Inicializa o display LiquidCrystal_I2C//                     
  lcd.backlight(); //Inicializa a luz do display LiquidCrystal_I2C// 
  dht.begin(); //Inicializa o sensor DHT//
  lcd.createChar(0, grau); //Cria o caractere customizado com o simbolo do grau//
  lcd.createChar(1, sorriso);
  pinMode(2, OUTPUT);
}

void loop()
{
  float h = dht.readHumidity(); //Le o valor da umidade
  float t = dht.readTemperature(); //Le o valor da temperatura
  float f = t * 9 / 5 + 32;
  float k = t * 5 / 5 + 273;
  lcd.setCursor(0,0); //Definindo a linha 0 e coluna 0 das letras no display//
  lcd.print("U:"); //Escreve o nome "umidade" no display//
  lcd.print(h); //Escreve o valor da leitura da umidade do DHT em frente da "umidade"//
  lcd.print("%"); //Escreve após o valor da umidade//
  lcd.setCursor(0,1); //Define a linha 0 da coluna 1 do display//
  lcd.print("C:"); //Escreve o nome Celsius para identificar a temperatura ambiente//
  lcd.print(t); //Escreve o valor da variável da temperatura ambiente após o nome "Celsius"//
  lcd.write((byte)0); //Escreve após o valor da temperatura, a array do símbolo do grau Celsius//
  lcd.setCursor(9,1);
  lcd.print("F:");
  lcd.print(f);
  lcd.setCursor(9,0);
  lcd.print("K:");
  lcd.print(k);
  lcd.setCursor(8,0);
  lcd.write((byte)1);
  lcd.setCursor(8,1);
  lcd.write((byte)1);
  if( t >= 25.00 ){
    digitalWrite(2, HIGH);
  }else{
    digitalWrite(2, LOW);
  }
}
