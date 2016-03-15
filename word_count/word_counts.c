#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define BUF_LEN 100
#define INIT_STR 10
#define WORD_INCR 5
int main(void)
{
	char buf[BUF_LEN];
	size_t str_size = INIT_STR;
	char *pStr = (char *)malloc(str_size);
	if (!pStr)
	{
		printf("No more Memory!\n");
		return 1;
	}
	*pStr = '\0';
	char delimiters[] = "\n.,/;:'\"?! ";
	while (true)
	{
		if (!fgets(buf, BUF_LEN, stdin))
		{
			printf("Error String reading!\n");
			free(pStr);
			pStr = NULL;
			return 1;
		}
		if (buf[0] == '\n') break;
		if (strnlen_s(pStr, str_size) + strnlen_s(buf, BUF_LEN) + 1 > str_size)
		{
			str_size =str_size + strnlen_s(buf, BUF_LEN) + 1;
			pStr = realloc(pStr, str_size);
		}
		if (strcat_s(pStr, str_size, buf))
		{
			printf("Error string reading.\n");
			free(pStr);
			pStr = NULL;
			return 1;
		}
	}
	printf("%s", pStr);
	bool new_word = true;
	size_t maxwords = 10;
	char **pWords = calloc(maxwords, sizeof(char *));
	int *pnWords = calloc(maxwords, sizeof(int));
	if (!(pWords && pnWords))
	{
		printf("No more Memory!\n");
		free(pStr);
		pStr = NULL;
		return 1;
	}
	int word_count = 0;

	char *ptr = NULL;
	char *pword = strtok_s(pStr, delimiters, &ptr);
	size_t word_length = 0;
	if (!pword)
	{
		printf("No words found!\n");
		free(pStr);
		free(pWords);
		free(pnWords);
		pStr = NULL;
		pnWords = NULL;
		pWords = NULL;
		return 1;
	}

	/**(pnWords + word_count) = 1;*/
	while (pword)
	{
		for (int i = 0; i < word_count; i++)
		{
			if (strcmp(*(pWords + i), pword)== 0)
			{
				++*(pnWords + i);
				new_word = false;
			}
		}
		if (new_word)
		{
			if (word_count == maxwords)
			{
				maxwords += WORD_INCR;
				pWords = realloc(pWords, maxwords * sizeof(char*));
				pnWords = realloc(pnWords, maxwords* sizeof(int));
			}
			word_length = ptr - pword;
			*(pWords + word_count) = malloc(word_length);
			if (!*(pWords + word_count))
			{
				free(pStr);
				free(pWords);
				free(pnWords);
				pStr = NULL;
				pnWords = NULL;
				pWords = NULL;
				return 1;
			}
			strcpy_s(*(pWords + word_count), word_length, pword);
			*(pnWords + word_count++) = 1;
		}
		else
			new_word = true;
		pword = strtok_s(NULL, delimiters, &ptr);
	}
	for (int i = 0; i < word_count; i++)
	{

		printf("%5s  %d\n", *(pWords + i), *(pnWords + i));
		if (i % 5 == 0) printf("\n");
	}
	for (int i = 0; i < word_count; i++)
	{

		free(*(pWords + i));
		*(pWords + i) = NULL;
	}
	free(pWords);
	pWords = NULL;
	free(pnWords);
	pnWords = NULL;
	free(pStr);
	pStr = NULL;

	return 0;











}