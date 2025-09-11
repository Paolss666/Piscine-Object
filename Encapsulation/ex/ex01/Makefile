NAME = Graph

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -MMD -Wno-unused -std=c++98

INC_PATH = ./incl/
INC = -I $(INC_PATH)

SRCS_PATH = ./src/
SRC = main.cpp  Vector.cpp
SRCS = $(addprefix $(SRCS_PATH), $(SRC))

OBJS_PATH = ./obj/
OBJ = $(SRC:.cpp=.o)
OBJS = $(addprefix $(OBJS_PATH), $(OBJ))

DEPS = $(OBJS:.o=.d)

all: $(OBJS_PATH) $(NAME)

$(OBJS_PATH):
	mkdir -p $(OBJS_PATH)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.cpp
		${CXX} ${CXXFLAGS} -c $< -o $@ $(INC)

$(NAME) : $(OBJS)
		$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(INC)

-include $(DEPS)

clean:
		rm -rf $(OBJS_PATH)

fclean:
		rm -rf $(NAME) $(OBJS_PATH)
	
re: fclean
		make all

.PHONY: all clean fclean re