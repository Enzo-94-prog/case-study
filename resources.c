#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs_macros.h"




/**
 * @pre Il creatore deve aver selezionato dal menu creatore l'opzione per aggiungere/modificare una delle sue resources.


 * @post Terminata la procedura di aggiunta/modifica la struttura risorsa puntata contiene al piu' 5 parole chiave.
 */
void acquisisci_parole_chiave (risorsa_t *risorsa)
{
	int i = 0;
	int j = 0;
	char parola_chiave [LUNGHEZZA_MAX_STRINGA];
	int parola_vuota = 0;


	while ((i < N_PAROLE_CHIAVE) && (parola_vuota == 0)) {

		printf("\n\t\t\t\t\t     Parola chiave #%d: ", i+1);
		scanf("%[^\n]s", parola_chiave);

		svuota_buffer_input();

		if (strcmp(parola_chiave, "0") != 0) {

			converti_stringa_in_lower (parola_chiave);

			strcpy(risorsa->parole_chiave[i], parola_chiave);

			i++;

		}

		else
			parola_vuota = 1;

	}

	puts("\n");
}


/**
 * @pre Viene chiamata ogni qualvolta L'utilizzatore ha scaricato una risorsa.

 * @post Terminata la procedura la valutazione media della risorsa e' stata aggiornata in base al numero di volte che e' stata scaricata.
 */
void aggiorna_valutazione_media_risorsa (FILE *file_risorse, FILE *file_attivita, int ID_risorsa)
{
	risorsa_t risorsa = {"", "", "", "", "", 0, 0, 0, 0, 0};
	attivita_t activity = {"", "", "", "", 0};
	int numero_valutazioni = 0;




	fseek(file_risorse, ID_risorsa * sizeof(risorsa), SEEK_SET);
	fread(&risorsa, sizeof(risorsa_t), 1, file_risorse);

	risorsa.valutazione_media = 0;

	rewind (file_attivita);
	fread(&activity, sizeof(attivita_t), 1, file_attivita);

	while (!feof(file_attivita)) {

		if ((strcmp(risorsa.titolo, activity.titolo_risorsa) == 0)) {

			risorsa.valutazione_media += activity.valutazione;

			numero_valutazioni++;

		}


		fread(&activity, sizeof(attivita_t), 1, file_attivita);

	}


	risorsa.valutazione_media = risorsa.valutazione_media / numero_valutazioni;

	fseek(file_risorse, ID_risorsa * sizeof(risorsa), SEEK_SET);
	fwrite(&risorsa, sizeof(risorsa_t), 1, file_risorse);
}


/**
 * @pre Il creatore deve aver selezionato dal menu creatore l'opzione per aggiungere una risorsa alla piattaforma.

 * @post La struttura risorsa contenente i dati della risorsa e' stata scritta nel file resources.
 */
