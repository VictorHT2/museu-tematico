#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int continuar = 1, bilhete1 = 0, bilhete2 = 0, bilhete3 = 0, opc = 0;
char email[50],emailB[50];

void cabecalho()
{
	system("cls");
	
	printf("-------------------------------------");
	printf("\n\t Museu tematica\n");
	printf("-------------------------------------\n");
	
}

struct Credenciais 
{
    char senha[20];
    char email[50];
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

struct Bilhete {
    int ID;
    char email[100];
    int tema;
    char estado[20];
};

struct registro
{
	char nome[40];
	char email[50];
	char telefone[14];
	char status;
	DATA aniv;
};

int verificar_credenciais(const char *senha, const char *email) 
{
    FILE *arquivoG;
    struct Credenciais credenciais;

    arquivoG = fopen("senhas.bin", "rb");

    while (fread(&credenciais, sizeof(struct Credenciais), 1, arquivoG) == 1) 
	{
        if (strcmp(credenciais.senha, senha) == 0 && strcmp(credenciais.email, email) == 0) 
		{
            fclose(arquivoG);
            return 1; 
        }
    }
    
    fclose(arquivoG);

    return 0;
}

void avaliacao(float exposicao) 
{
	int nota = 0;
	
	printf("\n");
	
	printf("\n Digite a nota (de 1 a 5): ");
    scanf("%d", &nota);
	
    FILE *arquivoC;

    arquivoC = fopen("avaliacoes.bin", "ab");

    Avaliacao avaliacao;
    
    avaliacao.exposicao = exposicao;
    avaliacao.nota = nota;

    fwrite(&avaliacao, sizeof(Avaliacao), 1, arquivoC);

    fclose(arquivoC);
}

int verifica_cadastro()
{
	int escolha;
	char senha[20];

    printf(" J� possui cadastro? (SIM = 1 / N�O = 2) \n ");
    scanf("%d", &escolha);

    
    if(escolha == 1)
    {
    	
    	fflush(stdin);
    	
    	int ct = 1;
    	
    	while(ct == 1)
    	{
    		cabecalho();
    	
	    	printf(" Digite seu Email: ");
	    	gets(email);
	    	
	    	printf(" Digite sua senha: ");
	    	gets(senha);
	    	
	    	
	    	
	    	if (verificar_credenciais(senha, email)) 
			{
	        	printf("\n Credenciais v�lidas. Acesso permitido.\n");
	        	ct = 0;
	        	
	        	strcpy(emailB,email);
	        	
	        	system("pause");
	    	} 
			else 
			{
	       		printf(" Credenciais inv�lidas. Acesso negado.\n ");
	       		system("pause");
	    	}
		}
    	
    	FILE * arquivo;
	
	 	REGISTRO r1;
		
		arquivo = fopen("usuarios.txt", "rb");
	
		while(fread(&r1, sizeof(REGISTRO),1,arquivo) == 1)
		{
			if(strcmp( email, r1.email) == 0)
			{
				cabecalho();
				
				printf("\n Nome: %s ",r1.nome);
				printf("\n Email: %s ", r1.email);
				printf("\n Telefone: %s", r1.telefone);
				
				if(r1.aniv.dia < 10 && r1.aniv.mes < 10)
				{
					printf("\n Aniversario: 0%d/0%d/%d", r1.aniv.dia, r1.aniv.mes, r1.aniv.ano);		
				}
				else if(r1.aniv.dia < 10)
				{
				printf("\n Aniversario: 0%d/%d/%d", r1.aniv.dia, r1.aniv.mes, r1.aniv.ano);
	
				}
				else if(r1.aniv.mes < 10)
				{
					printf("\n Aniversario: %d/0%d/%d", r1.aniv.dia, r1.aniv.mes, r1.aniv.ano);
				}
				else
				{
					printf("\n Aniversario: %d/%d/%d", r1.aniv.dia, r1.aniv.mes, r1.aniv.ano);
				}
				
				char certo;
				
				printf("\n As informa��es conferem? Se sim escreva 's' para continuar: ");
				scanf("%c", &certo);
			
			
				if(certo == 's')
				{
					return 1;
					break;
				}

			}
		}
		
		fclose(arquivo);
    	
	}
	else
	{
		return 0;		
	}
    
}

int Gerar_ID() 
{

    return rand() % 1000 + 1;
}

void Cadastro_de_Bilhete(int tema) 
{
	FILE *arquivoB;
	

	arquivoB = fopen("bilhetes.bin", "ab+");
	
    struct Bilhete bilhete1;

    strcpy(bilhete1.email, email);
    

    bilhete1.ID = Gerar_ID();

    bilhete1.tema = tema;

    strcpy(bilhete1.estado, "Disponivel");

    fwrite(&bilhete1, sizeof(struct Bilhete), 1, arquivoB);
    
    fclose(arquivoB);

}

void Ver_Bilhete() 
{
	FILE *arquivoB;

	arquivoB = fopen("bilhetes.bin", "ab+");

    struct Bilhete bilhete;

    while (fread(&bilhete, sizeof(struct Bilhete), 1, arquivoB) == 1) 
	{
        if (strcmp(bilhete.email, email) == 0 && strcmp(bilhete.estado, "Disponivel") == 0) 
		{
            if (bilhete.tema == 1) 
			{
                bilhete1 = bilhete1 + 1;
            } 
			else if (bilhete.tema == 2) 
			{
                bilhete2 = bilhete2 + 1;
            } 
			else if (bilhete.tema == 3) 
			{
                bilhete3 = bilhete3 + 1;
            }
        }
    }
    
	fclose(arquivoB);

}

void Usar_Bilhete(const char* email, int tema) {
    FILE *arquivoB, *tempArquivoB;

    if ((arquivoB = fopen("bilhetes.bin", "rb")) == NULL) {
        perror("Erro ao abrir o arquivo bilhetes.bin");
        return;
    }

    tempArquivoB = fopen("temp_bilhetes.bin", "wb");
    if (tempArquivoB == NULL) {
        perror("Erro ao criar o arquivo tempor�rio");
        fclose(arquivoB);
        return;
    }

    struct Bilhete bilhete;

    while (fread(&bilhete, sizeof(struct Bilhete), 1, arquivoB) == 1) {
        if (strcmp(bilhete.email, email) == 0 && bilhete.tema == tema && strcmp(bilhete.estado, "Disponivel") == 0) {
            // Criar um novo bilhete com estado "Usado"
            struct Bilhete novoBilhete = {bilhete.ID, "", tema, "Usado"};
            strncpy(novoBilhete.email, email, sizeof(novoBilhete.email) - 1);
            novoBilhete.email[sizeof(novoBilhete.email) - 1] = '\0';  // Garantir termina��o nula
            fwrite(&novoBilhete, sizeof(struct Bilhete), 1, tempArquivoB);
        } else {
            // Copiar bilhetes n�o modificados para o arquivo tempor�rio
            fwrite(&bilhete, sizeof(struct Bilhete), 1, tempArquivoB);
        }
    }

    fclose(arquivoB);
    fclose(tempArquivoB);

    // Remover o arquivo original
    if (remove("bilhetes.bin") != 0) {
        perror("Erro ao remover o arquivo original");
        return;
    }
    // Renomear o arquivo tempor�rio para o original
    if (rename("temp_bilhetes.bin", "bilhetes.bin") != 0) {
        perror("Erro ao renomear o arquivo tempor�rio");
    }
}

void ca_senha(const char *senha, const char *email)
{
	FILE *arquivoF;

    struct Credenciais credenciais;
  
	strncpy(credenciais.senha, senha, sizeof(credenciais.senha) - 1);
    strncpy(credenciais.email, email, sizeof(credenciais.email) - 1);
	
 	arquivoF = fopen("senhas.bin", "ab+");

    fwrite(&credenciais, sizeof(struct Credenciais), 1, arquivoF);

    fclose(arquivoF);

}

void cadastro()
{
	cabecalho();
	
	int verifica = verifica_cadastro();
	
	if(verifica == 0)
	{
		
		FILE * arquivo;
		
		arquivo = fopen("usuarios.txt", "ab");
		
		REGISTRO r1;
		
		cabecalho();
		
		fflush(stdin);
			
		char certo;
			
		printf("\n Informe seu Nome: ");
		gets(r1.nome);
			
		fflush(stdin);
			
		printf("\n Informe seu Email: ");
		gets(r1.email);
			
		fflush(stdin);
			
		printf("\n Informe seu Telefone: ");
		gets(r1.telefone);
			
		fflush(stdin);
			
		printf("\n Informe o seu dia de nascimento: ");
		scanf("%d", &r1.aniv.dia);
			
		printf("\n Informe o seu m�s de nascimento: ");
		scanf("%d", &r1.aniv.mes);
			
		printf("\n Informe o seu ano de nascimento: ");
		scanf("%d", &r1.aniv.ano);
		
		
		cabecalho();
		
		char senha[20];
		    	
    	printf(" Digite sua senha: ");
    	scanf("%s", senha);
    	
    	ca_senha(senha, r1.email);
    	

	   
	   fwrite(&r1, sizeof(REGISTRO),1, arquivo);
	   
	   printf("\n Arquivo salvo com sucesso !!! ");
	   
	   fclose(arquivo);
		
	}
	else
	{
		printf("\n J� tendo um cadastro, compre um ingresso e entre no museu.");
	}
	

    printf("\n ");

    system("pause");

}

void compra()
{
	
	cabecalho();
	    
	int verifica = verifica_cadastro();
	
	if(verifica == 1)
	{
		FILE * arquivo;
	
	 	REGISTRO r1;
		
		arquivo = fopen("usuarios.txt", "rb");
	
		while(fread(&r1, sizeof(REGISTRO),1,arquivo) == 1)
		{
			if(strcmp( email, r1.email) == 0)
			{
				cabecalho();
				
				if(r1.aniv.dia < 10 && r1.aniv.mes < 10)
				{
					printf("\n Seu aniversario � Aniversario: 0%d/0%d/%d", r1.aniv.dia, r1.aniv.mes, r1.aniv.ano);		
				}
				else if(r1.aniv.dia < 10)
				{
				printf("\n Seu aniversario � Aniversario: 0%d/%d/%d", r1.aniv.dia, r1.aniv.mes, r1.aniv.ano);
	
				}
				else if(r1.aniv.mes < 10)
				{
					printf("\n Seu aniversario � Aniversario: %d/0%d/%d", r1.aniv.dia, r1.aniv.mes, r1.aniv.ano);
				}
				else
				{
					printf("\n Seu aniversario � Aniversario: %d/%d/%d", r1.aniv.dia, r1.aniv.mes, r1.aniv.ano);
				}
				
				  
				  struct tm *data_hora_atual;     
				   
  				  time_t segundos;
  
  				  time(&segundos);   
  
 				  data_hora_atual = localtime(&segundos);
 				  
 				  int anoatual = data_hora_atual->tm_year+1900;
  				  int mesatual = data_hora_atual->tm_mon+1;
  				  int diaatual = data_hora_atual->tm_mday;
				
				printf("\n Data atual: %d/%d/%d", diaatual, mesatual, anoatual);
  				  
  				  
  				  int idade = anoatual - r1.aniv.ano;
  				  
  				    if (mesatual < r1.aniv.mes) 
					{
        				idade--;
    				}
    				else if(mesatual == r1.aniv.mes)
    				{
    					if (diaatual < r1.aniv.dia) 
						{
        					idade--;
    					}
					}
					
					printf("\n Voc� tem %d",idade);
					
					if(idade >= 60)
					{
						printf("\n Voc� paga meia na compra de um ingresso.\n \n ");						
					}
					else if(idade >= 3 && idade <= 12)
					{
						printf("\n Voc� paga meia na compra de um ingresso.\n \n ");	
					}
					else
					{
						
						int escolhaB;
						
						printf("\n Voc� n�o paga meia na compra de um ingresso por idade.\n \n ");
						
						printf("\n Voc� possui alguma defifiencia ou alguma condi��o especial? (SIM = 1 / N�O = 2)\n \n ");
						
    					scanf("%d", &escolhaB);

						if(escolhaB == 1)
						{
							printf("\n Voc� paga meia na compra de um ingresso.\n \n ");	

						}
						else
						{
							printf("\n Voc� paga inteira na compra de um ingresso.\n \n ");	
	
						}
					}
					
  				  system("pause");
		
				
				break;
			}

		}
			
		cabecalho();
		
		int ingresso;
		
		printf(" Ingresso da Copa do Mundo pressione 1.\n");
		printf(" Ingresso das Olimpiadas pressione 2.\n");
		printf(" Ingresso de Astrologia pressione 3.\n");
		printf(" Ingresso de ambos pressione 4.\n \n ");
					
		scanf("%d", &ingresso);
					
		if(ingresso == 1)
		{
			continuar = 1;
			
			Cadastro_de_Bilhete(1);
			
			bilhete1++;	
			
			cabecalho();
			printf(" Voc� comprou um ingresso da Copa do Mundo \n ");			
		}
		else if(ingresso == 2)
		{
			continuar = 1;
			
			Cadastro_de_Bilhete(2);
			
			bilhete2++;
			
			cabecalho();
			printf(" Voc� comprou um ingresso das Olimpiadas \n ");
		}
		else if(ingresso == 3)
		{
			continuar = 1;
			
			Cadastro_de_Bilhete(3);
			
			bilhete3++;
			
			cabecalho();
			printf(" Voc� comprou um ingresso de Astrologia.");
		}
		else if(ingresso == 4)
		{
			continuar = 1;
			
			bilhete1++;
			bilhete2++;
			bilhete3++;
			
			Cadastro_de_Bilhete(1);
			Cadastro_de_Bilhete(2);
			Cadastro_de_Bilhete(3);
			
			cabecalho();
			printf(" Voc� comprou um ingresso da Copa do Mundo, Olimpiadas e de Astrologia.");

		}
	}	
	else
	{
		printf(" V� para aba de cadastro !!");	
	}
    
    printf("\n ");

    system("pause");

}

void entrar()
{
	Ver_Bilhete();
	cabecalho();
			
	if(bilhete1 != 0 || bilhete2 != 0)
	{
		int escolha;
		printf(" Voc� gostaria de entrar na exposi��o da Copa do Mundo = 1 ou das Olimpiadas = 2 ou de Astrologia = 3 \n ");
    	scanf("%d", &escolha);	
    	
    	if(escolha == 1 && bilhete1 != 0)
    	{
    		Usar_Bilhete(emailB,1);
			
			bilhete1--;	
			
    		cabecalho();
    		
    		printf(" Escolheu a Copa do mundo e tem ingresso !!\n ");
    		system("pause");
    		
    		while(opc != 4)
    		{
    			cabecalho();
    			
    			printf(" Olhar Trof�u da Copa do Mundo pressione 1.\n");
				printf(" Mascote da Copa do Mundo de 2022 pressione 2.\n");
				printf(" OLhar Bola da Copa do Mundo pressione 3.\n");
				printf(" Para sair  pressione 4.\n \n ");
				
				scanf("%d", &opc);
				
				system("cls");
    			
	    		if(opc == 1)
	    		{
	    			printf("-------------------------------------");
					printf("\n\t Trof�u Copa do mundo\n");
					printf("-------------------------------------\n");
					
					printf(" Diante de tantas novidades e curiosidades, uma\n coisa se mant�m igual: o trof�u. De acordo com\n a Conmebol, ele foi desenhado pelo escultor\n Silvio Gazzaniga, que trabalhava para a\n empresa Bertoni, em Mil�o, na It�lia.\n\n O trof�u mostra duas figuras de atletas segurando\n a Terra e, desde 1974, n�o mudou em nada: ele �\n feito de ouro 18 quilates, tem 36,8 cm de altura\n e pesa 6,1kg, segundo a FIFA.\n\n Apenas oito na��es j� levaram a ta�a, ou seja, um\n seleto grupo de dez por cento. Uruguai, It�lia,\n Alemanha, Brasil, Inglaterra, Argentina, Fran�a e\n Espanha s�o os �nicos campe�es e, normalmente,\n favoritos a cada quatro anos.");    		
				
					avaliacao(1);
				}
				else if(opc== 2)
	    		{
	    			printf("-------------------------------------");
					printf("\n\t Mascote da Copa do Mundo de 2022\n");
					printf("-------------------------------------\n");
					
 					printf(" Mascote La'eeb, que significa 'Jogador super\n habilidoso', � um personagem inspirado no\n len�o usado na cabe�a das pessoas do mundo\n �rabe.Trata-se de uma vestimenta tradicional\n popularmente conhecida por tr�s nomes:Keffyeh,\n Shemagh e Ghutra.");	    		
	    			avaliacao(2);
				}
				else if(opc == 3)
	    		{
	    			printf("-------------------------------------");
					printf("\n\t Bola da Copa do Mundo\n");
					printf("-------------------------------------\n");
					
					printf(" A bola escolhida para a Copa do Mundo\n de 2022 foi produzida pela Adidas,\n fornecedora de bolas desde o Mundial\n do M�xico, em 1970. A bola foi nomeada\n como 'AL Rihla', que traduzida do �rabe\n significa 'A viagem'.");
	    		
	    			avaliacao(3);
				}  
			}
			
			opc = 0;
				
		}
		else if(escolha == 2 && bilhete2 != 0)
		{
    		Usar_Bilhete(emailB,2);
			
			bilhete2--;	
			
			cabecalho();
			
    		printf(" Escolheu as Olimpiadas e tem ingresso !!\n ");
    		system("pause");
    		
    		
    		while(opc != 4)
    		{
    			cabecalho();
    			
    			printf(" Olhar Mascotes de Tokyo 2020 pressione 1.\n");
				printf(" Olhar Medalhas das Olimpiadas pressione 2.\n");
				printf(" OLhar Est�dio de Tokyo  pressione 3.\n");
				printf(" Para sair pressione 4.\n \n ");
				
				scanf("%d", &opc);
				
				system("cls");
				
	    		if(opc == 1)
	    		{
	    			printf("-------------------------------------");
					printf("\n\t Mascotes de Tokyo 2020 \n");
					printf("-------------------------------------\n");
					
					printf(" Os mascotes da Tokyo 2020 representam\n super her�is futuristas e foram\n selecionados em um concurso que contou\n com mais de 2000 candidatos. Os nomes\n dos personagens Miraitowa\n (futuro e eternidade) e Someity\n (nome de uma �rvore de cerejeira) foram\n escolhidos por estudantes do ensino\n fundamental e representam um tributo\n � cultura japonesa.");
					
					avaliacao(4);
	    		
				}
				else if(opc == 2)
	    		{
	    			printf("-------------------------------------");
					printf("\n\t Medalhas das Olimpiadas \n");
					printf("-------------------------------------\n");
					
					printf(" Por meio de uma campanha de coleta de\n metal, foram arrecadados 100% dos\n metais necess�rios para a produ��o das 5.000\n medalhas ol�mpicas de ouro, prata e bronze.\n Em dois anos de campanha a popula��o contribuiu\n com aproximadamente 80 toneladas de aparelhos\n eletr�nicos que resultaram em 32 kg de ouro,\n 3,500 kg de prata e 2,200 kg de bronze.");
					
					avaliacao(5);
	    		
				}
				else if(opc == 3)
	    		{
	    			printf("-------------------------------------");
					printf("\n\t Est�dio de Tokyo\n");
					printf("-------------------------------------\n");
					
					printf(" O Est�dio Nacional do Jap�o foi palco\n dos jogos ol�mpicos de 1964 e foi\n remodelado para atender as Olimp�adas 2020.\n Na concep��o do projeto, o arquiteto japon�s\n Kengo Kuma utilizou madeira das 47 prov�ncias\n que formam o Jap�o e adicionou no projeto\n paisag�stico o plantio de aproximadamente\n 47.000 �rvores.");
					
					avaliacao(6);
	    		
				}
			}
			
			opc = 0;
    			
		}
		else if(escolha == 3 && bilhete3 != 0)
		{
    		Usar_Bilhete(emailB,3);
			
			bilhete3--;	
			
			cabecalho();
			
    		printf(" Escolheu a Astrologia e tem ingresso !!\n ");
    		system("pause");
    		
    		while(opc != 4)
    		{
    			cabecalho();
    			
    			printf(" Olhar Pilares da cria�ao pressione 1.\n");
				printf(" Olhar O Telesc�pio Espacial James Webb pressione 2.\n");
				printf(" OLhar Buraco Negro  pressione 3.\n");
				printf(" Para sair  pressione 4.\n \n ");
				
				scanf("%d", &opc);
				
				system("cls");
			
	    		if(opc == 1)
	    		{
	    			printf("-------------------------------------");
					printf("\n\t Pilares da cria�ao\n");
					printf("-------------------------------------\n");
	    		
					printf(" Os pilares da criacao sao colunas de gas hidrogenio\n e poeira na constelacao Serpentes, os tres pilares\n gasosos ficam localizados em uma regiao conhecida\n pelos astronomos como Messier 16 (M16), na Nebulosa\n da Aguia, e uma area de formacao ativa de estrelas,\n foto tirada pelo telesc�pio James Webb.\n");			
				
					avaliacao(7);
				}
				else if(opc == 2)
	    		{
	    			printf("-------------------------------------");
					printf("\n\t O Telesc�pio Espacial James Webb\n");
					printf("-------------------------------------\n");
					
					printf(" O Telesc�pio Espacial James Webb, em ingl�s James\n Webb Space Telescope (JWST), � um telesc�pio espacial\n projetado pela Nasa em colabora��o com a Ag�ncia Espacial\n Europeia (ESA) e a Ag�ncia Espacial Canadiana (CSA) com o\n intuito de substituir o Telesc�pio Espacial Hubble.\n\n 'Ele foi desenvolvido para responder aos questionamentos\n sobre a forma��o do universo, a exist�ncia de planetas\n habit�veis, a evolu��o de gal�xias, estrelas, buracos\n negros e sistemas planet�rios e investigar com\n profundidade os exoplanetas.'");			
				
					avaliacao(8);
				}
				else if(opc == 3)
	    		{
	    			printf("-------------------------------------");
					printf("\n\t Buraco Negro\n");
					printf("-------------------------------------\n");
				    	
	    			printf(" James Webb descobriu um buraco negro supermassivo\n na gal�xia CEERS 1019 que est� a 13,2 bilh�es de\n anos-luz de dist�ncia do nosso planeta, que tem uma\n massa de 10 milh�es de vezes a do sol no centro de\n uma gal�xia beb� formada 570 milh�es de anos ap�s\n o surgimento do universo.");			
				
					avaliacao(9);
				}
			}
			
			opc = 0;
		}
		
		else if(escolha == 1 && bilhete1 == 0)
    	{
    		cabecalho();
			printf(" Escolheu a Copa do Mundo mas n�o tem ingresso, v� na bilheteria !!\n");		
		}
		else if(escolha == 2 && bilhete2 == 0)
		{
			cabecalho();
			printf(" Escolheu as Olimpiadas mas n�o tem ingresso, v� na bilheteria !!\n");		
		}
				else if(escolha == 3 && bilhete3 == 0)
		{
			cabecalho();
    		printf(" Escolheu a Astrologia e n�o tem ingresso !!\n");
    				
		}
		
	}
	else
	{
		printf(" Voc� n�o possui bilhetes de entrada, v� na bilheteria !!");	
	}
		
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
    	fflush(stdin);
    	
		cabecalho();

        printf(" 1. Fazer Cadastro\n");
        printf(" 2. Bilheteria\n");
        printf(" 3. Entrar no museu\n");
        printf(" 4. Sair\n\n  ");
        
        fflush(stdin);

        scanf("%d", &opcao);

          switch(opcao)
          {
              case 1:
                  cadastro();
                  break;

              case 2:
                  compra();
                  break;

              case 3:
                  entrar();
                  break;

              case 4:
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
