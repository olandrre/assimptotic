import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('combSorto0.csv', index_col=0)

plt.figure(figsize=(10, 6))
# plt.errorbar(data['elements'], data['time'], yerr=0, xerr=0, fmt='.', capsize=3, color='green')
plt.errorbar(data['elements'], data['swaps'], yerr=0, xerr=0, fmt='.', capsize=3, color='blue')


plt.xscale('log') 
plt.yscale('log')  

plt.ylabel('k')
plt.xlabel('N')
plt.grid(True, alpha=0.3)
plt.title('Зависимость k(N)')
plt.legend()
plt.show()