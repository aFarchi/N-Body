#!/usr/bin/env python

import numpy             as np
import matplotlib.pyplot as plt
import matplotlib        as mpl

from matplotlib              import cm
from matplotlib              import gridspec
from mpl_toolkits.axes_grid1 import make_axes_locatable

# Parameters
outputDir             = '/Users/Alban/Desktop/test-nbody/'
particleFilePrefix    = 'xvp'
particleFileExtension = '.bin'

cubeLength            = 100.0

figureDir             = '/Users/Alban/Desktop/test-nbody/fig/'
figurePrefix          = particleFilePrefix
figureExtension       = '.pdf'

# Extensions <=> time steps
tSteps                = np.arange(101)
particleFileSuffix    = []
for t in tSteps:
    if np.mod(t,1) == 0 :
        particleFileSuffix.append(str(t))


figure = plt.figure()
ax     = plt.subplot(111)

gsCB   = gridspec.GridSpec(1, 1, left=0.93, bottom=0.1, right=0.96, top=0.9)
cax    = plt.subplot(gsCB[0, 0], frameon=False)
cmap   = cm.jet
norm   = mpl.colors.Normalize(vmin=0.0, vmax=cubeLength, clip=False)
cbar   = mpl.colorbar.ColorbarBase(cax, cmap=cmap, norm=norm, orientation='vertical')


for suffix in particleFileSuffix:
    fileName   = outputDir + particleFilePrefix + suffix + particleFileExtension
    figName    = figureDir + figurePrefix       + suffix + figureExtension
    f          = open(fileName, 'rb')

    nParticles = np.fromfile(f, dtype='int32', count=1)[0]
    xvpArray   = np.fromfile(f, count=6*nParticles).reshape((nParticles,6))

    ax.cla()
    ax.grid()
    ax.set_xlim(0.0, cubeLength)
    ax.set_ylim(0.0, cubeLength)
    ax.scatter(xvpArray[:,0], xvpArray[:,1], s=20, c=xvpArray[:,2], vmin=0.0, vmax=cubeLength, linewidths=0.0)
    plt.savefig(figName)
    print('Written '+figName)

plt.close()


