/*! \mainpage Simulazione Piattaforma Didattica Online
 *
 * Il sistema deve simulare una porzione delle funzionalita' di una piattaforma per la condivisione
 * di resources didattiche online.
 *
 * - \subpage introduzione_page "Una breve introduzione"
 *
 * - \subpage istruzioni_page "Istruzioni all'uso"
 *
 *
 *@authors Junio Matacchiera e Enzo Marcone
 *@version 2.0
 *@date 31/05/2020
 */

/*! \page introduzione_page Una breve introduzione
 *
 *
 *
 *Questo programma gestisce il caricamento e il dowmload delle resources presenti su una piattaforma didattica.
 *
 *Ogni utente puo' essere un utilizzatore oppure un creatore, descritto da: username, password, nome, cognome,
 *disciplina di specializzazione, livello educativo di rifermimento, tipo account (0 utilizzatore, 1 creatore)
 *ID (codice univoco), numero download totali (relativo alle resources).
 *
 *Le resources della piattaforma sono descritte da: titolo, livello educativo di riferimento, disciplina, parole
 *chiave (massimo 5), username creatore (autore della risorsa), valutazione media (da 0 a 5 stelle), numero
 *download, ID creatore, ID risorsa, tipo risorsa (gioco, documento, video).
 *
 */

/*! \page istruzioni_page Istruzioni all'uso
 *
 *All'avvio, il programma presenta un menu che consente all'utente di interagire con la piattaforma mediante
 *la scelta dell'opzione desiderata, immettendo il numero ad essa associata nel menu.
 *
 */





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "activity.h"
#include "sorting.h"
#include "resources.h"
#include "structs_macros.h"
#include "users.h"
#include "utility.h"





/**
 *Contiene l'ID dell'utente correntemente connesso.
 *@warning Variabile globale.
 */
int ID_utente_connesso = 0;


int main (void) {

	FILE *file_utenti;
	FILE *file_risorse;
    FILE *file_attivita;
	int scelta = 0;
	int logout = 0;
	int n_opzioni = 0;




	if ((file_utenti = fopen("data-files/users.dat", "rb+")) == NULL)
		puts("\n\n\n\n\t\t\t\t\t File users non trovato!");

	if ((file_risorse = fopen("data-files/resources.dat", "rb+")) == NULL)
		puts("\n\n\n\n\t\t\t\t\t File resources non trovato!");

	if ((file_attivita = fopen("data-files/activity.dat", "rb+")) == NULL)
		puts("\n\n\n\n\t\t\t\t\t File activity' non trovato!");

	if ((file_utenti != NULL) && (file_risorse != NULL) && (file_attivita != NULL))
	{
		puts("\n\t\t\t\t\t       File aperti con successo!\n\n\n\n");

		puts("\t\t\t\t    +--------------------------------------------+");
		puts("\t\t\t\t    |                                            |");
		puts("\t\t\t\t    |   BENVENUTO/A NELLA PIATTAFORMA PER LA     |");
		puts("\t\t\t\t    |   CONDIVISIONE DELLE RISORSE DIDATTICHE.   |");
		puts("\t\t\t\t    |                                            |");
		puts("\t\t\t\t    +--------------------------------------------+");

		do {
			puts("\n\n\n");
			puts("\t\t\t\t\t\t  +-----------------+");
			puts("\t\t\t\t\t\t  | MENU PRINCIPALE |");
			puts("\t\t\t\t******************************************************");
			puts("\t\t\t\t*                                                    *");
			puts("\t\t\t\t*\t  1. Accedi alla piattaforma.                *");
			puts("\t\t\t\t*\t  2. Registrati alla piattaforma.            *");
			puts("\t\t\t\t*\t  0. Termina il programma.                   *");
			puts("\t\t\t\t*                                                    *");
			puts("\t\t\t\t******************************************************\n");


			n_opzioni = N_OPZIONI_MENU_PRINCIPALE;
			scelta = acquisisci_scelta (n_opzioni);

			switch(scelta) {    // menu per la scelta dell'operazione da effettuare

			case 1:
				accedi (file_utenti, file_risorse, file_attivita);
				break;

			case 2:
				registra_utente (file_utenti);
				break;

			case 0:
				puts("\n\n\n\n\n\t\t\t\t\t   Chiusura del programma.....");
				logout = 1;
				break;
			}

		} while (logout == 0);



		if (!fclose(file_utenti))
			puts("\n\n\n\n\t\t\t\t\t File users chiuso con successo.");

		if (!fclose(file_risorse))
			puts("\n\n\n\t\t\t\t\t File resources chiuso con successo.");

		if (!fclose(file_attivita))
			puts("\n\n\n\t\t\t\t\t File activity chiuso con successo.");

	}

	puts("\n\n\n\n");
	printf("\t\t\t\t\t");
	system("pause");

	return (0);
}
