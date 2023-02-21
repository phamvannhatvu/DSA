#include <iostream>
#include <stack>

template<class T>
void selectionSort(T a[], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        int i_min = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (a[j] < a[i_min]) i_min = j;
        }
        if (i != i_min)
        {
            int tmp = a[i]; 
            a[i] = a[i_min];
            a[i_min] = tmp;
        }
    }
}

template<class T>
void insertionSort(T a[], int n)
{
    for (int i = 1, j; i < n; ++i)
    {
        int tmp = a[i];
        for (j = i - 1; j >= 0 && a[j] > tmp; --j)
        {
            a[j + 1] = a[j];
        }
        a[j + 1] = tmp;
    }
}

template<class T>
void shellSort(T a[], int n)
{
    std::stack<int> increments;
    for (int inc = 1; inc < n; inc = 3 * inc + 1)
    {
        increments.push(inc);
    }
    increments.pop();
    
    while (increments.size() > 0)
    {
        int inc = increments.top();
        for (int fi = 0; fi < inc; ++fi)
        {
            for (int i = fi, j; i < n; i += inc)
            {
                int tmp = a[i];
                for (j = i - 1; j >= fi && a[j] > tmp; j -= inc)
                {
                    a[j + inc] = a[j];
                }
                a[j + inc] = tmp;
            }
        }
        increments.pop();
    }
}

template<class T>
void bubbleSort(T a[], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = n - 1; j > i; --j)
        {
            if (a[j] < a[j - 1])
            {
                int tmp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = tmp;
            }
        }
    }
}

template<class T>
void quickSort(T a[], int first, int last)
{
    //pivot is the middle element
    int lower = first + 1, upper = last;

    //Isolate and avoid negative upper
    std::swap(a[first], a[(first + last) / 2]);
    int pivot = a[first];

    //partition
    while (lower <= upper)
    {
        while (a[lower] < pivot) ++lower;
        while (a[upper] > pivot) --upper;
        if (lower < upper)
        {
            std::swap(a[lower], a[upper]);
            ++lower;
            --upper;
        }else 
        {
            ++lower;
        }
    }

    std::swap(a[first], a[upper]);
    if (upper - 1 > first)
    {
        quickSort(a, first, upper - 1);
    }
    
    if (upper + 1 < last)
    {
        quickSort(a, upper + 1, last);
    }
}

template<class T>
void quickSort(T a[], int n)
{
    if (n < 2) return;
    int i_max = 0;
    for (int i = 1; i < n; ++i)
    {
        if (a[i] > a[i_max]) i_max = i;
    }
    std::swap(a[i_max], a[n - 1]);
    quickSort(a, 0, n - 2);
}

template<class T>
void mergeSort(T a[], int first, int last)
{
    if (first >= last) return;
    int mid = (first + last) / 2;
    mergeSort(a, first, mid);
    mergeSort(a, mid + 1, last);

    int *tmp = new int[last - first + 1];
    int i_first = first, i_last = mid + 1, i_tmp = 0;
    while (i_first <= mid && i_last <= last)
    {
        if (a[i_first] < a[i_last]) 
        {
            tmp[i_tmp] = a[i_first];
            ++i_first;
        }else
        {
            tmp[i_tmp] = a[i_last];
            ++i_last;
        }
        ++i_tmp;
    }
    while (i_first <= mid) 
    {
        tmp[i_tmp] = a[i_first];
        ++i_first;
        ++i_tmp;
    }
    while (i_last <= last)
    {
        tmp[i_tmp] = a[i_last];
        ++i_last;
        ++i_tmp;
    }
    for (int i = first; i <= last; ++i) a[i] = tmp[i - first];
    delete[] tmp;
}

template<class T>
void mergeSort(T a[], int n)
{
    mergeSort(a, 0, n - 1);
}

int main()
{
    int a[] = {1,4,3,4,2,7,0,3,4};
    selectionSort(a, 9);
    for (int i = 0; i < 9; ++i) std::cout << a[i] << ' ';
    std::cout << '\n';

    int b[] = {1,4,3,1,3,2,6,3,1};
    insertionSort(b, 9);
    for (int i = 0; i < 9; ++i) std::cout << b[i] << ' ';
    std::cout << '\n';

    int c[] = {4,13,23,12,43,42,42,24,1,3,7,22,13,43,1231,25,6,7,10,23,4,9,1,43,42,18,30,11,13,11,31,
        15,17,19,21,2,3,14,1,2,4,3,1,5};
    shellSort(c, 44);
    for (int i = 0; i < 44; ++i) std::cout << c[i] << ' ';
    std::cout << '\n';

    int d[] = {2,3,2,1,3,2,2,1,3};
    bubbleSort(d, 9);
    for (int i = 0; i < 9; ++i) std::cout << d[i] << ' ';
    std::cout << '\n';

    int e[] = {8,5,4,7,6,1,6,3,8,10,12};
    quickSort(e, 11);
    for (int i = 0; i < 11; ++i) std::cout << e[i] << ' ';
    std::cout << '\n';

    int f[] = {8,5,4,7,6,1,6,3,8,10,12};
    mergeSort(f, 11);
    for (int i = 0; i < 11; ++i) std::cout << f[i] << ' ';
    std::cout << '\n';
    return 0;
}