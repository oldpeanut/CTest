#include <stdio.h>

#define MAXSIZE  1000
#define TABWIDTH 8
#define TAB '\t'
#define SPACE ' '

char *fgetline(char *buff, int size, FILE* stream);
int getline(char *buff, int size);
char* detab(const char *s_in, char *s_out);
//char* entab(const char *s_in, char *s_out);

int main()
{
	const int LEN = 100;
	char line[LEN + 1];
	char sout[TABWIDTH * LEN + 1];
	FILE *fout, *fin;
	//fout = fopen("output.txt","w");
	fout = stdout;
	fin = stdin;
	//fin = fopen("in.txt","r");
	while (fgetline(line, LEN, fin) != NULL)
	{
		//fputs(line, fout);
		fputs(detab(line,sout), fout);
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
	return TABWIDTH - (offset % TABWIDTH);
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