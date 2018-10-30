#!/usr/bin/env python
import sys
from ROOT import TFile, TTree
import ROOT
import numpy as np
from array import array
from histogrammar import *
maxn = 1;
lim=0;
means = open("means.lst").readlines()
sigmas = open("sigmas.lst").readlines()
events = array('d', len(sigmas)*[0.])
meansArr = array('d', len(sigmas)*[0.])
sigmasArr=array('d', len(sigmas)*[0.])
rootf = ROOT.TFile("stats.root", "recreate")
t = ROOT.TTree("stats", "stats")
for i, j in enumerate(means):
	events[i]=float(j)
std= np.std(events)
print std

for x, line in enumerate(means):
	meansArr[x]= float(line)
	sigmasArr[x]= float(sigmas[x])
     
meanM = np.mean(meansArr)
meanS = np.mean(sigmasArr)
stdM = np.std(meansArr)
stdS = np.std(sigmasArr)
print stdS

for i in range(len(sigmasArr)):
	if float(sigmasArr[i]-meanS) > 5*stdS and i-lim>0:
		lim=200+i
		print "Relative std: "+str(float(sigmasArr[i]-meanS)/float(stdS)) + " en el dia "+ str(int((float(i)/(3600*24))+10)) + "en el segundo "+str(i)
		


meansHist = ROOT.TH1D("meansHist","Means histogram",1000,-20,20)
meansHist.SetLineColor(9)
meansHist.SetMarkerColor(9)
meansHist.GetYaxis().CenterTitle()
meansHist.GetYaxis().SetTitle("Bin count")
meansHist.GetYaxis().SetTitleOffset(1.5)



sigmasHist = ROOT.TH1D("sigmasHist","Standard deviation histogram",1000,-4,50)
sigmasHist.SetLineColor(9)
sigmasHist.SetMarkerColor(9)
sigmasHist.GetYaxis().CenterTitle()

sigmasHist.GetYaxis().SetTitle("Bin count")
sigmasHist.GetYaxis().SetTitleOffset(1.5)

for x, line in  enumerate(meansArr):
	meansHist.Fill((float(line)-meanM)/stdM)
	sigmasHist.Fill((float(sigmasArr[x]-meanS)/(stdS)))    



print "s"
rootf.Write()
rootf.Close()                
          