void aggiungi_risorsa (FILE *file_utenti, FILE *file_risorse)
{
	risorsa_t risorsa = {"", "", "", "", "", 0, 0, 0, 0, 0};
	utente_t utente = {"","","","","","", 0, 0, 0};
	int scelta = 0;
	int ID_risorsa = 0;
	int titolo_occupato = 0;
	int n_opzioni = 0;
	int i = 0;




	puts("\n\n\n\n\t\t\t\t    # Indicare il tipo di risorsa da aggiungere.");
	puts("\n\t\t\t\t       0. GIOCO    1. DOCUMENTO\t  2. VIDEO");

	n_opzioni = N_OPZIONI_SCELTA_TERNARIA;
	risorsa.tipo_risorsa = acquisisci_scelta (n_opzioni);

	do {

		printf("\n\n\n\n\t\t\t     # Inserire il titolo della risorsa: ");
		acquisisci_stringa(risorsa.titolo);

		ID_risorsa = genera_ID (risorsa.titolo);

		fseek(file_risorse, ID_risorsa * sizeof(risorsa), SEEK_SET);

		titolo_occupato = verifica_esistenza_risorsa (file_risorse);

		if (titolo_occupato == 0) {

			risorsa.ID_risorsa = ID_risorsa;
			risorsa.ID_creatore = ID_utente_connesso;

			fseek(file_utenti, ID_utente_connesso * sizeof(utente_t), SEEK_SET);
			fread(&utente, sizeof(utente_t), 1, file_utenti);

			strcpy(risorsa.username_creatore, utente.username);

			printf("\n\n\n\n\t\t\t     # Inserire fino a 5 parole chiave da associare alla risorsa.\n");
			puts("\t\t\t          (Digitare 0 per terminare l'inserimento in anticipo)\n\n");
			acquisisci_parole_chiave (&risorsa);

			printf("\n\n\n\n\t\t\t     # Inserire il livello educativo della risorsa: ");
			acquisisci_stringa(risorsa.livello_educativo);

			printf("\n\n\n\n\t\t\t     # Inserire la disciplina della risorsa: ");
			acquisisci_stringa(risorsa.disciplina);

			fseek(file_risorse, ID_risorsa * sizeof(risorsa), SEEK_SET);
	        fwrite(&risorsa, sizeof(risorsa_t), 1, file_risorse);

	    	puts("\n\n\n\n\t\t\t\t         ** Aggiunta della risorsa avvenuta con successo. **");
			puts("\n\n\n\n\t\t\tSi vuole aggiungere una nuova risorsa? Digitare 1 in caso affermativo, altrimenti 0.");

			n_opzioni = N_OPZIONI_SCELTA_BINARIA;
			scelta = acquisisci_scelta (n_opzioni);
		}

		else
		{
			printf("\n\n\n\n\t\t\t# Esiste gia' una risorsa con titolo \"%s\" presente sulla piattaforma! **\n\n" , risorsa.titolo);
		    puts("\t\t\t\t\t** Riprovare con un nuovo titolo... **");
		}

	} while (scelta == 1 || titolo_occupato == 1);


	puts("\n\n\n\n\t\t\t       ** L'utente verra' reindirizzato al menu creatore. **\n\n");
	printf("\t\t\t\t\t");
	system("pause");

}


/**
 * @pre Il creatore deve aver selezionato dal menu creatore l'opzione per cancellare una delle sue resources.
 * @post Dal file resources e' stata rimossa la struttura corrispondente alla risorsa scelta dal proprio creatore.
 */
void cancella_risorsa (FILE *file_risorse)
{
	risorsa_t risorsa = {"", "", "", "", "", 0, 0, 0, 0, 0};
	int scelta = 0;
	int opzione = 0;
	int ID = 0;
	int risorsa_esistente = 0;
	int n_opzioni = 0;




	visualizza_risorse_creatore (file_risorse);

	do {

		do {
			printf("\n\n\n\t\t\t     Inserire l'ID della risorsa che si vuole cancellare: ");
			scanf("%d", &ID);

			fseek(file_risorse, ID * sizeof(risorsa), SEEK_SET);

			if (verifica_esistenza_risorsa (file_risorse))
				risorsa_esistente = 1;
			else
				puts("\n\n\t\t\t       L'ID inserito non e' corretto... Riprovare.\n");

		} while (risorsa_esistente == 0);

		puts("\n\n\n\n\t  Procedere alla cancellazione della risorsa indicata? Immettere 1 in caso affermativo, altrimenti 0.");

		n_opzioni = N_OPZIONI_SCELTA_BINARIA;
		scelta = acquisisci_scelta (n_opzioni);

		if (scelta == 1) {

			fseek(file_risorse, ID * sizeof(risorsa), SEEK_SET);
			fwrite(&risorsa, sizeof(utente_t), 1, file_risorse);

			if (scelta == 1)
				puts("\n\n\n\n\t\t\t\t      ** Risorsa cancellata con successo. **\n");

			puts("\n\n\n\n\t   Si vuole cancellare un'altra risorsa? Immettere 1 in caso affermativo, immettere 0 altrimenti.");

			n_opzioni = N_OPZIONI_SCELTA_BINARIA;
			scelta = acquisisci_scelta (n_opzioni);
		}


	} while (scelta == 1 || risorsa_esistente == 0);

	puts("\n\n\n\n\t\t\t       ** L' utente verra' reindirizzato al menu creatore. **\n\n\n");
	printf("\t\t\t\t\t  ");
	system("pause");
}


