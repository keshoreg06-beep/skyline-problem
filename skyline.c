#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50000
#define REPEAT 50   // Repeat many times for accurate timing

// ---------------- STRUCTURES ----------------

typedef struct {
    int x;
    int height;
} Point;

typedef struct {
    int left, right, height;
} Building;

// ---------------- MAX HEAP ----------------

int heap[MAX];
int heapSize = 0;

void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

void insertHeap(int value) {
    heap[++heapSize] = value;
    int i = heapSize;
    while (i > 1 && heap[i/2] < heap[i]) {
        swap(&heap[i/2], &heap[i]);
        i /= 2;
    }
}

void heapify(int i) {
    int largest = i;
    int l = 2*i;
    int r = 2*i + 1;

    if (l <= heapSize && heap[l] > heap[largest])
        largest = l;
    if (r <= heapSize && heap[r] > heap[largest])
        largest = r;

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        heapify(largest);
    }
}

void removeHeap(int value) {
    for (int i = 1; i <= heapSize; i++) {
        if (heap[i] == value) {
            heap[i] = heap[heapSize--];
            heapify(i);
            return;
        }
    }
}

int getMax() {
    if (heapSize == 0) return 0;
    return heap[1];
}

// ---------------- RANDOM GENERATOR ----------------

void generateRandomBuildings(Building buildings[], int n) {
    for (int i = 0; i < n; i++) {
        int left = rand() % 100000;
        int width = rand() % 100 + 1;
        int right = left + width;
        int height = rand() % 1000 + 1;

        buildings[i].left = left;
        buildings[i].right = right;
        buildings[i].height = height;
    }
}

// ---------------- MAX HEAP SKYLINE ----------------

int compareEvents(const void *a, const void *b) {
    Point *p1 = (Point*)a;
    Point *p2 = (Point*)b;

    if (p1->x != p2->x)
        return p1->x - p2->x;

    return p1->height - p2->height;
}

void skylineMaxHeap(Building buildings[], int n) {

    Point *events = malloc(sizeof(Point) * 2 * n);
    int eventCount = 0;

    for (int i = 0; i < n; i++) {
        events[eventCount++] = (Point){buildings[i].left, -buildings[i].height};
        events[eventCount++] = (Point){buildings[i].right, buildings[i].height};
    }

    qsort(events, eventCount, sizeof(Point), compareEvents);

    heapSize = 0;
    insertHeap(0);
    int prevHeight = 0;

    for (int i = 0; i < eventCount; i++) {
        int h = events[i].height;

        if (h < 0)
            insertHeap(-h);
        else
            removeHeap(h);

        int currentHeight = getMax();

        if (currentHeight != prevHeight) {
            prevHeight = currentHeight;
        }
    }

    free(events);
}

// ---------------- DIVIDE & CONQUER ----------------

Point* merge(Point *left, int n1, Point *right, int n2, int *size) {

    Point *result = malloc(sizeof(Point) * (n1 + n2));
    int i = 0, j = 0, k = 0;
    int h1 = 0, h2 = 0;

    while (i < n1 && j < n2) {
        int x;

        if (left[i].x < right[j].x) {
            x = left[i].x;
            h1 = left[i].height;
            i++;
        }
        else if (left[i].x > right[j].x) {
            x = right[j].x;
            h2 = right[j].height;
            j++;
        }
        else {
            x = left[i].x;
            h1 = left[i].height;
            h2 = right[j].height;
            i++; j++;
        }

        int maxH = (h1 > h2) ? h1 : h2;

        if (k == 0 || result[k-1].height != maxH)
            result[k++] = (Point){x, maxH};
    }

    while (i < n1) result[k++] = left[i++];
    while (j < n2) result[k++] = right[j++];

    *size = k;
    return result;
}

Point* skylineDivide(Building buildings[], int l, int r, int *size) {

    if (l == r) {
        Point *res = malloc(sizeof(Point) * 2);
        res[0] = (Point){buildings[l].left, buildings[l].height};
        res[1] = (Point){buildings[l].right, 0};
        *size = 2;
        return res;
    }

    int mid = (l + r) / 2;

    int size1, size2;

    Point *left = skylineDivide(buildings, l, mid, &size1);
    Point *right = skylineDivide(buildings, mid+1, r, &size2);

    return merge(left, size1, right, size2, size);
}

// ---------------- MAIN ----------------

int main() {

    int n;
    printf("Enter number of buildings (try 10000 or more): ");
    scanf("%d", &n);

    Building buildings[MAX];

    srand(time(NULL));
    generateRandomBuildings(buildings, n);

    // -------- MAX HEAP TIMING --------

    double totalHeap = 0;

    for (int i = 0; i < REPEAT; i++) {
        clock_t start = clock();
        skylineMaxHeap(buildings, n);
        clock_t end = clock();
        totalHeap += (double)(end - start) / CLOCKS_PER_SEC;
    }

    double avgHeap = totalHeap / REPEAT;
    printf("\nAverage Execution Time (Max-Heap): %f seconds\n", avgHeap);


    // -------- DIVIDE & CONQUER TIMING --------

    double totalDivide = 0;

    for (int i = 0; i < REPEAT; i++) {
        int size;
        clock_t start = clock();
        Point *result = skylineDivide(buildings, 0, n-1, &size);
        clock_t end = clock();
        totalDivide += (double)(end - start) / CLOCKS_PER_SEC;
        free(result);
    }

    double avgDivide = totalDivide / REPEAT;
    printf("Average Execution Time (Divide & Conquer): %f seconds\n", avgDivide);

    return 0;
}
