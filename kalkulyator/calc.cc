#include <cerrno>
#include <cstring>
#include <cstdint>
#include <cstdio>
#include <string>
#include <wiringPi.h>
#include <wiringPiSPI.h>

constexpr int VOLTS = 29;
constexpr int LOAD = 28;
constexpr int CHANNEL = 1;

// Given a string of 10 digits, sets 16 bytes of driver output.
// Note that the first byte is sent LAST, and the MSb of each byte
// is sent first.
void digits_to_data(std::string& digits, unsigned char *data) {
  printf("%s\n", digits.c_str());
  memset(data, 0xFF, 16);

  for (int i = 9; i >= 0; i--) {
    uint8_t bit_to_set = digits[i] - '0';
    bit_to_set += i * 11;
    uint8_t data_index = 15 - bit_to_set / 8;
    uint8_t data_bit_index = bit_to_set % 8;
    data[data_index] ^= (1 << data_bit_index);
  }

  /*for (int i = 0; i < 16; i++) {
    printf("%02X ", data[i]);
  }
  printf("\n");*/
}

void init() {
  unsigned char data[16];
  std::string str("          ");
  digits_to_data(str, data);
  wiringPiSPIDataRW(CHANNEL, data, 16);
  digitalWrite(LOAD, 1);
  delayMicroseconds(10);
  digitalWrite(LOAD, 0);
}

int main(int argc, char **argv) {
  if (wiringPiSetup() < 0) {
    fprintf(stderr, "WiringPi setup failed: %s\n", std::strerror(errno));
    return 1;
  }
  printf("WiringPi set up.\n");
  if (wiringPiSPISetup(CHANNEL, 500000) < 0) {
    fprintf(stderr, "WiringPiSPI setup failed: %s\n", std::strerror(errno));
    return 1;
  }
  printf("WiringPiSPI set up.\n");

  pinMode(VOLTS, OUTPUT);
  pinMode(LOAD, OUTPUT);
  digitalWrite(VOLTS, 0);
  digitalWrite(LOAD, 0);

  std::string str("0000000000");
  init();
  digitalWrite(VOLTS, 1);
  
  while (1) {
    unsigned char bit_data[16];
    digits_to_data(str, bit_data);

    wiringPiSPIDataRW(CHANNEL, bit_data, 16);
    digitalWrite(LOAD, 1);
    delayMicroseconds(10);
    digitalWrite(LOAD, 0);
    delayMicroseconds(10000);

    //delayMicroseconds(200000);
    //digitalWrite(VOLTS, 1);
    //delayMicroseconds(200000);
    //digitalWrite(VOLTS, 0);

    for (int i = 0; i < 10; i++) {
      str[i]++;
    }
    if (str[0] == '9' + 1) {
      str = (char *)"0000000000";
    }
  }
}

