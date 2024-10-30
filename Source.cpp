#include <iostream>
#include <tuple>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <utility> // for swap function


using namespace std;

tuple<int, int> BubbleSort(int figures[], int n)
{
	int swaps = 0;
	int comparisons = 0;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			comparisons++;
			if (figures[j] > figures[j + 1]) {
				swap(figures[j], figures[j + 1]);
				swaps++;
			}
		}
	}
	return make_tuple(swaps, comparisons);
}


tuple<int, int> SelectionSort(int figures[], int n)
{
	int swaps = 0;
	int comparisons = 0;

	for (int i = 0; i < n - 1; i++)
	{
		int small = i;
		for (int j = i + 1; j < n; j++)
		{
			comparisons++;
			if (figures[j] < figures[small])
				small = j;
		}
		if (small != i) 
		{
			swap(figures[i], figures[small]);
			swaps++;
		}
	}
	return make_tuple(swaps, comparisons);
}


tuple<int, int> InsertionSort(int figures[], int n)
{
	int swaps = 0;
	int comparisons = 0;
	for (int i = 1; i < n; i++)
	{
		int temp = figures[i];  // save element
		int j = i - 1;

		// shift array
		while (j >= 0 && figures[j] > temp) {
			figures[j + 1] = figures[j]; // shift to left
			j--;
			swaps++; 
			comparisons++; 
		}
		figures[j + 1] = temp; // insert selected element on right place
		swaps++; 
		
	}
	return make_tuple(swaps, comparisons);
}


tuple<int, int> InsertionWithBinarySearchSort(int figures[], int n)
{
	// the upgraded version of insertion sort
	int swaps = 0;
	int comparisons = 0;

	for (int i = 1; i < n; ++i)
	{
		int selected = figures[i];

		int low = 0, high = i - 1;
		while (high > low)
		{
			comparisons++;
			int mid = (low + high) / 2; // try to divive into half

			if (selected == figures[mid])
			{
				mid += 1;
				break;
			}
			if (selected > figures[mid])
				low = mid + 1; // continue in right half
			else
				high = mid; // continue in left half
		}

		// location where put in element
		int loc = (selected > figures[low]) ? (low + 1) : low;

		// move all elements by 1 step ahead
		int j = i - 1; // start with element before selected element
		while (j >= loc)
		{
			figures[j + 1] = figures[j]; // shift element to left
			j--;
			swaps++;
		}

		figures[loc] = selected; // insert selected element on the right place
		swaps++;
	}
	return make_tuple(swaps, comparisons);
}


tuple<int, int> ShakerSort(int figures[], int n)
{
	// the upgraded version of bubble sort
	int swaps = 0;
	int comparisons = 0;

	int left = 0, right = n - 1;

	while (left <= right) {
		// left to right
		for (int i = left; i < right; i++) {
			if (figures[i] > figures[i + 1]) {
				swap(figures[i], figures[i + 1]);
			}
		}
		right--;

		// right to left
		for (int j = right; j > left; j--) {
			if (figures[j] < figures[j - 1]) {
				swap(figures[j], figures[j - 1]);
			}
		}
		left++;
	}
	return make_tuple(swaps, comparisons);
}


tuple<int, int> ShellSort(int figures[], int n)
{
	// variety of insertion sort
	int swaps = 0;
	int comparisons = 0;

	int interval = n / 2;

	while (interval > 0)
	{
		for (int i = interval; i < n; i++) {
			int temp = figures[i]; // save element
			int j = i - interval;

			// shift to right size to insert temp element
			while (j >= 0 && figures[j] > temp) {
				figures[j + interval] = figures[j]; // shift
				j -= interval; 
				swaps++;
				comparisons++;
			}
			figures[j + interval] = temp; // insert temp element
			swaps++;
		}
		interval /= 2; // dicrease interval to divide into more 2^n parts
	}
	return make_tuple(swaps, comparisons);
}


void MaxHeapify(int* figures, int n, int index, int& swaps, int& comparisons) {
	int left = 2 * index + 1;  
	int right = 2 * index + 2; 
	int maxIndex = index; // starting max value (root)

	comparisons++;
	if (left < n && figures[left] > figures[maxIndex])
		maxIndex = left;

	comparisons++;
	if (right < n && figures[right] > figures[maxIndex])
		maxIndex = right;

	comparisons++;
	// if max value isn't root: exchange and continue recover heap
	if (maxIndex != index) {
		swaps++;
		swap(figures[maxIndex], figures[index]); // exchange
		MaxHeapify(figures, n, maxIndex, swaps, comparisons); 
	}
}


