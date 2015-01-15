
ofiles = gametime.o
cTargets = gametime.c



#--------------Individual Targets----------------#
# default target
gametime: $(ofiles)
	gcc -Wall -g -o gametime $(ofiles)

gametime.o: gametime.c
	gcc -Wall -g -c gametime.c

#----------------Build Type Targets-----------------#
clean: 
	rm $(ofiles) gametime

buildall: clean
	gcc -Wall -g -c gametime.c	

test:
	make
	./gametime 10

gameSmall: $(ofiles)
	clear
	make
	./gametime 5

gameMedium: $(ofiles)
	clear
	make
	./gametime 1000

gameLarge: $(ofiles)
	clear
	make
	./gametime 10000
