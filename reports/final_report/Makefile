all: final.tex sources.bib
	pdflatex final.tex
	bibtex final
	pdflatex final.tex
	pdflatex final.tex

FILES := final.tex sources.bib

clean:
	rm -rf *.pdf *aux *.log *.dvi *.out *.bbl *.blg *.lof *.lot *.toc

.PHONY: all
