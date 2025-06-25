NAME			= minishell

# LIBRARY
LIBFT				= ft
LIBFT_PATH	= lib/libft
READLINE		= readline
READLINE_PATH = $(shell brew --prefix readline)

# CMD & OPTION
CC = cc
RM = rm -rf

CFLAGS			= -Wall -Wextra -Werror
CPPFLAGS		= -I include -I$(READLINE_PATH)/include
LDFLAGS			= -L $(LIBFT_PATH) -L$(READLINE_PATH)/lib
LDLIBS			= -l $(LIBFT) -l $(READLINE)

# SOURCE FILE NAME
MAIN				= main
BUILTIN			=	\
							ft_cd \
							ft_echo \
							ft_env \
							ft_exit \
							ft_export \
							ft_pwd \
							ft_unset
COMMAND			= \
							run_cmd \
							run_process \
							set_redir
CONTRLLER		= minishell_controller
PARSER			= \
							here_doc \
							lexer \
							token
LEXER_UTIL	= lexer_util
PARSER_UTIL	= \
							convert_env \
							heredoc_util \
							make_quoteline \
							make_redir \
							redir_util \
							token_util 
UTIL				= \
							ft_free_strs \
							get_env
UTIL_BUILTIN = builtin_utils
UTIL_COMMAND = command_utils
UTIL_DEQUE 	= \
							deque_util \
							deque
UTIL_DICTIONARY = \
							dictionary_util \
							dictionary_util2 \
							dictionary
UTIL_LINK_LIST = link_list

FILE_NAME 	= \
							$(MAIN) \
							$(BUILTIN) \
							$(COMMAND) \
							$(CONTRLLER) \
							$(PARSER) \
							$(LEXER_UTIL) \
							$(PARSER_UTIL) \
							$(UTIL) \
							$(UTIL_BUILTIN) \
							$(UTIL_COMMAND) \
							$(UTIL_DEQUE) \
							$(UTIL_DICTIONARY) \
							$(UTIL_LINK_LIST)

# SRCS, OBJS 선언
SRCS_DIR		= src
SRCS				= $(addsuffix .c, $(FILE_NAME))

OBJS_DIR 		= objs
OBJS				= $(addprefix $(OBJS_DIR)/, $(addsuffix .o, $(FILE_NAME)))

# %.c 검색 경로 지정
SUBDIRS := $(shell find $(SRCS_DIR) -type d)
vpath %.c $(SUBDIRS)

# ================ Color Variables ================ #
RED				=	"\033[0;31m"
GREEN			=	"\033[0;32m"
YELLOW			=	"\033[1;33m"
EOC				=	"\033[0;0m"

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS) $(LIBFT)
	@echo $(GREEN) "Source files are compiled!\n" $(EOC)
	@$(LINK.o) $(LDLIBS) $(OBJS) $(OUTPUT_OPTION)
	@echo $(GREEN) "$(NAME) is created!\n" $(EOC)

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)

$(OBJS_DIR)/%.o: %.c
	@echo $(YELLOW) "Compiling...\t" $< $(EOC) $(LINE_CLEAR)
	@$(COMPILE.c) $< $(OUTPUT_OPTION)

$(LIBFT):
	@make -C $(LIBFT_PATH)

clean:
	@rm -rf $(OBJS_DIR)
	@make -C $(LIBFT_PATH) clean
	@echo $(RED) "Object file clean!\n" $(EOC)

fclean:
	@rm -rf $(OBJS_DIR) $(NAME)
	@make -C $(LIBFT_PATH) fclean
	@echo $(RED) "$(NAME) is removed!\n\n" $(EOC)

re: fclean all