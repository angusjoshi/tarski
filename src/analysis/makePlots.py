import pandas as pd
import matplotlib.pyplot as plt

recBinData = {
    'testSize': [3, 5, 7, 9],
    'queries': [6, 344, 59507, 15644153],
    'times': [0.00073, 0.0568, 15.22, 5330],
}

decompData = {
    'testSize': [3, 6, 9, 12, 15, 18],
    'queries': [12, 141, 2727, 22274, 132383, 1466120],
    'times': [0.002, 0.05, 0.99, 8.70, 65.3, 833],
}

monDecompData = {
    'testSize': [3, 5, 7, 9, 11, 13],
    'queries': [4, 106, 1808, 23081, 230156, 2658314],
    'times': [0.00128, 0.0247, 0.5639, 9.306, 117.39, 1611],
}

walkData = {
    'testSize': [10, 100, 1000, 10000, 100000],
    'steps': [1, 7, 218, 1718, 11014],
    'times': [0.000014, 0.000036, 0.00089, 0.0080, 0.106],
}


def plotAverageQueries():
    plt.plot(recBinData['testSize'], recBinData['queries'], label='Dan, Qi, Ye')
    plt.plot(decompData['testSize'], decompData['queries'], label='Fearnley, Pálvölgyi, Savani')
    plt.plot(monDecompData['testSize'], monDecompData['queries'], label='Chen, Li')

    plt.title('Average queries for random arrival instance (n=20)')
    plt.yscale('log')
    plt.xlabel('Number of vertices')
    plt.ylabel('Average number of queries')

    plt.legend()
    plt.show()

def plotAverageTime():
    plt.plot(recBinData['testSize'], recBinData['times'], label='Dan, Qi, Ye')
    plt.plot(decompData['testSize'], decompData['times'], label='Fearnley, Pálvölgyi, Savani')
    plt.plot(monDecompData['testSize'], monDecompData['times'], label='Chen, Li')

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

plotAverageQueries()
plotAverageTime()
# plotWalkSteps()
# plotWalkTime()


