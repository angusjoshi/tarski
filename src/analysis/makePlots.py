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
    'walkData': {
        'testSize': [10, 100, 1000, 10000, 100000],
        'queries': [19, 23, 12, 10, 6],
        'times': [0.0035, 0.018, 0.067, 0.975, 6.67],

    }
}

longWalkData = {
    'recbin': {
        'testSize': [3, 6, 9, 12, 15],
        'queries': [4, 215, 2525, 17491, 143923],
        'times': [0.0005, 0.05, 0.88, 8.1, 89.0],
    },
    'decomp': {
        'testSize': [3, 7, 10, 13, 15, 18, 24],
        'queries': [4, 127, 968, 6109, 33824, 116885, 676685],
        'times': [0.0004, 0.050, 0.435, 3.44, 17.6, 75.9, 590],
    },
    'monDecomp': {
        'testSize': [3, 5, 7, 9, 11, 13],
        'queries': [4, 186, 2085, 21043, 175119, 1263033],
        'times': [0.0015, 0.041, 0.648, 8.61, 86.9, 740.1],
    },
    'walkData': {
        'testSize': [3, 6, 11, 17, 22],
        'queries': [7, 63, 2047, 131071, 4194303],
        'times': [0.00027, 0.0025, 0.086, 8.38, 379.1],

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
            'epsilon': [0.5, 0.1, 0.01, 0.001, 0.0001],
            'queries': [1553, 3493, 8488, 18008, 36145],
            'times': [881.5, 1751, 4267, 9104, 18207]
        },
        'decomp': {
            'epsilon': [0.5, 0.1, 0.01, 0.001, 0.0001],
            'queries': [320, 541, 1253, 2172, 2763],
            'times': [189.1, 305.6, 645.6, 1097, 1379]
        },
        'monDecomp': {
            'epsilon': [0.5, 0.1, 0.01, 0.001, 0.0001],
            'queries': [3492, 5045, 9314, 13469, 19336],
            'times': [1726, 2452, 4509, 6489, 9490]
        },
        'walkData': {
            'epsilon': [0.5, 0.1, 0.01, 0.001, 0.0001],
            'queries': [28, 36, 45, 56, 66],
            'times': [14.2, 17.2, 21.8, 26.9, 31.7]
        },
    }
}

algorithmNames = {
    'walkData': 'Kleene, Tarski',
    'recbin': 'Dang, Qi, Ye',
    'decomp': 'Fearnley, Pálvölgyi, Savani',
    'monDecomp': 'Chen, Li'
}

pltsFolder = '../../dissertation/plots'

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
        else:
            plt.ylabel('Average number of queries')

        plt.legend(loc='upper left')
        plt.savefig(f'{pltsFolder}/simple_{type}.png')
        plt.close()


        d = simpleStochasticData['walkData']
        plt.plot(d['testSize'], d[type])
        plt.title(f"Average {'number of iterations' if type == 'queries' else 'time'} for value\n"
                  f"iteration on random simple stochastic game instance walk (n=20)")

        plt.xscale('log')
        if type == 'times':
            plt.yscale('log')
        plt.xlabel('Number of vertices')
        if type == 'times':
            plt.ylabel('Average time (ms)')
            pass
        else:
            plt.ylabel('Average number of iterations')

        plt.savefig(f'{pltsFolder}/simple_{"iterations" if type == "queries" else "iter_time"}')
        plt.close()

def plotEpsilons():
    for problem in ['shapley', 'simple']:
        for type in ['queries', 'times']:
            for algorithm in ['recbin', 'decomp', 'monDecomp', 'walkData']:
                d = epsilonData[problem][algorithm]
                plt.plot(d['epsilon'],
                         d[type],
                         label="Value iteration" if algorithm == "walkData" else algorithmNames[algorithm])

            title = f"Average {type} for random {problem} stochastic game instance (n=20)"
            if problem == 'shapley':
                title += '\ninstance size = 6'
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
            plt.legend(loc='upper left')

            plt.savefig(f'{pltsFolder}/{problem}_eps_{type}')
            plt.close()


