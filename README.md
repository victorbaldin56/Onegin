# Onegin
A string sorter written on C, can sort strings by the beginning or by the end.
The main purpose of this project is to turn Onegin to the "encyclopedia of
Russian life" by sorting it by alphabet, skipping punctuation symbols.

## Build
```
git clone https://github.com/victorbaldin56/Onegin
make
```

## Usage
Onegin accepts a single text file and gives the output to the other file.
To run, enter: ```./onegin [inputfile] [outputfile]```. The output file
contains 3 sections:
1. Result of prefix sort
2. Result of suffix sort
3. Original text