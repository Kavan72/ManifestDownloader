CC := gcc
CFLAGS := -std=gnu18 -g -Wall -Wextra -pedantic -Os -flto# -DDEBUG
LDFLAGS := -l:libzstd.a

all: LDFLAGS := $(LDFLAGS) -pthread pcre2/libpcre2_linux.a
all: ManifestDownloader

mingw: LDFLAGS := $(LDFLAGS) -static -lWs2_32 pcre2/libpcre2_mingw.a
mingw: CFLAGS := $(CFLAGS) -D__USE_MINGW_ANSI_STDIO
mingw: ManifestDownloader.exe

object_files = general_utils.o rman.o socket_utils.o download.o main.o sha/sha2.o

general_utils.o: general_utils.h defs.h
rman.o: rman.h defs.h list.h
socket_utils.o: socket_utils.h defs.h list.h rman.h
download.o: download.h defs.h general_utils.h list.h rman.h socket_utils.h
main.o: download.h defs.h general_utils.h list.h rman.h socket_utils.h

ManifestDownloader ManifestDownloader.exe: $(object_files)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@


clean:
	rm -f ManifestDownloader ManifestDownloader.exe $(object_files)
