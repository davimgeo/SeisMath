import numpy as np
import matplotlib.pyplot as plt

nz = 509
nx = 509

model = np.fromfile("wavefield_result.bin", dtype=np.float32, count=nx*nz).reshape([nz, nx], order="C")

plt.imshow(model, cmap="Greys", aspect="auto")
plt.show()

