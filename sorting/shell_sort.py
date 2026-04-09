import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

data1 = pd.read_csv('sorting/Shell_sort_1.csv', index_col=0)
data2 = pd.read_csv('sorting/Shell_sort_2.csv', index_col=0)
data3 = pd.read_csv('sorting/Shell_sort_3.csv', index_col=0)

skip = 0

def slope(data):
    x = np.log(data['elements'][skip:])
    y = np.log(data['time'][skip:])
    k, b = np.polyfit(x, y, 1)
    return k, b

def line(data, color, label, skip):
    plt.plot(data['elements'][skip:], data['time'][skip:], 'o', color=color, markersize=3)
    k, b = slope(data)
    x0 = np.log(data['elements'][skip:])
    y0 = np.exp(b) * (data['elements'][skip:] ** k)
    plt.plot(data['elements'][skip:], y0, '-', color=color, linewidth=2, label=f'{label}, slope={k:1f}')
    return k

plt.figure(figsize=(10, 6))

k1 = line(data1, 'red', 'classic', skip)
k2 = line(data2, 'green', 'hibbard', skip)
k3 = line(data3, 'blue', 'fibonacci', skip)

plt.xscale('log') 
plt.yscale('log')  

plt.ylabel('t')
plt.xlabel('N')
plt.grid(True, alpha=0.3)
plt.title('Зависимость t(N)')
plt.legend()
plt.show()
