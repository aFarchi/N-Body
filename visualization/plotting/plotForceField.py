#!/usr/bin/env python

import numpy             as np
import matplotlib.pyplot as plt
import matplotlib.cm     as cm

# Parameters
outputDir            = '/Users/aFarchi/Desktop/test/'
#densityFilePrefix    = 'xvp_den'
densityFilePrefix    = 'potTest'
densityFileExtension = '.bin'

cubeLength           = 100.0

figureDir            = '/Users/aFarchi/Desktop/test/'
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

    fileName = 'fxTest.bin'
    f        = open(fileName, 'rb')
    nGrid    = np.fromfile(f, dtype='int32', count=1)[0]
    fxField  = np.fromfile(f, count=nGrid*nGrid*nGrid).reshape((nGrid,nGrid,nGrid))
    fxField  = np.sum(fxField, axis=2)

    fileName = 'fyTest.bin'
    f        = open(fileName, 'rb')
    nGrid    = np.fromfile(f, dtype='int32', count=1)[0]
    fyField  = np.fromfile(f, count=nGrid*nGrid*nGrid).reshape((nGrid,nGrid,nGrid))
    fyField  = np.sum(fyField, axis=2)

    f2Field  = np.power( np.power( fxField , 2.0 ) + np.power( fyField , 2.0 ) , 0.5 ) 
    print(f2Field.min())
    print(f2Field.mean())
    print(f2Field.max())

    xxx      = np.linspace(0.0, 1.0, nGrid)
    yyy      = np.linspace(0.0, 1.0, nGrid)
    XXX,YYY  = np.meshgrid(xxx,yyy,indexing='ij')


    figure   = plt.figure()
    ax       = plt.subplot(111)

    im       = ax.imshow(matrix.transpose(), **kwargs)
    ax.quiver(XXX,YYY,fxField,fyField)
    ax.set_xticks([])
    ax.set_yticks([])

    plt.colorbar(im)

    plt.savefig(figName)
    print('Written '+figName)
    plt.close()


