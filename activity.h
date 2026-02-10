#ifndef ATTIVITA_H_
#define ATTIVITA_H_

#include "structs_macros.h"



/**
 * @brief Aggiunge una struttura activity' nel file activity'.
 * @param file_utenti Puntatore al file users.
 * @param file_risorse Puntatore al file resources.
 * @param file_attivita Puntatore al file activity'.
 * @param ID_risorsa Variabile contenente l'ID della risorsa appena scaricata.
 * @param ID_creatore Variabile contenente l'ID del creatore della risorsa appena scaricata.
 */
void aggiorna_file_attivita (FILE *file_utenti, FILE *file_risorse, FILE *file_attivita, int ID_risorsa, int ID_creatore);


/**
 * @brief Stampa tutte le activity' svolte dagli utilizzatori della piattaforma.
 * @param file_attivita Puntatore al file activity'.
 */
void stampa_attivita_utilizzatori (FILE *file_attivita);




#endif /* ATTIVITA_H_ */
