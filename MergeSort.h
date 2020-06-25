#pragma once
#ifndef MERGESORT_H
#define MERGESORT_H
#include <vector>

class MergeSort
{
public:
	MergeSort();
	~MergeSort();
	int mergeSort(std::vector<int> &vec);
private:
	void mergeSortClone(std::vector<int> &vec);
	void merge(std::vector<int> &left, std::vector<int> &right, std::vector<int> &bars);
};

#endif