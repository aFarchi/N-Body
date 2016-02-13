#!/usr/bin/env python

import numpy             as np
import matplotlib.pyplot as plt
import matplotlib.cm     as cm

# Parameters
outputDir            = '/Users/Alban/Desktop/test-nbody/'
#densityFilePrefix    = 'xvp_den'
densityFilePrefix    = 'denTest'
densityFileExtension = '.bin'

cubeLength           = 100.0

figureDir            = '/Users/Alban/Desktop/test-nbody/fig/'
figurePrefix         = densityFilePrefix
figureExtension      = '.pdf'

# Extensions <=> time steps
#tSteps               = np.arange(101)
#densityFileSuffix    = []
#for t in tSteps:
#    if np.mod(t,1) == 0 :
#        densityFileSuffix.append(str(t))
densityFileSuffix = ['']

kwargs = {}
kwargs['interpolation'] = 'nearest'
kwargs['origin']        = 'lower'
kwargs['cmap']          = cm.jet
kwargs['extent']        = [0.0, 1.0, 0.0, 1.0]

for suffix in densityFileSuffix:
    fileName = outputDir + densityFilePrefix + suffix + densityFileExtension
    figName  = figureDir + figurePrefix      + suffix + figureExtension
    f        = open(fileName, 'rb')

    nGrid    = np.fromfile(f, dtype='int32', count=1)[0]
    denField = np.fromfile(f, count=nGrid*nGrid*nGrid).reshape((nGrid,nGrid,nGrid))

    matrix   = np.sum(denField, axis=2)

    figure   = plt.figure()
    ax       = plt.subplot(111)

    im       = ax.imshow(matrix.transpose(), **kwargs)
    ax.set_xticks([])
    ax.set_yticks([])

    plt.colorbar(im)

    plt.savefig(figName)
    print('Written '+figName)
    plt.close()


