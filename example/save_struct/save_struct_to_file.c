#include <stdio.h>
#include <string.h>
#define SAVE_PATH "./student.data"
#define ETH_IF_NAME_LEN     32
#define EN_SYS_IF_DEV_TOTAL 4

/* 单个网口配置信息 */
typedef struct tag_ST_GLB_SYS_ETH_CONFIG
{
    int bDhcp;              /* DHCP是否开启 */
    unsigned int  ulIp;               /* ip地址    网络字节序 */
    unsigned int  ulIpMask;           /* ip掩码    网络字节序 */
    unsigned int  ulGateAddr;         /* 网关      网络字节序 */
    char   aucIfName[ETH_IF_NAME_LEN];
}ST_GLB_SYS_ETH_CONFIG;

/* 全局网口配置信息 */
typedef struct tag_ST_GLB_SYS_IF_CONFIG
{
	    ST_GLB_SYS_ETH_CONFIG   stEth[EN_SYS_IF_DEV_TOTAL];
	    char                     aucIfPubName[ETH_IF_NAME_LEN];
}ST_GLB_SYS_IF_CONFIG;
typedef struct student
{
	//st_GLB_SYS_ETH_CONFIG   stEth[EN_SYS_IF_DEV_TOTAL];
        //char                     aucIfPubName[ETH_IF_NAME_LEN];
	ST_GLB_SYS_IF_CONFIG    stIfConfig;                 /* 网口驱动配置 */
}student;



void write_msg(const student* s,int len)
{

#define _BIN_WR

		FILE* fp;
		int i = 0;	
#ifdef _BIN_WR

		fp = fopen(SAVE_PATH,"rb+");
		if(NULL == fp)
		{
			fp = fopen(SAVE_PATH,"wb+");
		}
		fseek(fp,0,SEEK_END);
		while(i<len)
		{
			fwrite(s+i,sizeof(student),1,fp);
			i++;
		}
#else
		fp = fopen(SAVE_PATH,"r+");
		if(NULL == fp)
		{
			fp = fopen(SAVE_PATH,"w+");
		}
		fseek(fp,0,SEEK_END);
		while(i<len)
		{
			//fprintf(fp,"%-7s%-3d%-7s\n",(s+i)->stEth[0].aucIfName,(s+i)->id,(s+i)->addr);
		i++;
		}
#endif
		fclose(fp);
}

void read()
{
		FILE* fp;
		student s;
			
#ifdef _BIN_WR	
		fp =fopen(SAVE_PATH,"rb");
		if(NULL == fp)
		{
			perror("open fail");
			return;
		}
		while(1==fread(&s,sizeof(student),1,fp))
		{
			//printf("%s %d %s\n",s.name,s.id,s.addr);
		}	
#else
		fp = fopen(SAVE_PATH,"r");
		if(NULL == fp)
		{
			perror("open fail");	
		}
		while(!feof(fp))
		{
			//fscanf(fp,"%s %d %s\n",s.name,&s.id,s.addr);
			//printf("%s %d %s\n",s.name,s.id,s.addr);
																	}



#endif
		fclose(fp);

}



int main()
{

		student s;
		printf("\nsizeof(student)=%d\n",sizeof(student));
		memset(&s,0x0,sizeof(student));
		strcpy(s.stIfConfig.aucIfPubName,"eth0");
		write_msg(&s,1);
		read();
		return 0;
}
