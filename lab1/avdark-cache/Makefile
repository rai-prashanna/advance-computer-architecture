#
# Main Makefile for the AvDark cache simulator.
#
# Course: Advanced Computer Architecture, Uppsala University
# Course Part: Lab assignment 1
#
# Author: Andreas Sandberg <andreas.sandberg@it.uu.se>
# Revision (2015, 2016, 2017, 2018): German Ceballos, Johan Janzen, Chris Sakalis
# Revision 2019: Christos Sakalis, Per Ekemark
#

LAB_DIR  ?= ..
PIN_HOME ?= $(LAB_DIR)/pin
PIN_KIT   = $(PIN_HOME)

CC     = gcc
CFLAGS = -Wall -std=gnu99

include $(PIN_HOME)/source/tools/makefile.gnu.config

SRC_FILES = avdark-cache.c

TOOL_ROOTS = avdc
TOOLS = $(TOOL_ROOTS:%=$(OBJDIR)%$(PINTOOL_SUFFIX))

all: tools

tools: $(OBJDIR) $(TOOLS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o : %.c %.h
	$(CC) -c -std=c99 $(PIN_CXXFLAGS) ${OUTOPT}$@ $<

$(OBJDIR)%.o : %.c
	$(CC) -c -std=c99 $(PIN_CXXFLAGS) ${OUTOPT}$@ $<

$(OBJDIR)%.o : %.cc
	$(CXX) -c $(CXXFLAGS) $(PIN_CXXFLAGS) ${OUTOPT}$@ $<

$(TOOLS): $(PIN_LIBNAMES)

$(TOOLS): %$(PINTOOL_SUFFIX) : $(OBJDIR)pin-glue.o $(OBJDIR)avdark-cache.o
	${PIN_LD} $(PIN_LDFLAGS) $(LINK_DEBUG) ${LINK_OUT}$@ $^ ${PIN_LPATHS} $(PIN_LIBS) $(LIBS) $(DBG)

info:
	@echo "To compile the cache simulator, just run make."
	@echo
	@echo "To run test cases, use one of the following targets:"
	@echo "  test-direct - Tests for direct mapped caches"
	@echo "  test-assoc - Tests for set associative caches"
	@echo "  test - All tests"
	@echo
	@echo "To run a make target type 'make target'"

test: test-direct test-assoc

test-direct: test0
	@echo "**************************************************"
	@echo "* Running tests for direct mapped caches         *"
	@echo "**************************************************"
	./test0 > /dev/null

test-assoc: test1
	@echo "**************************************************"
	@echo "* Running tests for associative caches           *"
	@echo "**************************************************"
	./test1 > /dev/null

test0: test0.o avdark-cache.o
test1: test1.o avdark-cache.o

pin-clean:
	$(RM) -r $(OBJDIR)

clean: pin-clean
	$(RM) *.o test0 test1

.PHONY: all clean test-direct test-assoc  tools
