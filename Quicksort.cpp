#include "pch.h"
#include "Quicksort.h"
#include "Swap.h"
#include <vector>
#include <chrono>

Quicksort::Quicksort() {}

Quicksort::~Quicksort() {}

int Quicksort::partition(std::vector<int> &vec, int low, int high) {
	Swap sp;

	int pivot = vec[high]; //pivot, the last value gave best results
	int i = (low - 1);  //index of smaller element

	for (int j = low; j <= high - 1; j++) { //moves the elements and returns the pivot location
		if (vec[j] <= pivot) {
			i++;
			sp.swap(&vec[i], &vec[j]);
		}
	}
	sp.swap(&vec[i + 1], &vec[high]);
	return (i + 1);
}

void Quicksort::quickSortClone(std::vector<int> &vec, int low, int high) {

checkpoint:
	if (low < high) {
		int pi = partition(vec, low, high);

		if (pi < (low + high) / 2) {
			quickSortClone(vec, low, pi - 1);
			low = pi + 1; goto checkpoint;
		}
		else {
			quickSortClone(vec, pi + 1, high);
			high = pi - 1; goto checkpoint;
		}
	}
}

int Quicksort::quickSort(std::vector<int> &vec, int low, int high) {
	std::chrono::time_point<std::chrono::system_clock> now =
		std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	int microStart = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

checkpoint: //used to solve stack overflow issue at 10,000 and 50,000 elements
	if (low < high) {
		int pi = partition(vec, low, high); //pivot

		if (pi < (low + high)/2) {
			quickSortClone(vec, low, pi - 1);
			low = pi + 1; goto checkpoint;
		}
		else {
			quickSortClone(vec, pi + 1, high);
			high = pi - 1; goto checkpoint;
		}
	}

	now = std::chrono::system_clock::now();
	duration = now.time_since_epoch();
	int microEnd = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

	return (microEnd - microStart);
}