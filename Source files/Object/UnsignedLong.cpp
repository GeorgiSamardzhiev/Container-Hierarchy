#include "UnsignedLong.h"

void UnsignedLong::setValue(Object * other) {
	object = ((UnsignedLong*)other)->object;
}

bool UnsignedLong::read(std::istringstream & in) {
	in >> object;
	return in.good();
}

bool UnsignedLong::writeLine(std::ostream & out) {
	out << ' ' << object;
	return out.good();
}

int UnsignedLong::compare(Object * other) {
	if (((UnsignedLong*)other)->object == object) {
		return 0;
	} else if (((UnsignedLong*)other)->object > object) {
		return -1;
	} else {
		return 1;
	}
}
