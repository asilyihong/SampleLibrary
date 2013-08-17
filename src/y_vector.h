#ifndef __Y_VECTOR_H__
#define __Y_VECTOR_H__
typedef struct _YVectorPrivate YVectorPrivate;

typedef struct _YVector {
    YVectorPrivate *priv;
} YVector;

/**
 * The YVector constructor.
 */
YVector *YVector_new(void);
YVector *YVector_newWithCount(int count);
/**
 * The YVector destructor.
 */
void YVector_free(YVector *vector);

int YVector_add(YVector *vector, void *data);
void *YVector_pop(YVector *vector);

#endif // __Y_VECTOR_H__
