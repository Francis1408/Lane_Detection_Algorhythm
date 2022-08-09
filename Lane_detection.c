
/****

LAED1 - Projeto (Parte III) - Estimativa do formato da pista

Alunos(as): Tarcísio Batista Prates 
            Francisco Abreu Gonçalves 

Data: 18/11/2020

****/




#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#define INICIOARRANJO   1
#define MAXTAM          1000

typedef int TipoChave;

typedef int TipoApontador;

typedef int TipoRecorencia;

typedef int TipoDesvio;

typedef int TipoPontoMedio;

typedef struct {
  TipoChave Chave; // valor do bloco
  TipoRecorencia Quant; // quantidade de itens por bloco
  TipoDesvio erro;//poderá ser usada para retirar desvios padrão
  TipoPontoMedio relativo;//em relação ao conjunto

} TipoItem;


typedef struct {
  TipoItem Item[MAXTAM];
  TipoApontador Primeiro, Ultimo;
} TipoLista;

int Vazia(TipoLista Lista){ 
  return (Lista.Primeiro == Lista.Ultimo);
}

void FLVazia(TipoLista *Lista)
{ Lista -> Primeiro = INICIOARRANJO;
  Lista -> Ultimo = Lista -> Primeiro;
}

void Insere(TipoItem x, TipoLista *Lista)
{ if (Lista -> Ultimo > MAXTAM) printf("Lista esta cheia\n");
  else { Lista -> Item[Lista -> Ultimo - 1] = x;
         Lista -> Ultimo++;
       }
} 

void encontraMeio(TipoItem *Map, int pos){
  int count = 0;
  //A função soma, da esquesda para a direita, o intervalo até uma casa antes da pista vermelha.
  //Após isso, ela soma com o valor obtido, com a metade da extensão da pista. 
  for(int i = 0; i<=pos; i++){
    if(i == pos){
      if(Map[i].Quant%2 != 0 ){//Aqui, ocorre o arredondamento para cima, quando necessário.
        Map[i].Quant = Map[i].Quant + 1;//Arrendonda para cima
      }
      Map[i].relativo = (count-1)+(Map[i].Quant/2);
    }else
    {
      count+=Map[i].Quant;
    }
    
  }
}


int veriifcaCaminho(int max, TipoItem *Map, TipoChave limiteLateral, TipoChave pista, TipoChave acostamento, int *pos){
  // procura no mapa criado, a sequência 0 255 128 255 0
  for(int i = 0; i<max && i+4<max; i++){
    if(acostamento == Map[i].Chave && limiteLateral == Map[i+1].Chave){
      if(pista == Map[i+2].Chave){
        if(limiteLateral == Map[i+3].Chave && acostamento == Map[i+4].Chave){
          *pos = (i+2);//grava pos da pista vermelha
          return 1;
        }
      }
    }
  }
  return 0;
}


void findRecorrencia(int tam, TipoLista *lista, TipoItem *Map, int *max){
  /*
  Essa função agurupa a informação de recorrênicia em sequência
  de um valor.
  Ex: Na sequência: 0 0 0 0 255 255 255 255 0 0 0 0
  Serão condensados em apenas três casas, 0 225 0, cada
  unidade de informação conterá a qunatidade de repetições,
  assim, cada valor chave, será realocado para um outro vetor, 
  permitindo que se faça a busca pelo caminho, semelhante a um mapa. 
  */
  
  int aux = 0, k = 0;
  int cont = 0, pos = 0;
  for(int i = 0; i<tam; i=k){
    aux = lista->Item[i].Chave;
     k = i; cont = 0;
    while(aux == lista->Item[k].Chave){
      cont++; k++;
    }
    lista->Item[i].Quant = cont;
    Map[pos] = lista->Item[i];
    //printf("O valor %d possui %d repetições\n", Map[pos].Chave, Map[pos].Quant);
    pos++;
    
  }

  *max = pos;
  
}

