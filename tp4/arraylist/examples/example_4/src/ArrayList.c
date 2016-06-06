#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/ArrayList.h"
#include "../inc/Employee.h"

// funciones privadas
int resizeUp(ArrayList* pList);
int expand(ArrayList* pList,int index);
int contract(ArrayList* pList,int index);

#define AL_INCREMENT      10
#define AL_INITIAL_VALUE  10
//___________________

/** \brief Allocate a new arrayList with AL_INITIAL_VALUE elements.
 * \param void
 * \return ArrayList* Return (NULL) if Error [if can't allocate memory]
 *                  - (pointer to new arrayList) if ok
 */
ArrayList* al_newArrayList(void)
{
    ArrayList* pList;
    ArrayList* returnAux = NULL;
    void* pElements;
    pList=(ArrayList *)malloc(sizeof(ArrayList));

    if(pList != NULL)
    {
        pElements = malloc(sizeof(void *)*AL_INITIAL_VALUE );
        if(pElements != NULL)
        {
            pList->size=0;
            pList->pElements=pElements;
            pList->reservedSize=AL_INITIAL_VALUE;
            pList->add=al_add;
            pList->len=al_len;
            pList->set=al_set;
            pList->remove=al_remove;
            pList->clear=al_clear;
            pList->clone=al_clone;
            pList->get=al_get;
            pList->contains=al_contains;
            pList->push=al_push;
            pList->indexOf=al_indexOf;
            pList->isEmpty=al_isEmpty;
            pList->pop=al_pop;
            pList->subList=al_subList;
            pList->containsAll=al_containsAll;
            pList->deleteArrayList = al_deleteArrayList;
            pList->sort = al_sort;
            returnAux = pList;
        }
        else
        {
            free(pList);
        }
    }

    return returnAux;
}


/** \brief  Add an element to arrayList and if is
 *          nessesary resize the array
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (0) if Ok
 *
 */
int al_add(ArrayList* pList, void* pElement)
{

    int r=0;
    int rta=-1;
    if(pList==NULL || pElement==NULL ) return -1;

    resizeUp(pList);

    *((pList->pElements)+pList->size) = pElement;

    pList->size++;
    rta=0;


    //}
    return rta;
}

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Ok
 *
 */
int al_deleteArrayList(ArrayList* pList)
{

    if(pList==NULL)
    {
        return -1;
    }
    else
    {
        free(pList->pElements);
        free(pList);
        return 0;
    }


}

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return length of array or (-1) if Error [pList is NULL pointer]
 *
 */
int al_len(ArrayList* pList)
{
    int returnAux = -1;
    if(pList==NULL  ) return -1;
    returnAux = pList->size;

    return returnAux;
}


/** \brief  Get an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return void* Return (NULL) if Error [pList is NULL pointer or invalid index] - (Pointer to element) if Ok
 *
 */
void* al_get(ArrayList* pList, int index)
{
    void* returnAux = NULL;
    // Employee* auxEmployee;
    if(pList==NULL || index<0  ) return NULL;
    if(index > pList->size) return NULL;
    returnAux =  *(pList->pElements+index);


    return returnAux;
}


/** \brief  Find if pList contains at least one element pElement
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer]
 *                  - ( 0) if Ok but not found a element
 *                  - ( 1) if this list contains at least one element pElement
 *
 */
int al_contains(ArrayList* pList, void* pElement)
{
    // int returnAux = -1;
    int i;

    if(pList==NULL || pElement==NULL ) return -1;
    for (i=0; i< pList->size; i++)
    {

        if(*(pList->pElements+i) == pElement)
        {

            /*
                            printf("pElements+i = %d", *(pList->pElements+i));
                            printf(" \n");
                            printf("pElement=%d\n",pElement );
                            */

            // returnAux=1;
            return 1;

        }

    }
    //returnAux=0;

    return 0;
}


/** \brief  Set a element in pList at index position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 *
 */
int al_set(ArrayList* pList, int index,void* pElement)
{

    // int returnAux = -1;
    if(pList==NULL || pElement==NULL || index<0 || index==NULL || index > pList->size) return -1;

    *(pList->pElements+index) = pElement;
    pList->size++;
    return 0;

    /* printf("pElements+i = %d", *(pList->pElements+index));
    printf(" \n");
    printf("pElement=%d\n",pElement );*/


}


