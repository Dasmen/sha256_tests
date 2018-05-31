#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>  // for sleep
#include "cryptoext/sha256.h"

int32_t init_hexbytes_noT(char *hexbytes,uint8_t *message,long len);
void vcalc_sha256(char hashstr[(256 >> 3) * 2 + 1],uint8_t hash[256 >> 3],uint8_t *src,int32_t len);

/* iguana_utils.c */

char hexbyte(int32_t c)
{
    c &= 0xf;
    if ( c < 10 )
        return('0'+c);
    else if ( c < 16 )
        return('a'+c-10);
    else return(0);
}

int32_t init_hexbytes_noT(char *hexbytes,unsigned char *message,long len)
{
    int32_t i;
    if ( len <= 0 )
    {
        hexbytes[0] = 0;
        return(1);
    }
    for (i=0; i<len; i++)
    {
        hexbytes[i*2] = hexbyte((message[i]>>4) & 0xf);
        hexbytes[i*2 + 1] = hexbyte(message[i] & 0xf);
        //printf("i.%d (%02x) [%c%c]\n",i,message[i],hexbytes[i*2],hexbytes[i*2+1]);
    }
    hexbytes[len*2] = 0;
    //printf("len.%ld\n",len*2+1);
    return((int32_t)len*2+1);
}

// vcalc_sha256 with hardware acceleration
void vcalc_sha256(char hashstr[(256 >> 3) * 2 + 1],uint8_t hash[256 >> 3],uint8_t *src,int32_t len) {
    SHA256_hash(src, len, hash);
     if ( hashstr != 0 )
        init_hexbytes_noT(hashstr,hash,256 >> 3);
}

int main()
{
    //uint8_t digest[SHA256_DIGEST_SIZE];
    int i;

    char data[] = "decker";
    int len = sizeof(data) / sizeof(data[0]) - 1;
    printf("Data len: %d\n", len);

    char hashstr[(256 >> 3) * 2 + 1];
    uint8_t hash[256 >> 3];


    struct timeval  tv1, tv2;
    gettimeofday(&tv1, NULL);

    for (i=0; i < 10000000; i++) {
        vcalc_sha256(hashstr, hash, (uint8_t *) data, len);
    }

    gettimeofday(&tv2, NULL);

    printf("%s\n", hashstr);
    //printf("d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592\n");
    printf("bb7aa507ee307613a18d2b1eabb42e76a5e3ff8a00d021b738f6a5a8f299ed29\n");

    printf ("Total time = %f seconds\n",
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));

    sleep(1);
    return 0;
}
