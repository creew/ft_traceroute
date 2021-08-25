ALL_C =	options/parse_option_f.c \
		options/parse_option_h.c \
		options/parse_option_I.c \
		options/parse_option_m.c \
		options/parse_option_q.c \
		options/parse_option_v.c \
		options/parse_option_w.c \
		ft_traceroute.c \
		get_addr.c \
		logger.c \
		parse_arg.c \
		send_icmp.c \
		send_request.c \
		send_udp.c \
		socket.c \
		usage.c

SRCDIR = ./srcs
OBJDIR = ./objs
OBJDIRS = $(OBJDIR) $(OBJDIR)/options
ALL_OBJ = $(ALL_C:%.c=%.o)

OBJS = $(addprefix $(OBJDIR)/, $(ALL_OBJ))

NAME = ft_traceroute

INCLUDES = ./includes/ft_traceroute.h \
		./includes/get_addr.h \
		./includes/parse_options.h

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): ./libft/libft.a $(OBJS)
	gcc $(FLAGS) -L./libft $(OBJS) -lft -lm -o $@

$(OBJDIRS):
	/bin/mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDES) | $(OBJDIRS)
	gcc $(FLAGS) -I./includes -I./libft/includes -c $< -o $@

./libft/libft.a:
	make -C libft

clean:
	@/bin/rm -rf $(OBJDIR)
	make -C libft clean

fclean: clean
	@/bin/rm -rf $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: lib clean fclean all re
