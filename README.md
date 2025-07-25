# Heater Control System - Documentation

## Project Overview

Brief description of the system:

> A basic embedded heater control system that monitors temperature using a sensor and activates or deactivates a simulated heater based on defined thresholds.

---

## Part 1: System Design

### 1. Minimum Sensor Requirements

- **Primary Sensor:**\
  `e.g., DHT22 (Digital Temperature and Humidity Sensor)`\
  Justification:

  > Accurate temperature readings are crucial for reliable heater control.

- **Optional Sensors (for future enhancements):**

  - Overheat detection sensor
  - Ambient humidity sensor

---

### 3. System Block Diagram



---

### 4. Future Roadmap

| Feature                       | Description                                        |
| ----------------------------- | -------------------------------------------------- |
| **Overheating Protection**    | Integrate an overheat limit and emergency shutdown |
| **Multiple Heating Profiles** | Support user-defined heating curves or profiles    |
| **LED and Buzzer Alerts**     | Temperature-based LED and Buzzer notifications     |

---

## Part 2: Embedded Implementation

### 1. Platform Details

- **Simulation Platform:** Wokwi
- **Microcontroller:** `Arduino UNO`
- **Language/Framework:** C++ (Arduino)

---

### 2. System States

List of implemented states with description:

| State              | Description                         |
| ------------------ | ----------------------------------- |
| **Idle**           | System initialized, awaiting action |
| **Heating**        | Heater is ON, raising temperature   |
| **Stabilizing**    | Approaching target temperature      |
| **Target Reached** | Desired temperature maintained      |
| **Overheat**       | Emergency state, heater turned OFF  |

---

### 3. Control Logic

- **Temperature Read Interval:** `e.g., Every 1s using timer interrupt`

- **Thresholds:**

  - Target Temp: `e.g., 40°C`
  - Stabilizing Range: `±2°C`
  - Overheat Temp: `e.g., > 50°C`

- **Heater Control Logic:**

  ```cpp
  if (temp < target - 2) {
      // Heating
  } else if (temp >= target - 2 && temp <= target + 2) {
      // Stabilizing
  } else if (temp > target + 2) {
      // Overheat
  }
  ```

---

### 5. Bonus Features

#### BLE Advertising


#### Visual Indicators

- LED colors:
  - Green = Target Reached
  - Red = Heating
  - Yellow = Stabilizing
  - Blinking Red = Overheat


---

## Screenshots & Output Logs


---

---

##  References



