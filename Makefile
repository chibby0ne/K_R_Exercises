dirs=$(shell ls | xargs -n 1 | grep Chapter)

all: 
	@for dir in $(dirs); do \
		echo "==== $$dir ===="; \
		(cd $$dir; \
		make all); \
	done

clean:
	@for dir in $(dirs); do \
		echo "==== $$dir ===="; \
		(cd $$dir; \
		make clean); \
	done
