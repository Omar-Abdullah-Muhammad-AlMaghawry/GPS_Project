#include <stdio.h>
#include <stdbool.h>
#include "uart.h"

//char UartRead() { return 'c'; }   // «·„›—Ê÷ ⁄„— Ì⁄„· —Ì»·Ì” »«”„ «·›«‰ﬂ‘‰ » «⁄ Â 

// [$GPGGA,100156.000,2690.9416,N,07547.8441,E,1,08,1.0,442.8,M,-42.5,M,,0000*71]


bool coordinates_parser(const UartConfig * conf, float* longitude, float* latitude) { //«·ﬂÊœ «·ﬁœÌ„ ﬂ«‰ »Ì⁄  «—«Ì „‰ Õ—Ê› ⁄·‘«‰ Ì”Ã· ﬂ· —ﬁ„ ⁄·Ì ‘ﬂ· ‰’
	unsigned char incomer_data = 0;
	unsigned int array_count = 0;
	unsigned char latitude_char[9];
	unsigned char longitude_char[10];
	//while (1) {																			//keep loping till you reach the desired NMEA Sentence
	if(1){
		incomer_data = UART_recieveChar(conf);													   //Check the string '$GPGGA,'
		if (incomer_data == '$') {                                                      // First statement of the GPS data start with a $ sign
			incomer_data = UART_recieveChar(conf);                                                // If the first if become true then the next phase
			if (incomer_data == 'G') {
				incomer_data = UART_recieveChar(conf);
				if (incomer_data == 'P') {
					incomer_data = UART_recieveChar(conf);
					if (incomer_data == 'R') {
						incomer_data = UART_recieveChar(conf);
						if (incomer_data == 'M') {
							incomer_data = UART_recieveChar(conf);
							if (incomer_data == 'C') {
								incomer_data = UART_recieveChar(conf);
								if (incomer_data == ',') {                                   // first , received
									incomer_data = UART_recieveChar(conf);                             // At this stage Final check in done, GPRMC is found.
									while (incomer_data != ',') {                         // skipping GMT Time
										incomer_data = UART_recieveChar(conf);
									}
									incomer_data = UART_recieveChar(conf);
									while (incomer_data != ',') {                         // skipping next part curently 'A'
										incomer_data = UART_recieveChar(conf);
									}

									incomer_data = UART_recieveChar(conf);
									latitude_char[0] = incomer_data;
									while (incomer_data != ',') {
										for (array_count = 1; incomer_data != 'N' && incomer_data != 'S'; array_count++) {
											incomer_data = UART_recieveChar(conf);
											latitude_char[array_count] = incomer_data;             // Store the Latitude data
										}
										(*longitude) = strtod(longitude_char, NULL);            //convert char to double or  float
										if (incomer_data == 'S') (*longitude) *= -1;
										incomer_data = UART_recieveChar(conf);
										if (incomer_data == ',') {
											for (array_count = 0; incomer_data != 'E' && incomer_data != 'W'; array_count++) {
												incomer_data = UART_recieveChar(conf);
												longitude_char[array_count] = incomer_data;        // Store the Longitude data
											}
										}
										(*latitude) = strtod(latitude_char, NULL);
										if (incomer_data == 'W') (*latitude) *= -1;
									}
								}
							}

						}
					}
				}
			}
		}
	}
	return true;
}
