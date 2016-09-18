include Makefile.common

CPPFLAGS += -Iinclude

SRCS != ls src/*.cpp
OBJS := ${SRCS:.cpp=.o}

NAME := lib/libmotion.a

.PHONY: all clean

all: $(NAME)

$(NAME): $(OBJS)
	mkdir -p lib
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

clean:
	rm -f $(NAME) $(OBJS)
