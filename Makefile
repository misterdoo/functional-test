CC = gcc
CXX = g++
TOPDIR = $(shell pwd)

INCDIR = $(TOPDIR)/include
SRCDIR = $(TOPDIR)/timer

VPATH = $(SRCDIR)

CFLAGS = -O2 -I$(INCDIR)

TARGET = run

SRCS = $(foreach dir, .. $(SRCDIR), $(wildcard $(dir)/*.cpp))
SRCS := $(notdir $(SRCS))
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)
	@./run

$(TARGET) : $(OBJS)
	$(CXX) $^ -o $(TARGET) $(LIBS)
	@#mv $(TARGET) ../


%o:%cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

depend: $(SRCS)
	$(CXX) -M $(CFLAGS) $^ > $@



