import numpy as np
import matplotlib.pyplot as plt

plt.figure(figsize=(12,7))

# results from serial version of pi calculation
pi_serial = [0.021768, 0.210196, 2.0704, 7.64486,11.1792, 14.5713]

# results from openmp on host version of pi calculation: 8 threads
pi_omp_8threads = [0.01485,0.139777,2.62965,5.28052,5.46561, 6.65555]

# results from openmp on host version of pi calculation: 16 threads
pi_omp_16threads = [ 0.014698,0.133341,1.26872,4.58794,5.56647, 6.76215]

# results from openmp on host version of pi calculation: 32 threads
pi_omp_32threads = [0.009613,0.088251,0.793568,2.96612,5.01085,6.31294]

# results from openmp on host version of pi calculation: 48 threads
pi_omp_48threads = [0.010201,0.087593,0.794389,2.1457,4.39537,6.19422]

loops = ('1000000', '10000000', '100M', '200M','250M', '300M')
x_pos = np.arange(len(pi_serial))

plt.plot(pi_serial, label = 'pi_serial', color='black', marker='*')

plt.plot(pi_omp_8threads, label = 'pi_omp_8threads')
plt.plot(pi_omp_16threads, label = 'pi_omp_16threads', linestyle='--', marker='o')
plt.plot(pi_omp_32threads, label = 'pi_omp_32threads', linestyle=':', marker='s')
plt.plot(pi_omp_48threads, label = 'pi_omp_48threads')

plt.xlabel('Loop sizes (N)')
plt.xticks(x_pos, loops)
plt.ylabel('Execution time (s)')
plt.title('Pi Calculation in Parallel Computing by Riemann Integral method')
plt.grid(True)
plt.legend()

plt.show()
