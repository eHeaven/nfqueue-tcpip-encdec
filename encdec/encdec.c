#include "encdec.h"


/***
 *    songshuai add at 2019.08.06
 **/
unsigned char keyDataUnion[16][AES_BLOCK_SIZE] = {
    {0xA8, 0x8D, 0x2F, 0xCB, 0x29, 0xDF, 0x81, 0xEF, 0xAD, 0xE8, 0x1C, 0xDD, 0x41, 0xA8, 0xCF, 0x77}, // 0
    {0x4A, 0x33, 0xEF, 0x6C, 0xFF, 0x8B, 0x34, 0x34, 0xD6, 0x13, 0xDA, 0x1D, 0xEB, 0xA6, 0xBA, 0x93}, // 1
    {0x33, 0xE9, 0x5E, 0x5C, 0xC9, 0xE0, 0x4C, 0x76, 0xC8, 0x68, 0x54, 0x09, 0x10, 0x23, 0x80, 0x5B}, // 2
    {0x57, 0x6F, 0xC7, 0x56, 0xFB, 0xFB, 0x8A, 0xD1, 0x0E, 0x64, 0xEE, 0xF9, 0x0A, 0xA9, 0x8C, 0x3D}, // 3
    {0x92, 0xEB, 0x9A, 0x5B, 0xCB, 0xE6, 0xD2, 0x93, 0x4E, 0x26, 0x9C, 0x5E, 0x49, 0x1C, 0xB9, 0xA0}, // 4
    {0x8B, 0x80, 0xF6, 0x86, 0x7B, 0x80, 0x58, 0x8A, 0xE5, 0x46, 0x83, 0xEF, 0xEF, 0x10, 0x2D, 0x82}, // 5
    {0xFB, 0xC7, 0xDD, 0xC6, 0xAD, 0xAF, 0x59, 0xFB, 0xD5, 0xF5, 0x59, 0x1F, 0x11, 0x13, 0xBF, 0x9C}, // 6
    {0x93, 0xB6, 0x23, 0x0F, 0x36, 0x7B, 0x99, 0x1B, 0xC1, 0x1C, 0x0B, 0xB1, 0x2C, 0x38, 0x33, 0x27}, // 7
    {0xFF, 0x10, 0xED, 0xAC, 0xC0, 0x46, 0xA7, 0x95, 0x3B, 0x00, 0xB4, 0x4C, 0x13, 0x74, 0xE9, 0xA7}, // 8
    {0x2A, 0x0C, 0xB6, 0x60, 0x87, 0x4F, 0x7C, 0x48, 0x6B, 0x87, 0xF9, 0x98, 0xBF, 0x2C, 0xBF, 0xBE}, // 9
    {0x3D, 0xAD, 0x6A, 0xFD, 0xF3, 0x11, 0x92, 0x2F, 0x11, 0x47, 0x7B, 0x25, 0xBB, 0x64, 0xCC, 0xE5}, // 10
    {0x70, 0x82, 0x45, 0xF7, 0xD1, 0xC1, 0x40, 0x3C, 0x48, 0x39, 0xD4, 0x07, 0x66, 0x94, 0xC5, 0xA3}, // 11
    {0x41, 0x2F, 0xA0, 0x34, 0x40, 0x32, 0x63, 0x52, 0x79, 0xDF, 0x77, 0x34, 0x43, 0x43, 0x19, 0xB4}, // 12
    {0xC5, 0x5F, 0xAB, 0x96, 0x20, 0xEB, 0xD2, 0x69, 0x25, 0xA7, 0x70, 0x8B, 0x3B, 0x36, 0x2E, 0x7C}, // 13
    {0x65, 0xCE, 0xB0, 0xA6, 0x00, 0x14, 0xF8, 0x7A, 0xF3, 0x6F, 0xAE, 0x36, 0xB2, 0xC8, 0xEA, 0x77}, // 14
    {0x27, 0x96, 0x0D, 0x47, 0x81, 0xDF, 0xB0, 0xA6, 0x86, 0x21, 0x31, 0xC1, 0x57, 0x5F, 0x3D, 0xBC}  // 15
};
/***
 *    songshuai add at 2019.10.28, start
 **/
unsigned char ivData[AES_BLOCK_SIZE] = {
	0xc6,0xa1,0x3b,0x37,0x87,0x8f,0x5b,0x82,
	0x6f,0x4f,0x81,0x62,0xa1,0xc8,0xd8,0x79};
/***
 *    songshuai add at 2019.10.28, end
 **/

 
/***
 *    songshuai add at 2019.09.05
 **/
#define random_out(a,b) ((random()%(b-a))+a) // [a, b)之间的随机数，不包含数值b
#define random_in(a,b)  ((random()%(b-a+1))+a) // [a, b]之间的随机数，包含a和b 	

unsigned char getRandom(void)
{
    srand((int)time(NULL)); 
	return random_in(1, 15);
}

