// Eduardo Carmona Gomez
// Lab #1

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Global constants for file names
const string INPUT_FILE = "input.txt";
const string OUTPUT_FILE = "output";

// Function prototypes
void readFile(vector<int>& div5, vector<int>& div9, vector<int>& others);
void printStats(const vector<int>& arr, const string& name);
void bubbleSort(vector<int>& arr);
void writeToFile(const vector<int>& div5, const vector<int>& div9, const vector<int>& others);
double calculateMedian(vector<int> arr);
double calculateAverage(const vector<int>& arr);
int calculateSum(const vector<int>& arr);

int main() {
    vector<int> div5, div9, others;
    readFile(div5, div9, others);

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Print values and statistics\n";
        cout << "2. Print sorted values\n";
        cout << "3. Quit and write to file\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            printStats(div5, "Divisible by 5");
            printStats(div9, "Divisible by 9");
            printStats(others, "Others");
            break;
        case 2:
            bubbleSort(div5);
            bubbleSort(div9);
            bubbleSort(others);
            cout << "Sorted arrays displayed.\n";
            break;
        case 3:
            writeToFile(div5, div9, others);
            cout << "Data written to " << OUTPUT_FILE << "\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}

void readFile(vector<int>& div5, vector<int>& div9, vector<int>& others) {
    ifstream file(INPUT_FILE);
    if (!file) {
        cerr << "Error opening file: " << INPUT_FILE << "\n";
        return;
    }
    int num;
    while (file >> num) {
        if (num % 5 == 0) div5.push_back(num);
        else if (num % 9 == 0) div9.push_back(num);
        else others.push_back(num);
    }
    file.close();
}

void printStats(const vector<int>& arr, const string& name) {
    cout << "\n" << name << " Numbers:\n";
    cout << "---------------------------------\n";
    if (arr.empty()) {
        cout << "No values.\n";
        return;
    }
    for (int num : arr) cout << num << " ";
    cout << "\n";
    cout << left << setw(10) << "Sum:" << calculateSum(arr) << "\n";
    cout << left << setw(10) << "Average:" << calculateAverage(arr) << "\n";
    cout << left << setw(10) << "Median:" << calculateMedian(arr) << "\n";
}

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

double calculateMedian(vector<int> arr) {
    if (arr.empty()) return 0.0;
    sort(arr.begin(), arr.end());
    int n = arr.size();
    return (n % 2 == 0) ? (arr[n / 2 - 1] + arr[n / 2]) / 2.0 : arr[n / 2];
}

double calculateAverage(const vector<int>& arr) {
    if (arr.empty()) return 0.0;
    return static_cast<double>(calculateSum(arr)) / arr.size();
}

int calculateSum(const vector<int>& arr) {
    int sum = 0;
    for (int num : arr) sum += num;
    return sum;
}

void writeToFile(const vector<int>& div5, const vector<int>& div9, const vector<int>& others) {
    ofstream file(OUTPUT_FILE);
    if (!file) {
        cerr << "Error opening file: " << OUTPUT_FILE << "\n";
        return;
    }
    auto writeArray = [&](const vector<int>& arr, const string& name) {
        file << name << " Numbers:\n";
        file << "---------------------------------\n";
        if (arr.empty()) file << "No values.\n";
        else {
            for (int num : arr) file << num << " ";
            file << "\n";
            file << left << setw(10) << "Sum:" << calculateSum(arr) << "\n";
            file << left << setw(10) << "Average:" << calculateAverage(arr) << "\n";
            file << left << setw(10) << "Median:" << calculateMedian(arr) << "\n\n";
        }
        };
    writeArray(div5, "Divisible by 5");
    writeArray(div9, "Divisible by 9");
    writeArray(others, "Others");
    file.close();
}
/*Menu:
1. Print values and statistics
2. Print sorted values
3. Quit and write to file
Enter your choice: 1

Divisible by 5 Numbers:
---------------------------------
970 135 840 470 590 155 565 675 435
Sum:      4835
Average:  537.222
Median:   565

Divisible by 9 Numbers:
---------------------------------
189 909 837 27 63
Sum:      2025
Average:  405
Median:   189

Others Numbers:
---------------------------------
232 782 681 528 883 976 516 726 809 713 296 941 724 236 1 544 361 3 321 627 816 537 219 3 424 958 4 311 29 826 43 758 121 302 728
Sum:      16979
Average:  485.114
Median:   528

Menu:
1. Print values and statistics
2. Print sorted values
3. Quit and write to file
Enter your choice: 2
Sorted arrays displayed.

Menu:
1. Print values and statistics
2. Print sorted values
3. Quit and write to file
Enter your choice: 3
Data written to output*/