/**
 * @pre L'utilizzatore deve aver scaricato una risorsa.
 * @post Il campo del numero di download della struttura corrispondente alla risorsa appena scaricata e' stato incrementato di una unita'.
 */
void incrementa_contatore_download (FILE *file_risorse, int ID_risorsa)
{
	risorsa_t risorsa = {"", "", "", "", "", 0, 0, 0, 0, 0};




	fseek(file_risorse, ID_risorsa * sizeof(risorsa_t), SEEK_SET);
	fread(&risorsa, sizeof(risorsa_t), 1, file_risorse);

	risorsa.numero_download++;

	fseek(file_risorse, ID_risorsa * sizeof(risorsa_t), SEEK_SET);
	fwrite(&risorsa, sizeof(risorsa_t), 1, file_risorse);

}


/**
 * @pre Il creatore deve aver selezionato dal menu creatore l'opzione per modificare una delle sue resources.
 * @post Terminata la procedura di aggiunta/modifica la struttura risorsa puntata conterra' al massimo 5 parole chiave.
 */
void modifica_risorsa (FILE *file_risorse)
{
	risorsa_t risorsa = {"", "", "", "", "", 0, 0, 0, 0, 0};
	int scelta = 0;
	int n_opzioni = 0;
	int i = 0;
	int risorsa_esistente = 0;




	visualizza_risorse_creatore (file_risorse);

	do {

		do {
			printf("\n\n\n\n\t\t\t     # Inserire l'ID della risorsa che si vuole modificare: ");
			risorsa.ID_risorsa = acquisisci_ID ();

			fseek(file_risorse, risorsa.ID_risorsa * sizeof(risorsa), SEEK_SET);

			if (verifica_esistenza_risorsa(file_risorse))
				risorsa_esistente = 1;
			else
				puts("\n\n\t\t\t\t   ** L'ID inserito non e' corretto... Riprovare. **\n");

		} while (risorsa_esistente == 0);


	    if (risorsa_esistente == 1) {

	    	fseek(file_risorse, risorsa.ID_risorsa * sizeof(risorsa), SEEK_SET);
	    	fread(&risorsa, sizeof(risorsa_t), 1, file_risorse);
	    	fseek(file_risorse, risorsa.ID_risorsa * sizeof(risorsa), SEEK_SET);

	    	puts("\n\n\n\n\t\t\t      #Indicare la caratteristica della risorsa da modificare:");
	    	puts("\n\t\t\t   0. Livello Educativo\t     1. Disciplina\t  2. Parole chiave");

	    	n_opzioni = N_OPZIONI_SCELTA_TERNARIA;
	    	scelta = acquisisci_scelta(n_opzioni);

	    	switch (scelta) {

			case 0:
				printf("\n\n\n\n\t\t\t     # Inserire il nuovo livello educativo: ");
				acquisisci_stringa (risorsa.livello_educativo);
				fwrite(&risorsa, sizeof(risorsa_t), 1, file_risorse);
			    break;

			case 1:
				printf("\n\n\n\n\t\t\t     # Inserire la nuova disciplina: ");
			    acquisisci_stringa (risorsa.disciplina);
			    fwrite(&risorsa, sizeof(risorsa_t), 1, file_risorse);
			    break;

			case 2:
				printf("\n\n\n\n\t\t\t     # Inserire fino a 5 nuove parole chiave relative che identificano la risorsa.\n");
				puts("\t\t\t          (Digitare 0 per terminare l'inserimento in anticipo)\n\n");
				acquisisci_parole_chiave (&risorsa);
				fwrite(&risorsa, sizeof(risorsa_t), 1, file_risorse);
				break;

	    	}

	    }

		puts("\n\n\n\n\t\t\t#  Si vuole modificare un'altra risorsa? Digitare 1 in caso affermativo, altrimenti 0.");

	    n_opzioni = N_OPZIONI_SCELTA_BINARIA;
		scelta = acquisisci_scelta (n_opzioni);


	} while (scelta == 1 || risorsa_esistente == 0);


	puts("\n\n\n\n\t\t\t       ** L' utente verra' reindirizzato al menu creatore. **\n\n");
	printf("\t\t\t\t\t   ");
	system("pause");
}


