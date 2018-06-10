#ifndef OBJECT_H
#define OBJECT_H

#include <sstream>
#include <ostream>

class Object {
public:
	virtual bool read(std::istringstream& in) = 0;
	virtual bool writeLine(std::ostream& out) = 0;
	virtual void setValue(Object* other) = 0;
	virtual int getControlNumber() const = 0;
	virtual int compare(Object* other) = 0;
	virtual ~Object() {}
};

#endif // !OBJECT_H
