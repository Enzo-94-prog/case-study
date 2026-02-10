#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs_macros.h"




/**
 * @pre L'utente deve aver selezionato dall'apposito menu la procedura di accesso alla piattaforma.
 * @post L'utente e' reindirizzato al menu dedicato al proprio tipo di account (creatore o utilizzatore).
 */
void accedi (FILE *file_utenti, FILE *file_risorse, FILE *file_attivita)
{
	char username[LUNGHEZZA_MAX_STRINGA] = {0};
	char password[LUNGHEZZA_MAX_STRINGA] = {0};
    int registrato = 0; // vale 1 se l'account esiste
    int ID = 0;
    int tipo_account = 0;
    int scelta = 0;
    int n_opzioni = 0;




    puts("\n\n\n\n\t\t\t    +-------------------------------------------------------------+");
    puts("\t\t\t    |      DIGITARE 1 SE SI VUOLE CONTINUARE CON L'OPERAZIONE     |");
    puts("\t\t\t    |   DI ACCESSO, ALTRIMENTI 0 PER TORNARE AL MENU PRINCIPALE.  |");
    puts("\t\t\t    +-------------------------------------------------------------+");

    n_opzioni = N_OPZIONI_SCELTA_BINARIA;
    scelta = acquisisci_scelta(n_opzioni);

    if (scelta == 1) {

    	do {
    		puts("\n\n\t\t\t\t\t+--------------------------------------+");
    		puts("\t\t\t\t        |                                      |");
    		puts("\t\t\t\t        |    INSERIRE LE PROPRIE CREDENZIALI   |");
    		puts("\t\t\t\t        |    PER ACCEDERE ALLA PIATTAFORMA.    |");
    		puts("\t\t\t\t        |                                      |");
    		puts("\t\t\t\t\t+--------------------------------------+");

    		printf("\n\n\t\t\t\t\t      Digitare l'username: ");
    		scanf("%[^\n]s", username);
    		svuota_buffer_input ();

    		printf("\n\n\t\t\t\t\t      Digitare la password: ");
    		scanf("%[^\n]s", password);
    		svuota_buffer_input ();

    		ID = genera_ID (username);

    		registrato = controlla_credenziali_accesso (file_utenti, username, password, ID, &tipo_account);


    		if (registrato == 0)
    			puts("\n\n\n\t\t ** Non esiste alcun utente registrato alla piattaforma con le credenziali appena immesse! **\n");

    	} while (registrato == 0);

    	ID_utente_connesso = ID;

    	puts("\n\n\n\t\t\t\t\t  ** Accesso effettuato con successo. **\n\n");
    	printf("\t\t\t\t\t    ");
    	system("pause");


    	if (tipo_account == 1)
    		apri_menu_creatore (file_utenti, file_risorse);

    	else if (tipo_account == 0)
    		apri_menu_utilizzatore (file_utenti, file_risorse, file_attivita);

    }
}


/**
 * @pre L'utente deve aver effettuato l'accesso con il proprio account creatore.
 * @post L'utente puo' effettuare tutte le operazioni disponibili nel menu creatore.
 */
void apri_menu_creatore (FILE *file_utenti, FILE *file_risorse)
{
	int n_opzioni = 0;
	int scelta = 0;
	int logout = 0;
	int account_cancellato = 0;




	do {
		puts("\n\n\n\n\n\n\n\n\n\t\t\t\t\t# BENVENUTO/A NEL MENU CREATORE #");
		puts("\n\n\n");
		puts("\t\t\t\t\t\t+---------------+");
		puts("\t\t\t\t\t\t| MENU CREATORE |");
		puts("\t\t\t       ****************************************************");
		puts("\t\t\t       *                                                  *");
		puts("\t\t\t       *\t     1. Aggiungi risorsa.                 *");
		puts("\t\t\t       *\t     2. Modifica risorsa.                 *");
		puts("\t\t\t       *\t     3. Cancella risorsa.                 *");
		puts("\t\t\t       *\t     4. Visualizza resources creatore.      *");
		puts("\t\t\t       *\t     5. Cancella account.                 *");
		puts("\t\t\t       *\t     0. Effettua Logout.                  *");
		puts("\t\t\t       *                                                  *");
		puts("\t\t\t       ****************************************************\n");



		n_opzioni = N_OPZIONI_MENU_CREATORE;
		scelta = acquisisci_scelta (n_opzioni);

		switch (scelta) {

		case 1:
			aggiungi_risorsa (file_utenti, file_risorse);
			break;

		case 2:
			modifica_risorsa (file_risorse);
			break;

		case 3:
			cancella_risorsa (file_risorse);
			break;

		case 4:
			visualizza_risorse_creatore (file_risorse);
			break;

		case 5:
			account_cancellato = cancella_account (file_utenti);
			break;

		case 0:
	    	puts("\n\n\n\n\t\t\t       ** L'utente verra' reindirizzato al menu principale. **\n\n\n");
	    	printf("\t\t\t\t          ");
	    	system("pause");
	    	logout = 1;
			break;
		}

	} while ((logout == 0) && (account_cancellato == 0));
}


