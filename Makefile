.DEFAULT_GOAL	:= a
UTILS			= utils/sigsegv.cpp utils/color.cpp utils/check.cpp
TESTS_PATH		= tests/
MANDATORY		= strlen strcpy strcmp write read strdup
VMANDATORY		= $(addprefix v, $(MANDATORY))
BONUS			= atoi_base list_push_front list_size list_sort list_remove_if
VBONUS			= $(addprefix v, $(BONUS))
VSOPEN			= $(addprefix vs, $(MANDATORY)) $(addprefix vs, $(BONUS))
MAIL			= $(addprefix send, $(MANDATORY)) $(addprefix send, $(BONUS))


CC		= clang++
CFLAGS	= -g3 -std=c++11 -I utils/ -I.
VALGRIND = valgrind -q --leak-check=full

$(MANDATORY): %: mandatory_start
	@$(CC) $(CFLAGS) -fsanitize=address $(UTILS) $(TESTS_PATH)ft_$*_test.cpp -L.. -lasm && ./a.out && rm -f a.out

$(VMANDATORY): v%: mandatory_start
	@$(CC) $(CFLAGS) $(UTILS) $(TESTS_PATH)ft_$*_test.cpp -L.. -lasm && $(VALGRIND) ./a.out && rm -f a.out

$(BONUS): %: bonus_start
	@$(CC) $(CFLAGS) -fsanitize=address $(UTILS) $(TESTS_PATH)ft_$*_test.cpp -L.. -lasm && ./a.out && rm -f a.out

$(VBONUS): v%: bonus_start
	@$(CC) $(CFLAGS)  $(UTILS) $(TESTS_PATH)ft_$*_test.cpp -L.. -lasm && $(VALGRIND) ./a.out && rm -f a.out

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
	@git pull

message:

m: $(MANDATORY) 
b: $(BONUS)
a: m b 
vm: $(VMANDATORY) 
vb: $(VBONUS)
va: vm vb 

clean:
	make clean -C ..

fclean:
	make fclean -C ..	

.PHONY:	mandatory_start m vm bonus_start b vb a va clean update message $(VSOPEN)