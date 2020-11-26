#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//冒泡
void bubble_sort(int arr[], int len) {
    int i, j, temp;
    for (i = 0; i < len - 1; i++) {
        for (j = 0; j < len - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
//快排
typedef struct _Range {
    int start, end;
} Range;
Range new_Range(int s, int e) {
    Range r;
    r.start = s;
    r.end = e;
    return r;
}
void quick_sort(int arr[], const int len) {//快排
    if (len <= 0)
        return; // 避免len等於負值時引發段錯誤（Segment Fault）
    // r[]模擬列表,p為數量,r[p++]為push,r[--p]為pop且取得元素
    Range r[len];
    int p = 0;
    r[p++] = new_Range(0, len - 1);
    while (p) {
        Range range = r[--p];
        if (range.start >= range.end)
            continue;
        int mid = arr[(range.start + range.end) / 2]; // 選取中間點為基準點
        int left = range.start, right = range.end;
        do {
            while (arr[left] < mid) ++left;   // 檢測基準點左側是否符合要求
            while (arr[right] > mid) --right; //檢測基準點右側是否符合要求
            if (left <= right) {
                swap(&arr[left], &arr[right]);
                left++;
                right--;               // 移動指針以繼續
            }
        } while (left <= right);
        if (range.start < right) r[p++] = new_Range(range.start, right);
        if (range.end > left) r[p++] = new_Range(left, range.end);
    }
}
//选择
void selection_sort(int arr[], int len){
    int i, j;
    for (i = 0; i < len - 1; i++){
        int min = i;
        for (j = i + 1; j < len; j++)     //走訪未排序的元素
            if (arr[j] < arr[min])    //找到目前最小值
                min = j;    //紀錄最小值
        swap(&arr[min], &arr[i]);    //做交換
    }
}
//插入
void insertion_sort(int arr[], int len) {
    int i, j, key;
    for (i = 1; i < len; i++) {
        key = arr[i];
        j = i - 1;
        while ((j >= 0) && (arr[j] > key)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
//希尔
void shell_sort(int arr[], int len) {
    int gap, i, j;
    int temp;
    for (gap = len >> 1; gap > 0; gap >>= 1)
        for (i = gap; i < len; i++) {
            temp = arr[i];
            for (j = i - gap; j >= 0 && arr[j] > temp; j -= gap)
                arr[j + gap] = arr[j];
            arr[j + gap] = temp;
        }
}
//归并
void merge_sort(int arr[], int len) {
    int* a = arr;
    int* b = (int*)malloc(len * sizeof(int));
    int seg, start;
    for (seg = 1; seg < len; seg += seg) {
        for (start = 0; start < len; start += seg * 2) {
            int low = start, mid = min(start + seg, len), high = min(start + seg * 2, len);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while (start1 < end1 && start2 < end2)
                b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
            while (start1 < end1)
                b[k++] = a[start1++];
            while (start2 < end2)
                b[k++] = a[start2++];
        }
        int* temp = a;
        a = b;
        b = temp;
    }
    if (a != arr) {
        int i;
        for (i = 0; i < len; i++)
            b[i] = a[i];
        b = a;
    }
    free(b);
}
//堆排序
void max_heapify(int arr[], int start, int end) {
    // 建立父節點指標和子節點指標
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end) { // 若子節點指標在範圍內才做比較
        if (son + 1 <= end && arr[son] < arr[son + 1]) // 先比較兩個子節點大小，選擇最大的
            son++;
        if (arr[dad] > arr[son]) //如果父節點大於子節點代表調整完畢，直接跳出函數
            return;
        else { // 否則交換父子內容再繼續子節點和孫節點比較
            swap(&arr[dad], &arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}
void heap_sort(int arr[], int len) {
    int i;
    // 初始化，i從最後一個父節點開始調整
    for (i = len / 2 - 1; i >= 0; i--)
        max_heapify(arr, i, len - 1);
    // 先將第一個元素和已排好元素前一位做交換，再重新調整，直到排序完畢
    for (i = len - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        max_heapify(arr, 0, i - 1);
    }
}
//计数
void counting_sort(int* ini_arr, int* sorted_arr, int n) {
    int* count_arr = (int*)malloc(sizeof(int) * 100);
    int i, j, k;
    for (k = 0; k < 100; k++)
        count_arr[k] = 0;
    for (i = 0; i < n; i++)
        count_arr[ini_arr[i]]++;
    for (k = 1; k < 100; k++)
        count_arr[k] += count_arr[k - 1];
    for (j = n; j > 0; j--)
        sorted_arr[--count_arr[ini_arr[j - 1]]] = ini_arr[j - 1];
    free(count_arr);
}
void print_arr(int* arr, int n) {
    int i;
    printf("%d", arr[0]);
    for (i = 1; i < n; i++) {
        printf(" %d", arr[i]);
    }
    printf("\n");
}
int main(int argc, char** argv) {
    int n = 10;
    int i;
    int* arr = (int*)malloc(sizeof(int) * n);
    int* sorted_arr = (int*)malloc(sizeof(int) * n);
    srand(time(0));
    for (i = 0; i < n; i++)
        arr[i] = rand() % 100;
    printf("ini_array: ");
    print_arr(arr, n);
    counting_sort(arr, sorted_arr, n);
    printf("sorted_array: ");
    print_arr(sorted_arr, n);
    free(arr);
    free(sorted_arr);
    return 0;
}
//基数
#define MAX 20
//#define SHOWPASS
#define BASE 10
void radixsort(int* a, int n) {
    int i, b[MAX], m = a[0], exp = 1;
    for (i = 1; i < n; i++) {
        if (a[i] > m) {
            m = a[i];
        }
    }
    while (m / exp > 0) {
        int bucket[BASE] = { 0 };
        for (i = 0; i < n; i++) {
            bucket[(a[i] / exp) % BASE]++;
        }
        for (i = 1; i < BASE; i++) {
            bucket[i] += bucket[i - 1];
        }
        for (i = n - 1; i >= 0; i--) {
            b[--bucket[(a[i] / exp) % BASE]] = a[i];
        }
        for (i = 0; i < n; i++) {
            a[i] = b[i];
        }
        exp *= BASE;
#ifdef SHOWPASS
        printf("\nPASS   : ");
        print(a, n);
#endif
    }
}


void print(int* a, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d\t", a[i]);
    }
}
void swap(int* a, int* b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}
int main() {
    int arr[] = { 22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70 };
    int len = (int)sizeof(arr) / sizeof(*arr);
    bubble_sort(arr, len);
    int i;
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);
    return 0;
}
int main() {
    int arr[MAX];
    int i, n;
    printf("Enter total elements (n <= %d) : ", MAX);
    scanf("%d", &n);
    n = n < MAX ? n : MAX;
    printf("Enter %d Elements : ", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("\nARRAY  : ");
    print(&arr[0], n);
    radixsort(&arr[0], n);
    printf("\nSORTED : ");
    print(&arr[0], n);
    printf("\n");
    return 0;
}
https://www.runoob.com/w3cnote/ten-sorting-algorithm.html