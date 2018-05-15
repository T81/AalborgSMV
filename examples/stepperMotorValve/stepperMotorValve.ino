/*
  Aalborg SMV library Example

  Author: T81

  This file is free software; you can redistribute it and/or modify
  it under the terms of either the GNU General Public License version 3
  published by the Free Software Foundation.
*/

// include the required libraries
#include <SPI.h>
#include <DAC_MCP49xx.h>
#include <AalborgSMV.h>

// Create a DAC_MCP49xx instance
DAC_MCP49xx dac(DAC_MCP49xx::MCP4921, 10);  // using MCP4921 dac and pin10 as CS

// create an AalborgSMV instance and pass the DAC_MCP4921 reference
AalborgSMV valve(&dac);


void setup() {
  // initialize the object with pins 2,3,4 controlling Direction, Close and Purge pins respectively
  valve.begin(2, 3, 4);
}

void loop() {
  // open valve with 50% of max speed for 5s
  valve.speed(50.0);
  delay(5000);

  // set valve to purge (opening with full speed) for 5s
  valve.purge();
  delay(5000);

  // close valve with 50% of max speed for 5s
  valve.speed(-50.0);
  delay(5000);

  //set valve to close for 5s
  valve.close();
  delay(5000);

  while (true) {
    // do not repeat the above code
  }
}