/** \brief  Remove an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_remove(ArrayList* pList,int index)
{




    //////////////////



    /*  Employee* contenido;
      contenido = (Employee*)get(pList, index);*/


    // printf("estas borrando: %s\n", contenido->nombre);
    // system("pause");
    int rta=-1;
    int i;

    //if(pList  && pVoid ){
    if(pList==NULL || index<0 || index > pList->size) return -1;

    //*((pList->pElements)+index) = 0;
    for(i=index; i< pList->size; i++)  //recorro el arrayList desde el indice hasta el final, y re acomodo para sacar el numero de elemento indicado en los parametros de la funcion
    {
        *(pList->pElements+i)= *(pList->pElements+i+1);

    }
    pList->size--; //ahora la cantidad de items es uno menos..
    rta=0;
    //  printf("BORRADO :) y compactado el arrayList\n");

    //pList->size++;
    // rta=0;

    return rta;

}



/** \brief Removes all of the elements from this list
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer]
 *                  - ( 0) if Ok
 */
int al_clear(ArrayList* pList)
{
    int returnAux = -1;
    if(pList==NULL ) return -1;
    int i;
    for(i=0; i< pList->size; i++)
    {
        *(pList->pElements+i) =NULL;

    }
    pList->size=0;

    return 0;
}



/** \brief Returns an array containing all of the elements in this list in proper sequence
 * \param pList ArrayList* Pointer to arrayList
 * \return ArrayList* Return  (NULL) if Error [pList is NULL pointer]
 *                          - (New array) if Ok
 */
ArrayList* al_clone(ArrayList* pList)
{

    ArrayList* returnAux = NULL;
    if(pList==NULL ) return returnAux;
    int i;
    int size=pList->size;



    void* pElements;
    returnAux=(ArrayList *)malloc(sizeof(ArrayList));

    if(returnAux != NULL)  pElements = malloc(sizeof(void *)*size );
    returnAux->pElements = pElements;

    //  for(i=0; i<pList->size/10;i++){
    //    resizeUp(returnAux);
    //  }
    returnAux->size = pList->size;
    returnAux->reservedSize = pList->reservedSize;
    returnAux->pElements = pList->pElements;



    return returnAux;
}




/** \brief Inserts the element at the specified position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_push(ArrayList* pList, int index, void* pElement)
{

   // printf("DEBUG! %d-> %s %s: %f\n",(pList->pElements+index), ((Employee*)pElement)->name, ((Employee*)pElement)->lastName, ((Employee*)pElement)->salary);

    if(pList==NULL ||pElement==NULL ) return -1;
    if( index<0 || index>(pList->size)) return -1;

    int i;

    if ((pList->size) == (pList->reservedSize))  resizeUp(pList);

    for(i=pList->size; i>=index; i--)
    {
        *(pList->pElements+i+1) = *(pList->pElements+i); //pone en una mas q la ultima, la ultima

    }
    pList->size++;
    *(pList->pElements+index) = pElement;








    return 0;
}



/** \brief Returns the index of the first occurrence of the specified element
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (index to element) if Ok
 */
int al_indexOf(ArrayList* pList, void* pElement)
{
   // printf("DEBUG! [%p] %s %s: %f\n",pElement,  ((Employee*)pElement)->name, ((Employee*)pElement)->lastName, ((Employee*)pElement)->salary);
    int returnAux = -1;
    if(pList==NULL || pElement==NULL) return -1;
    int i;

    for(i=0; i<pList->size; i++){

        if(*(pList->pElements+i) == pElement){
            return i;

        }

    }


    return returnAux;
}



/** \brief Returns true if this list contains no elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Not Empty - (1) if is Empty
 */
int al_isEmpty(ArrayList* pList)
{
    int returnAux = -1;
  if(pList==NULL ) return -1;
  if(pList->size == 0){
    returnAux=1;
  } else{
    returnAux=0;
  }

 return returnAux;
}




/** \brief Remove the item at the given position in the list, and return it.
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid index]
 *                  - ( element pointer) if Ok
 */
