#include <iostream>
#include <random>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
using Clock = chrono::high_resolution_clock;

void mergeRec(int* a, int* buf, int l, int r)
{
    if (l >= r) return;
    int m = (l + r) / 2;
    mergeRec(a, buf, l, m);
    mergeRec(a, buf, m + 1, r);

    int i = l, j = m + 1, k = l;
    while (i <= m || j <= r) {
        if (j > r || (i <= m && a[i] <= a[j]))
            buf[k++] = a[i++];
        else
            buf[k++] = a[j++];
    }
    for (int t = l; t <= r; ++t) a[t] = buf[t];
}

void mergeSort(int* a, int n)
{
    int* buf = new int[n];
    mergeRec(a, buf, 0, n - 1);
    delete[] buf;
}
template <typename SortFunc>
inline double timeIt(SortFunc sortAlg, int* arr, int n)
{
    auto start = Clock::now();
    sortAlg(arr, n);
    auto end   = Clock::now();
    return chrono::duration<double>(end - start).count();
}
int* randomArray(int n, mt19937& gen);
void siftDown(int* a, int root, int end);
void heapSort(int* a, int n);
void insertionSort(int* a, int n);

int main()
{
    ios::sync_with_stdio(false);
    cout.setf(ios::fixed);
    cout.precision(6);
    int sizes[] = {1000, 10000, 25000, 50000, 150000, 250000};
    const int NSIZES = sizeof(sizes) / sizeof(sizes[0]);
    mt19937 gen(random_device{}());
    

    cout<<"Input Length \tHeap Sort(seconds) \tInsertion Sort(seconds)\t\tMerge Sort(seconds) \tBest time"<<endl;
    constexpr double EPS = 1e-5;
    for (int idx = 0; idx < NSIZES; ++idx) {
        int n = sizes[idx];
        int* base = randomArray(n, gen);
        int* arrHeap = new int[n];
        int* arrIns  = new int[n];
        int* arrMer  = new int[n];
        memcpy(arrHeap, base, n * sizeof(int));
        memcpy(arrIns,  base, n * sizeof(int));
        memcpy(arrMer,  base, n * sizeof(int));

        double th = timeIt(heapSort,     arrHeap, n);
        double ti = timeIt(insertionSort, arrIns,  n);
        double tm  = timeIt(mergeSort,     arrMer,  n);

        double tmi = min({th, ti, tm});
        string b = fabs(tmi - th) < EPS ? "Heap" : fabs(tmi - ti)  < EPS ? "Insertion" : "Merge";

        cout<< n << "\t\t\t"<< th<<" \t\t\t"<< ti<<"\t\t\t\t\t"<< tm<<"\t\t\t\t" << b << '\n';

        delete[] base;
        delete[] arrHeap;
        delete[] arrIns;
        delete[] arrMer;
    }

    return 0;
}
int* randomArray(int n, mt19937& gen)
{
    uniform_int_distribution<int> dist(1, 100000);
    int* arr = new int[n];
    for (int i = 0; i < n; ++i)
        arr[i] = dist(gen);
    return arr;
}
void siftDown(int* a, int root, int end)
{
    while (true) {
        int left  = 2 * root + 1;
        int right = left + 1;
        int largest = root;
        if (left  <= end && a[left]  > a[largest]) largest = left;
        if (right <= end && a[right] > a[largest]) largest = right;
        if (largest == root) break;
        swap(a[root], a[largest]);
        root = largest;
    }
}
void heapSort(int* a, int n)
{
    for (int i = n / 2 - 1; i >= 0; --i)
        siftDown(a, i, n - 1);
    for (int end = n - 1; end > 0; --end) {
        swap(a[0], a[end]);
        siftDown(a, 0, end - 1);
    }
}
void insertionSort(int* a, int n)
{
    for (int i = 1; i < n; ++i) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = key;
    }
}