/**
 * @pre L'utente deve aver effettuato l'accesso con il proprio account utilizzatore.
 * @post L'utente puo' effettuare tutte le operazioni disponibili nel menu utilizzatore.
 */
void apri_menu_utilizzatore (FILE *file_utenti, FILE *file_risorse, FILE *file_attivita)
{
	int n_opzioni = 0;
	int scelta = 0;
	int tipo_account  = 0;
	int logout = 0;
	int account_cancellato = 0;




	do {
		puts("\n\n\n\n\n\n\n\n\n\t\t\t\t\t # BENVENUTO/A NEL MENU UTILIZZATORE #");
		puts("\n\n\n");
		puts("\t\t\t\t\t\t   +-------------------+");
		puts("\t\t\t\t\t\t   | MENU UTILIZZATORE |");
		puts("\t\t\t\t***********************************************************");
		puts("\t\t\t\t*                                                         *");
		puts("\t\t\t\t*\t  1. Ricerca risorsa per titolo.                  *");
		puts("\t\t\t\t*\t  2. Ricerca per parola chiave.                   *");
		puts("\t\t\t\t*\t  3. Suggerisci resources.                          *");
		puts("\t\t\t\t*\t  4. Visualizza resources piu' scaricate.           *");
		puts("\t\t\t\t*\t  5. Visualizza creatori piu' popolari.           *");
		puts("\t\t\t\t*\t  6. Visualizza utilizzatori piu' attivi.         *");
		puts("\t\t\t\t*\t  7. Visualizza Statistiche creatori              *");
		puts("\t\t\t\t*\t  8. Stampa activity' utilizzatori.               *");
		puts("\t\t\t\t*\t  9. Cancella account.                            *");
		puts("\t\t\t\t*\t  0. Effettua Logout.                             *");
		puts("\t\t\t\t*                                                         *");
		puts("\t\t\t\t***********************************************************\n");

		n_opzioni = N_OPZIONI_MENU_UTILIZZATORE;

		scelta = acquisisci_scelta (n_opzioni);


		switch (scelta) {

			case 1:
				ricerca_risorsa_per_titolo (file_utenti, file_risorse, file_attivita);
				break;

			case 2:
				ricerca_risorse_per_parola_chiave (file_utenti, file_risorse, file_attivita);
				break;

			case 3:
				suggerisci_risorse (file_utenti, file_risorse, file_attivita);
				break;

			case 4:
				visualizza_risorse_piu_scaricate (file_risorse);
				break;

			case 5:
				tipo_account = 1;
				visualizza_utenti_piu_popolari (file_utenti, tipo_account);
				break;

			case 6:
				tipo_account = 0;
				visualizza_utenti_piu_popolari (file_utenti, tipo_account);
				break;

			case 7:
				visualizza_statistiche_creatori (file_utenti, file_risorse);
				break;

			case 8:
				stampa_attivita_utilizzatori (file_attivita);
				break;

			case 9:
				account_cancellato = cancella_account (file_utenti);
				break;

			case 0:
		    	puts("\n\n\n\n\t\t\t           ** L'utente verra' reindirizzato al menu principale. **\n\n\n");
		    	printf("\t\t\t\t\t        ");
		    	system("pause");
				logout = 1;
				break;
			}

	} while ((logout == 0) && (account_cancellato == 0));
}


/**
 * @pre L'utente deve aver effettuato il download di una risorsa.
 * @post L'utente puo' continuare il download di altre resources o terminare l'operazione.
 */
void incrementa_numero_download_totali_utenti (FILE *file_utenti, int ID_creatore)
{
	utente_t utente = {"", "", "", "", "", "", 0, 0, 0};


	/*
	 * Questa procedura ha il compito di incrementare di un'unit� il numero di download eseguiti
	 * dall'utilizzatore che ha appena scaricato una risorsa e il numero di volte che le resources del creatore
	 * di quest'ultima sono state scaricate.
	 */


	fseek(file_utenti, ID_utente_connesso * sizeof(utente_t), SEEK_SET);
	fread(&utente, sizeof(utente_t), 1, file_utenti);

	utente.numero_download_totali++;

	fseek(file_utenti, ID_utente_connesso * sizeof(utente_t), SEEK_SET);
	fwrite(&utente, sizeof(utente_t), 1, file_utenti);



	fseek(file_utenti, ID_creatore * sizeof(utente_t), SEEK_SET);
	fread(&utente, sizeof(utente_t), 1, file_utenti);

	utente.numero_download_totali++;

	fseek(file_utenti, ID_creatore * sizeof(utente_t), SEEK_SET);
	fwrite(&utente, sizeof(utente_t), 1, file_utenti);
}


