#include <stdlib.h>

#include "y_list.h"

typedef struct _YListInstance {
    void                        *data;
    struct _YListInstance       *prev;
    struct _YListInstance       *next;
} YListInstance;

struct _YListPrivate {
    int                  count;
    YListInstance    *instance;
};

YList *YList_new(void) {
    YList *rev = (YList *)malloc(sizeof(YList));
    if (NULL == rev) {
        return NULL;
    }

    rev->priv = (YListPrivate *)malloc(sizeof(YListInstance));
    if (NULL == rev->priv) {
        free (rev);
        return NULL;
    }
    rev->priv->count = 0;
    rev->priv->instance = NULL;

    return rev;
}

void YList_free(YList *list)
{
    if (NULL == list) {
        return;
    }

    if (NULL != list->priv) {
        free(list->priv);
    }

    free(list);
    return;
}

int YList_add(YList *list, void *data)
{
    if (NULL == list) {
        // throw null pointer exception.
        return -1;
    }

    if (NULL == data) {
        // throw empty data exception.
        return -10;
    }

    YListPrivate *priv = list->priv;
    YListInstance *temp = priv->instance;
    YListInstance *inst = (YListInstance *)malloc(sizeof(YListInstance));
    if (NULL == inst) {
        // throw out of memory error.
        return -100;
    }
    inst->data = data;
    inst->prev = NULL;
    inst->next = NULL;

    if (NULL == temp) {
        // This is a empty list.
        priv->instance = inst;
        goto out;
    }

    while(NULL != temp->next) {
        temp = temp->next;
    }
    // after while loop, temp points the last element of list.

    temp->next = inst;
    inst->prev = temp;
out:
    priv->count++;
    return 0;
}

int YList_removeItem(YList *list, void *data) {
    if (NULL == list) {
        // throw null pointer exception.
        return -1;
    }

    if (NULL == data) {
        // throw empty data exception.
        return -10;
    }

    YListPrivate *priv = list->priv;
    YListInstance *temp = priv->instance;
   
    while(NULL != temp) {
        if (temp->data == data) {
            break;
        }
        temp = temp->next;
    }
    
    if (NULL == temp) {
        // can not find specific data.
        return 100;
    }

    if (NULL != temp->prev) {
        temp->prev->next = temp->next;
    } else {
        priv->instance = temp->next;
    }

    if (NULL != temp->next) {
        temp->next->prev = temp->prev;
    } else {
        temp->prev->next = NULL;
    }
    priv->count--;
    return 0;
}

int YList_removeIndex(YList *list, int index) {
    if (NULL == list) {
        // throw null pointer exception.
        return -1;
    }
    YListPrivate *priv = list->priv;

    if (0 > index || priv->count < index) {
        // throw out of range exception.
        return -10;
    }

    YListInstance *temp = priv->instance;
    for (;0 < index; index--) {
        temp = temp->next;
    }

    if (NULL != temp->prev) {
        temp->prev->next = temp->next;
    } else {
        priv->instance = temp->next;
    }

    if (NULL != temp->next) {
        temp->next->prev = temp->prev;
    } else {
        temp->prev->next = NULL;
    }
    priv->count--;
    return 0;
}

void *YList_getItem(YList *list, int index) {
    if (NULL == list) {
        // throw null pointer exception.
        return NULL;
    }
    YListPrivate *priv = list->priv;

    if (0 > index || priv->count < index) {
        // throw out of range exception.
        return NULL;
    }

    YListInstance *temp = priv->instance;
    while (0 < index) {
        temp = temp->next;
        index--;
    }

    return temp->data;
}
