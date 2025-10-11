NAME		= minishell

LIBFT		= lib/libft/

INC_LIB		= include/lib_headers/
INC_HEADER	= include/headers/
READLINE_DIR = /opt/homebrew/opt/readline

SRC_DIR		= src/

LEX_DIR		= $(SRC_DIR)lexer/
SHELL_DIR	= $(SRC_DIR)shell/
PARSE_DIR	= $(SRC_DIR)parse/
BUILT_DIR	= $(SRC_DIR)builtins/
EXEX_DIR	= $(SRC_DIR)exec/
UTIL_DIR	= $(SRC_DIR)utils/

SRC 		= $(SRC_DIR)main.c \
			  $(LEX_DIR)lexer.c \
			  $(LEX_DIR)token.c \
			  $(LEX_DIR)syntax.c \
			  $(SHELL_DIR)free.c \
			  $(SHELL_DIR)expand.c \
			  $(SHELL_DIR)utils.c \
			  $(SHELL_DIR)readline.c\
			  $(SHELL_DIR)error.c \
			  $(SHELL_DIR)path.c \
			  $(SHELL_DIR)init.c \
			  $(SHELL_DIR)wildcard.c \
			  $(PARSE_DIR)parse_ast.c \
			  $(PARSE_DIR)init_ast.c \
			  $(PARSE_DIR)exec_ast.c \
			  $(BUILT_DIR)cd.c \
			  $(BUILT_DIR)pwd.c \
			  $(BUILT_DIR)env.c \
			  $(BUILT_DIR)echo.c \
			  $(BUILT_DIR)history.c \
			  $(BUILT_DIR)unset.c \
			  $(BUILT_DIR)utils.c \
			  $(BUILT_DIR)export.c \
			  $(EXEX_DIR)cmd.c \
			  $(EXEX_DIR)pipe.c \
			  $(EXEX_DIR)subshell.c \
			  $(EXEX_DIR)heredoc.c \
			  $(EXEX_DIR)utils.c \
			  $(UTIL_DIR)enum_type.c \
			  $(UTIL_DIR)quoted_type.c \
			  $(UTIL_DIR)token_type.c 

OBJ			= $(SRC:.c=.o)


LIB_FLAGS	= -L$(LIBFT) -lft -L$(READLINE_DIR)/lib -lreadline -lhistory -lncurses
IFLAG		= -I$(INC_HEADER) -I$(INC_LIB) -I$(LIBFT) -I$(READLINE_DIR)/include


FFLAG		= # -fsanitize=address
CFLAG		= -Wall -Wextra -Werror $(FFLAG) 
CC			= cc -g
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

valgrind:
			valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=ignore_readline.supp ./minishell

.PHONY:	all clean fclean re
