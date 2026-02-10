#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "structs_macros.h"



/**
 * @pre L'utente deve inserire in input una stringa che poi andra' salvata in un file.
 * @post L'utente puo' proseguire ad interagire con la piattaforma.
 */
void acquisisci_stringa (char *stringa)
{
	printf("(Minimo %d caratteri, massimo %d).\n" , LUNGHEZZA_MIN_STRINGA, LUNGHEZZA_MAX_STRINGA);

	do {

		printf("\n\t\t\t\t\t\t\t   ");

		scanf("%[^\n]s", stringa);

		svuota_buffer_input();


	} while (!controlla_lunghezza_stringa(stringa));
}

/**
 * @pre All'utente deve essere richiesto di specificare l'ID della risorsa che vuole scaricare.
 * @post L'utente puo' scaricare la risorsa di cui ha immesso l'ID.
 */
int acquisisci_ID (void)
{
	char numero_vettore[5];
	int numero_finale = 0;
	int moltiplicatore = 0;
	int i = 0;




	scanf("%s", numero_vettore);

	svuota_buffer_input ();

	/*
	 * Il numero viene acquisito e salvato all'interno di un vettore di caratteri.
	 * Dopodich�, essendo la sua ultima cifra salvata all'interno dell'ultimo
	 * elemento del vettore, si pone i uguale alla lunghezza del numero, sottraendogli
	 * 1, cosicch� numero[i] sia uguale alla cifra stessa.
	 *
	 * Si avvia un while che si interromper� quando il valore della i sar� minore di 0,
	 * in quanto ad ogni iterazione dello stesso la variabile indice viene decrementata
	 * di un'unit�.
	 *
	 * Alla prima iterazione, la variabile numero_finale acquisisce il valore dell'ultima cifra
	 * del vettore numero (diminuita di 48 per risalire al suo valore numerico, anzich� di carattere,
	 * in quanto � stata acquisita come stringa), moltiplicata per 1. Se in seguito a eventuali cicli
	 * successivi al primo la i sar� ancora maggiore di 0, la variabile moltiplicatore si decuplicher�
	 * alla fine di ognuno (per potersi poi moltiplicare con le cifre del numero che corrispondo alle decine,
	 * centinaia, ecc... e restituire il loro valore posizionale).
	 *
	 * Se, ad esempio, l'utente ha immesso il numero 7, la i varr� 0 all'inizio (strlen (che � 1) - 1 == 0,
	 * in quanto � un'unica cifra). Una volta entrati nel ciclo, numero_finale vedr� il suo valore (pari a 0,
	 * all'inizio) sommato a quello dell'ultima cifra del numero immesso dall'utente (dopo che � stato diminuito
	 * di 48), e moltiplicato per 1, poich� � appunto l'ultima cifra. i verr� decrementato, il while si
	 * interromper�, e il numero_finale varr� 7. Questo valore verr� ritornato all'utente e corrisponder�, eventualmente
	 * al numero da lui immesso inizialmente.
	 * Lo scopo di tutto questo procedimento � assicurarsi che l'utente immetta solo valori validi, dato che
	 * la scanf tradizionale, acquisendo una serie di cifre preceduta per� da anche un solo carattere, tende
	 * a causare problematiche gravi.
	 *
	 *
	 *
	 * Essendo ogni carattere rappresentato da un codice ASCII specifico, ad ognuno corrisponde un particolare
	 * codice numerico. Per esempio, il numero 0 ha un codice ASCII pari a 48, 1 49, (quando sono acquisiti
	 * come caratteri) e cos� via...
	 * Per cui, avendo acquisito quello che per noi � un numero, ma come carattere (il placeholder %s nella scanf
	 * ce lo indica), al fine di risalire al suo valore numerico, � sufficiente sottrargli 48.
	 */

	moltiplicatore = 1;

	i = strlen(numero_vettore) - 1;

	while (i >= 0) {

		numero_finale += (numero_vettore[i] - 48) * moltiplicatore;
		moltiplicatore *= 10;

		i--;
	}

	return (numero_finale);
}


