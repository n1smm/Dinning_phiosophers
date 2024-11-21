CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
NAME = philo
SRC = clean_up.c dinner.c init.c main.c monitor_onephil.c mutex_handle.c parsing.c safe_functions.c utils_dinner.c utils_main.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c philosophers.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