void* al_pop(ArrayList* pList,int index)
{
    void* returnAux = NULL;

    if(pList==NULL || index<0 || index>pList->size ) return returnAux;
    returnAux = al_get(pList, index);
    al_remove(pList, index);
    return returnAux;
}


/** \brief Returns a new arrayList with a portion of pList between the specified
 *         fromIndex, inclusive, and toIndex, exclusive.
 * \param pList ArrayList* Pointer to arrayList
 * \param from int Initial index of the element (inclusive)
 * \param to int Final index of the element (exclusive)
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid 'from' or invalid 'to']
 *                  - ( pointer to new array) if Ok
 */
ArrayList* al_subList(ArrayList* pList, int from, int to)
{
    void* returnAux = NULL;

    if(pList==NULL ||  from>(pList->size) || to > (pList->size) || from<0 || to<0 || from>to) return returnAux;
    int sizeNewArrayList = to-from; //esto va bien porq es excluyente
    int i;
    ArrayList* newArrayList =  al_newArrayList();



    for(i=from; i<to; i++){
        al_add(newArrayList, (*(pList->pElements+i)));

       // printf("pList [%d] id=%d \n",i,  ((Employee*)*(pList->pElements+i))->id);
       // printf("newArr [%d] id=%d \n",i-from,  ((Employee*)*(newArrayList->pElements+i-from))->id);


    }



  //  printf("size orig: %d - size new:%d from:%d, to:%d\n", pList->size, newArrayList->size, from, to);
    return newArrayList ;
}





/** \brief Returns true if pList list contains all of the elements of pList2
 * \param pList ArrayList* Pointer to arrayList
 * \param pList2 ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList or pList2 are NULL pointer]
 *                  - (0) if Not contains All - (1) if is contains All
 */
int al_containsAll(ArrayList* pList,ArrayList* pList2)
{
    int returnAux = -1;

    if(pList==NULL || pList2==NULL) return returnAux;
    int i;


    for(i=0; i< pList->size; i++){
      //  printf("pList [%d] id=%d \n",i,  ((Employee*)*(pList->pElements+i))->id);
      //  printf("pList2 [%d] id=%d \n",i,  ((Employee*)*(pList2->pElements+i))->id);
        if(*(pList->pElements+i) != *(pList2->pElements+i)){
            returnAux=0;
            break;
        }else{
            returnAux=1;
        }

    }



    return returnAux;
}

/** \brief Sorts objects of list, use compare pFunc
 * \param pList ArrayList* Pointer to arrayList
 * \param pFunc (*pFunc) Pointer to fuction to compare elements of arrayList
 * \param order int  [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [pList or pFunc are NULL pointer]
 *                  - (0) if ok
 */
int al_sort(ArrayList* pList, int (*pFunc)(void*,void*), int order)
{


    int returnAux = -1;

    if(pList==NULL || pFunc==NULL ) return returnAux;
   if(order!=1 && order!=0) return returnAux;


    int i,j;
    for(i=0; i<pList->size; i++){
        for(j=i+1; j<pList->size; j++){
            if(pFunc==1 && order==0){
                Employee* empAux;
                empAux=*(pList->pElements+i);
                *(pList->pElements+i) = *(pList->pElements+j);
                *(pList->pElements+j) = empAux;
            }
        }
    }



    return returnAux;
}


/** \brief Increment the number of elements in pList in AL_INCREMENT elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer or if can't allocate memory]
 *                  - (0) if ok
 */
int resizeUp(ArrayList* pList)
{


    void* aux;
    int respuesta=-1;

    //if (pList->size == pList->reservedSize){
    aux=realloc(pList->pElements, (pList->reservedSize) +AL_INCREMENT*(sizeof(void*))); // realloc(que puntero, nuevo tamaño)
    if(aux==NULL)
    {
        return -1;
    }
    else
    {
        pList->pElements = aux;
        pList->reservedSize += AL_INCREMENT;
        respuesta=0;
    }

    //}
    return respuesta;


}

/** \brief  Expand an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int expand(ArrayList* pList,int index)
{
    int returnAux = -1;

    return returnAux;
}

/** \brief  Contract an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int contract(ArrayList* pList,int index)
{
    int returnAux = -1;

    return returnAux;
}
