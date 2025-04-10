NAME = minishell

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./includes -I$(LIBFT_DIR)

# Readline library
LDFLAGS = -lreadline
LIBFT_DIR = ./libft/
LIBFT = $(LIBFT_DIR)libft.a

# Source files
SRCS_DIR = srcs/
SRCS = main/main.c \
       parsing/basic_parsing.c \
       env/env_init.c \
       utils/ft_putnbr_fd.c

# Convert SRCS to full paths
SRCS_PATHS = $(addprefix $(SRCS_DIR), $(SRCS))

# Object files
OBJS = $(SRCS_PATHS:.c=.o)

# Rules
all: $(NAME)

# Libft compilation rule - 增加目录检查
$(LIBFT):
	@echo "Checking for libft directory..."
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "Error: libft directory not found at $(LIBFT_DIR)"; \
		echo "Please create a symlink or copy your libft to this location"; \
		echo "You can use: ln -s /path/to/your/libft $(LIBFT_DIR)"; \
		exit 1; \
	fi
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "libft compiled successfully!"

# Main program compilation
$(NAME): $(LIBFT) $(OBJS)
	@echo "Linking minishell..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)
	@echo "Minishell compiled successfully!"

# Rule for object files
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	@echo "Cleaning object files..."
	@if [ -d "$(LIBFT_DIR)" ]; then \
		$(MAKE) -C $(LIBFT_DIR) clean; \
	fi
	@rm -f $(OBJS)
	@echo "Clean completed!"

# Full clean rule
fclean: clean
	@echo "Removing executables..."
	@if [ -d "$(LIBFT_DIR)" ]; then \
		$(MAKE) -C $(LIBFT_DIR) fclean; \
	fi
	@rm -f $(NAME)
	@echo "Full clean completed!"

# Rebuild rule
re: fclean all

# Run rule - builds and runs the program
run: $(NAME)
	@echo "Running minishell..."
	@./$(NAME)

.PHONY: all clean fclean re run
