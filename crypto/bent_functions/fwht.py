from scipy import signal
from sympy import fwht
from scipy.fft import fft, ifft

import matplotlib.pyplot as plot
import matplotlib.pyplot

import numpy as np

# Sampling rate 1000 hz / second
t = np.linspace(0, 1, 128, endpoint=True)
#print(t.shape)
x = signal.square(2 * np.pi * 5 * t)
#x = signal.unit_impulse(t.shape)
# Plot the square wave signal
plot.subplot(3,1,1)
plot.plot(t, x)
plot.title('Square wave - 5 Hz sampled at 1000 Hz /second')
plot.xlabel('Time')
plot.ylabel('Amplitude')
plot.grid(True, which='both')
plot.axhline(y=0, color='k')
plot.ylim(-2, 2)

y = fwht(x)
plot.subplot(3,1,2)
plot.plot(t, y, color='red')
plot.title('WHT coefficients')
plot.xlabel('Sequency index')
plot.ylabel('Amplitude')
plot.grid(True, which='both')
plot.axhline(y=0, color='k')
plot.ylim(-2, 2)


y = fft(x)
plot.subplot(3,1,3)
plot.plot(t, y)
plot.title('FFT coefficients')
plot.xlabel('fft index')
plot.ylabel('Amplitude')
plot.grid(True, which='both')
plot.axhline(y=0, color='k')
plot.ylim(-2, 2)

plot.show()


