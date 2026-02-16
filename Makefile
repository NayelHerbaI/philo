CC      := cc
CFLAGS  := -Wall -Wextra -Werror

NAME    := philo

OBJDIR  := obj

SRCS := main.c 

OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

philo: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
