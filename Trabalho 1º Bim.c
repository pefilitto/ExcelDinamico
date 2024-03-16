#include <conio.h>
#include <stdarg.h>
#include <windef.h>
#include <winbase.h>
#include <wincon.h>
#include <windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct matesp{
	int lin;
	char col;
	char campo[50];
	struct matesp *proxcol, *proxlin;
};
typedef struct matesp MatEsp;

struct listalin{
	int linha;
	struct listalin *prox;
	MatEsp *cabecalin;
};
typedef struct listalin ListaLin;

struct listacol{
  	char coluna;
  	struct listacol *prox; 
	MatEsp *cabecacol;
};
typedef struct listacol ListaCol;

struct planilha{
	ListaCol *pCaixaCol;
	ListaLin *pCaixaLin;
};
typedef struct planilha Planilha;

struct intervalo{
	int linIni, linFinal;
	char colIni, colFinal;
};
typedef struct intervalo Intervalo;

struct Reg{
	int lin;
	char col, campo[50];	
};
typedef struct Reg TpReg;

void infoEsq(int n, int info, char s_info[])
{
    int i, tam;
    itoa(info,s_info,10);
    tam = strlen(s_info);
    for (i=0; i<n-tam; i++)
        strcat(s_info," ");
}

void infoCenter(int info, char s_info[])
{
    char s[9];
    strcpy(s,"    ");
    sprintf(s_info,"%c",info);
    strcat(s,s_info);
    strcat(s,"    ");
    strcpy(s_info,s);
}

void desenhaTela(int lin, int col)
{
    int i,j;
    char slin[4],scol[9];
    textbackground(0);
    system("cls");
    textbackground(3);
    textcolor(0);
    
    //desenha a coluna esq 1..20
    for (i=4; i<=23; i++)
    {
        gotoxy(1,i);
        infoEsq(3,lin,slin);
        printf("%s",slin);
        lin=lin+1;
    }
    //desenha a linha sup A..H
    j=4;
    for (i=1; i<=8; i++)
    {
        gotoxy(j,3);
        infoCenter(col,scol);
        printf("%s",scol);
        j=j+9;
        col=col+1;
    }
}

ListaLin * criaCaixaListaLin(int linha){
	ListaLin *caixa = (ListaLin*)malloc(sizeof(ListaLin));
	caixa -> linha = linha;
	caixa -> cabecalin = NULL;
	caixa -> prox = NULL;
	return caixa;
}

ListaCol * criaCaixaListaCol(char coluna){
	ListaCol *caixa = (ListaCol*)malloc(sizeof(ListaCol));
	caixa -> coluna = coluna;
	caixa -> cabecacol = NULL;
	caixa -> prox = NULL;
	return caixa;
}

MatEsp * criaCaixaMatEsp(int lin, char col, char info[]){
	MatEsp *caixa = (MatEsp*)malloc(sizeof(MatEsp));
	caixa -> lin = lin;
	caixa -> col = col;
	strcpy(caixa -> campo, info);
	caixa -> proxcol = caixa -> proxlin = NULL;
	return caixa;
}

void verificaOcupado(Planilha *p, int lin, char col, MatEsp * * aux) {
	ListaLin *auxL = p -> pCaixaLin;
	MatEsp *auxM;
	while(auxL != NULL && auxL -> linha < lin)
		auxL = auxL -> prox;
	
	if(auxL != NULL){
		auxM = auxL -> cabecalin;
		while(auxM != NULL && auxM -> col < col)
			auxM = auxM -> proxcol;
			
		if(auxM != NULL && auxM -> col == col && auxM -> lin == lin)
			*aux = auxM;
		else *aux = NULL;		
	}
	else *aux = NULL;
}

int SUM(MatEsp * celulaIni, MatEsp * celulaFinal){
	int soma = 0;
	MatEsp *aux = celulaIni;
	if(celulaIni -> lin == celulaFinal -> lin){
		while(aux != celulaFinal){
			soma += atoi(aux -> campo);
			aux = aux -> proxcol;
		}	
	}
	else{
		if(celulaIni -> col == celulaFinal -> col){
			while(aux != celulaFinal){
				soma += atoi(aux -> campo);
				aux = aux -> proxlin;
			}	
		}
	}
	
	soma += atoi(aux -> campo);
	return soma;
}

