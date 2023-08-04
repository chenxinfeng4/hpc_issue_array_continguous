cimport numpy as np
import numpy as npy
from libc.stdint cimport uint8_t, int64_t
from libcpp cimport bool

cdef extern from "fast_concat_lib.hpp":
    # 导入C++中的函数声明

    void concat[T](T *source, T *destination, const int DIM_SRC_N,
        const int DIM_SRC_X, const int DIM_SRC_Y, const int DIM_SRC_Z,
        const int DIM_DST_X, const int DIM_DST_Y, const int DIM_DST_Z,
        const int START_X,   const int START_Y,   const int START_Z
        )


def concat_py(np.ndarray img_NXYZ,  
                DIM_DST_X:int, DIM_DST_Y:int, DIM_DST_Z:int, 
                START_X: int,  START_Y: int,  START_Z: int, 
                mode:int = 0):
    # 提取数组的指针
    cdef int DIM_SRC_N = img_NXYZ.shape[0]
    cdef int DIM_SRC_X = img_NXYZ.shape[1]
    cdef int DIM_SRC_Y = img_NXYZ.shape[2]
    cdef int DIM_SRC_Z = img_NXYZ.shape[3]

    cdef np.ndarray output_NXYZ = npy.empty((DIM_SRC_N, DIM_DST_X, DIM_DST_Y, DIM_DST_Z), dtype=img_NXYZ.dtype)
    cdef int64_t * img_NXYZ_ptr = <int64_t *> img_NXYZ.data
    cdef int64_t * output_NXYZ_ptr = <int64_t *> output_NXYZ.data
    # 调用C++函数处理数组
    concat[int64_t](img_NXYZ_ptr, output_NXYZ_ptr, DIM_SRC_N,
            DIM_SRC_X, DIM_SRC_Y, DIM_SRC_Z,
            DIM_DST_X, DIM_DST_Y, DIM_DST_Z,
            START_X,   START_Y,   START_Z
            )
    return output_NXYZ
