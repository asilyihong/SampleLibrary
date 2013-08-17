#ifndef __Y_LIST_H__
#define __Y_LIST_H__

typedef struct _YListPrivate YListPrivate;

typedef struct _YList {
    YListPrivate *priv;
} YList;

/**
 * The YList constructor.
 */
YList *YList_new(void);
/**
 * The YList destructor.
 */
void YList_free(YList *list);

int YList_add(YList *list, void *data);
int YList_removeItem(YList *list, void *data);
int YList_removeIndex(YList *list, int index);

#endif // __Y_LIST_H__
