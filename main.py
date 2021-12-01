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
