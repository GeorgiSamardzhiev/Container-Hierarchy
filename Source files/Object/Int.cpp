#include "Int.h"

void Int::setValue(Object * other) {
	object = ((Int*)other)->object;
}

bool Int::read(std::istringstream & in) {
	in >> object;
	return in.good();
}

bool Int::writeLine(std::ostream & out) {
	out << ' ' << object;
	return out.good();
}

int Int::compare(Object * other) {
	if (((Int*)other)->object == object) {
		return 0;
	} else if (((Int*)other)->object > object) {
		return -1;
	} else {
		return 1;
	}
}
