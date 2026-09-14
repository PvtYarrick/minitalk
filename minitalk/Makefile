
NAME_SERVER = server

NAME_CLIENT = client

NAME_SERVER_BONUS = server_bonus

NAME_CLIENT_BONUS = client_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -Iinclude -I$(LIBFT_DIR)

SRC_SERVER = src/server.c

SRC_CLIENT = src/client.c

SRC_SERVER_BONUS = src/bonus/server_bonus.c

SRC_CLIENT_BONUS = src/bonus/client_bonus.c

OBJ_SERVER = $(SRC_SERVER:src/%.c=obj/%.o)

OBJ_CLIENT = $(SRC_CLIENT:src/%.c=obj/%.o)

OBJ_SERVER_BONUS = $(SRC_SERVER_BONUS:src/bonus/%.c=obj/bonus/%.o)

OBJ_CLIENT_BONUS = $(SRC_CLIENT_BONUS:src/bonus/%.c=obj/bonus/%.o)

OBJ_DIR = ./obj

OBJ_DIR_BONUS = ./obj/bonus

# ========================
# RULES
# ========================

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER) $(LIBFT)

	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_SERVER) $(LIBFT) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT) $(LIBFT)

	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_CLIENT) $(LIBFT) -o $(NAME_CLIENT)

$(LIBFT):

	@$(MAKE) -C $(LIBFT_DIR)

bonus: $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

$(NAME_SERVER_BONUS): $(OBJ_SERVER_BONUS) $(LIBFT)

	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_SERVER_BONUS) $(LIBFT) -o $(NAME_SERVER_BONUS)

$(NAME_CLIENT_BONUS): $(OBJ_CLIENT_BONUS) $(LIBFT)

	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_CLIENT_BONUS) $(LIBFT) -o $(NAME_CLIENT_BONUS)

obj/%.o: src/%.c

	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

obj/bonus/%.o: src/bonus/%.c

	@mkdir -p $(OBJ_DIR_BONUS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
clean:

	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean

	rm -f $(NAME_SERVER) $(NAME_CLIENT) 
	rm -f $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

norme:
	@clear
	@norminette src/*.c

.PHONY: all bonus clean fclean re norme