def plotShapley():
    for type in ['queries', 'times']:
        for algorithm in ['recbin', 'decomp', 'monDecomp']:
            d = shapleyData[algorithm]
            plt.plot(d['testSize'], d[type], label=algorithmNames[algorithm])

        plt.title(f"Average {type} for random shapley stochastic game instance (n=20)")
        plt.yscale('log')
        plt.xlabel('Number of vertices')

        if type == 'times':
            plt.ylabel('Average time (ms)')
        else:
            plt.ylabel('Average number of queries')

        plt.legend(loc='upper left')
        plt.savefig(f'{pltsFolder}/shapley_{type}.png')
        plt.close()

        d = shapleyData['walkData']
        plt.plot(d['testSize'], d[type])
        plt.title(f"Average {'iterations' if type == 'queries' else 'time'} for value iteration on\n"
                  f"random shapley stochastic game instance walk (n=20)")
        plt.xlabel('Number of vertices')
        if type == 'times':
            plt.ylabel('Average time (ms)')
        else:
            plt.ylabel('Average number of steps')
        plt.savefig(f'{pltsFolder}/shapley_{"iterations" if type == "queries" else "iter_time"}.png')
        plt.close()

def plotLongWalk():
    for type in ['queries', 'times']:
        for algorithm in ['recbin', 'decomp', 'monDecomp', 'walkData']:
            d = longWalkData[algorithm]
            plt.plot(d['testSize'],
                     d[type],
                     label="walk" if algorithm == 'walkData' else algorithmNames[algorithm])

        plt.title(f"Average {type} for longest arrival instance (n=20)")
        plt.yscale('log')
        plt.xlabel('Number of vertices')
        if type == 'times':
            plt.ylabel('Average time (ms)')
            pass
        else:
            plt.ylabel('Average number of queries')
        plt.legend(loc='upper left')
        plt.savefig(f'{pltsFolder}/arrival_long_{type}')
        plt.close()

def plotAverageQueries():
    plt.plot(recBinData['testSize'], recBinData['queries'], label='Dang, Qi, Ye')
    plt.plot(decompData['testSize'], decompData['queries'], label='Fearnley, Pálvölgyi, Savani')
    plt.plot(monDecompData['testSize'], monDecompData['queries'], label='Chen, Li')

    plt.title('Average queries for random arrival instance (n=20)')
    plt.yscale('log')
    plt.xlabel('Number of vertices')
    plt.ylabel('Average number of queries')

    plt.legend(loc='upper left')
    plt.savefig(f'{pltsFolder}/arrival_queries.png')
    plt.close()

def plotAverageTime():
    plt.plot(recBinData['testSize'], recBinData['times'], label='Dang, Qi, Ye')
    plt.plot(decompData['testSize'], decompData['times'], label='Fearnley, Pálvölgyi, Savani')
    plt.plot(monDecompData['testSize'], monDecompData['times'], label='Chen, Li')

    plt.title('Average time for random arrival instance (n=20)')
    plt.yscale('log')
    plt.xlabel('Number of vertices')
    plt.ylabel('Average time (ms)')

    plt.legend(loc='upper left')
    plt.savefig(f'{pltsFolder}/arrival_time.png')
    plt.close()

def plotWalkSteps():
    plt.plot(walkData['testSize'], walkData['queries'])
    plt.title('Average walk length for random arrival instance (n=20)')
    plt.xlabel('Number of vertices')
    plt.ylabel('Average steps in walk')
    plt.xscale('log')
    plt.yscale('log')

    plt.legend(loc='upper left')
    plt.savefig(f'{pltsFolder}/arrival_steps.png')
    plt.close()
def plotWalkTime():
    plt.plot(walkData['testSize'], walkData['times'])
    plt.title('Average time to compute walk for random arrival instance (n=20)')
    plt.xlabel('Number of vertices')
    plt.ylabel('Average time (ms)')
    plt.xscale('log')
    plt.yscale('log')

    plt.legend(loc='upper left')
    plt.savefig(f'{pltsFolder}/arrival_wtime.png')
    plt.close()

plotLongWalk()
plotEpsilons()
plotSimpleStochastic()
plotShapley()
plotAverageQueries()
plotAverageTime()
plotWalkSteps()
plotWalkTime()


