# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.


import numpy as np
import matplotlib.pyplot as plt
from numpy import *

data = np.fromfile("data.txt", dtype=int,sep=',')
hist=np.histogram(data)
plt.hist(data, bins=np.arange(data.min(), data.max()+1), rwidth=0.7, align='left')
plt.ylabel("Количество")
plt.xlabel("Высота дерева")

print("Минимальная высота", data.min())
print("Макисмальная высота", data.max())
print("Медиана", np.median(data))
print("Среднее значение", np.average(data))
plt.show()
# See PyCharm help at https://www.jetbrains.com/help/pycharm/
