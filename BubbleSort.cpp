#include "pch.h"
#include "BubbleSort.h"
#include "Swap.h"
#include <vector>
#include <chrono>

BubbleSort::BubbleSort() {}

BubbleSort::~BubbleSort() {}

int BubbleSort::bubbleSort(std::vector<int> &vec) {
	std::chrono::time_point<std::chrono::system_clock> now =
		std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	int microStart = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

	int n, i, j;
	Swap sp;
	bool swapped;

	n = vec.size();

	for (i = 0; i < n - 1; i++) { //the simplest sorting algorithm
		swapped = false;
		for (j = 0; j < n - i - 1; j++) {
			if (vec[j] > vec[j + 1]) {
				sp.swap(&vec[j], &vec[j + 1]);
				swapped = true;
			}
		}

		// No swaps in one pass = sorted
		if (swapped == false)
			break;
	}

	now = std::chrono::system_clock::now();
	duration = now.time_since_epoch();
	int microEnd = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

	return (microEnd - microStart);
}