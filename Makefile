CC = gcc -Wall -DINITIAL_LOC=0 -DDEFAULT_PORT=1234

all: standalone_en standalone_fr server client_en client_fr

standalone_en: standalone.o map.o things.o lang_en.o util.o
	gcc -o $@ standalone.o map.o things.o lang_en.o util.o

standalone_fr: standalone.o map.o things.o lang_fr.o util.o
	gcc -o $@ standalone.o map.o things.o lang_fr.o util.o

server: server.o things.o util.o
	gcc -o $@ server.o things.o util.o

client_en: client.o map.o things.o lang_en.o util.o
	gcc -o $@ client.o map.o things.o lang_en.o util.o

client_fr: client.o map.o things.o lang_fr.o util.o
	gcc -o $@ client.o map.o things.o lang_fr.o util.o

clean:
	rm -f standalone_?? standalone_zh_* server client_?? client_zh_* *.o

# "gcc -MM" output:
client.o: client.c protocol.h mud.h lang.h map.h things.h util.h
map.o: map.c mud.h map.h
server.o: server.c protocol.h nplaces.h things.h util.h
standalone.o: standalone.c mud.h lang.h map.h things.h util.h
things.o: things.c
util.o: util.c util.h
lang_en.o: lang_en.c mud.h lang.h nplaces.h
lang_fr.o: lang_fr.c mud.h lang.h nplaces.h
