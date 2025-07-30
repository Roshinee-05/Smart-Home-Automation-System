#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo clothesServo;

// 🖥 Sensor & Actuator Pins
#define TRIG_ENTRY 4
#define ECHO_ENTRY 5
#define TRIG_EXIT 2
#define ECHO_EXIT 3
#define RAIN_SENSOR A0
#define FLAME_SENSOR 7
#define GAS_SENSOR A1
#define CLOTHES_SERVO 11
#define RELAY_LIGHT 8
#define BUZZER 10

// 🛠 Variables
int peopleCount = 0;
bool flameAlertTriggered = false;
bool gasAlertTriggered = false;
bool rainAlertTriggered = false;
const int GAS_BASELINE_SAMPLES = 50;
int gasBaseline = 0;
int gasThreshold = 0;
unsigned long lastGasAlert = 0;

void setup() {
Wire.begin();
lcd.init();
lcd.backlight();
delay(1000);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("System Starting...");
delay(2000);
lcd.clear();

pinMode(TRIG_ENTRY, OUTPUT);  
pinMode(ECHO_ENTRY, INPUT);  
pinMode(TRIG_EXIT, OUTPUT);  
pinMode(ECHO_EXIT, INPUT);  
pinMode(RAIN_SENSOR, INPUT);  
pinMode(FLAME_SENSOR, INPUT);  
pinMode(GAS_SENSOR, INPUT);  
pinMode(RELAY_LIGHT, OUTPUT);  
pinMode(BUZZER, OUTPUT);  

digitalWrite(RELAY_LIGHT, LOW);  
digitalWrite(BUZZER, LOW);  

clothesServo.attach(CLOTHES_SERVO);  
clothesServo.write(0);  

calibrateGasSensor();

}

void loop() {
int entryDist = getDistance(TRIG_ENTRY, ECHO_ENTRY);
int exitDist = getDistance(TRIG_EXIT, ECHO_EXIT);

// 🚪 **Entry Detection**  
if (entryDist < 5) {    
    delay(500);    
    if (getDistance(TRIG_ENTRY, ECHO_ENTRY) < 5) {    
        peopleCount++;  
        showMessage("Welcome!", 1500);  
    }  
}  

// 🚪 **Exit Detection**  
if (exitDist < 5 && peopleCount > 0) {    
    delay(500);  
    if (getDistance(TRIG_EXIT, ECHO_EXIT) < 5) {    
        peopleCount--;  
        showMessage("Thank You!", 1500);  
    }  
}  

// ✅ **Update LCD Properly**  
updateLCD();  

// ✅ **Control Lights**  
digitalWrite(RELAY_LIGHT, peopleCount > 0 ? HIGH : LOW);  

// 🚨 **Rain Alert**  
int rainValue = analogRead(RAIN_SENSOR);  
if (rainValue < 500 && !rainAlertTriggered) {    
    rainAlertTriggered = true;  
    clothesServo.write(90);  
    showMessage("Rain Detected!", 1000);  
    rainAlarm();  
} else if (rainValue >= 500) {  
    rainAlertTriggered = false;  
    clothesServo.write(0);  
}  

// 🔥 **Flame Alert**  
int flameDetected = digitalRead(FLAME_SENSOR);  
if (flameDetected == 0 && !flameAlertTriggered) {    
    flameAlertTriggered = true;  
    showMessage("FLAME ALERT!", 2000);  
    fireAlarm();  
} else if (flameDetected == 1) {  
    flameAlertTriggered = false;  
}  

// 🚨 **Gas Alert**  
int gasValue = getFilteredGasValue();  
if (gasValue > gasThreshold && !gasAlertTriggered && millis() - lastGasAlert > 10000) {    
    gasAlertTriggered = true;  
    lastGasAlert = millis();  
    showMessage("GAS LEAKAGE!", 3000);  
    gasAlarm();  
} else if (gasValue <= gasThreshold) {  
    gasAlertTriggered = false;  
}

}

// 🔄 LCD Update Function
void updateLCD() {
lcd.clear();
delay(10);
lcd.backlight();
lcd.setCursor(0, 0);
lcd.print("People: ");
lcd.print(peopleCount);
delay(1000);
}

// 🚨 Function to Show Messages
void showMessage(String message, int duration) {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print(message);
delay(duration);
}

// 📏 Distance Calculation
int getDistance(int trigPin, int echoPin) {
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
int duration = pulseIn(echoPin, HIGH);
return duration * 0.034 / 2;
}

// 🔄 Gas Sensor Calibration
void calibrateGasSensor() {
int sum = 0;
lcd.setCursor(0, 0);
lcd.print("Calibrating Gas...");
for (int i = 0; i < GAS_BASELINE_SAMPLES; i++) {
sum += analogRead(GAS_SENSOR);
delay(100);
}
gasBaseline = sum / GAS_BASELINE_SAMPLES;
gasThreshold = gasBaseline + 50;
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Gas Ready");
delay(2000);
}

// 🔄 Gas Sensor Filtering
int getFilteredGasValue() {
static int readings[10] = {0};
static int index = 0;
int sum = 0;

readings[index] = analogRead(GAS_SENSOR);  
index = (index + 1) % 10;  
  
for (int i = 0; i < 10; i++) {  
    sum += readings[i];  
}  
return sum / 10;

}

// 🔔 Fire Alarm Function (Fast Beeping)
void fireAlarm() {
for (int i = 0; i < 5; i++) {
tone(BUZZER, 2000);
delay(200);
noTone(BUZZER);
delay(200);
}
}

// 🚨 Gas Alarm Function (Medium Beep)
void gasAlarm() {
tone(BUZZER, 1500);
delay(1000);
noTone(BUZZER);
}

// 🌧 Rain Alarm Function (Rising & Falling Tone)
void rainAlarm() {
for (int freq = 500; freq < 2000; freq += 100) {
tone(BUZZER, freq);
delay(50);
}
for (int freq = 2000; freq > 500; freq -= 100) {
tone(BUZZER, freq);
delay(50);
}
noTone(BUZZER);
}
This is my smart home automation system that I made for samgatha x vashisht 2025 for Embedquest by IIITDM, kancheepuram and won first price. Give me read me file for this project repository

