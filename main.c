#include<stdio.h>         /*输入输出函数的头文件*/
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<windows.h>
#include<process.h>
#include<time.h>
#include<unistd.h>//用于unlink() 
#include<ctype.h>
#include <conio.h>
#define MAX_PASSWD_LEN 81 //最长密码长度 

int menu();              /*函数声明*/
int validuserid(char [],char[]);
int validadminid(char [],char[]);
int validuserpass(char [],char[]);
int validadminpass(char [],char[]);
int searchbuy(char []);
int userpersonal(char []);
int userlist(char []); //用户的个人订单管理 
int adminlist(char []);
int adminfly(char []);
int adminpersonal(char []);
void searchtime();
void searchlocation();
void searchnumber();
void searchflydate();
void salesfly();
void userordershow(char []);
void people(char []);
void money(char []);
void rate(char []);
void flightsearch(char []);
void addflight();
void init(); //初始化读入航班信息
void refreshhangban(); //随时更新航班信息; 
char *generatefilename();
char* strcpymiddle(char *,int,int); //字符串截取函数
int turntime(char *strtime); //时间准换函数，将标准时间格式转换成分钟数; 
int validpilot(char [],char [],char [],char [],char [],char []);
char *searchcompany(char []);
char *generatecompanyorders(char []);
char *generatecompanyinfo(char []);
char *generatefilename();
int datetimeshow();
int totaltimeshow();
int validname(char []);
int nobuylist(char []);
int nobuychoose(char *);
void showlist(FILE *);
void listdelete(char *);
void flybuy(char *userid);
int numexit(char [],FILE *);//判断所输入编号是否存在 
int idcheck(char *,char *);
int namecheck(char *,char *);
int timecheck(char *,char *);
int ticketcheck(char [],char);
void renewfile(char [],char,char []);
char *codechange(char *);
char *phonechange(char *);
char *mailchange(char *);
void inputPW(char *,int);//暗文密码函数
int checkfn(char []); //验证航班号格式是否正确 
int back2(int i,char id[][81],char code[][81],char temp1[][81],char temp2[][81],char mail[][81]);
int back3(int i,char id[][81],char code[][81],char temp1[][81],char temp2[][81],char phonenumber[][81],char mail[][81]);
 
int xx=0; //这个全局的变量用作产生临时文件的编号；
int m=0;

struct air
{
	char airnumber[10];
	char locationstart[20];
	char locationover[20];
	int flydate;
	char timestart[10];
	char timeover[20];
	char planetype[10];
	int fprice;
	int bprice;
	int eprice;
	int ontimepercent;
	char pilot1[20];
	char pilot2[20];
	int fspare;
	int bspare;
	int espare;
	int ticketsold;
	int totalprice;
} 
userorder[10000];

struct flight
{
	char flightnumber[1024];
	char flightstart[1024];
	char flightend[1024];
	char riqi[1024];
	char *starttime;
	char *endtime;
	char flightmodel[81];
	int toudengprice;
	int shangwuprice;
	int jingjiprice;
	int flightrate;
	char pilot1[81];
	char pilot2[81];
	int toudengzuo;
	int shangwuzuo;
	int jingjizuo;
};
 
int main()  /*主函数*/
{
    while(1)
    {
    	xx=0;
    	system("cls");
    	init();
    	if(menu()!=1)
          break;
    }
    return 0;
}

char *strcpymiddle(char *ch,int pos,int length)  //字符串截取函数的一个编写 
{  
    char *pch=ch;  //定义一个字符指针，指向传递进来的ch地址。  
    char *subch=(char*)calloc(sizeof(char),length+1);  //通过calloc来分配一个length长度的字符数组，返回的是字符指针。  
    int j; 
    pch=pch+pos;  //是pch指针指向pos位置。  
    for(j=0;j<length;j++)  
    {  
        subch[j]=*(pch++);  //循环遍历赋值数组。  
    }  
    subch[length]='\0';  //加上字符串结束符。  
    return subch;       //返回分配的字符数组地址。  
}

int turntime(char *strtime)
{
	char *timehh,*timemm; 
	int timehh_num,timemm_num; //这里统一化成分钟来处理
	int timenum;
	{
		timehh=strcpymiddle(strtime,0,2);
		timemm=strcpymiddle(strtime,3,2);
		timehh_num=atoi(timehh);
		timemm_num=atoi(timemm);
		timenum=timehh_num*60+timemm_num;
    }
    return timenum;
}

int back()  //返回上级菜单或退出系统选择函数 
{
	int a=1,opcode; 
	while(a) 
	{
		printf("\n返回上级菜单请输入1，退出系统请输入0\n");
		scanf("%d",&opcode);
		fflush(stdin);
		switch(opcode)
		{
			case 0:a=0;printf("\n感谢您的使用！");exit(1);break;//退出系统 
			case 1:a=0;return 1;break;//退出循环 返回1 
			default:
				printf("输入的操作码有误，请重新输入！\n");
				break; 					
		}
	} 
}

/****************************************************/
/*函数定义
 函数名称：menu
 功能描述 : 实现主菜单功能的循环选择。*/
 
int menu()
{
    char usercode[81];//相应用户正确的密码
    char admincode[81];//相应管理员的正确密码
    char adminid[81];
    char userpass[81];
    char adminpass[81];
    int opcode3;
    int i;
    char opcode1[81];
    printf("$---------------------------------$\n");
    printf("|                                 |\n");
    printf("|   **欢迎进入上路民航管理系统**  |\n");
    printf("|                                 |\n");
    printf("用户进入请按1，管理员进入请按2：");
    scanf("%s",opcode1);
	fflush(stdin);
    while (1)
    {
        if ((strcmp(opcode1,"1")!=0)&&(strcmp(opcode1,"2")!=0))
        {
            printf("输入错误，请重新输入!\n");
            fflush(stdin);  //清空输入缓存
            printf("用户进入请按1，管理员进入请按2:");
            scanf("%s",opcode1);
            fflush(stdin);
        }
        else break;
    }
    char userid[80];
    if (strcmp(opcode1,"1")==0)
    {
        printf("请输入用户ID(如果要返回最初菜单请按【CTRL+Z】):\n");
  		if(gets(userid) == NULL)
  		  return 1;
        fflush(stdin);
        while (validuserid(userid,usercode)==0)
        {
            printf("用户名输入错误，请重新输入:(如果要返回最初菜单请按【CTRL+Z】):\n");
            if(gets(userid) == NULL)
  		  		return 1;
            fflush(stdin);
        }
        printf("下面请输入密码：\n");
        inputPW(userpass,80);
		//userpass=GetPasswd();
		//gets(userpass);
		printf("\n");//帮助打一个回车 
        fflush(stdin);
        while (validuserpass(userpass,usercode)==0)
        {
            printf("密码错误，请重新输入：\n");
        	inputPW(userpass,80);
			printf("\n");
            fflush(stdin);
        }
        while(1)
        {
            printf("\n\n     1.      查询及购买\n");
            printf("     2.      个人信息修改管理\n");
            printf("     3.      订单管理\n");
            printf("     0.      退出菜单\n");
            printf("【CTRL+Z】.  返回初始菜单\n");
            
            int opcode2;
            printf("请输入操作码进行相应操作\n");
            if(scanf("%d",&opcode2) == EOF)
              return 1;
            if (opcode2==0)
                break;
            else if (opcode2==1)
            {
                if(searchbuy(userid)==1)
                {	
                	xx=1;
                    continue;
                }
                else
                    break;
            }
            else if(opcode2==2)
                userpersonal(userid);
            else if(opcode2==3)
            {
              if(userlist(userid)==1) 
		    	continue;
		      else
		        break;
            }
        }
    }
    else
    {
        printf("请输入管理员ID(如果要返回最初菜单请按【CTRL+Z】):\n");
        if(gets(adminid) == NULL)
  		  	return 1;
        fflush(stdin);
        while (validadminid(adminid,admincode)==0)
        {
            printf("管理员ID输入错误，请重新输入(如果要返回最初菜单请按【CTRL+Z】):\n");
            if(gets(adminid) == NULL)
  		  		return 1;
            fflush(stdin);
        }
        printf("下面请输入密码：\n");
        inputPW(adminpass,81);
		printf("\n");
        fflush(stdin);
        while (validadminpass(adminpass,admincode)==0)
        {
            printf("密码错误，请重新输入：\n");
            inputPW(adminpass,81);
            printf("\n");
            fflush(stdin);
        }
        char *flightcompany;
		flightcompany = searchcompany(adminid);
        while(1)
        {
            printf("\n\n     1.      订单管理\n");
            printf("     2.      航班管理\n");
            printf("     3.      个人信息管理\n");
            printf("     0.      退出程序\n");
            printf("【CTRL+Z】.  返回初始菜单\n");
            printf("请输入操作码：\n");
            if(scanf("%d",&opcode3) == EOF)
              return 1;
            if (opcode3==0) //选0退出程序 
                break;
            if (opcode3==1) //选1进入航班管理 
            {
                if (adminlist(flightcompany)==1) //返回值为1进入下一个循环 
                    continue;
                else
                    break; //返回值不为1退出循环 
            }
            if (opcode3==2) //选2进入个人信息管理 
            {
                if (adminfly(flightcompany)==1) //返回值为1进入下一个循环 
                    continue;
                else
                    break; //返回值不为1退出循环 
            }
            if (opcode3==3) adminpersonal(adminid); //选3修改个人信息 
        }
  	 }
  	 
  	return 0;
}
//初始化读入文件

void init()			//定义读取文件函数
{
	FILE *fp;
	FILE *tempfp;
	xx++;
	char *tempfilename;
	tempfilename=generatefilename();
	//puts(tempfilename);
	tempfp=fopen(tempfilename,"w+");
	
	if((fp=fopen("hangban.dat","r"))==NULL)
	{
		printf("打开文件失败! ");
		getchar();
		return;
	}
	
	int i=0;
	while(!feof(fp))
	{
		fscanf(fp,"%s %s %s %d %s %s %s %d %d %d %d %s %s %d %d %d %d %d",userorder[i].airnumber,\
																		  userorder[i].locationstart,\
																		  userorder[i].locationover,\
																		  &userorder[i].flydate,\
																		  userorder[i].timestart,\
																		  userorder[i].timeover,\
																		  userorder[i].planetype,\
																		  &userorder[i].fprice,\
																		  &userorder[i].bprice,\
																		  &userorder[i].eprice,\
																		  &userorder[i].ontimepercent,\
																		  userorder[i].pilot1,\
																		  userorder[i].pilot2,\
																		  &userorder[i].fspare,\
																		  &userorder[i].bspare,\
																		  &userorder[i].espare,\
																		  &userorder[i].ticketsold,\
																		  &userorder[i].totalprice);
		
		//fread(&userorder[i],sizeof(struct air),1,fp);		//逐块读取数据
		m++;  //计算存在航班数
		i++;		
	}
	
	m--;
	int j;
	for (j=0;j<m;j++)
      fprintf(tempfp,"%s %s %s %d %s %s %s %d %d %d %d %s %s %d %d %d %d %d\n",userorder[j].airnumber,\
	                                                                  userorder[j].locationstart,\
																	  userorder[j].locationover,\
																	  userorder[j].flydate,\
																	  userorder[j].timestart,\
																	  userorder[j].timeover,\
																	  userorder[j].planetype,\
																	  userorder[j].fprice,\
																	  userorder[j].bprice,\
																	  userorder[j].eprice,\
																	  userorder[j].ontimepercent,\
																	  userorder[j].pilot1,\
																	  userorder[j].pilot2,\
																	  userorder[j].fspare,\
																	  userorder[j].bspare,\
																	  userorder[j].espare,\
																	  userorder[j].ticketsold,\
																	  userorder[j].totalprice);
	fclose(fp);
	fclose(tempfp);
	return;
}

void refreshhangban()
{
	FILE *fp;
	fp=fopen("hangban.dat","w+");
	if (fp==NULL) //这里是覆盖原文件的操作，要十分谨慎; 
	  {
		printf("打开hangban.dat失败！");
		return;
	  }
	else
	{
	  rewind(fp);
	  int j;
	  for (j=0;j<m;j++)
	    fprintf(fp,"%s %s %s %d %s %s %s %d %d %d %d %s %s %d %d %d %d %d\n",userorder[j].airnumber,\
	                                                                  userorder[j].locationstart,\
																	  userorder[j].locationover,\
																	  userorder[j].flydate,\
																	  userorder[j].timestart,\
																	  userorder[j].timeover,\
																	  userorder[j].planetype,\
																	  userorder[j].fprice,\
																	  userorder[j].bprice,\
																	  userorder[j].eprice,\
																	  userorder[j].ontimepercent,\
																	  userorder[j].pilot1,\
																	  userorder[j].pilot2,\
																	  userorder[j].fspare,\
																	  userorder[j].bspare,\
																	  userorder[j].espare,\
																	  userorder[j].ticketsold,\
																	  userorder[j].totalprice);
	  fclose(fp);	
	}
}

void inputPW(char *s,int len)        //自己写的密码输入的函数
{
	int i;
    fflush(stdin);               
    for(i=0; ;i++)
    {
      	s[i]=getch();
        if(s[i]==13)                  //输入结束 不能用=='\n'来判断!!
        	break;                    //因为对于回车来说getchar()='\n'=10;而getch()=13 !='\n' 这个要知道!  
        if(s[i]==8 && i>0)             //如果用户按退格键 并且要有格可退时候
        {
            printf("\b \b");           //显示退一格
            i=i-2;                          //输入数据退2(因为for循环体会加1 所以实际就是退了1)
         	continue;
        }
    	if(i==len) 
    	{
			i--; 
			continue;
		}
    	if ((i<=0)&&(s[i]==8)) 
			i--;
		else printf("*");
    }
    s[i]='\0';                  //末尾补\0 所以该密码实际有效长度为i-1;定义有效长为len 实际定义的串长为len+1
}

//下面的三个函数为修改信息的函数 

char *codechange(char *truecode)//传递的参数为文件中找到的正确原密码 
{
	static char oricode[81],newcode[81],finalcode[81];
	int flag2=1,flag3=0,flag4=0,len,xxx;
	printf("请输入原密码:");
	inputPW(oricode,80);
    printf("\n");
    fflush(stdin);
    while(1)//判断原密码是否正确
    {
    	if(strcmp(oricode,truecode)!=0)
        {
            printf("密码输入错误，请输入正确原密码： ");
            scanf("%s",oricode);
        }
            else
                break;
    }
    printf("\n请输入新密码(密码长度为6到10位，由字母和数字组成）: ");
	inputPW(newcode,80);
	printf("\n"); 
	while(1)//判断修改的密码是否符合要求
	{
		while(1)
		{
			flag2=1;
			len=strlen(newcode);
            if(len>10||len<6)
			{
				flag2=0;
				break;
			}
			for(xxx=0;xxx<len;xxx++)
			{ 
				if(isdigit(newcode[xxx])!=0)
					flag3++;
				else if(isalpha(newcode[xxx])!=0)
					flag4++;
				else
				{
					flag2=0;
					break;
				}
			}
			if(flag3==0||flag4==0)
			{
				flag2=0;
				break;
			}
			break;
		}
		if(flag2==0)
		{
			printf("\n密码格式不符合要求，请输入长度为6到10位，由字母数字组成的密码： ");
			inputPW(newcode,80);
			printf("\n"); 
		}
		else
		{
			strcpy(finalcode,newcode);
			printf("密码修改成功\n");
			break;
    	}
    }
    return finalcode;
} 

