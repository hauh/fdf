# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smorty <smorty@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/03 17:42:05 by smorty            #+#    #+#              #
#    Updated: 2019/07/12 20:46:07 by smorty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

INCLUDE = include/

SRCDIR = srcs/

OBJDIR = $(SRCDIR)obj/

LFT = $(LFTDIR)libft.a

LFTDIR = $(SRCDIR)libft/

SRCS = $(addprefix $(SRCDIR),main.c get_next_line.c read_map.c print.c controls.c colors.c rotate.c)

OBJ = $(SRCS:%.c=$(OBJDIR)%.o)

CC = gcc -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(OBJ) $(LFT)
	@$(CC) -L$(LFTDIR) -lft -L$(SRCDIR) -lmlx -framework OpenGL -framework AppKit $^ -o $@
	@echo "$(NAME) done!"

$(OBJDIR)%.o: %.c
	@mkdir -p '$(@D)'
	@$(CC) -I./include -c $< -o $@

$(LFT):
	@$(MAKE) -C $(LFTDIR)
	@$(MAKE) -C $(LFTDIR) clean

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LFTDIR) fclean

fclean: clean
	@rm -f $(NAME)

re: fclean all