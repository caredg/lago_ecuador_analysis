#!/usr/bin/env python

#Para datos completos->Ventanas de 5  minutos divididas en segundos

import sys
import numpy as np
from array import array
doc = sys.argv[1]

myFile = open(doc).readlines()
bins = len(myFile)
farr = array('d', bins*[0.])
warr = array('d', 300*[0.])
means = array('d', (bins-300)*[0.])
sigmas = array('d', (bins-300)*[0.])
meansFile = open("means.lst",'w')
sigmasFile = open("sigmas.lst", 'w')
errFile = open("errs.lst",'w')
for x, line in enumerate(myFile):
	
	l = line.split(',')
	farr[x]=float(l[1]);
windows= bins-300
print "Number of windows to be analyzed "+str(windows)
for i in range(windows):
	if i%10000==0:
		print "Analyzing window "+ str(i)
	for j in range(300):
		warr[j]=farr[j+i]
	means[i]=np.mean(warr)
	sigmas[i]=np.std(warr)
	print>>meansFile, means[i]
	print>>sigmasFile, sigmas[i]
	for j in range(300):
		err = warr[j]/means[i]
		if err >5*sigmas[i]:
			print>>errFile, "window " +str(i)+" error at "+str((((75600*200)+j+i)/200))+" of " +str(err)+" sigma"



