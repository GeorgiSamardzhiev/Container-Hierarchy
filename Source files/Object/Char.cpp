#include "Char.h"

void Char::setValue(Object * other) {
	object = ((Char*)other)->object;
}

bool Char::read(std::istringstream & in) {
	in >> object;
	return in.good();
}

bool Char::writeLine(std::ostream & out) {
	out << ' ' << object;
	return out.good();
}

int Char::compare(Object * other) {
	if (((Char*)other)->object == object) {
		return 0;
	} else if (((Char*)other)->object > object) {
		return -1;
	} else {
		return 1;
	}
}
