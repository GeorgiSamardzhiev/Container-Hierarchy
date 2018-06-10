#include "Float.h"

void Float::setValue(Object * other) {
	object = ((Float*)other)->object;
}

bool Float::read(std::istringstream & in) {
	in >> object;
	return in.good();
}

bool Float::writeLine(std::ostream & out) {
	out << ' ' << object;
	return out.good();
}

int Float::compare(Object * other) {
	if (((Float*)other)->object == object) {
		return 0;
	} else if (((Float*)other)->object > object) {
		return -1;
	} else {
		return 1;
	}
}
