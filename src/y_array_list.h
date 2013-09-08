#ifndef __Y_ARRAY_LIST_H__
#define __Y_ARRAY_LIST_H__

typedef struct _YArrayListPrivate YArrayListPrivate;

typedef struct _YArrayList {
    YArrayListPrivate *priv;
} YArrayList;

YArrayList *YArrayList_new(void);
YArrayList *YArrayList_newWithCount(int count);
void YArrayList_destroy(YArrayList *list);

/**
 * Get current list item count.
 */
int YArrayList_getCount(YArrayList *list);
int YArrayList_appendItem(YArrayList *list, void *item);
void *YArrayList_getItemAt(YArrayList *list, int index);
void *YArrayList_removeItemAt(YArrayList *list, int index);
void *YArrayList_pop(YArrayList *list);
#endif // __Y_ARRAY_LIST_H__