int AVG(MatEsp * celulaIni, MatEsp * celulaFinal){
	int media = 0, soma = 0, cont = 0;
	MatEsp *aux = celulaIni;
	if(celulaIni -> lin == celulaFinal -> lin){
		while(aux != celulaFinal){
			soma += atoi(aux -> campo);
			aux = aux -> proxcol;
			cont++;
		}
	}
	else{
		if(celulaIni -> col == celulaFinal -> col){
			while(aux != celulaFinal){
				soma += atoi(aux -> campo);
				aux = aux -> proxlin;
				cont++;
			}
		}
	}
	soma += atoi(aux -> campo);
	cont++;
	
	media = soma/cont;
	return media;
}

int MAX(MatEsp * celulaIni, MatEsp * celulaFinal){
	MatEsp *aux = celulaIni;
	int maior = 0;
	
	if(celulaIni -> lin == celulaFinal -> lin){
		while(aux != celulaFinal){
			if(atoi(aux -> campo) > maior)
				maior = atoi(aux -> campo);
			aux = aux -> proxcol;
		}
	}
	else{
		if(celulaIni -> col == celulaFinal -> col){
			while(aux != celulaFinal){
				if(atoi(aux -> campo) > maior)
					maior = atoi(aux -> campo);
				aux = aux -> proxlin;
			}
		}
	}
	if(atoi(aux -> campo) > maior)
		maior = atoi(aux -> campo);
	return maior;
}

int MIN(MatEsp * celulaIni, MatEsp * celulaFinal){
	MatEsp *aux = celulaIni;
	int menor = 9999;
	
	if(celulaIni -> lin == celulaFinal -> lin){
		while(aux != celulaFinal){
			if(atoi(aux -> campo) < menor)
				menor = atoi(aux -> campo);
			aux = aux -> proxcol;
		}
	}
	else{
		if(celulaIni -> col == celulaFinal -> col){
			while(aux != celulaFinal){
				if(atoi(aux -> campo) < menor)
					menor = atoi(aux -> campo);
				aux = aux -> proxlin;
			}
		}
	}
	if(atoi(aux -> campo) < menor)
		menor = atoi(aux -> campo);
	return menor;
}

Intervalo intervaloCelulas(char * formula){
	Intervalo limites;
    limites.linIni = 0;
    limites.linFinal = 0;
    limites.colIni = '0';
    limites.colFinal = '0';

    char linIniStr[4] = "", linFinalStr[4] = "";
    int linIniIndex = 0, linFinalIndex = 0;
    int i = 0;

    while (formula[i] != ')' && formula[i] != '\0') {
        if (formula[i] != ':' && (formula[i] >= 'A' && formula[i] <= 'Z')) {
            if (limites.colIni == '0' && limites.colFinal == '0') {
                limites.colIni = formula[i];
            } 
			else {
                limites.colFinal = formula[i];
            }
        }
        if (formula[i] >= '0' && formula[i] <= '9') {
            if (strcmp(linIniStr, "") == 0 && strcmp(linFinalStr, "") == 0) {
                while (formula[i] != ':') {
                    linIniStr[linIniIndex++] = formula[i];
                    i++;
                }
            } 
			else {
                while (formula[i] != ')') {
                    linFinalStr[linFinalIndex++] = formula[i];
                    i++;
                }
            }
        }
        i++;
    }

    if (linIniIndex > 0) {
        limites.linIni = atoi(linIniStr);
    }
    if (linFinalIndex > 0) {
        limites.linFinal = atoi(linFinalStr);
    }
    return limites;
}

int CalculaFormula(Planilha *p, int lin, char col, char * formula){
	int i=0, resultado;
	MatEsp *celulaIni, *celulaFinal;
	Intervalo intervalo;
	
	if (strncmp(formula, "=SUM(", 5) == 0) {
	    formula += strlen("=SUM(");
	    intervalo = intervaloCelulas(formula);
		    
        verificaOcupado(p, intervalo.linIni, intervalo.colIni, &celulaIni);
        verificaOcupado(p, intervalo.linFinal, intervalo.colFinal, &celulaFinal);

        resultado = SUM(celulaIni, celulaFinal);
    } 
	else if (strncmp(formula, "=AVG(", 5) == 0) {
        formula += strlen("=AVG(");
	    intervalo = intervaloCelulas(formula);
		    
        verificaOcupado(p, intervalo.linIni, intervalo.colIni, &celulaIni);
        verificaOcupado(p, intervalo.linFinal, intervalo.colFinal, &celulaFinal);
        
        resultado = AVG(celulaIni, celulaFinal);        
    } 
	else if (strncmp(formula, "=MAX(", 5) == 0) {
        formula += strlen("=MAX(");
	    intervalo = intervaloCelulas(formula);
		    
        verificaOcupado(p, intervalo.linIni, intervalo.colIni, &celulaIni);
        verificaOcupado(p, intervalo.linFinal, intervalo.colFinal, &celulaFinal);
        
		resultado = MAX(celulaIni, celulaFinal);
    } 
	else if (strncmp(formula, "=MIN(", 5) == 0) {
        formula += strlen("=MIN(");
	    intervalo = intervaloCelulas(formula);
		    
        verificaOcupado(p, intervalo.linIni, intervalo.colIni, &celulaIni);
        verificaOcupado(p, intervalo.linFinal, intervalo.colFinal, &celulaFinal);
        
		resultado = MIN(celulaIni, celulaFinal);
    } 
	return resultado;
}

