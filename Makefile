
CFLAGS += -fPIC
CFLAGS += -Wall -I. -I./include

LDFLAGS += -L.

OBJS := flash_mtd.o files.o

all: libshared.so

libshared.so: $(OBJS)
	$(LD) -shared -o $@ $^

clean:
	rm -f *.o libshared.so

.PHONY: clean
