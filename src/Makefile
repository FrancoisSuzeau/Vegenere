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
	EXEC=../build/debug/VegenereDebug
else
	EXEC=../build/release/VegenereRelease
endif
CC=g++

# Generate source files list
SRC=Main.cpp VigenereCrypto/Input.cpp

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
	@${CC}  -o $@ $^ ${CFLAGS}

# include all .d files
-include $(DEP)

# Compile all modules
%.o:%.cpp
	@echo Compiling : $<
	@$(CC) -o $@ -c $< ${CFLAGS}

# Config all dependencies (header files)
%.d:%.cpp
	@$(CC) -MM -MD -o $@ $< ${CFLAGS}



# Window only
.PHONY: clean mrpoper

clean:
	del $(OBJET) $(DEP)

mrpoper: clean
	del $(EXEC)