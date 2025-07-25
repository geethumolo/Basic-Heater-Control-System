# Heater Control System - Documentation
Simulation run link: [Link](https://wokwi.com/projects/437441097611879425) (Please refer Heading 3: Control Logic for Wokwi simulation runs)

## Project Overview

Brief description of the system:

> A basic embedded heater control system that monitors temperature using a sensor and activates or deactivates a simulated heater based on defined thresholds.

---

## Part 1: System Design

### 1. Minimum Sensor Requirements

- **Primary Sensor:**\
  `DHT22 (Digital Temperature and Humidity Sensor)`\
  Justification:

  > Accurate temperature readings are crucial for reliable heater control.

- **Optional Sensors (for future enhancements):**

  - Overheat detection sensor (e.g., thermal fuse)
  - Ambient humidity sensor

---

### 2. Communication Protocol Recommendation

- **Chosen Protocol:** `I2C`

  Justification:
  > I2C is chosen due to its simplicity and ability to connect multiple devices over two wires, including the LCD and DHT sensor.

---


### 3. Future Roadmap

| Feature                   | Description                                        |
| ------------------------- | -------------------------------------------------- |
| Overheating Protection    | Integrate an overheat limit and emergency shutdown |
| Multiple Heating Profiles | Support user-defined heating curves or profiles    |

---

## Part 2: Embedded Implementation

### 1. Platform Details

- Simulation Platform: Wokwi
- Microcontroller: Arduino UNO
- Language/Framework: C++ (Arduino)

---

### 2. System States

| State          | Description                         |
| -------------- | ----------------------------------- |
| Idle           | System initialized, awaiting action |
| Heating        | Heater is ON, raising temperature   |
| Stabilizing    | Approaching target temperature      |
| Target Reached | Desired temperature maintained      |
| Overheat       | Emergency state, heater turned OFF  |

---

### 4. Control Logic (Please refer this for Wokwi simulation runs)

- **Temperature Reading Logic:**

  - A `testMode` flag determines whether the system uses simulated temperature values (via a timed sequence) or reads actual temperature from the DHT22 sensor.
  - When `testMode` is set to `true`, the temperature increases over time using a predefined sequence.
  - When `testMode` is set to `false`, the DHT22 sensor is polled for real-time temperature values.

- **Timing Intervals:**

  - `lcdUpdateInterval`: 1000 ms (LCD refresh rate)
  - `tempStepInterval`: 6000 ms (interval between simulated temperature changes)
  - `overheatHoldTime`: 5000 ms (duration to hold in overheat state before reset)

- **Pin Configuration:**

  - DHT22 Sensor: Digital Pin 3
  - Switch/Button Input: Digital Pin 2
  - Buzzer Output: Digital Pin 7
  - LEDs for State Indication: Digital Pins 8–12
  - LCD via I2C: Address 0x27

- **Stage Determination Logic:**

  - `< 25°C` > Idle
  - `25–31°C` > Heating
  - `32–35°C` > Stabilizing
  - `36–38°C` > Target Reached
  - `≥ 39°C` > Overheat

- **Activation & Reset:**

  - Heater system activates upon button press.
  - When in Overheat state for 5 seconds, the system resets to Idle and restarts the simulation (if testMode is enabled).

---

### 5. Additional Features

- **Visual Indicators:**

  - Five LEDs represent each system state. Only one LED is active at a time.
  - Buzzer is triggered continuously during the Overheat state.

- **Timing Mechanism:**

  - All time-based updates use the `millis()` function for non-blocking periodic operations.

### 6. Screenshots
- Schematic Diagram (Off state)
- ![Off Screenshot](../screenshots/Off.png)
- Schematic Diagram (Running state)
- ![On Screenshot](../screenshots/On.png)


## References

- Sensor datasheets
- Arduino documentation
- Wokwi simulation environment
- LCD and DHT libraries for Arduino

