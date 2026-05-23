NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INC = -I include
SRC_DIR = src
OBJ_DIR = obj

SRCS = \
	core/main.c \
	core/cleanup.c \
	init/setup.c \
	init/setup_forks.c \
	init/setup_philos.c \
	sync/stop.c \
	sync/monitor.c \
	simulation/threads.c \
	simulation/routine.c \
	simulation/sleep.c \
	simulation/schedule.c \
	simulation/forks.c \
	simulation/forks_wait.c \
	simulation/eat.c \
	io/print_safe.c \
	utils/time.c \
	utils/utils.c

OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INC) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c include/philo.h
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
