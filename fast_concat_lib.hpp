
#include <cstring>

template<typename T>
void thread_concat(T *source, T *destination, 
                const int DIM_SRC_X, const int DIM_SRC_Y, const int DIM_SRC_Z,
                const int DIM_DST_X, const int DIM_DST_Y, const int DIM_DST_Z,
                const int START_X,   const int START_Y,   const int START_Z
                )
{
    // T (*vectorSRC)[DIM_SRC_Y][DIM_SRC_Z] = reinterpret_cast<T(*)[DIM_SRC_Y][DIM_SRC_Z]>(source);
    // T (*vectorDST)[DIM_DST_Y][DIM_DST_Z] = reinterpret_cast<T(*)[DIM_DST_Y][DIM_DST_Z]>(destination);

    size_t size_cp = DIM_DST_Z * sizeof(T);
    for (int ix = 0; ix < DIM_DST_X; ix++){
        for (int iy = 0; iy < DIM_DST_Y; iy++){
            // T * ptrSRC = &vectorSRC[ix][iy][0];
            // T * ptrDST = &vectorDST[ix+START_X][iy+START_Y][START_Z];
            T * ptrSRC = &source[(ix + START_X) * DIM_SRC_Y * DIM_SRC_Z + (iy + START_Y) * DIM_SRC_Z + START_Z];
            T * ptrDST = &destination[ix * DIM_DST_Y * DIM_DST_Z + iy * DIM_DST_Z + 0];
            std::memcpy(ptrDST, ptrSRC, size_cp);
            // for (int iz = 0; iz < DIM_DST_Z; iz++){
            //     ptrDST[iz] = ptrSRC[iz];
            // }
        }
    }
}

template<typename T>
void concat(T *source, T *destination, const int DIM_SRC_N,
            const int DIM_SRC_X, const int DIM_SRC_Y, const int DIM_SRC_Z,
            const int DIM_DST_X, const int DIM_DST_Y, const int DIM_DST_Z,
            const int START_X,   const int START_Y,   const int START_Z
            )
{
    // 开启 openmp 多线程加速, 好像2个线程就饱和了
    // #pragma omp parallel for num_threads(2)
    for(int in=0; in < DIM_SRC_N; in++){
        T *source_batch = &source[in*DIM_SRC_X*DIM_SRC_Y*DIM_SRC_Z];
        T *destination_batch = &destination[in*DIM_DST_X*DIM_DST_Y*DIM_DST_Z];
        thread_concat(source_batch, destination_batch, DIM_SRC_X, DIM_SRC_Y, DIM_SRC_Z,
                    DIM_DST_X, DIM_DST_Y, DIM_DST_Z, START_X, START_Y, START_Z);
    }
}
