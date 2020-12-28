TARGET = calc_elec
SRC = $(TARGET).cpp

all: exe

OBJDIR ?= objs
DEPDIR ?= $(OBJDIR)/dep
ROOTCFLAGS = `root-config --cflags`
ROOTLIBS = `root-config --libs`
OPT ?= 2
DEBUG ?= -g
STD ?= c++11

GENDEPFLAGS = -MMD -MP -MF $(DEPDIR)/$(@F).d
CXXFLAGS += $(CXXDEFS)
CXXFLAGS += -O$(OPT)
CXXFLAGS += -march=native
CXXFLAGS += $(DEBUG)
CXXFLAGS += -Wall -Wextra
CXXFLAGS = -std=$(STD)
CXXFLAGS += $(ROOTCFLAGS)
MATHLIB = -lm
LIBS += $(MATHLIB)
ALL_CXXFLAGS = $(GENDEPFLAGS) $(CXXFLAGS)
LDFLAGS = $(ROOTLIBS)
OBJ = $(SRC:%.cc=$(OBJDIR)/%.o)

CXX := g++
LD := g++
REMOVE := rm -f
REMOVEDIR := rm -rf

exe: $(TARGET)

$(TARGET): $(OBJ)
	$(LD) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o : %.cc
	$(CXX) -c $(ALL_CXXFLAGS) $< -o $@

clean:
	-$(REMOVE) $(TARGET)
	-$(REMOVE) $(OBJ)
	-$(REMOVEDIR) $(DEPDIR)
	-$(REMOVEDIR) $(OBJDIR)

.PHONY: all exe
.PRECIOUS: $(OBJ)
