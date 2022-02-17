/*
The MIT License (MIT)

Copyright (c) 2016 British Broadcasting Corporation.
This software is provided by Lancaster University by arrangement with the BBC.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <memory>

#include "MicroBit.h"
#include "des.h"
//#include "MicroBitSamples.h"

//#ifdef MICROBIT_SAMPLE_BUTTON_EVENTS

MicroBit uBit;

//
// Print details of all events received to the serial port.
// Default settings are 115200 baud, 8N1 over the USB interface.
//
//////////////////////MD5 REGION///////////////////////////////////
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
uint32_t h0, h1, h2, h3;
void md5(uint8_t *initial_msg, size_t initial_len) {

    // Message
    uint8_t *msg = NULL;

    // Note: All variables are unsigned 32 bit and wrap modulo 2^32 when calculating

    // r specifies the per-round shift amounts

    uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

    // Use binary integer part of the sines of integers (in radians) as constants

    // Initialize variables:
    uint32_t k[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

    h0 = 0x67452301;
    h1 = 0xefcdab89;
    h2 = 0x98badcfe;
    h3 = 0x10325476;

    // Pre-processing: adding a single 1 bit
    // append "1" bit to message
    /* Notice: the input bytes are considered as bits strings,
       where the first bit is the most significant bit of the byte.*/

    // Pre-processing: padding with zeros
    // append "0" bit until message length in bit Ã¢â€°Â¡ 448 (mod 512)
    // append length mod (2 pow 64) to message

    int new_len;
    for(new_len = initial_len*8 + 1; new_len%512!=448; new_len++);
    new_len /= 8;

    msg = (uint8_t *) calloc(new_len + 64, 1);

    // also appends "0" bits
    memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 128; // write the "1" bit

    uint32_t bits_len = 8*initial_len; // note, we append the len
    memcpy(msg + new_len, &bits_len, 4);           // in bits at the end of the buffer

    // Process the message in successive 512-bit chunks:
    //for each 512-bit chunk of message:
    int offset;
    for(offset=0; offset<new_len; offset += (512/8)) {

    // break chunk into sixteen 32-bit words w[j], 0 Ã¢â€°Â¤ j Ã¢â€°Â¤ 15
        uint32_t *w = (uint32_t *) (msg + offset);

#ifdef DEBUG
        printf("offset: %d %x\n", offset, offset);
        int j;
        for(j =0; j < 64; j++) printf("%x ", ((uint8_t *) w)[j]);
        puts("");
#endif

     // Initialize hash value for this chunk:
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;

     // Main loop:
        uint32_t i;
        for(i = 0; i<64; i++) {

#ifdef ROUNDS
            uint8_t *p;
            printf("%i: ", i);
            p=(uint8_t *)&a;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], a);

            p=(uint8_t *)&b;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], b);

            p=(uint8_t *)&c;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], c);

            p=(uint8_t *)&d;
            printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], d);
            puts("");
#endif


            uint32_t f, g;

             if (i < 16) {
                f = (b & c) | ((~b) & d);
                g = i;
            } else if (i < 32) {
                f = (d & b) | ((~d) & c);
                g = (5*i + 1) % 16;
            } else if (i < 48) {
                f = b ^ c ^ d;
                g = (3*i + 5) % 16;
            } else {
                f = c ^ (b | (~d));
                g = (7*i) % 16;
            }

#ifdef ROUNDS
            printf("f=%x g=%d w[g]=%x\n", f, g, w[g]);
