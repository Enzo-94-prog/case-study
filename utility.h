#ifndef UTILITY_H_
#define UTILITY_H_


#include "structs_macros.h"


/**
 * @brief Acquisice una stringa in input dall'utente, assicurandosi che sia di lunghezza sufficiente.
 * @param stringa Puntatore al primo carattere della stringa in cui viene salvato l'input dell'utente.
 */
void acquisisci_stringa (char *stringa);

/**
 * @brief Acquisisce dall'utente l'ID relativo alla risorsa che vuole scaricare.
 */
void acquisisci_ID (void);


/**
 * @brief Rende tutti i caratteri della stringa minuscoli.
 * @param stringa Immessa dall'utente.
 */
void converti_stringa_in_lower (char *stringa);

/**
 * @brief Localizza il primo spazio libero all'interno del file activity'.
 * @param file_attivita Puntatore al file activity'.
 */
void localizza_spazio_libero_file_attivita (FILE *file_attivita);

/**
 * @brief Svuota il buffer di input.
 */
void svuota_buffer_input (void);

/**
 * @brief Acquisisce l'input dell'utente.
 * @param n_opzioni Variabile contenente il valore numerico delle opzioni presenti in un menu
 * o in una scelta multipla (lo 0 e' incluso).
 * @return Ritorna il primo valore corretto acquisito.
 */
int acquisisci_scelta (int n_opzioni);

/**
 * @brief Controlla che le credenziali d'accesso immesse dall'utente siano valide.
 * @param file_utenti Puntatore al file users.
 * @param username Username immesso dall'utente.
 * @param password Password immessa dall'utente.
 * @param ID ID generato a partire dall'username immesso dall'utente.
 * @param tipo_account Variabile che acquisisce valore 0 se l'utente e' un utilizzatore,
 * altrimenti 1 se e' un creatore.
 * @return Ritorna 1 se esiste un account corrispondente alle credenziali immesse dall'utente, altrimenti 0.
 */
int controlla_credenziali_accesso (FILE *file_utenti, char *username, char *password, int ID, int *tipo_account);

/**
 * @brief Controlla se la lunghezza della stringa immessa dall'utente sia valida o meno.
 * @param stringa Immessa dall'utente.
 * @return Ritorna 1 se la stringa e' valida, 0 altrimenti.
 */
int controlla_lunghezza_stringa (char *stringa);

/**
 * @brief Controlla l'input dell'utente.
 * @param scelta Immessa dall'utente.
 * @param n_opzioni Variabile contenente il valore numerico delle opzioni presenti in un menu
 * o in una scelta multipla (lo 0 e' incluso).
 * @return Ritorna 1 se la scelta dell'utente e' valida, 0 altrimenti.
 */
int controlla_scelta (char *scelta, int n_opzioni);

/**
 * @brief Controlla che l'username immesso dall'utente non sia utilizzato da un altro utente.
 * @param file_utenti Puntatore al file users.
 * @param ID generato a partire dall'username immesso dall'utente.
 * @return Ritorna 1 se l'username immesso e' libero, 0 altrimenti.
 */
int controlla_username_registrazione (FILE *file_utenti, int ID);

/**
 * @brief Genera un ID a partire dalla stringa immessa dall'utente.
 * @param stringa Immessa dall'utente.
 * @return Ritorna un valore numerico corrispondente alla stringa immessa.
 */
int genera_ID (char *stringa);




#endif /* UTILITY_H_ */
