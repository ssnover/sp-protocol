/*
 * file: test.cpp
 * purpose: Test the serialization function.
 */

#include <cassert>
#include <iostream>
#include <memory>
#include "serialize.h"

int main(int argc, char ** argv)
{
  sp_TemperatureKelvin kelvin;
  kelvin.temperature = 0;
  SerializationBuffer buffer;
  auto managed_memory = std::make_unique<uint8_t[]>(10);
  buffer.data = managed_memory.get();
  std::cout << "Serializing test case 0." << std::endl;
  serializeTemperatureKelvin(&kelvin, &buffer);
  assert(buffer.size == 6);
  assert(buffer.data[0] == 0xAA);
  assert(buffer.data[1] == 3);
  assert(buffer.data[2] == SPMESG_TEMPERATURE_KELVIN);
  assert(buffer.data[3] == 0x00);
  assert(buffer.data[4] == 0x00);
  assert(buffer.data[5] == 0xFF);

  std::cout << "Serializing test case 1." << std::endl;
  kelvin.temperature = 0xAA;
  serializeTemperatureKelvin(&kelvin, &buffer);
  assert(buffer.size == 7);

  std::cout << "Serializing test case 2." << std::endl;
  kelvin.temperature = (0xAA << 8) + (0xFF);
  serializeTemperatureKelvin(&kelvin, &buffer);
  assert(buffer.size == 8);

  return 0;
}
