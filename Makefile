CC			= gcc
FLAGS		= -fPIC -Wall -Wextra -Werror
TABS		= \t

SRC_DIR		= src/
SRC_LIST	= malloc.c \
			utilits.c \
			free.c \
			ft_find_block_size.c \
			ft_free_small_zone.c \
			calloc.c \
			ft_get_new_zone_size.c \
			ft_memory_allocation.c \
			ft_unite_with_next.c \
			realloc.c \
			show_alloc_mem.c \
			ft_malloc_multithread.c
SRC			= $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR		= obj/
OBJ_LIST	= $(patsubst %.c, %.o, $(SRC_LIST))
OBJ			= $(addprefix $(OBJ_DIR), $(OBJ_LIST))

INC_LIST	= ft_malloc.h
INC_DIR		= inc/
INC			= $(addprefix $(INC_DIR), $(INC_LIST))

INCLUDES	= -I$(INC_DIR)

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

LIBEXT		= .so
SUBNAME		= libft_malloc
NAME		= $(SUBNAME)_$(HOSTTYPE)$(LIBEXT)

# COLORS

GRN = \033[0;32m
RED = \033[0;31m
YEL = \033[1;33m
END = \033[0m

.PHONY: all clean fclean re run

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(INC)
	@gcc -shared -o $(NAME) $(OBJ) -g
	@ln -sf $(NAME) $(SUBNAME)$(LIBEXT)
	@echo "$(SUBNAME):$(TABS)$(GRN)Library created$(END)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo "$(SUBNAME):$(TABS)$(GRN)Compiling $<$(END)"
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(SUBNAME):$(TABS)$(GRN)$(OBJ_DIR) created$(END)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(SUBNAME):$(TABS)$(RED)*.o files deleted$(END)"
	@echo "$(SUBNAME):$(TABS)$(RED)$(OBJ_DIR) deleted$(END)"

fclean: clean
	@rm -f $(NAME)
	@rm -f test
	@rm -f $(SUBNAME)$(LIBEXT)
	@echo "$(SUBNAME):$(TABS)$(RED)$(NAME) deleted$(END)"
	@echo "$(SUBNAME):$(TABS)$(RED)$(SUBNAME)$(LIBEXT) deleted$(END)"

re: fclean all

run: all
	@$(CC) -Wall -Wextra -Werror -L. -lft_malloc -Wl,-rpath,. $(INCLUDES) main.c -o test
	@./test