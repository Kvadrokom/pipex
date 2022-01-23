#CC		=	gcc -g -fsanitize=address
CC			=	gcc -g
CFLAGS		= 	-Wall -Wextra -Werror

OBJDIR		=	objs
OBJDIR_BON	=	objs_bonus

SRCDIR		=	src
SRCDIR_BON	=	src_bonus

NAME		=	pipex
NAME_BONUS	=	pipex_bonus

SRC			:=	split.c\
				utils.c\
				errors.c\
				lib.c\
				check_cmd.c\
				pipex.c\
				


SRC_BONUS	=  	heredoc_bonus.c middle_bonus.c pipex_bonus.c split_bonus.c\
				utils_bonus.c errors_bonus.c lib_bonus.c check_cmd_bonus.c\
				get_next_line.c get_next_line_utils.c

SRC			:=	$(addprefix $(SRCDIR)/, $(SRC))
SRC_BONUS	:=	$(addprefix $(SRCDIR_BON)/, $(SRC_BONUS))
OBJ			=	$(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SRC:.c=.o))
OBJ_BON		=	$(patsubst $(SRCDIR_BON)/%, $(OBJDIR_BON)/%, $(SRC_BONUS:.c=.o))

all:		$(NAME)

bonus:		$(NAME_BONUS)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(NAME_BONUS):	$(OBJ_BON)
			$(CC) $(CFLAGS) $(OBJ_BON) -o $(NAME_BONUS)

$(OBJ):		|$(OBJDIR)
$(OBJ_BON):	|$(OBJDIR_BON)

$(OBJDIR):
			@mkdir $(OBJDIR)

$(OBJDIR_BON):
			@mkdir $(OBJDIR_BON)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c ./includes/*.h
			$(CC) $(CFLAGS) -I ./includes -c $< -o $@

$(OBJDIR_BON)/%.o:	$(SRCDIR_BON)/%.c ./includes_bonus/*.h
			$(CC) $(CFLAGS) -I ./includes_bonus -c $< -o $@


clean:
			@rm -rf $(OBJDIR) $(OBJDIR_BON)

fclean:		clean
			@rm -f $(NAME) $(NAME_BONUS)

re:			fclean all

.PHONY:		all clean fclean re

test:
	gcc -g src/split.c src/utils.c src/errors.c src/lib.c src/check_cmd.c\
	 tst.c -I ./includes