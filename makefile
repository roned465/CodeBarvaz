# project directories
INCDIR = include
BINDIR = bin

SRCDIR = source
OBJDIR = build

PRGDIR = program
PRGOBJDIR = program_build

TSTDIR = test
TSTOBJDIR = test_build

# object subdirectories
SRCDIRS = $(wildcard $(SRCDIR)/*)
_OBJDIRS = $(patsubst $(SRCDIR)/%, %, $(SRCDIRS))
OBJDIRS = $(addprefix $(OBJDIR)\, $(_OBJDIRS))

# programs
PROGS = $(wildcard $(PRGDIR)/*.cpp)
_PROGS_OBJS = $(patsubst $(PRGDIR)/%.cpp, %.o, $(PROGS))
PROGS_OBJS = $(addprefix $(PRGOBJDIR)/, $(_PROGS_OBJS))
PROGS_NAMES = $(patsubst $(PRGDIR)/%.cpp, %, $(PROGS))

# tests
TESTS = $(wildcard $(TSTDIR)/*.cpp)
_TESTS_OBJS = $(patsubst $(TSTDIR)/%.cpp, %.o, $(TESTS))
TESTS_OBJS = $(addprefix $(TSTOBJDIR)/, $(_TESTS_OBJS))
TESTS_NAMES = $(patsubst $(TSTDIR)/%.cpp, %, $(TESTS))

# all source and object files
SRC = $(wildcard $(SRCDIR)/*/*.cpp)
_OBJS = $(patsubst $(SRCDIR)/%.cpp, %.o, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(_OBJS))

# include directories
INCDIRS = $(wildcard $(INCDIR)/*)
# include compiler flags
INCFLAGS = $(addprefix -I, $(INCDIRS))

# compiler and flags
CC = g++
CFLAGS = -Wall -g $(INCFLAGS)
LDFLAGS = 

# make all
.PHONY: all
all: programs tests

# make programs
.PHONY: programs $(PROGS_NAMES)
progs: $(PROGS_NAMES)

# rule for making a specific program from programs directory
$(PROGS_NAMES): $(OBJS) $(BINDIR) $(PROGS_OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(PRGOBJDIR)/$@.o -o $(BINDIR)/$@.exe

# make tests
.PHONY: tests $(TESTS_NAMES)
tests: $(TESTS_NAMES)

# rule for making a specific test from tests directory
$(TESTS_NAMES): $(OBJS) $(BINDIR) $(TESTS_OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(TSTOBJDIR)/$@.o -o $(BINDIR)/$@.exe

# make the programs object files
$(PRGOBJDIR)/%.o: $(PRGDIR)/%.cpp $(PRGOBJDIR)
	$(CC) $(CFLAGS) -c $(word 1, $^) -o $@

# make the tests object files
$(TSTOBJDIR)/%.o: $(TSTDIR)/%.cpp $(TSTOBJDIR)
	$(CC) $(CFLAGS) -c $(word 1, $^) -o $@

# make the object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp objdirs
	$(CC) $(CFLAGS) -c $(word 1, $^) -o $@

# rules for making building directories
$(TSTOBJDIR):
	mkdir $(TSTOBJDIR)

$(PRGOBJDIR):
	mkdir $(PRGOBJDIR)

.PHONY: objdirs
objdirs: $(OBJDIRS)

$(OBJDIRS):
	mkdir $@

$(BINDIR):
	mkdir $(BINDIR)

# make clean
.PHONY: clean
clean:
	rmdir /s /q $(OBJDIR) $(BINDIR) $(PRGOBJDIR) $(TSTOBJDIR)
