/* xor_packer.c
 * Uso:
 *   gcc -o xor_packer xor_packer.c
 *   ./xor_packer libB/libB.so libB/libB.so.enc mi_clave
 *   ./xor_packer libB/libB.so.enc libB/libB.so.dec mi_clave  # para probar
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <infile> <outfile> <key>\n", argv[0]);
        return 1;
    }
    const char *infile = argv[1];
    const char *outfile = argv[2];
    const unsigned char *key = (unsigned char *)argv[3];
    size_t keylen = strlen((const char*)key);
    if (keylen == 0) {
        fprintf(stderr, "Key must be non-empty\n");
        return 2;
    }

    FILE *fin = fopen(infile, "rb");
    if (!fin) { perror("fopen infile"); return 3; }
    FILE *fout = fopen(outfile, "wb");
    if (!fout) { perror("fopen outfile"); fclose(fin); return 4; }

    unsigned char buf[4096];
    size_t r;
    unsigned long long pos = 0;
    while ((r = fread(buf, 1, sizeof buf, fin)) > 0) {
        for (size_t i = 0; i < r; ++i) {
            buf[i] ^= key[(pos + i) % keylen];
        }
        pos += r;
        if (fwrite(buf, 1, r, fout) != r) { perror("fwrite"); fclose(fin); fclose(fout); return 5; }
    }

    fclose(fin);
    fclose(fout);
    printf("Processed %s -> %s (keylen=%zu)\n", infile, outfile, keylen);
    return 0;
}
