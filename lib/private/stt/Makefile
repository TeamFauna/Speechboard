CC = gcc
CFLAGS  = -g -Wall -I/opt/local/include -L/opt/local/lib -lcurl -L/opt/local/lib -L/opt/local/lib -L/opt/local/lib -lidn -lssl -lcrypto -lssl -lcrypto -lz -lz

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
#
default: curler

curler:         curllib.o
		$(CC) $(CFLAGS) -o curler curllib.o

curler.o:   curllib.cc
		$(CC) $(CFLAGS) -c curllib.cc


# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean:
		rm -f curler *.o *~
