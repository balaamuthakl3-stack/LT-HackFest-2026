# LT-HackFest-2026
Project submission for LT HackFest 2026
Smart Toxic Gas Early-Warning & Worker Safety System

LT HackFest 2026

Detect Early. Alert Fast. Protect People.

Project Overview

The Smart Toxic Gas Early-Warning & Worker Safety System is an industrial safety solution designed to detect abnormal toxic gas conditions at an early stage and help protect workers during hazardous situations.

The system continuously monitors environmental conditions using gas sensors and other safety inputs connected to an ESP32 controller. When an abnormal or dangerous gas condition is detected, the system provides immediate local alerts, identifies the affected zone, guides workers toward a safe assembly area, and helps verify worker safety using RFID-based accountability.

The system is designed to continue providing essential local safety functions even when internet connectivity is unavailable.

Problem Statement

Toxic gas leaks in factories, chemical industries, laboratories, storage facilities, and other confined industrial environments can become dangerous very quickly.

Conventional monitoring systems may focus mainly on detecting gas leakage, but workers also need timely warning, clear information about the affected area, evacuation guidance, and confirmation that workers have reached a safe location.

The major challenges include:

- Lack of early warning for abnormal gas conditions
- Difficulty identifying the affected zone
- Delayed evacuation decisions
- Difficulty confirming whether workers have reached a safe area
- Dependence on internet connectivity in some monitoring systems
- Loss of monitoring capability during power interruptions

Proposed Solution

Our system combines gas monitoring, zone identification, worker accountability, local alerts, and evacuation guidance into one integrated safety system.

The ESP32 acts as the main controller and processes information from gas sensors, temperature and humidity sensors, RFID readers, and an emergency button.

When a dangerous condition is detected, the system:

1. Detects the abnormal gas condition.
2. Evaluates the risk level.
3. Identifies the affected zone.
4. Displays the zone and safety status on the OLED display.
5. Activates the appropriate LED indicators and buzzer.
6. Provides evacuation guidance toward a safe assembly zone.
7. Uses RFID information to help account for workers.
8. Indicates if workers are missing or have reached the safe zone.
9. Stores or maintains essential information locally so basic operation can continue without internet connectivity.

Key Features

- Real-time toxic gas monitoring
- Early abnormal-condition detection
- Affected-zone identification
- Local OLED status display
- Red, yellow, and green safety indicators
- Audible emergency alarm
- RFID-based worker entry and accountability
- Safe-zone and evacuation guidance
- Emergency button
- Temperature and humidity monitoring
- Local operation during internet failure
- Backup power support
- Scalable architecture for multiple industrial zones

System Architecture

Inputs

- Gas sensor
- Temperature and humidity sensor
- RFID reader and worker tags
- Emergency button

Processing Unit

- ESP32 controller

Outputs

- OLED display
- Buzzer/alarm
- Red, yellow, and green LED indicators
- Safe-path/evacuation indicator

Power

- Main power supply
- Backup battery/power source for essential operation

Working Flow

Sensors Monitor Continuously
          ↓
Abnormal Gas Condition Detected
          ↓
ESP32 Evaluates Risk
          ↓
Affected Zone Identified
          ↓
Alarm + Local Display Activated
          ↓
Workers Guided to Safe Zone
          ↓
RFID Used for Worker Accountability
          ↓
System Confirms Safe / Missing Workers

Zone-Based Safety Concept

The system divides the workplace into monitored zones.

For example:

- Zone A — Safe
- Zone B — Danger
- Zone C — Safe

If a dangerous gas condition is detected in Zone B, the system identifies Zone B as the affected area and provides local warning and evacuation guidance toward the designated safe assembly area.

Worker Accountability

RFID technology is used to help track workers entering and leaving monitored areas.

During an emergency:

1. Workers are identified through RFID.
2. A gas danger condition is detected.
3. Workers move toward the safe zone.
4. The system checks available RFID information.
5. The system can indicate whether workers are accounted for or whether someone may be missing.

This adds an accountability layer beyond simple gas detection.

Offline Safety Operation

The system is designed to maintain essential local safety functions even when internet connectivity is unavailable.

Local sensors, ESP32 processing, OLED display, buzzer, LEDs, and backup power can continue supporting immediate safety decisions without depending entirely on a remote server.

Technologies Used

- ESP32
- MQ-series gas sensor
- Temperature and humidity sensor
- RFID reader and RFID tags
- OLED display
- Buzzer
- Red/Yellow/Green LEDs
- Emergency push button
- Backup power supply
- Embedded C/C++ programming

Applications

The system can be adapted for:

- Chemical industries
- Manufacturing plants
- Laboratories
- Industrial storage facilities
- Confined work areas
- Processing plants
- Other workplaces where hazardous gas leakage may occur

Expected Impact

The proposed system aims to improve industrial safety by combining early gas detection with zone identification, immediate local alerts, evacuation guidance, and worker accountability.

Instead of only detecting a gas leak, the system focuses on helping answer three important questions:

What happened?

Where is the danger?

Are the workers safe?

Future Enhancements

Future versions can include:

- Cloud-based monitoring
- Mobile application notifications
- Remote alerts to authorized personnel
- Multiple gas-type identification
- Historical sensor-data analysis
- AI-based abnormal-condition prediction
- Larger multi-zone deployment
- Integration with industrial safety systems

Project Goal

We don't just detect gas. We protect people through early warning, zone identification, safe evacuation, and worker accountability.
