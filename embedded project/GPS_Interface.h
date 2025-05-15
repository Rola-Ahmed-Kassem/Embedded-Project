#ifndef GPS_INTERFACE_H
#define GPS_INTERFACE_H

#include "STD_TYPES.h"
#include "UART_interface.h"

typedef enum {
    GPS_VALID_DATA,
    GPS_INVALID_DATA,
    GPS_NO_DATA
} GPS_Status_t;

GPS_Status_t GPS_GetLocation(UART_CONFIG_t *uart, f64 *lat, f64 *lon);
u8 GPS_IsInRange(f64 currLat, f64 currLon, f64 targetLat, f64 targetLon, f64 radius);
f64 GPS_StringToFloat(u8 *str);
f64 GPS_CalculateDistance(f64 lat1, f64 lon1, f64 lat2, f64 lon2);
f64 GPS_ConvertToDecimalDegrees(f64 coord);

#endif
