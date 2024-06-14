SRCS = main_bonus.c utils1_bonus.c utils2_bonus.c utils3_philo_bonus.c utils4_init_bonus.c
# SRCB = main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c ft_split_bonus.c utils_bonus.c utils2_bonus.c utils3_bonus.c utils4_bonus.c here_doc_bonus.c
DIR = ./
# BONUS_DIR = ./bonus/
OBJS = $(SRCS:%.c=$(DIR)%.o)
# OBJB = $(SRCB:%.c=$(BONUS_DIR)%.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g
# BONUS_NAME = pipex_bonus
NAME = philo_bonus

all: $(NAME)

# bonus: $(BONUS_NAME)

# $(BONUS_NAME): $(OBJB) $(BONUS_DIR)pipex_bonus.h
# 	$(CC) $(OBJB) $(IFLAGS) -o $(BONUS_NAME) 

$(NAME): $(OBJS) $(DIR)philo_bonus.h
	$(CC) $(CFLAGS) -pthread $(OBJS) -o $(NAME) 

$(DIR)%.o: $(DIR)%.c $(DIR)philo_bonus.h
	$(CC) $(CFLAGS) -pthread -c $< -o $@

# $(BONUS_DIR)%.o: $(BONUS_DIR)%.c $(BONUS_DIR)pipex_bonus.h
# 	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) 

fclean: clean
	rm -rf $(NAME) 

re: fclean all