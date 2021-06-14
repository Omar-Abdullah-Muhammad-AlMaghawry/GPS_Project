void cooridinates_f2s(double number, char *char_array, char mode) {
	int whole_len = 0, fraction_len = 0, floating_pos = 0, array_count = 0;
	double temp, remainder, digit;
	if (mode == 'T') {
		whole_len = 4;
		fraction_len = 5;
	}
	else if (mode == 'G') {
		whole_len = 5;
		fraction_len = 5;
	}
	temp = number;
	for (int i = 0; i < whole_len + fraction_len + 1; i++) {
		if (array_count == 2 && mode == 'T') {
			char_array[array_count] = '.';
			array_count++;
			i--;
			temp /= .60;
		}
		else if (array_count == 3 && mode == 'G') {
			char_array[array_count] = '.';
			array_count++;
			i--;
			temp /= .60;
		}
		else {
			remainder = fmod(temp, pow(10, whole_len - 1 - i));
			digit = temp - remainder;
			temp = remainder;
			digit /= pow(10, whole_len - 1 - i);
			char_array[array_count] = (int)digit + '0';
			array_count++;
		}
	}
}