#endif
            uint32_t temp = d;
            d = c;
            c = b;
            //printf("rotateLeft(%x + %x + %x + %x, %d)\n", a, f, k[i], w[g], r[i]);
            b = b + LEFTROTATE((a + f + k[i] + w[g]), r[i]);
            a = temp;



        }

        // Add this chunk's hash to result so far:

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;

    }

    // cleanup
    free(msg);

}
/////////////////END OF MD5 REGION//////////////////////////////
//function to print hexadecimal array
void print_hex(const BYTE str[], int len)
{
    int idx;

    for(idx = 0; idx < len; idx++)
        uBit.serial.printf("%2.2x", str[idx]);
}
//function to convert ascii to hexadecimal
void conv2hex(const char* str, const BYTE* hex){
    sprintf((char *)hex, "%02x", str[0]);
    int i=1;
    while(str[i] != '\0'){
        sprintf((char *)hex, "%s%02x", hex, str[i++]);
    }
    //hex[(strlen(str)*2)] ='\0';
}
//functions to convert hexadecimal to ascii
int hex_to_int(char c)
{
    if (c >= 97)
        c = c - 32;
    int first = c / 16 - 3;
    int second = c % 16;
    int result = first * 10 + second;
    if (result > 9) result--;
    return result;
}
int hex_to_ascii(char c, char d){
        int high = hex_to_int(c) * 16;
        int low = hex_to_int(d);
        return high+low;
}
 BYTE key1[DES_BLOCK_SIZE] = {0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF}; //initial key
 BYTE schedul[16][6];
 BYTE buf[DES_BLOCK_SIZE], buf2[DES_BLOCK_SIZE];
 int cycle=0;
 char HalfMD5[25] = "0123456789ABCDEF"; //initialization of the string used to cut half of MD5
 
 //Function to handle click of all buttons events
