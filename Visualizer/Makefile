
EXE_NAME = visu

VISU_SRC_FILES = main.cpp ants.cpp visualizer.cpp get_input.cpp
VISU_SRC_PATH = ./srcs/
VISU_SRCS = $(addprefix $(VISU_SRC_PATH), $(VISU_SRC_FILES))

SDL_LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

all: $(EXE_NAME)

$(EXE_NAME):
	@g++ -o $(EXE_NAME) $(VISU_SRCS) $(SDL_LIBS)
	@echo "Executable 'visu' successfully compiled!"

fclean:
	@rm -f $(EXE_NAME)
	@echo "Executable removed."

re: fclean all
