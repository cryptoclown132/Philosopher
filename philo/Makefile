NAME = philo

SRC = ${shell echo *.c}

OBJ = $(patsubst %.c, %.o, $(SRC))

THREAD = -lpthread

HEADER = philo.h

CC = gcc

CFLAGS = -Werror -Wextra -Wall

all: $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) $(THREAD)  -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re