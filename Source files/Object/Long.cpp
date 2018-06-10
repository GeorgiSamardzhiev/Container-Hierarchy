#include "Long.h"

void Long::setValue(Object * other) {
	object = ((Long*)other)->object;
}

bool Long::read(std::istringstream & in) {
	in >> object;
	return in.good();
}

bool Long::writeLine(std::ostream & out) {
	out << ' ' << object;
	return out.good();
}

int Long::compare(Object * other) {
	if (((Long*)other)->object == object) {
		return 0;
	} else if (((Long*)other)->object > object) {
		return -1;
	} else {
		return 1;
	}
}
