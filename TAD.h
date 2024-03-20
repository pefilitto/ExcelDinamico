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

struct reg_lista{
	struct listagen *cabeca, *cauda;	
};
typedef struct reg_lista RegLista;

union info_lista{
	char info[50];
	struct reg_lista lista;
};
typedef union info_lista InfoLista;

struct listagen{
	char terminal;
	union info_lista no;
};
typedef struct listagen ListaGen;

struct no_pilha{
	char info[50];
	struct no_pilha *prox;;
};
typedef struct no_pilha NoPilha;

struct pilha{
	struct no_pilha *topo;
};
typedef struct pilha Pilha;

























