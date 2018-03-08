#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

static int inplace_sort_up (int * data, int data_sz) {
    int swap = 0;
    int pivot = 0;
    while (pivot < data_sz - 1) {
        int tmp = data[pivot];
        int k = data_sz - 1;
        while ((k > pivot) && (data[k] < tmp)) {
            k --;
        }
        if (data[k] < tmp) {
            data[pivot] = data[k];
            data[k] = tmp;
            swap ++;
        }
        pivot ++;
    }
    return swap;
}
    
static int inplace_sort_down (int * data, int data_sz) {
    int swap = 0;
    int pivot = data_sz - 1;
    while (pivot > 0) {
        int tmp = data[pivot];
        int k = 0;
        while ((k < pivot) && (data[k] > tmp)) {
            k ++;
        }
        if (data[k] > tmp) {
            data[pivot] = data[k];
            data[k] = tmp;
            swap ++;
        }
        pivot --;
    }

    if ((data_sz == 3) && (data[1] < data[0])) {
        int tmp = data[0];
        data[0] = data[1];
        data[1] = tmp;
        swap ++;
    }
    return swap;
}

static int inplace_sort2 (int a[2]) {
    //printf ("sort2\n");
    int tmp = a[0];
    if (tmp < a[1]) {
        return 0;
    }
    a[0] = a[1];
    a[1] = tmp;
    return 1;
}

static int inplace_sort3 (int a[3]) {
    //printf ("sort3\n");
    int swap = 0;
    int tmp = a[0];
    if (tmp > a[1]) {
        a[0] = a[1];
        a[1] = tmp;
        swap ++;
    }
    // now a[1] > a[0]
    tmp = a[1];
    if (tmp > a[2]) {
        if (a[2] < a[0]) {
            tmp = a[0];
            a[0] = a[2];
            a[2] = tmp;
        } else {
            a[1] = a[2];
            a[2] = tmp;
        }
        swap ++;
    }
    return swap;
}

static int inplace_sort4 (int a[4]) {
    //printf ("sort4\n");
    int swap = inplace_sort2(a);
    swap += inplace_sort2(a+2);
    // now (a0 < a1) && (a2 < a3)
    if (a[1] < a[2]) {
        // done
        return swap;
    }
    if (a[3] < a[0]) {
        // a2 < a3 < a0 < a1
        int tmp = a[0];
        a[0] = a[2];
        a[2] = tmp;
        tmp  = a[1];
        a[1] = a[3];
        a[3] = tmp;
        swap += 2;
        return swap;
    }
    // there (a2 < a1), is (a2 < a0) too ?
    if (a[2] < a[0]) {
        // a2 < a0 < a1, just check a1 against a3 and we're done
        if (a[3] < a[1]) {
            // a2 < a0 < a3 < a1
            int tmp = a[0];
            a[0] = a[2];
            a[2] = a[3];
            a[3] = a[1];
            a[1] = tmp;
            swap += 2;
        } else {
            // a2 < a0 < a1 < a3
            int tmp = a[0];
            a[0] = a[2];
            a[2] = a[1];
            a[1] = tmp;
            swap += 2;
        }
    } else {
        // a0 < a2 < a1, just check a1 against a3 and we're done
        if (a[3] < a[1]) {
            // a0 < a2 < a3 < a1
            int tmp = a[1];
            a[1] = a[2];
            a[2] = a[3];
            a[3] = tmp;
            swap += 2;
        } else {
            // a0 < a2 < a1 < a3
            int tmp = a[1];
            a[1] = a[2];
            a[2] = tmp;
            swap ++;
        }
    }
    return swap;
}

