#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void InitTable(unsigned int *pTable)
{
	int   i,j;
	unsigned int crc;
	for(i = 0;i < 256;i++)
	{
		crc = i;
		for(j = 0;j < 8;j++)
		{
			if(crc & 1)
			{
				crc = (crc >> 1) ^ 0xEDB88320;
			}
			else
			{
				crc = crc >> 1;
			}
		}
		pTable[i] = crc;
	}
}

unsigned int CRC32(const char *pszBuffer, unsigned int ulLen)
{
	static unsigned int aulTable[256];
	static int bInit = 0;
	unsigned int i = 0;
	if(!bInit)
	{
		InitTable(aulTable);
		bInit = 1;
	}

	unsigned int ulRet = 0xFFFFFFFF;
	unsigned int ulRet_wrong = 0xFFFFFFFF;
	for( ; i < ulLen;i++)
	{
		//ulRet_wrong = aulTable[(((unsigned char)(ulRet_wrong & 0xFF)) ^ pszBuffer[i])] ^ (ulRet_wrong >> 8);
		ulRet_wrong = aulTable[(((unsigned char)(ulRet_wrong & 0xFF)) ^ (unsigned char)pszBuffer[i])] ^ (ulRet_wrong >> 8);
		/*ulRet_wrong = aulTable[(((unsigned char)(ulRet_wrong & 0xFF)) ^ (unsigned char)pszBuffer[i])] ^ (ulRet_wrong >> 8);
		ulRet = aulTable[(ulRet  ^ pszBuffer[i])&0xFF] ^ (ulRet >> 8);
		if( ulRet_wrong != ulRet )
		{
			printf("Idx:%d bytes:0x%x\n", i, (unsigned char)pszBuffer[i]);
		}*/
	}
	//ulRet = ~ulRet;
	ulRet_wrong = ~ulRet_wrong;
	//printf("CRC value:0x%x\n", ulRet);
	printf("CRC wrong value:0x%x\n", ulRet_wrong);

	return ulRet;
}

int main(int argc, char *argv[])
{
	unsigned char data[] = {0x31, 0x32, 0x33, 0xe4, 0xb8, 0x9c, 0x31};
	unsigned int ret = 0;

	CRC32(data, sizeof(data));
}

