#ifndef _RMAN_H
#define _RMAN_H

#include <inttypes.h>

#include "general_utils.h"
#include "defs.h"

typedef struct chunk {
    uint32_t compressed_size;
    uint32_t uncompressed_size;
    uint64_t chunk_id;
    struct bundle* bundle;
    uint32_t offset;
} Chunk;

typedef LIST(Chunk) ChunkList;

typedef struct bundle {
    uint64_t bundle_id;
    ChunkList chunks;
} Bundle;

typedef struct language {
    uint8_t language_id;
    char* name;
} Language;

typedef LIST(struct bundle) BundleList;
typedef LIST(struct language) LanguageList;

typedef struct file_entry {
    uint64_t file_entry_id;
    uint64_t directory_id;
    uint32_t file_size;
    uint8_list language_ids;
    uint64_list chunk_ids;
    char* name;
    char* link;
} FileEntry;

typedef struct directory {
    uint64_t directory_id;
    uint64_t parent_id;
    char* name;
} Directory;

typedef struct file {
    char* name;
    char* link;
    uint8_list language_ids;
    uint32_t file_size;
    ChunkList chunks;
} File;

typedef LIST(FileEntry) FileEntryList;
typedef LIST(Directory) DirectoryList;
typedef LIST(File) FileList;

struct manifest {
    uint64_t manifest_id;
    ChunkList chunks;
    BundleList bundles;
    uint8_t language_ids[64];
    LanguageList languages;
    FileList files;
};

typedef struct manifest Manifest;
Manifest* parse_manifest(char* filepath);


#endif
