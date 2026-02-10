#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs_macros.h"

/**
 * @pre L'utilizzatore deve aver scaricato una risorsa.
 * @post L'activity' dell'utilizzatore viene salvata nel file activity' sotto forma di struttura.
 */

void aggiorna_file_attivita (FILE *file_utenti, FILE *file_risorse, FILE *file_attivita, int ID_risorsa, int ID_creatore)
{
	incrementa_contatore_download (file_risorse, ID_risorsa);
	salva_attivita_utilizzatore (file_utenti, file_risorse, file_attivita, ID_risorsa);
	aggiorna_valutazione_media_risorsa (file_risorse, file_attivita, ID_risorsa);
	incrementa_numero_download_totali_utenti (file_utenti, ID_creatore);
}

/**
 * @pre L'utilizzatore deve aver selezionato l'opzione di visualizzazione delle activity' degli utilizzatori.
 * @post Viene stampato a schermo un elenco di activity' degli utilizzatori.
 */

void stampa_attivita_utilizzatori (FILE *file_attivita)
{
	attivita_t activity = {"", "", "", "", 0};
	int attivita_trovata = 0;
	int numero_attivita = 0;




	rewind(file_attivita);
	fread(&activity, sizeof(attivita_t), 1, file_attivita);

	if (strlen(activity.username_utilizzatore) >= LUNGHEZZA_MIN_STRINGA)
		attivita_trovata = 1;


	if (attivita_trovata == 1) {

		rewind(file_attivita);
		fread(&activity, sizeof(attivita_t), 1, file_attivita);

		while (!feof(file_attivita)) {

			printf("\n\n\t\t\t\t                       Activity' #%d", numero_attivita + 1);

			puts ("\n\t\t\t\t+---------------------------------------------------------+");

			printf("\n\t\t\t\t\t         Titolo risorsa: << %s >>", activity.titolo_risorsa);

			printf("\n\n\t\t\t\t\t         Di disciplina: %s", activity.disciplina);

			printf("\n\n\t\t\t\t\t         Creata da: %s", activity.username_creatore);

			printf("\n\n\t\t\t\t\t         Scaricata da: %s", activity.username_utilizzatore);

			printf("\n\n\t\t\t\t\t         Valutata : %d/%d stelle", activity.valutazione, N_MASSIMO_STELLE_VALUTAZIONE);

			puts ("\n\n\t\t\t\t+---------------------------------------------------------+\n\n");

			fread(&activity, sizeof(attivita_t), 1, file_attivita);

			numero_attivita++;
		}

		printf("\n\n\t\t\t\t\t    Sono state trovate %d activity'", numero_attivita);

	}

	else
		puts("\n\n\t\t\t  ** Non e' stata trovata alcuna activity' svolta da utilizzatori. **");

	puts("\n\n\n\n\t\t\t       ** L'utente verra' reindirizzato al menu utilizzatore. **\n\n");
	printf("\t\t\t\t\t  ");
	system("pause");

}
