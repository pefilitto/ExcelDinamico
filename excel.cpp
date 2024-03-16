#include <conio.h>
#include <stdarg.h>
#include <windef.h>
#include <winbase.h>
#include <wincon.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//--- conio 2 -------------------------------------------------------
void gotoxy(int x, int y)
{
  COORD c ;
  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void textattr(int _attr)
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _attr);
}

void textbackground(int _color)
{
  CONSOLE_SCREEN_BUFFER_INFO Info ;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
  textattr((Info.wAttributes & 0x0F) | (_color<<4));
}

void textcolor(int _color) {
  CONSOLE_SCREEN_BUFFER_INFO Info ;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
  textattr((Info.wAttributes & 0xF0) | _color);
}

int wherex()
{
  CONSOLE_SCREEN_BUFFER_INFO Info;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
  return Info.dwCursorPosition.X + 1;
}

int wherey()
{
  CONSOLE_SCREEN_BUFFER_INFO Info;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
  return Info.dwCursorPosition.Y + 1;
}

void clrscr(void)
{
  COORD coord = { 0, 0 };
  DWORD dwWritten, dwSize;
  HANDLE hScreen=GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO Info;

  if(GetConsoleScreenBufferInfo(hScreen, &Info))
  {
      dwSize = Info.dwSize.X * Info.dwSize.Y;
      FillConsoleOutputCharacter (hScreen, ' ', dwSize, coord, &dwWritten);
      FillConsoleOutputAttribute (hScreen, Info.wAttributes, dwSize, coord, &dwWritten);
      gotoxy (1, 1);
  }
}
//-------------------------------------------------------------------

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
    clrscr();
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

void iniciaExcel()
{
    char key;
    int c,l,col,lin;

    textbackground(0);
    clrscr();
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
                case 80:if (l==20 && lin<100 - 19) //seta p/ baixo
                            lin++;
                        if (l<20)
                            l++;
                        break;
                case 72:if (l==1 && lin>1) //seta p/ cima
                            lin--;
                        if (l>1)
                            l--;
                        break;
                                     //'A' alfabeto  colunas-1
                case 77:if (c==8 && col<65 + 26 - 8) //seta p/ direita
                            col++;
                        if (c<8)
                            c++;
                        break;
                case 75:if (c==1 && col>65) //seta p/ esquerda
                            col--;
                        if (c>1)
                            c--;
                        break;
            }
            desenhaTela(lin,col);
            textbackground(0);
            textcolor(7);
            //<--------------------exibir todas as celulas na janela atual
            //                     de lin até lin+19, col até col+8
            gotoxy(c*9-9+4,l+3);
            textbackground(3);
            textcolor(0);
            printf("         "); //desenhar o conteudo da celula atual a partir da matriz esparsa
        }
    }while (key!=27);
}

main(void)
{
    iniciaExcel();
}

