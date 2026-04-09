import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data = pd.read_csv('/Users/olandrre/Desktop/asimptotic/1/binary_mid2.csv', index_col=0)
data2 = pd.read_csv('/Users/olandrre/Desktop/asimptotic/1/binary_2.csv', index_col=0)

plt.figure(figsize=(10, 6))
plt.plot((data['X']), data['Y'], 'o', label='mid', color='blue')
plt.plot((data2['X']), data2['Y'], 'o', label='worst' ,color='green')

plt.xscale('log') 
plt.yscale('log')  

plt.ylabel('t')
plt.xlabel('N')
plt.grid(True, alpha=0.3)
plt.legend()
plt.show()