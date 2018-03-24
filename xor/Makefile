all: uuid4 check

uuid4: main.o uuid4.o xorshift128.o

clean:
	@rm -v uuid4 main.o uuid4.o xorshift128.o .SEED .UUID*
	@cd orig/uuid4/ && git reset --hard && cd ../..

ref: orig/uuid4/example/example

orig/uuid4/example/example: uuid4.patch orig/uuid4/src/uuid4.c orig/uuid4/example/example.c
	@patch -p1 -d orig/uuid4 < uuid4.patch
	@cd orig/uuid4/example/ && ./build.sh && cd ../../..

check: uuid4 ref check.sh
	@./check.sh

.PHONY = clean check

