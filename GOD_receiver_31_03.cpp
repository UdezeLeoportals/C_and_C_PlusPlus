/*********************************************************************
* Filename:   aes.h
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Defines the API for the corresponding AES implementation.
*********************************************************************/
/*************************** HEADER FILES ***************************/
/*#include <stddef.h>
#include <stdio.h>
#include <memory>
#include <stdlib.h> */
#include "MicroBit.h" 
#include "GOD_JESUSC_HOLY_SPIRIT_Group4.h"

#ifdef GOD_JESUS_CHRIST_HOLY_SPIRIT_Recv_h
#include "GOD_JESUS_CHRIST_HOLY_SPIRIT_sha256.h"
#include "GOD_JESUSC_HolySpirit_AESecb.h"

MicroBit uBit;
/*********************** FUNCTION DEFINITIONS ***********************/
void print_hex(BYTE str[], int len)
{
    int idx;

    for(idx = 0; idx < len; idx++)
        uBit.serial.printf("%02x", str[idx]);
}


int mercy=0, i;
char *Christ_cypher2, *Christ_cypher1, GODly[50], HEAVEN[50];
ManagedString Holy, Spirit, Grace, Crucifix_pin;
char *Christ_pinSalt, Heaven_key[100], Gods_command[20], JesusChrist_cypher[33];      
WORD key_schedule[60];
BYTE  enc_buf4[128], key[SHA256_BLOCK_SIZE];
char lord=0, Gospel_command5[40];

void GodJesusSpirit_handler(MicroBitEvent)
{       mercy++;
        /*if(mercy%4==1){
            Crucifix_pin = uBit.radio.datagram.recv();    
        }
        
        if(Crucifix_pin=="1"){*/
        uBit.serial.printf("\nJESUS IS LORD\n");
        //Receive first half of ciphertext
        if(mercy%3==1){
            Holy = uBit.radio.datagram.recv();
            Christ_cypher1= (char*)Holy.toCharArray(); 
            print_hex((BYTE*)Christ_cypher1, 8);
            uBit.serial.printf("\n%d",strlen(Christ_cypher1));
        }
        
        //Receive second half of ciphertext
          if(mercy%3==2){  
          Spirit = uBit.radio.datagram.recv(); 
            Christ_cypher2= (char*)Spirit.toCharArray();
            uBit.serial.printf("\n");
            print_hex((BYTE*)Christ_cypher2,8);
            //concatenate the two halves of the cipher text into one
            memcpy(GODly, Christ_cypher1, 8); 
            memcpy(HEAVEN, Christ_cypher2, 8);
            sprintf(JesusChrist_cypher, "%s%s", GODly, HEAVEN);
            uBit.serial.printf("\n");
            print_hex((BYTE*)JesusChrist_cypher,16);
        }
        
        //Receive pin+salt
        if(mercy%3==0){
        uBit.serial.printf("\n");
        Grace = uBit.radio.datagram.recv();
        Christ_pinSalt = (char*) Grace.toCharArray();
         uBit.serial.printf("\n%s", Christ_pinSalt);
        }
        uBit.serial.printf("\n%d",mercy);
        
        if(mercy%3==0){
            uBit.serial.printf("\n\t strlen cipher= %d",strlen(JesusChrist_cypher));
            
            //Generate key from pin+salt
            SHA256_CTX ctx;
    
            sha256_init(&ctx);
            sha256_update(&ctx, (BYTE*)Christ_pinSalt, strlen((char*)Christ_pinSalt));
            sha256_final(&ctx, key);
    
            //AES ECB DECRYPTION
            aes_key_setup(key, key_schedule, 256);
            aes_decrypt((BYTE*)JesusChrist_cypher, enc_buf4, key_schedule, 256);
            
            uBit.serial.printf(  "\n\tKey \t: ");
            print_hex(key, 32);
            uBit.serial.printf("\n\t Cipher text: ");
            print_hex((BYTE*)JesusChrist_cypher, 16);
            uBit.serial.printf("\n\tDecrypted Hex: ");
            print_hex(enc_buf4, strlen((char*)enc_buf4));
            
            //convert the hexadecimal decrypted text to ascii
            sprintf(Gospel_command5, "%c", hex_to_ascii(enc_buf4[0], enc_buf4[1]));
            for(i=2; i<strlen((char*)enc_buf4); i++){
            if(i%2 != 0) sprintf(Gospel_command5 , "%s%c", Gospel_command5 , hex_to_ascii(lord, enc_buf4[i]));
                else lord = enc_buf4[i];
            }
            uBit.serial.printf("\n\t ASCII value of command= %s\n", Gospel_command5);
        }
    }
    
    



int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();
    
    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, GodJesusSpirit_handler);
    uBit.radio.enable();
    
    while(1){
        
        uBit.sleep(1000);
     }
}

#endif
