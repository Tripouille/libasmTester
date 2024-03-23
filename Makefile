.DEFAULT_GOAL	:= a
UTILS			= utils/sigsegv.cpp utils/color.cpp utils/check.cpp
UTILS_O			= $(UTILS:.cpp=.o)

TESTS_PATH		= tests/
MANDATORY		= strlen strcpy strcmp write read strdup
BONUS			= atoi_base list_push_front list_size list_sort list_remove_if
ALL				= $(MANDATORY) $(BONUS)
ALL				:= $(addprefix ft_, $(addsuffix _test.cpp, $(ALL)))
ALL				:= $(addprefix $(TESTS_PATH), $(ALL))

OBJECTS			= $(UTILS:.cpp=.o) $(ALL:.cpp=.o)

VMANDATORY		= $(addprefix v, $(MANDATORY))
VBONUS			= $(addprefix v, $(BONUS))

VSOPEN			= $(addprefix vs, $(MANDATORY)) $(addprefix vs, $(BONUS))
VIOPEN			= $(addprefix vi, $(MANDATORY)) $(addprefix vi, $(BONUS))

# Code editors, you can change them to your preferred ones
CODE			= code
VI				= vim

DEBUG			?= 0
UPD				?= 1


CC		= clang++
CFLAGS	= -g3 -std=c++11 -I utils/ -I.
CFLAGS += -Wl,-z,noexecstack -Wno-unused-result -Wno-unknown-warning-option -Wno-unused-command-line-argument
VALGRIND = valgrind -q --leak-check=full

$(MANDATORY): %: mandatory_start $(UTILS_O) $(TESTS_PATH)ft_%_test.o
	$(CC) $(CFLAGS) -fsanitize=address $(UTILS_O) $(TESTS_PATH)ft_$*_test.o -L.. -lasm
	./a.out
ifneq ($(DEBUG), 1)
	rm -f a.out
endif

$(VMANDATORY): v%: mandatory_start $(UTILS_O) $(TESTS_PATH)ft_%_test.o
	$(CC) $(CFLAGS) $(UTILS_O) $(TESTS_PATH)ft_$*_test.o -L.. -lasm 
	$(VALGRIND) ./a.out
ifneq ($(DEBUG), 1)
	rm -f a.out
endif

$(BONUS): %: bonus_start $(UTILS_O) $(TESTS_PATH)ft_%_test.o
	$(CC) $(CFLAGS) -fsanitize=address $(UTILS_O) $(TESTS_PATH)ft_$*_test.o -L.. -lasm
	./a.out
ifneq ($(DEBUG), 1)
	rm -f a.out
endif

$(VBONUS): v%: bonus_start $(UTILS_O) $(TESTS_PATH)ft_%_test.o
	$(CC) $(CFLAGS) $(UTILS_O) $(TESTS_PATH)ft_$*_test.o -L.. -lasm 
	$(VALGRIND) ./a.out
ifneq ($(DEBUG), 1)
	rm -f a.out
endif

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(VSOPEN): vs%:
	$(CODE) $(TESTS_PATH)ft_$*_test.cpp

$(VIOPEN): vi%:
	$(VI) $(TESTS_PATH)ft_$*_test.cpp

mandatory_start: update
	tput setaf 6
	make -C ..
	tput setaf 4 && echo [Mandatory]

bonus_start: update
	tput setaf 6
	make bonus -C ..
	tput setaf 5 && echo [Bonus]

update:
ifeq ($(UPD), 1)
	tput setaf 3 && echo "[Checking for updates]"
	git pull
else
	tput setaf 3 && echo "[Skipping update check]"
endif

m: $(MANDATORY) 
b: $(BONUS)
a: m b 
vm: $(VMANDATORY) 
vb: $(VBONUS)
va: vm vb 

oclean:
	rm -rf $(OBJECTS)

clean: oclean
	make clean -C ..

fclean: oclean
	make fclean -C ..	

.PHONY:	mandatory_start m vm bonus_start b vb a va oclean clean fclean update $(VSOPEN) $(VIOPEN)

.SILENT:
