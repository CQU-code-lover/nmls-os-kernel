#include "dprint.h"
#include "types.h"
#include "common.h"
#include "string.h"
#include "console.h"
#include "vargs.h"


void insert_str(char *inserted_str,char *inserting_str,uint32_t offset)  //插入辅助函数
{
	char m[100]={0};
	char *afterInsetedPositionStr=m;
	strcpy(afterInsetedPositionStr,inserted_str+offset+2);
	memcpy(inserted_str+offset,inserting_str,strlen(inserting_str));
	*(inserted_str+offset+strlen(inserting_str))='\0';
	strcat(inserted_str,afterInsetedPositionStr);
	//memcpy(*(inserted_str+offset+1+strlen(inserting_str)),afterInsetedPositionStr,strlen(afterInsetedPositionStr));
	return inserted_str;
}

void printk(char *input_str,...)
{
	static char staticArry[100]={0};
	char *output_str=staticArry;
	strcpy(output_str,input_str);
	va_list ptr;
	va_start(ptr,output_str);
	int offset=0;
	for(;*(output_str+offset)!='\0';offset++)
	{
		char *charptr=output_str+offset;
		if (*charptr=='%')
		{
			if (*(charptr+1)=='s')
			{
				char *arg_str_ptr=va_arg(ptr,char*);//此处是否需要复制static数组？

				insert_str(output_str,arg_str_ptr,offset);
				
				offset=offset+strlen(arg_str_ptr)-1;
				
			}
			else if(*(charptr+1)=='d')
			{
				int arg_int=va_arg(ptr,int);

				char *temp_ptr=uintTostring(arg_int);

				insert_str(output_str,temp_ptr,offset);
				
				offset=offset+strlen(temp_ptr)-1;
			}
			else if(*(charptr+1)=='c')
			{
				;
			}
			else if(*(charptr+1)=='H')
			{
				int arg_int=va_arg(ptr,int);

				char*hexstrptr=num2hexstr(arg_int,1);
				
				insert_str(output_str,hexstrptr,offset);

				offset=offset+strlen(hexstrptr)-1;
			} 
			else if(*(charptr+1)=='h')
			{
				int arg_int=va_arg(ptr,int);

				char*hexstrptr=num2hexstr(arg_int,0);
				
				insert_str(output_str,hexstrptr,offset);

				offset=offset+strlen(hexstrptr)-1;
			}
		}
	}
	va_end(ptr);
	console_write(output_str);
}


//输入uint32_t或者char*  使用%d或者%s
//wdnmd 这个可变参有问题！！
void printbasic(char *format_str,char *m)
{
	//va_list ptr_start=NULL;
	char *formatStr=format_str;
	//va_start(ptr_start,format_str);
	//console_write_color(va_arg(ptr_start,char *), rc_black, rc_green);	
	int i=0;
	for(char *head=formatStr;*(head+i)!='\0';i++)
	{
		if (*(head+i)=='%'){
			if(*(head+i+1)=='s')
			{
				//char *str_head=va_arg(&ptr_start,char*);
				insert_str(format_str,m,i);
				
			}
			else if(*(head+i+1)=='d')
			{

			}
			else;
		}
	}
	//console_write_color(formatStr, rc_black, rc_white);
	
}



void printk_color(char *input_str,real_color_t back,real_color_t fore,...)
{
	static char staticArry[100]={0};
	char *output_str=staticArry;
	strcpy(output_str,input_str);
	va_list ptr;
	va_start(ptr,output_str);
	int offset=0;
	for(;*(output_str+offset)!='\0';offset++)
	{
		char *charptr=output_str+offset;
		if (*charptr=='%')
		{
			if (*(charptr+1)=='s')
			{
				char *arg_str_ptr=va_arg(ptr,char*);//此处是否需要复制static数组？

				insert_str(output_str,arg_str_ptr,offset);
				
				offset=offset+strlen(arg_str_ptr)-1;
				
			}
			else if(*(charptr+1)=='d')
			{
				int arg_int=va_arg(ptr,int);

				char *temp_ptr=uintTostring(arg_int);

				insert_str(output_str,temp_ptr,offset);
				
				offset=offset+strlen(temp_ptr)-1;
			}
			else if(*(charptr+1)=='c')
			{
				;
			}
			else if(*(charptr+1)=='H')
			{
				int arg_int=va_arg(ptr,int);

				char*hexstrptr=num2hexstr(arg_int,1);
				
				insert_str(output_str,hexstrptr,offset);

				offset=offset+strlen(hexstrptr)-1;
			} 
			else if(*(charptr+1)=='h')
			{
				int arg_int=va_arg(ptr,int);

				char*hexstrptr=num2hexstr(arg_int,0);
				
				insert_str(output_str,hexstrptr,offset);

				offset=offset+strlen(hexstrptr)-1;
			}
		}
	}
	va_end(ptr);
	console_write_color(output_str,back,fore);
}
