CC=gcc
CFLAGS=-Wall -g
LIB=libhashtable
BINS=$(LIB).so $(LIB).a test

all: $(BINS)

%: %.c $(LIB).a
	$(CC) $(FLAGS) $< -o $@ $(LIB).a 

%.o: %.c
	$(CC) $(FLAGS) -c $<

lib%.a: %.o
	ar -cvrs $@ $<

lib%.so: %.c
	$(CC) $(CFLAGS) -shared -fPIC $< -o $@

clean:
	rm -rf *.dSYM *.so *.a *.o $(BINS)
