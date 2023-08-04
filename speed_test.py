# %%
import numpy as np
import tqdm
import fast_concat

index_all = np.random.randint(0,800*1280-1, size=(9,164,164,164))
random_com3d = np.random.randint(0,100-1,size=(3))
com3d_x, com3d_y, com3d_z = random_com3d.tolist()

index_conti2 = fast_concat.concat_py(index_all, 64,64,64, com3d_x, com3d_y, com3d_z)

index_conti = np.ascontiguousarray(index_all[:, com3d_x:com3d_x+64, com3d_y:com3d_y+64, com3d_z:com3d_z+64])

assert np.all(index_conti2==index_conti)

# %%
for _ in tqdm.trange(1000):
    index_conti = np.ascontiguousarray(index_all[:, com3d_x:com3d_x+64, com3d_y:com3d_y+64, com3d_z:com3d_z+64])


for _ in tqdm.trange(1000):
    index_conti2 = fast_concat.concat_py(index_all, 64,64,64, com3d_x, com3d_y, com3d_z)

fps = 279
IO_rate = fps * index_all.itemsize * index_conti2.size / 1024**3
print(f'IO 的速度为 {IO_rate:.1f} GB/s')