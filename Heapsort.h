#pragma once
#ifndef HEAPSORT_H
#define HEAPSORT_H
#include <vector>

class Heapsort
{
public:
	Heapsort();
	~Heapsort();
	int heapSort(std::vector<int> &vec);
private:
	void heapify(std::vector<int> &vec, int n, int i);
};

#endif