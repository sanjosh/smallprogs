from scipy import signal
from sympy import fwht
from scipy.fft import fft, ifft
import numpy

import matplotlib.pyplot as plt

import numpy as np
import math

# Generate truth table for random Boolean function
percent_ones = 0.5
num_boolean_var = 4
num_combinations = pow(2, num_boolean_var)

t = np.linspace(0, num_combinations, num_combinations, endpoint=True)
print(t.shape[0])

# generate random truth table
truth_table = numpy.random.choice([0, 1], size=t.shape[0], p=[1 - percent_ones, percent_ones])
print(truth_table)
# Plot the square wave signal
plt.subplot(3,1,1)
plt.plot(t, truth_table)
plt.title('Boolean function ' + str(num_boolean_var) + ' variables ')
plt.xlabel('input')
plt.ylabel('truth table')
plt.grid(True, which='both')
plt.axhline(y=0, color='k')
#plt.ylim(-max_coeff, max_coeff)

y = fwht(truth_table)
print(min(y), max(y))
plt.subplot(3,1,2)
plt.plot(t, y, color='red')
plt.title('Walsh Hadamard Transform')
plt.xlabel('Sequency index')
plt.grid(True, which='both')
plt.axhline(y=0, color='k')
#plt.ylim(min(y), max(y))


y = fft(truth_table)
print(min(y), max(y))
plt.subplot(3,1,3)
plt.plot(t, y)
plt.title('Fast Fourier transform')
plt.xlabel('fft index')
plt.grid(True, which='both')
plt.axhline(y=0, color='k')
#plt.ylim(min(y), max(y))

plt.subplots_adjust(left=0.1,
                    bottom=0.1,
                    right=0.9,
                    top=0.9,
                    wspace=0.4,
                    hspace=1)

plt.show()


