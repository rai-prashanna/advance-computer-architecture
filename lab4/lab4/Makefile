#
# Makefile for lab4 in Advanced Computer Architecture.
#
# Author: Andreas Sandberg <andreas.sandberg@it.uu.se>
#
# $Id: Makefile 61 2011-11-03 13:31:05Z ansan501 $
#

ifdef NO_SSE41
SSE_ARCH_FLAGS=-msse3
MOV_INSTRUCTIONS=MOVDQU MOVDQA
else
SSE_ARCH_FLAGS=-msse4.1
MOV_INSTRUCTIONS=MOVDQU MOVDQA MOVNTDQ
endif

MATMUL_MODES=SSE BLOCKED SSE_BLOCKED

CC=gcc
ARCH=-m64 $(SSE_ARCH_FLAGS)
CFLAGS= -O2 $(ARCH) -g -Wall
LDFLAGS=$(ARCH)
LIBS=-lrt

all: $(MOV_INSTRUCTIONS:%=lcase_%) \
	matvec \
	$(MATMUL_MODES:%=matmul_%)

test_lcase: $(MOV_INSTRUCTIONS:%=test_lcase_%)

test_lcase_%: lcase_%
	./lcase_$*
	@ echo "----------------------------------------"

test_matvec: matvec
	./matvec
	@ echo "----------------------------------------"

test_matmul: $(MATMUL_MODES:%=test_matmul_%)

test_matmul_%: matmul_%
	./matmul_$*
	@ echo "----------------------------------------"

test: all test_lcase test_matvec test_matmul
	@ echo "----------------------------------------"
	@ echo "----------------------------------------"
	@ echo "All tests completed successfully!"

lcase_%: lcase_%.o util.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

lcase_%.o: lcase.c
	$(CC) -c -o $@ -DACCESS_TYPE=ACCESS_$* $(CFLAGS) $< $(LIBS)

matvec: matvec.o util.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

matvec.o: matvec.c
	$(CC) -c -o $@ $(CFLAGS) $< $(LIBS)

matmul_%: matmul_%.o util.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

matmul_%.o: matmul.c
	$(CC) -c -o $@ -DMODE=MODE_$* $(CFLAGS) $<

util.o: util.c
	$(CC) -c -o $@ $(CFLAGS) $< $(LIBS)

util.c: util.h

lcase.c: util.h

matvec.c: util.h

matmul.c: util.h

clean:
	$(RM) *.o lcase_* matmul_* matvec

.PHONY: clean all test
