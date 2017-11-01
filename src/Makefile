CC = g++
CCFLAGS = -g -W -Wall

FLEX = flex
FLEX_OPTS = -PInstant

BISON = bison
BISON_OPTS = -t -pInstant

OBJS = Absyn.o Lexer.o Parser.o Printer.o

.PHONY: clean distclean

all: TestInstant

clean:
	rm -f *.o TestInstant Instant.aux Instant.log Instant.pdf Instant.dvi Instant.ps Instant

distclean: clean
	rm -f Absyn.C Absyn.H Test.C Parser.C Parser.H Lexer.C Skeleton.C Skeleton.H Printer.C Printer.H Makefile Instant.l Instant.y Instant.tex 

TestInstant: ${OBJS} Test.o
	@echo "Linking TestInstant..."
	${CC} ${CCFLAGS} ${OBJS} Test.o -o TestInstant

Absyn.o: Absyn.C Absyn.H
	${CC} ${CCFLAGS} -c Absyn.C

Lexer.C: Instant.l
	${FLEX} -oLexer.C Instant.l

Parser.C: Instant.y
	${BISON} Instant.y -o Parser.C

Lexer.o: Lexer.C Parser.H
	${CC} ${CCFLAGS} -c Lexer.C

Parser.o: Parser.C Absyn.H
	${CC} ${CCFLAGS} -c Parser.C

Printer.o: Printer.C Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Printer.C

Skeleton.o: Skeleton.C Skeleton.H Absyn.H
	${CC} ${CCFLAGS} -c Skeleton.C

Test.o: Test.C Parser.H Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Test.C

