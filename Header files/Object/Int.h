#ifndef INT_H
#define INT_H

#include "Object.h"

class Int: public Object {
private: 
	int object;
public:
	Int(int number = 0) : object(number) {}

	void setValue(Object* other);
	bool read(std::istringstream & in);
	bool writeLine(std::ostream & out);
	int getControlNumber() const { return 1; }
	int compare(Object* other);
};

#endif // !INT_H
