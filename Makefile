NAME = pipex
NAME_BONUS = pipex_bonus

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
INCLUDES = -I/usr/include -I./$(LIBFT_DIR)/include -I./include
CFLAGS = -Wall -Wextra -Werror -g3 $(INCLUDES)

SRCS_DIR = ./srcs
SRCS_DIR_BONUS = ./srcs_bonus
OBJS_DIR = ./obj
OBJS_DIR_BONUS = ./obj_bonus
SRCS = pipex.c utils.c 
SRCS_BONUS = pipex_bonus.c utils_bonus.c
OBJS = $(patsubst %.c, $(OBJS_DIR)/%.o, $(SRCS))
OBJS_BONUS = $(patsubst %.c, $(OBJS_DIR_BONUS)/%.o, $(SRCS_BONUS))
LIBFT_FLAGS = -L $(LIBFT_DIR) -lft

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "Compiling $(NAME) with objects: $(OBJS)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_FLAGS)
	@echo "$(NAME) has been created."

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@echo "Compiling $< to $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -sC $(LIBFT_DIR)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
	@echo "Compiling $(NAME_BONUS) with objects: $(OBJS_BONUS)"
	@$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIBFT_FLAGS)
	@echo "$(NAME_BONUS) has been created."

$(OBJS_DIR_BONUS)/%.o: $(SRCS_DIR_BONUS)/%.c | $(OBJS_DIR_BONUS)
	@echo "Compiling $< to $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR_BONUS):
	@mkdir -p $(OBJS_DIR_BONUS)

clean:
	@echo "Cleaning up..."
	@rm -rf $(OBJS_DIR)
	@rm -rf $(OBJS_DIR_BONUS)
	@$(MAKE) -sC $(LIBFT_DIR) clean 

fclean: clean
	@echo "Performing full clean..."
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@$(MAKE) -sC $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
