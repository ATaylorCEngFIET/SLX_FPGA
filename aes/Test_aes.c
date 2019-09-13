#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "aes_main.h"
#include "sbox.h"

uint8_t state_temp[16] =  {0x00,0x44,0x88,0xcc,0x11,0x55,0x99,0xdd,0x22,0x66,0xaa,0xee,0x33,0x77,0xbb,0xff};

uint8_t key[32] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};  // initial key

//#define TIME_STAMP_INIT  unsigned long long clock_start, clock_end;  clock_start = sds_clock_counter();
//#define TIME_STAMP_SW  { clock_end = sds_clock_counter(); printf("Average number of processor cycles : %llu \n", (clock_end-clock_start)); clock_start = sds_clock_counter();  }

void keyexpansion(uint8_t key[32], uint8_t ekey[240]);

int main(void)
{
	uint8_t x,y,i;
	uint8_t *state;
	uint8_t *cipher;

	uint8_t *ekey;
	ekey = (uint8_t *) malloc(240 *sizeof(uint8_t));
	cipher = (uint8_t *) malloc(16*sizeof(uint8_t));
	state = (uint8_t *) malloc(16*sizeof(uint8_t));


		state[0] = state_temp[0];
		state[1] = state_temp[1];
		state[2] = state_temp[2];
		state[3] = state_temp[3];
		state[4] = state_temp[4];
		state[5] = state_temp[5];
		state[6] = state_temp[6];
		state[7] = state_temp[7];
		state[8] = state_temp[8];
		state[9] = state_temp[9];
		state[10] = state_temp[10];
		state[11] = state_temp[11];
		state[12] = state_temp[12];
		state[13] = state_temp[13];
		state[14] = state_temp[14];
		state[15] = state_temp[15];

	keyexpansion(key,ekey);

//	TIME_STAMP_INIT
	aes_enc(state,cipher,ekey);
//	TIME_STAMP_SW

	for(x=0;x<16;x++){
			printf(" %x", cipher[x]);
	}
	printf("\n");
	return 0;
}

void keyexpansion(uint8_t key[32], uint8_t ekey[240])
{
	  uint32_t i, j, k;
	  uint8_t temp[4];

	  for(i = 0; i < nk; ++i)
	  {
	    ekey[(i * 4) + 0] = key[(i * 4) + 0];
	    ekey[(i * 4) + 1] = key[(i * 4) + 1];
	    ekey[(i * 4) + 2] = key[(i * 4) + 2];
	    ekey[(i * 4) + 3] = key[(i * 4) + 3];
	  }


	  for(; (i < (nb * (nr + 1))); ++i)
	  {
	    for(j = 0; j < 4; ++j)
	    {
	      temp[j]= ekey[(i-1) * 4 + j];
	    }
	    if (i % nk == 0)
	    {
	      {
	        k = temp[0];
	        temp[0] = temp[1];
	        temp[1] = temp[2];
	        temp[2] = temp[3];
	        temp[3] = k;
	      }


	      {
	        temp[0] = sbox[temp[0]];
	        temp[1] = sbox[temp[1]];
	        temp[2] = sbox[temp[2]];
	        temp[3] = sbox[temp[3]];
	      }

	      temp[0] =  temp[0] ^ Rcon[i/nk];
	    }
	    else if (nk > 6 && i % nk == 4)
	    {
	      // Function Subword()
	      {
	        temp[0] = sbox[temp[0]];
	        temp[1] = sbox[temp[1]];
	        temp[2] = sbox[temp[2]];
	        temp[3] = sbox[temp[3]];
	      }
	    }
	    ekey[i * 4 + 0] = ekey[(i - nk) * 4 + 0] ^ temp[0];
	    ekey[i * 4 + 1] = ekey[(i - nk) * 4 + 1] ^ temp[1];
	    ekey[i * 4 + 2] = ekey[(i - nk) * 4 + 2] ^ temp[2];
	    ekey[i * 4 + 3] = ekey[(i - nk) * 4 + 3] ^ temp[3];
	  }

}
