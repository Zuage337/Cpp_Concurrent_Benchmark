#pragma once
#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <vector>

class Quicksort
{
public:
	Quicksort();
	~Quicksort();
	int quickSort(std::vector<int> &arr, int low, int high);
private:
	void quickSortClone(std::vector<int> &arr, int low, int high);
	int partition(std::vector<int> &arr, int low, int high);
};

#endif