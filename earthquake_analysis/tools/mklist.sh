#!/bin/bash



rm listaCanvas.lst

sed "/SetBinContent(/ !d" $1 > listaCanvas.lst
sed -i "s/^.*SetBinContent(//" listaCanvas.lst

sed  -i "s/);//" listaCanvas.lst
#sed -i "s/^[^,]*,//g" listaCanvas.lst




