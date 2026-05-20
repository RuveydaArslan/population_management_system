hepsi: derle calistir

derle:
	gcc -I ./include -c ./src/main.c -o ./lib/main.o
	gcc -I ./include -c ./src/dosyaOkuma.c -o ./lib/dosyaOkuma.o
	gcc -I ./include -c ./src/ilce.c -o ./lib/ilce.o
	gcc -I ./include -c ./src/kisi.c -o ./lib/kisi.o
	gcc -I ./include -c ./src/mahalle.c -o ./lib/mahalle.o
	gcc -I ./include -c ./src/oyun.c -o ./lib/oyun.o
	gcc -I ./include -c ./src/seciliSehir.c -o ./lib/seciliSehir.o
	gcc -I ./include -c ./src/sehir.c -o ./lib/sehir.o
	gcc -I ./include -c ./src/turArttir.c -o ./lib/turArttir.o
	gcc -I ./include -c ./src/yerlesim.c -o ./lib/yerlesim.o
	gcc -I ./include -c ./src/sehirOlustur.c -o ./lib/sehirOlustur.o
	gcc -I ./include -c ./src/yazdir.c -o ./lib/yazdir.o
	gcc ./lib/*.o -o ./bin/program

calistir:
	./bin/program.exe