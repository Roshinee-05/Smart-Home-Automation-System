# Smart Home Automation System – **EmbedQuest Winner (Samgatha x Vashisht 2025)**

**First Prize Winner** – *EmbedQuest 2025*, hosted by **IIITDM Kancheepuram** during **Samgatha x Vashisht 2025**.

This Smart Home Automation System is a fully integrated embedded solution built using **Arduino**, focusing on safety, automation, and convenience. It combines **occupancy-based control**, **environmental hazard alerts**, and **automated rain protection** using sensor-actuator fusion.

---

## Features

### Occupancy-Based Control
- Entry/exit detection using two **ultrasonic sensors**
- Automatic room light control based on people count
- LCD greetings like **"Welcome!"** and **"Thank You!"**

### Rain Detection and Clothes Protection
- **Rain sensor** detects showers
- Servo motor pulls clothes indoors automatically
- Rising/falling buzzer tone alerts users

### Fire Detection System
- **Flame sensor** detects fire presence
- Fast pulsing buzzer alert
- LCD displays **"FLAME ALERT!"**

### Gas Leakage Detection
- MQ-based gas sensor with **adaptive threshold calibration**
- Medium-tone buzzer alert
- LCD displays **"GAS LEAKAGE!"**

### Live Display and Interaction
- **I2C LCD (16x2)** shows:
  - Occupancy count
  - Alert messages
  - Calibration progress
- All messages and counts update in real time

---

## Hardware Components

| Component              | Quantity |
|------------------------|----------|
| Arduino Uno            | 1        |
| Ultrasonic Sensors     | 2        |
| MQ Gas Sensor (A1)     | 1        |
| Flame Sensor (D7)      | 1        |
| Rain Sensor (A0)       | 1        |
| I2C LCD Display (16x2) | 1        |
| Servo Motor (Clothes)  | 1        |
| Relay Module (Light)   | 1        |
| Buzzer                 | 1        |
| Wires, Resistors, etc. | -        |

---

## How It Works

1. **System Initialization**
   - LCD shows startup message
   - Gas sensor calibrates and sets a dynamic threshold

2. **Occupancy Logic**
   - Distance-based entry/exit updates people count
   - Light controlled via relay based on count

3. **Environmental Sensing**
   - Rain triggers servo to retract clothes + rising/falling buzzer tone
   - Flame triggers high-priority alarm
   - Gas sensor uses moving average filtering to detect spikes

4. **Alerts**
   - LCD messages & distinct buzzer patterns differentiate each alert:
     - **Rain**: Rising/falling tone
     - **Gas**: Medium tone
     - **Fire**: Fast beeping

---