char *phonechange(char *turephone)//传递的参数为文件中找到的正确原手机号 
{
	static char oriphone[81],newphone[81],finalphone[81];
	int flag2=1,flag3=0,flag4=0,len,xxx;
	printf("请输入原手机号: ");
    scanf("%s",oriphone);
    while(1)//判断原手机号是否正确
    {
        if(strcmp(oriphone,turephone)!=0)
        {
            printf("原手机号输入错误，请输入正确原手机号： ");
            scanf("%s",oriphone);
        }
        else
            break;
    }
    printf("\n请输入新手机号: ");
    scanf("%s",newphone);
    while(1)//判断修改的新手机号是否符合要求
    {
        while(1)
        {
            flag2=1;
			len=strlen(newphone);
            for(xxx=0;xxx<len;xxx++)
            {
                if(isdigit(newphone[xxx])==0)
                {flag2=0;
                    break;}
            }
            if(strlen(newphone)!=11)
            {
                flag2=0;
                break;
            }
            break;
        }
        if(flag2==0)
        {
            printf("\n手机号格式错误，请输入11位的正确手机号： ");
            scanf("%s",newphone);
            fflush(stdin);
        }
        else
        {   
	   		strcpy(finalphone,newphone);
            printf("手机号修改成功\n");
            break;
        }
    }
    return finalphone ; 
} 

char *mailchange(char *turemail)//传递的参数为文件中找到的正确原邮箱 
{
	static char orimail[81],newmail[81],finalmail[81];
	int flag2=1,flag3=0,flag4=0,len,xxx;
        printf("请输入原邮箱: ");
        scanf("%s",orimail);
        while(1)//判断原邮箱是否正确
        {
            if(strcmp(orimail,turemail)!=0)
            {
                printf("原邮箱输入错误，请输入正确原邮箱： ");
                scanf("%s",orimail);
            }
            else
                break;
        }
        printf("\n请输入新邮箱: ");
        scanf("%s",newmail);
        while(1)//判断新邮箱格式是否符合要求
        {
                flag2=0;
                int a,flaga=0;
				len=strlen(newmail);
                for(xxx=0;xxx<(len-1);xxx++)//计数@ 
                {
                    if(newmail[xxx]=='@')
                        flag2++;//如果flag2为1则通过 0或其他就不合法	
                }
                for(xxx=0;xxx<(len-1);xxx++)
                {
                    if(newmail[xxx]=='@')
                        break;//定位第一个@的位置为a 
                }
                a=xxx;
                for(xxx=a;xxx<(len-1);xxx++)//验证@后是否有点 
                {
                	if(newmail[xxx]=='.')
	                	flaga=1;
                }
                for(xxx=0;xxx<a;xxx++)//验证@前是否有. 
                {
                	if(newmail[xxx]=='.')
	                	flaga=0;
                }

            if(flag2!=1||flaga!=1)
            {
                printf("\n邮箱格式错误，请输入正确邮箱： ");
                scanf("%s",newmail);
                fflush(stdin);
            }
            else
            {	
				strcpy(finalmail,newmail);
                printf("邮箱修改成功\n");              
                break;
            }
        }
        return finalmail;
}

//验证输入的函数模块
int validuserid(char userid[],char usercode[])
{
    char id[21];char code[81]; char temp1[81];char temp2[81];char temp3[81];char temp4[81];
    int flag2=0;
    FILE*inFile;
    inFile=fopen("用户信息.txt","r");
    if(inFile==NULL)
    {
        printf("文件无法成功打开\n");
        printf("请联系管理员");
        exit(1);
    }
    while((strcmp(id,userid)!=0)&&(fscanf(inFile,"%s%s%s%s%s%s",id,code,temp1,temp2,temp3,temp4)!=EOF))
    {
            if(strcmp(id,userid)==0)
            {
                printf("用户名验证通过\n");
                flag2=1;}
            else;
    }
    strcpy(usercode,code);
    fclose(inFile);
    return flag2;
}

int validadminid(char adminid[],char admincode[])
{
    char id[21];char code[81]; char temp1[81];char temp2[81];char temp3[81];
    int flag2=0;
    FILE*outFile;
    outFile=fopen("管理员信息.txt","r");
    if(outFile==NULL)
    {
        printf("文件无法成功打开\n");
        exit(1);
    }
    while((strcmp(id,adminid)!=0)&&(fscanf(outFile,"%s%s%s%s%s",id,code,temp1,temp2,temp3)!=EOF))
    {
        if(strcmp(id,adminid)==0)
        {
            printf("管理员用户名验证通过\n");
            flag2=1;}
        else;
    }
    strcpy(admincode,code);
    fclose(outFile);
    return flag2;
}

int validuserpass(char userpass[],char usercode[])
{
    int flag2=0;
    if(strcmp(usercode,userpass)==0)
    {
        printf("密码验证成功!\n");
        flag2=1;
    }
    return flag2;
}
int validadminpass(char adminpass[],char admincode[])
{
    int flag2=0;
    if(strcmp(admincode,adminpass)==0)
    {
        printf("管理员密码验证成功");
        flag2=1;
    }
    return flag2;
}

char *generatefilename()
{
	static char str1[81];
	strcpy(str1,"temp");
	static char str3[81];
	strcpy(str3,".txt"); 
	char str2[81];
	itoa(xx,str2,10);
	
	strcat(str1,str2);
    strcat(str1,str3);
	return str1;
}

void searchnumber() //按照航班号检索及过滤 
{
    char *tempfilename_old;
	tempfilename_old=generatefilename();
	FILE *fpold;
	fpold=fopen(tempfilename_old,"r");
	
	xx++;
	char *tempfilename_new;
	tempfilename_new=generatefilename();
	FILE *fpnew;
	fpnew=fopen(tempfilename_new,"w+");
	
	if (fpold==NULL){printf("旧文件打开失败！\n");getchar();return;} 
	if (fpnew==NULL){printf("新文件打开失败！\n");getchar();return;}
	struct air tempsearchnumber[10000];
	int i=0;
	while(!feof(fpold))
	{
		fscanf(fpold,"%s %s %s %d %s %s %s %d %d %d %d %s %s %d %d %d %d %d",tempsearchnumber[i].airnumber,\
																	tempsearchnumber[i].locationstart,\
																	tempsearchnumber[i].locationover,\
																	&tempsearchnumber[i].flydate,\
																	tempsearchnumber[i].timestart,\
																	tempsearchnumber[i].timeover,\
																	tempsearchnumber[i].planetype,\
																	&tempsearchnumber[i].fprice,\
																	&tempsearchnumber[i].bprice,\
																	&tempsearchnumber[i].eprice,\
																	&tempsearchnumber[i].ontimepercent,\
																	tempsearchnumber[i].pilot1,\
																	tempsearchnumber[i].pilot2,\
																	&tempsearchnumber[i].fspare,\
																	&tempsearchnumber[i].bspare,\
																	&tempsearchnumber[i].espare,\
																	&tempsearchnumber[i].ticketsold,\
																	&tempsearchnumber[i].totalprice);
											
		
		i++;		//计算存在航班数
	}
	
	char strairnumber[255];
	printf("请输入航班号:\n");
	fflush(stdin);
	scanf("%s",strairnumber);
	fflush(stdin);
	
	int j;
	printf("正在检索\n");
	sleep(1.5);
	printf("航班号   起飞地     降落地   起飞日期  起飞时间  降落时间   机型  头等舱票价 商务舱票价 经济舱票价 准点率\n");
	for (j=0;j<i-1;j++)
	  if (strcmp(strairnumber,tempsearchnumber[j].airnumber)==0)
	  {
	  	  fprintf(fpnew,"%s %s %s %d %s %s %s %d %d %d %d %s %s %d %d %d %d %d\n",tempsearchnumber[j].airnumber,\
																	tempsearchnumber[j].locationstart,\
																	tempsearchnumber[j].locationover,\
																	tempsearchnumber[j].flydate,\
																	tempsearchnumber[j].timestart,\
																	tempsearchnumber[j].timeover,\
																	tempsearchnumber[j].planetype,\
																	tempsearchnumber[j].fprice,\
																	tempsearchnumber[j].bprice,\
																	tempsearchnumber[j].eprice,\
																	tempsearchnumber[j].ontimepercent,\
																	tempsearchnumber[j].pilot1,\
																	tempsearchnumber[j].pilot2,\
																	tempsearchnumber[j].fspare,\
																	tempsearchnumber[j].bspare,\
																	tempsearchnumber[j].espare,\
																	tempsearchnumber[j].ticketsold,\
																	tempsearchnumber[j].totalprice);
		   													
		   printf("%-9s%-11s%-9s%-10d%-10s%-11s%-6s%-11d%-11d%-11d%d%%\n",tempsearchnumber[j].airnumber,\
																	tempsearchnumber[j].locationstart,\
																	tempsearchnumber[j].locationover,\
																	tempsearchnumber[j].flydate,\
																	tempsearchnumber[j].timestart,\
																	tempsearchnumber[j].timeover,\
																	tempsearchnumber[j].planetype,\
																	tempsearchnumber[j].fprice,\
																	tempsearchnumber[j].bprice,\
																	tempsearchnumber[j].eprice,\
																	tempsearchnumber[j].ontimepercent);
	  }
    
	//if (nofound==1) printf("未找到符合要求的航班信息!\n"); 
	fclose(fpold);
	fclose(fpnew);
	return;
    printf("按照航班号检索完毕！\n");
}

void searchtime() //按照时间检索及过滤 
{
    char *tempfilename_old;
	tempfilename_old=generatefilename();
	//puts(tempfilename_old);
	FILE *fpold;
	fpold=fopen(tempfilename_old,"r");
	
	xx++;
	char *tempfilename_new;
	tempfilename_new=generatefilename();
	FILE *fpnew;
	fpnew=fopen(tempfilename_new,"w+");
	
		struct air tempsearchtime[10000];
	int i=0;
	while(!feof(fpold))
	{
		fscanf(fpold,"%s %s %s %d %s %s %s %d %d %d %d %s %s %d %d %d %d %d",tempsearchtime[i].airnumber,\
																	tempsearchtime[i].locationstart,\
																	tempsearchtime[i].locationover,\
																	&tempsearchtime[i].flydate,\
																	tempsearchtime[i].timestart,\
																	tempsearchtime[i].timeover,\
																	tempsearchtime[i].planetype,\
																	&tempsearchtime[i].fprice,\
																	&tempsearchtime[i].bprice,\
																	&tempsearchtime[i].eprice,\
																	&tempsearchtime[i].ontimepercent,\
																	tempsearchtime[i].pilot1,\
																	tempsearchtime[i].pilot2,\
																	&tempsearchtime[i].fspare,\
																	&tempsearchtime[i].bspare,\
																	&tempsearchtime[i].espare,\
																	&tempsearchtime[i].ticketsold,\
																	&tempsearchtime[i].totalprice);
		
		i++;		//计算存在航班数
	}

	printf("按起飞时间段查询请按1，按降落时间段查询请按2\n");
	int opcode;
	printf("请输入操作码\n");
	scanf("%d",&opcode);
	char strtime[81];
	int j,timestartcmp,timeovercmp;
	int temptime;
	
	if (opcode==1)
	{
		printf("请按照以下格式输入时间段hh:mm-hh:mm\n");
		fflush(stdin);
		gets(strtime);
		fflush(stdin);
		timestartcmp=turntime(strcpymiddle(strtime,0,5));
		timeovercmp=turntime(strcpymiddle(strtime,6,5));
		printf("正在检索\n");
		sleep(1.5);
		printf("航班号   起飞地     降落地   起飞日期  起飞时间  降落时间   机型  头等舱票价 商务舱票价 经济舱票价 准点率\n");
		for (j=0;j<j-1;j++)
		{
			temptime=turntime(tempsearchtime[j].timestart);
			
			if ((temptime>=timestartcmp)&&(temptime<=timeovercmp))
			{
				fprintf(fpnew,"%s %s %s %d %s %s %s %d %d %d %d %s %s %d %d %d %d %d\n",tempsearchtime[j].airnumber,\
																	tempsearchtime[j].locationstart,\
																	tempsearchtime[j].locationover,\
																	tempsearchtime[j].flydate,\
																	tempsearchtime[j].timestart,\
																	tempsearchtime[j].timeover,\
																	tempsearchtime[j].planetype,\
																	tempsearchtime[j].fprice,\
																	tempsearchtime[j].bprice,\
																	tempsearchtime[j].eprice,\
																	tempsearchtime[j].ontimepercent,\
																	tempsearchtime[j].pilot1,\
																	tempsearchtime[j].pilot2,\
																	tempsearchtime[j].fspare,\
																	tempsearchtime[j].bspare,\
																	tempsearchtime[j].espare,\
																	tempsearchtime[j].ticketsold,\
																	tempsearchtime[j].totalprice);
				printf("%-9s%-11s%-9s%-10d%-10s%-11s%-6s%-11d%-11d%-11d%d%%\n",tempsearchtime[j].airnumber,\
																	tempsearchtime[j].locationstart,\
																	tempsearchtime[j].locationover,\
																	tempsearchtime[j].flydate,\
																	tempsearchtime[j].timestart,\
																	tempsearchtime[j].timeover,\
																	tempsearchtime[j].planetype,\
																	tempsearchtime[j].fprice,\
																	tempsearchtime[j].bprice,\
																	tempsearchtime[j].eprice,\
																	tempsearchtime[j].ontimepercent);
																	
			}
		}
		 
	}
	else if (opcode==2)
	{
		printf("请按照以下格式输入时间段hh:mm-hh:mm\n");
		fflush(stdin); 
		gets(strtime);
		fflush(stdin);
		timestartcmp=turntime(strcpymiddle(strtime,0,5));
		timeovercmp=turntime(strcpymiddle(strtime,6,5));
		printf("正在检索\n");
		sleep(1.5);
		printf("航班号   起飞地     降落地   起飞日期  起飞时间  降落时间   机型  头等舱票价 商务舱票价 经济舱票价 准点率\n");
		for (j=0;j<i-1;j++)
		{
			temptime=turntime(tempsearchtime[j].timeover);
			
			if ((temptime>=timestartcmp)&&(temptime<=timeovercmp))
			{
					fprintf(fpnew,"%s %s %s %d %s %s %s %d %d %d %d %s %s %d %d %d %d %d\n",tempsearchtime[j].airnumber,\
																	tempsearchtime[j].locationstart,\
																	tempsearchtime[j].locationover,\
																	tempsearchtime[j].flydate,\
																	tempsearchtime[j].timestart,\
																	tempsearchtime[j].timeover,\
																	tempsearchtime[j].planetype,\
																	tempsearchtime[j].fprice,\
																	tempsearchtime[j].bprice,\
																	tempsearchtime[j].eprice,\
																	tempsearchtime[j].ontimepercent,\
																	tempsearchtime[j].pilot1,\
																	tempsearchtime[j].pilot2,\
																	tempsearchtime[j].fspare,\
																	tempsearchtime[j].bspare,\
																	tempsearchtime[j].espare,\
																	tempsearchtime[j].ticketsold,\
																	tempsearchtime[j].totalprice);
				printf("%-9s%-11s%-9s%-10d%-10s%-11s%-6s%-11d%-11d%-11d%d%%\n",tempsearchtime[j].airnumber,\
																	tempsearchtime[j].locationstart,\
																	tempsearchtime[j].locationover,\
																	tempsearchtime[j].flydate,\
																	tempsearchtime[j].timestart,\
																	tempsearchtime[j].timeover,\
																	tempsearchtime[j].planetype,\
																	tempsearchtime[j].fprice,\
																	tempsearchtime[j].bprice,\
																	tempsearchtime[j].eprice,\
																	tempsearchtime[j].ontimepercent);
																	
			}	
		}
		 	
	}
	
	fclose(fpold);
	fclose(fpnew);
    printf("按照时间检索完毕!\n");
    
}

