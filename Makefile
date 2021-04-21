NAME= philo_one_p
NAME1= philo_two_p
NAME2= philo_three_p

SRC_PATH= ./philo_one/sources
OBJ_PATH= ./philo_one/obj
SRC_PATH1= ./philo_two/sources
OBJ_PATH1= ./philo_two/obj
SRC_PATH2= ./philo_three/sources
OBJ_PATH2= ./philo_three/obj
HDR_PATH= includes
# LIB_PATH= libft

SRC_NAME=main.c\
		
SRC_NAME1=main.c\

SRC_NAME2=main.c\

HDR_NAME=philosopher.h

OBJ_NAME= $(SRC_NAME:.c=.o)
OBJ_NAME1= $(SRC_NAME1:.c=.o)
OBJ_NAME2= $(SRC_NAME2:.c=.o)

OBJ= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
SRC= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
HDR= $(addprefix $(HDR_PATH)/,$(HDR_NAME))

OBJ1= $(addprefix $(OBJ_PATH1)/,$(OBJ_NAME1))
SRC1= $(addprefix $(SRC_PATH1)/,$(SRC_NAME1))
HDR1= $(addprefix $(HDR_PATH)/,$(HDR_NAME))

OBJ2= $(addprefix $(OBJ_PATH2)/,$(OBJ_NAME2))
SRC2= $(addprefix $(SRC_PATH2)/,$(SRC_NAME2))
HDR2= $(addprefix $(HDR_PATH)/,$(HDR_NAME))

FLAGS= -Wall -Wextra -Werror
H_FLAG= -I $(HDR_PATH)

COMP= gcc

all:  $(NAME) $(NAME1) $(NAME2)

$(NAME) : $(LIB_PATH)/$(LIB) $(OBJ)
		@rm -rf $(NAME)
		@$(COMP) -g $(H_FLAG) $(OBJ) -o $@
$(NAME1) : $(LIB_PATH)/$(LIB) $(OBJ1)
		@rm -rf $(NAME1)
		@$(COMP) -g $(H_FLAG) $(OBJ1) -o $@
$(NAME2) : $(LIB_PATH)/$(LIB) $(OBJ2)
		@rm -rf $(NAME2)
		@$(COMP) -g $(H_FLAG) $(OBJ2) -o $@
		@echo " Made by : \033[1;91mAhaddad\033[m"


$(OBJ_PATH)/%.o:  $(SRC_PATH)/%.c $(HDR)
			@mkdir -p $(OBJ_PATH) 
			@$(COMP) -g $(FLAGS) $(H_FLAG) -g -o $@ -c $<
$(OBJ_PATH1)/%.o:  $(SRC_PATH1)/%.c $(HDR)
			@mkdir -p $(OBJ_PATH1) 
			@$(COMP) -g $(FLAGS) $(H_FLAG) -g -o $@ -c $<
$(OBJ_PATH2)/%.o:  $(SRC_PATH2)/%.c $(HDR)
			@mkdir -p $(OBJ_PATH2) 
			@$(COMP) -g $(FLAGS) $(H_FLAG) -g -o $@ -c $<

clean:
		@rm -rf $(OBJ_PATH)
		@rm -rf $(OBJ_PATH1)
		@rm -rf $(OBJ_PATH2)

fclean: clean
		@rm -rf $(NAME)
		@rm -rf $(NAME1)
		@rm -rf $(NAME2)
		@echo "all objects are deleted."  

re : fclean all