void verifica_direcao(int v_pmedio[], int *direc, int k){
  k--;
  if(v_pmedio[k] <= (v_pmedio[0]*1.2) && v_pmedio[k] >= (v_pmedio[0]*0.8)){
    *direc = 1;
  }else if(v_pmedio[0] < v_pmedio[k]){
    *direc = 2;
  }else
    *direc = 3;

}

int main(){


  char nome[100];
  FILE *arquivo;
  int tam, max, pos;
  TipoChave limiteLateral = 255;
  TipoChave pista = 128;
  TipoChave acostamento = 0;
  TipoItem map[100];
  TipoLista lista;
  FLVazia(&lista);
  TipoItem item;
  int linha; int k =0;
  int direc;

  printf("Digite o nome do arquivo: ");
	scanf("%s", nome);
	getchar();

	arquivo = fopen(nome, "r");

	if(!arquivo){
		printf("Erro na abertura do arquivo!");
        exit(0);
	}
  else{
    fscanf(arquivo,"%d", &linha);
    int v_pmedio[linha];
    for(int j = 0; j<linha;j++){
      FLVazia(&lista);
      fscanf(arquivo,"%d",&tam);
      int i; item.Chave = 0;
      for(i = 0; i<tam; i++){
        fscanf(arquivo,"%d",&item.Chave);
        Insere(item,&lista);
      }

      findRecorrencia(tam,&lista,map,&max);
      if(veriifcaCaminho(max,map,limiteLateral,pista, acostamento,&pos)){
        encontraMeio(map,pos);
        //printf("Pos = %d\n", pos);
        v_pmedio[k] = map[pos].relativo;
        k++;

      }
    }   
    if(k>=(linha*0.7)){

     /* for(int m = 0; m<k; m++){
        printf("Linha %d > ponto médio = %d\n", m, v_pmedio[m]);
      }*/

      verifica_direcao(v_pmedio, &direc, k);
      if(direc == 2){
        printf("Resultado: Curva a esquerda.");
      }
      if(direc == 3){
        printf("Resultado: Curva a direita.");
      }
      if(direc == 1){
        printf("Resultado: Pista em linha reta.");
      }
    }
    else{
      printf("Resultado: Formato da pista nao estimado.");
    }
  }

}

/*
L 
l
n

Digite o nome do arquivo: 
Linha 0 > ponto médio = 311
Linha 1 > ponto médio = 384
Linha 2 > ponto médio = 434
Linha 3 > ponto médio = 463
Linha 4 > ponto médio = 482
Linha 5 > ponto médio = 494
Linha 6 > ponto médio = 500
Linha 7 > ponto médio = 501
Linha 8 > ponto médio = 500
Linha 9 > ponto médio = 499
Linha 10 > ponto médio = 497
Linha 11 > ponto médio = 495
Linha 12 > ponto médio = 492
Resultado: Curva a direita.



linha reta 
Digite o nome do arquivo: 
Linha 0 > ponto médio = 489
Linha 1 > ponto médio = 495
Linha 2 > ponto médio = 494
Linha 3 > ponto médio = 496
Linha 4 > ponto médio = 496
Linha 5 > ponto médio = 496
Linha 6 > ponto médio = 496
Linha 7 > ponto médio = 497
Linha 8 > ponto médio = 496
Linha 9 > ponto médio = 495
Linha 10 > ponto médio = 494
Linha 11 > ponto médio = 495
Linha 12 > ponto médio = 494
Linha 13 > ponto médio = 493
Linha 14 > ponto médio = 492
Resultado: Curva a direita.





  REFERÊNCIAS

ZIVIANI, Nivio. Projeto de algoritmos com implementações em Pascal e C. UFMG, 2ª EDICAO - 2004, cap. 3. Disponível em:
http://www2.dcc.ufmg.br/livros/algoritmos/cap3/codigo/c/3.1a3.2-lista-arranjo.c. 
Acessado em: 10 out. 2020. 

Agradecimentos:

H. R. @Limão


*/