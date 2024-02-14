NAME = philosophers
CC = cc
CFLAGS = -Wall -Wextra -Werror

# sources
PHILO_DIR = ./philo/
PHILO_OBJS_DIR = ./objs/
PHILO_OBJS_DIR_PATH = $(PHILO_DIR)$(PHILO_OBJS_DIR)

PHILO_SRCS = validator.c Util.c main.c time.c sleeping.c setup_data.c routines.c philosopher_setters.c \
				philosopher_getters.c error.c eating.c 

PHILO_SRCS_PATH = $(PHILO_SRCS:%=$(PHILO_DIR)%)

PHILO_OBJS = $(PHILO_SRCS:%.c=%.o)

PHILO_OBJS_PATH = $(addprefix $(PHILO_OBJS_DIR_PATH),$(PHILO_OBJS))

# colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
ORANGE = \033[0;33m

all: $(PHILO_OBJS_DIR) $(NAME)

$(NAME): $(PHILO_OBJS_PATH)
	@$(CC) $(CFLAGS) $(PHILO_OBJS_PATH) -o $@
	@echo "$(GREEN)philosophers is ready!$(RESET)"
	@echo "$(ORANGE)Run ./philo/philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] to start$(RESET)"


$(PHILO_OBJS_PATH):$(PHILO_SRCS_PATH)
	@$(MAKE) $(PHILO_OBJS) 

$(PHILO_OBJS):
	$(CC) $(CFLAGS) -c $(PHILO_DIR)$(@:%.o=%.c) -o $(PHILO_OBJS_DIR_PATH)$@

$(PHILO_OBJS_DIR):
	@echo "$(GREEN)Setting up obj directories...$(RESET)"
	@mkdir -p $(PHILO_OBJS_DIR_PATH)

clean:
	@echo "$(RED)Cleaning up...$(RESET)"
	@rm -rf $(PHILO_OBJS_DIR_PATH)
	@rm -f $(NAME)

fclean: clean
	@rm -f $(NAME)


re: fclean all

.PHONY: all clean fclean re
