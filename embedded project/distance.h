#include <math.h>       // Standard math library for trigonometric functions
#include <string.h>     // String manipulation functions
#include <stdlib.h>     // Standard library for atof function
#include "UART_interface.h"  // UART communication interface
#include "STD_TYPES.h"       // Standard type definitions
#include "BIT_PATH.h"        // Bit manipulation macros
#include "GPS_private.h"     // Private GPS module definitions
#include "GPS_Config.h"      // GPS configuration
#include "GPS_Interface.h"   // GPS module interface
#include "funcUart.h"
// Constants
#define PI 3.14159265358979323846
#define EARTH_RADIUS_M 6371000.0  // Earth's radius in meters
#define SENTENCE_SIZE 256         // Maximum NMEA sentence size
#define MAX_ATTEMPTS 5            // Max attempts to read valid GPS data

/* Convert GPS coordinate format (ddmm.mmmm) to decimal degrees */
f64 GPS_ConvertToDecimalDegrees(f64 coord) {
    u32 degrees = (u32)(coord / 100);      // Extract degrees part (first 2 digits)
    f64 minutes = coord - (degrees * 100); // Extract minutes part (remainder)
    return degrees + (minutes / 60.0);     // Combine as decimal degrees
}

/* Convert degrees to radians for trigonometric calculations */
f64 GPS_DegreesToRadians(f64 degrees) {
    return degrees * (PI / 180.0);
}

/* Calculate distance between two points using Haversine formula */
f64 GPS_CalculateDistance(f64 lat1, f64 lon1, f64 lat2, f64 lon2) {
	
	    float lat1Degree = GPS_ConvertToDecimalDegrees(lat1);
	    float lon1Degree = GPS_ConvertToDecimalDegrees(lon1);

    // Convert differences to radians
    f64 dLat = GPS_DegreesToRadians(lat2 - lat1Degree);
    f64 dLon = GPS_DegreesToRadians(lon2 -  lon1Degree);
    
    // Convert individual coordinates to radians
    lat1 = GPS_DegreesToRadians(lat1Degree);
    lat2 = GPS_DegreesToRadians(lat2);
    
    // Haversine formula components
    f64 a = sin(dLat/2) * sin(dLat/2) + 
             cos(lat1) * cos(lat2) * 
             sin(dLon/2) * sin(dLon/2);
    f64 c = 2 * atan2(sqrt(a), sqrt(1-a));
    
    return EARTH_RADIUS_M * c;  // Distance in meters
}




u8 GPS_IsInRange(float currLat, float currLon, 
                float targetLat, float targetLon, 
                float radius) {
    f64 distance = GPS_CalculateDistance(currLat, currLon, 
                                      targetLat, targetLon);
								//	UART0_SendChar('u'); 
    return (distance <= radius) ? 1 : 0;
}
