import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('sum.csv')

plt.figure(figsize=(10, 6))
plt.plot(data['X'], data['Y'], 'o', markersize=8, color='blue')

plt.xlabel('N')
plt.ylabel('t, ms')
plt.grid(True, alpha=0.3)
plt.show()