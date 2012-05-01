all: final.tex sources.bib
	pdflatex final.tex
	bibtex final
	pdflatex final.tex
	pdflatex final.tex

FILES := final.tex sources.bib

clean:
	rm -rf *.pdf *aux *.log *.dvi *.out *.bbl *.blg *.lof *.lot *.toc

.PHONY: all

count:
	texcount correlation.tex description.tex dspvsfpga.tex evaluation.tex further.tex hardwaremodelling.tex lms.tex matlabmodelling.tex pcbplan.tex pcb.tex philipsphones.tex previouslyinthisthread.tex projmanagement.tex psychoacoustics.tex softimple.tex testhard.tex testsoft.tex

countall:
	texcount *.tex
