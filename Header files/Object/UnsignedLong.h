#ifndef UNSIGNED_LONG_H
#define UNSIGNED_LONG_H

#include "Object.h"

class UnsignedLong : public Object {
private:
	unsigned long object;
public:
	UnsignedLong(unsigned long _object = 0) : object(_object) {}

	void setValue(Object* other);
	bool read(std::istringstream & in);
	bool writeLine(std::ostream & out);
	int getControlNumber() const { return 6; }
	int compare(Object * other);

};

#endif // !UNSIGNED_LONG_H
