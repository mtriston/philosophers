NAME = philo_two

SRC = main.c \
	  initialization.c \
	  life_cycle.c \
	  utils.c \

OBJ = $(SRC:.c=.o)

HEADER = philo_two.h

CC = gcc

CC_FLAGS = -Wall -Wextra -Werror -pthread -g

all: $(NAME)

%.o: %.c
		$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJ) $(HEADER)
		$(CC) $(CC_FLAGS) -o $(NAME) $(OBJ)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all