void searchlocation() //按照地点检索及过滤 
{
    char *tempfilename_old;
	tempfilename_old=generatefilename();
	//puts(tempfilename_old);
	//puts(tempfilename_old);
	FILE *fpold;
	fpold=fopen(tempfilename_old,"r");
	
	xx++;
	char *tempfilename_new;
	tempfilename_new=generatefilename();
	FILE *fpnew;
	fpnew=fopen(tempfilename_new,"w+");
	
	
	if (fpold==NULL)
	{
		printf("旧文件打开失败！\n");
		getchar();
		return; 
	} 
	
	if (fpnew==NULL)
	{
		printf("新文件打开失败！\n");
		getchar();
		return; 
	}
	
	struct air tempsearchlocation[10000];
	int i=0;
	while(!feof(fpold))
	{
		fscanf(fpold,"%s %s %s %d %s %s %s %d %d %d %d %s %s %d %d %d %d %d",tempsearchlocation[i].airnumber,\
																	tempsearchlocation[i].locationstart,\
																	tempsearchlocation[i].locationover,\
																	&tempsearchlocation[i].flydate,\
																	tempsearchlocation[i].timestart,\
																	tempsearchlocation[i].timeover,\
																	tempsearchlocation[i].planetype,\
																	&tempsearchlocation[i].fprice,\
																	&tempsearchlocation[i].bprice,\
																	&tempsearchlocation[i].eprice,\
																	&tempsearchlocation[i].ontimepercent,\
																	tempsearchlocation[i].pilot1,\
																	tempsearchlocation[i].pilot2,\
																	&tempsearchlocation[i].fspare,\
																	&tempsearchlocation[i].bspare,\
																	&tempsearchlocation[i].espare,\
																	&tempsearchlocation[i].ticketsold,\
																	&tempsearchlocation[i].totalprice);
		
		i++;		//计算存在航班数
	}
	
	printf("按照起飞地查询请按1，按照降落地查询请按2\n");
	int opcode;
	printf("请输入操作码\n");
	scanf("%d",&opcode);
	char strlocation[81];
	if (opcode==1)
	{
		printf("请输入起飞地:\n");
		scanf("%s",strlocation);fflush(stdin);
		fflush(stdin);
		int j;
		printf("航班号   起飞地     降落地   起飞日期  起飞时间  降落时间   机型  头等舱票价 商务舱票价 经济舱票价 准点率\n");
		for (j=0;j<i-1;j++)
		{
			if (strcmp(strlocation,tempsearchlocation[j].locationstart)==0)
			{
				fprintf(fpnew,"%s %s %s %d %s %s %s %d %d %d %d %s %s %d %d %d %d %d\n",tempsearchlocation[j].airnumber,\
																	tempsearchlocation[j].locationstart,\
																	tempsearchlocation[j].locationover,\
																	tempsearchlocation[j].flydate,\
																	tempsearchlocation[j].timestart,\
																	tempsearchlocation[j].timeover,\
																	tempsearchlocation[j].planetype,\
																	tempsearchlocation[j].fprice,\
																	tempsearchlocation[j].bprice,\
																	tempsearchlocation[j].eprice,\
																	tempsearchlocation[j].ontimepercent,\
																	tempsearchlocation[j].pilot1,\
																	tempsearchlocation[j].pilot2,\
																	tempsearchlocation[j].fspare,\
																	tempsearchlocation[j].bspare,\
																	tempsearchlocation[j].espare,\
																	tempsearchlocation[j].ticketsold,\
																	tempsearchlocation[j].totalprice);
				printf("%-9s%-11s%-9s%-10d%-10s%-11s%-6s%-11d%-11d%-11d%d%%\n",tempsearchlocation[j].airnumber,\
																	tempsearchlocation[j].locationstart,\
																	tempsearchlocation[j].locationover,\
																	tempsearchlocation[j].flydate,\
																	tempsearchlocation[j].timestart,\
																	tempsearchlocation[j].timeover,\
																	tempsearchlocation[j].planetype,\
																	tempsearchlocation[j].fprice,\
																	tempsearchlocation[j].bprice,\
																	tempsearchlocation[j].eprice,\
																	tempsearchlocation[j].ontimepercent);
																
			}
		} 
	}
	else if (opcode==2)
	{
		printf("请输入降落地:\n");
		scanf("%s",strlocation);fflush(stdin);
		int j;
		printf("正在检索\n");
	    sleep(1.5);
		printf("航班号   起飞地     降落地   起飞日期  起飞时间  降落时间   机型  头等舱票价 商务舱票价 经济舱票价 准点率\n");
		for (j=0;j<i-1;j++)
		{
			if (strcmp(strlocation,tempsearchlocation[j].locationover)==0)
			{
				fprintf(fpnew,"%s %s %s %d %s %s %s %d %d %d %d %s %s %d %d %d %d %d\n",tempsearchlocation[j].airnumber,\
																	tempsearchlocation[j].locationstart,\
																	tempsearchlocation[j].locationover,\
																	tempsearchlocation[j].flydate,\
																	tempsearchlocation[j].timestart,\
																	tempsearchlocation[j].timeover,\
																	tempsearchlocation[j].planetype,\
																	tempsearchlocation[j].fprice,\
																	tempsearchlocation[j].bprice,\
																	tempsearchlocation[j].eprice,\
																	tempsearchlocation[j].ontimepercent,\
																	tempsearchlocation[j].pilot1,\
																	tempsearchlocation[j].pilot2,\
																	tempsearchlocation[j].fspare,\
																	tempsearchlocation[j].bspare,\
																	tempsearchlocation[j].espare,\
																	tempsearchlocation[j].ticketsold,\
																	tempsearchlocation[j].totalprice);
				printf("%-9s%-11s%-9s%-10d%-10s%-11s%-6s%-11d%-11d%-11d%d%%\n",tempsearchlocation[j].airnumber,\
																	tempsearchlocation[j].locationstart,\
																	tempsearchlocation[j].locationover,\
																	tempsearchlocation[j].flydate,\
																	tempsearchlocation[j].timestart,\
																	tempsearchlocation[j].timeover,\
																	tempsearchlocation[j].planetype,\
																	tempsearchlocation[j].fprice,\
																	tempsearchlocation[j].bprice,\
																	tempsearchlocation[j].eprice,\
																	tempsearchlocation[j].ontimepercent);
																
			}
		}
	}
	
	fclose(fpold);
	fclose(fpnew);
    printf("按照地点检索完毕！\n");
}

void searchflydate() //按照起飞日期检索及过滤 
{
	char *tempfilename_old;
	tempfilename_old=generatefilename();

	FILE *fpold;
	fpold=fopen(tempfilename_old,"r");
	//puts(tempfilename_old);
	xx++;
	char *tempfilename_new;
	tempfilename_new=generatefilename();
	FILE *fpnew;
	fpnew=fopen(tempfilename_new,"w+");
	//puts(tempfilename_new);
	
	if (fpold==NULL)
	{
		printf("旧文件打开失败！\n");
		getchar();
		return; 
	} 
	
	if (fpnew==NULL)
	{
		printf("新文件打开失败！\n");
		getchar();
		return; 
	}
	
	struct air tempsearchdate[10000];
	int i=0;
	while(!feof(fpold))
	{
		fscanf(fpold,"%s %s %s %d %s %s %s %d %d %d %d %s %s %d %d %d %d %d",tempsearchdate[i].airnumber,\
																	tempsearchdate[i].locationstart,\
																	tempsearchdate[i].locationover,\
																	&tempsearchdate[i].flydate,\
																	tempsearchdate[i].timestart,\
																	tempsearchdate[i].timeover,\
																	tempsearchdate[i].planetype,\
																	&tempsearchdate[i].fprice,\
																	&tempsearchdate[i].bprice,\
																	&tempsearchdate[i].eprice,\
																	&tempsearchdate[i].ontimepercent,\
																	tempsearchdate[i].pilot1,\
																	tempsearchdate[i].pilot2,\
																	&tempsearchdate[i].fspare,\
																	&tempsearchdate[i].bspare,\
																	&tempsearchdate[i].espare,\
																	&tempsearchdate[i].ticketsold,\
																	&tempsearchdate[i].totalprice);
		
		i++;		//计算存在航班数
	}
	
	printf("请输入需要的飞机的起飞的日期:(例如: 19970429)\n");
	int tempdate;
	scanf("%d",&tempdate);
	int j;
	printf("正在检索\n");
	sleep(1.5);
	printf("航班号   起飞地     降落地   起飞日期  起飞时间  降落时间   机型  头等舱票价 商务舱票价 经济舱票价 准点率\n");
	for (j=0;j<i-1;j++)
	{
	  if (tempdate==tempsearchdate[j].flydate)
	  {
	    fprintf(fpnew,"%s %s %s %d %s %s %s %d %d %d %d %s %s %d %d %d %d %d\n",tempsearchdate[j].airnumber,\
																	tempsearchdate[j].locationstart,\
																	tempsearchdate[j].locationover,\
																	tempsearchdate[j].flydate,\
																	tempsearchdate[j].timestart,\
																	tempsearchdate[j].timeover,\
																	tempsearchdate[j].planetype,\
																	tempsearchdate[j].fprice,\
																	tempsearchdate[j].bprice,\
																	tempsearchdate[j].eprice,\
																	tempsearchdate[j].ontimepercent,\
																	tempsearchdate[j].pilot1,\
																	tempsearchdate[j].pilot2,\
																	tempsearchdate[j].fspare,\
																	tempsearchdate[j].bspare,\
																	tempsearchdate[j].espare,\
																	tempsearchdate[j].ticketsold,\
																	tempsearchdate[j].totalprice);
				printf("%-9s%-11s%-9s%-10d%-10s%-11s%-6s%-11d%-11d%-11d%d%%\n",tempsearchdate[j].airnumber,\
																	tempsearchdate[j].locationstart,\
																	tempsearchdate[j].locationover,\
																	tempsearchdate[j].flydate,\
																	tempsearchdate[j].timestart,\
																	tempsearchdate[j].timeover,\
																	tempsearchdate[j].planetype,\
																	tempsearchdate[j].fprice,\
																	tempsearchdate[j].bprice,\
																	tempsearchdate[j].eprice,\
																	tempsearchdate[j].ontimepercent);
																
			}
		} 
		
	fclose(fpold);
	fclose(fpnew);
}

void sorttime() //按照时间排序 
{
	printf("正在检索\n");
	sleep(1.5);
    char *tempfilename_old;
	tempfilename_old=generatefilename();
	//puts(tempfilename_old);
	FILE *fpold;
	fpold=fopen(tempfilename_old,"r");
	
	xx++;
	char *tempfilename_new;
	tempfilename_new=generatefilename();
	FILE *fpnew;
	fpnew=fopen(tempfilename_new,"w+");
	
	if (fpold==NULL)
	{
		printf("旧文件打开失败！\n");
		getchar();
		return; 
	} 
	
	if (fpnew==NULL)
	{
		printf("新文件打开失败！\n");
		getchar();
		return; 
	}
	struct air tempsorttime[10000],tempswap;
	
	//读入最新的临时文件
	
	int i=0;
	while(!feof(fpold))
	{
		fscanf(fpold,"%s %s %s %d %s %s %s %d %d %d %d %s %s %d %d %d %d %d",tempsorttime[i].airnumber,\
																	tempsorttime[i].locationstart,\
																	tempsorttime[i].locationover,\
																	&tempsorttime[i].flydate,\
																	tempsorttime[i].timestart,\
																	tempsorttime[i].timeover,\
																	tempsorttime[i].planetype,\
																	&tempsorttime[i].fprice,\
																	&tempsorttime[i].bprice,\
																	&tempsorttime[i].eprice,\
																	&tempsorttime[i].ontimepercent,\
																	tempsorttime[i].pilot1,\
																	tempsorttime[i].pilot2,\
																	&tempsorttime[i].fspare,\
																	&tempsorttime[i].bspare,\
																	&tempsorttime[i].espare,\
																	&tempsorttime[i].ticketsold,\
																	&tempsorttime[i].totalprice);
		
		i++;		//计算存在航班数
	}
	int j,k;
	
	for (j=0;j<i-2;j++)
	  for (k=j+1;k<i-1;k++)
      {
      	if (turntime((tempsorttime[j].timestart))>turntime((tempsorttime[k].timestart)))
      	{		  
      		tempswap=tempsorttime[j];
      		tempsorttime[j]=tempsorttime[k];
      		tempsorttime[k]=tempswap;
		}
	  }
	printf("航班号   起飞地     降落地   起飞日期  起飞时间  降落时间   机型  头等舱票价 商务舱票价 经济舱票价 准点率\n");
	for (j=0;j<i-1;j++)
	{
		fprintf(fpnew,"%s %s %s %d %s %s %s %d %d %d %d %s %s %d %d %d %d %d\n",tempsorttime[j].airnumber,\
	                                                                  tempsorttime[j].locationstart,\
																	  tempsorttime[j].locationover,\
																	  tempsorttime[j].flydate,\
																	  tempsorttime[j].timestart,\
																	  tempsorttime[j].timeover,\
																	  tempsorttime[j].planetype,\
																	  tempsorttime[j].fprice,\
																	  tempsorttime[j].bprice,\
																	  tempsorttime[j].eprice,\
																	  tempsorttime[j].ontimepercent,\
																	  tempsorttime[j].pilot1,\
																	  tempsorttime[j].pilot2,\
																	  tempsorttime[j].fspare,\
																	  tempsorttime[j].bspare,\
																	  tempsorttime[j].espare,\
																	  tempsorttime[j].ticketsold,\
																	  tempsorttime[j].totalprice);
		printf("%-9s%-11s%-9s%-10d%-10s%-11s%-6s%-11d%-11d%-11d%d%%\n",tempsorttime[j].airnumber,\
	                                                                  tempsorttime[j].locationstart,\
																	  tempsorttime[j].locationover,\
																	  tempsorttime[j].flydate,\
																	  tempsorttime[j].timestart,\
																	  tempsorttime[j].timeover,\
																	  tempsorttime[j].planetype,\
																	  tempsorttime[j].fprice,\
																	  tempsorttime[j].bprice,\
																	  tempsorttime[j].eprice,\
																	  tempsorttime[j].ontimepercent);
																	 
	}
	
	fclose(fpold);
	fclose(fpnew);
	printf("排序完毕！\n");
}

