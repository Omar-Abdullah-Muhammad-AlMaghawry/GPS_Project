void convert_double(double *number) {
	double fraction;
	*number = *number / (double)100;
	fraction = *number - (int)*number;
	fraction /= 0.6;
	*number = (int)*number + fraction;
}