/**
 * @pre L'utente deve aver immesso una stringa di sufficiente lunghezza.
 * @post La stringa immessa dall'utente avra' tutti i caratteri minuscoli.
 */
void converti_stringa_in_lower (char *stringa)

{
	int i = 0;




	for (i = 0; i < strlen(stringa); i++)
		*(stringa + i) = tolower( (*(stringa + i)) );
}


/**
 * @pre L'utente deve aver scaricato e valutato una risorsa.
 * @post Sara' stata individuata la prima posizione libera all'interno del file activity'.
 */
void localizza_spazio_libero_file_attivita (FILE *file_attivita)
{
	attivita_t activity = {"", "", "", 0};


	/*
	 * Il puntatore al file attivit� viene posizionato sul primo punto libero di questi.
	 */



	rewind(file_attivita);

	while (fread(&activity, sizeof(attivita_t), 1, file_attivita) != 0);
}


/**
 * @pre Deve essere avvenuta una funzione di acquisizione dell'input.
 * @post Il buffer di input risultera' vuoto.
 */
void svuota_buffer_input (void)
{

	/*
	 * In seguito ad una scanf, questa procedura ha lo scopo di svuotare il buffer di input da tutti
	 * i caratteri eventualmente rimasti al suo interno, cos� da evitare effetti indesiderati sui successivi
	 * input.
	 */
	while (getchar() != '\n');
}


/**
 * @pre L'utente deve scegliere una delle opzioni presenti in un menu o in una scelta multipla.
 * @post L'utente avra' scelto un'opzione necessariamente valida.
 */
int acquisisci_scelta (int n_opzioni)
{
	char scelta[2];
	int lunghezza_scelta = 0;

	/*
	 * Questa funzione viene eseguita ogni qualvolta all'utente � richiesto di effettuare una scelta dal
	 * menu visualizzato al momento, immettendo un numero che le corrisponda. La scanf da questo punto
	 * di vista � problematica, in quanto immissioni "miste" come "1a" sono da essa riconosciute identiche
	 * a "1". Quindi la scelta dell'utente (che dev'essere numerica, alla fine) viene salvata all'interno
	 * di un vettore di caratteri di due elementi. Se viene individuato che il secondo non � vuoto, allora
	 * gli verr� richiesta una nuova immissione (perch� la scelta corretta deve essere di UNA sola cifra).
	 * Il motivo per cui a scelta[0] viene sottratto 48 � analogo a quello illustrato nel commento
	 * di << int acquisisci_ID (void) >>.
	 */


	do {

		printf("\n\n\t\t\t     Digitare il numero corrispondente alla scelta desiderata: ");
		scanf("%s", scelta);

		svuota_buffer_input();

		lunghezza_scelta = strlen(scelta);

		*scelta = *scelta - 48;

		if ( (lunghezza_scelta != 1) || !(controlla_scelta (scelta, n_opzioni)))
			puts("\n\t\t\t\t       **  Scelta non valida... riprovare **\n");

	} while ((lunghezza_scelta != 1) || !(controlla_scelta (scelta, n_opzioni)) );


	return (*scelta);
}


/**
 * @pre L'utente deve aver immesso un username ed una password di lunghezza valida.
 * @post Se l'account esiste l'utente verra' indirizzato nel menu dedicato, altrimenti si ripetera'
 * l'immissione delle credenziali.
 */
int controlla_credenziali_accesso (FILE *file_utenti, char *username, char *password, int ID, int *tipo_account)
{
	utente_t utente = {"","","","","","", 0, 0};
	int account_trovato = 0;


	/*
	 * Se nel file users viene individuata una struttura associata all'username ed alla password immessi
	 * dall'utente, la variabile account_trovata acquisir� il valore 1, cos� da segnalare alla funzione
	 * chiamante che l'account specificato dall'utente esiste, e che questi pu� effettuare l'accesso.
	 */


	fseek(file_utenti, ID * sizeof(utente_t), SEEK_SET);
	fread(&utente, sizeof(utente_t), 1, file_utenti);

		if ((strcmp(utente.username, username) == 0) && (strcmp(utente.password, password) == 0))
			account_trovato = 1;


	*tipo_account = utente.tipo_account;

	return (account_trovato);
}


