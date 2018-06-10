#include "Double.h"

void Double::setValue(Object * other) {
	object = ((Double*)other)->object;
}

bool Double::read(std::istringstream & in) {
	in >> object;
	return in.good();
}

bool Double::writeLine(std::ostream & out) {
	out << ' ' << object;
	return out.good();
}

int Double::compare(Object * other) {
	if (((Double*)other)->object == object) {
		return 0;
	} else if (((Double*)other)->object > object) {
		return -1;
	} else {
		return 1;
	}
}
