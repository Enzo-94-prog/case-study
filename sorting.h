#ifndef ORDINAMENTO_H_
#define ORDINAMENTO_H_

#include "structs_macros.h"


/**
 * @brief Esegue un sorting con algoritmo Quicksort delle strutture risorsa contenute nel file resources.
 * @param file_ordinamento Puntatore al file sorting.
 * @param primo Variabile corrispondente alla posizione della prima risorsa nel file sorting.
 * @param ultimo Variabile corrispondente alla posizione dell'ultima risorsa nel file sorting.
 */
void ordina_risorse_piu_scaricate (FILE *file_ordinamento, int primo, int ultimo);


/**
 * @brief Esegue un sorting con algoritmo Quicksort delle strutture utente contenute nel file users.
 * @param file_ordinamento Puntatore al file sorting.
 * @param primo Variabile corrispondente alla posizione del primo utente nel file sorting.
 * @param ultimo Variabile corrispondente alla posizione dell'ultimo utente nel file sorting.
 */
void ordina_utenti (FILE *file_ordinamento, int primo, int ultimo);




#endif /* ORDINAMENTO_H_ */
