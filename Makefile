NAME		= minishell

LIBFT		= lib/libft/

INC_LIB		= include/lib_headers/
INC_HEADER	= include/headers/
READLINE_DIR = /opt/homebrew/opt/readline

SRC_DIR		= src/

LEX_DIR		= $(SRC_DIR)lexer/
FREE_DIR	= $(SRC_DIR)free_all/
SHELL_DIR	= $(SRC_DIR)shell/
MSG_DIR		= $(SRC_DIR)exit_msg/
AST_DIR		= $(SRC_DIR)ast/
PARSE_DIR	= $(SRC_DIR)parse/
ENV_DIR		= $(SRC_DIR)env/
BUILT_DIR	= $(SRC_DIR)builtins/
EXEX_DIR	= $(SRC_DIR)exec/

SRC 		= $(SRC_DIR)main.c \
			  $(LEX_DIR)lexer.c \
			  $(LEX_DIR)init_lexer.c \
			  $(LEX_DIR)syntax_validator.c \
			  $(LEX_DIR)utils.c \
			  $(FREE_DIR)free.c \
			  $(FREE_DIR)utils.c \
			  $(SHELL_DIR)readline.c\
			  $(MSG_DIR)error.c \
			  $(AST_DIR)ast.c \
			  $(PARSE_DIR)parse_ast.c \
			  $(PARSE_DIR)init_ast.c \
			  $(PARSE_DIR)exec_ast.c \
			  $(SHELL_DIR)commands.c \
			  $(SHELL_DIR)history.c \
			  $(SHELL_DIR)utils.c \
			  $(SHELL_DIR)get_path.c \
			  $(SHELL_DIR)init.c \
			  $(BUILT_DIR)exec_cd.c \
			  $(BUILT_DIR)exec_pwd.c \
			  $(BUILT_DIR)exec_env.c \
			  $(BUILT_DIR)exec_echo.c \
			  $(BUILT_DIR)exec_history.c \
			  $(BUILT_DIR)utils.c \
			  $(ENV_DIR)init_env.c \
			  $(EXEX_DIR)cmd.c \
			  $(EXEX_DIR)pipe.c \
			  $(EXEX_DIR)subshell.c \
			  $(EXEX_DIR)heredoc.c \
			  $(EXEX_DIR)utils.c



OBJ			= $(SRC:.c=.o)


LIB_FLAGS	= -L$(LIBFT) -lft -L$(READLINE_DIR)/lib -lreadline -lhistory -lncurses
IFLAG		= -I$(INC_HEADER) -I$(INC_LIB) -I$(LIBFT) -I$(READLINE_DIR)/include


FFLAG		= 
CFLAG		= -Wall -Wextra -Werror $(FFLAG) -fsanitize=address
CC			= cc
RM			= rm -rf

$(NAME):	$(OBJ)

			make -C $(LIBFT)
			$(CC) $(CFLAG) $(OBJ) $(LIB_FLAGS) -o $(NAME)

%.o:		%.c
			$(CC) $(CFLAG) $(IFLAG) -c $< -o $@

all:		$(NAME)

clean:				
			make -C $(LIBFT) clean
			$(RM) $(OBJ)

fclean: 	clean
			make -C $(LIBFT) fclean
			$(RM) $(NAME)

re:			fclean all

# valgrind:
# 			valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=ignore_readline.supp ./minishell

.PHONY:	all clean fclean re
