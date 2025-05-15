#ifndef MY_HEADER_H2
#define MY_HEADER_H2

#include "funcUart.h"
static volatile char gpsStoredData [100];
int static volatile WrongReceivedSignals=0 ;
static volatile bool  SentenceFound= false;
static volatile bool flagEnd = false;
static volatile bool flag_found = false; 
static  int counter = 0 ;


/*

void UART1_Handler(void)
{	  
	 int counter = 0  ;
   flagEnd = false;
	
   while (IsUartDataAvailable()==true)
   {
        
		  char current_char = UART1_ReadChar();	
					
			
	  	if (current_char == '\n'|| counter>100)
				{   
            SentenceFound=false;
						gpsStoredData[counter] = '\0';
					//  print counter
					  UART0_SendChar('p');


						break;
						
				}
			
				
			if(counter== 0 && (current_char!='$'))
					
				{
				    continue; //start again form while
				
				}
				
			gpsStoredData[counter++]= current_char;
					
			if(counter==6)
				{ 
				    SentenceFound = RequiredSentence(gpsStoredData);
					
				    if(!SentenceFound)
					
				     {
								counter=0;
							  flagEnd=false;

								WrongReceivedSignals += 1;// all sentence gps normally recevies are disabled except for a few
							   UART0_SendChar('w');

								break; // out of  while loop 
						 }	
		  	}
				
		}
	 
		counter=0;
		if(SentenceFound)
		{	flagEnd=true;
		}
	
			
}
*/
void UART1_Handler(void)
{	  
		
  
	
   if (IsUartDataAvailable()==true)
   {
        
		  char current_char = UART1_ReadChar();	
					
			
	  	if ((current_char == '\n'|| counter>100))
         	
			   

				{   gpsStoredData[counter] = '\0';
						 //UART0_SendChar('u');
     

					if(RequiredSentence(gpsStoredData))
					{
							  flagEnd=true; 
					}	 
				else   
			   	{   
					      flagEnd=false;
								WrongReceivedSignals += 1;
				  }   
				
				  	counter=0;
					
				    return;
 
				}
			
				
			if(counter== 0 && (current_char!='$'))
					
				{
				    return; //start again form while
				
				}
				
			gpsStoredData[counter++]= current_char;

		}
	 
		
	
			
}

bool gpsDataParser( char gpsStoredData[], char fields[][20] )  // get longtitude and latitude from  char[]  gpsStoredData
  {
		
   bool flag_found = false; 
   char *address_array[7];	
		
		
	 address_array[0] =	strchr( gpsStoredData , 'A');
	 
	if(address_array[0]==NULL )
	{ 
	    address_array[0] =	strchr( gpsStoredData , 'V');
	    
          if(address_array[0]==NULL)  
         {   UART0_SendChar('u');
              return false;
          }
				 
					else if (*address_array[0] == 'V')
						 {  UART0_SendChar('h');
              return false;
          }
          
	}

   
		
		
	 if (*address_array[0] == 'A')
		{   //  UART0_SendChar('d');

    		 flag_found =true;
         //printf("Sentence is valid: %c\n", *address_array[0]);
         fields[0][0] = 'A';
		     fields[0][1] = '\0';
       
			/*
			for (int i=1;i<=5;i++)
		    {
		     address_array[i] =	strchr(  address_array[i-1]+2 , ',');
            
             if (address_array[i] == NULL) 
						 {  UART0_SendChar('n');
                     return false;
                 }
          //  printf("Message: %p %d \n" , (void*)address_array[i], i);
								 
            int offset2= address_array[i]-address_array[i-1];
								 
			      strncpy( fields[i],address_array[i-1]+2,offset2-1);
            fields[i][offset2] = '\0';  
		        //printf("fields are   %s\n" , fields[i-1]);
						//UART0_SendChar('j');

		    }
		*/
	    	for (int i=1;i<=5;i++)
		    { 
				 if (i==1) { address_array[i] =	strchr(  address_array[i-1]+2 , ',');}
				else {
		     address_array[i] =	strchr(  address_array[i-1]+1 , ',');}
            
             if (address_array[i] == NULL) 
						 {  UART0_SendChar('r');
                     return false;
                 }
          //  printf("Message: %p %d \n" , (void*)address_array[i], i);
								 
            int offset2= address_array[i]-address_array[i-1];
						if (i==1) 		 { strncpy( fields[i],address_array[i-1]+2,offset2-2);	} 
						else{  strncpy( fields[i],address_array[i-1]+1,offset2-1);}
            fields[i][offset2] = '\0';  
		        //printf("fields are   %s\n" , fields[i-1]);
		    
			} 
     }
		 		//		UART0_SendChar('x');

		return true;
		 
  }
	
	float simple_atof(const char *str) //convert from ascii to float
		{ 
    if (str == NULL) return 0.0;  
    float result = 0.0;
    float frac = 0.1;
    int is_fraction = 0;

    while (*str) {
        if (*str == '.') {
            is_fraction = 1;
        } else if (*str >= '0' && *str <= '9') {
            if (!is_fraction) {
                result = result * 10 + (*str - '0');
            } else {
                result += (*str - '0') * frac;
                frac *= 0.1;
            }
        }
        str++;
    }   		 //		UART0_SendChar('x');

    return result;
}
#endif // MY_HEADER_H2
	