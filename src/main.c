#include <stdio.h>
#include <stdlib.h>

#include "y_list.h"
#include "y_vector.h"

void list_test(void);
void vector_test(void);

int main(int argc, char **argv)
{
    list_test();
    vector_test();

    return EXIT_SUCCESS;
}

void list_test(void) {
    int sample[] = {2, 5, 3, 6, 9};
    int res = 0, index;
    void *item;
    YList *list = YList_new();
    for(index = 0; index < 5; index++) {
        res = YList_add(list, &sample[index]);
        printf("res == %d\n", res);
    }

    for(index = 0; index < 5; index++) {
        item = YList_getItem(list, index);
        printf("(int)(*(int *)item)) == %d\n", (int)(*(int *)item));
    }

    res = YList_removeItem(list, &sample[0]);
    printf("res == %d\n", res);
    res = YList_removeIndex(list, 0);
    printf("res == %d\n", res);
    // this should out of bound
    res = YList_removeIndex(list, 4);
    printf("res == %d\n", res);
}

void vector_test(void) {
    int sample[] = {2, 5, 3, 6, 9};
    int res = 0, index;
    void *item;
    YVector *vector = YVector_new();
    for(index = 0; index < 5; index++) {
        res = YVector_add(vector, &sample[index]);
        printf("res == %d\n", res);
    }

    item = YVector_pop(vector);
    printf("(int)(*(int *)(item)) == %d\n", (int)(*(int *)item));
    item = YVector_pop(vector);
    printf("(int)(*(int *)(item)) == %d\n", (int)(*(int *)item));
    item = YVector_pop(vector);
    printf("(int)(*(int *)(item)) == %d\n", (int)(*(int *)item));
    item = YVector_pop(vector);
    printf("(int)(*(int *)(item)) == %d\n", (int)(*(int *)item));
    item = YVector_pop(vector);
    printf("(int)(*(int *)(item)) == %d\n", (int)(*(int *)item));
}
