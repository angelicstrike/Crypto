CC=gcc
AES=aes.c
GCD=gcd.c
EXE_AES=test_aes.c
EXE_GCD=test_gcd.c
CFLAGS=-Wall -Werror -pedantic

aes:
	$(CC) $(CFLAGS) -o aes $(EXE_AES) $(AES)

gcd:
	$(CC) $(CFLAGS) -o gcd $(EXE_GCD) $(GCD)

clean:
	rm -rf aes gcd
