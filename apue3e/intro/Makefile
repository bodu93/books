target = myls in2out in2out2 printpid tinyshell errhandle puidgid tswithsignal
all : $(target)

$(target) :
	clang -o $@ ../src/error.c ../src/log.c $@.c

.PHONY : all clean
clean :
	rm -rf $(target) *.o
