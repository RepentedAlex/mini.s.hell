#     _____        _____        _____        _____         _____
#  __|_    |__  __|_    |__  __|___  |__  __|___  |__  ___|__   |__
# |    |      ||    |      ||      >    ||   ___|    ||_    _|     |
# |    |_     ||    |      ||     <     ||   ___|    | |    |      |
# |______|  __||____|    __||______>  __||___|     __| |____|    __|
#    |_____|      |_____|      |_____|      |_____|       |_____|

NAME	= libft.a

######################
## COMPILER & FLAGS ##
######################

CC		= gcc
FLAGS	= -Wall -Wextra -Werror -Wpedantic -fPIE
DEBUG	= -g3
FLAGS	+= $(DEBUG)
DFLAGS	= -MMD -MP
FLAGS	+= $(DFLAGS)
FFLAGS	= -fsanitize=address
#FLAGS	+= $(FFLAGS)
IFLAGS	= -Iinclude
FLAGS	+= $(IFLAGS)

#################
## DIRECTORIES ##
#################

BUI_DIR	= build/
INC_DIR	= ../include/
SRC_DIR	= src/
TES_DIR	= tests/

##############
## COMMANDS ##
##############

RM		= rm -rf
AR		= ar rcs

#############
## SOURCES ##
#############

SRC_FILES =		ft_is/ft_isalnum \
				ft_is/ft_isalpha \
				ft_is/ft_isascii \
				ft_is/ft_isdigit \
				ft_is/ft_isifs \
				ft_is/ft_isprint \
				ft_lst/ft_lstadd_back_bonus \
				ft_lst/ft_lstadd_front_bonus \
				ft_lst/ft_lstclear_bonus \
				ft_lst/ft_lstdelone_bonus \
				ft_lst/ft_lstiter_bonus \
				ft_lst/ft_lstlast_bonus \
				ft_lst/ft_lstmap_bonus \
				ft_lst/ft_lstnew_bonus \
				ft_lst/ft_lstsize_bonus \
				ft_mem/ft_memchr \
				ft_mem/ft_memcmp \
				ft_mem/ft_memcpy \
				ft_mem/ft_memmove \
				ft_mem/ft_memset \
				ft_put/ft_putchar_fd \
				ft_put/ft_putendl_fd \
				ft_put/ft_putnbr_fd \
				ft_put/ft_putstr_fd \
				ft_str/ft_strapp \
				ft_str/ft_strnapp \
				ft_str/ft_strcat \
				ft_str/ft_strchr \
				ft_str/ft_strcmp \
				ft_str/ft_strcpy \
				ft_str/ft_strdup \
				ft_str/ft_strndup \
				ft_str/ft_striteri \
				ft_str/ft_strjoin \
				ft_str/ft_strlcat \
				ft_str/ft_strlcpy \
				ft_str/ft_strlen \
				ft_str/ft_strmapi \
				ft_str/ft_strncat \
				ft_str/ft_strncmp \
				ft_str/ft_strnstr \
				ft_str/ft_strrchr \
				ft_str/ft_strtrim \
				ft_str/ft_substr \
				ft_to/ft_atoi \
				ft_to/ft_itoa \
				ft_to/ft_tolower \
				ft_to/ft_toupper \
				ft_bzero \
				ft_calloc \
				ft_split

SRC		= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ		= $(addprefix $(BUI_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF	= .cache_exists

############
## COLORS ##
############

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

#############
## RECIPES ##
#############

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

$(BUI_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@

$(OBJF):
	@touch $(OBJF)

clean: 
	@$(RM) $(OBJ) $(OBJF)
	@$(RM) $(BUI_DIR)

fclean: clean 
	@$(RM) $(NAME)

re: fclean all

-include $(OBJ:.o=.d)
	
.PHONY: all bonus clean fclean re
