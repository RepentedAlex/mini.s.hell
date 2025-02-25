## SETTINGS
NAME	= minishell
VAL		= valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --child-silent-after-fork=yes
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
DFLAGS	= -MMD -MP
FFLAGS	= -fsanitize=leak -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined
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

LIBFT_A	= Libft/libft.a
SUP_FILE = supress_readline.valgrind

## SOURCES
SRC_FIL	= 	minishell \
			exit \
			init \
			builtins/builtins \
			builtins/checkers \
			builtins/error_msg \
			builtins/ms_cd \
			builtins/ms_echo \
			builtins/ms_env \
			builtins/ms_exit \
			builtins/ms_export \
			builtins/ms_pwd \
			builtins/ms_unset \
			debug/debug \
			exec/closers/closers \
			exec/deleters/deleters \
			exec/fillers/fillers \
			exec/initialisers/initialisers \
			exec/modifyers/modifyers \
			exec/cmd_blocks \
			exec/exec \
			exec/exec_handlers \
			exec/exec_preparations \
			exec/file_openings \
			exec/path_finder \
			parsing/checkers/checkers \
			parsing/finders/finders \
			parsing/getters/getters \
			parsing/initialisers/initialisers \
			parsing/modifyers/modifyers \
			parsing/check_quotes \
			parsing/check_not_dirfile \
			parsing/lexing \
			parsing/blocks \
			parsing/parsing \
			parsing/pipe_check \
			parsing/pipe_inspection \
			parsing/redir_check \
			parsing/redir_inspection \
			parsing/redir_splitter \
			parsing/splitters_1 \
			parsing/splitters_2 \
			parsing/var_splitter \
			parsing/variable_expansion \
			redirections/heredocs/generators/generators \
			redirections/heredocs/modifyers/modifyers \
			redirections/heredocs/heredocs \
			signals/signals \
			utilitaries/block_nodes \
			utilitaries/block_add_front \
			utilitaries/checkers \
			utilitaries/ft_is \
			utilitaries/ft_split \
			utilitaries/ft_str \
			utilitaries/ft_strnjoin \
			utilitaries/initialisers \
			utilitaries/splash_screen \
			utilitaries/utils1

SRC		= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FIL)))
OBJ		= $(addprefix $(BUI_DIR), $(addsuffix .o, $(SRC_FIL)))

OBJF	= .cache_exists

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	@echo "Linking $(NAME)..."
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT_A) $(LFLAGS) -o $(NAME)
	@echo "$(NAME) is born! :D"

$(LIBFT_A):
	@$(MAKE) --no-print-directory -C ./Libft

$(BUI_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	@mkdir -p $(dir $@)
	@echo "$(PENDING)Compiling $<..."
	@$(CC) $(FLAGS)  -c $< -o $@

$(OBJF):
	@echo "Creating build directory"
	@touch $(OBJF)

clean:
	@echo "Removing build files..."
	@rm -rf $(BUI_DIR) $(OBJF)
	@$(MAKE) --no-print-directory clean -C ./Libft
	@echo "Build files removed successfully!"

fclean: clean
	@echo "Removing $(NAME)..."
	@$(MAKE) --no-print-directory fclean -C ./Libft
	@rm -f $(SUP_FILE)
	@rm -f $(NAME)

re: fclean
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory re -C ./Libft
	@echo "Making $(NAME) again"
	@$(MAKE) --no-print-directory all

$(SUP_FILE):
	@echo \
	"{\n"\
	"\tignore_libreadline_leaks\n"\
	"\tMemcheck:Leak\n"\
	"\t...\n"\
	"\tobj:*/libreadline.so.*\n"\
	"}\n" > $(SUP_FILE)

v: all $(SUP_FILE)
	@clear
	@$(VAL) --suppressions=$(SUP_FILE) ./$(NAME)

-include $(OBJ:.o=.d)

.PHONY: all clean fclean re
