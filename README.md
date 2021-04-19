# TOF10120_UART
TOF10120 arduino example (UART MODE)

Serial port of Arduino Nano used for local monitoring, SoftWare Serial used for TOF10120 connection.

When using Arduino MEGA2560 (or another with two hardware uart interfaces) - sketch can be easily edited.

I'm using this sensors as level-meters in water tanks - very quick and accurate enough.

Example based on https://github.com/SoyM/TOF10120, but with some modifications - more fast metering and average data calculating.

# Connections:

TOF10120     Arduino Nano (atmega328)

GND(1) -----> GND

VDD(2) -----> +5v

RX(3)  -----> D11

TX(4)  -----> D10
