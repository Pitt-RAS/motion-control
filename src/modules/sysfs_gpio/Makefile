include ../../../Makefile.common

CPPFLAGS += -Iinclude

SRCS != ls src/*.cpp
OBJS := ${SRCS:.cpp=.o}

NAME := lib/libsysfs_gpio.a

.PHONY: all clean

all: $(NAME) bin/export bin/unexport

$(NAME): $(OBJS)
	mkdir -p lib
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

bin/export: tools/export.o
	mkdir -p bin
	$(CXX) -Llib $< -lpthread -lsysfs_gpio -o $@

bin/unexport: tools/unexport.o
	mkdir -p bin
	$(CXX) -Llib $< -lpthread -lsysfs_gpio -o $@

clean:
	rm -f $(NAME) $(OBJS)
	rm -f bin/export bin/unexport tools/export.o tools/unexport.o
