NAME = Container

CC = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

RM = rm -rf

SOURCES = 	./src/test/test.cpp


OBJECTS = $(SOURCES:%.cpp=%.o)

all :		$(NAME)

$(NAME):	$(OBJECTS)
		@$(CC)  $(OBJECTS) -o $(NAME)


clean:
		@$(RM) $(OBJECTS)

fclean: clean
		@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
