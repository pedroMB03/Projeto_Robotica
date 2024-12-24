#include <SoftwareSerial.h>
SoftwareSerial BTSerial(3, 4); // RX, TX
 
// Frequências das notas (em Hz)
#define C4  261 * 2
#define D4  294 * 2
#define E4  329 * 2
#define F4  349 * 2
#define G4  392 * 2
#define A4  440 * 2
#define B4  493 * 2
#define C5  523 * 2
 
int buzzerPin = 5;  // Pino do buzzer
int motorPinPWM = 9; // Pino para controle de potência do motor (PWM)
int motorPin1 = 2;   // Pino IN1 do Motor (direção fixa, sempre ligado)
 
 
// Pinos dos LEDs correspondentes às notas
int ledPins[] = {6, 7, 8, 13, 10, 11, 12}; // LEDs de C4 a C5
 
// Potências associadas às notas (de C4 a C5)
int powerMap[] = {75, 110, 150, 175, 200, 225, 255};  // Mapeamento de potência (0-255)
 
void setup() {
  BTSerial.begin(9600); // Inicializa o Bluetooth
  pinMode(buzzerPin, OUTPUT); // Define o pino do buzzer como saída
  pinMode(motorPin1, OUTPUT); // Define o pino de direção do motor como saída (sempre ligado)
  pinMode(motorPinPWM, OUTPUT); // Pino PWM para controle de potência do motor
 
  Serial.begin(9600); // Inicializa a comunicação serial para depuração
 
  // Inicializa os LEDs
  for (int i = 0; i < 7; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}
 
void loop() {
  if (BTSerial.available()) {
    char command = BTSerial.read(); 
    switch (command) {
      case ' ':
        delay(500);
        break;
      case 'C':
        digitalWrite(ledPins[0], HIGH); 
        playTone(C4);
        digitalWrite(ledPins[0], LOW);
        motorControl(0);
        break;
      case 'D':
        digitalWrite(ledPins[1], HIGH); 
        playTone(D4);
        digitalWrite(ledPins[1], LOW);
        motorControl(1); 
        break;
      case 'E':
        digitalWrite(ledPins[2], HIGH); 
        playTone(E4);
        digitalWrite(ledPins[2], LOW);
        motorControl(2); 
        break;
      case 'F':
        digitalWrite(ledPins[3], HIGH); 
        playTone(F4);
        digitalWrite(ledPins[3], LOW);
        motorControl(3); 
        break;
      case 'G':
        digitalWrite(ledPins[4], HIGH); 
        playTone(G4);
        digitalWrite(ledPins[4], LOW);
        motorControl(4); 
        break;
      case 'A':
        digitalWrite(ledPins[5], HIGH);
        playTone(A4);
        digitalWrite(ledPins[5], LOW);
        motorControl(5);
        break;
      case 'B':
        digitalWrite(ledPins[6], HIGH); 
        playTone(B4);
        digitalWrite(ledPins[6], LOW);
        motorControl(6);
        break;
      case 'c':
        digitalWrite(ledPins[0], HIGH); 
        playTone(C5);
        digitalWrite(ledPins[0], LOW);
        motorControl(7);
        break;
      case '0': // Para parar o som e o motor
        noTone(buzzerPin);
        break;
      default:
        break;
    }
  }
}
 
// Função para controlar o motor com potência variável
void motorControl(int noteIndex) {
  // inicia recebendo a potencia da nota
  int potencia = powerMap[noteIndex];
  analogWrite(motorPinPWM, potencia);
  delay(200); 
  analogWrite(motorPinPWM, 0); 
}
 
// Função para tocar a nota
void playTone(int frequency) {
  tone(buzzerPin, frequency); // Toca a frequência especificada
  delay(500); // Duração da nota
  noTone(buzzerPin); // Para o som
}