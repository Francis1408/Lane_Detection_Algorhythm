# Lane_Detection_Algorithm
### Authors: Francisco Abreu Gonçalves and Tarcísio Prates

This program was the final project of my Algorithm and Data Structures I subject, during my sophomore year. The following Algorithm was inspired by Ziviani's Data Structure Book.

#### About the Algorithm:

  Giving a file which contains information of a lane, the programs returns piece of information about it, such as: If it is a valid Lane pattern, Lane's midpoint and Lane's Direction.

#### Lane pattern:
  
  At first, the program will save the Lane's information in a array and by the function below, return if the lane has a valid pattern:

  ```cpp
  void findRecorrencia(int tam, TipoLista *lista, TipoItem *Map, int *max){
  
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
    pos++;
    
  }

  *max = pos;  
}
  ```
  ![alt text](https://github.com/Francis1408/Lane_Detection_Algorhythm/blob/main/img/LanePattern.png)

  Every lane must have the following pattern inside the array:

  ```
  1 3 2 3 1
  ```
  Each number represents a certain color:

  | Color    | True Value  | Mapping value |
  |----------|:-----------:|--------------:|
  | Black    | 0           | 1             | 
  | Red      | 128         | 2             |
  | White    | 255         | 3             |

#### Lane's midpoint:

  If the lane given follows a correct pattern, the algorithm will find its mid point by running the following function:

  ```cpp

  void encontraMeio(TipoItem *Map, int pos){
  int count = 0;
  for(int i = 0; i<=pos; i++){
    if(i == pos){
      if(Map[i].Quant%2 != 0 ){

        Map[i].Quant = Map[i].Quant + 1;
      }
      Map[i].relativo = (count-1)+(Map[i].Quant/2);
    }else
    {
      count+=Map[i].Quant;
    }
    
  }
}

  ```
  ![alt text](https://github.com/Francis1408/Lane_Detection_Algorhythm/blob/main/img/Midpoint.png)

  If the array contains N pixels, from 0 to N-1, the midpoint will be the (p+q)/2 element, which p and q are the Lane's initial and final position. 

  #### Lane's direction:

  In order to find the lane's direction, whether it is to the right, to the left or straight ahead, the algorithm divides the lane in horizontal lines and finds theirs midpoints. 

  ![alt text](https://github.com/Francis1408/Lane_Detection_Algorhythm/blob/main/img/LaneDirection.png)


  The following Algorithm will receive the midpoints of every line and, thus, analyses the lane's behaviour:

  ```cpp
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

void verifica_direcao(int v_pmedio[], int *direc, int k){
  k--;
  if(v_pmedio[k] <= (v_pmedio[0]*1.2) && v_pmedio[k] >= (v_pmedio[0]*0.8)){
    *direc = 1;
  }else if(v_pmedio[0] < v_pmedio[k]){
    *direc = 2;
  }else
    *direc = 3;

}

  ```