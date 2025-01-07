#
# Created by gmakemake (Ubuntu Jul 25 2014) on Sat Nov 23 16:43:06 2024
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

CFLAGS = -std=c99 -ggdb -Wall -Wextra -pedantic

########## End of flags from header.mak


CPP_FILES =	
C_FILES =	interp.c parser.c stack.c symtab.c symtab_test.c tree_node.c
PS_FILES =	
S_FILES =	
H_FILES =	interp.h parser.h stack.h stack_node.h symtab.h tree_node.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	parser.o stack.o symtab.o tree_node.o 

#
# Main targets
#

all:	interp symtab_test 

interp:	interp.o $(OBJFILES)
	$(CC) $(CFLAGS) -o interp interp.o $(OBJFILES) $(CLIBFLAGS)

symtab_test:	symtab_test.o $(OBJFILES)
	$(CC) $(CFLAGS) -o symtab_test symtab_test.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

interp.o:	interp.h symtab.h
parser.o:	parser.h stack.h stack_node.h symtab.h tree_node.h
stack.o:	stack.h stack_node.h
symtab.o:	symtab.h
symtab_test.o:	symtab.h
tree_node.o:	symtab.h tree_node.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) interp.o symtab_test.o core

realclean:        clean
	-/bin/rm -f interp symtab_test 
