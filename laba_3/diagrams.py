import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def f(data_v, data_v2, title, filename):
    colors = {
        'naive': 'blue',
        'naive_FMA': 'green',
        'recursive': 'orange',
        'circle_recursive': 'purple',
        'kahan': 'red'
    }

    fig, axes = plt.subplots(4, 2, figsize=(14, 20))

    temp = sorted(data_v['T'].unique())
    number = sorted(data_v['N'].unique())
    methods = list(colors.keys())

    for idx, T in enumerate(temp):
        axe1 = axes[idx, 0]
        v1 = data_v[data_v['T'] == T]
        x = np.arange(len(number))
        width = 0.15

        for method_idx, method in enumerate(methods):
            errors = []

            for N in number:
                err = v1[(v1['method'] == method) & (v1['N'] == N)]['error'].values
                errors.append(err[0] if len(err) > 0 else 0)

            offset = (method_idx - len(methods)/2) * width
            bars = axe1.bar(x + offset, errors, width, label=method, color=colors[method])

            for bar, err in zip(bars, errors):
                if err > 0:
                    if err < 0.01:
                        label = f'{err:.2e}'
                    else:
                        label = f'{err:.4f}'
                axe1.text(bar.get_x() + bar.get_width()/2, bar.get_height(), label, ha='center', fontsize=3)

        axe1.set_yscale('log')
        axe1.set_ylabel('Error, %')
        axe1.set_title(f'(v), T = {T}')
        axe1.set_xticks(x)
        axe1.set_xticklabels(number)

        axe2 = axes[idx, 1]
        v2 = data_v2[data_v2['T'] == T]
        x = np.arange(len(number))
        width = 0.15

        for method_idx, method in enumerate(methods):
            errors = []

            for N in number:
                err = v2[(v2['method'] == method) & (v2['N'] == N)]['error'].values
                errors.append(err[0] if len(err) > 0 else 0)
            offset = (method_idx - len(methods)/2) * width

            bars = axe2.bar(x + offset, errors, width, label=method, color=colors[method])

            for bar, err in zip(bars, errors):
                if err > 0:
                    if err < 0.01:
                        label = f'{err:.2e}'
                    else:
                        label = f'{err:.2f}'
                axe2.text(bar.get_x() + bar.get_width()/2, bar.get_height(), label, ha='center', fontsize=3)

        axe2.set_yscale('log')
        axe2.set_ylabel('Error, %')
        axe2.set_title(f'(v^2), T = {T}')
        axe2.set_xticks(x)
        axe2.set_xticklabels(number)

    fig.legend(methods, fontsize=12)
    plt.suptitle(title, fontsize=25)
    plt.subplots_adjust(left=0.08, right=0.92, top=0.93, bottom=0.05, hspace=0.35, wspace=0.25)
    plt.savefig(filename, dpi=200)

data_v_float = pd.read_csv('laba_3/v_float.csv')
data_v2_float = pd.read_csv('laba_3/v2_float.csv')

data_v_double = pd.read_csv('laba_3/v_double.csv')
data_v2_double = pd.read_csv('laba_3/v2_double.csv')

f(data_v_float, data_v2_float, 'Сравнение методов интегрирования (float)', 'v_float.png')
f(data_v_double, data_v2_double, 'Сравнение методов интегрирования (double)', 'v_double.png')