/**
 * @pre L'utente deve aver scelto di effettuare la registrazione alla piattaforma.
 * @post L'utente e' reindirizzato al menu principale.
 */
void registra_utente (FILE *file_utenti)
{
	utente_t utente = {"","","","","","", 0, 0, 0};
    int username_disponibile = 0;
    int n_opzioni = 0;
    int scelta = 0;



    puts("\n\n\n\n\t\t\t +-------------------------------------------------------------------+");
    puts("\t\t\t |         DIGITARE 1 SE SI VUOLE CONTINUARE CON L'OPERAZIONE        |");
    puts("\t\t\t |   DI REGISTRAZIONE, ALTRIMENTI 0 PER TORNARE AL MENU PRINCIPALE.  |");
    puts("\t\t\t +-------------------------------------------------------------------+");

    n_opzioni = N_OPZIONI_SCELTA_BINARIA;
    scelta = acquisisci_scelta(n_opzioni);


    if (scelta == 1) {

		puts("\n\n\t\t\t\t\t+---------------------------------------+");
		puts("\t\t\t\t        |                                       |");
		puts("\t\t\t\t        |    INSERIRE TUTTI I DATI RICHIESTI    |");
		puts("\t\t\t\t        |    PER COMPLETARE LA PROCEDURA DI     |");
		puts("\t\t\t\t        |    REGISTRAZIONE ALLA PIATTAFORMA.    |");
		puts("\t\t\t\t        |                                       |");
		puts("\t\t\t\t\t+---------------------------------------+");

    	do {

    		printf("\n\n\n\t\t\t# Inserire l'username che si desidera utilizzare: ");
    		acquisisci_stringa (utente.username);

    		utente.ID = genera_ID (utente.username);

    		username_disponibile = controlla_username_registrazione (file_utenti, utente.ID);

    		if (username_disponibile == 0)
    			puts("\n\n\t\t\t\t         ** Username non disponibile. Riprovare... **");

    	} while (username_disponibile == 0);

    	printf("\n\n\n\n\t\t\t# Inserire la password che si desidera utilizzare: ");
    	acquisisci_stringa(utente.password);

    	printf("\n\n\n\n\t\t\t# Inserire il proprio nome: ");
    	acquisisci_stringa(utente.nome);

    	printf("\n\n\n\n\t\t\t# Inserire il proprio cognome: ");
    	acquisisci_stringa(utente.cognome);

    	printf("\n\n\n\n\t\t\t# Inserire il livello educativo di riferimento: ");
    	acquisisci_stringa(utente.livello_educativo);

    	printf("\n\n\n\n\t\t\t# Inserire la disciplina di specializzazione: ");
    	acquisisci_stringa (utente.disciplina);

    	printf("\n\n\n\n\t\t\tInserire 0 per registrarsi come UTILIZZATORE, oppure 1 per registrarsi come CREATORE: \n");

    	n_opzioni = N_OPZIONI_SCELTA_BINARIA;
    	utente.tipo_account = acquisisci_scelta (n_opzioni);

    	fseek(file_utenti, utente.ID * sizeof(utente_t), SEEK_SET);
    	fwrite(&utente, sizeof(utente_t), 1, file_utenti);

    	printf("\n\n\n\n\t\t\t\t\t ** Registrazione effettuata con successo **\n\n\n");
    	puts("\n\n\n\n\t\t\t           ** L'utente verra' reindirizzato al menu principale. **\n\n\n");
    	printf("\t\t\t\t\t        ");
    	system("pause");
    	puts("\n\n\n\n\n\n\n\n\n\n\n\n");

    }
}


/**
 * @pre L'utilizzatore deve aver effettuato il download di una risorsa.
 * @post Verra' calcolata ed aggiornata la valutazione media della risorsa appena scaricata.
 */
