#include "ISS_PROJECT.h"

unsigned regs[NB_REGS];

int	instrNum = 0;
int	reg1     = 0;
int	reg2     = 0;
int	flag     = 0;
int	imm      = 0;
int	nbInstr;
int	nbLines;

char	filePath[256];
char*	fileContent;
char**	fileExtract;

uint32_t*	program;
uint32_t	memory[SIZE_MEM];
uint32_t	actualInstr;

int	running = 1;

int init()
{
  int count;
	
	printf("Fichier à analyser : ");
	scanf("%s", filePath);
	if (readFile(filePath, &fileContent) == EXIT_FAILURE)
	{
		printf("Le fichier n'existe pas.\nArrêt du programme.\n");
		return EXIT_FAILURE;
	}
	//printf("Contenu du fichier %s :\n%s\n", filePath, fileContent);

	nbLines = howManyLines(fileContent);
	fileExtract = malloc(sizeof(char*)*(nbLines));
	
	nbInstr = stringToLines(fileContent, fileExtract);
	printf("%d instructions dans le fichier.\n",nbInstr);
	/*for(count=0;count<nbInstr;count++)
	{	
		printf("[%d]",count);
		printf("[@%lx]",(long unsigned)&fileExtract[count]);
		printf("[%d] : ",(int)strlen(fileExtract[count]));
		printf("%s\n", fileExtract[count]);
	}*/

	printf("Conversion des données hexadécimales vers entier.\n");
	program = malloc(sizeof(uint32_t)*(nbLines));
	for(count=0;count<nbInstr;count++)
	{
		program[count] = strtol(fileExtract[count], NULL, 16);
	}

	actualInstr = 0;

	return EXIT_SUCCESS;
}

void run()
{
  int i;
	
	while(running)
	{
		printf("\nloop\n");
		showRegs();
		decode(program[actualInstr]);
		eval();
		fetch();
	}
}

int fetch()
{
	program[actualInstr++];
}

void decode(uint32_t instr)
{
	instrNum = (instr & 0xF8000000) >>  27;
	reg1     = (instr & 0x7C00000 ) >>  22;
	reg2     = (instr & 0x3E0000  ) >>  17;
	flag     = (instr & 0x10000   ) >>  16;
	imm      = (instr & 0xFFFF  );

	printf("instrNum : %d\nreg1 : %d\nreg2 : %d\nflag : %d\nimm : %d\n", instrNum, reg1, reg2, flag, imm);
}

