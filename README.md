
<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/carlozamu/Fall_Detection_MSP432_and_ESP8266r">
    <img src="ambulance-logo.png" alt="Logo" width="140" height="140">
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
  
<p float="left">
  <img src="msp432p401r.png" alt="msp432p401r" width="140" height="225">
  <img src="boosterpack.png" alt="boosterpack" width="450" height="225">
  <img src="esp8266.png" alt="boosterpack" width="450" height="225">
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



