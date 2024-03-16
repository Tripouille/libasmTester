.DEFAULT_GOAL	:= a
UTILS			= utils/sigsegv.cpp utils/color.cpp utils/check.cpp
UTILS_O			= $(UTILS:.cpp=.o)
TESTS_PATH		= tests/
MANDATORY		= strlen strcpy strcmp write read strdup
VMANDATORY		= $(addprefix v, $(MANDATORY))
BONUS			= atoi_base list_push_front list_size list_sort list_remove_if
VBONUS			= $(addprefix v, $(BONUS))
VSOPEN			= $(addprefix vs, $(MANDATORY)) $(addprefix vs, $(BONUS))
MAIL			= $(addprefix send, $(MANDATORY)) $(addprefix send, $(BONUS))


CC		= clang++
CFLAGS	= -g3 -std=c++11 -I utils/ -I.
CFLAGS += -Wl,-z,noexecstack -Wno-unused-result -Wno-unknown-warning-option -Wno-unused-command-line-arguments
VALGRIND = valgrind -q --leak-check=full

$(MANDATORY): %: $(UTILS_O) mandatory_start
	@$(CC) $(CFLAGS) -fsanitize=address $(UTILS_O) $(TESTS_PATH)ft_$*_test.cpp -L.. -lasm && ./a.out && rm -f a.out

$(VMANDATORY): v%: $(UTILS_O) mandatory_start
	@$(CC) $(CFLAGS) $(UTILS_O) $(TESTS_PATH)ft_$*_test.cpp -L.. -lasm && $(VALGRIND) ./a.out && rm -f a.out

$(BONUS): %: $(UTILS_O) bonus_start
	@$(CC) $(CFLAGS) -fsanitize=address $(UTILS_O) $(TESTS_PATH)ft_$*_test.cpp -L.. -lasm && ./a.out && rm -f a.out

$(VBONUS): v%: $(UTILS_O) bonus_start
	@$(CC) $(CFLAGS) $(UTILS_O) $(TESTS_PATH)ft_$*_test.cpp -L.. -lasm && $(VALGRIND) ./a.out && rm -f a.out

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

$(VSOPEN): vs%:
	@code $(TESTS_PATH)ft_$*_test.cpp

mandatory_start: update message
	@tput setaf 6
	make -C ..
	@tput setaf 4 && echo [Mandatory]

bonus_start: update message
	@tput setaf 6
	make bonus -C ..
	@tput setaf 5 && echo [Bonus]

update:
	@tput setaf 3 && echo "[Checking for updates]"
	@git pull

message:

m: $(MANDATORY) 
b: $(BONUS)
a: m b 
vm: $(VMANDATORY) 
vb: $(VBONUS)
va: vm vb 

clean:
	rm -rf $(UTILS_O)
	make clean -C ..

fclean:
	make fclean -C ..	

.PHONY:	mandatory_start m vm bonus_start b vb a va clean update message $(VSOPEN)
