#ifndef LONG_H
#define LONG_H

#include "Object.h"

class Long : public Object {
private:
	long object;
public:
	Long(long number = 0) : object(number) {}

	void setValue(Object* other);
	bool read(std::istringstream & in);
	bool writeLine(std::ostream & out);
	int getControlNumber() const { return 5; }
	int compare(Object* other);

};

#endif // !LONG_H
