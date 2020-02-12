import numpy as np
import matplotlib.pyplot as plt

plt.figure(figsize=(12,7))

# results from serial version of pi calculation
sgemm_serial = [ 0.004461, 5.1802, 38.7382, 180.573 ]
# 0.004461, 5.1802, 38.7382
# results from openmp on host version of sgemm calculation: 8 threads
sgemm_omp_8threads = [0.001147,1.07362,6.77483,31.8085, 101.339]

# results from openmp on host version of sgemm calculation: 16 threads
sgemm_omp_16threads = [0.000994,0.465896,3.54219,16.1335,50.8369]

# results from openmp on host version of sgemm calculation: 32 threads
sgemm_omp_32threads = [ 0.00128, 0.381392, 2.74637, 10.2054,30.8246]

# results from openmp on host version of sgemm calculation: 48 threads
sgemm_omp_48threads = [0.004496,0.325616, 2.56176, 9.98931, 27.6423]

loops = ('100', '1000', '2000', '3000', '4000', '8000', '10000')
x_pos = np.arange(len(sgemm_serial))

plt.plot(sgemm_serial, label = 'sgemm_serial', color='black', marker='*')

plt.plot(sgemm_omp_8threads, label = 'sgemm_omp_8threads')
plt.plot(sgemm_omp_16threads, label = 'sgemm_omp_16threads', linestyle='--', marker='o')
plt.plot(sgemm_omp_32threads, label = 'sgemm_omp_32threads', linestyle=':', marker='s')
plt.plot(sgemm_omp_48threads, label = 'sgemm_omp_48threads')

plt.xlabel('Matrix sizes (N)')
plt.xticks(x_pos, loops)
plt.ylabel('Execution time (s)')
plt.title('SGEMM Calculation in Parallel Computing')
plt.grid(True)
plt.legend()

plt.show()
