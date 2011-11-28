all: 
	pdflatex progress.tex
	#bibtex progress
	pdflatex progress.tex
	pdflatex progress.tex

FILES := progress.tex

clean:
	rm -rf *.pdf *aux *.log *.dvi *.out *.toc *.lof *.lot *.blg *.bbl

.PHONY: all
