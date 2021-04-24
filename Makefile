FILE_GPP 	= \
				  main \
				  gpp \
				  lexer \
				  token \
				  io \
				  parser \
				  ast \
				  visitor \
				  scope

DIR_SRC			= ./src/
DIR_INC			= ./include/
DIR_OBJ 		= ./obj/

OBJ_GPP 		= \
				  	$(addprefix $(DIR_OBJ), $(addsuffix .o, $(FILE_GPP)))

CC 	   			= gcc
COMPILER 		= gpp
#CFLAGS 	   		= -Wall -Werror -Wextra -O2 -I$(DIR_INC)
CFLAGS 	   		=  -O2 -g -I$(DIR_INC)

all: compiler

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

compiler: $(DIR_OBJ) $(OBJ_GPP)
	@$(CC) $(CFLAGS) -o $(COMPILER) $(OBJ_GPP)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
 
clean:
	@rm -rf $(DIR_OBJ)

fclean: clean
	@rm -rf $(COMPILER)

re: fclean all
