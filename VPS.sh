#!/bin/bash

# $1 stores the filename...
./vocab_gen $1
#creates a dot tex file....
pdflatex "${1}.tex"
pdflatex "${1}_test.tex"

rm *.aux *.log *.tex