void BuildMaxHeap(int* figures, int n, int& swaps, int& comparisons) {
	// indexes for heap bulding start with n/2 - 1
	for (int i = n / 2 - 1; i >= 0; i--) {
		MaxHeapify(figures, n, i, swaps, comparisons);
	}
}


tuple<int, int> HeapSort(int figures[], int n) {
	int swaps = 0;
	int comparisons = 0;
	BuildMaxHeap(figures, n, swaps, comparisons); 

	// start sort
	for (int i = n - 1; i >= 1; i--) {
		swap(figures[0], figures[i]); // move max value to the end
		swaps++;
		MaxHeapify(figures, i, 0, swaps, comparisons); 
	}
	return make_tuple(swaps, comparisons);
}


void QuickSortOptional(int* figures, int left, int right, int& swaps, int& comparisons)
{
	int l = left, r = right;
	int piv = figures[(l + r) / 2]; // pivot element

	while (l <= r) {
		while (figures[l] < piv) {
			comparisons++; 
			l++;
		}
		comparisons++;

		while (figures[r] > piv) {
			comparisons++; 
			r--;
		}
		comparisons++;

		if (l <= r) {
			swap(figures[l], figures[r]);
			swaps++; 
			l++;
			r--;
		}
	}

	// sort subarrays
	if (left < r) {
		QuickSortOptional(figures, left, r, swaps, comparisons);
	}
	if (l < right) {
		QuickSortOptional(figures, l, right, swaps, comparisons);
	}
}


tuple<int, int> QuickSort(int figures[], int n)
{
	int swaps = 0;
	int comparisons = 0;
	QuickSortOptional(figures, 0, n - 1, swaps, comparisons);
	return make_tuple(swaps, comparisons);
}


void readFromFile(const string& filename, int* figures) {
	ifstream inputFile(filename);
	if (!inputFile) {
		cerr << "Error: don't manage to open file - " << filename << endl;
		return;
	}

	int number;
	int count = 0; 
	while (inputFile >> number && count < 200) {
		figures[count++] = number; 
	}

	inputFile.close();
}


string ChooseFile()
{
	int choice_file = 0;
	string filename;

	while (choice_file != 1 && choice_file != 2)
	{
		cout << "Choose file:" << endl;
		cout << "1 - file, where sorted numbers" << endl;
		cout << "2 - file, where reverse sorted numbers" << endl;
		cin >> choice_file;

		switch (choice_file)
		{
			case 1: {
				filename = "sortedNumbers.txt";
				break;
			}
			case 2: {
				filename = "reverseSortedNumbers.txt";
				break;
			}
			default:
				cout << "Try again! Invalid number!" << endl;
		}
	}
	return filename;
}


void readFromInput(int* figures) {
	cout << "Enter numbers (enter 'end' to end) [up to 200 numbers]: " << endl;
	string input;
	int count = 0; 

	while (count < 200) {
		cin >> input;
		if (input == "end") {
			break;
		}

		try {
			figures[count++] = stoi(input); // str to int
		}
		catch (invalid_argument&) {
			cout << "Invalid Enter: Enter figure or 'end' for ending." << endl;
		}
	}

	if (count < 200) {
		cout << "< 200 figures";
		exit(1);
	}
}


void readRandomValues(int* figures, int n) {
	random_device rd; 
	mt19937 gen(rd()); 
	uniform_int_distribution<> distrib(0, 1000); 

	for (int i = 0; i < n; ++i) {
		figures[i] = distrib(gen); // fill in random values
	}
}


void displayArray(int* figures, int n, tuple<int, int> swapsComparisons) {
	for (int i = 0; i < n; i++) {
		cout << figures[i] << " "; 
	}
	cout << endl;
	cout << "swaps: " << get<0>(swapsComparisons) << endl;
	cout << "comparisons: " << get<1>(swapsComparisons) << endl;
	cout << endl;
}


