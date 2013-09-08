#include <stdlib.h>
#include <string.h>

#include "YArrayList.h"

struct _YArrayListPrivate {
    int currCount;
    void **list;
    int mallCount;
};

YArrayList *YArrayList_new(void) {
    return YArrayList_newWithCount(100);
}

YArrayList *YArrayList_newWithCount(int count) {
    YArrayList *res = (YArrayList *)malloc(sizeof(YArrayList));
    if (NULL == res) {
        return NULL;
    }

    YArrayListPrivate *priv = (YArrayListPrivate *)malloc(sizeof(YArrayListPrivate));
    if (NULL == priv) {
        YArrayList_destroy(res);
        return NULL;
    }
    res->priv = priv;
    priv->list = (void **)malloc(sizeof(void *) * count);
    if (NULL == priv->list) {
        YArrayList_destroy(res);
        return NULL;
    }
    priv->currCount = 0;
    priv->mallCount = count;

    return res;
}

void YArrayList_destroy(YArrayList *list) {
    if (NULL == list) {
        return;
    }

    YArrayListPrivate *priv = list->priv;
    if (NULL == priv) {
        return;
    }

    if (NULL != priv->list) {
        free(priv->list);
        priv->list = NULL;
    }
    priv->currCount = 0;
    priv->mallCount = 0;
    free(priv);
    list->priv = NULL;
    free(list);
}

int YArrayList_getCount(YArrayList *list) {
    if (NULL == list) {
        return -1;
    }

    YArrayListPrivate *priv = list->priv;
    if (NULL == priv) {
        return -10;
    }
    
    return priv->currCount;    
}

int YArrayList_appendItem(YArrayList *list, void *item) {
    if (NULL == list) {
        return -1;
    }

    YArrayListPrivate *priv = list->priv;
    if (NULL == priv) {
        return -10;
    }
    
    if (priv->currCount == priv->mallCount) {
        void **newList = (void **)realloc(priv->list, priv->mallCount + 100);
        if (NULL == newList) {
            return -100;
        }
        priv->list = newList;
        priv->mallCount += 100;
    }
    priv->list[priv->currCount] = item;
    priv->currCount++;
    return 1;
}

void *YArrayList_getItemAt(YArrayList *list, int index) {
    if (NULL == list) {
        return NULL;
    }

    YArrayListPrivate *priv = list->priv;
    if (NULL == priv) {
        return NULL;
    }
    
    if (index < 0 || index >= priv->currCount) {
        return NULL;
    }

    return priv->list[index];
}
void *YArrayList_removeItemAt(YArrayList *list, int index) {
    if (NULL == list) {
        return NULL;
    }

    YArrayListPrivate *priv = list->priv;
    if (NULL == priv) {
        return NULL;
    }
    
    if (index < 0 || index >= priv->currCount) {
        return NULL;
    }
    void *res = priv->list[index];

    memmove(priv->list + index, priv->list + index + 1, priv->currCount - index - 1);
    priv->currCount--;
    return res;
}

void *YArrayList_pop(YArrayList *list) {
    if (NULL == list) {
        return NULL;
    }

    YArrayListPrivate *priv = list->priv;
    if (NULL == priv) {
        return NULL;
    }
    
    priv->currCount--;
    return priv->list[priv->currCount];
}
