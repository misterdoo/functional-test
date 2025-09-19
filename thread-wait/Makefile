CC = gcc
CXX = g++
TOPDIR = $(shell pwd)
BUILDDIR = $(TOPDIR)/build

INCDIR = $(TOPDIR)/../include
INCDIR += $(TOPDIR)/../lib

SRCDIR = $(TOPDIR)
SRCDIR += $(TOPDIR)/../lib

CXXFLAGS = -g -Wall -O2 $(addprefix -I,$(INCDIR)) -std=c++17

TARGET = a.out

SRCS = $(foreach dir,$(SRCDIR),$(wildcard $(dir)/*.cpp))
OBJS = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(notdir $(SRCS)))

vpath %.cpp $(SRCDIR)

all: $(TARGET)
	@./$(BUILDDIR)/$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $^ -o $(BUILDDIR)/$(TARGET)

$(BUILDDIR)/%.o: %.cpp | $(BUILDDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

clean:
	@rm -rf $(BUILDDIR) $(TARGET)

#depend: $(SRCS)
#	$(CXX) -M $(CXXFLAGS) $^ > $@



