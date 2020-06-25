#include "pch.h"
#include "InsertionSort.h"
#include <vector>
#include <chrono>

InsertionSort::InsertionSort() {}

InsertionSort::~InsertionSort() {}

int InsertionSort::insertionSort(std::vector<int> &vec) {
	std::chrono::time_point<std::chrono::system_clock> now =
		std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	int microStart = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

	int i, key, j;
	int n = vec.size();

	for (i = 1; i < n; i++) {
		key = vec[i]; //key is the newest value being looked at
		j = i - 1;

		while (j >= 0 && vec[j] > key) { //while value at j is larger than the key
			vec[j + 1] = vec[j]; //move it up
			j = j - 1;
		}
		vec[j + 1] = key; //move the smaller value down
	}

	now = std::chrono::system_clock::now();
	duration = now.time_since_epoch();
	int microEnd = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

	return (microEnd - microStart);
}