NAME = pulse

SRC_DIR = srcs
INC_DIR = includes

SRC_EXT = .c
OBJ_EXT = .o

SRCS = $(wildcard $(SRC_DIR)/*$(SRC_EXT))

OBJS = $(SRCS:$(SRC_EXT)=$(OBJ_EXT))

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -I $(INC_DIR)

$(NAME): $(OBJS)
	@echo "Compiling $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%$(OBJ_EXT): $(SRC_DIR)/%$(SRC_EXT)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	rm -f $(OBJS)

fclean: clean
	@echo "Cleaning $(NAME)..."
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re
