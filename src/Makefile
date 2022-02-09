# ================== Reminder ======================
# $@ left side of rule (target)
# $< dependency of the target
# $^ list all dependencies
# @$ Deactivate echo

DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CFLAGS = -Wextra -m64 -g
else
	CFLAGS = -Wextra -m64
endif

ifeq ($(DEBUG), 1)
	EXEC=../build/debug/VigenereDebug
else
	EXEC=../build/release/VigenereRelease
endif
CC=g++

LD_SDL_MINGW32=-L./../lib -I./../include -m64 -lmingw32 -lSDL2main -lSDL2
LD_GLEW_MINGW32=-L./../lib -I./../include -m64 -lmingw32 -lglew32 -lopengl32 -lglu32 -lgdi32

# Generate source files list
SRC=Main.cpp
SRC+=VigenereCrypto/Input/Input.cpp VigenereCrypto/Encryption/Encryption.cpp
SRC+=Analysis/Analysis.cpp
SRC+=Graphics/Graphics.cpp
SRC+=../lib/imgui/imgui_demo.cpp ../lib/imgui/imgui_draw.cpp ../lib/imgui/imgui_impl_opengl3.cpp ../lib/imgui/imgui_impl_sdl.cpp ../lib/imgui/imgui_tables.cpp ../lib/imgui/imgui_widgets.cpp ../lib/imgui/imgui.cpp

OBJET=$(SRC:.cpp=.o)
DEP=$(SRC:.cpp=.d)

all:${EXEC}
ifeq ($(DEBUG), 1)
	@echo "GENERATING IN DEBUG MODE -> DONE"
else
	@echo "GENERATING IN RELEASE MODE -> DONE"
endif

# Comile target with modules
${EXEC}: ${OBJET}
	@${CC}  -o $@ $^ ${LD_SDL_MINGW32} ${LD_GLEW_MINGW32} ${CFLAGS}

# include all .d files
-include $(DEP)

# Compile all modules
%.o:%.cpp
	@echo Compiling : $<
	@$(CC) -o $@ -c $< ${LD_SDL_MINGW32} ${LD_GLEW_MINGW32} ${CFLAGS}

# Config all dependencies (header files)
%.d:%.cpp
	@$(CC) -MM -MD -o $@ $< ${LD_SDL_MINGW32} ${LD_GLEW_MINGW32} ${CFLAGS}



# Window only
.PHONY: clean mrpoper

clean:
	del $(OBJET) $(DEP)

mrpoper: clean
	del $(EXEC)