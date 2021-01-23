# project directories
INCDIR	= include
BINDIR	= bin
OBJDIR	= build
SRCDIR	= source

# final executable name
_BIN	= main.exe
BIN	= $(addprefix $(BINDIR)/, $(_BIN))

# all source and object files
SRC = $(wildcard $(SRCDIR)/*.cpp)
_OBJS = $(patsubst $(SRCDIR)/%.cpp, %.o, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(_OBJS))

# compiler and flags
CC = g++
CFLAGS = -Wall -g -I$(INCDIR)
LDFLAGS = 

.PHONY: all
all: $(BIN)

# make the executable target
$(BIN): $(OBJS) $(BINDIR)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

$(BINDIR):
	mkdir $(BINDIR)

# make the object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(OBJDIR)
	$(CC) $(CFLAGS) -c $(word 1, $^) -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

# remove the bin and build directories
.PHONY: clean
clean:
	rmdir /s /q $(OBJDIR) $(BINDIR)
