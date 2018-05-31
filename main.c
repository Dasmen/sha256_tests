#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "cryptoext/sha256.h"

int main()
{
    uint8_t digest[SHA256_DIGEST_SIZE];
    int i;

    char data[] = "decker";

    int len = sizeof(data) / sizeof(data[0]) - 1;
    //printf("%ld\n", len);

    struct timeval  tv1, tv2;
    gettimeofday(&tv1, NULL);

    for (i=0; i < 100000000; i++) {
    SHA256_hash(data, len, digest);
    }

    gettimeofday(&tv2, NULL);

    for (i=0; i < SHA256_DIGEST_SIZE; i++) {
        printf("%02x", digest[i]);
    }
    printf("\n");
    //printf("d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592\n");
    printf("bb7aa507ee307613a18d2b1eabb42e76a5e3ff8a00d021b738f6a5a8f299ed29\n");

    printf ("Total time = %f seconds\n",
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));

    return 0;
}
