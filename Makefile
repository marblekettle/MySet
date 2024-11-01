NAME = myset
CC = g++
FLAGS = -Wall -Werror -Wextra -g
INCLUDE = ./include
BUILDDIR = ./build
SRCDIR = ./src
SRC = \
	implementation.cpp \
	main.cpp

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CC) $(FLAGS) -c $< -I$(INCLUDE) -o $@

$(NAME): $(addprefix $(BUILDDIR)/, $(SRC:.cpp=.o))
	$(CC) $(FLAGS) $(addprefix $(BUILDDIR)/, $(SRC:.cpp=.o)) \
		-I$(INCLUDE) -o $(NAME)

$(BUILDDIR):
	mkdir $@

all: $(NAME)

clean:
	rm -rf $(BUILDDIR)

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: clean fclean