void exibir(Planilha *p, int lin, char col) {
    MatEsp *aux;
    int i, colTela, linTela = 4, resultado;
	char j, resultadoString[20];
	
    for (i = lin; i <= lin+19; i++) {
    	colTela = 4;
        for (j = col; j <= col+7; j++) {
            verificaOcupado(p, i, j, &aux);
            if (aux != NULL){	
            	if(aux -> campo[0] == '='){
            		resultado = CalculaFormula(p, aux -> lin, aux -> col, aux -> campo);
            		gotoxy(1, 26);
					sprintf(resultadoString, "%d", resultado);
            		gotoxy(colTela, linTela);
            		printf("%s", resultadoString);	
            	}
            	else{
            		gotoxy(colTela, linTela);
        			printf("%s", aux->campo); 	
            	}   	        	    	
            }
            colTela += 9;
        }
        linTela++;
    }
}

void gravarPlanilhaArquivo(Planilha *p, char nomeArq[]){
	TpReg reg;
	int i, j;
	MatEsp *aux;
	FILE *ptr = fopen(nomeArq, "wb");
	
	if(ptr == NULL)
		printf("Erro ao criar arquivo!");
	else{
		for(i = 1; i <= 100; i++){
			for(j = 'A'; j <= 'Z'; j++){
				verificaOcupado(p, i, j, &aux);
				if(aux != NULL){
					reg.lin = aux -> lin;
					reg.col = aux -> col;
					strcpy(reg.campo, aux -> campo);
					fwrite(&reg, sizeof(TpReg), 1, ptr);
				}
			}
		}
	}
	fclose(ptr);
}

void abrirPlanilhaArquivo(Planilha *p, char nomeArq[]){
	TpReg reg;
	int i, j;
	MatEsp *aux;
	FILE *ptr = fopen(nomeArq, "rb");
	
	fread(&reg, sizeof(TpReg), 1, ptr);
	while(!feof(ptr)){
		gravaInformacao(&p, reg.lin, reg.col, reg.campo);
		
		fread(&reg, sizeof(TpReg), 1, ptr);
	}
	fclose(ptr);
}

void insereListaLin(ListaLin * * pCaixa, int lin, ListaLin * * aux){
	ListaLin *antL, *auxL, *nova;
	if(*pCaixa == NULL){ 
		*pCaixa = criaCaixaListaLin(lin);
		*aux = *pCaixa; 
	}
	else{
		antL = NULL;
		auxL = *pCaixa;
		while(auxL != NULL && lin > auxL -> linha)
		{
			antL = auxL;
			auxL = auxL -> prox;
		}
		if(auxL != NULL && lin == auxL->linha)
			*aux = auxL;
		else
		{
			nova = criaCaixaListaLin(lin);
			if (antL == NULL)
			{
				nova -> prox = *pCaixa;
				*pCaixa = nova;	
			}
			else
			{
				antL -> prox = nova;
				nova -> prox = auxL;
			}
			*aux = nova;
		}
	}
}

void insereListaCol(ListaCol * * pCaixa, char col, ListaCol * * aux){
	ListaCol *auxC, *nova, *antC;
	if(*pCaixa == NULL){
		*pCaixa = criaCaixaListaCol(col);
		*aux = *pCaixa;
	}
	else{
		antC = NULL;
		auxC = *pCaixa;
		while(auxC != NULL && col > auxC -> coluna){
			antC = auxC;
			auxC = auxC -> prox;	
		}
		
		if(auxC != NULL && col == auxC -> coluna)
			*aux = auxC;
		else{
			nova = criaCaixaListaCol(col);
			
			if(antC == NULL){
				nova -> prox = *pCaixa;
				*pCaixa = nova;
			}
			else{
				antC -> prox = nova;
				nova -> prox = auxC;
			}
			*aux = nova;
		}
	}
}