/**
 * @pre L'utilizzatore deve aver immesso un titolo valido per la ricerca dell'omonima risorsa.
 * @post E' stata stampata a schermo la eventuale risorsa ricercata.
 */
void ricerca_risorsa_per_titolo (FILE *file_utenti, FILE *file_risorse, FILE *file_attivita)
{
	risorsa_t risorsa = {"", "", "", "", "", 0, 0, 0, 0, 0};
	attivita_t activity = {"", "", "", "", 0};
	int i = 0;
	int ID_risorsa = 0;
	int scelta = 0;
	int n_opzioni = 0;



	do {
		printf("\n\n\t\t\t     Inserire titolo della risorsa da ricercare: ");
		acquisisci_stringa(risorsa.titolo);

		ID_risorsa = genera_ID (risorsa.titolo);

		scelta = 0;

		fseek(file_risorse, ID_risorsa * sizeof(risorsa_t), SEEK_SET);
		fread(&risorsa, sizeof(risorsa_t), 1, file_risorse);


		if ((ID_risorsa == risorsa.ID_risorsa) && (strlen(risorsa.titolo) >= LUNGHEZZA_MIN_STRINGA)) {

			stampa_risorsa_singola (&risorsa);

			printf("\n\t\t    Vuoi scaricare la risorsa << %s >> ? Digitare 1 in caso affermativo, altrimenti 0.\n", risorsa.titolo);

			n_opzioni = N_OPZIONI_SCELTA_BINARIA;
			scelta = acquisisci_scelta(n_opzioni);

		}

		else
			puts("\n\n\t\t\t\t\t        ** Risorsa non trovata.**\n");

		if (scelta == 1) {

			puts("\n\n\t\t\t\t\t   ** Risorsa scaricata con successo. **\n");

			aggiorna_file_attivita (file_utenti, file_risorse, file_attivita, ID_risorsa, risorsa.ID_creatore);
		}

		printf("\n\n\t\t      Si vuole cercare per titolo un'altra risorsa? Digitare 1 in caso affermativo, altrimenti 0.\n");
		n_opzioni = N_OPZIONI_SCELTA_BINARIA;
		scelta = acquisisci_scelta(n_opzioni);


	} while (scelta == 1);

	puts("\n\n\n\n\t\t\t       ** L'utente verra' reindirizzato al menu utilizzatore. **\n\n");
	printf("\t\t\t\t\t  ");
	system("pause");
}


/**
 * @pre L'utilizzatore deve aver immesso una parola chiave eventualmente associata alla risorsa desiderata.
 * @post Sono state stampata a schermo tutte le eventuali resources associate alla parola chiave immessa dall'utilizzatore.
 */