void eval()
{
	switch(instrNum)
	{
		case STOP:
			printf( "STOP\n" );
			running = 0;
			break;

		case ADD:
			if(flag==0)
			{
				printf( "ADD r%d #%d r%d\n", reg1, imm, reg2);
				regs[ reg1 ] = regs[ reg2 ] - imm;
			}
			else //flag == 1
			{
				if(imm<NB_REGS)
				{
					printf( "ADD r%d r%d r%d\n", reg1, imm, reg2);
					regs[ reg1 ] = regs[ reg2 ] + regs[ imm ];
				}
			}
			break;

		case SUB:
			if(flag==0)
			{
				printf( "SUB r%d #%d r%d\n", reg1, imm, reg2);
				regs[ reg1 ] = regs[ reg2 ] + imm;
			}
			else //flag == 1
			{
				if(imm<NB_REGS)
				{
					printf( "SUB r%d r%d r%d\n", reg1, imm, reg2);
					regs[ reg1 ] = regs[ reg2 ] - regs[ imm ];
				}
			}
			break;

		case MULT:
			if(flag==0)
			{
				printf( "MULT r%d #%d r%d\n", reg1, imm, reg2);
				regs[ reg1 ] = regs[ reg2 ] * imm;
			}
			else //flag == 1
			{
				if(imm<NB_REGS)
				{
					printf( "MULT r%d r%d r%d\n", reg1, imm, reg2);
					regs[ reg1 ] = regs[ reg2 ] * regs[ imm ];
				}
			}
			break;

		case DIV:
			if(flag==0)
			{
				printf( "DIV r%d #%d r%d\n", reg1, imm, reg2);
				regs[ reg1 ] = regs[ reg2 ] / imm;
			}
			else //flag == 1
			{
				if(imm<NB_REGS)
				{
					printf( "DIV r%d r%d r%d\n", reg1, imm, reg2);
					regs[ reg1 ] = regs[ reg2 ] / regs[ imm ];
				}
			}
			break;
		case AND:
			if(flag==0)
			{
				printf( "AND r%d #%d r%d\n", reg1, imm, reg2);
				regs[ reg1 ] = regs[ reg2 ] & imm;
			}
			else //flag == 1
			{
				if(imm<NB_REGS)
				{
					printf( "AND r%d r%d r%d\n", reg1, imm, reg2);
					regs[ reg1 ] = regs[ reg2 ] & regs[ imm ];
				}
			}
			break;
		case OR:
			if(flag==0)
			{
				printf( "OR r%d #%d r%d\n", reg1, imm, reg2);
				regs[ reg1 ] = regs[ reg2 ] | imm;
			}
			else //flag == 1
			{
				if(imm<NB_REGS)
				{
					printf( "OR r%d r%d r%d\n", reg1, imm, reg2);
					regs[ reg1 ] = regs[ reg2 ] | regs[ imm ];
				}
			}
			break;
		case XOR:
			if(flag==0)
			{
				printf( "XOR r%d #%d r%d\n", reg1, imm, reg2);
				regs[ reg1 ] = regs[ reg2 ] | imm;
			}
			else //flag == 1
			{
				if(imm<NB_REGS)
				{
					printf( "XOR r%d r%d r%d\n", reg1, imm, reg2);
					regs[ reg1 ] = regs[ reg2 ] ^ regs[ imm ];
				}
			}
			break;
		case SHL:

			printf( "SHL r%d #%d r%d\n", reg1, imm, reg2);
			regs[ reg1 ] = regs[ reg2 ] << imm;

      // faire un warning en cas de depassement
			break;

		case SHR:
			printf( "SHL r%d #%d r%d\n", reg1, imm, reg2);
			regs[ reg1 ] = regs[ reg2 ] >> imm;

			//faire un warning en cas de depassement
			break;

		case	SLT:
			if (flag == 0)	//	imm est une valeur constante
			{
				printf("SLT r%d #%d r%d\n", reg1, imm, reg2);
				if (regs[reg1] < imm)
					regs[reg2] = 1;
				else
					regs[reg2] = 0;
			}
			else 		//	imm est un registre
			{
				printf("SLT r%d r%d r%d\n", reg1, imm, reg2);
				if (imm < NB_REGS) 	//	Vérification pour ne pas chercher un registre inexistant
				{
					if (regs[reg1] < regs[imm])
						regs[reg2] = 1;
					else
						regs[reg2] = 0;
				}
				else
					printf("Erreur registre : adresse inexistante !\n");
			}
			break;

		case	SLE:
			if (flag == 0)	//	imm est une valeur constante
			{
				printf("SLE r%d #%d r%d\n", reg1, imm, reg2);
				if (regs[reg1] <= imm)
					regs[reg2] = 1;
				else
					regs[reg2] = 0;
			}
			else 		//	imm est un registre
			{
				printf("SLE r%d r%d r%d\n", reg1, imm, reg2);
				if (imm < NB_REGS) 	//	Vérification pour ne pas chercher un registre inexistant
				{
					if (regs[reg1] <= regs[imm])
						regs[reg2] = 1;
					else
						regs[reg2] = 0;
				}
				else
					printf("Erreur registre : adresse inexistante !\n");
			}
			break;

		case	SEQ:
			if (flag == 0)	//	imm est une valeur constante
			{
				printf("SEQ r%d #%d r%d\n", reg1, imm, reg2);
				if (regs[reg1] = imm)
					regs[reg2] = 1;
				else
					regs[reg2] = 0;
			}
			else 		//	imm est un registre
			{
				printf("SEQ r%d r%d r%d\n", reg1, imm, reg2);
				if (imm < NB_REGS) 	//	Vérification pour ne pas chercher un registre inexistant
				{
					if (regs[reg1] = regs[imm])
						regs[reg2] = 1;
					else
						regs[reg2] = 0;
				}
				else
					printf("Erreur registre : adresse inexistante !\n");
			}
			break;

		case	LOAD:	
			if (flag == 0)	//	imm est une valeur constante
			{
				printf("LOAD r%d #%d r%d\n", reg1, imm, reg2);
				if ( (regs[reg1] + imm) < SIZE_MEM)
					regs[reg2] = memory[regs[reg1] + imm];
			}
			else 		//	imm est un registre
			{
				printf("LOAD r%d r%d r%d\n", reg1, imm, reg2);
				if (imm < NB_REGS)
				{
					if ( (regs[reg1] + regs[imm]) < SIZE_MEM)
						regs[reg2] = memory[regs[reg1] + regs[imm]];
					else
						printf("Erreur mémoire : adresse inexistante !\n");
				}
				else
					printf("Erreur registre : adresse inexistante !\n");
			}
			break;

		case	STORE:
			if (flag == 0)	//	imm est une valeur constante
			{
				printf("STORE r%d #%d r%d\n", reg1, imm, reg2);
				if ( (regs[reg1] + imm) < SIZE_MEM)
					 memory[regs[reg1] + imm] = regs[reg2];
				else
					printf("Erreur mémoire : adresse inexistante !\n");
			}
			else 		//	imm est un registre
			{
				printf("STORE r%d r%d r%d\n", reg1, imm, reg2);
				if (imm < NB_REGS)
				{
					if ( (regs[reg1] + regs[imm]) < SIZE_MEM)
						memory[regs[reg1] + regs[imm]] = regs[reg2];
					else
						printf("Erreur mémoire : adresse inexistante !\n");
				}
				else
					printf("Erreur registre : adresse inexistante !\n");
			}
			break;

		case	JMP:
			printf("JMP #%d r%d\n", imm, reg1);
			if (imm < nbInstr)
			{
				regs[reg1] = actualInstr + 1;
				actualInstr = imm - 1;		//	Décrémentation car incrémentation par fetch()
			}
			else
				printf("Erreur mémoire : adresse inexistante !\n");
			break;

		case	BRAZ:
			printf("BRAZ r%d @%d\n", reg1, imm);
			if (regs[reg1] == 0)
			{
				if (imm < nbInstr)
				{
					actualInstr = imm - 1;		//	Décrémentation car incrémentation par fetch()
				}
				else
					printf("Erreur mémoire : adresse inexistante !\n");
			}
			printf("\n");
			break;

		case	BRANZ:
			printf("BRANZ r%d @%d\n", reg1, imm);
			if (regs[reg1] != 0)
			{
				if (imm < nbInstr)
				{
					actualInstr = imm - 1;		//	Décrémentation car incrémentation par fetch()
				}
				else
					printf("Erreur mémoire : adresse inexistante !\n");
			}
			break;

		case	SCALL:
			printf("SCALL %d\n", imm);
			printf("\n");
			break;

		default:
			printf("Commande inconnue\n");
			break;
	}
}

void showRegs()
{
  int i;
	
	printf("Affichage des registres en base 0x :\n");
	for( i=0; i<NB_REGS; i++ )
	{
		printf( "REG[%02d] : %08X\t", i, regs[ i ] );
		if(i%4 == 3)
			printf("\n");
	}
	printf( "\n" );
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
