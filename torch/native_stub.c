#include <moonbit.h>
#include <stdlib.h>
#include <string.h>

typedef int64_t tensor_id;

tensor_id at_tensor_of_data_internal(void *vs, int64_t *dims, size_t ndims,
                                     size_t element_size_in_bytes, int type);

int get_tensor_raw_internal(tensor_id global_id, unsigned char **data);

tensor_id reshape_internal(tensor_id global_id, int64_t *dims, size_t ndims);

int get_tensor_shape_internal(tensor_id global_id, unsigned **shape);

tensor_id at_tensor_of_data(moonbit_bytes_t data_ptr, moonbit_bytes_t dims,
                            unsigned ndims, unsigned element_size_in_bytes,
                            int type) {
    tensor_id id = at_tensor_of_data_internal(data_ptr, (int64_t *)dims, ndims,
                                              element_size_in_bytes, type);
    moonbit_decref(data_ptr);
    moonbit_decref(dims);
    return id;
}

moonbit_bytes_t get_tensor_raw(tensor_id global_id) {
    unsigned char *data;
    int size = get_tensor_raw_internal(global_id, &data);
    moonbit_bytes_t bytes = moonbit_make_bytes(size, 0);
    memcpy(bytes, data, size);
    free(data);
    return bytes;
}

tensor_id reshape(tensor_id global_id, moonbit_bytes_t dims, unsigned ndims) {
    tensor_id id = reshape_internal(global_id, (int64_t *)dims, ndims);
    moonbit_decref(dims);
    return id;
}

moonbit_bytes_t get_tensor_shape(tensor_id global_id) {
    unsigned *shape;
    int size = get_tensor_shape_internal(global_id, &shape);
    size *= sizeof(unsigned);
    moonbit_bytes_t bytes = moonbit_make_bytes(size, 0);
    memcpy(bytes, shape, size);
    free(shape);
    return bytes;
}