// Eduardo Carmona Gomez
// Lab #1

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const string INPUT_FILE = "input.txt";
const string OUTPUT_FILE = "output.txt";

const int MAX_SIZE = 1000;

void readFile(int div5[], int& size5, int div9[], int& size9, int others[], int& sizeOthers);
void printStats(const int arr[], int size, const string& name);
void bubbleSort(int arr[], int size);
void writeToFile(const int div5[], int size5, const int div9[], int size9, const int others[], int sizeOthers);
double calculateMedian(int arr[], int size);
double calculateAverage(const int arr[], int size);
int calculateSum(const int arr[], int size);

int main() {
    int div5[MAX_SIZE], div9[MAX_SIZE], others[MAX_SIZE];
    int size5 = 0, size9 = 0, sizeOthers = 0;

    readFile(div5, size5, div9, size9, others, sizeOthers);
    
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
                printStats(div5, size5, "Divisible by 5");
                printStats(div9, size9, "Divisible by 9");
                printStats(others, sizeOthers, "Others");
                break;
            case 2:
                bubbleSort(div5, size5);
                bubbleSort(div9, size9);
                bubbleSort(others, sizeOthers);
                cout << "Sorted arrays displayed.\n";
                break;
            case 3:
                writeToFile(div5, size5, div9, size9, others, sizeOthers);
                cout << "Data written to " << OUTPUT_FILE << "\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);
    
    return 0;
}

void readFile(int div5[], int& size5, int div9[], int& size9, int others[], int& sizeOthers) {
    ifstream file(INPUT_FILE);
    if (!file) {
        cerr << "Error opening file: " << INPUT_FILE << "\n";
        return;
    }
    int num;
    while (file >> num) {
        if (num % 5 == 0) div5[size5++] = num;
        else if (num % 9 == 0) div9[size9++] = num;
        else others[sizeOthers++] = num;
    }
    file.close();
}

void printStats(const int arr[], int size, const string& name) {
    cout << "\n" << name << " Numbers:\n";
    cout << "---------------------------------\n";
    if (size == 0) {
        cout << "No values.\n";
        return;
    }
    for (int i = 0; i < size; ++i) cout << arr[i] << " ";
    cout << "\n";
    cout << left << setw(10) << "Sum:" << calculateSum(arr, size) << "\n";
    cout << left << setw(10) << "Average:" << calculateAverage(arr, size) << "\n";
    cout << left << setw(10) << "Median:" << calculateMedian(arr, size) << "\n";
}

void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i)
        for (int j = 0; j < size - i - 1; ++j)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

double calculateMedian(int arr[], int size) {
    if (size == 0) return 0.0;
    bubbleSort(arr, size);
    return (size % 2 == 0) ? (arr[size / 2 - 1] + arr[size / 2]) / 2.0 : arr[size / 2];
}

double calculateAverage(const int arr[], int size) {
    if (size == 0) return 0.0;
    return static_cast<double>(calculateSum(arr, size)) / size;
}

int calculateSum(const int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) sum += arr[i];
    return sum;
}

void writeToFile(const int div5[], int size5, const int div9[], int size9, const int others[], int sizeOthers) {
    ofstream file(OUTPUT_FILE);
    if (!file) {
        cerr << "Error opening file: " << OUTPUT_FILE << "\n";
        return;
    }
    auto writeArray = [&](const int arr[], int size, const string& name) {
        file << name << " Numbers:\n";
        file << "---------------------------------\n";
        if (size == 0) file << "No values.\n";
        else {
            for (int i = 0; i < size; ++i) file << arr[i] << " ";
            file << "\n";
            file << left << setw(10) << "Sum:" << calculateSum(arr, size) << "\n";
            file << left << setw(10) << "Average:" << calculateAverage(arr, size) << "\n";
            file << left << setw(10) << "Median:" << calculateMedian(arr, size) << "\n\n";
        }
    };
    writeArray(div5, size5, "Divisible by 5");
    writeArray(div9, size9, "Divisible by 9");
    writeArray(others, sizeOthers, "Others");
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


