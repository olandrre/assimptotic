import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

data1 = pd.read_csv('sorting/combSorto01.csv', index_col=0)

def slope(data):
    x = np.log(data['swaps'])
    y = np.log(data['time'])
    k, b = np.polyfit(x, y, 1)
    return k, b

def line(data, color, label):
    plt.plot(data['swaps'], data['time'], 'o', color=color, markersize=3)
    k, b = slope(data)
    x0 = np.log(data['swaps'])
    y0 = np.exp(b) * (data['swaps'] ** k)
    plt.plot(data['swaps'], y0, '-', color=color, linewidth=2, label=f'{label}, slope={k:1f}')
    return k

plt.figure(figsize=(10, 6))

k1 = line(data1, 'red', 'classic')

plt.xscale('log') 
plt.yscale('log')  

plt.ylabel('t')
plt.xlabel('N')
plt.grid(True, alpha=0.3)
plt.title('Зависимость k(N)')
plt.legend()
plt.show()