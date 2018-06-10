#ifndef STRING_H
#define STRING_H

#include "Object.h"

class String : public Object {
private:
	std::string object;
public:
	String(std::string str = "") : object(str) {}

	void setValue(Object* other);
	bool read(std::istringstream & in);
	bool writeLine(std::ostream & out);
	int getControlNumber() const {return 2;}
	int compare(Object* other);
};

#endif // !CHAR_H
