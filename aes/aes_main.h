#ifndef AES_MAIN_H_
#define AES_MAIN_H_
#define nk 8
#define nb 4
#define nr 14


void aes_enc(uint8_t state[16],uint8_t cipher[16],uint8_t ekey[240]);

#endif /* AES_MAIN_H_ */