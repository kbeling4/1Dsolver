import numpy as np
import matplotlib.pyplot as plt

# Read in scalar flux data
scalar = np.loadtxt('../build/src/scalar.txt', usecols=range(2,1))
xgrid  = np.loadtxt('../build/src/x_grid.txt', usecols=range(2,1))

x1 = []
y1 = []

for val in xgrid:
    x1.append(val)
    
for val in scalar:
    y1.append(val)

plt.plot(x1, y1, label='scalar')
plt.xlabel('position (cm)')
plt.ylabel('scalar flux (1/cm^2)')
plt.title('Scalar flux vs position')
plt.grid()

plt.show()