void gravaInformacao(Planilha **p, int lin, char col, char info[]) {
    MatEsp *aux, *caixaMatEsp, *nova, *ant;
    ListaLin *caixaLin, *auxL;
    ListaCol *caixaCol, *auxC;

    insereListaLin(&(*p)->pCaixaLin, lin, &auxL);
    insereListaCol(&(*p)->pCaixaCol, col, &auxC);    	   

    verificaOcupado(*p, lin, col, &aux);
    // Caso haja uma caixinha na posição especificada, o valor contido nela será substituído
    if (aux != NULL)
        strcpy(aux->campo, info);
    else {
    	nova = criaCaixaMatEsp(lin, col, info);
        
        // Ligação horizontal
        if (auxL->cabecalin == NULL) {
            auxL->cabecalin = nova;
        } 
		else if (col < auxL->cabecalin->col) {
            nova->proxcol = auxL->cabecalin;
            auxL->cabecalin = nova;
        }
		else {
            aux = auxL->cabecalin;
            while (aux != NULL && col > aux->col) {
                ant = aux;
                aux = aux->proxcol;
            }
            ant->proxcol = nova;
        }

        // Ligação vertical
        if (auxC->cabecacol == NULL) {
            auxC->cabecacol = nova;
        } 
		else if (lin < auxC->cabecacol->lin) {
            nova->proxlin = auxC->cabecacol;
            auxC->cabecacol = nova;
        } 
		else {
            aux = auxC->cabecacol;
            while (aux != NULL && lin > aux->lin) {
                ant = aux;
                aux = aux->proxlin;
            }
            ant->proxlin = nova;
        }
    }
}

Planilha * inicia(){
	Planilha *p = (Planilha*)malloc(sizeof(Planilha));
	p -> pCaixaLin = NULL;
	p -> pCaixaCol = NULL;
	return p;
}

void iniciaExcel(Planilha * * p)
{
    char key;
    char m[100], texto[100], nomeArq[20];
    
    int c,l,col,lin;

    textbackground(0);
    system("cls");
    desenhaTela(1,65);
    //coordenadas de tela
    c=l=1;
    //coordenadas da matriz
    col=65; //letra A
    lin=1;
    gotoxy(c*9-9+4,l+3);
    printf("         ");

    do
    {
        key=getch();
        if (key==-32)
        {
            key=getch();
            switch(key)
            {                       //linhas   linhas-1
                case 80:
					if (l==20 && lin<100 - 19) //seta p/ baixo
                        lin++;
                    if (l<20)
                        l++;
                break;
                
                case 72:
					if (l==1 && lin>1) //seta p/ cima
                        lin--;
                    if (l>1)
                        l--;
                break;
                                     //'A' alfabeto  colunas-1
                case 77:
					if (c==8 && col<65 + 26 - 8) //seta p/ direita
                        col++;
                    if (c<8)
                        c++;
                break;
                
                case 75:
					if (c==1 && col>65) //seta p/ esquerda
                        col--;
                    if (c>1)
                        c--;
                break;				           
            }
            desenhaTela(lin,col);
            textbackground(0);
            textcolor(7);
            
            //<--------------------exibir todas as celulas na janela atual
            //                     de lin atï¿½ lin+19, col atï¿½ col+8
            exibir(*p, lin, col);
            textbackground(3);
            textcolor(0);
            gotoxy(1, 1);
			printf("%c%d: ", col+c-1, lin+l-1);
            
            
            gotoxy(c*9-9+4,l+3);
            textbackground(3);
            textcolor(0);
            printf("         "); //desenhar o conteudo da celula atual a partir da matriz esparsa         	
        }
        else if (key == 224 || key == 0){
        	key = getch();
        	switch(key)
			{
                case 60: //Alterar celula (F2)
                	gotoxy(1, 2);
                	scanf("%s", &texto);
                	gravaInformacao(&(*p), lin+l-1, col+c-1, texto);
                break;    
                
                case 61: //Salvar planilha (F3)
                	gotoxy(1, 2);
                	scanf("%s", &nomeArq);
                	gravarPlanilhaArquivo(*p, nomeArq);
				break;
                
                case 62: //Abrir planilha (F4)
                	gotoxy(1, 2);
                	scanf("%s", &nomeArq);
                	abrirPlanilhaArquivo(*p, nomeArq);
                break;
            }        	
        }
    }while (key!=27);
}

int main()
{
	Planilha *p;
	gotoxy(50, 1);
	printf("Bem vindo ao excel!");
	gotoxy(45, 3);
	printf("Digite enter para continuar");
	getch();
	p = inicia();
	iniciaExcel(&p);
		
	return 0;
}
