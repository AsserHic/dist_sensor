PAPER=cable.tex
SHELL=/bin/bash

all:  ## Compile paper
	rubber --pdf $(PAPER)

clean:  ## Clean output files
	rubber --clean $(PAPER)
	rm -f cable.bcf cable.run.xml

watch:  ## Recompile on updates to the source file
	@while true; do; inotifywait $(PAPER); sleep 0.01; make all; done

