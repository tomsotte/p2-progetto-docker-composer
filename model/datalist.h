#ifndef DATALIST_H
#define DATALIST_H

#include <list>
#include <vector>
#include <algorithm>

#include "datamodel.h"
#include "../lib/json.hpp"

template <class T>
class DataList : public DataModel
{
public:
	DataList() = default;

	DataList(const DataList& l)
	{
		from(l);
	}

	DataList& operator=(const DataList& l)
	{
		if (this != &l) from(l);
		return *this;
	}

	virtual ~DataList()
	{
		clear();
	}

	virtual void add(T t) {
		list.push_back(t);
	}

	virtual void remove(T t) {
		auto it = std::find(list.begin(), list.end(), t);

		if (it != this->end()) {
			T temp = *it;
			list.erase(it);
			delete temp;
		}
	}

	typename std::list<T>::iterator begin() {
		return list.begin();
	}

	typename std::list<T>::iterator end() {
		return list.end();
	}

	typename std::list<T>::const_iterator begin() const {
		return list.cbegin();
	}

	typename std::list<T>::const_iterator end() const {
		return list.cend();
	}

	bool empty() {
		return list.empty();
	}

	// used for deep deleting of the list
	void clear() {
		auto it = list.begin();

		T t;
		while (it != list.end()) {
			t = *it;
			it = list.erase(it); // implicit ++it, erase return next to it
			delete t;
		}
	}

	void from(const DataList& l) {
		for (const T& elem : l.list) add(elem->clone());
	}

	nlohmann::json exportToJSON() const {
		nlohmann::json j = nlohmann::json::array();

		for (const T& elem : list) {
			j.push_back(elem->exportToJSON());
		}

		return j;
	}

	virtual DataList* clone() const = 0;

protected:
	std::list<T> list;

};

#endif // DATALIST_H
