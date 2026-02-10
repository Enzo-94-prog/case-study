#ifndef STRUCT_MACRO_H_
#define STRUCT_MACRO_H_




/**
 * Costante utilizzata per memorizzare il massimo numero di caratteri in una stringa.
 */
#define LUNGHEZZA_MAX_STRINGA 40
/**
 *Costante utilizzata per memorizzare il minimo numero di caratteri in una stringa.
 */
#define LUNGHEZZA_MIN_STRINGA 3
/**
 *Costante utilizzata per memorizzare il numero massimo di opzioni del menu principale ( a partire dallo 0)	.
 */
#define N_OPZIONI_MENU_PRINCIPALE 2
/**
 *Costante utilizzata per memorizzare il numero massimo di opzioni del menu creatore ( a partire dallo 0).
 */
#define N_OPZIONI_MENU_CREATORE 5
/**
 *Costante utilizzata per memorizzare il numero massimo di opzioni del menu utilizzatore ( a partire dallo 0).
 */
#define N_OPZIONI_MENU_UTILIZZATORE 9
/**
 *Costante utilizzata per memorizzare il numero massimo di opzioni della scelta binaria ( a partire dallo 0).
 */
#define N_OPZIONI_SCELTA_BINARIA 1
/**
 *Costante utilizzata per memorizzare il numero massimo di opzioni della scelta ternaria ( a partire dallo 0).
 */
#define N_OPZIONI_SCELTA_TERNARIA 2
/**
 *Costante utilizzata per memorizzare il numero massimo di opzioni della scelta quaternaria ( a partire dallo 0).
 */
#define N_OPZIONI_SCELTA_QUATERNARIA 3
/**
 *Costante utilizzata per memorizzare il numero massimo di users da mostrare nella classifica.
 */
#define N_UTENTI_PIU_POPOLARI 5
/**
 *
 *Costante utilizzata per memorizzare il numero massimo di parole chiave associate ad una risorsa.
 */
#define N_PAROLE_CHIAVE 5
/**
 *Costante utilizzata per memorizzare il numero massimo di stelle che lutente puo' attribuire come voto
 *ad una risorsa (a partire da 0).
 */
#define N_MASSIMO_STELLE_VALUTAZIONE 5
/**
 *Costante utilizzata per memorizzare il numero massimo di resources che lutente puo' visualizzare
 *nella stampa delle resources piu' scaricate.
 */
#define N_RISORSE_PIU_SCARICATE 4




int ID_utente_connesso;

/**
 * Tipo enumerato che associa ad ogni tipo di risorsa un valore numerico.
 */
typedef enum {
	gioco,    /**< 0 */
	documento,/**< 1 */
	video     /**< 2 */

} tipo_risorsa_t;

/**
 * Struttura dati contenente le informazioni di ogni utente registrato alla piattaforma.
 */
typedef struct {

	char username[LUNGHEZZA_MAX_STRINGA]; /**< Username dell'utente.*/
	char password[LUNGHEZZA_MAX_STRINGA]; /**< Password dell'utente.*/
	char nome[LUNGHEZZA_MAX_STRINGA]; /**< Nome dell'utente.*/
	char cognome[LUNGHEZZA_MAX_STRINGA]; /**< Cognome dell'utente.*/
	char disciplina[LUNGHEZZA_MAX_STRINGA]; /**< Disciplina di specializzazione dell'utente.*/
	char livello_educativo[LUNGHEZZA_MAX_STRINGA]; /**< Livello educativo di riferimento dell'utente.*/
	int tipo_account; /**< Tipo account dell'utente (1 = creatore, 0 = utilizzatore).*/
	int ID; /**< Codice identificativo univoco dell'utente.*/
	int numero_download_totali; /**< Numero di download effettuati/Numero di volte che le proprie resources sono state scaricate dall'utilizzatore/dal creatore.*/

} utente_t;

/**
 * Struttura dati contenente le informazioni di ogni risorsa salvata sulla piattaforma.
 */
typedef struct {

	char titolo[LUNGHEZZA_MAX_STRINGA]; /**< Titolo della risorsa. */
	char livello_educativo[LUNGHEZZA_MAX_STRINGA]; /**< Livello educativo di riferimento della risorsa. */
	char disciplina[LUNGHEZZA_MAX_STRINGA]; /**< Disciplina della risorsa. */
    char parole_chiave[N_PAROLE_CHIAVE][LUNGHEZZA_MAX_STRINGA]; /**< Parole chiave della risorsa. */
	char username_creatore[LUNGHEZZA_MAX_STRINGA]; /**< Username del creatore della risorsa. */
	int valutazione_media; /**< Valutazione media della risorsa. */
	int numero_download; /**< Numero di volte in cui e' stata scaricata la risorsa. */
	int ID_creatore; /**< Codice identificativo univoco del creatore della risorsa. */
	int ID_risorsa; /**< Codice identificativo univoco della risorsa. */
	tipo_risorsa_t tipo_risorsa; /**< 0 = Gioco, 1 = Documento, 2 = Video */

} risorsa_t;

/**
 * Struttura dati contenente i dettagli di ogni activity' avvenuta sulla piattaforma.
 */
typedef struct {

	char titolo_risorsa[LUNGHEZZA_MAX_STRINGA]; /**< Titolo della risorsa scaricata. */
	char username_creatore[LUNGHEZZA_MAX_STRINGA]; /**< Username del creatore della risorsa. */
	char username_utilizzatore[LUNGHEZZA_MAX_STRINGA]; /**< Username dell'utilizzatore della risorsa. */
	char disciplina[LUNGHEZZA_MAX_STRINGA]; /**< Disciplina della risorsa. */
	int valutazione; /**< Valutazione data dall'utilizzatore alla risorsa. */

} attivita_t;




#endif /* STRUCT_MACRO_H_ */
