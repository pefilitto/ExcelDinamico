struct matesp{
	int lin;
	char col;
	char campo[100];
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

union info_lista{
	float valor;
	char operador;
	char funcao[15];
};
typedef union info_lista InfoLista;

struct listagen{
	char terminal; //Vai ser do tipo V = Valor | O = Operador | F = Função
	union info_lista no;
	struct listagen *cabeca, *cauda;
};
typedef struct listagen ListaGen;

struct listaencadeada{
	char info[20];
	struct listaencadeada *prox;
};
typedef struct listaencadeada ListaEncadeada;

struct no_pilha{
	ListaGen * no;
	struct no_pilha *prox;
};
typedef struct no_pilha NoPilha;

struct pilha{
	struct no_pilha *topo;
};
typedef struct pilha Pilha;

struct no_pilhaValor{
	float valor;
	struct no_pilhaValor *prox;
};
typedef struct no_pilhaValor NoPilhaValor;

struct pilhavalor{
	struct no_pilhaValor *topo;	
};
typedef struct pilhavalor PilhaValor;

struct no_pilhaOperador{
	char operador;
	struct no_pilhaOperador *prox;
};
typedef struct no_pilhaOperador NoPilhaOperador;

struct pilhaoperador{
	struct no_pilhaOperador *topo;
};
typedef struct pilhaoperador PilhaOperador;


ListaEncadeada * criaCaixaListaEncadeada(char info[]){
	ListaEncadeada *caixa = (ListaEncadeada*)malloc(sizeof(ListaEncadeada));
	strcpy(caixa -> info, info);
	caixa -> prox = NULL;
	return caixa;
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

void init(Pilha * * P){
	*P = (Pilha*)malloc(sizeof(Pilha));
	(*P) -> topo = NULL;
}

void initPOperador(PilhaOperador * * P){
	*P = (PilhaOperador*)malloc(sizeof(PilhaOperador));
	(*P) -> topo = NULL;
}

void initPValor(PilhaValor * * P){
	*P = (PilhaValor*)malloc(sizeof(PilhaValor));
	(*P) -> topo = NULL;
}

char Nula(ListaGen *L){
	return L == NULL;
}

char Tail(ListaGen *L){
	return !Nula(L) && L -> cauda;
}

char Head(ListaGen *L){
	return !Nula(L) && L -> cabeca;
}

void exibeListaGen(ListaGen *L){
	exibeListaGen(L -> cabeca);
	exibeListaGen(L -> cauda);
}

void push(Pilha * * P, ListaGen * noLista) {
    NoPilha *novoNo = (NoPilha *)malloc(sizeof(NoPilha));
    novoNo->no = noLista;
    novoNo->prox = (*P)->topo;
    (*P)->topo = novoNo;
}

void pop(Pilha * * P, ListaGen * * noLista) {
    *noLista = (*P)->topo->no;
    NoPilha *noRemovido = (*P)->topo;
    (*P)->topo = (*P)->topo->prox;
    free(noRemovido);
}

void pushValor(PilhaValor * * P, float valor){
	NoPilhaValor *novoNo = (NoPilhaValor *)malloc(sizeof(NoPilha));
	novoNo -> valor = valor;
	novoNo -> prox = (*P) -> topo;
	(*P) -> topo = novoNo; 
}

void pushOperador(PilhaOperador * * P, char operador){
	NoPilhaOperador *novoNo = (NoPilhaOperador *)malloc(sizeof(PilhaOperador));
	novoNo -> operador = operador;
	novoNo -> prox = (*P) -> topo;
	(*P) -> topo = novoNo;
}

void popValor(PilhaValor * * P, float * valor){
	*valor = (*P) -> topo -> valor;
	NoPilhaValor *noRemovido = (*P) -> topo;
	(*P) -> topo = (*P) -> topo -> prox;
	free(noRemovido);
}

void popOperador(PilhaOperador * * P, char * operador){
	*operador = (*P) -> topo -> operador;
	NoPilhaOperador *noRemovido = (*P) -> topo;
	(*P) -> topo = (*P) -> topo -> prox;
	free(noRemovido);
}

char isEmpty(Pilha * P){
	return P -> topo == NULL;
}

char isEmptyPilhaOperador(PilhaOperador * P){
	return P -> topo == NULL;
}

char isEmptyPilhaValor(PilhaValor * P){
	return P -> topo == NULL;
}

ListaGen * ConsV(ListaGen * H, ListaGen * T, char info[]){ //Cria uma caixinha que ira armazenar um valor
	ListaGen *L;
	float infoF;
	L = (ListaGen*)malloc(sizeof(ListaGen));
	L -> terminal = 'V';
	L -> cabeca = H;
	L -> cauda = T;
	
	infoF = atof(info);
	L -> no.valor = infoF;
	return L;
}

ListaGen * ConsO(ListaGen * H, ListaGen * T, char info){ //Cria uma caixinha que ira armazenar um operador
	ListaGen *L;
	L = (ListaGen*)malloc(sizeof(ListaGen));
	L -> terminal = 'C';
	L -> cabeca = H;
	L -> cauda = T;
	L -> no.operador = info;
	return L;
}

ListaGen * ConsF(ListaGen * H, ListaGen * T, char info[]){ //Cria uma caixinha que ira armazenar uma funcao
	ListaGen *L;
	L = (ListaGen*)malloc(sizeof(ListaGen));
	L -> terminal = 'F';
	L -> cabeca = H;
	L -> cauda = T;
	strcpy(L -> no.funcao, info);
	return L;
}




















