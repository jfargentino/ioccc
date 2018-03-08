all:
	@echo "Are you sure ?"

BOMBS=h2co3 joshua mc_carthy speight.o trauma viraptor voight.o zapiku

.PHONY: clean

nuklear: $(BOMBS)

clean:
	@rm -v $(BOMBS)

h2co3: h2co3.c
	@gcc -E $^
	@gcc $^ -o $@

joshua: joshua.c
	@gcc $^ -o $@

mc_carthy: mc_carthy.c
	@gcc -E $^
	@gcc $^ -o $@

speight.o: speight.cpp
	@g++ -ftemplate-depth=999999 -g -c -o $@ $^

trauma: trauma.c
	@gcc -mcmodel=medium $^ -o $@

viraptor: viraptor.s
	@gcc $^ -mcmodel=large -Wl,-fuse-ld=gold

voight.o: voight.cpp
	@g++ -ftemplate-depth=999999 -g -c -o $@ $^

