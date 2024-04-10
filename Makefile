CC ?= clang
CFLAGS ?= -Wall -I/opt/local/include -L/opt/local/lib
LDFLAGS = -lexif

image-gps-info-reader:
	$(CC) $(CFLAGS) image-gps-info-reader.c -o $@ $(LDFLAGS)

clean:
	rm -f image-gps-info-reader