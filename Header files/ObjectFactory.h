#ifndef CONTAINERFACTORY_H
#define CONTAINERFACTORY_H

#include<iostream>

#include "Object.h"

class ObjectFactory{
public:
	static Object* createObject(int controlNumber);
};

#endif // !CONTAINERFACTORY_H
