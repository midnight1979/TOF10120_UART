#include <SoftwareSerial.h>

// common variables for TOF10120 UART reading and parsing
String rx_tof = "";
char rx_char;
uint8_t double_m = 0;
bool newLine_tof = false;

// total distance value
uint8_t distance = 0;

// Average filter variables, because of noise of raw sensor values from UART
uint8_t counter = 0;
int commulative = 0;
const uint8_t koeff = 5;    // average coefficient


// software serial #1: RX = digital pin 10, TX = digital pin 11
SoftwareSerial portOne(10, 11);

void setup() {
  // Open serial communications (monitoring port)
  Serial.begin(9600);
  // Start software serial port (TOF10120 port)
  portOne.begin(9600);
  Serial.println("TOF10120 Laser Distance Metering Sensor start...");
  portOne.write("s2-20#");
}

void loop() {

  // Getting values from sensor procedure
  measure();
}

void measure()
{
  rx_tof = "";

  // Values parsing from TOF10120 UART
  while (1) {
    if (portOne.available()) {
      rx_char = portOne.read();
      if (rx_char == 10) {
        newLine_tof = true;
        continue;
      }
      if (newLine_tof == true) {
        if (rx_char == 'm') {
          double_m = double_m + 1;
        }
        else {
          rx_tof.concat(rx_char);
        }
        if (double_m == 2) {
          newLine_tof = false;
          break;
        }
      }
    }
  }

  newLine_tof = false;
  double_m = 0;

  // average sensor values and print to Serial
  if (rx_tof != "") {
    if (counter < koeff)
    {
      commulative = commulative + (rx_tof.toInt() / 10);
      counter = counter + 1;
    }
    else
    {
      distance = commulative / counter;
      commulative = 0;
      counter = 0;

      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm.");
    }
  }
}
