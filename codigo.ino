#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define TRIG_PIN 9
#define ECHO_PIN 10

#define LED_VERDE 3
#define LED_VERMELHO 4
#define BUZZER 5
#define LED_AMARELO 6

void setup() {

  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);


  pinMode(BUZZER, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Sistema de");

  lcd.setCursor(0, 1);
  lcd.print("Monitoramento");

  delay(3000);

  lcd.clear();
}

void loop() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duracao = pulseIn(ECHO_PIN, HIGH);

  float distancia = duracao * 0.034 / 2;

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  lcd.clear();

  if (distancia > 150) {

    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, LOW);

    noTone(BUZZER);

    lcd.setCursor(0, 0);
    lcd.print("Nivel Normal");

    lcd.setCursor(0, 1);
    lcd.print("Dist:");
    lcd.print(distancia);
    lcd.print("cm");
  }

  else if (distancia > 100 && distancia <= 150) {

    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERMELHO, LOW);

    noTone(BUZZER);

    lcd.setCursor(0, 0);
    lcd.print("!!! ATENCAO !!!");

    lcd.setCursor(0, 1);
    lcd.print("Dist:");
    lcd.print(distancia);
    lcd.print("cm");
  }


  else {

    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, HIGH);

    tone(BUZZER, 1000);

    lcd.setCursor(0, 0);
    lcd.print("!!! ALERTA !!!");

    lcd.setCursor(0, 1);
    lcd.print("RISCO ENCHENTE");
  }

  delay(1000);
}
