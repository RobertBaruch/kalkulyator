#include <SPI.h>

// See https://www.arduino.cc/en/reference/SPI for details on
// where the clock (SCK) and data output pins (MOSI) are.
// We're going to use A0 as the serial latch signal -- the MAX6922
// isn't quite SPI-compatible, requiring a latch pulse at the
// end of transmission.

// Attach a 330R resistor followed by an LED from pin A1 to ground.
const int led = A1;
const int latch = A0;

void setup() {
  SPI.begin();
  pinMode(latch, OUTPUT);
  digitalWrite(latch, LOW);

  // Never underestimate a simple blinking light to say
  // we're doing stuff and we're not stuck.
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  // Write all 1s to all four MAX6922s. This turns off all
  // the pins on the driver board.
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  for (int i = 0; i < 16; i++) {
    SPI.transfer(0xFF);
  }
  SPI.endTransaction();
  
  // Pulse the latch pin to load the MAX6922s.
  digitalWrite(latch, HIGH);
  digitalWrite(latch, LOW);

  // And wait a short amount of time before starting
  delay(500);
}

// Specs:
// Use 1MHz
// SPI_MODE0 = Clock polarity 0, Clock phase 0
// MSBFIRST = send the most significant bit first. So if
// we want to turn on bit 3, we need to send
// 11111111 11110111.
//
// Remember that in the Nixie circuit, a digit is off
// when its driver output is high. So we need to set all
// the driver outputs high except for the the digit we want
// lit up.

void loop() {
  for (int x = 0; x < 11; x++) {
    uint64_t shifted_bit = 1 << x;
    uint64_t pattern = 0xFFFFFFFFFFFFFFFF ^ shifted_bit; // bit x is now 0, all others 1
    uint64_t patternbits[2] = {0xFFFFFFFFFFFFFFFF, pattern};
    uint64_t bits[2] = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF};

    for (int i = 0; i < 10; i++) {
      // shift bits left 11
      bits[1] <<= 11;
      bits[1] |= bits[0] >> (64 - 11);
      bits[0] <<= 11;
      bits[0] |= 0x7FF;
      bits[0] &= pattern;
    }
    
    // Send the bit pattern
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    for (int i = 1; i >= 0; i--) {
      SPI.transfer(bits[i] >> (64 - 8) & 0xFF);
      SPI.transfer(bits[i] >> (64 - 16) & 0xFF);
      SPI.transfer(bits[i] >> (64 - 24) & 0xFF);
      SPI.transfer(bits[i] >> (64 - 32) & 0xFF);
      SPI.transfer(bits[i] >> (64 - 40) & 0xFF);
      SPI.transfer(bits[i] >> (64 - 48) & 0xFF);
      SPI.transfer(bits[i] >> (64 - 56) & 0xFF);
      SPI.transfer(bits[i] & 0xFF);
    }
    SPI.endTransaction();

    // Pulse the latch
    digitalWrite(latch, HIGH);
    digitalWrite(latch, LOW);

    // Turn LED on
    digitalWrite(led, HIGH);
    delay(250);
    // And off again
    digitalWrite(led, LOW);
    
    // Display digit for a full half second.
    delay(250);
  }
}

