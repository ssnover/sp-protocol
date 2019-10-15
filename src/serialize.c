/*
 * file: sp-protocol.c
 * purpose: Implementation of serialization of message types into data buffers.
 */

#include <stdbool.h>
#include "serialize.h"

typedef enum SPMessageFields
{
  FIELD_SOM = 0u,
  FIELD_LENGTH = 1u,
} SPMessageFields;

static uint8_t const START_OF_MESSAGE = 0xAA;
static uint8_t const END_OF_MESSAGE = 0xFF;
static uint8_t const ESCAPE_CHARACTER = 0x18;

static void addHeader(SerializationBuffer * buffer)
{
  buffer->data[FIELD_SOM] = START_OF_MESSAGE;
  buffer->size = FIELD_LENGTH + 1;
}

static void appendEndFrame(SerializationBuffer * buffer)
{
  buffer->data[buffer->size++] = END_OF_MESSAGE;
}

static bool needsEscape(uint8_t data)
{
  return (data == START_OF_MESSAGE || data == END_OF_MESSAGE || data == ESCAPE_CHARACTER);
}

static void serialize_byte(uint8_t data, SerializationBuffer * buffer)
{
  if (needsEscape(data))
  {
    buffer->data[buffer->size++] = ESCAPE_CHARACTER;
  }
  buffer->data[buffer->size++] = data;
}

static void serialize_u16(uint16_t data, SerializationBuffer * buffer)
{
  serialize_byte(data >> 8, buffer);
  serialize_byte(data & 0xFF, buffer);
}

static void serialize_u32(uint32_t data, SerializationBuffer * buffer)
{
  serialize_byte(data >> 24, buffer);
  serialize_byte((data >> 16) & 0xFF, buffer);
  serialize_byte((data >> 8) & 0xFF, buffer);
  serialize_byte(data & 0xFF, buffer);
}

void serializeTemperatureKelvin(sp_TemperatureKelvin const * const data, SerializationBuffer * buffer)
{
  addHeader(buffer);
  serialize_byte(SPMESG_TEMPERATURE_KELVIN, buffer);
  serialize_u16(data->temperature, buffer);
  buffer->data[FIELD_LENGTH] = buffer->size - (FIELD_LENGTH + 1);
  appendEndFrame(buffer);
}

