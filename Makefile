NAME = stl_cont

SRCS = 	main.cpp	\
		vectorMain.cpp	\
		mapMain.cpp	\
		stackMain.cpp

OBJDIR = build/
SRCDIR = srcs/
HEADER = includes/

OBJS := $(SRCS:.cpp=.o)
SRCS_PREFIXED := $(addprefix $(SRCDIR), $(SRCS))
OBJECTS_PREFIXED := $(addprefix $(OBJDIR), $(OBJS))

CXX	=	c++

CXXFLAGS = -Wall	-Werror	-Wextra -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJECTS_PREFIXED) $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS_PREFIXED) -o $(NAME)

$(OBJECTS_PREFIXED): $(OBJDIR)%.o : $(SRCDIR)%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -I$(HEADER) $< -o $@ 

vector:
			$(CXX) -D_VECTOR_ $(CXXFLAGS) $(SRCS_PREFIXED) -o $(NAME)

map:
			$(CXX) -D_MAP_ $(CXXFLAGS) $(SRCS_PREFIXED) -o $(NAME)

stack:
			$(CXX) -D_STACK_ $(CXXFLAGS) $(SRCS_PREFIXED) -o $(NAME)

clean:
	/bin/rm -rf $(OBJDIR)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY:	all	clean	fclean	re