static void inplace_mm (int * data, int data_sz) {
    int k_min = INT_MAX;
    int k_max = INT_MIN;
    int min = INT_MAX;
    int max = INT_MIN;
    for (int k = 0; k < data_sz; k++) {
        if (data[k] > max) {
            k_max = k;
            max = data[k];
        }
        if (data[k] < min) {
            k_min = k;
            min = data[k];
        }
    }
    if (k_min == 0) {
        // nothing
    } else {
        int tmp = data[0];
        data[0] = data[k_min];
        data[k_min] = tmp;
    }
    if (k_max == data_sz - 1) {
        // nothing
    } else {
        int tmp = data[data_sz - 1];
        data[data_sz-1] = data[k_max];
        data[k_max] = tmp;
    }
}

static void inplace_sort (int * data, int data_sz) {
    // { 3, 1, 2, 0 };
    int k_head = 0;
    int k_tail = data_sz - 1;
    while (k_tail - k_head > 2) {
        // init min and max, since head and tail are not tested in the loop,
        // check one against the other now, data[k_head] < data[k_tail] ?
        int k_min = k_head;
        int k_max = k_tail;
        if ((0)&&(data[k_min] > data[k_max])) {
            k_min = k_tail;
            k_max = k_head;
        }
        // search for min and max
        for (int k = k_head + 1; k < k_tail; k++) {
            if (data[k] > data[k_max]) {
                k_max = k;
            }
            if (data[k] < data[k_min]) {
                k_min = k;
            }
        }
        printf ("[%d...%d]: min %d@%d, max %d@%d, ",
                k_head, k_tail, data[k_min], k_min, data[k_max], k_max);
        if (k_min == k_max) {
            // everything between head and tail are equal, done
            return;
        }

        if (k_head == k_min) { printf ("k_head == k_min, "); }
        if (k_head == k_max) { printf ("k_head == k_max, "); }
        if (k_tail == k_min) { printf ("k_tail == k_min, "); }
        if (k_tail == k_max) { printf ("k_tail == k_max, "); }

        if (0) {
        // backup all before to swap
        int head = data[k_head];
        int tail = data[k_tail];
        int min = data[k_min];
        int max = data[k_max];
        data[k_max] = tail;
        data[k_tail] = max;
        data[k_min] = head;
        data[k_head] = min;
        // KO for d1, f1, b2, e2, b3, d3, e3, f3
        }

        if (0) {
        // swap min and head, then swap max and tail
        //   M        m
        // { 3, 1, 2, 0 };
        int tmp;
        tmp = data[k_head]; // tmp = 3
        data[k_head] = data[k_min]; // { 0, 1, 2, 0 }
        data[k_min] = tmp; // { 0, 1, 2, 3 } 
        tmp = data[k_tail]; // tmp = 3
        data[k_tail] = data[k_max]; // { 0, 1, 2, 0 }
        data[k_max] = tmp; // { 3, 1, 2, 0 }
        // this way, a3 to f3 are KO but without missing
        // more, a3 left unchanged!
        }

        if (1) {
        //  swap max and tail, then swap min and head
        int tmp;
        tmp = data[k_tail];
        data[k_tail] = data[k_max];
        data[k_max] = tmp;
        tmp = data[k_head];
        data[k_head] = data[k_min];
        data[k_min] = tmp;
        // KO for d1, f1, b2, e2, a3, c3
        // more, a3 and c3 left unchanged!
        }
#if 0
        // TODO sort data[k_min] and data[k_max]
        if (d) {
            if (k_min > k_max) {
                data[k_min] = d_head;
                data[k_max] = d_tail;
            } else {
                data[k_min] = d_tail;
                data[k_max] = d_head;
            }
        } else {
            if (k_min > k_max) {
                data[k_min] = d_tail;
                data[k_max] = d_head;
            } else {
                data[k_min] = d_head;
                data[k_max] = d_tail;
            }
        }
#endif
        k_head ++;
        k_tail --;
    }
    switch (k_tail - k_head + 1) {
        case 3:
        inplace_sort3(data + k_head);
        break;
        case 2:
        inplace_sort2(data + k_head);
        break;
        default:
        printf ("%d to %d -> %d elements\n",
                k_head, k_tail,  k_tail - k_head + 1 );
        return;
    }
    return;
}

