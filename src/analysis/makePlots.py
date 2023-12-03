import pandas as pd
import matplotlib.pyplot as plt

decompData = {
    'testSize': [3, 6, 9, 12, 15, 18],
    'queries': [12, 141, 2727, 22274, 132383, 1466120],
    'times': [0.002, 0.05, 0.99, 8.70, 65.3, 833],
}

recBinData = {
    'testSize': [3, 5, 7, 9],
    'queries': [10, 639, 140839, 25625439],
    'times': [0.001, 0.12, 35.4, 8768],
}

walkData = {
    'testSize': [10, 100, 1000, 10000, 100000],
    'steps': [1, 7, 218, 1718, 11014],
    'times': [0.000014, 0.000036, 0.00089, 0.0080, 0.106],
}

def plotAverageQueries():
    plt.plot(decompData['testSize'], decompData['queries'], label='Fearnley, Pálvölgyi, Savani')
    plt.plot(recBinData['testSize'], recBinData['queries'], label='Dan, Qi, Ye')

    plt.title('Average queries for random arrival instance (n=20)')
    plt.yscale('log')
    plt.xlabel('Number of vertices')
    plt.ylabel('Average number of queries')

    plt.legend()
    plt.show()

def plotAverageTime():
    plt.plot(decompData['testSize'], decompData['times'], label='Fearnley, Pálvölgyi, Savani')
    plt.plot(recBinData['testSize'], recBinData['times'], label='Dan, Qi, Ye')

    plt.title('Average time for random arrival instance (n=20)')
    plt.yscale('log')
    plt.xlabel('Number of vertices')
    plt.ylabel('Average time (ms)')

    plt.legend()
    plt.show()

def plotWalkSteps():
    plt.plot(walkData['testSize'], walkData['steps'])
    plt.title('Average walk length for random arrival instance (n=20)')
    plt.xlabel('Number of vertices')
    plt.ylabel('Average steps in walk')
    plt.xscale('log')
    plt.yscale('log')

    plt.legend()
    plt.show()
def plotWalkTime():
    plt.plot(walkData['testSize'], walkData['times'])
    plt.title('Average time to compute walk for random arrival instance (n=20)')
    plt.xlabel('Number of vertices')
    plt.ylabel('Average time (ms)')
    plt.xscale('log')
    plt.yscale('log')

    plt.legend()
    plt.show()

# plotAverageQueries()
# plotAverageTime()
plotWalkSteps()
plotWalkTime()


