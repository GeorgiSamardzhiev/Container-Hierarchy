#include "ObjectFactory.h"

#include "Int.h"
#include "String.h"
#include "Char.h"
#include "Bool.h"
#include "Short.h"
#include "Long.h"
#include "UnsignedLong.h"
#include "Float.h"
#include "Double.h"

Object * ObjectFactory::createObject(int controlNumber) {
	switch (controlNumber) {
		case 0: return new Char();
		case 1: return new Int();
		case 2: return new String();
		case 3: return new Bool();
		case 4: return new Short();
		case 5: return new Long();
		case 6: return new UnsignedLong();
		case 7: return new Float();
		case 8: return new Double();
		default:
		{
			std::cerr << "Such type does not exist!"<<std::endl;
			return nullptr;
		}
	}
}
