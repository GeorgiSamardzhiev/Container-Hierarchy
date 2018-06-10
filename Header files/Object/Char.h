#ifndef CHAR_H
#define CHAR_H

#include "Object.h"

class Char : public Object {
private:
	char object;
public:
	Char(char c = 0) : object(c) {}

	void setValue(Object * other);
	bool read(std::istringstream & in);
	bool writeLine(std::ostream & out);
	int getControlNumber() const { return 0; }
	int compare(Object * other);

};

#endif // !CHAR_H
