#include "pch.h"
#include "MergeSort.h"
#include <vector>
#include <chrono>

MergeSort::MergeSort() {}

MergeSort::~MergeSort() {}

void MergeSort::merge(std::vector<int> &left, std::vector<int> &right, std::vector<int> &bars) {
	int nL = left.size();
	int nR = right.size();
	int leftLoop = 0, rightLoop = 0, barLoop = 0;

	while (leftLoop < nL && rightLoop < nR)	{ //merge left and right and sort them
		if (left[leftLoop] < right[rightLoop]) {
			bars[barLoop] = left[leftLoop];
			leftLoop++;
		}
		else {
			bars[barLoop] = right[rightLoop];
			rightLoop++;
		}
		barLoop++;
	}
	while (leftLoop < nL) {
		bars[barLoop] = left[leftLoop];
		leftLoop++; barLoop++;
	}
	while (rightLoop < nR) {
		bars[barLoop] = right[rightLoop];
		rightLoop++; barLoop++;
	}
}

void MergeSort::mergeSortClone(std::vector<int> &vec) {
	int nVec = vec.size();

	if (nVec <= 1) return;

	int mid = nVec / 2;

	std::vector<int> left(&vec[0], &vec[mid]);

	std::vector<int> right(&vec[mid], &vec.back());
	right.push_back(vec.back());

	mergeSortClone(left);
	mergeSortClone(right);
	merge(left, right, vec);
}

int MergeSort::mergeSort(std::vector<int> &vec) {
	std::chrono::time_point<std::chrono::system_clock> now =
		std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	int microStart = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

	int nVec = vec.size();

	if (nVec <= 1) return 0; //do nothing when the size of the subvector is 1 or 0

	int mid = nVec / 2;

	std::vector<int> left(&vec[0], &vec[mid]); //left side

	std::vector<int> right(&vec[mid], &vec.back()); //right side
	right.push_back(vec.back()); //by defult doesn't include last value, so adding it in here

	mergeSortClone(left); //split the left and right sides further
	mergeSortClone(right);
	merge(left, right, vec); //sorting occurs here

	now = std::chrono::system_clock::now();
	duration = now.time_since_epoch();
	int microEnd = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

	return (microEnd - microStart);
}