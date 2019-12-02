import numpy as np
import matplotlib.pyplot as plt
from reader import read

PRINTER = read()

for i in range(0, len(PRINTER)):
    if i == 0 and PRINTER[i]:
        scalar = np.loadtxt('../build/src/scalar.txt', usecols=range(2,1))

        x = []
        y = []

        for pair in scalar:
            x.append(pair[0])
            y.append(pair[1])

        plt.figure(1)
        plt.plot(x, y, label='scalar')
        plt.xlabel('Position (cm)')
        plt.ylabel('Scalar Flux (1/cm^2)')
        plt.title('Scalar Flux vs Position')
        plt.grid()

    if i == 1 and PRINTER[i]:
        errIn = np.loadtxt('../build/src/error_In.txt', usecols=range(2,1))
        
        x = []
        y = []

        for pair in errIn:
            x.append(pair[0])
            y.append(pair[1])

        plt.figure(2)
        plt.semilogy(x, y, label='Scalar Flux Error')
        plt.xlabel('Iteration')
        plt.ylabel('Scalar Flux Error')
        plt.title('Scalar Flux Error vs Iteration NUmber')
        plt.grid()

    if i == 2 and PRINTER[i]:
        k_vals = np.loadtxt('../build/src/k_vals.txt', usecols=range(2,1))

        x = []
        y = []

        for pair in k_vals:
            x.append(pair[0])
            y.append(pair[1])

        plt.figure(4)
        plt.plot(x, y, label='k-value')
        plt.hlines(y[-1], x[0], x[-1], colors='r', linestyles='dashed')
        plt.xlabel('Iteration')
        plt.ylabel('k-value')
        plt.title('k-value vs Iteration Number')
        plt.grid()

    if i == 3 and PRINTER[i]:
        errOut = np.loadtxt('../build/src/error_Out.txt', usecols=range(2,1))
        
        x = []
        y = []

        for pair in errOut:
            x.append(pair[0])
            y.append(pair[1])

        plt.figure(3)
        plt.semilogy(x, y, label='k-value Error')
        plt.xlabel('Iteration')
        plt.ylabel('K-value Error')
        plt.title('K-value Error vs Iteration NUmber')
        plt.grid()
    

        
plt.show()