void ChooseSortingAlgorithm(int* figures, int n)
{
	int choice;
	do {
		cout << "\nSorting alghoritms:\n";
		cout << "1 - Bubble Sort\n";
		cout << "2 - Selection Sort\n";
		cout << "3 - Insertion Sort\n";
		cout << "4 - Insertion Sort with Binary Search\n";
		cout << "5 - Shaker Sort\n";
		cout << "6 - Shell Sort\n";
		cout << "7 - Heap Sort\n";
		cout << "8 - Quick Sort\n";
		cout << "0 - Exit\n";
		cout << "Choose sorting alghoritm (0-8): ";
		cin >> choice;

		int* tempArr = new int[n];
		tuple<int, int> swapsComparisons = { 0, 0 };
		copy(figures, figures + n, tempArr);

		switch (choice) {
		case 1: {
			cout << "Before Bubble Sort: ";
			displayArray(figures, n, swapsComparisons);
			swapsComparisons = BubbleSort(tempArr, n);
			cout << "After Bubble Sort: ";
			displayArray(tempArr, n, swapsComparisons);
			break;
		}
		case 2: {
			cout << "Before Selection Sort: ";
			displayArray(figures, n, swapsComparisons);
			swapsComparisons = SelectionSort(tempArr, n);
			cout << "After Selection Sort: ";
			displayArray(tempArr, n, swapsComparisons);
			break;
		}
		case 3: {
			cout << "Before Insertion Sort: ";
			displayArray(figures, n, swapsComparisons);
			swapsComparisons = InsertionSort(tempArr, n);
			cout << "After Insertion Sort: ";
			displayArray(tempArr, n, swapsComparisons);
			break;
		}
		case 4: {
			cout << "Before Insertion Sort with Binary Search: ";
			displayArray(figures, n, swapsComparisons);
			swapsComparisons = InsertionWithBinarySearchSort(tempArr, n);
			cout << "After Insertion Sort with Binary Search: ";
			displayArray(tempArr, n, swapsComparisons);
			break;
		}
		case 5: {
			cout << "Before Shaker Sort: ";
			displayArray(figures, n, swapsComparisons);
			swapsComparisons = ShakerSort(tempArr, n);
			cout << "After Shaker Sort: ";
			displayArray(tempArr, n, swapsComparisons);
			break;
		}
		case 6: {
			cout << "Before Shell Sort: ";
			displayArray(figures, n, swapsComparisons);
			swapsComparisons = ShellSort(tempArr, n);
			cout << "After Shell Sort: ";
			displayArray(tempArr, n, swapsComparisons);
			break;
		}
		case 7: {
			cout << "Before Heap Sort: ";
			displayArray(figures, n, swapsComparisons);
			swapsComparisons = HeapSort(tempArr, n);
			cout << "After Heap Sort: ";
			displayArray(tempArr, n, swapsComparisons);
			break;
		}
		case 8: {
			cout << "Before Quick Sort: ";
			displayArray(figures, n, swapsComparisons);
			swapsComparisons = QuickSort(tempArr, n);
			cout << "After Quick Sort: ";
			displayArray(tempArr, n, swapsComparisons);
			break;
		}
		case 0:
			cout << "Exit from the program." << endl;
			break;
		default:
			cout << "Invalid choice. Try again." << endl;
		}
		delete[] tempArr; // free memory
	} while (choice != 0);
}


void DoChoice(int* figures, int n)
{
	int choice;

	do {
		cout << "Choose action:" << endl;
		cout << "1. Read values from file" << endl;
		cout << "2. Read values from keyboard" << endl;
		cout << "3. Random values" << endl;
		cout << "0. Exit" << endl;
		cout << "Enter your choice (0-3): ";
		cin >> choice;

		switch (choice) {
		case 1: {
			string filename = ChooseFile();
			readFromFile(filename, figures);
			ChooseSortingAlgorithm(figures, n);
			break;
		}
		case 2:
			readFromInput(figures);
			ChooseSortingAlgorithm(figures, n);
			break;
		case 3:
			readRandomValues(figures, n);
			ChooseSortingAlgorithm(figures, n);
			break;
		case 0: {
			cout << "Exit from program." << endl;
			break;
		}
		default:
			cout << "Invalid choice. Try again." << endl;
			break;
		}
	} while (choice != 0);
}


int main() {
	int n = 200;
	int figures[200];

	DoChoice(figures, n);
	return 0;
}
