#include "UartInitalization.h"
#include "funcUart.h"
#include "interrupt&parser.h"
#include "distance.h"
#include "LCD_-1.h"
#include "SysTick-1.h"



int main(void)
{   //enable_fpu();
	
   UART0_Init();   
    UART1_Init();
 __enable_irq();
    bool x; 
	 static char Fields[6][20];
	  char copiedGpsStoredData[100];
	float latitude =0;
	float longtitude =0;
	 // Structure with fixed-size string array
typedef struct {
    float latitude;
    float longitude;
    char name[20];  // Use array instead of pointer
} Location;

// Saved location definitions
Location places[] = {
    {30.0636111, 31.2802777, "Hall c&D"},
    {30.06416666666667,31.27999999999998	, "hall A&B"},
    {30.0647222, 31.2777777, "gate 2"},
    {30.0638888888889, 31.277777777777778, " mech workshop"},
    {30.06361111111111, 31.278333333333332, "credit building"}
};
    u8 numPlaces = sizeof(places) / sizeof(places[0]); 
	        UART0_SendChar('z');
    
	  while (1) 
		{  

       if(flagEnd)
			{     
				                           

			   __disable_irq();
			   UART0_SendString("main started\n");
			  strcpy(copiedGpsStoredData,(const char*)gpsStoredData);
			  flagEnd=false;

			 UART0_SendString("ISR OUTPUT: ");
			 UART0_SendString(copiedGpsStoredData);
                         UART0_SendChar('\n');
                        __enable_irq();
          
			 x= gpsDataParser(copiedGpsStoredData, Fields);  


     			 if(x)
			{		  
				//UART0_SendString("gpsDataParser OUTPUT:");
								
                                  UART0_SendString("Current Location: ");
                              
				for (int i= 1 ;i<5 ; i++)
				{ //UART0_SendChar('c');
                        
				UART0_SendString(Fields[i]);
				UART0_SendChar(',');
												
				}
				 // UART0_SendString("\r\n");  
											
											
				 latitude = simple_atof(Fields[1]);
				//	UART0_SendChar('p');
            
			         longtitude = simple_atof(Fields[3]);
							;

							}
		//	float	 latitude1 =  3003.81738;   //30.063623,31.278644
      //float   longtitude1 =03116.71866; // 3003.81738,N,03116.71866,E					//30.0633333, 31.2783333

//float distance = GPS_CalculateDistance(  3003.81738,03116.71866, 30.0633333, 31.2783333);
//char buffer[32];
  // sprintf(buffer, "Converted: %.9f\n", distance);		
    //UART0_SendString(buffer);  
	 
//if (43 > GPS_CalculateDistance(  3003.81738,03116.71866, 30.0633333, 31.2783333))  {UART0_SendChar('y');}  else{UART0_SendChar('b');}
//3003.80539,N
//Longitude = 3116.70622,E



	 u8 found = 0;
							
	UART0_SendChar('l');
       for (u8 i = 0; i < numPlaces; i++) {
	//	UART0_SendChar('b');

            if (GPS_IsInRange(latitude, longtitude,
                              places[i].latitude,
                              places[i].longitude,
                              20.0)) {
															//								UART0_SendChar('v');

                UART0_SendString("Near: ");
                UART0_SendString(places[i].name);  // Use the name array directly
                UART0_SendString("\r\n");
                found = 1;
                break;
            }
													//		else {UART0_SendChar('y');} 
        }

        // If not near any saved place
        if (!found) {
            UART0_SendString("Not near any known location\r\n");
        }

        // Wait 2 seconds before checking again
       // Delay_ms(2000);
    }

    LCD_init();
    LCD_command(0x01);  // Clear display
    LCD_command(0x80);  // Set cursor to first row

    delayMs(100);  // Extra delay after initialization
    LCD_data('A'); // Display 'A'
   
    while(1);
        
			}    
			   
		}	  
		
	
		
	
  
		


