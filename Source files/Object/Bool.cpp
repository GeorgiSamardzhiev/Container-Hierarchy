#include "Bool.h"

void Bool::setValue(Object * other) {
	object = ((Bool*)other)->object;
}

bool Bool::read(std::istringstream & in) {
	in >> object;
	return in.good();
}

bool Bool::writeLine(std::ostream & out) {
	out << ' ' << object;
	return out.good();
}

int Bool::compare(Object * other) {
	if (((Bool*)other)->object == object) {
		return 0;
	} else if (((Bool*)other)->object == true && object == false) {
		return -1;
	} else {
		return 1;
	}
}
