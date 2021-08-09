
build:
	$(MAKE) -C montador
	$(MAKE) -C ligador
	mkdir -p bin
	cp ligador/bin/ligador bin
	cp montador/bin/montador bin

test: build
	./bin/montador ligador/tst/ex_pt1.txt > ligador/tst/ex_pt1.mv
	./bin/montador ligador/tst/ex_pt2.txt > ligador/tst/ex_pt2.mv
	./bin/ligador ligador/tst/ex_pt1.mv ligador/tst/ex_pt2.mv | tee ligador/tst/ex_final.mv
