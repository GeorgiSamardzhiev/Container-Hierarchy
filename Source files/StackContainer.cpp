#include "StackContainer.h"

void StackContainer::split(StackContainer& l1, StackContainer& l2) {
	StackContainer *addNow = &l1, *addLater = &l2;
	for (std::list<T>::iterator it = begin(); it != end(); ++it) {
		addNow->push(*it);
		std::swap(addNow, addLater);
	}
}

void StackContainer::merge(StackContainer& l1, StackContainer& l2) {
	std::list<T>::iterator it1 = l1.begin(), it2 = l2.begin();
	while (it1 != l1.end() && it2 != l2.end()) {
		if ((*it1)->compare(*it2) > 0) {
			push(*it1);
			++it1;
		} else {
			push(*it2);
			++it2;
		}
	}
	while (it1 != l1.end()) {
		push(*it1);
		++it1;
	}
	while (it2 != l2.end()) {
		push(*it2);
		++it2;
	}
}

void StackContainer::clean() {
	for (std::list<Object*>::iterator iter = begin(); iter != end(); ++iter) {
		delete (*iter);
	}
	clear();
}

bool StackContainer::member(T const & x) {
	for (std::list<T>::iterator it = begin(); it!=end(); ++it) {
		if ((*it)->getControlNumber() == x->getControlNumber() && (*it)->compare(x) == 0) {
			return true;
		}
	}
	return false;
}

bool StackContainer::hasMemberPredicate(Condition c) {
	for (std::list<T>::iterator it = begin(); it!=end(); ++it) {
		if (c(*it)) {
			return true;
		}
	}
	return false;
}

void StackContainer::filter(Condition c) {
	for (std::list<T>::iterator it = begin(); it!=end(); ++it) {
		if (!c(*it)) {
			std::list<T>::erase(it);
			it = begin();
			if (empty()) {
				return;
			}
		}
	}
}

std::ostream & StackContainer::print(std::ostream & os) {
	if (empty()) {
		os<<"s"<<' ';
	} else {
		os<<"s"<<' '<<top()->getControlNumber();
		for (iterator it = begin(); it!=end(); ++it) {
			(*it)->writeLine(os);;
		}
	}
	return os<<std::endl;
}

void StackContainer::push(const T & el) {
	T newObject = ObjectFactory::createObject((el)->getControlNumber());
	newObject->setValue(el);
	push_back(newObject);
}

size_t StackContainer::size() {
	return std::list<T>::size();
}

bool StackContainer::empty() {
	return std::list<T>::empty();
}

void StackContainer::insert(T const & x, std::list<T>::iterator iter) {
	this->push(x);
}

void StackContainer::erase(std::list<T>::iterator iter) {
	this->pop();
}

T StackContainer::get(std::list<T>::iterator iter) {
	return this->top();
}

T StackContainer::top() {
	return std::list<T>::back();
}

void StackContainer::pop() {
	delete top();
	std::list<T>::pop_back();
}

int StackContainer::getType() const {
	return 0;
}

abstractIterator * StackContainer::my_begin() {
	return new StackIterator(*this);
}

abstractIterator * StackContainer::my_end() {
	StackIterator* si = new StackIterator(*this);
	si->iter = rend();
	return si;
}

void StackContainer::sort() {
	if (size() == 0 || size() == 1) {
		return;
	}
	StackContainer l1, l2;
	split(l1, l2);
	clean();
	l1.sort();
	l2.sort();
	merge(l1, l2);
}

StackContainer::~StackContainer() {
	clean();
}

StackContainer::StackIterator::StackIterator(StackContainer & sc) {
	iter = sc.rbegin();
	this->sc = &sc;
}

T & StackContainer::StackIterator::operator*() {
	return *iter;
}

abstractIterator * StackContainer::StackIterator::operator++() {
	if (!sc->empty()) {
		sc->pop();
	}
	return (this);
}

bool StackContainer::StackIterator::hasNext() {
	return std::next(iter) != sc->rend();
}

StackContainer::StackIterator::operator bool() {
	return iter != sc->rend();
}
