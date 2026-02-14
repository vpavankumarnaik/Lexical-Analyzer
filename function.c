#include "header.h"

int iskeyword(char word[])
{
	for(int i=0; keywords_data[i]; i++)
	{
		if(strcmp(keywords_data[i], word) == 0)
		{
			return 1;
		}
	}
	return 0;
}

int iskeyword_non(char word[])
{
	for(int i=0; keywords_non_data[i]; i++)
	{
		if(strcmp(keywords_non_data[i], word) == 0)
		{
			return 1;
		}
	}
	return 0;
}

int isoperator(char ch)
{
	for(int i=0; i < 14; i++)
	{
		if(operators[i] == ch)
		{
			return 1;
		}
	}
	return 0;
}

int issymbol(char ch)
{
	for(int i=0; i < 9; i++)
	{
		if(symbols[i] == ch)
		{
			return 1;
		}
	}
	return 0;
}
