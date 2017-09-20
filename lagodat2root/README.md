This is a simple package for converting a set of LAGO dat files into root files.

DESCRIPTION:
============

* lagodat2root.C is a simple C++ code which can (need to) be compiled using:

> g++ -o lagodat2root lagodat2root.C \`root-config --glibs --cflags\`

or equivalent.
This program takes a LAGO dat file (original is for V5 electronics) as an argument and converts it to a root file with a tree structure that can be seen elsewhere.

One can run it like:

> ./lagodat2root <filename.dat>

* lagomassdat2root.py 
This is a simple python script which takes a directory as an argument.  The directory must contain the *.dat.bz2 files (or *.dat) files to be converted to root files.  This is done massively.


INSTRUCTIONS:
=============

1. Download the code to your favorite area:

> git clone https://github.com/caredg/lagodat2root

2. Compile the code doing:

> g++ -o lagodat2root lagodat2root.C \`root-config --glibs --cflags\`

3. If you want to just convert one dat file do:

> ./lagodat2root /full/path/to/file.dat

4. If you want to convert all *.dat.bz2 or *.dat files in a directory do:

> python lagomassdat2root.py /full/path/to/where/dat/files/are/

Root files will appear in their original directory.
