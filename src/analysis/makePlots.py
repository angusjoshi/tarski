import pandas as pd
import matplotlib.pyplot as plt

decompData = {
    'testSize': [3, 6, 9, 12, 15, 18],
    'queries': [2, 20, 208, 3707, 51598, 351584],
    'times': [0.0003, 0.005, 0.07, 1.45, 23.9, 204.6],
}

recBinData = {
    'testSize': [3, 5, 7, 9],
    'queries': [2, 136, 26410, 6642940],
    'times': [0.0002, 0.023, 6.79, 2232],
}

def plotAverageQueries():
    decDf = pd.DataFrame(decompData)
    recDf = pd.DataFrame(recBinData)

    plt.plot(decompData['testSize'], decompData['queries'], label='Fearnley, Pálvölgyi, Savani')
    plt.plot(recBinData['testSize'], recBinData['queries'], label='Dan, Qi, Ye')

    plt.title('Average queries for random arrival instance (n=20)')
    plt.yscale('log')
    plt.xlabel('Number of vertices')
    plt.ylabel('Average number of queries')

    plt.legend()
    plt.show()

def plotAverageTime():
    decDf = pd.DataFrame(decompData)
    recDf = pd.DataFrame(recBinData)

    plt.plot(decompData['testSize'], decompData['times'], label='Fearnley, Pálvölgyi, Savani')
    plt.plot(recBinData['testSize'], recBinData['times'], label='Dan, Qi, Ye')

    plt.title('Average time for random arrival instance (n=20)')
    plt.yscale('log')
    plt.xlabel('Number of vertices')
    plt.ylabel('Average time (ms)')

    plt.legend()
    plt.show()

plotAverageQueries()
plotAverageTime()


