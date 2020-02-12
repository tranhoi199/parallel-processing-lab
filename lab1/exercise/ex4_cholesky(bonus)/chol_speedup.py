import numpy as np
import matplotlib.pyplot as plt

plt.figure(figsize=(12,7))

# results from serial version of pi calculation
chol_serial = [0.000929, 1.1194, 8.62048, 180.573, ]

# results from openmp on host version of chol calculation: 8 threads
chol_omp_8threads = []

# results from openmp on host version of chol calculation: 16 threads
chol_omp_16threads = []

# results from openmp on host version of chol calculation: 32 threads
chol_omp_32threads = []

# results from openmp on host version of chol calculation: 48 threads
chol_omp_48threads = []

loops = ('100', '1000', '2000', '4000', '6000', '8000', '10000')
x_pos = np.arange(len(chol_serial))

plt.plot(chol_serial, label = 'chol_serial', color='black', marker='*')

plt.plot(chol_omp_8threads, label = 'chol_omp_8threads')
plt.plot(chol_omp_16threads, label = 'chol_omp_16threads', linestyle='--', marker='o')
plt.plot(chol_omp_32threads, label = 'chol_omp_32threads', linestyle=':', marker='s')
plt.plot(chol_omp_48threads, label = 'chol_omp_48threads')

plt.xlabel('Matrix sizes (N)')
plt.xticks(x_pos, loops)
plt.ylabel('Execution time (s)')
plt.title('chol Calculation in Parallel Computing')
plt.grid(True)
plt.legend()

plt.show()