void ricerca_risorse_per_parola_chiave (FILE *file_utenti, FILE *file_risorse, FILE *file_attivita)
{
	risorsa_t risorsa = {"", "", "", "", "", 0, 0, 0, 0, 0};
	attivita_t activity = {"", "", "", "", 0};
	char parola_chiave [LUNGHEZZA_MAX_STRINGA] = "";
	int numero_risorse_trovate = 0;
	int n_opzioni = 0;
	int scelta = 0;
	int risorsa_esistente = 0;




    do {

    	scelta = 0;

		printf("\n\n\n\t\t\t     Immettere una parola chiave: ");
		acquisisci_stringa (parola_chiave);

		converti_stringa_in_lower (parola_chiave);

		rewind(file_risorse);
		fread(&risorsa, sizeof(risorsa_t), 1, file_risorse);

		while (!feof(file_risorse)) {

			if (verifica_corrispondenza_parola_chiave (&risorsa, parola_chiave)) {
				numero_risorse_trovate++;

				stampa_risorsa_singola (&risorsa);

			}

			fread(&risorsa, sizeof(risorsa_t), 1, file_risorse);
		}

		if (numero_risorse_trovate != 0) {

			do {

				do {
					printf("\n\n\t\t\t     Inserire ID della risorsa che si vuole scaricare: ");
					risorsa.ID_risorsa = acquisisci_ID();

					fseek(file_risorse, risorsa.ID_risorsa * sizeof(risorsa_t), SEEK_SET);

					if (verifica_esistenza_risorsa(file_risorse))
						risorsa_esistente = 1;

					else
						puts("\n\n\t\t\t\t      ** L'ID inserito non e' corretto... Riprovare. ** \n");

				} while (risorsa_esistente == 0);

				fseek(file_risorse, risorsa.ID_risorsa * sizeof(risorsa_t), SEEK_SET);
				fread(&risorsa, sizeof(risorsa_t), 1, file_risorse);

				printf("\n\n\n\t\t    Vuoi scaricare la risorsa << %s >> ? Digitare 1 in caso affermativo, altrimenti 0.\n", risorsa.titolo);

				n_opzioni = N_OPZIONI_SCELTA_BINARIA;
				scelta = acquisisci_scelta(n_opzioni);

				if (scelta == 1) {

					puts("\n\n\t\t\t\t      ** Risorsa scaricata con successo ** \n");

					aggiorna_file_attivita (file_utenti, file_risorse, file_attivita, risorsa.ID_risorsa, risorsa.ID_creatore);
				}

				if (numero_risorse_trovate > 1) {

					puts("\n\n\n\t\t  Si vuole scaricare un'altra risorsa? Digitare 1 in caso affermativo, altrimenti 0.");

					n_opzioni = N_OPZIONI_SCELTA_BINARIA;
					scelta = acquisisci_scelta(n_opzioni);
				}


			} while ((numero_risorse_trovate > 1) && (scelta == 1));

		}
		else
			puts("\n\n\t\t   ** Non e' stata trovata alcuna risorsa corrispondente alla parola chiave inserita. **");

		numero_risorse_trovate = 0;

		puts("\n\n\n\t   Si vuole effettuare una nuova ricerca con parola chiave? Digitare 1 in caso affermativo, altrimenti 0.");

		n_opzioni = N_OPZIONI_SCELTA_BINARIA;
		scelta = acquisisci_scelta(n_opzioni);

	} while (scelta == 1);


	puts("\n\n\n\n\t\t\t       ** L'utente verra reindirizzato al menu utilizzatore. **\n\n");
	printf("\t\t\t\t\t  ");
	system("pause");
}

/**
 * @pre La struttura risorsa deve aver acquisito i dati di una risorsa presente all'interno del file resources.
 * @post L'utente puo' visualizzare i campi della risorsa e proseguire con la sua visualizzazione ed eventualmente scaricarla.
 *  */
