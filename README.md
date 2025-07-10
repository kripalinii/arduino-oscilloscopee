# arduino-oscilloscopee


# Arduino-Based Oscilloscope

GE107 Group Project | March 2025  
Guide: Dr. Basant Subba, Assistant Professor, CSE, IIT Ropar

Designed a real-time dual-trace oscilloscope and square signal generator using Arduino Uno. Visualized voltage and current waveforms on a 2.4" TFT LCD and provided serial output compatible with the Arduino IDE Serial Plotter. Aimed at low-frequency signal monitoring for educational and diagnostic applications.

---

## Features

- Real-time waveform display for both voltage and current
- Dual-trace plotting with axis labels and gridlines
- Uses ZmPT101B (voltage) and ACS712 (current) sensors
- Displayed on TFT LCD via Adafruit GFX and TFTLCD libraries
- Compatible with Arduino IDE Serial Monitor and Plotter

---

## Circuit Setup

- Arduino Uno with TFT LCD shield
- Voltage sensor (ZmPT101B) connected to A5
- Current sensor (ACS712) connected to A4
- TFT connected using standard shield pin configuration
- USB used for power, programming, and serial output

---

## Code Snippet

```cpp
float voltage = map(analogRead(A5), 0, 1023, -100, 100) / 10.0;
int voltageY = map(voltage * 10, -100, 100, 130,*
