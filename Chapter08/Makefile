EXES=$(shell ls | xargs -n 1 | grep .c$ | cut -d '.' -f 1)
CFLAGS=-lm

all: $(EXES)

%: %.o
	gcc -o $@ $^ $(CFLAGS) 

%: %.c

%.o: %.c 
	gcc -c -o $@ $<

clean:
	rm $(EXES)
