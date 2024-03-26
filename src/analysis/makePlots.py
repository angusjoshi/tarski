#!/bin/python3

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
    'queries': [1, 7, 218, 1718, 11014],
    'times': [0.000014, 0.000036, 0.00089, 0.0080, 0.106],
}

simpleStochasticData = {
    'recbin': {
        'testSize': [3, 5, 7, 9, 11, 13],
        'queries': [23, 216, 726, 2387, 5099, 12306],
        'times': [0.0036, 0.0614, 0.284, 1.189, 2.876, 8.22941],
    },
    'decomp': {
        'testSize': [3, 5, 7, 9, 11, 13],
        'queries': [23, 115, 190, 1429, 1657, 2586],
        'times': [0.0047, 0.0469, 0.099, 0.6936, 1.046, 1.8464],
    },
    'monDecomp': {
        'testSize': [3, 5, 7, 9, 11, 13],
        'queries': [28, 479, 2895, 27837, 76880, 978393],
        'times': [0.0061, 0.147, 1.513, 17.61, 53.40, 736.1],
    },
    # todo
    'walkData': {
        'testSize': [10, 100, 1000, 10000, 100000],
        'queries': [19, 23, 12, 10, 6],
        'times': [0.0035, 0.018, 0.067, 0.975, 6.67],

    }
}

shapleyData = {
    'recbin': {
        'testSize': [2, 3, 4, 5, 6],
        'queries': [77, 350, 1123, 3072, 7848],
        'times': [11.6, 103.0, 416.4, 1297, 4245],
    },
    'decomp': {
        'testSize': [2, 3, 4, 5, 6],
        'queries': [78, 55, 306, 1157, 1228],
        'times': [10.72, 8.89, 71.3, 459.0, 634.7],
    },
    'monDecomp': {
        'testSize': [2, 3, 4, 5, 6],
        'queries': [76, 49, 1201, 724, 8713],
        'times': [10.4, 8.44, 298, 292, 4671],
    },
    'walkData': {
        'testSize': [10, 15, 20, 30, 40],
        'queries': [48, 49, 50, 52, 52],
        'times': [54.5, 74.94, 107.2, 176.2, 255.4],

    }
}

epsilonData = {
    'simple': {
        'recbin': {
            'epsilon': [0.1, 0.01, 0.001, 0.0001, 0.00001, 0.000001],
            'queries': [525, 3145, 10012, 48649, 81726, 149171],
            'times': [ 0.278, 1.733, 5.247, 26.7, 43.17, 79.47]
        },
        'decomp': {
            'epsilon': [0.1, 0.01, 0.001, 0.0001, 0.00001, 0.000001],
            'queries': [143, 831, 2531, 10350, 19877, 23802],
            'times': [0.0845, 0.5016, 1.538, 6.606, 12.31, 15.76]
        },
        'monDecomp': {
            'epsilon': [0.1, 0.01, 0.001, 0.0001, 0.00001, 0.000001],
            'queries': [4079, 22619, 84430, 214668, 335322, 1035565],
            'times': [2.478, 13.95, 51.49, 144.7, 289.5, 693.7]
        },
        'walkData': {
            'epsilon': [0.1, 0.01, 0.001, 0.0001, 0.00001, 0.000001],
            'queries': [5, 10, 21, 12, 56, 83],
            'times': [0.0012, 0.0021, 0.0043, 0.0027, 0.011, 0.016]
        },
    },
    'shapley': {
        'recbin': {
            'epsilon': [0.5, 0.1, 0.01, 0.001, 0.0001, 0.00001, 0.000001],
            'queries': [111, 191, 370, 551, 779, 1389, 1779],
            'times': [42.0, 52.7, 77.56, 114.4, 176.7, 283.6, 338.8]
        },
        'decomp': {
            'epsilon': [0.5, 0.1, 0.01, 0.001, 0.0001, 0.00001, 0.000001],
            'queries': [29, 39, 55, 73, 89, 118, 120],
            'times': [5.48, 7.27, 10.5, 14.8, 17.2, 24.1, 23.2]
        },
        'monDecomp': {
            'epsilon': [0.5, 0.1, 0.01, 0.001, 0.0001, 0.00001, 0.000001],
            'queries': [32, 41, 54, 71, 93, 103, 122],
            'times': [5.95, 7.93, 10.7, 13.8, 17.7, 21.0, 23.38]
        },
        'walkData': {
            'epsilon': [0.5, 0.1, 0.01, 0.001, 0.0001, 0.00001, 0.000001],
            'queries': [26, 33, 43, 54, 64, 74, 85],
            'times': [7.97, 7.57, 8.64, 9.22, 12.2, 20.14, 25.1]
        },
    }
}

