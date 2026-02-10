#ifndef RISORSE_H_
#define RISORSE_H_
#include "structs_macros.h"


/**
 * @brief Acquisisce le parole chiave che si vogliono associare alla risorsa in fase di creazione o di modifica.
 *
 * @param risorsa Puntatore alla struttura contenente i dati della risorsa che si vuole creare/modificare.
 */
void acquisisci_parole_chiave (risorsa_t *risorsa);

/**
 * @brief Aggiorna la valutazione media della risorsa che l'utente ha appena scaricato.

 * @param file_risorse Puntatore al file resources.
 * @param file_attivita Puntatore al file activity'.
 * @param ID_risorsa Variabile contenente l'ID della risorsa di cui aggiornare la valutazione media.
 */
void aggiorna_valutazione_media_risorsa (FILE *file_risorse, FILE *file_attivita, int ID_risorsa);

/**
 * @brief Acquisisce dal creatore tutte le caratteristiche proprie della risorsa che vuole aggiungere.
 * @param file_utenti Puntatore al file users.
 * @param file_risorse Puntatore al file resources.
 */
void aggiungi_risorsa (FILE *file_utenti, FILE *file_risorse);

/**

 * @brief Cancella dal file resources la risorsa scelta dal proprio creatore.

 * @param file_risorse Puntatore al file resources.
 */
void cancella_risorsa (FILE *file_risorse);

/**
 * @brief Incrementa di una unita' il numero di volte che la risorsa e' stata scaricata.
 *
 * @param file_risorse Puntatore al file resources.
 * @param ID_risorsa Variabile contenente l'ID della risorsa appena scaricata dall'utente.
 */
void incrementa_contatore_download (FILE *file_risorse, int ID_risorsa);

/**
 * @brief Modifica un campo della struttura corrispondente alla risorsa scelto dal creatore.
 * @param file_risorse Puntatore al file resources.
 */
void modifica_risorsa (FILE *file_risorse);

/**
 * @brief Ricerca all'interno del file resources la struttura, se esiste, corrispondente alla risorsa dal titolo specificato dall'utilizzatore.
 * @param file_utenti Puntatore al file users.
 * @param file_risorse Puntatore al file resources.
 * @param file_attivita Puntatore al file activity'.
 */
void ricerca_risorsa_per_titolo (FILE *file_utenti, FILE *file_risorse, FILE *file_attivita);

/**
 * @brief Ricerca all'interno del file resources la struttura, se esiste, corrispondente alla risorsa associata alla parola chiave immessa dall'utilizzatore.
 * @param file_utenti Puntatore al file users.
 * @param file_risorse Puntatore al file resources.
 * @param file_attivita Puntatore al file activity'.
 */
void ricerca_risorse_per_parola_chiave (FILE *file_utenti, FILE *file_risorse, FILE *file_attivita);

/**
 * @brief Stampa a schermo una serie di resources affini a quelle gia' scaricate (almeno una) in precedenza dall'utilizzatore.
 * @param file_utenti Puntatore al file users.
 * @param file_risorse Puntatore al file resources.
 * @param file_attivita Puntatore al file activity'.
 */
void suggerisci_risorse (FILE *file_utenti, FILE *file_risorse, FILE *file_attivita);

/**
 * @brief Visualizza tutte le resources create dal creatore.
 * @param file_risorse Puntatore al file resources.
 */
void visualizza_risorse_creatore (FILE *file_risorse);

/**
 * @brief Stampa i dati della singola risorsa indicata dal puntatore.
 * @param risorsa Puntatore alla risorsa i cui dati andranno stampati a schermo.
 */
void stampa_risorsa_singola (risorsa_t *risorsa);

/**
 * @brief Visualizza le prime 5 resources piu' scaricate della piattaforma.
 * @param file_risorse Puntatore al file resources.
 */
void visualizza_risorse_piu_scaricate (FILE *file_risorse);

/**
 * @brief Ha lo scopo di verificare se almeno una delle parole chiave della risorsa coincida con quella immessa dall'utente.
 * @param risorsa Puntatore alla struttura contenente i dati della risorsa che si vuole controllare.
 * @param parola_chiave Puntatore al primo carattere della stringa immessa dall'utente.
 * @return Ritorna 1 se e' stata trovata corrispondenza fra una delle parole chiave della risorsa e quella immessa dall'utente, altrimenti 0.
 */
int verifica_corrispondenza_parola_chiave (risorsa_t *risorsa, char *parola_chiave);

/**
 * @brief Controlla se alla posizione specificata dall'ID corrispondente al titolo indicato dall'utente
 * e' presente una risorsa.
 * @param file_risorse Puntatore al file resources.
 * @return Ritorna 1 se in quella posizione non vi e' alcuna risorsa, altrimenti 0.
 */
int verifica_esistenza_risorsa (FILE *file_risorse);


#endif /* RISORSE_H_ */
