
NAME			=	libft.a

INCDIR			=	.
HEADER			=	libft.h

SRCS			=	$(wildcard *.c)
OBJS			=	$(patsubst %.c,%.o,$(SRCS))

GCC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -f

all:			$(NAME)

.c.o:
	@$(GCC) $(CFLAGS) -I$(INCDIR) -c $< -o $(<:.c=.o)

$(NAME):		$(OBJS) $(HEADER)
	@ar rc $@ $^
	@ranlib $@

.PHONY:			all clean fclean re

clean:
	@$(RM) $(OBJS)
			
fclean:			clean
	@$(RM) $(NAME)

re:				fclean all