/**
 * @pre L'utente deve aver immesso una stringa di qualsivoglia lunghezza.
 * @post L'utente avra' immesso una stringa di lunghezza valida e potra' continuare con l'inserimento.
 */
int controlla_lunghezza_stringa (char *stringa)
{
	int valida = 0;
	int lunghezza_stringa = strlen(stringa);




	if (lunghezza_stringa > LUNGHEZZA_MAX_STRINGA)
		printf("\n\t\t\t\t       ** Stringa eccessivamente lunga! Riprovare... **\n\n\n");

	else if (lunghezza_stringa < LUNGHEZZA_MIN_STRINGA)
		printf("\n\t\t\t\t       ** Stringa eccessivamente corta! Riprovare... **\n\n\n");

	else
		valida = 1;

	return (valida);
}


/**
 * @pre L'utente deve aver immesso un valore numerico.
 * @post L'utente puo' continuare ad interagire con la piattaforma.
 */
int controlla_scelta (char *scelta, int n_opzioni)
{
	int successo = 0;  // vale 1 se "scelta" e' valida


	/*
	 * Viene comparato il valore di scelta[0], che � una cifra, con quello di n_opzioni, al fine di stabilire
	 * se la scelta effettuata dall'utente � fra quelle consentite.
	 * In caso affermativo, la variabile successo viene avvalorata ad 1. Infine, il suo valore � restituito
	 * dalla presente funzione.
	 */


	while ((successo != 1) && (n_opzioni != -1)) {

		if (*scelta == n_opzioni)
			successo = 1;

		n_opzioni--;
	}

	return (successo);
}


/**
 * @pre L'utente deve aver immesso un username in fase di registrazione.
 * @post L'utente puo' continuare la registrazione dell'account.
 */
int controlla_username_registrazione (FILE *file_utenti, int ID)
{
	utente_t utente = {"","","","","","", 0, 0, 0};
	int username_libero = 0;


	/*
	 * Se l'username immesso dall'utente in fase di registrazione non figura all'interno di nessuna struttura
	 * del file users, allora la variabile username_libero viene avvalorata ad 1, e dunque restituita come
	 * valore di ritorno dalla presente funzione.
	 */

	fseek(file_utenti, ID * sizeof(utente_t), SEEK_SET);

	fread(&utente, sizeof(utente_t), 1, file_utenti);

	if ((strcmp(utente.username,"") == 0))
		username_libero = 1;


	return (username_libero);
}


/**
 * @pre L'utente deve aver immesso una stringa di lunghezza valida.
 * @post L'utente/la risorsa sara' localizzato/a a seconda dell'ID generato.
 */
int genera_ID (char *stringa)
{
	int i = 0;
	unsigned int ID = 0;
	char stringa_ID[strlen(stringa)];

	/*
	 * La stringa immessa dall'utente viene utilizzata per generare un ID, univoco, adoperato poi per localizzare
	 * le strutture (users e resources) all'interno dei file a loro corrispondenti.
	 * Ogni carattere della stringa (composta esclusivamente da caratteri minuscoli, vedasi la procedura
	 * converti_stringa_lower) viene convertito in un numero, sommato e moltiplicato per dei numeri in base
	 * alla sua posizione relativa, cio� rispetto agli altri caratteri.
	 */


	strcpy(stringa_ID, stringa);
	converti_stringa_in_lower(stringa_ID);

	for (i = 0; i < strlen(stringa_ID); i++) {

		ID += *(stringa_ID + i) * (i + 1);

	}

	return (ID);
}