void Encrypt_ecb(unsigned char *in, unsigned char *out, unsigned char *key, int len )
{
    int i;
    AES_KEY aes;
	if(AES_set_encrypt_key(key, 128, &aes) < 0) return ;
    for(i = 0; i < len / 16; i++) AES_encrypt(in + i * 16, out + i * 16, &aes);
}
void Decrypt_ecb(unsigned char *in, unsigned char *out, unsigned char *key, int len )
{
    int i;
    AES_KEY aes;
    if( AES_set_decrypt_key(key, 128, &aes) < 0) return ;
    for(i = 0; i < len / 16; i++) AES_decrypt(in + i * 16, out + i * 16, &aes);
}
/**
 * songshuai add in 2019.10.22 start
 **/
void Encrypt_cbc(unsigned char *in, unsigned char *out, unsigned char *key, unsigned char *iv, int len )
{
    AES_KEY aes;
    unsigned char ivtmp[16] = {0};
    memcpy(ivtmp, iv, 16);
	if( AES_set_encrypt_key(key, 128, &aes) < 0) return ;
    AES_cbc_encrypt(in, out, len, &aes, ivtmp, AES_ENCRYPT);
}
void Decrypt_cbc(unsigned char *in, unsigned char *out, unsigned char *key, unsigned char *iv, int len )
{
    AES_KEY aes;
    unsigned char ivtmp[16] = {0};
    memcpy(ivtmp, iv, 16);
    if( AES_set_decrypt_key(key, 128, &aes) < 0) return ;
    AES_cbc_encrypt(in, out, len, &aes, ivtmp, AES_DECRYPT);
}
void printData(u_int8_t *data, u_int32_t data_size)
{
    u_int32_t i = 0;
	for(i=0; i<data_size; ++i) printf("%02X", data[i]);
    printf("\n");
}
/**
 * songshuai add in 2019.10.22 end
 **/
int EncDecTest()
{
    int length = 0;
    unsigned char randomNum = 0;
    char buf[] = { 
            0xA8, 0x8D, 0x2F, 0xCB, 0x29, 0xDF, 0x81, 0xEF, 0xAD, 0xE8, 0x1C, 0xDD, 0x41, 0xA8, 0xCF, 0x77, 
            0x4A, 0x33, 0xEF, 0x6C, 0xFF, 0x8B, 0x34, 0x34, 0xD6, 0x13, 0xDA, 0x1D, 0xEB, 0xA6, 0xBA, 0x93,
        };
    
    char *offset = buf + 0;
    unsigned char *encbuf = (unsigned char *)malloc(1024);
    unsigned char *decbuf = (unsigned char *)malloc(1024);

    
    length = sizeof(buf) - 0;
    length -= length % ENCLENBASE;

    randomNum = ((length % ENCLENBASE) == 0 ? 1 : (length % ENCLENBASE));
    printf("length = %d, randomNum = %d \n", length, randomNum);
    printf("keydat : "); printData(keyDataUnion[randomNum], 16);
    Encrypt_ecb(offset, encbuf, keyDataUnion[randomNum], length); 
    printf("offset : "); printData(offset, length);
    printf("keydat : "); printData(keyDataUnion[randomNum], 16);
    Decrypt_ecb(encbuf, decbuf, keyDataUnion[randomNum], length); 
    printf("decbuf : "); printData(decbuf, length);
    
    if( memcmp(offset, decbuf, length) == 0 )
    {
        system("./size/abcd 1");
        system("./size/abcd 2");
        printf("Comparison complete, pass!\n");
        system("./size/abcd 2");
        system("./size/abcd 1");
    }
    else
    {
        system("./size/abcd 1");
        system("./size/abcd 2");
        printf("Comparison complete, NO pass!\n");
        system("./size/abcd 2");
        system("./size/abcd 1");
    }

    free(encbuf);
    free(decbuf);

    putchar(10);
    putchar(10);
    putchar(10);

    unsigned char *encbuf_cbc = (unsigned char *)malloc(1024);
    unsigned char *decbuf_cbc = (unsigned char *)malloc(1024);

    printf("keydat : "); printData(keyDataUnion[randomNum], 16);
    printf("offset : "); printData(offset, length);
    Encrypt_cbc(offset, encbuf_cbc, keyDataUnion[randomNum], ivData, length); 
    printf("encbuf : "); printData(encbuf_cbc, length);

    Decrypt_cbc(encbuf_cbc, decbuf_cbc, keyDataUnion[randomNum], ivData, length); 
    printf("decbuf : "); printData(decbuf_cbc, length);

    if( memcmp(offset, decbuf_cbc, length) == 0 )
    {
        system("./size/abcd 1");
        system("./size/abcd 2");
        printf("Comparison complete, pass!\n");
        system("./size/abcd 2");
        system("./size/abcd 1");
    }
    else
    {
        system("./size/abcd 1");
        system("./size/abcd 2");
        printf("Comparison complete, NO pass!\n");
        system("./size/abcd 2");
        system("./size/abcd 1");
    }

    free(encbuf_cbc);
    free(decbuf_cbc);
    return 0;
}
