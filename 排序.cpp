#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <cstdlib>  

// ��������
void insertionSort(std::vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// �鲢����ϲ�����
void merge(std::vector<int>& arr, int left, int mid, int right) {
    std::vector<int> temp;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp.push_back(arr[i++]);
        else temp.push_back(arr[j++]);
    }
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);
    for (int k = 0; k < temp.size(); k++) arr[left + k] = temp[k];
}

// �鲢����������
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// ���������������
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// ��������������
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low >= high) return;
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
}

// ��������
std::vector<int> countSort(std::vector<int> arr) {
    if (arr.empty()) return {};
    int minVal = arr[0], maxVal = arr[0];
    for (int num : arr) {
        if (num < minVal) minVal = num;
        if (num > maxVal) maxVal = num;
    }
    std::vector<int> count(maxVal - minVal + 1, 0);
    for (int num : arr) count[num - minVal]++;
    std::vector<int> result;
    for (int i = 0; i < count.size(); i++) {
        while (count[i]-- > 0) result.push_back(i + minVal);
    }
    return result;
}

// ��������
void radixSort(std::vector<int>& arr) {
    if (arr.empty()) return;
    int maxVal = abs(arr[0]);
    for (int num : arr) if (abs(num) > maxVal) maxVal = abs(num);
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        std::vector<int> output(arr.size());
        int count[10] = { 0 };
        for (int num : arr) count[(abs(num) / exp) % 10]++;
        for (int i = 1; i < 10; i++) count[i] += count[i - 1];
        for (int i = arr.size() - 1; i >= 0; i--) {
            int digit = (abs(arr[i]) / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }
        arr = output;
    }
}

// �����������
std::vector<int> generateData(int size) {
    std::vector<int> data(size);
    for (int& num : data) num = rand() % 10000;
    return data;
}

// ��������ʱ��
void testSort(void (*sortFunc)(std::vector<int>&), std::vector<int> data, std::string name) {
    clock_t start = clock();
    sortFunc(data);
    double time = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("%-12s: %.4f��\n", name.c_str(), time);
}

// ������
int main() {
    srand(time(0));

    // ���Դ�������
    std::vector<int> sizes = { 10000, 50000, 200000 };
    for (int size : sizes) {
        std::vector<int> data = generateData(size);
        printf("\n������: %d\n", size);

        // ������������������
        if (size <= 50000) {
            testSort(insertionSort, data, "��������");
        }

        testSort([](std::vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }, data, "�鲢����");
        testSort([](std::vector<int>& arr) { quickSort(arr, 0, arr.size() - 1); }, data, "��������");
        testSort([](std::vector<int>& arr) { arr = countSort(arr); }, data, "��������");
        testSort(radixSort, data, "��������");
    }

    // ����С������
    std::vector<int> smallData = generateData(100);
    printf("\nС���ݲ���(100����������10���):\n");

    clock_t total = clock();
    for (int i = 0; i < 100000; i++) {
        std::vector<int> copy = smallData;
        insertionSort(copy);
    }
    printf("���������ܺ�ʱ: %.2f��\n", (double)(clock() - total) / CLOCKS_PER_SEC);

    return 0;
}