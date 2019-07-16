# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smorty <smorty@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/03 17:42:05 by smorty            #+#    #+#              #
#    Updated: 2019/07/16 20:53:55 by smorty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

INCLUDE = include/

SRCDIR = srcs/

OBJDIR = obj/

LFT = $(LFTDIR)libft.a

LFTDIR = $(SRCDIR)libft/

LMLX = $(LMLXDIR)libmlx.a

LMLXDIR = $(SRCDIR)minilibx/

SRCS = main.c get_next_line.c read_map.c colors.c print.c draw.c controls.c rotate.c

OBJ = $(SRCS:%.c=$(OBJDIR)%.o)

CC = gcc -Wall -Werror -Wextra

FDFFLAGS = -framework OpenGL -framework AppKit

LIBS = -L./$(LFTDIR) -lft -L./$(LMLXDIR) -lmlx

all: $(NAME)

$(NAME): $(OBJ) $(LFT) $(LMLX)
	@$(CC) $(FDFFLAGS) $^ $(LIBS) -o $@
	@echo "$(NAME) done!"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p '$(@D)'
	@$(CC) -I./$(INCLUDE) -c $< -o $@

$(LIBS): $(LFT) $(LMLX)

$(LFT):
	@$(MAKE) -C $(LFTDIR)
	@$(MAKE) -C $(LFTDIR) clean

$(LMLX):
	@$(MAKE) -C $(LMLXDIR)

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LFTDIR) fclean
	@$(MAKE) -C $(LMLXDIR) clean

fclean: clean
	@rm -f $(NAME)

re: fclean all