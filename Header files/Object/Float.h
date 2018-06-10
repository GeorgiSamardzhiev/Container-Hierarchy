#ifndef FLOAT_H
#define FLOAT_H

#include "Object.h"

class Float : public Object {
private:
	float object;
public:
	Float(float number = 0) : object(number) {}

	void setValue(Object* other);
	bool read(std::istringstream & in);
	bool writeLine(std::ostream & out);
	int getControlNumber() const { return 7; }
	int compare(Object* other);
};

#endif // !FLOAT_H
