CC=gcc
AES=aes.c
GCD=gcd.c
EXE_AES=test_aes.c
EXE_GCD=test_gcd.c
CFLAGS=-Wall -Werror -pedantic -std=c99

aes:
	$(CC) $(CFLAGS)  -o aes $(EXE_AES) $(GCD) $(AES) 

gcd:
	$(CC) $(CFLAGS) -o gcd $(EXE_GCD) $(GCD)

clean:
	rm -rf aes gcd
