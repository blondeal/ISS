#include <stdlib.h>
#include <fcntl.h>
#include "ISS_PROJECT.h"

char* test (void);

int main( int argc, const char * argv[] )
{
  char*	filePath = "test.hex";
  char*	fileContent;
  char**	fileExtract;
  int	nbInstr;
  int	nbLines;
  int count=0;

	readFile(filePath, &fileContent);
	printf("Contenu du fichier %s :\n%s\n", filePath, fileContent);

	nbLines = howManyLines(fileContent);
	fileExtract = malloc(sizeof(char*)*(nbLines));
	nbInstr = stringToLines(fileContent, fileExtract);
	printf("%d instructions\n",nbInstr);
	for(count=0;count<nbInstr;count++)
	{	
		printf("[%d]",count);
		printf("[@%lx]",(long unsigned)&fileExtract[count]);
		printf("[%d] : ",(int)strlen(fileExtract[count]));
		printf("%s\n", fileExtract[count]);
	}
	//run();
  return 0;
}
