#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <math.h>
#include<string.h>

int continuar = 1;

struct Bilhete 
{
    int ID;
    char email[100];
    int tema;
    char estado[20];
};

typedef struct 
{
    float exposicao;
    int nota;
} Avaliacao;

typedef struct data  DATA;

struct data
{
	int dia;
	int mes;
	int ano;	
};

typedef struct registro  REGISTRO;

struct registro
{
	char nome[40];
	char email[50];
	char telefone[14];
	char status;
	DATA aniv;
};

void cabecalho()
{
	system("cls");
	
	printf("-------------------------------------");
	printf("\n Administador - Museu tematica\n");
	printf("-------------------------------------\n");
	
}


void listar()
{
	cabecalho();
	
	FILE * arquivo;
	
	 REGISTRO r1;
		
	arquivo = fopen("usuarios.txt", "rb");
	
	while(fread(&r1, sizeof(REGISTRO),1,arquivo) == 1)
	{
	
			printf(" Nome: %s ",r1.nome);
			printf("\n Email: %s ", r1.email);
			printf("\n Telefone: %s", r1.telefone);
			if(r1.aniv.dia < 10 && r1.aniv.mes < 10)
			{
				printf("\n Aniversario: 0%d/0%d/%d \n", r1.aniv.dia, r1.aniv.mes, r1.aniv.ano);		
			}
			else if(r1.aniv.dia < 10)
			{
				printf("\n Aniversario: 0%d/%d/%d \n", r1.aniv.dia, r1.aniv.mes, r1.aniv.ano);
	
			}	
			else if(r1.aniv.mes < 10)
			{
				printf("\n Aniversario: %d/0%d/%d \n", r1.aniv.dia, r1.aniv.mes, r1.aniv.ano);
			}
			else
			{
				printf("\n Aniversario: %d/%d/%d \n", r1.aniv.dia, r1.aniv.mes, r1.aniv.ano);
			}
		
		printf("-------------------------------------\n");
	}
	
	
	system("pause");
		
	
	fclose(arquivo);
}

void bilhete()
{
	cabecalho();
	
	struct Bilhete bilhete;
	
	FILE *arquivoB;

    arquivoB = fopen("bilhetes.bin", "ab+");
    
    rewind(arquivoB);
    
    printf("\n");
    
    printf(" Conte�do do arquivo de bilhetes:\n ");

    while (fread(&bilhete, sizeof(struct Bilhete), 1, arquivoB) == 1) 
	{
		printf("\n");
        printf("   ID: %d | Email: %s | Tema: %d | Estado: %s\n", bilhete.ID, bilhete.email, bilhete.tema, bilhete.estado);

    }
    
    printf("\n ");
    
	system("pause");	
}

void mostrarAvaliacoes() 
{
	cabecalho();
	
    FILE *arquivoC;

    arquivoC = fopen("avaliacoes.bin", "rb");

    Avaliacao avaliacao;

    printf(" Conte�do do arquivo de avalia��es:\n ");

    while (fread(&avaliacao, sizeof(Avaliacao), 1, arquivoC) == 1) 
	{
		printf("\n");
        printf(" Exposi��o: %.2f, Nota: %d\n ", avaliacao.exposicao, avaliacao.nota);
    }

    fclose(arquivoC);
    
	printf("\n ");
    system("pause");
}

