import matplotlib.pyplot as plt
import numpy as np

N, is_min, is_ave, is_max, dis_min, dis_ave, dis_max, ms_min, ms_ave, ms_max, hs_min, hs_ave, hs_max = np.loadtxt('output.csv', delimiter=',', unpack=True)

plt.plot(N, is_ave, label="Insertion Sort Ave")
plt.plot(N, dis_ave, label="Div Insertion Sort Ave")
plt.plot(N, ms_ave, label="Merge Sort Ave")
plt.plot(N, hs_ave, label="Hybrid Sort Ave")

plt.xlabel('N')
plt.ylabel('Time')
plt.title('Time Complexity Analysis')
plt.grid(True)
plt.legend()
plt.savefig("Complexity.png")
plt.show()
