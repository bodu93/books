long switch2(long x) {
	long val = 0;
	switch (x) {
		case 0:
			val = 1;
			break;

		case 1:
			val = 2;
			break;

		case 2:
			val = 3;
			break;

		case 3:
			val = 5;
			break;

		case 5:
			val = 11;
			break;

		case 4:
			val = 12;
			break;

		case 1000:
			val = 1023;
			break;

		default:
			val = 0;
	}

	return val;
}
