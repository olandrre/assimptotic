import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data = pd.read_csv('results/binary_mid.csv', index_col=0)
data2 = pd.read_csv('results/binary.csv', index_col=0)

plt.figure(figsize=(10, 6))
plt.plot(np.log2(data['X']), data['Y'], 'o', color='blue')
plt.plot(np.log2(data2['X']), data2['Y'], 'o', color='green')

plt.ylabel('t')
plt.xlabel('log(N)')
plt.grid(True, alpha=0.3)
plt.legend()
plt.show()