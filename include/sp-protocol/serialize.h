/*
 * file: sp-protocol.h
 * purpose: Take in SP messages and return serialized byte arrays for transfer over UART.
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct SerializationBuffer
{
  size_t size;
  uint8_t * data;
} SerializationBuffer;

typedef enum SPMessageType
{
  SPMESG_TEMPERATURE_KELVIN = 0u,
  SPMESG_TEMPERATURE_CELSIUS = 1u,
  SPMESG_TEMPERATURE_FAHRENHEIT = 2u,
} SPMessageType;

typedef struct sp_TemperatureKelvin
{
  uint16_t temperature;
} sp_TemperatureKelvin;

/*
 * Emplaces the temperature data into an SP message buffer.
 * Returns: The serialized message buffer.
 */
void serializeTemperatureKelvin(sp_TemperatureKelvin const * const data, SerializationBuffer * buffer);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

