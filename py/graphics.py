import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('results/binary.csv', index_col=0)
data2 = pd.read_csv('results/linear.csv', index_col=0)

plt.figure(figsize=(10, 6))
plt.errorbar(data['X'], data['Y'], yerr=0, xerr=0, fmt='.', capsize=3, color='green')
plt.errorbar(data2['X'], data2['Y'], yerr=0, xerr=0, fmt='.', capsize=3, color='blue')

plt.xscale('log') 
plt.yscale('log')  

plt.ylabel('t, ms')
plt.xlabel('N')
plt.grid(True, alpha=0.3)
plt.legend()
plt.show()