void salva_attivita_utilizzatore (FILE *file_utenti, FILE *file_risorse, FILE *file_attivita, int ID_risorsa)
{
	attivita_t activity = {"", "", "", 0};
	utente_t utente = {"","","","","","", 0, 0, 0};
	risorsa_t risorsa = {"", "", "", "", "", 0, 0, 0, 0, 0};
	int numero_massimo_stelle = 0;




    fseek(file_utenti, ID_utente_connesso * sizeof(utente_t), SEEK_SET);
	fread(&utente, sizeof(utente_t), 1, file_utenti);


	fseek(file_risorse, ID_risorsa * sizeof(risorsa_t), SEEK_SET);
	fread(&risorsa, sizeof(risorsa_t), 1, file_risorse);


	strcpy(activity.titolo_risorsa, risorsa.titolo);               // titolo della risorsa
	strcpy(activity.username_creatore, risorsa.username_creatore); // username del creatore
	strcpy(activity.username_utilizzatore, utente.username);       // username dell'utilizzatore
	strcpy(activity.disciplina, risorsa.disciplina);

	printf("\n\n\t\t\tSi prega di dare una valutazione da 0 a 5 stelle alla risorsa appena scaricata.\n");

	numero_massimo_stelle = N_MASSIMO_STELLE_VALUTAZIONE;
	activity.valutazione = acquisisci_scelta(numero_massimo_stelle);

	localizza_spazio_libero_file_attivita (file_attivita);

	fwrite(&activity, sizeof(attivita_t), 1, file_attivita);
}

/**
 * @pre L'utente deve aver scelto di visualizzare un elenco di users.
 * @post L'utente puo' visualizzare dettagliatamente i dati degli users stampati.
 */
void stampa_utente_singolo (utente_t *utente)
{
	puts ("\n\n\t\t\t\t+---------------------------------------------------------+");

	printf("\n\t\t\t\t  Username: %s", utente->username);

	if (utente->tipo_account == 1) {
		printf("\n\t\t\t\t  Livello educativo: %s", utente->livello_educativo);
		printf("\n\t\t\t\t  Le sue resources sono state scaricate %d volte.\n\n", utente->numero_download_totali);
	}

	else if (utente->tipo_account == 0)
		printf("\n\t\t\t\t  L'utente ha scaricato resources per %d volte.\n\n", utente->numero_download_totali);

	puts ("\t\t\t\t+---------------------------------------------------------+\n");

}


/**
 * @pre L'utilizzatore deve aver scelto dal menu utilizzatore di visualizzare l'elenco di tutti i creatori
 * in base al tipo di resources da essi caricati.
 * @post L'utilizzatore deve poter interagire nuovamente con il menu utilizzatore.
 */
void visualizza_statistiche_creatori (FILE *file_utenti, FILE *file_risorse)
{
	utente_t utente = {"","","","","","", 0, 0, 0};
	risorsa_t risorsa = {"", "", "", "", "", 0, 0, 0, 0, 0};
	int i = 0;
	int gioco = 0;
	int documento = 0;
    int video = 0;




    puts("\n\n\n\t\t\t\t\t     ** STATISTICHE CREATORI **\n");

	rewind (file_utenti);
	fread(&utente, sizeof(utente_t), 1, file_utenti);

	rewind (file_risorse);
	fread(&risorsa, sizeof(	risorsa_t), 1, file_risorse);

	while (!feof(file_utenti)) {

		if (utente.tipo_account == 1) {

			while (!feof(file_risorse)) {

				if (risorsa.ID_creatore == utente.ID) {

					if(risorsa.tipo_risorsa == 0)
						gioco++;

					else if (risorsa.tipo_risorsa == 1)
						documento++;

					else if (risorsa.tipo_risorsa == 2)
						video++;

				}

				fread(&risorsa, sizeof(	risorsa_t), 1, file_risorse);

			}

			rewind (file_risorse);

			puts ("\n\n\n\t\t\t\t+------------------------------------------------+");

			printf("\n\t\t\t\t\t\t  Creatore \"%s\" ", utente.username);

			printf("\n\n\n\t\t\t\t   Giochi caricati      (%d)   ---> ", gioco);

			for (i = 0; i < gioco; i++) {

				printf(" []");

			}

			printf("\n\n\t\t\t\t   Documenti caricati   (%d)   ---> ", documento);

			for (i = 0; i < documento; i++) {

				printf(" []");

			}

			printf("\n\n\t\t\t\t   Video caricati       (%d)   ---> ", video);

			for (i = 0; i < video; i++) {

				printf(" []");

			}

			puts ("\n\n\t\t\t\t+------------------------------------------------+");

			gioco = 0;
			documento = 0;
		    video = 0;

		}

		fread(&utente, sizeof(utente_t), 1, file_utenti);
	}

	puts("\n\n\n\n\t\t\t       ** L'utente verra' reindirizzato al menu utilizzatore. **\n\n");
	printf("\t\t\t\t\t  ");
	system("pause");
}


