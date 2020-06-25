#pragma once
#ifndef BUBBLESORT_H
#define BUBBLESORT_H
#include <vector>

class BubbleSort
{
public:
	BubbleSort();
	~BubbleSort();
	int bubbleSort(std::vector<int> &vec);
};

#endif