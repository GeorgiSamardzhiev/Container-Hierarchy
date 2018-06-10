#ifndef SHORT_H
#define SHORT_H

#include "Object.h"

class Short : public Object {
private:
	short object;
public:
	Short(short number = 0) : object(number) {}

	void setValue(Object* other);
	bool read(std::istringstream & in);
	bool writeLine(std::ostream & out);
	int getControlNumber() const { return 4; }
	int compare(Object* other);

};

#endif // !Short_H
