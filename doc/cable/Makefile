PAPER=cable.tex
DELIVERY=AsserWire.pdf
SHELL=/bin/bash

.PHONY: compile
compile:  ## Compile paper
	rubber --pdf $(PAPER)

.PHONY: clean
clean:  ## Clean output files
	rubber --clean $(PAPER)
	rm -f cable.bcf cable.run.xml

watch:  ## Recompile on updates to the source file
	@while true; do; inotifywait $(PAPER); sleep 0.01; make all; done

.PHONY: dist
dist: compile  ## Produce the final output
	gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/printer -dNOPAUSE -dQUIET -dBATCH -sOutputFile=$(DELIVERY) cable.pdf
	@echo "$(DELIVERY) is now available."