void stampa_risorsa_singola (risorsa_t *risorsa)
{
    int i = 0;




	puts ("\n\n\n\t\t\t\t+------------------------------------------------+");

	printf("\t\t\t\t\t\t     # ID: %d #", risorsa->ID_risorsa);
	printf("\n\n\t\t\t\t  Titolo: %s", risorsa->titolo);
	printf("\n\t\t\t\t  Tipo risorsa: ");

	if (risorsa->tipo_risorsa == 0)
		puts("GIOCO");

	else if (risorsa->tipo_risorsa == 1)
		puts("DOCUMENTO");

	else if (risorsa->tipo_risorsa == 2)
		puts("VIDEO");

	printf("\t\t\t\t  Valutazione media: %d ", risorsa->valutazione_media);

	if(risorsa->valutazione_media == 1)
		printf("stella");
	else
		printf("stelle");

	printf("\n\t\t\t\t  Disciplina: %s", risorsa->disciplina);
	printf("\n\t\t\t\t  Livello Educativo: %s", risorsa->livello_educativo);
	printf("\n\t\t\t\t  Numero download: %d", risorsa->numero_download);

	printf("\n\t\t\t\t  Parole chiave: ");

	for (i = 0; i < N_PAROLE_CHIAVE; i++) {

		if (strcmp(risorsa->parole_chiave[i], "") != 0)
			printf("< %s >  ", risorsa->parole_chiave[i]);
	}

	puts ("\n\t\t\t\t+------------------------------------------------+\n\n");
}


/**
 * @pre L'utilizzatore deve aver selezionato dal menu utilizzatore l'opzione per farsi suggerire dal sistema una risorsa.
 * @post Se l'utente ha in precedenza scaricato almeno una risorsa vengono stampate una serie di resources affini ai suoi gusti.
 */
void suggerisci_risorse (FILE *file_utenti, FILE *file_risorse, FILE *file_attivita)
{
	risorsa_t risorsa = {"", "", "", "", "", 0, 0, 0, 0, 0};
	utente_t utente = {"","","","","","", 0, 0, 0};
	attivita_t activity = {"", "", "", "", 0};
	int attivita_trovata = 0;
	int n_opzioni = 0;
	int scelta = 0;
	int risorsa_scelta = 0;
	int ID = 0;
	int risorsa_esistente = 0;
	int numero_risorse_trovate = 0;
	int valida = 0;


	/*
	 * Ammesso che l'utilizzatore abbia scaricato almeno una risorsa in precedenza, allora potr� farsi
	 * suggerire dal sistema tutte le resources della affini alla disciplina della prima risorsa scaricata.
	 */


	fseek(file_utenti, ID_utente_connesso * sizeof(utente_t), SEEK_SET);
	fread(&utente, sizeof(utente_t), 1, file_utenti);

	rewind(file_attivita);
	fread(&activity, sizeof(attivita_t), 1, file_attivita);

	while ((!feof(file_attivita)) && (attivita_trovata == 0)) {

		if ((strcmp(utente.username, activity.username_utilizzatore) == 0)) // l'utente ha effettuato un download in passato
			attivita_trovata = 1;

		if (attivita_trovata == 0)
			fread(&activity, sizeof(attivita_t), 1, file_attivita);
	}

	if (attivita_trovata == 1) {

		rewind(file_risorse);
	    fread(&risorsa, sizeof(risorsa_t), 1, file_risorse);

		while (!feof(file_risorse)) {

			if ((strcmp(risorsa.disciplina, activity.disciplina) == 0))
			{

				stampa_risorsa_singola (&risorsa);

				numero_risorse_trovate++;
			}

			fread(&risorsa, sizeof(risorsa_t), 1, file_risorse);
		}


		if (numero_risorse_trovate > 0) {

			printf("\n\n\t\t    Vuoi scaricare una delle resources suggerite? Digitare 1 in caso affermativo, altrimenti 0.");

			n_opzioni = N_OPZIONI_SCELTA_BINARIA;
			scelta = acquisisci_scelta(n_opzioni);

			do {

				if (scelta == 1) {

					do {

						printf("\n\n\t\t\t     Inserire ID risorsa suggerita che si vuole scaricare: ");
						risorsa.ID_risorsa = acquisisci_ID();

						fseek(file_risorse, risorsa.ID_risorsa * sizeof(risorsa_t), SEEK_SET);

						if (verifica_esistenza_risorsa (file_risorse))
							risorsa_esistente = 1;
						else
							puts("\n\n\t\t\t       L'ID inserito non e' corretto... Riprovare.\n");

					} while (risorsa_esistente == 0);


					puts("\n\n\t\t\tSi vuole scaricare la risorsa? Digitare 1 in caso affermativo, altrimenti 0.");

					n_opzioni = N_OPZIONI_SCELTA_BINARIA;
					scelta = acquisisci_scelta(n_opzioni);

					if (scelta == 1) {

						puts("\n\n\t\t\t\t\t   ** Risorsa scaricata con successo. **\n");

						aggiorna_file_attivita (file_utenti, file_risorse, file_attivita, risorsa.ID_risorsa, risorsa.ID_creatore);

					}

					scelta = 0;

					if (numero_risorse_trovate > 1) {

						puts("\n\n\t\t\t     Si vuole scaricare un'altra delle resources suggerite? Digitare 1 in caso affermativo, altrimenti 0.");

						n_opzioni = N_OPZIONI_SCELTA_BINARIA;
						scelta = acquisisci_scelta(n_opzioni);

					}

				}

			} while ((numero_risorse_trovate > 1) && (scelta == 1));

		}

	}
	else
		puts("\n\n\t\t   Non e' stato possibile suggerire delle resources affini a quelle gia' scaricate in precedenza dall'utente.\n");

	puts("\n\n\n\n\t\t\t       ** L'utente verra' reindirizzato al menu utilizzatore. **\n\n");
	printf("\t\t\t\t\t  ");
	system("pause");
}


