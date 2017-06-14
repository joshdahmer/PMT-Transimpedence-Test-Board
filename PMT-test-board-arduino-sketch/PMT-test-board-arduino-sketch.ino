
#include <SPI.h>

uint8_t MCP41050_CS_PIN = 5;
uint8_t MOSI_PIN = 11;
uint8_t SCK_PIN = 13;

void setup() {
  pinMode(MCP41050_CS_PIN, OUTPUT);
  Serial.begin (115200);
  SPI.begin();
  set_pot(0x00);
  delay(1000);
}

void loop() {
  for (uint8_t i = 0; i < 255; i++) {
    set_pot(i);
    int sensorValue = analogRead(14);
    float voltage = sensorValue * (3.2/1023.0);
    Serial.println(voltage,4);
    delay(100);
  }
  Serial.println("End");
}

void set_pot(uint8_t value) {
  // take the SS pin low to select the chip:
  digitalWrite(MCP41050_CS_PIN, LOW);

  // send Command to write value and enable the pot
  SPI.transfer(0x11);
  // send in the value via SPI:
  SPI.transfer(value);

  // take the SS pin high to de-select the chip:
  digitalWrite(MCP41050_CS_PIN, HIGH);

}

