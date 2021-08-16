#!/bin/bash

#given a file, just runs pdflatex on it and removes the unnecessary intermediary files... 
pdflatex "${1}"

rm *.aux *.log