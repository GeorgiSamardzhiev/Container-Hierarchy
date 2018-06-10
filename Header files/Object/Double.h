#ifndef DOUBLE_H
#define DOUBLE_H

#include "Object.h"

class Double : public Object {
private:
	double object;
public:
	Double(double number = 0) : object(number) {}

	void setValue(Object* other);
	bool read(std::istringstream & in);
	bool writeLine(std::ostream & out);
	int getControlNumber() const { return 8; }
	int compare(Object* other);

};

#endif // !DOUBLE_H
