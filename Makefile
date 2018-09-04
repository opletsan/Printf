# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: opletsan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/17 21:36:02 by opletsan          #+#    #+#              #
#    Updated: 2018/08/17 21:36:12 by opletsan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libftprintf.a

SRC_DIR		=	./src/
OBJ_DIR		=	./obj/
INC_DIR		=	./inc/

HEADER		=	$(INC_DIR)ft_printf.h

SRC 		=   ft_printf.c src_flag_spec.c width_prec_size.c input_digits.c \
				input_str_char.c non_printable.c color.c print_data.c

OBJ			=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

FLAGS		=	-Wall -Werror -Wextra

HEAD_FLAGS	=	-I $(INC_DIR)

BG			=	"\033[32;1m"
BR			=	"\033[31;1m"
EOC			=	"\033[0m"

all: $(NAME)
	
$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo ${BG}"[✓] $(NAME)"${EOC}

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o : %.c $(HEADER)
	@gcc -c $< -o $@ $(FLAGS) $(HEAD_FLAGS)
	@echo ${BG}"[✓] $<"

clean:
	@rm -rf $(OBJ)
	@echo ${BR}"[✗] $(OBJ)"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(OBJ_DIR)
	@echo ${BR}"[✗] $(NAME)"

re: fclean all

vpath %.c $(SRC_DIR)

.PHONY: all fclean clean re
