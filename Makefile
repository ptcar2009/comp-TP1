
build:
	$(MAKE) -C montador
	$(MAKE) -C ligador
	mkdir -p bin
	cp ligador/bin/ligador bin
	cp montador/bin/montador bin
