#include "ISS_PROJECT.h"

void run()
{
}

int fetch()
{
}

void decode(uint32_t instr)
{
}

void eval()
{
}

void showRegs()
{
}

int readFile(char* filePath, char** fileContent)
{
  int	fileDesc;
  int	fileSize;
  int	fileRead;
  int	count=0;

	if (filePath == NULL)
	{
		perror("Erreur fichier");
		return EXIT_FAILURE;
	}
	fileDesc = open(filePath, O_RDONLY);
	if (fileDesc == -1)
	{
		perror("Erreur fichier");
		return EXIT_FAILURE;
	}
	else
	{
		fileSize = lseek(fileDesc, 0L, SEEK_END);
		printf("%d octets dans le fichier\n", fileSize);
		lseek(fileDesc, 0L, SEEK_SET);
		//printf("Allocation mémoire\n");
		*fileContent = malloc(fileSize);
		fileRead = read(fileDesc, *fileContent, fileSize);
		//printf("%d octets lus\n", fileRead);
		//printf("%d octets alloués\n", (int)strlen(*fileContent));
		//printf("Lecture du fichier.\nContenu à l'adresse\n[@%lx]:\n%s\n", (long unsigned)fileContent,*fileContent);
		close(fileDesc);
		printf("Fermeture du fichier\n");
	}
	return EXIT_SUCCESS;
}

int howManyLines(char* string)
{
  int	count = 0;
  int	nbLines = 0;
  int	lengthStr = strlen(string);
  char	lineChar[] = {'\n','\0'};

	while (count < lengthStr)
	{
		if (cmpChar(string[count],lineChar))
			nbLines++;
		count++;
	}
	return nbLines;
}

int stringToLines(char* string, char* lines[])
{
	int i = 0;
	char seps[]="\n";
	char * token;
	token = strtok( string, seps );
	while( token != NULL )
	{
		lines[i] = malloc(sizeof(char)*strlen(token));
		strcpy(lines[i], token); 
		token = strtok( NULL, seps );
		i++;
	}
	lines[i] = NULL;
	return i;
}

bool cmpChar(char c, char cmpTabChar[])
{
  int	count = 0;
  int	lengthTab = strlen(cmpTabChar);

	while (count < lengthTab)
	{
		if (c == cmpTabChar[count])
			return true;
		else
			count++;
	}

	return false;
}
