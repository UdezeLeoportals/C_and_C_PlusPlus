/*********************************************************************
* Filename:   aes.h
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Defines the API for the corresponding AES implementation.
*********************************************************************/
//#include "GOD_JESUS_CHRIST_HOLY_SPIRIT_sha256.h"
//#include "GOD_JESUSC_HolySpirit_AESecb.h"
#include "MicroBit.h"
#include "GOD_JESUSC_HOLY_SPIRIT_Group4.h"

#ifdef GOD_JESUS_CHRIST_HOLY_SPIRIT_Send_h
#include "GOD_JESUS_CHRIST_HOLY_SPIRIT_sha256.h"
#include "GOD_JESUSC_HolySpirit_AESecb.h"

MicroBit uBit;
//Function to receive pin+salt, command and perform SHA256 hash to generate dp key  
//and return the AES ECB cipher text
void print_hex(BYTE str[], int len)
{
    int idx;

    for(idx = 0; idx < len; idx++)
        uBit.serial.printf("%02x", str[idx]);
}
void JesusChrist_shaEnc(char* ChristSalt, char* Gospel_command, BYTE *enc_buf){
            WORD key_schedule[60];
            BYTE Godplaintext4[128], Heaven_key[SHA256_BLOCK_SIZE];
            SHA256_CTX ctx;
            
            //Perform SHA 256 on the pin+salt to get the data protection key
            sha256_init(&ctx);  
            sha256_update(&ctx, (BYTE*)ChristSalt, strlen((char*)ChristSalt));
            sha256_final(&ctx, Heaven_key);
            
            //Convert the ASCII format of the command to hexadecimal
            JESUS_CHRIST_conv(Gospel_command, Godplaintext4);
            
            //Perform AES ECB Encryption on the command using the key
            aes_key_setup(Heaven_key, key_schedule, 256);
            aes_encrypt(Godplaintext4, enc_buf, key_schedule, 256);
}
int main()
{
    uBit.init();
    uBit.radio.enable();
  
    BYTE enc_buf[128];

    int pin, Lord, number;
    char Christ_salt[10], GOD_JESUSC_SPIRIT_cipher1[32], GOD_JESUSC_SPIRIT_cipher2[32], Church_enc[64], ChristSalt[12];
    char * Gospel_command;

     while(1){
       //Generate random salt like JESUS345, JESUS789, JESUS045
       sprintf(Christ_salt, "%s", "JESUS");
       for(Lord=0; Lord<3; Lord++){
           number = (int) (10.0*rand()/(RAND_MAX + 1.0));
           sprintf(Christ_salt, "%s%d",Christ_salt, number);
       }
       //First event for a Press of A
        if (uBit.buttonA.isPressed()){
            pin =1;                         //pin for Button A long press
            Gospel_command = "CHRIST"; //command for Button A long press
            sprintf(ChristSalt, "%d%s", pin, Christ_salt); //pin+salt concatenation
            
            //call to SHA256 and AES encryption function
            JesusChrist_shaEnc(ChristSalt, Gospel_command, enc_buf);
            
           //copy cipher text from enc_buf BYTE array to Christ_enc C array
            memcpy(Church_enc, enc_buf, strlen((char*)enc_buf));
            
            //split into two strings for radio transmission
            strncpy(GOD_JESUSC_SPIRIT_cipher1, Church_enc, 8);
            GOD_JESUSC_SPIRIT_cipher1[8] = '\0';
            strcpy(GOD_JESUSC_SPIRIT_cipher2, &Church_enc[8]);
                
            // create two strings for the cipher text halves, and the salt
            ManagedString AlmightyLord_cipher1(GOD_JESUSC_SPIRIT_cipher1);
            ManagedString AlmightyLord_cipher2(GOD_JESUSC_SPIRIT_cipher2);
            ManagedString AlmightyLord_salt(ChristSalt);
            
            //print the two cipher texts halves, pin+salt and command
          /* printf("\n\tCiphertext = ");
            print_hex((BYTE*)GOD_JESUSC_SPIRIT_cipher1, 8);
            printf("\n\t");
            print_hex((BYTE*)GOD_JESUSC_SPIRIT_cipher2, 8);
            printf("\n\t");
            uBit.serial.send(AlmightyLord_salt);
            //uBit.serial.printf("\n\tSalt = %s",ChristSalt);
            uBit.serial.printf("\n\t Command = %s", Gospel_command);*/
            
            //uBit.radio.datagram.send("1");
            uBit.radio.datagram.send(AlmightyLord_cipher1);
            uBit.radio.datagram.send(AlmightyLord_cipher2);
            uBit.radio.datagram.send(AlmightyLord_salt);      
      }
      //Event for Press of B Button 
       if (uBit.buttonB.isPressed()){
            pin =2;                         //pin for Button A long press
            Gospel_command = "SPIRIT"; //command for Button A long press
            sprintf(ChristSalt, "%d%s", pin, Christ_salt); //pin+salt concatenation
            
            //call to SHA256 and AES encryption function
            JesusChrist_shaEnc(ChristSalt, Gospel_command, enc_buf);
            
           //copy cipher text from enc_buf BYTE array to Christ_enc C array
            memcpy(Church_enc, enc_buf, strlen((char*)enc_buf));
            
            //split into two strings for radio transmission
            strncpy(GOD_JESUSC_SPIRIT_cipher1, Church_enc, 8);
            GOD_JESUSC_SPIRIT_cipher1[8] = '\0';
            strcpy(GOD_JESUSC_SPIRIT_cipher2, &Church_enc[8]);
                
            // create two strings for the cipher text halves, and the salt
            ManagedString AlmightyLord_cipher1(GOD_JESUSC_SPIRIT_cipher1);
            ManagedString AlmightyLord_cipher2(GOD_JESUSC_SPIRIT_cipher2);
            ManagedString AlmightyLord_salt(ChristSalt);
            
              //print the two cipher texts halves, pin+salt and command
           /* printf("\n\tCiphertext = ");
            print_hex((BYTE*)GOD_JESUSC_SPIRIT_cipher1, 8);
            printf("\n");
            print_hex((BYTE*)GOD_JESUSC_SPIRIT_cipher2, 8);
            uBit.serial.printf("\n\tSalt = %s",ChristSalt);
            uBit.serial.printf("\n\t Command = %s", Gospel_command);*/
           
            //uBit.radio.datagram.send("2");
            uBit.radio.datagram.send(AlmightyLord_cipher1);
            uBit.radio.datagram.send(AlmightyLord_cipher2);
            uBit.radio.datagram.send(AlmightyLord_salt);      
      }
      //Event for a Press A and B
       if (uBit.buttonAB.isPressed()){ 
            pin =   3;                         //pin for Button A long press
            Gospel_command = "ALMIGHTY"; //command for Button A long press
            sprintf(ChristSalt, "%d%s", pin, Christ_salt); //pin+salt concatenation
            
            //call to SHA256 and AES encryption function
            JesusChrist_shaEnc(ChristSalt, Gospel_command, enc_buf);
            
           //copy cipher text from enc_buf BYTE array to Christ_enc C array
            memcpy(Church_enc, enc_buf, strlen((char*)enc_buf));
            
            //split into two strings for radio transmission
            strncpy(GOD_JESUSC_SPIRIT_cipher1, Church_enc, 8);
            GOD_JESUSC_SPIRIT_cipher1[8] = '\0';
            strcpy(GOD_JESUSC_SPIRIT_cipher2, &Church_enc[8]);
                
            // create two strings for the cipher text halves, and the salt
            ManagedString AlmightyLord_cipher1(GOD_JESUSC_SPIRIT_cipher1);
            ManagedString AlmightyLord_cipher2(GOD_JESUSC_SPIRIT_cipher2);
            ManagedString AlmightyLord_salt(ChristSalt);
            
            //print the two cipher texts halves and pin+salt
             //print the two cipher texts halves, pin+salt and command
           /* printf("\n\tCiphertext = ");
            print_hex((BYTE*)GOD_JESUSC_SPIRIT_cipher1, 8);
            print_hex((BYTE*)GOD_JESUSC_SPIRIT_cipher2, 8);
            uBit.serial.printf("\n\tSalt = %s",ChristSalt);
            uBit.serial.printf("\n\t Command = %s", Gospel_command);*/
           
            uBit.radio.datagram.send(AlmightyLord_cipher1);
            uBit.radio.datagram.send(AlmightyLord_cipher2);
            uBit.radio.datagram.send(AlmightyLord_salt);   
      } 
      
      uBit.sleep(100);
    }
    release_fiber();
}

#endif