/**
 * @pre L'utilizzatore deve aver scelto dal menu utilizzatore di visualizzare una lista dei 5 users piu' popolari,
 * specificando anche il loro tipo (creatori o utilizzatori).
 * @post L'utilizzatore deve poter interagire nuovamente con il menu utilizzatore.
 */
void visualizza_utenti_piu_popolari (FILE *file_utenti, int tipo_account)
{
	utente_t utente = {"","","","","","", 0, 0, 0};
	int numero_primo_utente = 0;
	int numero_ultimo_utente = -1;
	int numero_utente = 0;
	FILE *file_ordinamento;


	/*
	 * Se possibile, il file sorting viene riempito con tutte le strutture utente presenti all'interno
	 * del file users, al fine di eseguirne l'sorting.
	 */


	if ((file_ordinamento = fopen("data-files/ranking.dat", "wb+")) == NULL)
		puts("\n\n\n\n\t\t\t\t\t File sorting non trovato!");

	else
	{
		rewind(file_utenti);
		fread(&utente, sizeof(utente_t), 1, file_utenti);

		while(!feof(file_utenti)) {

			if (strlen(utente.username) >= LUNGHEZZA_MIN_STRINGA) {

				if ((tipo_account == 0) && (utente.tipo_account == 0)) {

					fwrite(&utente, sizeof(utente_t), 1, file_ordinamento);

					numero_ultimo_utente++;
				}

				else if ((tipo_account == 1) && (utente.tipo_account == 1)) {

					fwrite(&utente, sizeof(utente_t), 1, file_ordinamento);

					numero_ultimo_utente++;
				}

			}

			fread(&utente, sizeof(utente_t), 1, file_utenti);

		}

		if (numero_ultimo_utente > 0) {

			rewind(file_ordinamento);
			ordina_utenti (file_ordinamento, numero_primo_utente, numero_ultimo_utente);

			puts("\n");

			rewind(file_ordinamento);
			fread(&utente, sizeof(utente_t), 1, file_ordinamento);

			while((!feof(file_ordinamento)) && (numero_utente < N_UTENTI_PIU_POPOLARI)) {

				printf("\n\t\t\t\t\t\t       Utente #%d", numero_utente + 1);

				stampa_utente_singolo (&utente);

				fread(&utente, sizeof(utente_t), 1, file_ordinamento);

				numero_utente++;
			}
		}

		else if (numero_ultimo_utente == -1) {
			printf("\n\n\t\t\t          Non vi sono ");

			if (tipo_account == 1)
				printf("creatori ");
			else
				printf("utilizzatori ");

			printf("registrati alla piattaforma.\n\n");
		}

		else if (numero_ultimo_utente == 0) {

			rewind(file_ordinamento);
			fread(&utente, sizeof(utente_t), 1, file_ordinamento);

			stampa_utente_singolo (&utente);
		}
	}

	if (!fclose(file_ordinamento))
		puts("\n\n\n\n\t\t\t\t\t File sorting chiuso con successo.");

	puts("\n\n\n\n\t\t\t       ** L'utente verra' reindirizzato al menu utilizzatore. **\n\n");
	printf("\t\t\t\t\t  ");
	system("pause");
}


/**
 * @pre L'utente deve aver scelto dall'apposito menu di effettuare la cancellazione del proprio account.
 * @post In base alla scelta effettuata l'utente e' reindirizzato al menu principale della piattaforma
 * oppure al menu precedente.
 */
int cancella_account (FILE *file_utenti)
{
	utente_t utente = {"","","","","","", 0, 0, 0};
	int scelta = 0;
	int n_opzioni = 0;




	fseek(file_utenti, ID_utente_connesso * sizeof(utente_t), SEEK_SET);

	printf("\n\n\n\t\tDigitare 1 per confermare l'eliminazione, altrimenti 0 per tornare al menu principale.");

	n_opzioni = N_OPZIONI_SCELTA_BINARIA;
	scelta = acquisisci_scelta(n_opzioni);

	if (scelta == 1) {

		fwrite(&utente, sizeof(utente_t), 1, file_utenti);

		printf("\n\n\n\n\t\t\t\t\t ** Cancellazione dell'account completata. **\n\n");
		printf("\n\n\n\n\t\t\t       ** L'utente verra reinderizzato al menu principale della piattaforma. **\n\n\n");
		printf("\t\t\t\t\t      ");
		system("pause");
        puts("\n\n\n\n\n\n\n\n\n\n\n\n");
	}
	return (scelta);
}

