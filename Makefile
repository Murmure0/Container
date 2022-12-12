NAME = myContainer

STD_NAME = stdContainer

CC = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98


SOURCES = ./src/test/mainFt.cpp \
		./src/test/src/mapTest.cpp \
		./src/test/src/stackTest.cpp \
		./src/test/src/vectorTest.cpp 

SOURCES_STD = ./src/test/mainStd.cpp \
		./src/test/src/mapTestStd.cpp \
		./src/test/src/stackTestStd.cpp \
		./src/test/src/vectorTestStd.cpp 


OBJECTS = $(SOURCES:%.cpp=%.o)

OBJECTS_STD = $(SOURCES_STD:%.cpp=%.o)

RM = rm -rf

all :		$(NAME)

$(NAME):	$(OBJECTS) $(OBJECTS_STD)
		@$(CC) $(CXXFLAGS) $(OBJECTS) -o $(NAME)
		@$(CC) $(CXXFLAGS) $(OBJECTS_STD) -o $(STD_NAME)
		@echo "Executables $(NAME) & $(STD_NAME) are ready."

ft:			$(OBJECTS)
			$(CPP) $(CPPFLAGS) $(SOURCES) -o FT_tester

std:		$(OBJECTS_STD)
			$(CPP) $(CPPFLAGS) $(SOURCES_STD) -o STD_tester

clean:
		@$(RM) $(OBJECTS)
		@$(RM) $(OBJECTS_STD)

fclean: clean
		@$(RM) $(NAME)
		@$(RM) $(STD_NAME)

re: fclean all

.PHONY: clean fclean re all
