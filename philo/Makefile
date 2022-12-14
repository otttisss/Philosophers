NAME				=	philo

GREEN 				=	\033[0;32m
RED					=	\033[0;31m
RESET				=	\033[0m

CC					=	gcc
FLAGS				=	-Wall -Wextra -Werror
HEADERS_LIST		=	philo.h		\
						errors.h	\

HEADERS_DIR			=	./includes/
HEADERS				=	$(addprefix $(HEADERS_DIR), $(HEADERS_LIST))
INCLUDES			=	-I$(HEADERS_DIR)


SOURCES_DIR			=	sources/
SOURCES_LIST		=	main.c		\
						utils.c		\
						actions.c	\
						init.c

SOURCES				=	$(addprefix $(SOURCES_DIR), $(SOURCES_LIST))

OBJECTS_DIR			=	objects/
OBJECTS_LIST		=	$(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS				=	$(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST))

all					:	$(NAME)

$(NAME)				:	$(OBJECTS_DIR) $(OBJECTS)
						@$(CC) $(FLAGS) $(OBJECTS) -o $(NAME)
						@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
						@echo "$(NAME): $(GREEN)executable file was created$(RESET)"

$(OBJECTS_DIR)		:
						@mkdir -p $(OBJECTS_DIR)
						@echo "$(NAME): $(GREEN)$(OBJECTS_DIR) was created$(RESET)"

$(OBJECTS_DIR)%.o	:	$(SOURCES_DIR)%.c $(HEADERS)
						@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
						@echo "$(GREEN)*$(RESET)\c"

clean				:
						@rm -rf $(OBJECTS_DIR)
						@echo "$(NAME): $(RED)$(OBJECTS_DIR) and object files was deleted $(RESET)"

fclean				:	clean
						@rm -rf $(NAME)
						@echo "$(NAME): $(RED)$(NAME) was deleted $(RESET)"

re					:
						@$(MAKE) fclean
						@$(MAKE) all

.PHONY				:	all clean fclean re