void sortprice() //按照价格排序 
{
	printf("正在检索\n");
	sleep(1.5);
    char *tempfilename_old;
	tempfilename_old=generatefilename();
	//puts(tempfilename_old);
	FILE *fpold;
	fpold=fopen(tempfilename_old,"r");
	
	xx++;
	char *tempfilename_new;
	tempfilename_new=generatefilename();
	FILE *fpnew;
	fpnew=fopen(tempfilename_new,"w+");
	
	if (fpold==NULL)
	{
		printf("旧文件打开失败！\n");
		getchar();
		return; 
	} 
	
	if (fpnew==NULL)
	{
		printf("新文件打开失败！\n");
		getchar();
		return; 
	}
	struct air tempprice[10000],tempswap;
	
	//读入最新的临时文件
	
	int i=0;
	while(!feof(fpold))
	{
		fscanf(fpold,"%s %s %s %d %s %s %s %d %d %d %d %s %s %d %d %d %d %d",tempprice[i].airnumber,\
																	tempprice[i].locationstart,\
																	tempprice[i].locationover,\
																	&tempprice[i].flydate,\
																	tempprice[i].timestart,\
																	tempprice[i].timeover,\
																	tempprice[i].planetype,\
																	&tempprice[i].fprice,\
																	&tempprice[i].bprice,\
																	&tempprice[i].eprice,\
																	&tempprice[i].ontimepercent,\
																	tempprice[i].pilot1,\
																	tempprice[i].pilot2,\
																	&tempprice[i].fspare,\
																	&tempprice[i].bspare,\
																	&tempprice[i].espare,\
																	&tempprice[i].ticketsold,\
																	&tempprice[i].totalprice);
		
		i++;		//计算存在航班数
	}
	int j,k;
	
	for (j=0;j<i-2;j++)
	  for (k=j+1;k<i-1;k++)
      {
      	if ((tempprice[j].eprice)>(tempprice[k].eprice))
      	{		  
      		tempswap=tempprice[j];
      		tempprice[j]=tempprice[k];
      		tempprice[k]=tempswap;
		}
	  }
	printf("航班号   起飞地     降落地   起飞日期  起飞时间  降落时间   机型  头等舱票价 商务舱票价 经济舱票价 准点率\n");
	for (j=0;j<i-1;j++)
	{
		fprintf(fpnew,"%s %s %s %d %s %s %s %d %d %d %d %s %s %d %d %d %d %d\n",tempprice[j].airnumber,\
																	tempprice[j].locationstart,\
																	tempprice[j].locationover,\
																	tempprice[j].flydate,\
																	tempprice[j].timestart,\
																	tempprice[j].timeover,\
																	tempprice[j].planetype,\
																	tempprice[j].fprice,\
																	tempprice[j].bprice,\
																	tempprice[j].eprice,\
																	tempprice[j].ontimepercent,\
																	tempprice[j].pilot1,\
																	tempprice[j].pilot2,\
																	tempprice[j].fspare,\
																	tempprice[j].bspare,\
																	tempprice[j].espare,\
																	tempprice[j].ticketsold,\
																	tempprice[j].totalprice);
																	
		printf("%-9s%-11s%-9s%-10d%-10s%-11s%-6s%-11d%-11d%-11d%d%%\n",tempprice[j].airnumber,\
																	tempprice[j].locationstart,\
																	tempprice[j].locationover,\
																	tempprice[j].flydate,\
																	tempprice[j].timestart,\
																	tempprice[j].timeover,\
																	tempprice[j].planetype,\
																	tempprice[j].fprice,\
																	tempprice[j].bprice,\
																	tempprice[j].eprice,\
																	tempprice[j].ontimepercent);
																	
	}
	
	fclose(fpold);
	fclose(fpnew);
	
    printf("按照价格排序完毕！\n");
}

void salesfly()
{
    printf("下面将为您推荐从北京出发的航班~\n");
    FILE *fp; 
	fp=fopen("hangban.dat","r");
	struct air temp[10000];
	int i=0;
	while(!feof(fp))
	{
		fscanf(fp,"%s %s %s %d %s %s %s %d %d %d %d %s %s %d %d %d %d %d",temp[i].airnumber,\
																	temp[i].locationstart,\
																	temp[i].locationover,\
																	&temp[i].flydate,\
																	temp[i].timestart,\
																	temp[i].timeover,\
																	temp[i].planetype,\
																	&temp[i].fprice,\
																	&temp[i].bprice,\
																	&temp[i].eprice,\
																	&temp[i].ontimepercent,\
																	temp[i].pilot1,\
																	temp[i].pilot2,\
																	&temp[i].fspare,\
																	&temp[i].bspare,\
																	&temp[i].espare,\
																	&temp[i].ticketsold,\
																	&temp[i].totalprice);
											
		
		i++;		//计算存在航班数
	}
	
	int j;
	printf("航班号   起飞地     降落地   起飞日期  起飞时间  降落时间   机型  头等舱票价 商务舱票价 经济舱票价 准点率\n");
	for (j=0;j<i-1;j++)
	  if (strcmp("Beijing",temp[j].locationstart)==0)
	  {
	  	  fprintf(fp,"%s %s %s %d %s %s %s %d %d %d %d %s %s %d %d %d %d %d\n",temp[j].airnumber,\
																	temp[j].locationstart,\
																	temp[j].locationover,\
																	temp[j].flydate,\
																	temp[j].timestart,\
																	temp[j].timeover,\
																	temp[j].planetype,\
																	temp[j].fprice,\
																	temp[j].bprice,\
																	temp[j].eprice,\
																	temp[j].ontimepercent,\
																	temp[j].pilot1,\
																	temp[j].pilot2,\
																	temp[j].fspare,\
																	temp[j].bspare,\
																	temp[j].espare,\
																	temp[j].ticketsold,\
																	temp[j].totalprice);
		   													
		   printf("%-9s%-11s%-9s%-10d%-10s%-11s%-6s%-11d%-11d%-11d%d%%\n",temp[j].airnumber,\
																	temp[j].locationstart,\
																	temp[j].locationover,\
																	temp[j].flydate,\
																	temp[j].timestart,\
																	temp[j].timeover,\
																	temp[j].planetype,\
																	temp[j].fprice,\
																	temp[j].bprice,\
																	temp[j].eprice,\
																	temp[j].ontimepercent);
	  }
    
	//if (nofound==1) printf("未找到符合要求的航班信息!\n"); 
	fclose(fp);
	return;
}

void generatenobuy(char userid[]) //生成一个未购买的订单，存放到ID.txt文件中去 
{
	char *tempfilename_old;
	tempfilename_old=generatefilename();
	//puts(tempfilename_old);
	FILE *fpold;
	fpold=fopen(tempfilename_old,"r");
	
	struct air tempwaitbuy[10000];
	int i=0;
	while(!feof(fpold))
	{
		fscanf(fpold,"%s %s %s %d %s %s %s %d %d %d %d %s %s %d %d %d %d %d",tempwaitbuy[i].airnumber,\
																	tempwaitbuy[i].locationstart,\
																	tempwaitbuy[i].locationover,\
																	&tempwaitbuy[i].flydate,\
																	tempwaitbuy[i].timestart,\
																	tempwaitbuy[i].timeover,\
																	tempwaitbuy[i].planetype,\
																	&tempwaitbuy[i].fprice,\
																	&tempwaitbuy[i].bprice,\
																	&tempwaitbuy[i].eprice,\
																	&tempwaitbuy[i].ontimepercent,\
																	tempwaitbuy[i].pilot1,\
																	tempwaitbuy[i].pilot2,\
																	&tempwaitbuy[i].fspare,\
																	&tempwaitbuy[i].bspare,\
																	&tempwaitbuy[i].espare,\
																	&tempwaitbuy[i].ticketsold,\
																	&tempwaitbuy[i].totalprice);
		
		i++;		//计算现有文件里的订单数; 
	}
	
	//展示现在的待确认的航班情况
	//
	printf("编号  航班号   起飞地     降落地   起飞日期  起飞时间  降落时间   机型  头等舱票价 商务舱票价 经济舱票价 准点率\n");
	int j;
	for (j=0;j<i-1;j++)
		printf("%-6d%-9s%-11s%-9s%-10d%-10s%-11s%-6s%-11d%-11d%-11d%d%%\n",\
																	3001+j,\
																	tempwaitbuy[j].airnumber,\
																	tempwaitbuy[j].locationstart,\
																	tempwaitbuy[j].locationover,\
																	tempwaitbuy[j].flydate,\
																	tempwaitbuy[j].timestart,\
																	tempwaitbuy[j].timeover,\
																	tempwaitbuy[j].planetype,\
																	tempwaitbuy[j].fprice,\
																	tempwaitbuy[j].bprice,\
																	tempwaitbuy[j].eprice,\
																	tempwaitbuy[j].ontimepercent);
																	
	printf("请回复相应的编号进行确认:    ");
	int opcode;
	scanf("%d",&opcode);
	while (!(((opcode-3000)>0)&&((opcode-3000)<i)))
	  {
	  	printf("输入编号错误，请再次输入相应编号进行确认:    ");
	  	scanf("%d",&opcode);
	  }
	//打开以用户ID命名的文件  
	FILE *fpwait;
	static char str1[81];
	strcpy(str1,userid);
	static char str3[81];
	strcpy(str3,".txt");
	
	strcat(str1,str3);
	fpwait=fopen(str1,"a+");
	opcode=opcode-3001;
	
	sprintf(str1,"%d",datetimeshow());
	strcat(str1,str3);
	
	FILE *fpdate;
	fpdate=fopen(str1,"r");
	int bianhao;
	fscanf(fpdate,"%d",&bianhao); //读入日期文档中的编号 
	fclose(fpdate);
	 
	char tempname[81];
	printf("请输入相应的乘机人姓名:		");
	fflush(stdin);
	gets(tempname);
	fflush(stdin);
	while(1)
	{
	  if (validname(tempname)==1)
		{
		  bianhao++;
		  fprintf(fpwait,"%d ",datetimeshow()*100+bianhao);
		  fprintf(fpwait,"%s %d %s %s %s %s %s %s %d |\n",tempname,\
														tempwaitbuy[opcode].flydate,\
														tempwaitbuy[opcode].airnumber,\
														tempwaitbuy[opcode].locationstart,\
														tempwaitbuy[opcode].locationover,\
														tempwaitbuy[opcode].timestart,\
														tempwaitbuy[opcode].timeover,\
														tempwaitbuy[opcode].planetype,\
														tempwaitbuy[opcode].ontimepercent);
		  fpdate=fopen(str1,"w+");
		  fprintf(fpdate,"%d\n",bianhao);
		  fclose(fpdate);
		  break;
		  //写入信息;	 
		}
	  else
		{
		  printf("您输入的乘客姓名有误，请查验后再次输入....\n");
		  gets(tempname);
		  fflush(stdin);
		}
	}
	printf("如需添加其他乘客，请直接输入乘客姓名，如果添加完毕，请输入#\n");
	fflush(stdin);
	gets(tempname);
	fflush(stdin);
	while (strcmp(tempname,"#")!=0)
	{
		if (validname(tempname)==1)
		{
			bianhao++;
			fprintf(fpwait,"%d ",datetimeshow()*100+bianhao);
			fprintf(fpwait,"%s %d %s %s %s %s %s %s %d |\n",tempname,\
														tempwaitbuy[opcode].flydate,\
														tempwaitbuy[opcode].airnumber,\
														tempwaitbuy[opcode].locationstart,\
														tempwaitbuy[opcode].locationover,\
														tempwaitbuy[opcode].timestart,\
														tempwaitbuy[opcode].timeover,\
														tempwaitbuy[opcode].planetype,\
														tempwaitbuy[opcode].ontimepercent);
			fpdate=fopen(str1,"w+");
			fprintf(fpdate,"%d\n",bianhao); //更新文档中的编号 
			fclose(fpdate);
			
			//写入信息；
			printf("如需添加其他乘客，请直接输入乘客姓名，如果添加完毕，请输入#\n");
			fflush(stdin);
			gets(tempname);
			fflush(stdin);
		}
		else
		{
			printf("您输入的乘客姓名有误，请查验后再次输入，或者输入#结束本次订单添加\n");
			fflush(stdin);
			gets(tempname);
			fflush(stdin);
		}
	}
	fclose(fpwait);
		 
}

int datetimeshow()
{
	int yearnum,monnum,daynum;
	long timedisplay;
	
	struct tm *ptr;
  	time_t it;
  	it=time(NULL);
  	ptr=localtime(&it);
  	yearnum=ptr->tm_year+1900;
  	monnum=ptr->tm_mon+1;
  	daynum=ptr->tm_mday;
  	timedisplay=yearnum*10000+monnum*100+daynum;
  	return timedisplay;
  	
} 

int validname(char name[])
{
    int bb;//计数用 
    int i;
    FILE*inFile;
    inFile=fopen("用户信息.txt","r");
    char tempstr[256];
    char names[81][81];
    if(inFile==NULL)
    {
        printf("文件无法成功打开");
        exit(1);
    }
    while(fgets(tempstr,256,inFile))
	{
    	bb++;
	}
    rewind(inFile);
    for(i=0;i<bb;i++)
    {
        fgets(tempstr,256,inFile);
        sscanf(tempstr,"%*s %*s %*s %s",names[i]);
        //printf("%s\n",names[i]);
        if(strcmp(names[i],name)==0)
            return 1;
    }
    fclose(inFile);
    return 0;
}

/****************************************************/
/*函数定义
 函数名称：查询购买
 功能描述：实现管理员信息操作界面*/

