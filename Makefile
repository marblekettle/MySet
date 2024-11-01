NAME = myset
CC = g++
FLAGS = -Wall -Werror -Wextra
INCLUDE = ./include
BUILDDIR = ./build
SRCDIR = ./src
SRC = \
	main.cpp

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	if [ ! -d $(BUILDDIR) ]; then mkdir $(BUILDDIR); fi
	$(CC) $(FLAGS) -c $< -I$(INCLUDE) -o $@

$(NAME): $(addprefix $(BUILDDIR)/, $(SRC:.cpp=.o))
	$(CC) $(FLAGS) $< -I$(INCLUDE) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(BUILDDIR)

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: clean fclean
