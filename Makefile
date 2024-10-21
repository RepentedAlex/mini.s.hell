## SETTINGS
NAME	= minishell
VAL		= valgrind --leak-check=full --show-leak-kinds=all
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
DFLAGS	= -MMD -MP
FFLAGS	= -fsanitize=address
IFLAGS	= -Iinclude -ILibft/include
LFLAGS	= -lreadline
DEBUG	= -g3
FLAGS	= $(CFLAGS) $(DFLAGS) $(IFLAGS)
#FLAGS	+= $(FFLAGS)
FLAGS	+= $(DEBUG)

## DIRECTORIES
BUI_DIR	= build/
EXA_DIR	= examples/
EXT_DIR	= external/
XTR_DIR	= extras/
INC_DIR	= include/
LIB_DIR	= libs/
SRC_DIR	= src/
TES_DIR	= tests/

## SOURCES
SRC_FIL	= 	minishell \
			exit \
			init \
			builtins/builtins \
			parsing/check_quotes \
			parsing/lexing \
			parsing/blocks \
			parsing/lexing_nodes \
			parsing/parsing \
			parsing/pipe_inspection \
			parsing/redir_inspection \
			parsing/variable_expansion \
			utilitaries/block_nodes \
			utilitaries/ft_is \
			utilitaries/ft_split \
			utilitaries/ft_str \
			utilitaries/ft_strnjoin \
			utilitaries/utils1

SRC		= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FIL)))
OBJ		= $(addprefix $(BUI_DIR), $(addsuffix .o, $(SRC_FIL)))

OBJF	= .cache_exists

all: $(NAME)

$(NAME): $(OBJ) Libft/libtoolbox.a
	@echo "Linking $(NAME)..."
	$(CC) $(FLAGS) $(OBJ) Libft/libtoolbox.a $(LFLAGS) -o $(NAME)
	@echo "$(NAME) is born! :D"

Libft/libtoolbox.a:
	cd ./Libft/ ; git pull ; cd ../
	$(MAKE) -C ./Libft

$(BUI_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	@echo "$(PENDING)Compiling $<..."
	@$(CC) $(FLAGS)  -c $< -o $@

$(OBJF):
	@echo "Creating build directory"
	@mkdir -p $(BUI_DIR) $(BUI_DIR)/builtins $(BUI_DIR)/parsing $(BUI_DIR)/utilitaries
	@touch $(OBJF)

clean:
	@rm -rf $(BUI_DIR) $(OBJF)
	$(MAKE) clean -C ./Libft
	@echo "Removing build files..."

fclean: clean
	@echo "Removing $(NAME)..."
	$(MAKE) fclean -C ./Libft
	@rm -f $(NAME)

re:
	@$(MAKE) --no-print-directory fclean
	$(MAKE) re -C ./Libft
	@echo "Making $(NAME) again"
	@$(MAKE) --no-print-directory all

gen_sup:
	@echo -e \
	"{\n"\
	"\tignore_libreadline_leaks\n"\
	"\tMemcheck:Leak\n"\
	"\t...\n"\
	"\tobj:*/libreadline.so.*\n"\
	"}\n" > supress_readline.valgrind

v:
	@$(VAL) --suppressions=supress_readline.valgrind ./$(NAME)

-include $(OBJ:.o=.d)

.PHONY: all clean fclean re