static void print_array (int const * data, int data_sz) {
    printf ("[");
    for (int k = 0; k < data_sz; k++) {
        printf ("%3d%s", data[k], (k == data_sz - 1) ? "" : ",");
    }
    printf ("]");
}

static int compare_int (void const * left, void const * right) {
    int l = *((int*)left);
    int r = *((int*)right);
    return l - r;
}

static void reference_sort (int * data, int data_sz) {
    qsort (data, data_sz, sizeof (int), compare_int);
}

static void do_array(char const * data_name, int * data, int data_sz) {
    #if 0
    int swap = inplace_sort4 (data);
    printf ("%s[", data_name); print_array(data, data_sz);
    printf ("]: %d\n", swap); 
    #else
    printf ("%s ", data_name);
    print_array(data, data_sz);
    printf (":");
    inplace_mm (data, data_sz);
    print_array(data, data_sz);
    printf ("\n");
    int * cpy = malloc (data_sz * sizeof(int));
    memcpy (cpy, data, data_sz * sizeof (int));
    inplace_sort (data, data_sz);
    reference_sort (cpy, data_sz);
    if (memcmp (data, cpy, data_sz * sizeof (int))) {
        printf ("*** KO %s ", data_name);
        print_array(data, data_sz);
        printf (" ***\n\n");
    } else {
        printf ("OK\n\n");
    }
    free (cpy);
    #endif
}

int main (void) {
    int a0[4] = { 0, 1, 2, 3 };
    do_array("a0", a0, 4);
    int b0[4] = { 0, 1, 3, 2 };
    do_array("b0", b0, 4);
    int c0[4] = { 0, 2, 1, 3 };
    do_array("c0", c0, 4);
    int d0[4] = { 0, 2, 3, 1 };
    do_array("d0", d0, 4);
    int e0[4] = { 0, 3, 1, 2 };
    do_array("e0", e0, 4);
    int f0[4] = { 0, 3, 2, 1 };
    do_array("f0", f0, 4);

    int a1[4] = { 1, 0, 2, 3 };
    do_array("a1", a1, 4);
    int b1[4] = { 1, 0, 3, 2 };
    do_array("b1", b1, 4);
    int c1[4] = { 1, 2, 0, 3 };
    do_array("c1", c1, 4);
    int d1[4] = { 1, 2, 3, 0 };
    do_array("d1", d1, 4);
    int e1[4] = { 1, 3, 0, 2 };
    do_array("e1", e1, 4);
    int f1[4] = { 1, 3, 2, 0 };
    do_array("f1", f1, 4);

    int a2[4] = { 2, 1, 0, 3 };
    do_array("a2", a2, 4);
    int b2[4] = { 2, 1, 3, 0 };
    do_array("b2", b2, 4);
    int c2[4] = { 2, 0, 1, 3 };
    do_array("c2", c2, 4);
    int d2[4] = { 2, 0, 3, 1 };
    do_array("d2", d2, 4);
    int e2[4] = { 2, 3, 1, 0 };
    do_array("e2", e2, 4);
    int f2[4] = { 2, 3, 0, 1 };
    do_array("f2", f2, 4);

    int a3[4] = { 3, 1, 2, 0 };
    do_array("a3", a3, 4);
    int b3[4] = { 3, 1, 0, 2 };
    do_array("b3", b3, 4);
    int c3[4] = { 3, 2, 1, 0 };
    do_array("c3", c3, 4);
    int d3[4] = { 3, 2, 0, 1 };
    do_array("d3", d3, 4);
    int e3[4] = { 3, 0, 1, 2 };
    do_array("e3", e3, 4);
    int f3[4] = { 3, 0, 2, 1 };
    do_array("f3", f3, 4);

    return 0;
}

