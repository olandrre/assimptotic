import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data = pd.read_csv('binary.csv', index_col=0)

plt.figure(figsize=(10, 6))
plt.plot(np.log2(data['X']), data['Y'], 'o', color='blue')

plt.ylabel('t')
plt.xlabel('log(N)')
plt.grid(True, alpha=0.3)
plt.legend()
plt.show()