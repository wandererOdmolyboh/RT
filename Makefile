
NAME		= RTv1

#	compiler
CC			= gcc
FLAGS		= -Wall -Wextra -Werror

#	files
SRC			=  closestintersection.c  create_list_l.c get_next_line.c intersect_objct.c  main.c  oper_w_color.c oper_w_vector.c \
pass_list.c trace_ray.c ft_atof.c error_manegmant.c camera.c rotaror.c\
computelighting.c create_list_obj.c initial_sdl.c  leaks.c normal.c oper_w_img.c  \
reader.c

#	directories
INC_DIR		= ./inc/
OBJ_DIR		= ./obj/
SRC_DIR		= ./src/
FRM_DIR		= frameworks

OBJ			= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

#	ft library
FT			= ./libft/
FT_LIB		= $(addprefix $(FT), libft.a)
FT_INC		= -I $(FT)
FT_LNK		= -L $(FT) -lft

#	SDL
UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	SDL_LNK	= -l SDL2 -l SDL2_image 
else
	SDL_INC	= -I $(CURDIR)/$(FRM_DIR)/SDL2.framework/Headers \
				-I $(CURDIR)/$(FRM_DIR)/SDL2_image.framework/Headers \
				-F $(CURDIR)/$(FRM_DIR)

	SDL_LNK	= -F $(CURDIR)/$(FRM_DIR) \
				-rpath $(CURDIR)/$(FRM_DIR) \
				-framework SDL2 -framework SDL2_image 
endif

all: obj $(FT_LIB) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

$(FT_LIB):
	@make -C $(FT)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@$(CC) $(FLAGS) -I $(INC_DIR) $(FT_INC) $(SDL_INC) -o $@ -c $<
	@echo "(+) $@"

$(NAME):$(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(FT_LNK) -I $(INC_DIR) $(SDL_INC) $(SDL_LNK)\
	 -lm -o $(NAME)
	@echo "$(NAME) ready to win!"

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(FT) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(FT) fclean

re: fclean all

.PHONY: all clean fclean re