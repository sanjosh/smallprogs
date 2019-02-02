#!/usr/bin/python3

import random 
from random import gauss

'''
inspired by Michel van Biezen
https://www.youtube.com/watch?v=-cD7WkbAIL0

Although initial estimate is incorrectly set to 50
and the Gaussian is generating random numbers centered around mean of 70

but the estimate converges to 70
and the Kalman Gain converges to 0.01

'''

class KalmanFilter:

  def __init__(self):
    # kalman gain is between [0, 1]
		# kg = 0 means estimate stable, measurement inaccurate
		# kg = 1 means estimate unstable, measurement accurate
    self.kg = 0.5 

    # error in measurement which is const depending on sensor
    self.e_meas = 4  

    # error in estimate
    self.e_est = []
    self.e_est.append(2)

    # set initial estimate 
    self.est = []
    self.est.append(50)

    # time = 0
    self.t = 0

  def update(self, mea):
    self.t = self.t + 1

    # update kalman gain
    self.kg = self.e_est[self.t - 1]/(self.e_est[self.t - 1] + self.e_meas)

    # update estimate
    self.est.append(self.est[self.t - 1] + self.kg * (mea - self.est[self.t - 1]))

    # update error in estimate
    self.e_est.append((1 - self.kg) * self.e_est[self.t-1])

    print(round(self.kg, 2), round(self.e_est[self.t], 2), round(self.est[self.t], 2))


def main():

  k = KalmanFilter()

  temp = []

  for j in range(100):
    temp.append(random.gauss(70, 10))

  for i in range(len(temp)):
    k.update(temp[i])

if __name__ == "__main__":
  main()
