all : p1

p1 : zafar_pa2_stra.o zafar_pa2_tro.o zafar_pa2_floyd.o
	gcc zafar_pa2_stra.o -o p1
	gcc zafar_pa2_tro.o -o p2
	gcc zafar_pa2_floyd.o -o p3
	
zafar_pa2_stra.o : zafar_pa2_stra.c
	gcc -c zafar_pa2_stra.c -std=c99 
	
zafar_pa2_tro.o : zafar_pa2_tro.c
	gcc -c zafar_pa2_tro.c -std=c99
	
zafar_pa2_floyd.o : zafar_pa2_floyd.c
	gcc -c zafar_pa2_floyd.c -std=c99
	
clean :
	rm *.o