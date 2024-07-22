NAME = pipex

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
INCLUDES = -I/usr/include -I./$(LIBFT_DIR)/include -I./include
CFLAGS = -Wall -Wextra -Werror -g3 $(INCLUDES)

SRCS_DIR = ./srcs
OBJS_DIR = ./obj
SRCS = $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_FLAGS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIR)

clean:
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -sC $(LIBFT_DIR) clean 

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -sC $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re