/**
 * @pre Il creatore deve aver selezionato dal menu creatore l'opzione per visualizzare tutte le sue resources.
 * @post Vengono stampate tutte le resources aggiunte dal creatore.
 */
void visualizza_risorse_creatore (FILE *file_risorse)
{
	risorsa_t risorsa = {"", "", "", "", "", 0, 0, 0, 0, 0};
	int i = 0;
	int numero_risorse_aggiunte = 0;




	rewind(file_risorse);
	fread(&risorsa, sizeof(risorsa_t), 1, file_risorse);

	while(!feof(file_risorse)) {

		if ((risorsa.ID_creatore == ID_utente_connesso) && (strcmp(risorsa.titolo, "") != 0)) {

			stampa_risorsa_singola (&risorsa);

			numero_risorse_aggiunte++;

		}

		fread(&risorsa, sizeof(risorsa_t), 1, file_risorse);
	}

	if (numero_risorse_aggiunte == 0)
		puts("\n\n\n\n\t\t\t\t     ** L'utente non ha aggiunto alcuna risorsa. **\n\n");
	else
		puts("\n\n\n\n\t\t\t\t      ** Tutte le resources sono state stampate. **\n\n");

	printf("\t\t\t\t\t  ");
	system("pause");

}


/**
 * @pre L'utilizzatore deve aver selezionato dal menu utilizzatore l'opzione per visualizzare le resources piu' scaricate della piattaforma.
 * @post Vengono stampate le prime 5 resources piu' scaricate della piattaforma.
 */
