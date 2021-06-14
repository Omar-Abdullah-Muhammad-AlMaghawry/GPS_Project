int number_f2s(double number, char *char_array) {
	int whole_count = 0, array_count = 0;
	double temp, remainder, digit;
	bool flag = true;
	remainder = number;
	while (flag) {
		remainder = number / pow(10, whole_count);
		/*printf("%f", remainder);
		printf("\n");*/
		temp = (int)remainder;
		if (!(temp >= 0 && temp <= 9)) {
			whole_count++;
		}
		else {
			flag = false;
			whole_count++;
		}
	}
	temp = number;
	for (int i = 0; i < whole_count + 6; i++) {
		if (array_count == whole_count) {
			char_array[array_count] = '.';
			array_count++;
			i--;
		}
		else {
			remainder = fmod(temp, pow(10, whole_count - 1 - i));
			digit = temp - remainder;
			temp = remainder;
			digit /= pow(10, whole_count - 1 - i);
			/*printf("%f", digit);
			printf("\n");*/
			char_array[array_count] = (int)digit + '0';
			array_count++;
		}
	}
}