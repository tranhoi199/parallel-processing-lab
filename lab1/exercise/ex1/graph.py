import numpy as np
import matplotlib.pyplot as plt


# results from serial version of matrix multiplication with size of matrices: 10, 100, 1000, 10000
serial_version = [0.009, 0.010, 18.421, 159.710] # 10, 100, 1000 va 10000()

# results from serial version of matrix multiplication with size of matrices: 10, 100, 1000, 10000.
pthread_version = [0.005,0.007,8.753,79.670]

matrix_sizes = ('10', '100', '1000', '2000')
x_pos = np.arange(len(serial_version))

plt.plot(serial_version, label = 'Serial Version')
plt.plot(pthread_version, label = 'Pthread Version')

plt.xlabel('Matrix sizes (N)')
plt.xticks(x_pos, matrix_sizes)
plt.ylabel('Execution time (s)')
plt.title('Matrix Multiplication in Parallel Computing')
plt.grid(True)
plt.legend()

plt.show()

