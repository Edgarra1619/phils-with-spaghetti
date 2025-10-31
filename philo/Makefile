NAME = philo
SRCS = main.c parse.c philosopher.c init.c utils.c mutex_utils.c notlibft.c
TESTARGS = 3 800 200 200
OPTFLAG = 0
SRCDIR = ./srcs/
OBJDIR = ./objs/
CC = cc
INCFLAGS = -I ./includes/
CFLAGS = -Wall -Wextra -Werror -g -O$(OPTFLAG)
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

re: clean all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJS): $(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCFLAGS) $^ -c -o $@

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
