#include "QueueContainer.h"

void QueueContainer::split(QueueContainer & l1, QueueContainer & l2) {
	QueueContainer* addNow = &l1, *addLater = &l2;
	for (std::list<T>::iterator it = begin(); it != end(); ++it) {
		addNow->push(*it);
		std::swap(addNow, addLater);
	}
}

void QueueContainer::merge(std::list<T>& l1, std::list<T>& l2) {
	iterator it1 = l1.begin(), it2 = l2.begin();
	while (it1 != l1.end() && it2 != l2.end()) {
		if ((*it1)->compare(*it2) < 0) {
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

void QueueContainer::clean() {
	for (std::list<Object*>::iterator iter = begin(); iter != end(); ++iter) {
		delete (*iter);
	}
	clear();
}

bool QueueContainer::member(T const & x) {
	for (iterator it = begin(); it!=end(); ++it) {
		if ((*it)->getControlNumber() == x->getControlNumber()&&(*it)->compare(x) == 0) {
			return true;
		}
	}
	return false;
}

bool QueueContainer::hasMemberPredicate(Condition c) {
	for (iterator it = begin(); it!=end(); ++it) {
		if (c(*it)) {
			return true;
		}
	}
	return false;
}

void QueueContainer::filter(Condition c) {
	for (iterator it = begin(); it!=end(); ++it) {
		if (!c(*it)) {
			std::list<T>::erase(it);
			it = begin();
			if (empty()) {
				return;
			}
		}
	}
}

std::ostream & QueueContainer::print(std::ostream & os) {
	if (empty()) {
		os<<"q"<<' ';
	} else {
		os<<"q"<<' '<<top()->getControlNumber();
		for (iterator it = begin(); it!=end(); ++it) {
			(*it)->writeLine(os);
		}
	}
	return os<<std::endl;
}

void QueueContainer::push(const T & el) {
	Object* newObject = ObjectFactory::createObject((el)->getControlNumber());
	newObject->setValue(el);
	std::list<T>::push_back(newObject);
}

bool QueueContainer::empty() {
	return std::list<T>::empty();
}

T QueueContainer::front() {
	return std::list<T>::front();
}

size_t QueueContainer::size() {
	return std::list<T>::size();
}

void QueueContainer::insert(T const & x, std::list<T>::iterator iter) {
	this->push(x);
}

void QueueContainer::erase(std::list<T>::iterator iter) {
	this->pop();
}

T QueueContainer::get(std::list<T>::iterator iter) {
	return this->top();
}

void QueueContainer::pop() {
	delete front();
	std::list<T>::pop_front();
}

T QueueContainer::top() {
	return front();
}

int QueueContainer::getType() const {
	return 1;
}

abstractIterator * QueueContainer::my_begin() {
	return new QueueIterator(*this);
}

abstractIterator * QueueContainer::my_end() {
	QueueIterator* qi = new QueueIterator(*this);
	qi->iter = end();
	return qi;
}

void QueueContainer::sort() {
	if (size() == 0 || size() == 1) {
		return;
	}
	QueueContainer l1, l2;
	split(l1, l2);
	clean();
	l1.sort();
	l2.sort();

	merge(l1, l2);
}

QueueContainer::~QueueContainer() {
	clean();
}

QueueContainer::QueueIterator::QueueIterator(QueueContainer & sc) {
	iter = sc.begin();
	this->sc = &sc;
}

T & QueueContainer::QueueIterator::operator*() {
	return *iter;
}

abstractIterator * QueueContainer::QueueIterator::operator++() {
	++iter;
	if (!sc->empty()) {
		sc->pop();
	}
	return (this);
}

bool QueueContainer::QueueIterator::hasNext() {
	return std::next(iter) != sc->end();
}

QueueContainer::QueueIterator::operator bool() {
	return iter != sc->end();
}
