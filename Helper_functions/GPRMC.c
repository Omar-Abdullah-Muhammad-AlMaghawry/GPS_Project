#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

char UartRead() { return 'c'; }   // «·„›—Ê÷ ⁄„— Ì⁄„· —Ì»·Ì” »«”„ «·›«‰ﬂ‘‰ » «⁄ Â 

// [$GPRMC,141848.00,A,2690.9416,N,07547.8441,E,0.553,,100418,,,A*73]

// don't forget to free the pointers u send
bool coordinates_parser_char_GPRMC(unsigned char* latitude_char, unsigned char* longitude_char){ 
	unsigned char incomer_data = 0;
	unsigned int array_count = 0;
	latitude_char = (unsigned char*)malloc(11 * sizeof(unsigned char));
	longitude_char= (unsigned char*)malloc(12 * sizeof(unsigned char));
	while (1) {																			//keep loping till you reach the desired NMEA Sentence
		incomer_data = UartRead();													   //Check the string '$GPGGA,'
		if (incomer_data == '$') {                                                      // First statement of the GPS data start with a $ sign
			incomer_data = UartRead();                                                // If the first if become true then the next phase
			if (incomer_data == 'G') {
				incomer_data = UartRead();
				if (incomer_data == 'P') {
					incomer_data = UartRead();
					if (incomer_data == 'R') {
						incomer_data = UartRead();
						if (incomer_data == 'M') {
							incomer_data = UartRead();
							if (incomer_data == 'C') {
								incomer_data = UartRead();
								if (incomer_data == ',') {                                   // first , received
									incomer_data = UartRead();                             // At this stage Final check in done, GPRMC is found.
									while (incomer_data != ',') {                         // skipping GMT Time
										incomer_data = UartRead();
									}
									incomer_data = UartRead();
									while (incomer_data != ',') {                         // skipping next part curently 'A'
										incomer_data = UartRead();
									}

									incomer_data = UartRead();
									latitude_char[0] = incomer_data;
									while (incomer_data != ',') {
										for (array_count = 1; incomer_data != 'N' && incomer_data != 'S'; array_count++) {
											incomer_data = UartRead();
											latitude_char[array_count] = incomer_data;             // Store the Latitude data latitude_char={"2690.9416,N"}
										}
										lcd_write_line(latitude_char);
										//(*longitude) = strtod(longitude_char, NULL);            //convert char to double or  float
										//if (incomer_data == 'S') (*longitude) *= -1;
										incomer_data = UartRead();
										if (incomer_data == ',') {
											for (array_count = 0; incomer_data != 'E' && incomer_data != 'W'; array_count++) {
												incomer_data = UartRead();
												longitude_char[array_count] = incomer_data;        // Store the Longitude data longitude_char={"07547.8441,E"}
											}
										}
										lcd_write_line(longitude_char);
										/*(*latitude) = strtod(latitude_char, NULL);
										if (incomer_data == 'W') (*latitude) *= -1;*/
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