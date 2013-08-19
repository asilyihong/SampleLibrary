#include <stdlib.h>

#include "y_vector.h"

struct _YVectorPrivate {
    void **data;
    void **current;
    int cCount; // current count
    int aCount; // allocate count
};

YVector *YVector_new(void) {
    return YVector_newWithCount(10);
}

YVector *YVector_newWithCount(int count) {
    YVector *res = (YVector *)malloc(sizeof(YVector));
    if (NULL == res) {
        // throw out of memory ERROR
        return NULL;
    }
    YVectorPrivate *priv = (YVectorPrivate *)malloc(sizeof(YVectorPrivate));
    if (NULL == priv) {
        // throw out of memory ERROR
        free(res);
        return NULL;
    }

    res->priv = priv;
    priv->data = malloc(sizeof(void *) * count);
    priv->aCount = count;
    priv->cCount = 0;
    priv->current = priv->data;

    return res;
}

void YVector_free(YVector *vector) {
    if (NULL == vector) {
        // throw a null pointer exception
        return;
    }

    YVectorPrivate *priv = vector->priv;
    if (NULL == priv) {
        // this should not happen
        return;
    }

    free(priv->data);
    priv->current = NULL;
    priv->aCount = 0;
    priv->cCount = 0;

    return;
}


int YVector_add(YVector *vector, void *data) {
    if (NULL == vector) {
        // throw null pointer exception
        return -1;
    }

    if (NULL == data) {
        // throw invilid data exception
        return -10;
    }
    YVectorPrivate *priv = vector->priv;
    if (priv->aCount - 1 <= priv->cCount) {
        priv->aCount <<= 1;
        priv->data = realloc(priv->data, sizeof(void *) * priv->aCount);
        priv->current = priv->data + priv->cCount;
    }

    *(priv->current) = data;
    priv->current++;
    priv->cCount++;
    return 0;
}

void *YVector_pop(YVector *vector) {
    if (NULL == vector) {
        // throw null pointer exception
        return NULL;
    }
    
    YVectorPrivate *priv = vector->priv;
    priv->current--;
    void *data = *(priv->current);
    priv->data[priv->cCount] = NULL;
    priv->cCount--;
    return data;
}