int searchbuy(char userid[])
{
    int flag=0;
    printf("\n欢迎查询航空信息^_^\n");
    salesfly();
    printf("1  <按照日期查询>\n"); 
    printf("2  <按照航班号查询>\n");
    printf("3  <按照地点查询>\n");
    printf("4  <按照起飞时间查询>\n");
    printf("5  <按起飞时间排序所有航班>\n");
    printf("6  <根据最低价格排序>\n");
    printf("0  <返回主界面>\n\n");
    printf("请输入操作码<0-6>:");
    int opcode4;
    scanf("%d",&opcode4);
    switch (opcode4)
    {
        case 0: flag=1; return flag; break;
        case 1: searchflydate();break;
        case 2: searchnumber();break;
        case 3: searchlocation();break;
        case 4: searchtime();break;
        case 5: sorttime(); break;
        case 6: sortprice(); break;
    }
    
    printf("如果需要继续过滤搜索请按1,进入购买界面请按2，返回主菜单请按0\n");
	int opcode5;
    scanf("%d",&opcode5);
    while ((opcode5!=0)&&(opcode5!=1)&&(opcode5!=2))
        {
        	printf("操作码有误！请重新输入......\n");
        	printf("如果需要继续过滤搜索请按1,进入购买界面请按2，返回主菜单请按0\n");
            scanf("%d",&opcode5);
        	fflush(stdin);
		}
		
    
    if (opcode5==0)
    {
        flag=1;
        return flag;
    }
    while (opcode5==1)
    {
        printf("1  <按照日期过滤>\n"); 
		printf("2  <按照航班号过滤>\n");
        printf("3  <按照地点过滤>\n");
        printf("4  <按照起飞时间过滤>\n");
        printf("5  <按起飞时间过滤所有航班>\n");
        printf("6  <根据最低价格排序过滤>\n");
        printf("请输入操作码<1-6>:");
        scanf("%d",&opcode4); //抄了上面的
        switch (opcode4)
        {
            case 1: searchflydate();break;    
            case 2: searchnumber();break;
            case 3: searchlocation();break;
            case 4: searchtime();break;
            case 5: sorttime(); break;
            case 6: sortprice(); break;
        }
        printf("如果需要继续过滤搜索请按1,进入购买界面请按2，返回主菜单请按0\n");
        scanf("%d",&opcode5);
        //printf("%d",opcode5);
        fflush(stdin);
        while ((opcode5!=0)&&(opcode5!=1)&&(opcode5!=2))
        {
        	printf("操作码有误！请重新输入......\n");
        	printf("如果需要继续过滤搜索请按1,进入购买界面请按2，返回主菜单请按0\n");
            scanf("%d",&opcode5);
        	fflush(stdin);
		}
        if (opcode5==0)
        {
            flag=1;
            return flag;
        }
    }
    
    //默认出了循环以后opcode5==2;
	 
    
    generatenobuy(userid);
    printf("程序将自动进入订单管理...\n");
    //printf("请回复相应编号确定要购买的购买...\n");
    
    return (userlist(userid));
    //return flag;
}

int userpersonal(char userid[])
{
    char id[81][81],code[81][81],temp1[81][81],temp2[81][81],phonenumber[81][81],mail[81][81];
    int i=0,a=0,b=0;//i用来统计总人数，a用来表示所找的人的序号，b用来之后将存储的字符串写入文件 
    char opcode6[81];
    char opcode7[81];
    char oricode[81];//用户所输入的原密码
    char newcode[81];//用户所输入的新密码
    char oriphone[81];
    char newphone[81];
    char orimail[81];
    char newmail[81];
    int flag2=1,flag3=0,flag4=0;
    long int len;
    int xxx;
    int re=0;
	int w=1;
    FILE*inFile;
    inFile=fopen("用户信息.txt","r");
    if(inFile==NULL)
    {
        printf("文件打开失败，请联系管理员");
        exit(1);
    }
    while(!feof(inFile))//将文件中的有关信息分别保存到相应字符串数组中
    {
        while((fscanf(inFile," %s%s%s%s%s%s",id[i],code[i],temp1[i],temp2[i],phonenumber[i],mail[i]))!=EOF)
        {i++;}
    }
    for(a=0;a<i;a++)//确定用户的信息在字符串中的位置 
    {
        if(strcmp(userid,id[a])==0)
            break;
    }
	while(w)
    {
	printf("1.修改密码\n2.修改个人手机号\n3.修改邮箱\n4.返回主菜单\n0.退出程序\n");
    printf("请输入相应操作码\n");
    fflush(stdin);
    gets(opcode6);
    while(1)
	{
		if(strcmp(opcode6,"0")!=0&&strcmp(opcode6,"1")!=0&&strcmp(opcode6,"2")!=0&&strcmp(opcode6,"3")!=0&&strcmp(opcode6,"4")!=0)
		{
			printf("您输入的操作码有误，请输入正确的操作码");
			gets(opcode6); 
		}
		else
		break;
	} 
	if(strcmp(opcode6,"4")==0)
		return 1;
	if(strcmp(opcode6,"0")==0)
	exit(1);
    
    if(strcmp(opcode6,"1")==0)
    {
		char finalcode[81];	
		strcpy(code[a],codechange(code[a]));
		printf("最终密码为%s",code[a]);
        fclose(inFile);
		w=back3(i,id,code,temp1,temp2,phonenumber,mail);//返回上级 
    }
    else if(strcmp(opcode6,"2")==0)
    {
		char finalnumber[81];
		strcpy(phonenumber[a],phonechange(phonenumber[a]));
		printf("最终手机号为%s",phonenumber[a]);
        fclose(inFile);
		w=back3(i,id,code,temp1,temp2,phonenumber,mail);//返回上级 
    }
    else if(strcmp(opcode6,"3")==0)
    {
		char finalmail[81];
		strcpy(mail[a],mailchange(mail[a]));
		printf("最终邮箱为%s",mail[a]);
        fclose(inFile);
        w=back3(i,id,code,temp1,temp2,phonenumber,mail);//返回上级 
    }
	}
}

//以下程序为订单管理系列 
int userlist(char userid[])
{
    int opcode1,a=1;
	while(a) //返回上级a=1 a=0就不再循环 
	{
	    printf("|   **订单管理菜单**  |\n");
		printf("|                     |\n");
		printf("|    0. 返回主菜单    |\n"); 
		printf("|    1. 未购买订单    |\n");
		printf("|    2. 已付款订单    |\n");
		printf("|    3. 乘坐的航班    |\n");
		printf("请输入操作码<0-3>以选择您要查看的订单类型\n"); 
		scanf("%d",&opcode1);
		fflush(stdin); 
		switch(opcode1)
		{
			case 0:
				a=0;return 1; break;
			case 1:				
				if(nobuylist(userid)) break;// 有信息返回0 无信息想要返回上级返回1 
				a=nobuychoose(userid);
				break;
			case 2://已购买订单查看 buyid.txt
			{
				char idbuyfilename[81]="buy";
				strcat(idbuyfilename,userid); 
				strcat(idbuyfilename,".txt");				
				FILE *outIDfile;a=0;
				outIDfile=fopen(idbuyfilename,"r");
				printf("|    **已付款订单**    |\n");
				if(outIDfile==NULL)
					printf("\n目前还未购买任何订单！\n"); 
				else
				{
					int ch;
					ch=fgetc(outIDfile);
					if(ch==EOF)
						printf("\n目前还未购买任何订单！\n");
					else
					{
						printf("\n已付款订单信息如下:\n");
						printf("\n| 订单编号 |   乘机人   | 航班日期 | 航班号 |     起飞地     |     降落地     |起飞时间|降落时间|  机型  | 准点率| 座位号\n");//读取buyid.txt 
						showlist(outIDfile);
					}					
				}
				fclose(outIDfile);
				a=back(); 
				break;
			}
			case 3://查看自己作为乘机人的已付款订单
			{
				char username[81],s[81];a=0;
				FILE *userinfofile;FILE *usernamefile;
				userinfofile=fopen("用户信息.txt","r");
				printf("|    **乘坐的航班**    |\n");
				while(fgets(s,81,userinfofile)!=NULL)//逐行扫描用户信息直到扫描到底 这一步是用来找对应姓名的 
				{
					if(strstr(s,userid)!=NULL)//找到了该id 
	 				{
						sscanf(s,"%*s%*s%*s%s",username);
						strcat(username,".txt");//找到id对应的姓名 文件 
						usernamefile=fopen(username,"r");//打开该姓名对应的乘机人文件
						if(usernamefile!=NULL)
						{
							char nameinfo[11][21]; 
							printf("\n您的航班信息如下：\n");
							printf("|   乘机人   |    购票id   | 航班日期 | 航班号 |      起飞地      |      降落地      |起飞时间|降落时间|  机型  | 准点率| 座位号\n");//读取name.txt 
							while(fscanf(usernamefile,"%s %s %s %s %s %s %s %s %s %s %s",
										 nameinfo[0],nameinfo[1],nameinfo[2],nameinfo[3],nameinfo[4],nameinfo[5],
										 nameinfo[6],nameinfo[7],nameinfo[8],nameinfo[9],nameinfo[10])
								  !=EOF)
							  	{
									printf("| %10s | %10s | %s | %s |  %-16s|  %-16s| %s  | %s  |%6s  |  %s%%  | %s\n",
											nameinfo[0],nameinfo[1],nameinfo[2],nameinfo[3],nameinfo[4],nameinfo[5],
											nameinfo[6],nameinfo[7],nameinfo[8],nameinfo[9],nameinfo[10]);
								}
						}
						else
							printf("目前还未有您的乘机航班\n");
						fclose(usernamefile);//关闭name.txt 
						break;
					}
					else
						continue;
						
				}
				fclose(userinfofile);
				a=back();	//选择退出或返回上级菜单
				break;
			}
			default:
				printf("输入的操作码有误，请重新输入！\n");
				break;			
		}
	}
	return 1;//返回值为1回到主菜单 返回值为0退出系统 
	
}

int nobuylist(char userid[])
{
	int a=0;
	FILE *nobuyfile;//打开id.txt 
	char listfilename[21];
	strcpy(listfilename,userid);
	strcat(listfilename,".txt");
	nobuyfile=fopen(listfilename,"r");
	printf("|    **未购买订单**    |\n");
	if(nobuyfile!=NULL)
	{
		int ch;
		ch=fgetc(nobuyfile);
		if(ch==EOF)
		{
			printf("目前还未有您的订单收藏信息！\n");
			a=back();//返回上级为1 
		}
		else
		{
			printf("您的未购买订单信息如下：\n");
			printf("\n| 订单编号 |   乘机人   | 航班日期 | 航班号 |     起飞地     |     降落地     |起飞时间|降落时间|  机型  | 准点率| |\n");
			showlist(nobuyfile);//有信息为0 	
		}		
	}
	else
	{
		printf("目前还未有您的订单收藏信息！\n");
		a=back();//返回上级为1 
	}
	fclose(nobuyfile);
	return a;	
}

int adminpersonal(char adminid[])
{   
    char id[81][81],code[81][81],temp1[81][81],temp2[81][81],mail[81][81];
    int i=0,a=0,b=0;//i用来统计总人数，a用来表示所找的人的序号，b用来之后将存储的字符串写入文件 
    char opcode6[81];
    char opcode7[81];
    char oricode[81];//管理员所输入的原密码
    char newcode[81];//管理员所输入的新密码
    char orimail[81];
    char newmail[81];
    int flag2=1,flag3=0,flag4=0;
    long int len;
    int xxx;
    int w=1;
    int re=0; 
    FILE*inFile;
    inFile=fopen("管理员信息.txt","r");
    if(inFile==NULL)
    {
        printf("文件打开失败");
        exit(1);
    }
    while(!feof(inFile))//将文件中的有关信息分别保存到相应字符串数组中
    {
        while((fscanf(inFile," %s%s%s%s%s",id[i],code[i],temp1[i],temp2[i],mail[i]))!=EOF)
        {i++;}
    }
    for(a=0;a<i;a++)//确定用户的信息在字符串中的位置 
    {
        if(strcmp(adminid,id[a])==0)
            break;
    }
	while(w)
    {
	printf("1.修改密码\n2.修改邮箱\n3.返回上级菜单\n0.退出程序\n");
    printf("请输入相应操作码\n");
    fflush(stdin);
    scanf("%s",opcode6);
    while(1)
	{
		if(strcmp(opcode6,"0")!=0&&strcmp(opcode6,"1")!=0&&strcmp(opcode6,"2")!=0&&strcmp(opcode6,"3")!=0)
		{
			printf("您输入的操作码有误，请输入正确的操作码");
			fflush(stdin);
			scanf("%s",opcode6);	 
		}
		else
		break;
	} 
	if(strcmp(opcode6,"3")==0)
	{
		return 1;
	}
	if(strcmp(opcode6,"0")==0)
	exit(1);
    
    if(strcmp(opcode6,"1")==0)
    {
		char finalcode[81];	
		strcpy(code[a],codechange(code[a]));
		printf("最终密码为%s",code[a]);
		fclose(inFile);
  		w=back2(i,id,code,temp1,temp2, mail);//返回上级 
    }
 else if(strcmp(opcode6,"2")==0)
    {
		char finalmail[81];
		strcpy(mail[a],mailchange(mail[a]));
		printf("最终邮箱为%s",mail[a]);
        fclose(inFile);
        w=back2(i,id,code,temp1,temp2, mail);//返回上级 
    }
	}
}

int adminlist(char flightcompany[])  //管理员对用户订单操作函数，接收管理员所在航班公司字符串指针，允许管理员按照一定顺序排列用户订单，返回值与返回菜单功能有关 
{
    int opcode,opcode1,flag=0;
    char *filename1;
	char *filename2;
	filename1 = generatecompanyorders(flightcompany);
	filename2 = generatecompanyinfo(flightcompany);
    while(1)
    {
        printf("\n\n0.返回上级菜单\n");
        printf("1.查看用户订单情况\n");
        printf("2.统计用户订单信息\n");
        printf("请输入操作码<0-2>:");
        scanf("%d",&opcode);
        if (opcode==1)
        {
            userordershow(filename1);
            printf("下面你将返回管理员功能选择界面\n");
            sleep(2);
            return 1;  //结束目前的函数并返回1 
	  		break;
        }
        else if(opcode==2)
        {
            printf("0.返回上级菜单\n");
            printf("1.按已购票人数排序还未起飞的本航空公司所有的航班信息\n");
            printf("2.按飞机上座率排序已经飞行结束的所有航班信息\n");
            printf("3.按航班总票价收入排序已经飞行结束的所有历史航班信息\n");
            printf("请输入操作码<1-3>:");
            scanf("%d",&opcode1);
            if(opcode1==0)
                continue;
            else if(opcode1==1)
                {
					people(filename2);
					printf("下面你将返回管理员功能选择界面\n");
					sleep(2);
					return 1;  //结束目前的函数并返回1 
				}	 
            else if(opcode1==2)
                {
					rate(filename2);
					printf("下面你将返回管理员功能选择界面\n");
					sleep(2);
					return 1;  //结束目前的函数并返回1 
				}	 
            else if(opcode1==3)
                {
					money(filename2);
					printf("下面你将返回管理员功能选择界面\n");
					sleep(2);
					return 1;  //结束目前的函数并返回1 
				}	 
            break;
        }
        else if(opcode==0)
        {
            flag=1;
            return flag;
        }
        else
            printf("输入有误请重新输入\n");
    }
    
    return flag; 
}

