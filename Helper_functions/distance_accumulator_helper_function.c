#include "TM4C123GH6PM.h"
#include <stdlib.h>
#include <stdio.h>
#include "lcd_driver.h"
#include "get_distance.c"
#include "GPRMC.c"

#define GPIO_PF_2 									(7<<1);
#define GPIO_PORTF_DIR_R 						0x40025400;
#define GPIO_PORTF_UNLOCK 					0x4C4F434B;

int GPIO_PORTF_CR_R = 0x40025524;


/* configure GPIO port F */
void LEDInit() {
	SYSCTL->RCGCGPIO |= (1 << 5);							// enable clock for port F
	while ((SYSCTL->RCGCGPIO & (1 << 5)) == 0) {}		// wait until port F is enabled
	GPIOF->LOCK = GPIO_PORTF_UNLOCK;		// unlock port F
	GPIO_PORTF_CR_R |= GPIO_PF_2;						// commit changes to port F
	GPIOF->AMSEL = 0x00000000;					// disable analog functions
	GPIOF->PCTL &= 0x00000000;					// clear PCTL bits for port F
	GPIOF->AFSEL &= ~GPIO_PF_2;					// disable AFSEL for (PF2)
	GPIOF->DIR = GPIO_PF_2;						// setting direction
	GPIOF->DEN = GPIO_PF_2;						// enable digital mode
	GPIOF->DATA |= (1 << 1);							// enable red LED
}

/* configering GPTM */
void GPTMInit() {
	SYSCTL->RCGCTIMER |= (1 << 0);							// enable clock fro timerA0
	TIMER0->CTL &= !(1 << 0);							// disable timerA0 from control register
	TIMER0->CFG = 0x00000000;					// write configuration register for timerA0
												/* configure timerA0 mode register */
	TIMER0->TAMR |= (0x2 << 0);						// sets the timer to periodic mode
	TIMER0->TAMR |= (1 << 4);							// sets the counter to count down
	TIMER0->TAILR = 0x10;								// set load value for timerA0 // 0x00F42400(1 sec); // 0x3D09000(4 secs); // 0x140
	TIMER0->CTL |= (1 << 0);							// enable timerA0 from control register
}


/* void coordinates_parser(float* longitude, float* latitude, char input[]) {
unsigned char incomer_data = 0;
unsigned int array_count = 0;
char latitude_char[9];
char longitude_char[10];
int i = 0;
float f = 1.1110023;
while (1) {																			//keep loping till you reach the desired NMEA Sentence
incomer_data = input[i++];													   //Check the string '$GPGGA,'
if (incomer_data == '$') {                                                      // First statement of the GPS data start with a $ sign
incomer_data = input[i++];                                                // If the first if become true then the next phase
if (incomer_data == 'G') {
incomer_data = input[i++];
if (incomer_data == 'P') {
incomer_data = input[i++];
if (incomer_data == 'G') {
incomer_data = input[i++];
if (incomer_data == 'G') {
incomer_data = input[i++];
if (incomer_data == 'A') {
incomer_data = input[i++];
if (incomer_data == ',') {                                   // first , received
incomer_data = input[i++];                             // At this stage Final check in done, GPGGA is found.
while (incomer_data != ',') {                         // skipping GMT Time
incomer_data = input[i++];
}
incomer_data = input[i++];
latitude_char[0] = incomer_data;
if (incomer_data != ',') {
for (array_count = 1; incomer_data != 'N' && incomer_data != 'S'; array_count++) {
incomer_data = input[i++];
latitude_char[array_count] = incomer_data;             // Store the Latitude data
}
f = (float)strtof(latitude_char, NULL);
*latitude = f;            //convert char to double or  float
if (incomer_data == 'S') (*latitude) *= -1;
incomer_data = input[i++];
if (incomer_data == ',') {
for (array_count = 0; incomer_data != 'E' && incomer_data != 'W'; array_count++) {
incomer_data = input[i++];
longitude_char[array_count] = incomer_data;        // Store the Longitude data
}
}
(*longitude) = strtod(longitude_char, NULL);
if (incomer_data == 'W') (*longitude) *= -1;
break;
}
}
}

}
}
}
}
}
}
} */

int DistanceAccumulator() {
	int first_time = 0;


	/*
	// will be deleted!!!
	int c = 0;
	char cc;
	*/

	float accumulated_distance = 0, old_longitude, old_latitude;
	float *longitude, *latitude;
	/*char text[16];
	lcd_init();
	lcd_select_line(1);
	lcd_write_line("Test accumulator"); */
	while (accumulated_distance < 100) {
		if ((TIMER0->RIS & 0x00000001) == 1) {
			/*char input[] = "$GPGGA,141848.00,2237.63306,N,08820.86316,E,1,03,2.56,1.9,M,-54.2, M,,*74";*/
			if (first_time == 0) {
				/*coordinates_parser(longitude, latitude, input);*/
				coordinates_parser(longitude, latitude);
				first_time = first_time + 1;
			}
			else {
				old_longitude = *longitude;
				old_latitude = *latitude;


				// will be deleted 
				c = input[20] - '0';
				c = c + 1;
				cc = c + '0';
				input[20] = cc;


				/*coordinates_parser(longitude, latitude, input);*/
				coordinates_parser(longitude, latitude);
				accumulated_distance = get_distance(old_longitude, old_latitude, *longitude, *latitude) + accumulated_distance;
				if (accumulated_distance < 100) {
					// periodic printing on LCD
					sprintf(text, "%d", (int)(accumulated_distance * 100));
					text[3] = text[2];
					text[2] = text[1];
					text[1] = '.';
					lcd_select_line(3);
					lcd_write_line(text);
				}
				else if (accumulated_distance >= 100) {
					GPIOF->DATA &= ~(1 << 1);				// turn off red LED
					GPIOF->DATA |= (1 << 2);				// turn on blue LED
				}
				TIMER0->ICR |= (1 << 0);
			}
		}
	}

	return 0;
}

int main() {
	return 0;
}
void SystemInit() {
	LEDInit();
	GPTMInit();
	DistanceAccumulator();
}
