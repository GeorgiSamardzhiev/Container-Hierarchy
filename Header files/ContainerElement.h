#ifndef CONTAINERELEMENT_H
#define CONTAINERELEMENT_H

#include "ObjectFactory.h"

using T = Object*;
class abstractIterator {
public:
	virtual T& operator*() = 0;
	virtual abstractIterator* operator++() = 0;
	virtual operator bool() = 0;
	virtual bool hasNext() = 0;
	virtual ~abstractIterator() {}
};
class ContainerElement {
public:
	using Condition = bool(*)(T const&);
	
	virtual bool member(T const& x) = 0;
	virtual bool hasMemberPredicate(Condition c) = 0;
	virtual void filter(Condition c) = 0;
	virtual void sort() = 0;
	virtual std::ostream& print(std::ostream& os = std::cout) = 0;
	virtual void push(T const& x) = 0;
	virtual void pop() = 0;
	virtual T top() = 0;
	virtual bool empty() = 0;
	virtual size_t size() = 0;
	virtual int getType() const = 0;
	virtual abstractIterator* my_begin() = 0;
	virtual abstractIterator* my_end() = 0;
	virtual void insert(T const& x, std::list<T>::iterator iter) = 0;
	virtual void erase(std::list<T>::iterator iter) = 0;
	virtual T get(std::list<T>::iterator iter) = 0;
	void readLine(std::istringstream& line) {
		int controlNumber;
		line>>controlNumber;
		Object* newObject = ObjectFactory::createObject(controlNumber);
		if (empty() || top()->getControlNumber() == controlNumber) {
			while (newObject && line) {
				Object* newObject = ObjectFactory::createObject(controlNumber);
				newObject->read(line);
				if (line) {
					push(newObject);
				}
			}
		}
	}
	virtual ~ContainerElement() {}
};

#endif // !CONTAINERELEMENT_H
