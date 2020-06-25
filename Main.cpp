#include "pch.h"
#include <iostream>
#include <thread>
#include <fstream>
#include <vector>
#include <string>
#include <future>
#include "Quicksort.h"
#include "BubbleSort.h"
#include "Heapsort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "Swap.h"

//sortTest() will add all the scores into here, main will average it and reset it
float qsAverageScore;
float bsAverageScore;
float hsAverageScore;
float isAverageScore;
float msAverageScore;

//a score that tells you how well your computer did
float finalScore;

std::vector<int> getList(int n, int to, int testNum) { //puts values from a text file into a vector
	std::ifstream in;
	in.open("Lists\\" + std::to_string(n) + '_' + std::to_string(to) + '_' + std::to_string(testNum) + ".txt");

	std::vector<int> v;
	int element;

	if (in.is_open()) {
		int i = 0;
		while (in >> element) {
			v.push_back(element);
		}
	}

	in.close();

	return v;
}


void sortTest(int n, int to, int testNum) { //runs test on all 5 algorithms on their own threads

	std::vector<int> sortThis = getList(n, to, testNum);

	Quicksort qs;
	BubbleSort bs;
	Heapsort hs;
	InsertionSort is;
	MergeSort ms;

	//copies of the unsorted vector for each to work on
	std::vector<int> qs_vec = sortThis;
	std::vector<int> bs_vec = sortThis;
	std::vector<int> hs_vec = sortThis;
	std::vector<int> is_vec = sortThis;
	std::vector<int> ms_vec = sortThis;

	std::future<int> qsFtr = std::async(std::launch::async,
		&Quicksort::quickSort, qs, std::ref(qs_vec), 0, n - 1);
	std::future<int> bsFtr = std::async(std::launch::async,
		&BubbleSort::bubbleSort, bs, std::ref(bs_vec));
	std::future<int> hsFtr = std::async(std::launch::async,
		&Heapsort::heapSort, hs, std::ref(hs_vec));
	std::future<int> isFtr = std::async(std::launch::async,
		&InsertionSort::insertionSort, is, std::ref(is_vec));
	std::future<int> msFtr = std::async(std::launch::async,
		&MergeSort::mergeSort, ms, std::ref(ms_vec));

	//when all threads are complete, get the time taken from each
	if (qsFtr.valid() || bsFtr.valid() || hsFtr.valid() || isFtr.valid() || msFtr.valid()) {
		qsAverageScore += qsFtr.get();
		bsAverageScore += bsFtr.get();
		hsAverageScore += hsFtr.get();
		isAverageScore += isFtr.get();
		msAverageScore += msFtr.get();
	}
}

//Large inputs take too long with Bubble and Insetion Sort
void sortTestFast(int n, int to, int testNum) {

	std::vector<int> sortThis = getList(n, to, testNum);

	Quicksort qs;
	Heapsort hs;
	MergeSort ms;

	//copies of the unsorted vector for each to work on
	std::vector<int> qs_vec = sortThis;
	std::vector<int> hs_vec = sortThis;
	std::vector<int> ms_vec = sortThis;

	std::future<int> qsFtr = std::async(std::launch::async,
		&Quicksort::quickSort, qs, std::ref(qs_vec), 0, n - 1);
	std::future<int> hsFtr = std::async(std::launch::async,
		&Heapsort::heapSort, hs, std::ref(hs_vec));
	std::future<int> msFtr = std::async(std::launch::async,
		&MergeSort::mergeSort, ms, std::ref(ms_vec));

	//when all threads are complete, get the time taken from each
	if (qsFtr.valid() || hsFtr.valid() || msFtr.valid()) {
		qsAverageScore += qsFtr.get();
		hsAverageScore += hsFtr.get();
		msAverageScore += msFtr.get();
	}
}


//for running multiple tests and outputing the results
void runTest(int n, int to) {

	std::cout << std::to_string(n) + " Numbers, 1 to " + std::to_string(to) + "..." << '\n' << '\n';

	for (int i = 1; i <= 3; ++i) { sortTest(n, to, i); } //runs the test with 3 different data sets

	std::cout << "Quicksort: " + std::to_string(qsAverageScore / 3) + "us" << '\n';
	std::cout << "Bubble Sort: " + std::to_string(bsAverageScore / 3) + "us" << '\n';
	std::cout << "Heapsort: " + std::to_string(hsAverageScore / 3) + "us" << '\n';
	std::cout << "Insertion Sort: " + std::to_string(isAverageScore / 3) + "us" << '\n';
	std::cout << "Merge Sort: " + std::to_string(msAverageScore / 3) + "us" << '\n' << '\n';
	std::cout << "====================================================" << '\n' << '\n';

	if (n == 2000 && to == 50) {
		finalScore += (qsAverageScore / (559 * 3)); //values obtained by averaging 5 runs on my PC
		finalScore += (bsAverageScore / (3711 * 3));
		finalScore += (hsAverageScore / (530 * 3));
		finalScore += (isAverageScore / (956 * 3));
		finalScore += (msAverageScore / (860 * 3));
	}
	else { //n == 2000, to == 250
		finalScore += (qsAverageScore / (119 * 3));
		finalScore += (bsAverageScore / (3193 * 3));
		finalScore += (hsAverageScore / (195 * 3));
		finalScore += (isAverageScore / (837 * 3));
		finalScore += (msAverageScore / (802 * 3));
	}

	//reset them for the next run
	qsAverageScore = 0;
	bsAverageScore = 0;
	hsAverageScore = 0;
	isAverageScore = 0;
	msAverageScore = 0;
}

//version for the 3 fastest algorithms
void runTestFast(int n, int to) {

	std::cout << std::to_string(n) + " Numbers, 1 to " + std::to_string(to) + "..." << '\n' << '\n';

	for (int i = 1; i <= 3; ++i) { sortTestFast(n, to, i); } //runs the test with 3 different data sets

	std::cout << "Quicksort: " + std::to_string(qsAverageScore / 3) + "us" << '\n';
	std::cout << "Heapsort: " + std::to_string(hsAverageScore / 3) + "us" << '\n';
	std::cout << "Merge Sort: " + std::to_string(msAverageScore / 3) + "us" << '\n' << '\n';
	std::cout << "====================================================" << '\n' << '\n';

	if (n == 10000 && to == 100) {
		finalScore += (qsAverageScore / (981 * 3));
		finalScore += (hsAverageScore / (1042 * 3));
		finalScore += (msAverageScore / (3399 * 3));
	}
	else if (n == 10000 && to == 500) {
		finalScore += (qsAverageScore / (545 * 3));
		finalScore += (hsAverageScore / (1005 * 3));
		finalScore += (msAverageScore / (3323 * 3));
	}
	else { //n == 50000, to == 250
		finalScore += (qsAverageScore / (7968 * 3));
		finalScore += (hsAverageScore / (5839 * 3));
		finalScore += (msAverageScore / (17540 * 3));
	}

	//reset them for the next run
	qsAverageScore = 0;
	hsAverageScore = 0;
	msAverageScore = 0;
}

int main() {
	int n, to;

	std::cout << "Start! (\"us\" = microseconds)" << '\n' << '\n';

	//these will sort a total of 690,000 elements
	runTest(2000, 50);
	runTest(2000, 250);
	runTestFast(10000, 100);
	runTestFast(10000, 500);
	runTestFast(50000, 250);


	finalScore = (1/(finalScore / 19)) * 1000; //larger score = better PC
	
	std::cout << "Hardware score: " + std::to_string((int)(round(finalScore))) << '\n';

	std::cin.get(); //keeps the window open
	return 0;
}