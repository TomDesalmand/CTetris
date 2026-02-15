UNAME_S := $(shell uname -s)
CURDIR := $(shell pwd)

CXX       := gcc
CXXFLAGS ?= -std=c23 -Wall -Wextra -O2

# INCLUDE_DIRS := include

ifeq ($(UNAME_S), Darwin)
	LDFLAGS := -lncurses -L/opt/homebrew/lib -L/usr/local/lib
	CPPFLAGS += -I/opt/homebrew/include -I/usr/local/include
else
	LDFLAGS  := -lncurses -lm
endif

# CPPFLAGS += $(addprefix -I,$(INCLUDE_DIRS))

RM := rm -f

NAME := project

SRC := 	$(wildcard *.c) \
	  	$(wildcard source/*.c) \
		$(wildcard source/application/*.c) \
		$(wildcard source/objects/*.c) \
		$(wildcard source/gui/*.c)		

OBJ := $(SRC:.c=.o)

all: maybe_bear

maybe_bear:
	@if [ "$(UNAME_S)" != "Darwin" ]; then \
		echo "Non-macOS platform detected; running normal build"; \
		$(MAKE) --no-print-directory build; \
	else \
		if ! command -v bear >/dev/null 2>&1 ; then \
			echo "bear not found in PATH; running normal build"; \
			$(MAKE) --no-print-directory build; \
		elif [ -f compile_commands.json ]; then \
			echo "compile_commands.json already exists; running normal build"; \
			$(MAKE) --no-print-directory build; \
		elif [ -n "$$BEAR_CAPTURE" ]; then \
			$(MAKE) --no-print-directory build; \
		else \
			echo "Capturing compile commands with bear (one-time build) ..."; \
			BEAR_CAPTURE=1 exec bear -- $(MAKE) --no-print-directory build; \
		fi; \
	fi

build: $(NAME)

$(NAME): $(OBJ)
	@echo -e '\e[1m\e[32mLinking $(NAME)\e[0m'
	@$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo -e '\e[1m\e[32mCompiled $(NAME)\e[0m'

%.o: %.cpp
	@echo -e '\e[2mCompiling $< -> $@\e[0m'
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@$(RM) $(wildcard *.d)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(wildcard shaders/*.spv)
	@$(RM) compile_commands.json

re: fclean all

.PHONY: all maybe_bear build clean fclean re shaders