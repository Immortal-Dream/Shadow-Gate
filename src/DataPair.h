#pragma once
/*
* template class for a data pair of two data types
*/

template <typename T1,typename T2>
class DataPair
{
private:
	T1 firstData;
	T2 secondData;
public:
	// construct a new data pair
	DataPair(T1 first, T2 second) :firstData(first), secondData(second) {

	}
	T1 getFirst() {
		return firstData;
	}
	void setFirst(T1 first) {
		firstData = first;
	}

	T2 getSecond() {
		return secondData;
	}
	void setSecond(T2 second) {
		secondData = second;
	}
};

