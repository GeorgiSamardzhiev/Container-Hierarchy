#include "String.h"

void String::setValue(Object * other) {
	object = ((String*)other)->object;
}

bool String::read(std::istringstream & in) {
	in >> object;
	return in.good();
}

bool String::writeLine(std::ostream & out) {
	out << ' ' << object;
	return out.good();
}

int String::compare(Object * other) {
	int diff = this->getControlNumber()-other->getControlNumber();
	if (diff == 0) {
		return ((String*)other)->object.compare(object);
	}
	return  diff;

}
