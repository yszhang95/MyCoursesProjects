CC=latexmk
CCFLAGS=-pdf

.PHONY: all clean cleanall

all: final.pdf

final.pdf: final.tex
	$(CC) $(CCFLAGS) $<

clean:
	$(CC) -c final.tex
cleanall:
	$(CC) -C final.tex
