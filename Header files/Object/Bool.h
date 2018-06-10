#ifndef BOOL_H
#define BOOL_H

#include "Object.h"

class Bool : public Object {
private:
	bool object;
public:
	Bool(bool b = false) : object(b) {}

	void setValue(Object* other);
	bool read(std::istringstream & in);
	bool writeLine(std::ostream & out);
	int getControlNumber() const { return 3;}
	int compare(Object * other);

};

#endif // !BOOL_H