void visualizza_risorse_piu_scaricate (FILE *file_risorse)
{

	risorsa_t risorsa = {"", "", "", "", "", 0, 0, 0, 0, 0};
	int i = 0;
	int pivot = 0;
	int temp = 0;
	int numero_prima_risorsa = 0;
	int numero_ultima_risorsa = -1;
	FILE *file_ordinamento;

	/*
	 * Se possibile, il file sorting viene riempito con tutte le strutture risorsa presenti all'interno
	 * del file resources, al fine di eseguirne l'sorting.
	 */


	if ((file_ordinamento = fopen("data-files/ranking.dat", "wb+")) == NULL)
		puts("\n\n\n\n\t\t\t\t\t File sorting non trovato!");

	else {
		rewind(file_risorse);
		fread(&risorsa, sizeof(risorsa_t), 1, file_risorse);

		while(!feof(file_risorse)) {

			if (strcmp(risorsa.titolo, "") != 0) {

				fwrite (&risorsa, sizeof(risorsa_t), 1, file_ordinamento);

				numero_ultima_risorsa++;
			}

			fread(&risorsa, sizeof(risorsa_t), 1, file_risorse);
		}

		if (numero_ultima_risorsa > 0) {

		rewind(file_ordinamento);
		ordina_risorse_piu_scaricate (file_ordinamento, numero_prima_risorsa, numero_ultima_risorsa);

		printf("\n\n\t\t\t\t\t   Prime %d Resources piu' Scaricate\n\n", N_RISORSE_PIU_SCARICATE + 1);

		rewind(file_ordinamento);
		fread(&risorsa, sizeof(risorsa_t), 1, file_ordinamento);

		for (i = 0; i < N_RISORSE_PIU_SCARICATE; i++) {

			stampa_risorsa_singola (&risorsa);

			fread(&risorsa, sizeof(risorsa_t), 1, file_ordinamento);
		}

		puts("\n");
		}

		else if (numero_ultima_risorsa == -1)
			puts("\n\n\t\t       ** Non vi sono resources all'interno della piattaforma. Impossibile eseguirne l'sorting **");

		else if (numero_ultima_risorsa == 0)
			rewind(file_ordinamento);
			fread(&risorsa, sizeof(risorsa_t), 1, file_ordinamento);

			stampa_risorsa_singola(&risorsa);

			printf("\t\t\t\t\t  ");
			system("pause");


	}

	if (!fclose(file_ordinamento))
		puts("\n\n\n\n\t\t\t\t\t File sorting chiuso con successo.");

	puts("\n\n\n\n\t\t\t       ** L'utente verra' reindirizzato al menu utilizzatore. **\n\n");
	printf("\t\t\t\t\t  ");
	system("pause");
}


/**
 * @pre L'utilizzatore deve aver immesso un titolo valido per la ricerca dell'omonima risorsa.
 * @post Viene stabilito se la parola chiave specificata dall'utente e' associata ad una risorsa.
 */
int verifica_corrispondenza_parola_chiave (risorsa_t *risorsa, char *parola_chiave)
{
	int i = 0;
	int parola_trovata = 0;




	while ((i < N_PAROLE_CHIAVE) && (parola_trovata == 0)) {

		if (strcmp(parola_chiave, risorsa->parole_chiave[i]) == 0) {

			parola_trovata = 1;

		}

		i++;

	}

	return (parola_trovata);
}


/**
 * @pre Viene chiamata ogni qualvolta si vuole aggiungere/modificare/cancellare/ricercare una risorsa, al fine di verificarne l'esistenza.
 * @post Viene confermata o meno l'esistenza della risorsa con la quale si vuole interagire.
 */
int verifica_esistenza_risorsa (FILE *file_risorse)
{
	risorsa_t risorsa = {"", "", "", "", "", 0, 0, 0, 0, 0};
	int risorsa_esistente = 0;

	/*
	 * Dopo che l'utente ha immesso un titolo, si controlla se quest'ultimo � gi� associato ad una risorsa
	 * preesistente. In caso affermativo, la variabile risorsa_esistente acquisisce valore 1.
	 */


	fread(&risorsa, sizeof(risorsa_t), 1, file_risorse);

	if (strlen(risorsa.titolo) >= LUNGHEZZA_MIN_STRINGA)
		risorsa_esistente = 1;

	return (risorsa_esistente);
}
