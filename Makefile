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

SRC 		= $(SRC_DIR)main.c \
			  $(LEX_DIR)lexer.c \
			  $(LEX_DIR)init_lexer.c \
			  $(LEX_DIR)token_analyse.c \
			  $(FREE_DIR)free.c \
			  $(SHELL_DIR)readline.c\
			  $(MSG_DIR)error.c \
			  $(AST_DIR)ast.c \
			  $(PARSE_DIR)parse_ast.c \
			  $(PARSE_DIR)init_ast.c \
			  $(SHELL_DIR)commands.c \
			  $(SHELL_DIR)history.c \
			  $(SHELL_DIR)utils.c \
			  $(SHELL_DIR)exec_cd.c \
			  $(SHELL_DIR)exec_pwd.c \
			  $(SHELL_DIR)exec_env.c



OBJ			= $(SRC:.c=.o)


LIB_FLAGS	= -L$(LIBFT) -lft -L$(READLINE_DIR)/lib -lreadline -lhistory -lncurses
IFLAG		= -I$(INC_HEADER) -I$(INC_LIB) -I$(LIBFT) -I$(READLINE_DIR)/include

CFLAG		= -Wall -Wextra -Werror -g -fsanitize=address

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

.PHONY:	all clean fclean re
