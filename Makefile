.DEFAULT_GOAL	:= m
UTILS			= utils/sigsegv.cpp utils/color.cpp utils/check.cpp
TESTS_PATH		= tests/
MANDATORY		= strlen
VMANDATORY		= $(addprefix v, $(MANDATORY))
BONUS			= lstnew lstadd_front lstsize lstlast lstadd_back lstdelone lstclear lstiter lstmap
VBONUS			= $(addprefix v, $(BONUS))
VSOPEN			= $(addprefix vs, $(MANDATORY)) $(addprefix vs, $(BONUS))
MAIL			= $(addprefix send, $(MANDATORY)) $(addprefix send, $(BONUS))


CC		= clang++
CFLAGS	= -g3 -std=c++11 -I utils/ -I.

$(MANDATORY): %: mandatory_start
	@$(CC) $(CFLAGS) -fsanitize=address $(UTILS) $(TESTS_PATH)ft_$*_test.cpp -L.. -lasm && ./a.out && rm -f a.out

$(VMANDATORY): v%: mandatory_start
	@$(CC) $(CFLAGS) $(UTILS) $(TESTS_PATH)ft_$*_test.cpp -L.. -lasm && valgrind -q --leak-check=full ./a.out && rm -f a.out

$(BONUS): %: bonus_start
	@$(CC) $(CFLAGS) -fsanitize=address $(UTILS) $(TESTS_PATH)ft_$*_test.cpp -L.. -lasm && ./a.out && rm -f a.out

$(VBONUS): v%: bonus_start
	@$(CC) $(CFLAGS)  $(UTILS) $(TESTS_PATH)ft_$*_test.cpp -L.. -lasm && valgrind -q --leak-check=full ./a.out && rm -f a.out

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
	#@git pull

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

.PHONY:	mandatory_start m vm bonus_start b vb a va clean update message $(VSOPEN) $(MAIL)