void Estatisticas_Bilhetes() 
{
	FILE *arquivoD;

    arquivoD = fopen("bilhetes.bin", "ab+");
    
    struct Bilhete bilhete;
    int total_bilhetes = 0;
    int total_tipo1 = 0, total_tipo2 = 0, total_tipo3 = 0;
    int total_usados = 0, total_disponiveis = 0;
    int usados_tipo1 = 0, usados_tipo2 = 0, usados_tipo3 = 0;
    int disponiveis_tipo1 = 0, disponiveis_tipo2 = 0, disponiveis_tipo3 = 0;

    rewind(arquivoD);

    // Calcula as estat�sticas
    while (fread(&bilhete, sizeof(struct Bilhete), 1, arquivoD) == 1) 
	{
        total_bilhetes++;

        switch (bilhete.tema) 
		{
            case 1:
                total_tipo1++;
                break;
            case 2:
                total_tipo2++;
                break;
            case 3:
                total_tipo3++;
                break;
        }

        if (strcmp(bilhete.estado, "Usado") == 0) 
		{
            total_usados++;

            switch (bilhete.tema) {
                case 1:
                    usados_tipo1++;
                    break;
                case 2:
                    usados_tipo2++;
                    break;
                case 3:
                    usados_tipo3++;
                    break;
            }
        } else if (strcmp(bilhete.estado, "Disponivel") == 0) 
		{
            total_disponiveis++;

            switch (bilhete.tema) {
                case 1:
                    disponiveis_tipo1++;
                    break;
                case 2:
                    disponiveis_tipo2++;
                    break;
                case 3:
                    disponiveis_tipo3++;
                    break;
            }
        }
    }

    printf(" Total de Bilhetes Comprados: %d\n", total_bilhetes);
    printf("\n");
    printf(" Total de Bilhetes Tipo 1: %d\n", total_tipo1);
    printf(" Total de Bilhetes Tipo 2: %d\n", total_tipo2);
    printf(" Total de Bilhetes Tipo 3: %d\n", total_tipo3);
    printf("\n");
    printf(" Total de Bilhetes Usados: %d\n", total_usados);
    printf("\n");
    printf(" Total de Bilhetes Dispon�veis: %d\n", total_disponiveis);
    printf("\n");

    if (total_bilhetes > 0) {
        printf(" Rela��o entre os tipos:\n");
        printf("\n");
        printf(" Tipo 1: %.2f%%\n", (float)total_tipo1 / total_bilhetes * 100);
        printf(" Tipo 2: %.2f%%\n", (float)total_tipo2 / total_bilhetes * 100);
        printf(" Tipo 3: %.2f%%\n", (float)total_tipo3 / total_bilhetes * 100);
        printf("\n");

        if (total_usados + total_disponiveis > 0) 
		{
            printf(" Rela��o entre Usados e Dispon�veis: %.2f%% usados, %.2f%% dispon�veis\n",
                   (float)total_usados / (total_usados + total_disponiveis) * 100,
                   (float)total_disponiveis / (total_usados + total_disponiveis) * 100);
            printf("\n");
            
        } 
		else 
		{
            printf(" Nenhum bilhete comprado ainda.\n");
        }

        if (total_tipo1 > 0) 
		{
            printf(" Rela��o de Bilhetes Tipo 1 Usados/Dispon�veis: %.2f%% usados, %.2f%% dispon�veis\n",
                   (float)usados_tipo1 / total_tipo1 * 100,
                   (float)disponiveis_tipo1 / total_tipo1 * 100);
            printf("\n");
        }

        if (total_tipo2 > 0) 
		{
            printf(" Rela��o de Bilhetes Tipo 2 Usados/Dispon�veis: %.2f%% usados, %.2f%% dispon�veis\n",
                   (float)usados_tipo2 / total_tipo2 * 100,
                   (float)disponiveis_tipo2 / total_tipo2 * 100);
        	printf("\n");
        }

        if (total_tipo3 > 0) 
		{
            printf(" Rela��o de Bilhetes Tipo 3 Usados/Dispon�veis: %.2f%% usados, %.2f%% dispon�veis\n",
                   (float)usados_tipo3 / total_tipo3 * 100,
                   (float)disponiveis_tipo3 / total_tipo3 * 100);
            printf("\n ");
        }
    }
}

void mostrarRelatorioAvaliacoes() 
{
    
	FILE *arquivoE;

    arquivoE = fopen("avaliacoes.bin", "rb");

    int totalAvaliacoes = 0;
    int contagemExposicoes[6] = {0}; 
    float somaNotasExposicao[6] = {0}; 
    int i;

    Avaliacao avaliacao;

    while (fread(&avaliacao, sizeof(Avaliacao), 1, arquivoE) == 1) {
        totalAvaliacoes++;

        contagemExposicoes[(int)avaliacao.exposicao]++;

        somaNotasExposicao[(int)avaliacao.exposicao] += avaliacao.nota;
    }

    fclose(arquivoE);
    
    cabecalho();

    printf(" Relat�rio de Avalia��es:\n");
    printf("\n");
    printf(" Total de Avalia��es: %d\n", totalAvaliacoes);
    printf("\n");

    for (i = 1; i <= 5; i++) 
	{
        if (contagemExposicoes[i] > 0) 
		{
            printf(" Exposi��o %.0f: %d avalia��o(�es)\n", (float)i, contagemExposicoes[i]);

            float mediaNotas = somaNotasExposicao[i] / contagemExposicoes[i];
            printf(" M�dia de Notas: %.2f\n", mediaNotas);
            printf("\n");
        }
    }
}

void estatisticas()
{
	cabecalho();
	
	printf("\n");
	
	Estatisticas_Bilhetes();
	
	system("pause");
	
	mostrarRelatorioAvaliacoes();	
	
	printf("\n ");
        
    system("pause");
}

void sair()
{
    
	printf("\n");
    
	printf(" Volte sempre\n");
    
    printf("\n ");
        
    system("pause");


    continuar = 0;
}

int main()
{
    int opcao;
    
    
    setlocale(LC_ALL, "Portuguese");

    while(continuar)
    {
    	
		cabecalho();

        printf(" 1. Listar usuario\n");
        printf(" 2. Listar bilhetes\n");
        printf(" 3. Listar avalia��es\n");
        printf(" 4. Mostrar estatisticas\n");

        printf(" 5. Sair\n\n ");
        
        fflush(stdin);

        scanf("%d", &opcao);

          switch(opcao)
          {
              case 1:
                  listar();
                  break;
                  
              case 2:
                  bilhete();
                  break;

              case 3:
              	mostrarAvaliacoes();
              	break;
              	
              case 4:
              	estatisticas();
              	break;
              	
              case 5:
              	sair();
                break;

              default:
              	  printf("\n");
              	  
                  printf(" Digite uma opcao valida\n");
                  
                  printf("\n ");
                  
                  system("pause");
                  
          }
    }
	
}
