
CC = gcc -lreadline -o minishell

LDFLAGS="-L/Users/ayajrhou/.brew/opt/readline/lib"

CPPFLAGS="-I/Users/ayajrhou/.brew/opt/readline/include"

SRC =  *.c

NAME = minishell

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(SRC) $(LDFLAGS) $(CPPFLAGS)

clean:
	rm -f $(NAME) 

fclean: clean	
	rm -f $(NAME) 

re : fclean all
