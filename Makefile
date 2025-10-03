SRCDIRS = src
INCDIRS = include

CC = g++
FLAGS = -Wall -Wextra -Werror $(foreach D, $(INCDIRS), -I$(D))

SRCS = $(foreach D, $(SRCDIRS), $(wildcard $(D)/*.cpp))
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

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
