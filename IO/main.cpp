#include <stdio.h>

#define MAXSIZE  1000
#define TABSTOP 8
#define TAB '\t'
#define SPACE ' '

char *fgetline(char *buff, int size, FILE* stream);
int getline(char *buff, int size);
char* detab(const char *s_in, char *s_out);
char* entab(const char *s_in, char *s_out, int *l_in, int *l_out);

int main()
{
	const int LEN = 200;
	char line[MAXSIZE];
	char sout[MAXSIZE];
	FILE *fout, *fin;
	//fout = fopen("output.txt","w");
	fout = stdout;
	fin = stdin;
	//fin = fopen("in.txt","r");
	while (fgetline(line, 200, fin) != NULL)
	{
		//fputs(line, fout);
		int in = 0, out = 0;
		//fputs(detab(line, sout), fout);
		fputs(entab(line, sout, &in, &out), fout);
		fprintf(fout, "%d,%d\n", in, out);
	}
	fclose(fout);
	fclose(fin);
	return 0;
}


//----------------------------------------------------------------------
// Autor:    Peanut
// Describe: fgets重写版本
//----------------------------------------------------------------------
char *fgetline(char *buff, int size, FILE* stream)
{
	int i,a;
	i = 0;
	while (i < size - 1 && (a = getc(stream)) != EOF && a != '\n')
	{
		buff[i++] = a; 
	}
	
	if (i == 0 && a == EOF)
	{
		return NULL;
	}
	if (a == '\n' || a == EOF)
		buff[i++] = '\n';
	buff[i] = '\0';
	return buff;
}

//----------------------------------------------------------------------
// Autor:    Peanut
// Describe: 从stdin读取一行
//----------------------------------------------------------------------
int getline(char *buff, int size)
{
	int i,a;
	for (i = 0; i < size - 1 && (a = getchar()) != EOF && a != '\n'; ++i)
	{
		buff[i] = a;
	}
	if (a == '\n')
	{
		buff[i++] = a;
	}
	buff[i] = '\0';
	return i;
}


//----------------------------------------------------------------------
// Function: detab
// Autor:    Peanut
// Describe: 把制表符替换为适当数目的空格 
//----------------------------------------------------------------------
int gettabwidth(int offset)
{
	return TABSTOP - (offset % TABSTOP);
};

char* detab(const char *s_in, char* s_out)
{
	int i,offset,tabwidth,a;
	i = 0;
	offset = 0;
	while ((a = s_in[i++]) != '\0')
	{
		if (a == TAB)
		{
			tabwidth = gettabwidth(offset);
			while ( tabwidth-- )
			{
				s_out[offset++] = SPACE;
			}
		}
		else
			s_out[offset++] = a;
	}
	s_out[offset] = '\0';
	return s_out;
}

//----------------------------------------------------------------------
// Function: entab
// Autor:    Peanut
// Describe: 将空格串替换为最少的制表符和空格。
//			 l_in(out):输入字符串长度；l_out(out):输出字符串长度
//----------------------------------------------------------------------
char* entab(const char *s_in, char *s_out, int *l_in, int *l_out)
{
	int i,x,a;
	int offset;
	int spaces;
	
	i = 0, x = 0, offset = 0, spaces = 0;
	while ((a = s_in[i++]) != '\0')
	{
		if (a == SPACE)
		{
			++spaces;
		} 
		//else if (spaces == 0)
		//{
		//	s_out[x++] = a;
		//	++offset;
		//}
		else if (spaces == 1)
		{
			s_out[x++] = ' ';
			s_out[x++] = a;
			offset += 2;
			spaces = 0;
		}
		else
		{
			while (offset/TABSTOP != (offset+spaces)/TABSTOP)
			{
				s_out[x++] = '\t';
				--spaces;
				++offset;
				while (offset%TABSTOP != 0)
				{
					--spaces;
					++offset;
				}
			}
			while (spaces > 0)
			{
				s_out[x++] = ' ';
				--spaces;
				++offset;
			}
			s_out[x++] = a;
			++offset;
		}
	}
	s_out[x] = '\0';
	*l_in = i - 1;
	*l_out = x;
	return s_out;
}