#pragma once
#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H
#include <vector>

class InsertionSort
{
public:
	InsertionSort();
	~InsertionSort();
	int insertionSort(std::vector<int> &vec);
};

#endif