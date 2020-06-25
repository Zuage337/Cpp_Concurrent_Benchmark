#include "pch.h"
#include "Heapsort.h"
#include "Swap.h"
#include <vector>
#include <chrono>

Heapsort::Heapsort() {}

Heapsort::~Heapsort() {}

void Heapsort::heapify(std::vector<int> &vec, int n, int i) {
	Swap sp;

	int largest = i; //initialise largest as root
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	//if left child is larger than root
	if (l < n && vec[l] > vec[largest])
		largest = l;

	//if right child is larger than largest so far
	if (r < n && vec[r] > vec[largest])
		largest = r;

	//if largest is not root
	if (largest != i) {
		sp.swap(&vec[i], &vec[largest]);

		heapify(vec, n, largest);
	}
}

int Heapsort::heapSort(std::vector<int> &vec) {
	std::chrono::time_point<std::chrono::system_clock> now =
		std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	int microStart = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

	Swap sp;
	int n = vec.size();

	//build heap (rearrange array)
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(vec, n, i);
	}

	//one by one extract an element from heap
	for (int i = n - 1; i > 0; i--) {
		sp.swap(&vec[0], &vec[i]); //move current root to end 
		heapify(vec, i, 0); //call heapify on the reduced heap
	}

	now = std::chrono::system_clock::now();
	duration = now.time_since_epoch();
	int microEnd = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

	return (microEnd - microStart);
}