## SETTINGS
NAME	= minishell
VAL		= valgrind --leak-check=full --show-leak-kinds=all
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
DFLAGS	= -MMD -MP
FFLAGS	= -fsanitize=address
IFLAGS	= -Iinclude
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
			lexing \
			utils1

SRC		= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FIL)))
OBJ		= $(addprefix $(BUI_DIR), $(addsuffix .o, $(SRC_FIL)))

OBJF	= .cache_exists

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $(NAME)..."
	@$(CC) $(FLAGS) $(LFLAGS) $(OBJ) -o $(NAME)
	@echo "$(NAME) is born! :D"

$(BUI_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	@echo "$(PENDING)Compiling $<..."
	@$(CC) $(FLAGS)  -c $< -o $@

$(OBJF):
	@echo "Creating build directory"
	@mkdir -p $(BUI_DIR)
	@mkdir -p $(BUI_DIR)
	@touch $(OBJF)

clean:
	@rm -rf $(BUI_DIR) $(OBJF)
	@echo "Removing build files..."

fclean: clean
	@echo "Removing $(NAME)..."
	@rm -f $(NAME)

re:
	@$(MAKE) --no-print-directory fclean
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
