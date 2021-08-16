#!/bin/bash

#creates a dot tex file....
pdflatex "worksheet.tex"
pdflatex "testsheet.tex"

rm *.aux *.log *.tex