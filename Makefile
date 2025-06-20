NAME		= minishell

PRINTF		= lib/ft_printf/
LIBFT		= lib/libft/

INC_LIB		= include/lib_headers/
INC_HEADER	= include/headers/

SRC_DIR		= src/

LEX_DIR		= $(SRC_DIR)lexer/
FREE_DIR	= $(SRC_DIR)free_all/
SHELL_DIR	= $(SRC_DIR)shell/
MSG_DIR		= $(SRC_DIR)exit_msg/
AST_DIR		= $(SRC_DIR)ast/
PARSE_DIR	= $(SRC_DIR)parse/

SRC 		= $(SRC_DIR)main.c \
			  $(LEX_DIR)lexer.c \
			  $(FREE_DIR)free.c \
			  $(SHELL_DIR)readline.c \
			  $(MSG_DIR)error.c \
			  $(AST_DIR)ast.c \
			  $(PARSE_DIR)parse_ast.c

OBJ			= $(SRC:.c=.o)

LIB_FLAGS	= -L$(LIBFT) -lft -L$(PRINTF) -lftprintf
IFLAG		= -I$(INC_HEADER) -I$(INC_LIB) -I$(LIBFT) -I$(PRINTF)
CFLAG		= -Wall -Wextra -Werror

CC			= cc
RM			= rm -rf

$(NAME):	$(OBJ)
			make -C $(PRINTF)
			make -C $(LIBFT)
			$(CC) $(CFLAG) $(OBJ) $(LIB_FLAGS) -o $(NAME)

%.o:		%.c
			$(CC) $(CFLAG) $(IFLAG) -c $< -o $@

all:		$(NAME)

clean:				
			make -C $(PRINTF) clean
			make -C $(LIBFT) clean
			$(RM) $(OBJ)

fclean: 	clean
			make -C $(PRINTF) fclean
			make -C $(LIBFT) fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:	all clean fclean re
