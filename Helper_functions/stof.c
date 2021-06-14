double stof(const char* s) {
	int rez = 0;
	double	fact = 1;
	int point_seen, d, index = 0;
	if (*s == '-') {
		s++;
		fact = -1;
	}
	for (point_seen = 0; *s != ','; s++) {
		if (*s == '.') {
			point_seen = 1;
			continue;
		}
		d = *s - '0';
		if (d >= 0 && d <= 9) {
			if (point_seen) {
				index++;
				fact /= 10.0f;
			}
			rez = rez * 10 + d;
		}
	}
	if (fact > 0) fact = ceil(fact * pow(10, index));
	else if (fact < 0) fact = floor(fact * pow(10, index));
	//fact = fact / pow(10, index);
	//fact = ceil(fact * pow(10, index)) / pow(10, index);
	return ((double)rez * pow(10, -index) * fact);
}