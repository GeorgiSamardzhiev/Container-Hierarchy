#include "Short.h"

void Short::setValue(Object * other) {
	object = ((Short*)other)->object;
}

bool Short::read(std::istringstream & in) {
	in >> object;
	return in.good();
}

bool Short::writeLine(std::ostream & out) {
	out << ' ' << object;
	return out.good();
}

int Short::compare(Object * other) {
	if (((Short*)other)->object == object) {
		return 0;
	} else if (((Short*)other)->object > object) {
		return -1;
	} else {
		return 1;
	}
}