algorithmNames = {
    'walkData': 'Kleene, Tarski',
    'recbin': 'Dan, Qi, Ye',
    'decomp': 'Fearnley, Pálvölgyi, Savani',
    'monDecomp': 'Chen, Li'
}

def plotSimpleStochastic():
    for type in ['queries', 'times']:
        for algorithm in ['recbin', 'decomp', 'monDecomp']:
            d = simpleStochasticData[algorithm]
            plt.plot(d['testSize'], d[type], label=algorithmNames[algorithm])

        plt.title(f"Average {type} for random simple stochastic game instance (n=20)")
        plt.yscale('log')
        plt.xlabel('Number of vertices')
        if type == 'times':
            plt.ylabel('Average time (ms)')
            pass
        else:
            plt.ylabel('Average number of queries')

        plt.legend()
        plt.show()

        d = simpleStochasticData['walkData']
        plt.plot(d['testSize'], d[type])
        plt.title(f"Average {'steps' if type == 'queries' else 'time'} for random simple stochastic game instance walk (n=20)")
        plt.xscale('log')
        if type == 'times':
            plt.yscale('log')
        plt.xlabel('Number of vertices')
        if type == 'times':
            plt.ylabel('Average time (ms)')
            pass
        else:
            plt.ylabel('Average number of steps')
        plt.show()

def plotEpsilons():
    for problem in ['shapley', 'simple']:
        for type in ['queries', 'times']:
            for algorithm in ['recbin', 'decomp', 'monDecomp', 'walkData']:
                d = epsilonData[problem][algorithm]
                plt.plot(d['epsilon'], d[type], label=algorithmNames[algorithm])

            title = f"Average {type} for random {problem} stochastic game instance (n=20)"
            if problem == 'shapley':
                title += '\ninstance size = 3'
            else:
                title += '\ninstance size = 11'

            plt.title(title)

            plt.xscale('log')
            plt.yscale('log')
            plt.xlabel('Approximation factor')
            plt.gca().invert_xaxis()
            if type == 'times':
                plt.ylabel('Average time (ms)')
                pass
            else:
                plt.ylabel('Average number of queries')
            plt.legend()
            plt.show()


def plotShapley():
    for type in ['queries', 'times']:
        for algorithm in ['recbin', 'decomp', 'monDecomp']:
            d = shapleyData[algorithm]
            plt.plot(d['testSize'], d[type], label=algorithmNames[algorithm])

        plt.title(f"Average {type} for random shapley stochastic game instance (n=20)")
        plt.yscale('log')
        plt.xlabel('Number of vertices')
        if algorithm == 'walkData':
            plt.xscale('log')
        if type == 'times':
            plt.ylabel('Average time (ms)')
            pass
        else:
            plt.ylabel('Average number of queries')
        plt.legend()
        plt.show()

        d = shapleyData['walkData']
        plt.plot(d['testSize'], d[type])
        plt.title(f"Average {'steps' if type == 'queries' else 'time'} for random shapley stochastic game instance walk (n=20)")
        plt.xlabel('Number of vertices')
        if type == 'times':
            plt.ylabel('Average time (ms)')
        else:
            plt.ylabel('Average number of steps')
        plt.show()

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
    plt.plot(walkData['testSize'], walkData['queries'])
    plt.title('Average walk length for random arrival instance (n=20)')
    plt.xlabel('Number of vertices')
    plt.ylabel('Average queries in walk')
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

plotEpsilons()
# plotSimpleStochastic()
# plotShapley()
# plotAverageQueries()
# plotAverageTime()
# plotWalkSteps()
# plotWalkTime()


