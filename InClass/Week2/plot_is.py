import matplotlib.pyplot as plt
import numpy as np

N, is_min, is_ave, is_max, dis_min, dis_ave, dis_max, ms_min, ms_ave, ms_max, hs_min, hs_ave, hs_max = np.loadtxt('output.csv', delimiter=',', unpack=True)

plt.plot(N, is_min, label="Insertion Sort Best")
plt.plot(N, is_ave, label="Inserion Sort Ave")
plt.plot(N, is_max, label="Inserion Sort Worst")
plt.plot(N, N*N/294000000, label="N^2 control")

plt.xlabel('N')
plt.ylabel('Time')
plt.title('Time Complexity Analysis')
plt.grid(True)
plt.legend()
plt.savefig("Complexity.png")
plt.show()
