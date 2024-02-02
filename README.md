
<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/carlozamu/Fall_Detection_MSP432_and_ESP8266r">
    <img src="images/ambulance-logo.png" alt="Logo" width="140" height="140">
  </a>

<h3 align="center">Fall Detection MSP432 and ESP8266</h3>

  <p align="center">
    Fall detection system using MSP432 microcontroller with Boosterpack and esp8266
    <br />
    <br /><br />
  </p>
</div>


# Requirements

## Software requirements

To use this project, you will need the following software:

* MSP432-specific version of the [MSPWare software](https://www.ti.com/tool/MSP432WARE#downloads)
* [Code Composer Studio](https://www.ti.com/tool/CCSTUDIO) Integrated Development Environment (IDE)
* Software developement kit for MSP432: [SIMPLELINK-MSP432-SDK](https://www.ti.com/tool/download/SIMPLELINK-MSP432-SDK/3.40.01.02)
<br> <br>

## Hardware Requirements
To use this project, you will need the following hardware:

* Texas Instruments MSP432P401R microcontroller
* [Educational BoosterPack MKII](https://www.ti.com/tool/BOOSTXL-EDUMKII)
* ESP8266 12E [esp8266_nonos_sdk_v1.5.3_16_04_18_0]
  
<p float="left" align="center">
  <img src="images/msp432p401r.png" alt="msp432p401r" width="120" height="205">
  <img src="images/boosterpack.png" alt="boosterpack" width="430" height="205">
  <img src="images/esp8266png.png" alt="esp8266" width="225" height="225">
</p>

<br> <br>

## Setting up the hardware
* Connect MSP432 to BoosterPack
* Connect Rx/Tx of MSP432 (pin 3.2 / 3.3) to esp Tx/Rx 
* Make sure that the rx and tx pins are connected inversely
* Connect GND in both parts
* Coonect 3.3V of MSP432 to 3.3V pin in ESP8266
* After making sure the pins are well connected, connect the MSP to a power source
* Check that the display lights up white and the esp8266 has produced a blue LED to confirm power on. If all this is verified, then the connection was successful

# Development of a Fall Detection System using the MSP432 Microcontroller
This innovative system is designed to enhance user safety through timely fall detection, drawing inspiration from the advanced capabilities of devices like the Apple Watch. By utilizing the MSP432 microcontroller, our system provides a suite of key features:

## 1. Advanced Fall Detection
Utilizing precise movement sensors, including a gyroscope and accelerometer, the system distinguishes falls from daily movements. This functionality allows it to trigger alarms only when strictly necessary, thus reducing false positives.

## 2. Multisensory Alarms
Upon detecting a fall, the device activates:

Auditory Alarms: A buzzer generates loud sounds to draw attention, helping quickly locate the user in distress.
Visual Notifications: Red and white flashes are displayed on the device's screen, enhancing visibility, especially in low-light conditions.
#3. Interactive Health-Check Mode
The system allows users to cancel alarms through an interactive interface requiring the completion of simple motor tasks. This ensures the user's ability to physically respond before deactivating the alarm, thereby confirming their safety status.

## 4. Emergency Call Management via Telegram Bot
If the user does not deactivate the alarm within a set timeframe, the system automatically sends an emergency message via a Telegram bot. This message communicates the situation to emergency services or pre-set contacts, ensuring an immediate and effective response to the emergency.

# Future Implementations
Looking ahead, we aim to expand and enhance our system's capabilities further by introducing new features:

## Operator Management System
A significant future enhancement will involve introducing a dedicated platform for emergency operators. This platform will allow for real-time monitoring of active emergencies, enabling operators to confirm interventions and manage emergency situations more effectively. Through an intuitive interface, operators will be able to view incident details and report the assistance provided, ensuring optimal management of emergencies.

These future enhancements are aimed at making our fall detection system not only more responsive and reliable but also better integrated with existing emergency services, ensuring faster and more targeted responses in emergency situations.

## Video and Presentation

- Youtube [video](https://www.youtube.com/watch?v=hzegHrGtqXE)
- Presentation [slides](https://www.youtube.com/watch?v=hzegHrGtqXE)
The contributions to the project were as follows:

# Team members 
- <strong>Carlo Zamuner </strong> and<strong> Edoardo Castagnini</strong> both played a pivotal role in the software development aspect, bringing technical expertise and significant innovations to the underlying code.
- <strong>Gianluigi Vazzoler</strong> had a multidisciplinary impact, leading the hardware design of the project, implementing the Telegram interface, and providing essential support in code development, showcasing his versatility and technical proficiency.
- <strong>Valeria Mayora</strong> was responsible for the graphic creation of the project, contributing significantly to the communication of the project and the dissemination of the results and objectives through effective and professional visual materials.