int adminfly(char flightcompany[])  //管理员对航班信息操作函数，接收管理员所在航班公司字符串指针，允许管理员按照一定顺序排列航班信息以及添加航班，返回值与返回菜单功能有关
{
    int opcode,flag=0;
    while(1)
    {
        printf("0.返回管理员功能选择界面\n"); 
        printf("1.查询本公司全部航班\n");
        printf("2.添加航班\n");
        printf("请输入操作码<0-2>:");
        scanf("%d",&opcode);
        if(opcode==0)
        {
            return 1;
        }
        else if(opcode==1)
        {
            flightsearch(flightcompany);
            printf("下面你将返回管理员功能选择界面\n");
			sleep(2);
            return 1;
            break;
        }
        else if(opcode==2)
        {
            addflight();
            printf("下面你将返回管理员功能选择界面\n");
			sleep(2);
			return 1;
            break;
        }
        else
            printf("输入有误请重新输入\n"); 
    }
    return flag;
}

void showlist(FILE *outfile)
{
	char flyinfo[11][81];
	rewind(outfile);
	while(fscanf(outfile,"%s %s %s %s %s %s %s %s %s %s %s",
						flyinfo[0],flyinfo[1],flyinfo[2],flyinfo[3],flyinfo[4],
						flyinfo[5],flyinfo[6],flyinfo[7],flyinfo[8],flyinfo[9],flyinfo[10])
				!=EOF)
		printf("|%s| %10s | %s | %s |  %-14s|  %-14s| %s  | %s  |%6s  |  %s%%  | %s\n",
				flyinfo[0],flyinfo[1],flyinfo[2],flyinfo[3],flyinfo[4],
				flyinfo[5],flyinfo[6],flyinfo[7],flyinfo[8],flyinfo[9],flyinfo[10]);
}

int nobuychoose(char *userid)
{
	int opcode,a=0;
	while(!a)
	{
		printf("\n接下来您希望进行哪一操作？\n");
		printf("0.  返回上级菜单\n");//返回订单管理菜单 
		printf("1.  删除订单\n");
		printf("2.  购买订单\n");
		printf("请输入操作码<0-2>以选择\n"); 
		scanf("%d",&opcode);
		fflush(stdin); 
		switch(opcode)
		{
			case 0:a=1;break;
			case 1:listdelete(userid);a=back();break;
			case 2:flybuy(userid);a=back();break;	
			default:
				printf("输入的操作码有误，请重新输入！\n");
				break;
		}
	}
	return a;
}

void listdelete(char *userid)//未购订单中选择删除 
{
	int a=1;
	char flynum[11],idfilename[81],s[256],ss[11];
	FILE *oldfile;FILE *newfile;
	strcpy(idfilename,userid);
	strcat(idfilename,".txt");
	oldfile=fopen(idfilename,"r");
	newfile=fopen("temp.txt","w");
	
	while(a) 
	{	
		printf("请输入对应编号进行删除："); //通过把订单编号存到ss 只检索订单编号 
		scanf("%s",flynum);
		fflush(stdin);
		a=numexit(flynum,oldfile);//编号输入正确返回0 退出循环 
	}
	
	rewind(oldfile);//光标移到file最前 
	while(fgets(s,256,oldfile)!=NULL)
	{
		sscanf(s,"%s",ss);
		if(strstr(ss,flynum)==NULL) 
			fputs(s,newfile);
		else
			continue;
	}
	fclose(oldfile);
	fclose(newfile);
	if(remove(idfilename)==0)//删除和改名都失败了  remove返回值为-1 成功删除返回值为0
	 	printf("成功删除该订单！\n");
	else
		printf("文件删除失败！\n"); 
	rename("temp.txt",idfilename);
	
}

void flybuy(char *userid)//未购订单中选择购买 
{
	int a=1,c1,c2,c3;
	char flynum[11],idfilename[81],s[256],ss[11];
	FILE *oldfile;
	strcpy(idfilename,userid);
	strcat(idfilename,".txt");
	oldfile=fopen(idfilename,"r");
	while(a)
	{
	printf("请输入对应编号进行购买："); 
	scanf("%s",flynum);
	fflush(stdin);
	a=numexit(flynum,oldfile);
	}//订单编号输入成功flynum[] 
	
	rewind(oldfile);//验证编号是否正确已读取全部文件 光标移到file最前 
	
	while(fgets(s,256,oldfile)!=NULL)//提取含该订单号的整条信息 
	{
		sscanf(s,"%s",ss);
		if(strstr(ss,flynum)!=NULL) 
			break;
		else
			continue;
	} 
	fclose(oldfile);
	
	c1=idcheck(userid,s);//验证是否能购买 
	c2=namecheck(userid,s);
	c3=timecheck(userid,s);
	if(c1&&c2&&c3)//可以购买 
	{
		char seat;
		while(1)
		{
			printf("舱位选择\n");
			printf("F.  头等舱\n");
			printf("B.  商务舱\n");
			printf("E.  经济舱\n");
			printf("输入操作码<F/B/E>进行选择："); 
			scanf("%c",&seat);
			fflush(stdin);
			if(seat!='E'&&seat!='B'&&seat!='F')
			{
				printf("您输入的操作码有误!\n");
				printf("请重新输入！"); 
			}
			else
				break; 
		}
		
		if(ticketcheck(s,seat)==1)
		{
			renewfile(s,seat,userid);
			printf("购买成功！\n"); //更新id.txt 
		}
		else
			printf("抱歉，该种机票已售空，无法购买！\n"); 
		
	} 
	else
		return;
}

int idcheck(char *userid,char *s)//检查同一id今日购买次数是否已达到5 参数输入为待确认购买的一条信息 
{
	int todate,filedate,a=0;
	char idfilename[81]="buy",buys[256];
	FILE *buyfile;
	strcat(idfilename,userid);
	strcat(idfilename,".txt");
	buyfile=fopen(idfilename,"r");
	todate=datetimeshow();
	while(fgets(buys,256,buyfile)!=NULL)
	{
		sscanf(buys,"%8d",&filedate);
		if(filedate==todate)
			a++;
		else
			continue;
	}
	fclose(buyfile);
	if(a==5)
	{
		printf("今日您已购买5张票，无法购买！\n");
		return 0;
	}
	else
		return 1;	
}

int namecheck(char *userid,char *s)//检查乘机人乘坐航班是否时间冲突 不冲突返回1
{
	char name[81],names[256],flytakeoff[6],flyland[6],filetakeoff[6],fileland[6];
	int flydate,filedate,flytakeoffnum,flylandnum,filetakeoffnum,filelandnum,i,j,a=0;
	int time[1440];
	sscanf(s,"%*s %s %8d %*s %*s %*s %s %s",name,&flydate,flytakeoff,flyland);
	FILE *namefile;
	strcat(name,".txt");
	namefile=fopen(name,"r");
	while(fgets(names,256,namefile)!=NULL)//逐行扫描name.txt直到扫描到文件结束
	{
		sscanf(names,"%*s %*s %8d %*s %*s %*s %s %s",&filedate,filetakeoff,fileland);
		if(filedate==flydate)//找到相同日期的话就要进行时间查重啦
		{
			flytakeoffnum=turntime(flytakeoff);
			flylandnum=turntime(flyland);
			for(i=flytakeoffnum;i<=flylandnum;i++)
				time[i]=1;//待定航班所占时间的分钟数改为1
			filetakeoffnum=turntime(filetakeoff);
			filelandnum=turntime(fileland);
			for(i=filetakeoffnum;i<flylandnum;i++)
			{
				if(time[i])
					a++;//时间冲突改变a值 
			}			
		}
		else
			continue; 
	} 
	fclose(namefile);
	if(a)
	{
		printf("航班时间冲突，无法购买！\n");
		return 0;
	}
	else
		return 1;
} 

int timecheck(char *userid,char *s) 
{
	int todate,flydate,fly,flytakeoffnum;
	char flytakeoff[6];
	todate=datetimeshow();
	sscanf(s,"%*s %*s %8d %*s %*s %*s %s",&flydate,flytakeoff);
	if(todate<flydate)
		return 1;
	if(todate<flydate)
	{
		printf("该航班已过期，无法购买！\n");
		return 0;
	}
	if(todate==flydate)
	{
		flytakeoffnum=turntime(flytakeoff);
		
		int hournum,minnum;
		long timenow;		
		struct tm *ptr;
  		time_t it;
  		it=time(NULL);
  		ptr=localtime(&it);
  		hournum=ptr->tm_hour;
  		minnum=ptr->tm_min;
  		timenow=hournum*60+minnum;
  		
  		if(timenow>=flytakeoffnum)
  		{
  			printf("该航班已过期，无法购买！\n");
			return 0;
		}
		else
			return 1;
	}
}

int ticketcheck(char stemp[],char ch)//参数为一整条信息 和 仓位号 
{
	struct air temp;
	char chengjiren[256];
	char seat[256];
	char dingdanhao[256];

	sscanf(stemp,"%s %s %d %s %s %s %s %s %s %d",dingdanhao,\
												 chengjiren,\
												 &temp.flydate,\
												 temp.airnumber,\
												 temp.locationstart,\
												 temp.locationover,\
												 temp.timestart,\
												 temp.timeover,\
												 temp.planetype,\
												 &temp.ontimepercent);
												 
	int i;
	int flag=0; //临时的一个flag 
	//init();
	for (i=0;i<m;i++)
	{
		switch (ch)
		{
			case 'F':
				if ((temp.flydate==userorder[i].flydate)&&(strcmp(temp.airnumber,userorder[i].airnumber)==0))
				  if (userorder[i].fspare>=0)
				    {
				    	flag=1;
				    	break;
					}
			case 'B':
				if ((temp.flydate==userorder[i].flydate)&&(strcmp(temp.airnumber,userorder[i].airnumber)==0))
				  if (userorder[i].bspare>=0)
				    {
				    	flag=1;
				    	break;
					}
			case 'E':
				if ((temp.flydate==userorder[i].flydate)&&(strcmp(temp.airnumber,userorder[i].airnumber)==0))
				  if (userorder[i].espare>=0)
				    {
				    	flag=1;
				    	break;
					}
		}
		if (flag==1) break;
	}
	refreshhangban(); //将更改的整个航班信息结构重新覆盖写入文件 
	return flag;	
}

int numexit(char flynum[],FILE *oldfile)//判断所输入编号是否存在 
{
	char ss[11],s[256];
	int a=0; 

	while(fgets(s,256,oldfile)!=NULL)//输入的订单编号存在 改变a 
	{
		sscanf(s,"%s",ss);
		if(strcmp(ss,flynum)==0) 
			a++;
		else
			continue;
	} 
	if(a==0)
	{
		rewind(oldfile);
		printf("\n输入的订单编号不存在,请重新输入正确的订单编号！\n");
		return 1;
	}		
	else
		return 0;
}

void renewfile(char str[],char seatcode,char userid[]) //接收一段订单信息，座位号和userid，用来更新文件 
{
	int i;
	char chengjiren[256];
	char seat[256];
	char dingdanhao[256];
	char cangwei[2];
	struct air temp;
	cangwei[0]=seatcode;
	cangwei[1]='\0';
	sscanf(str,"%s %s %d %s %s %s %s %s %s %d",dingdanhao,chengjiren,&temp.flydate,temp.airnumber,temp.locationstart,temp.locationover,temp.timestart,temp.timeover,temp.planetype,&temp.ontimepercent);
	
	for(i=0;i<m;i++)
	{
		if((strcmp(temp.airnumber,userorder[i].airnumber)==0) && (temp.flydate == userorder[i].flydate)) //i停止的值便是需要修改的航班信息所在行数 
		  break;
	}
	char filename[256];
	char tempstr[256];
	char randletter[256];
	char tempcangwei[256];
	int randnum; 
	strcpy(tempcangwei,cangwei);
	strcpy(tempstr,chengjiren);
	strcat(tempstr,".txt");
	strcpy(filename,tempstr);
	FILE *outfile;
	outfile=fopen(filename,"a+");
	char sparestr[256];
	srand((int)time(NULL)); 
	randnum=rand()%3+1;
	switch(randnum) //随机产生1-3，若为1则分配座位A，2为B，3为C 
	{
		case 1: strcpy(randletter,"A"); break;
		case 2: strcpy(randletter,"B"); break;
		case 3: strcpy(randletter,"C"); break;
	}
	
	if(strcmp(cangwei,"F") == 0) //头等舱仓位减一，总票价增加 
		{
	  		itoa(userorder[i].fspare,sparestr,10);
	  		userorder[i].totalprice += userorder[i].fprice;
	  		userorder[i].fspare--;
	  	}
	else if(strcmp(cangwei,"B") == 0) //商务舱仓位减一，总票价增加 
		{
	  		itoa(userorder[i].bspare,sparestr,10);
	  		userorder[i].totalprice += userorder[i].bprice;
	  		userorder[i].bspare--;
	  	}
	else if(strcmp(cangwei,"E") == 0)//经济舱仓位减一，总票价增加 
		{
	  		itoa(userorder[i].espare,sparestr,10);
	  		userorder[i].totalprice += userorder[i].eprice;
	  		userorder[i].espare--;
	  	}
	else printf("舱位接受有误！\n");
	
	strcat(sparestr,randletter);
	strcat(tempcangwei,sparestr);
	strcpy(seat,tempcangwei);
	fprintf(outfile,"%s %s %d %s %s %s %s %s %s %d %s\n",chengjiren,userid,temp.flydate,temp.airnumber,temp.locationstart,temp.locationover,temp.timestart,temp.timeover,temp.planetype,temp.ontimepercent,seat);
	fclose(outfile);
	strcpy(tempstr,userid);
	char tempstr1[256];
	strcpy(tempstr1,"buy");
	strcat(tempstr,".txt");
	strcat(tempstr1,tempstr);
	strcpy(filename,tempstr1);
	outfile=fopen(filename,"a+");
	fprintf(outfile,"%s %s %d %s %s %s %s %s %s %d %s\n",dingdanhao,chengjiren,temp.flydate,temp.airnumber,temp.locationstart,temp.locationover,temp.timestart,temp.timeover,temp.planetype,temp.ontimepercent,seat);
	fclose(outfile);
	userorder[i].ticketsold++; //购买人数加1 
	refreshhangban();
	outfile=fopen("总订单.txt","a+");
	fprintf(outfile,"%s %s %s %d %s %s %s %s %s %s %d %s\n",dingdanhao,userid,chengjiren,temp.flydate,temp.airnumber,temp.locationstart,temp.locationover,temp.timestart,temp.timeover,temp.planetype,temp.ontimepercent,seat);
	//将订单输入总订单.txt文件 
	fclose(outfile);
	FILE *oldfile;
	FILE *newfile;
	strcpy(filename,userid);
	strcat(filename,".txt");
	oldfile=fopen(filename,"r");
	newfile=fopen("tempuserid.txt","w");
	while(fgets(tempstr,256,oldfile)!=NULL)
	{
		if(strstr(tempstr,dingdanhao)==NULL) 
			fputs(tempstr,newfile);
		else
			continue;
	} 
	fclose(oldfile);
	fclose(newfile);

	remove(filename); //移除老文件 
	rename("tempuserid.txt",filename); //重命名新文件 
	
	return;
}


