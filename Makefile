output: main.o map.o perlin.o item.o player.o mob.o
	gcc main.o map.o perlin.o item.o player.o mob.o -o ProjectC

main.o: main.c
	gcc -c main.c

map.o: map.c map.h
	gcc -c map.c

perlin.o: perlin.c perlin.h
	gcc -c perlin.c

item.o: item.c item.h
	gcc -c item.c

player.o: player.c player.h
	gcc -c player.c

mob.o: mob.c mob.h
	gcc -c mob.c

clean:
	rm main.o
	rm map.o
	rm perlin.o
	rm player.o
	rm item.o
	rm mob.o
