SRCDIRS = src
TEST_SRCDIRS = test 
INCDIRS = include

CC = g++
AR = ar
FLAGS = -Wall -Wextra -Werror $(foreach D, $(INCDIRS), -I$(D))

SRCS = $(foreach D, $(SRCDIRS), $(wildcard $(D)/*.cpp))
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

TEST_SRCS = $(foreach D, $(TEST_SRCDIRS), $(wildcard $(D)/*.cpp))
TEST_OBJS = $(patsubst %.cpp, %.o, $(TEST_SRCS))

NAME = sudoku

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^

%.o: %.cpp
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

.PHONY: all clean fclean