void onButton(MicroBitEvent e)
{
    //if block to handle click of button A
    if (e.source == MICROBIT_ID_BUTTON_A && e.value == MICROBIT_BUTTON_EVT_CLICK){
        char c, *plaintext;
    ManagedString str;
   uBit.serial.send("\r\n Button A was clicked, Please Enter a string of characters:");
    str=uBit.serial.readUntil("'\r''\n'");
    plaintext= (char *) str.toCharArray(); //conversion of input string to character array
    
    uint8_t * msg= (uint8_t *) plaintext;
    size_t len = strlen(( char *)msg);

        md5(msg, len);
    
    uint8_t *p;
    uBit.serial.printf("\nYou made a click on Button A and String= %s", (char *) msg);
    // display result
    uBit.serial.printf("\nThe md5 hash of the string is: ");
    
    char Md5Array[50];
    p=(uint8_t *)&h0; 
    sprintf(Md5Array, "%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
    p=(uint8_t *)&h1; 
    sprintf(Md5Array, "%s%2.2x%2.2x%2.2x%2.2x",Md5Array, p[0], p[1], p[2], p[3]);
    p=(uint8_t *)&h2; 
    sprintf(Md5Array, "%s%2.2x%2.2x%2.2x%2.2x",Md5Array, p[0], p[1], p[2], p[3]);
    p=(uint8_t *)&h3; 
    sprintf(Md5Array, "%s%2.2x%2.2x%2.2x%2.2x",Md5Array, p[0], p[1], p[2], p[3]);
    uBit.serial.printf(Md5Array);
    uBit.serial.printf("\n");
    
    //Block of code to encrypt in DES
    const BYTE pt1[DES_BLOCK_SIZE] = {0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xE7};
    conv2hex((const char*) plaintext, pt1); //conversion of input string to hexadecimal
    des_key_setup(key1, schedul, DES_ENCRYPT);
    des_crypt(pt1, buf,  schedul);
    
    //printing of cipher and key
    uBit.serial.printf("The cipher text with DES is: \t");
    print_hex(buf, DES_BLOCK_SIZE);
    uBit.serial.printf("\n");
    uBit.serial.printf("The Key used was: \t");
    if(cycle==0)
    print_hex(key1, DES_BLOCK_SIZE);
    else uBit.serial.printf(HalfMD5);
    puts("");
    }
    
    //if block to handle press of button B
    if (e.source == MICROBIT_ID_BUTTON_B && e.value == MICROBIT_BUTTON_EVT_CLICK){
        //code segment to decrypt the cipher text
        memcpy(buf2, buf, DES_BLOCK_SIZE);
        des_key_setup(key1, schedul, DES_DECRYPT);
        des_crypt(buf2, buf,  schedul);
        
        //conversion of the decrypted hexadecimal to ascii
        char letter=0, decrypted[40]; int i;
        sprintf(decrypted, "%c", hex_to_ascii(buf[0], buf[1]));
            for(i=2; i<DES_BLOCK_SIZE; i++){
            if(i%2 != 0) sprintf(decrypted , "%s%c", decrypted , hex_to_ascii(letter, buf[i]));
                else letter = buf[i];
            }
            //printing out the decrypted text
         uBit.serial.printf("\n");
         uBit.serial.printf("You pressed B, The decrypted text is: \t");   
         uBit.serial.printf(decrypted);
         uBit.serial.printf("\n");
    }
    
    //if block to handle press of button A+B
    if (e.source == MICROBIT_ID_BUTTON_AB && e.value == MICROBIT_BUTTON_EVT_CLICK){
        char c, *plaintext;
    ManagedString str;
   uBit.serial.send("\r\n Button A and B was clicked, Please Enter a string of characters:");
    str=uBit.serial.readUntil("'\r''\n'");
    plaintext= (char *) str.toCharArray(); //conversion of Managedstring to character array
    
    uint8_t * msg= (uint8_t *) plaintext;
    size_t len = strlen(( char *)msg);

        md5(msg, len);
    
    uint8_t *p;
    uBit.serial.printf("\nYou made a click on Button A and B and String= %s", (char *) msg);
    // display result
    uBit.serial.printf("\nThe Key used  for the encryption was: \t");
    if(cycle==0)
    print_hex(key1, DES_BLOCK_SIZE);
    else uBit.serial.printf(HalfMD5);
    uBit.serial.printf("\nThe md5 hash of the string is: ");
    
    //MD5 code 
    char Md5Array[50];
    p=(uint8_t *)&h0; 
    sprintf(Md5Array, "%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
    sprintf(HalfMD5, "%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
    p=(uint8_t *)&h1; 
    sprintf(Md5Array, "%s%2.2x%2.2x%2.2x%2.2x",Md5Array, p[0], p[1], p[2], p[3]);
    sprintf(HalfMD5, "%s%2.2x%2.2x%2.2x%2.2x",HalfMD5, p[0], p[1], p[2], p[3]);
    p=(uint8_t *)&h2; 
    sprintf(Md5Array, "%s%2.2x%2.2x%2.2x%2.2x",Md5Array, p[0], p[1], p[2], p[3]);
    p=(uint8_t *)&h3; 
    sprintf(Md5Array, "%s%2.2x%2.2x%2.2x%2.2x",Md5Array, p[0], p[1], p[2], p[3]);
    uBit.serial.printf(Md5Array);
    uBit.serial.printf("\n");
    
    //Encryption of plaintext
    const BYTE pt1[DES_BLOCK_SIZE] = {0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xE7};
    conv2hex((const char*) plaintext, pt1);  //conversion of ascii text to hexadecimal
    des_key_setup(key1, schedul, DES_ENCRYPT);
    des_crypt(pt1, buf,  schedul);
    uBit.serial.printf("The cipher text with DES is: \t");
    print_hex(buf, DES_BLOCK_SIZE);
    uBit.serial.printf("\n");
    
    //decryption of cipher text
    memcpy(buf2, buf, DES_BLOCK_SIZE);
        des_key_setup(key1, schedul, DES_DECRYPT);
        des_crypt(buf2, buf,  schedul);
        
        //conversion of hexadecimal to ascii
        char letter=0, decrypted[40]; int i;
        sprintf(decrypted, "%c", hex_to_ascii(buf[0], buf[1]));
            for(i=2; i<DES_BLOCK_SIZE; i++){
            if(i%2 != 0) sprintf(decrypted , "%s%c", decrypted , hex_to_ascii(letter, buf[i]));
                else letter = buf[i];
            }
         uBit.serial.printf("\n");
         uBit.serial.printf("The decrypted text is: \t");   
         uBit.serial.printf(decrypted);
         uBit.serial.printf("\n");
         
         //Copying half of the MD5 hash into the key
         //This function will copy the first 8 Chracters of the HalfMD5 array into key
        memcpy(key1, HalfMD5, DES_BLOCK_SIZE);
        cycle = 1;
            
    }
   
    uBit.serial.printf("\n");
}


int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();

    // Register to receive events when any buttons are clicked, including the A+B virtual button (both buttons at once).
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_EVT_ANY, onButton);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_EVT_ANY, onButton);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_AB, MICROBIT_EVT_ANY, onButton);

    // We're done, so just enter a power efficient sleep while we wait for an event.
    while (1)
        uBit.sleep(10000);
}

//#endif