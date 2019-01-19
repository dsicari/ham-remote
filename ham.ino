#include <LiquidCrystal.h>

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#define ANT_1   22
#define ANT_2   23
#define ANT_3   24
#define ANT_4   25
#define BTN_1   26
#define BTN_2   27
#define BTN_3   28
#define BTN_4   29
#define LCD_D4  30
#define LCD_D3  31 
#define LCD_D2  32 
#define LCD_D1  33
#define LCD_EN  34
#define LCD_RS  35
#define LED_1   36
#define LED_2   37
#define LED_3   38
#define LED_4   39 
#define BAUDRATE 9600
#define COUNT_SENSOR 10

unsigned long tempo_100ms = 0;
unsigned char statusBotoes;
char sensorCountHigh[5] = {0};
char sensorCountLow[5] = {0};
bool firstTimeInputs = false;

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D3, LCD_D2, LCD_D1);

void cat2usb();
void verifica100ms();
void switchOffAntennas();

void setup() {
  Serial.begin(BAUDRATE);
  Serial1.begin(BAUDRATE);

  //inicia variaveis de contagem de tempo
  tempo_100ms = millis();
  
  pinMode(ANT_1, OUTPUT);
  pinMode(ANT_2, OUTPUT);
  pinMode(ANT_3, OUTPUT);
  pinMode(ANT_4, OUTPUT);
  pinMode(BTN_1, INPUT);
  pinMode(BTN_2, INPUT);
  pinMode(BTN_3, INPUT);
  pinMode(BTN_4, INPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT); 

  lcd.begin(8, 2);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("PU2WAV");
  lcd.setCursor(0, 1);
  lcd.print(" KC1KRX ");  

  switchOffAntennas();

  digitalWrite(LED_4, HIGH);
}

void loop() {
  
  cat2usb();
  
  verifica100ms(); 

}

void cat2usb(){
  //CAT <RS232> ARDUINO <USB> PC
  if (Serial.available()) {
    digitalWrite(LED_1, HIGH);
    Serial1.write(Serial.read());
  }
  if (Serial1.available()) {
    digitalWrite(LED_2, HIGH);
    byte byte_recebido = Serial1.read();    
    Serial.write(byte_recebido);
    if(byte_recebido == ';') Serial.println();
  }
}

void verifica100ms() 
{
  if ((millis() - tempo_100ms) > 100) 
  {
    tempo_100ms = millis();   
    
    if(digitalRead(BTN_1)==LOW){
      switchOffAntennas();  
      digitalWrite(ANT_1, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("ANT1 80m");
      Serial.println("Antena 1: 80m selecionada");
    }
    if(digitalRead(BTN_2)==LOW){
      switchOffAntennas();  
      digitalWrite(ANT_2, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("ANT2 40m");
      Serial.println("Antena 2: 40m selecionada");
    }
    if(digitalRead(BTN_3)==LOW){
      switchOffAntennas();  
      digitalWrite(ANT_3, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("ANT3 10m");
      Serial.println("Antena 3: 10m selecionada");
    }
    if(digitalRead(BTN_4)==LOW){
      switchOffAntennas();  
      digitalWrite(ANT_4, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("ANT4  G5");
      Serial.println("Antena 4: G5RV selecionada");
    }

    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
  }
}

void switchOffAntennas(){
    digitalWrite(ANT_1, LOW);
    digitalWrite(ANT_2, LOW);
    digitalWrite(ANT_3, LOW);
    digitalWrite(ANT_4, LOW);
}



