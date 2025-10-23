NAME = philo
SRCS = main.c parse.c philosopher.c init.c utils.c
TESTARGS = 3 2000 200 200
OPTFLAG = 0
SRCDIR = ./srcs/
OBJDIR = ./objs/
LIBFT = ./libft/
CC = cc
INCFLAGS = -I ./includes/ -I $(LIBFT)
CFLAGS = -Wall -Wextra -g -O$(OPTFLAG)
OBJS = $(patsubst %.c, $(OBJDIR)%.o, $(SRCS))

ifeq ($(BONUS), 1)
CFLAGS += -D BONUS
SRCS += 
endif

all: $(NAME)

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT) fclean

re: clean all

$(NAME): $(OBJS) $(LIBFT)libft.a
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT)libft.a -o $@

$(OBJS): $(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCFLAGS) $^ -c -o $@

$(LIBFT)libft.a:
	make -C $(LIBFT)

$(MINILIBX)libmlx.a $(MINILIBX)libmlx_Linux.a:
	make -C $(MINILIBX)

test: $(NAME)
	./$(NAME) $(TESTARGS)

gprof: $(NAME)
	./$(NAME) $(TESTARGS)
	rm gprof-output -f
	gprof $(NAME) > gprof-output

valgrind: $(NAME)
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./$(NAME) $(TESTARGS)

helgrind: $(NAME)
	valgrind --tool=helgrind ./$(NAME) $(TESTARGS)

gdb: $(NAME)
	gdbtui --args $(NAME) $(TESTARGS)

vgdb: $(NAME)
	valgrind --vgdb=yes --vgdb-error=0 --track-origins=yes ./$(NAME) $(TESTARGS)
