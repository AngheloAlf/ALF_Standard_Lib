# ALF_Standard_Lib
A little lib for stuff I usually use.

## How to use

###Compile the library
- `cd ALF_Standard_Lib`
- `make`

###Compile against the library
- `gcc *.c *.o -o outputFile -Wall -lALF_std` (Put a `-L` and then the location where the lib is if not detected by gcc, example `-L.` for the same folder.)

###Compile against the extra library
The extra library is all the code that have dependencies apart of the C standard library. You have to link them at compile time. The needed libraries are:
-Linux
-- `-ldl`


## TODO's:
- [ ] Make documentation for everything (a .md per folder)
- [ ] Create a `make` and an example of use for every file.
- [ ] Put an autoconf and automake
