OBJS = redis.o demo.o

CFLAGS := -g -O2 $(CFLAGS)
LDFLAGS := -lm $(LDFLAGS)

ifeq ($(DEBUG),1)
	CFLAGS += -g
endif

all: redis

redis: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

demo.o: redis.h
redis.o: redis.h

clean:
	rm -fr redis $(OBJS)