void userordershow(char filename[]) //用户订单显示函数，显示管理员所在航班公司的全部用户订单
{
	printf("正在生成用户信息列表\n");
	sleep(2);
    printf("用户订单情况如下:\n");
    printf("订单号       用户名       购买人       起飞日期   航班号  起飞地    降落地    起飞时间  降落时间  机型   准点率  座位号\n"); 
    FILE *infile;
	char temp[81];
	char tempstr[12][256];
	infile=fopen(filename,"r");
	while(fgets(temp,256,infile))
	{
		sscanf(temp,"%s %s %s %s %s %s %s %s %s %s %s %s",tempstr[0],tempstr[1],tempstr[2],tempstr[3],tempstr[4],tempstr[5],tempstr[6],tempstr[7],tempstr[8],tempstr[9],tempstr[10],tempstr[11]);
	  	printf("%-13s%-13s%-13s%-11s%-8s%-10s%-10s%-10s%-10s%-7s%s%%     %s\n",tempstr[0],tempstr[1],tempstr[2],tempstr[3],tempstr[4],tempstr[5],tempstr[6],tempstr[7],tempstr[8],tempstr[9],tempstr[10],tempstr[11]);
	}
	
	return;
}

void people(char filename[])  //未起飞航班的以购票人数排序函数，排序管理员所在航空公司的全部航班信息并显示
{
    int i,j,k,temp;
	int rows=0;
	char str[256];
	char tempstr[256];
	FILE *infile;
	infile = fopen(filename,"r");
  	while(fgets(str,256, infile) != NULL)
    	rows++;   //数行数 
    rewind(infile);
    char flight[rows][256];
    char flighttimestr[rows][256];
    int flighttime[rows];
    int flightdate[rows];
    int timenow;
    for(i=0;i<rows;i++)  //读取文件中航班信息的日期和起飞时间 
    {
    	fgets(flight[i],256,infile);
    	sscanf(flight[i],"%*s %*s %*s %d %s",&flightdate[i],flighttimestr[i]);
    	flighttime[i]=turntime(flighttimestr[i])+flightdate[i]*10000;
	}
	timenow=totaltimeshow();
    fclose(infile);
    infile=fopen("peopletemp.txt","w");
    for(i=0;i < rows;i++)
      if(flighttime[i]>timenow) //若航班已起飞 
      {
	    fprintf(infile,"%s",flight[i]); 
	  }
	fclose(infile);
	rows=0;
	infile=fopen("peopletemp.txt","r");
	while(fgets(str,256,infile) != NULL)
    	rows++; //数行数 
    rewind(infile);
    int flightpeople[rows];
    for(i=0;i<rows;i++)
    {
    	fgets(flight[i],256,infile);
    	sscanf(flight[i],"%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %d",&flightpeople[i]);
	}
  	for(i=0;i<rows-1;i++)  //通过已购票人数选择排序，从而排序整个航班信息 
  	{
		k=i;
  		for(j=i+1;j<rows;j++)
		if(flightpeople[k]>flightpeople[j])
			k=j; 
		if(i!=k)
		{
			temp=flightpeople[i]; 
			flightpeople[i]=flightpeople[k]; 
			flightpeople[k]=temp; 
			strcpy(tempstr,flight[i]);
			strcpy(flight[i],flight[k]);
			strcpy(flight[k],tempstr);
	    }
	}
	char strtemp[18][256];
	printf("正在生成航班信息列表...\n");
	sleep(2);
	printf("未起飞航班的已购票人数排序如下:\n"); 
	printf("航班号 起飞地     目的地     起飞日期  起飞时间  降落时间  机型   头等舱票价  商务舱票价  经济舱票价  准点率 飞行员1   飞行员2   头等舱余票  商务舱余票  经济舱余票  购买人数  总票价\n");
	for(i=0;i<rows;i++)
	{
		sscanf(flight[i],"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",strtemp[0],strtemp[1],strtemp[2],strtemp[3],strtemp[4],strtemp[5],strtemp[6],strtemp[7],strtemp[8],strtemp[9],strtemp[10],strtemp[11],strtemp[12],strtemp[13],strtemp[14],strtemp[15],strtemp[16],strtemp[17]);
		printf("%-7s%-11s%-11s%-10s%-10s%-10s%-7s%-12s%-12s%-12s%s%%    %-10s%-10s%-12s%-12s%-12s%-10s%s\n",strtemp[0],strtemp[1],strtemp[2],strtemp[3],strtemp[4],strtemp[5],strtemp[6],strtemp[7],strtemp[8],strtemp[9],strtemp[10],strtemp[11],strtemp[12],strtemp[13],strtemp[14],strtemp[15],strtemp[16],strtemp[17]);
	}
	return;
}

void money(char filename[])  //已飞行结束航班的总票价收入排序函数，排序管理员所在航空公司的全部航班信息并显示
{
    int i,j,k,temp;
	int rows=0;
	char str[256];
	char tempstr[256];
	FILE *infile;
	infile = fopen(filename,"r");
  	while(fgets(str,256, infile) != NULL)
    	rows++; //数行数 
    rewind(infile); //指针重新返回文件开头 
    char flight[rows][256];
    char flighttimestr[rows][256];
    int flighttime[rows];
    int flightdate[rows];
    int timenow;
    for(i=0;i<rows;i++) //读取文件中航班信息的日期和起飞时间 
    {
    	fgets(flight[i],256,infile);
    	sscanf(flight[i],"%*s %*s %*s %d %s",&flightdate[i],flighttimestr[i]);
    	flighttime[i]=turntime(flighttimestr[i])+flightdate[i]*10000;
	}
	timenow=totaltimeshow();
    fclose(infile);
    infile=fopen("moneytemp.txt","w");
    for(i=0;i < rows;i++)
      if(flighttime[i]<=timenow) //若航班已起飞 
      {
	    fprintf(infile,"%s",flight[i]);  
	  }
	fclose(infile);
	rows=0;
	infile=fopen("moneytemp.txt","r");
	while(fgets(str,256,infile) != NULL)
    	rows++;  //数行数 
    rewind(infile); //指针重新返回文件开头 
    int flightprice[rows];
    for(i=0;i<rows;i++)
    {
    	fgets(flight[i],256,infile);
    	sscanf(flight[i],"%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %d",&flightprice[i]);
	}
  	for(i=0;i<rows-1;i++)  //通过总票价收入选择排序，从而排序整个航班信息 
  	{
		k=i;
  		for(j=i+1;j<rows;j++) 
		if(flightprice[k]>flightprice[j]) 
			k=j; 
		if(i!=k) 
		{
			temp=flightprice[i]; //交换航班价格 
			flightprice[i]=flightprice[k]; 
			flightprice[k]=temp; 
			strcpy(tempstr,flight[i]); //交换对应的航班信息 
			strcpy(flight[i],flight[k]);
			strcpy(flight[k],tempstr);
	    } 
	} 
	char strtemp[18][256];
	printf("正在生成航班信息列表...\n");
	sleep(2);
	printf("已飞行结束航班的总票价收入排序如下:\n"); 
	printf("航班号 起飞地     目的地     起飞日期  起飞时间  降落时间  机型   头等舱票价  商务舱票价  经济舱票价  准点率 飞行员1   飞行员2   头等舱余票  商务舱余票  经济舱余票  购买人数  总票价\n");
	for(i=0;i<rows;i++)
	{
		sscanf(flight[i],"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",strtemp[0],strtemp[1],strtemp[2],strtemp[3],strtemp[4],strtemp[5],strtemp[6],strtemp[7],strtemp[8],strtemp[9],strtemp[10],strtemp[11],strtemp[12],strtemp[13],strtemp[14],strtemp[15],strtemp[16],strtemp[17]);
		printf("%-7s%-11s%-11s%-10s%-10s%-10s%-7s%-12s%-12s%-12s%s%%    %-10s%-10s%-12s%-12s%-12s%-10s%s\n",strtemp[0],strtemp[1],strtemp[2],strtemp[3],strtemp[4],strtemp[5],strtemp[6],strtemp[7],strtemp[8],strtemp[9],strtemp[10],strtemp[11],strtemp[12],strtemp[13],strtemp[14],strtemp[15],strtemp[16],strtemp[17]);
	}
	
	return;
}

void rate(char filename[]) //已飞行完毕航班的上座率排序函数，排序管理员所在航空公司的全部航班信息并显示
{
    int i,j,k,temp;
    int a,b,c,d; //用于记录票价及购票人数 
	int rows=0;
	char str[256];
	char tempstr[256];
	FILE *infile;
	infile = fopen(filename,"r");
  	while(fgets(str,256, infile) != NULL)
    	rows++; //数行数 
    rewind(infile); //指针重新返回文件开头 
    char flight[rows][256];
    char flighttimestr[rows][256];
    int flighttime[rows];
    int flightdate[rows];
    int timenow;
    for(i=0;i<rows;i++)
    {
    	fgets(flight[i],256,infile);
    	sscanf(flight[i],"%*s %*s %*s %d %s",&flightdate[i],flighttimestr[i]);
    	flighttime[i]=turntime(flighttimestr[i])+flightdate[i]*10000; //将航班日期以及时间全部转化为数字 
	}
	timenow=totaltimeshow();
    fclose(infile);
    infile=fopen("ratetemp.txt","w");
    for(i=0;i < rows;i++)
      if(flighttime[i]>timenow)
      {
	    fprintf(infile,"%s",flight[i]); 
	  }
	fclose(infile);
	rows=0;
	infile=fopen("ratetemp.txt","r");
	while(fgets(str,256,infile) != NULL)
    	rows++; //数行数 
    rewind(infile); //指针重新返回文件开头 
    float flightrate[rows];
    for(i=0;i<rows;i++)
    {
    	fgets(flight[i],256,infile);
    	sscanf(flight[i],"%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %d %d %d %d",&a,&b,&c,&d);
    	flightrate[i]=(float)d/((float)a+(float)b+(float)c+(float)d); //计算上座率 
	}
  	for(i=0;i<rows-1;i++) //通过上座率选择排序，从而排序整个航班信息 
  	{
		k=i;
  		for(j=i+1;j<rows;j++) 
		if(flightrate[k]>flightrate[j]) 
			k=j; 
		if(i!=k) 
		{
			temp=flightrate[i]; 
			flightrate[i]=flightrate[k]; 
			flightrate[k]=temp; 
			strcpy(tempstr,flight[i]);
			strcpy(flight[i],flight[k]);
			strcpy(flight[k],tempstr);
	    } 
	} 
	char strtemp[18][256];
	printf("正在生成航班信息列表...\n");
	sleep(2);
	printf("已飞行完毕航班的上座率排序如下:\n"); 
	printf("航班号 起飞地     目的地     起飞日期  起飞时间  降落时间  机型   头等舱票价  商务舱票价  经济舱票价  准点率 飞行员1   飞行员2   头等舱余票  商务舱余票  经济舱余票  购买人数  总票价\n");
	for(i=0;i<rows;i++)
	{
		sscanf(flight[i],"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",strtemp[0],strtemp[1],strtemp[2],strtemp[3],strtemp[4],strtemp[5],strtemp[6],strtemp[7],strtemp[8],strtemp[9],strtemp[10],strtemp[11],strtemp[12],strtemp[13],strtemp[14],strtemp[15],strtemp[16],strtemp[17]);
		printf("%-7s%-11s%-11s%-10s%-10s%-10s%-7s%-12s%-12s%-12s%s%%    %-10s%-10s%-12s%-12s%-12s%-10s%s\n",strtemp[0],strtemp[1],strtemp[2],strtemp[3],strtemp[4],strtemp[5],strtemp[6],strtemp[7],strtemp[8],strtemp[9],strtemp[10],strtemp[11],strtemp[12],strtemp[13],strtemp[14],strtemp[15],strtemp[16],strtemp[17]);
	}
	
	return;
}

void flightsearch(char flightcompany[]) //显示管理员所在航空公司的所有航班信息 
{
    FILE *infile;
	char *filename;
	char file_str[1024];
	char tempstr[18][256];
	filename = generatecompanyinfo(flightcompany);
	infile=fopen(filename,"r");
	printf("正在生成\n");
	sleep(2);
	printf("所有开设航班信息如下:\n");
	printf("航班号 出发地    目的地    起飞日期  起飞时间  降落时间  机型  头等舱票价 商务舱票价 经济舱票价 准点率  飞行员1     飞行员2     头等舱余座 商务舱余座 经济舱余座 购买人数 总票价\n"); 
	while(fgets(file_str,sizeof(file_str),infile))
	{
		sscanf(file_str,"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",tempstr[0],tempstr[1],tempstr[2],tempstr[3],tempstr[4],tempstr[5],tempstr[6],tempstr[7],tempstr[8],tempstr[9],tempstr[10],tempstr[11],tempstr[12],tempstr[13],tempstr[14],tempstr[15],tempstr[16],tempstr[17]);
		if(strstr(file_str,flightcompany) != NULL)
		{
			printf("%-7s%-10s%-10s%-10s%-10s%-10s%-6s%-11s%-11s%-11s%s%%     %-12s%-12s%-11s%-11s%-11s%-9s%s\n",tempstr[0],tempstr[1],tempstr[2],tempstr[3],tempstr[4],tempstr[5],tempstr[6],tempstr[7],tempstr[8],tempstr[9],tempstr[10],tempstr[11],tempstr[12],tempstr[13],tempstr[14],tempstr[15],tempstr[16],tempstr[17]);
		}
	}
	fclose(infile);
}

void addflight()  //添加航班，以飞行员时间是否重复和前后飞行航班城市是否相接为条件 
{
    int oprand;
	int i;
	int flag1,flag2;
	char strtime[81];
	char strtemp[81]; //声明临时字符串接收航班信息 
	struct flight temp;
	FILE *infile;
	while(1)
	{
		printf("请输入添加的航班号(形如CA1234):");
		scanf("%s",temp.flightnumber);
		fflush(stdin);
		while(checkfn(temp.flightnumber) == 1)
		{
			printf("输入错误请重新输入:");
			scanf("%s",temp.flightnumber);
			fflush(stdin);
		}
		printf("请输入该航班出发地:");
		scanf("%s",temp.flightstart);
		fflush(stdin); //清空键盘缓冲区 
		printf("请输入该航班目的地:");
		scanf("%s",temp.flightend);
		fflush(stdin); //清空键盘缓冲区 
		printf("请输入该航班起飞时间及落地时间(形如hh:mm-hh:mm):\n");
		gets(strtime);
		fflush(stdin); //清空键盘缓冲区 
		temp.starttime=strcpymiddle(strtime,0,5);
		temp.endtime=strcpymiddle(strtime,6,5);
		printf("请输入该航班机型:");
		scanf("%s",temp.flightmodel);
		fflush(stdin); //清空键盘缓冲区 
		printf("请输入头等舱，商务舱，经济舱票价(形如1234 800 600):");
		scanf("%d %d %d",&temp.toudengprice,&temp.shangwuprice,&temp.jingjiprice);
		fflush(stdin); //清空键盘缓冲区 
		printf("请输入上座率(形如90%%):");
		scanf("%s",strtemp);
		fflush(stdin); //清空键盘缓冲区 
		temp.flightrate = atoi(strtemp);
		printf("请输入飞行员1:");
		while(1)
		{
			scanf("%s",temp.pilot1);
			fflush(stdin);
			flag1 = validpilot(temp.flightnumber,temp.pilot1,temp.flightstart,temp.flightend,temp.starttime,temp.endtime);
			if(flag1==1) //返回1为时间重复 
			{
				printf("该飞行员飞行时间重复，请更换飞行员\n");
				printf("请输入飞行员1:");
				continue;
			}
			else if(flag1==2) //返回2为地点不相接 
			{
				printf("添加航班后目的地与出发地无法在保证时间内到达，请更换飞行员\n");
				printf("请输入飞行员1:");
				continue;
			}
			else break;
		}
		printf("请输入飞行员2:");
		while(1)
		{
			scanf("%s",temp.pilot2);
			fflush(stdin);
			flag2 = validpilot(temp.flightnumber,temp.pilot2,temp.flightstart,temp.flightend,temp.starttime,temp.endtime);
			if(flag2==1) //返回1为时间重复 
			{
				printf("该飞行员飞行时间重复，请更换飞行员\n");
				printf("请输入飞行员2:");
				continue;
			}
			else if(flag2==2) //返回2为地点不相接 
			{
				printf("添加航班后目的地与出发地无法在保证时间内到达，请更换飞行员\n");
				printf("请输入飞行员2:");
				continue;
			}
			else break;
		}
		printf("请输入头等舱，商务舱，经济舱座位数(形如20 50 200):");
		scanf("%d %d %d",&temp.toudengzuo,&temp.shangwuzuo,&temp.jingjizuo);
		fflush(stdin); //清空键盘缓冲区 
		printf("添加的航班信息如下:\n");
		printf("航班号   起飞地    降落地    起飞时间  降落时间  机型  头等舱票价 商务舱票价 经济舱票价 准点率 飞行员1   飞行员2   头等舱座位 商务舱座位 经济舱座位\n");
		printf("%-9s%-10s%-10s%-10s%-10s%-6s%-11d%-11d%-11d%d%%%    -10s%-10s%-11d%-11d%d\n",temp.flightnumber,temp.flightstart,temp.flightend,temp.starttime,temp.endtime,temp.flightmodel,temp.toudengprice,temp.shangwuprice,temp.jingjiprice,temp.flightrate,temp.pilot1,temp.pilot2,temp.toudengzuo,temp.shangwuzuo,temp.jingjizuo); 
		printf("修改请按1，确认添加请按2，放弃添加请按3:");
		scanf("%d",&oprand);
		int date=20160907;
		switch(oprand)
		{
			case 1: continue; break;
			case 2: infile=fopen("hangban.dat","a");  //将添加的航班信息输入到两个文件 
					for(i=0;i<6;i++)
			        	fprintf(infile,"%s %s %s %d %s %s %s %d %d %d %d %s %s %d %d %d 0 0\n",temp.flightnumber,temp.flightstart,temp.flightend,date+i,temp.starttime,temp.endtime,temp.flightmodel,temp.toudengprice,temp.shangwuprice,temp.jingjiprice,temp.flightrate,temp.pilot1,temp.pilot2,temp.toudengzuo,temp.shangwuzuo,temp.jingjizuo);
			        printf("添加成功!"); 
			        fclose(infile);
			        infile=fopen("航班信息.txt","a");
			        fprintf(infile,"%s %s %s %s %s %s %d %d %d %d %s %s %d %d %d 0 0\n",temp.flightnumber,temp.flightstart,temp.flightend,temp.starttime,temp.endtime,temp.flightmodel,temp.toudengprice,temp.shangwuprice,temp.jingjiprice,temp.flightrate,temp.pilot1,temp.pilot2,temp.toudengzuo,temp.shangwuzuo,temp.jingjizuo);
			        return;
			        break;
			case 3: return;
			         
		}
	}
	return;
}

char *generatecompanyorders(char flightcompany[]) //将该管理员所在航空公司的全部用户订单写入文件 
{
	FILE *infile;
    FILE *temp;
	char file_str[1024];
	infile=fopen("总订单.txt","r");
	static char filename[81]; //将文件名声明为静态变量 ，方便传递 
	strcpy(filename,flightcompany);
	char str1[]="orders";
	char str2[]=".txt";
	strcat(str1,str2);
	strcat(filename,str1);
	temp=fopen(filename,"w");
	while(fgets(file_str,sizeof(file_str),infile)) //如果航班公司是订单信息的子字符串，则输入到临时文件夹 
	{
		if(strstr(file_str,flightcompany))
		{
			fprintf(temp,"%s",file_str);
		}
	}
	fclose(temp);
	fclose(infile);
	
	return filename; //返回文件名的首地址 
}

char *generatecompanyinfo(char flightcompany[]) //将该管理员所在航空公司的全部航班信息写入文件 
{
	FILE *infile;
    FILE *temp;
	char file_str[1024];
	infile=fopen("hangban.dat","r");
	static char filename[81]; //将文件名声明为静态变量 ，方便传递 
	strcpy(filename,flightcompany);
	char str1[]="info";
	char str2[]=".txt";
	strcat(str1,str2);
	strcat(filename,str1);
	temp=fopen(filename,"w");
	while(fgets(file_str,sizeof(file_str),infile))//全部读入 
	{
		if(strstr(file_str,flightcompany)) //如果航班公司是航班信息的子字符串，则输入到临时文件夹 
		{
			fprintf(temp,"%s",file_str);
		}
	}
	fclose(temp);
	fclose(infile);
	
	return filename; //返回文件名的首地址 
}

char *searchcompany(char adminid[])//查找管理员所在航空公司 
{
	FILE *infile;
	char file_str[1024];
	static char flightcompany[81]; //将航班公司名声明为静态变量 ，方便传递 
	infile=fopen("管理员信息.txt","r");
	while(fgets(file_str,sizeof(file_str),infile))
	{
		if(strstr(file_str,adminid))
		{
			sscanf(file_str,"%*s %*s %s",flightcompany);
			break;
		}
	}
	fclose(infile);
	return flightcompany; //返回航班公司的首地址 
}

int validpilot(char flightnum[],char pilot[],char flightstart[],char flightend[],char starttimestr[],char endtimestr[]) //时间重复返回1，地点不一致返回2  //验证飞行员飞行时间是否重复，城市地点是否相接 
{
	FILE *infile1;
	FILE *infile2;
	int time[1440]; //将一天的所有分钟转换为数组 
	char tempstr[256];
	char file_str[256];
	int starttime,endtime;
	int rows=0;
	int i,n,k,j,temp;
	int a;
	for(i=0;i<1440;i++)
	  time[i]=0;
	infile1=fopen("航班信息.txt","r");
	infile2=fopen("飞行员临时文件1.txt","w");
	while(fgets(file_str,sizeof(file_str),infile1)) //将含有飞行员姓名的航班信息输出到文件 
	{
		if(strstr(file_str,pilot))
			fprintf(infile2,"%s",file_str);
	}
	fclose(infile1);
	fclose(infile2);
	infile2=fopen("飞行员临时文件1.txt","r");
	while(fgets(tempstr,256,infile2))
	{
    	rows++; //数行数 
	}
    rewind(infile2); //指针重新返回文件开头 
    char searchstarttimestr[rows][81];
    char searchendtimestr[rows][81];
    char filecopy[rows+1][256]; //整个航班信息的二维数组 
    int searchstarttime[rows+1];
    int searchendtime[rows+1];
    for(i=0;i<rows;i++)
    {
    	fgets(tempstr,256,infile2);
    	sscanf(tempstr,"%*s %*s %*s %s %s",searchstarttimestr[i],searchendtimestr[i]);
    	searchstarttime[i]=turntime(searchstarttimestr[i]);
    	searchendtime[i]=turntime(searchendtimestr[i]);
	}
	rewind(infile2); //指针重新返回文件开头 
	for(i=0;i<rows;i++)
	{
		fgets(filecopy[i],256,infile2);
		a=strlen(filecopy[i]);
		filecopy[i][a-1] = '\0';
	}
	fclose(infile2);
	starttime=turntime(starttimestr); //将起飞时间字符串转化为整型数 
	endtime=turntime(endtimestr); //将落地时间字符串转化为整型数 
	for(i=starttime;i<=endtime;i++)
	  time[i]=1;
	for(i=0;i<rows;i++) //一共验证rows次 
	{
		for(n=searchstarttime[i];n<=searchendtime[i];n++) //从起飞时间到飞行时间的时间数组的元素的值 
		{
		  if(time[n]==1) //如果已经为一，则时间段重复 
		  {
		  	remove("飞行员临时文件1.txt"); 
		    return 1; //时间段重复返回1 
		  }
		  else
		    time[n]=1; //如果不为1，则设置为1 
		}
	}
	searchstarttime[rows]=starttime;
	searchendtime[rows]=endtime;
	char strtemp[rows][256];
	strcpy(strtemp[0],flightnum); strcpy(strtemp[1],flightstart);	strcpy(strtemp[2],flightend);	strcpy(strtemp[3],starttimestr); //将输入的航班信息合并为一行 
	strcat(strtemp[0]," ");	strcat(strtemp[1]," ");	strcat(strtemp[2]," ");	strcat(strtemp[3]," ");
	strcat(strtemp[2],strtemp[3]); strcat(strtemp[1],strtemp[2]);  strcat(strtemp[0],strtemp[1]);
	strcpy(filecopy[rows],strtemp[0]);
	for(i=0;i<rows;i++) //按照起飞时间排序航班 
  	{
		k=i;
  		for(j=i+1;j<rows+1;j++) 
		if(searchstarttime[k]>searchstarttime[j]) 
			k=j; 
		if(i!=k) 
		{
			temp=searchstarttime[i]; 
			searchstarttime[i]=searchstarttime[k]; 
			searchstarttime[k]=temp; 
			strcpy(tempstr,filecopy[i]);
			strcpy(filecopy[i],filecopy[k]);
			strcpy(filecopy[k],tempstr);
	    } 
	}
	infile2=fopen("飞行员临时文件2.txt","w");
	for(i=0;i<rows+1;i++)
	{
		fprintf(infile2,"%s\n",filecopy[i]); //将排序后的航班信息输入到文件 
	}
	fclose(infile2);
	infile2=fopen("飞行员临时文件2.txt","r");
	rows++;
	char startcity[rows][81];
	char endcity[rows][81];
	for(i=0;i<rows;i++)
	{
		fgets(tempstr,256,infile2);
    	sscanf(tempstr,"%*s %s %s",startcity[i],endcity[i]);
	}
	for(i=0;i<rows-1;i++)
	{
		if(strcmp(endcity[i],startcity[i+1]) != 0) //如果序航班目的地与当前航班起飞地不一致返回2
		{
			fclose(infile2); 
			remove("飞行员临时文件1.txt");
			remove("飞行员临时文件2.txt"); 
			return 2;
			break;
		}
	}
	
	fclose(infile2);
	return 0; //都符合返回1 
}

int totaltimeshow() //将具体日期时间转换为一个数字 
{
	int yearnum,monnum,daynum;
	int timedisplay;
	
	struct tm *ptr;
  	time_t it;
  	it=time(NULL);
  	ptr=localtime(&it);
  	yearnum=ptr->tm_year+1900;
  	monnum=ptr->tm_mon+1;
  	daynum=ptr->tm_mday;
  	timedisplay=ptr->tm_hour*60 + ptr->tm_min + yearnum*100000000 + monnum*1000000 + daynum*10000;
  	
	return timedisplay;	 
}

int checkfn(char flightnumber[]) //检测输入的航班号是否符合格式要求 
{
	int aa; //计数用 
	if(strlen(flightnumber)!=6)//是否由六位组成 
	return 1;
	for (aa=0;aa<2;aa++)//判断前两位是否是字母 
	{
		if(isalpha(flightnumber[aa])==0)
		return 1;
	}
	for(aa=2;aa<6;aa++)//判断后四位是否是数字 
	{
		if(isdigit(flightnumber[aa])==0)
		return 1;
	}
	return 0;
}

int back2(int i,char id[][81],char code[][81],char temp1[][81],char temp2[][81],char mail[][81])
{
	int b;
	char opcode7[2];
	FILE *inFile;
		inFile=fopen("管理员信息.txt","w");//打开文件待读入 
        for(b=0;b<=i;b++)
        {
            if(inFile==NULL)
            {
                printf("文件打开失败");
                exit(1);
            }
			else
            fprintf(inFile,"%s %s %s %s %s\n",id[b],code[b],temp1[b],temp2[b],mail[b]);//更改文件读入 
        }
        fclose(inFile);
        printf("\n1.返回上级菜单\n2.退出程序\n3.返回主菜单\n请输入相应的操作码");//返回菜单界面 
		fflush(stdin);
		scanf("%s",opcode7);//键入操作码 
		while(1)
	    {
		    if(strcmp(opcode7,"1")!=0&&strcmp(opcode7,"2")!=0&&strcmp(opcode7,"3")!=0)
		    {
			    printf("您输入的操作码有误，请输入正确的操作码");
	    		fflush(stdin);
				scanf("%s",opcode7);	 
	      	}
		    else
				break;
	    }
		if(strcmp(opcode7,"2")==0)//退出程序 
	    exit(1); 
	    if(strcmp(opcode7,"3")==0)//返回主菜单 
	    return 0;
	    if(strcmp(opcode7,"1")==0)//返回上级菜单 
	    return 1;
} 

int back3(int i,char id[][81],char code[][81],char temp1[][81],char temp2[][81],char phonenumber[][81],char mail[][81])
{
	int b;
	char opcode7[2];
	FILE *inFile;
        inFile=fopen("用户信息.txt","w");//打开文件待读入 
        for(b=0;b<=i;b++)
        {
            if(inFile==NULL)
            {
                printf("文件打开失败，请联系管理员");
                exit(1);
            }
			else
            fprintf(inFile,"%s %s %s %s %s %s\n",id[b],code[b],temp1[b],temp2[b],phonenumber[b],mail[b]);//更改文件读入 
        }
        fclose(inFile);
        printf("\n1.返回上级菜单\n2.退出程序\n3.返回主菜单\n请输入相应的操作码");//返回菜单界面 
		scanf("%s",opcode7);//键入操作码 
		fflush(stdin);
		while(1)
	    {
		    if(strcmp(opcode7,"1")!=0&&strcmp(opcode7,"2")!=0&&strcmp(opcode7,"3")!=0)
		    {
			    printf("您输入的操作码有误，请输入正确的操作码");
			    scanf("%s",opcode7);
				fflush(stdin); 
	      	}
		    else
	        	break;
	    } 
		if(strcmp(opcode7,"2")==0)//退出程序
	    exit(1); 
	    if(strcmp(opcode7,"3")==0)//返回主菜单
	    return 0;
	    if(strcmp(opcode7,"1")==0)//返回上级菜单
	    return 1;
}
