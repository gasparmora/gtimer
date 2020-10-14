#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ncurses.h>
#include <unistd.h>
#include <assert.h>

#define DELAY_FOR_NCURSES 30000 // To control refresh rate

time_t start_time,current_time; // To measure execution time (wall clock)

void Print_Digit(unsigned int value, unsigned int y, unsigned int x)
{
	assert(value<10);
	if(value==0) {
		mvprintw(y,   x,"  #####  ");
		mvprintw(y+1, x," ##   ## ");
		mvprintw(y+2, x," ##   ## ");
		mvprintw(y+3, x," ##   ## ");
		mvprintw(y+4, x," ##   ## ");
		mvprintw(y+5, x," ##   ## ");
		mvprintw(y+6, x,"  #####  ");
	} else if(value==1) {
		mvprintw(y,   x,"    ##   ");
		mvprintw(y+1, x,"   ###   ");
		mvprintw(y+2, x,"  ####   ");
		mvprintw(y+3, x," ## ##   ");
		mvprintw(y+4, x,"    ##   ");
		mvprintw(y+5, x,"    ##   ");
		mvprintw(y+6, x," ####### ");
	} else if(value==2) {
		mvprintw(y,   x,"   ####  ");
		mvprintw(y+1, x,"  ##  ## ");
		mvprintw(y+2, x," ##   ## ");
		mvprintw(y+3, x,"     ##  ");
		mvprintw(y+4, x,"    ##   ");
		mvprintw(y+5, x,"  ##     ");
		mvprintw(y+6, x," ####### ");
	} else if(value==3) {
		mvprintw(y,   x,"  ####   ");
		mvprintw(y+1, x," #   ##  ");
		mvprintw(y+2, x,"    ##   ");
		mvprintw(y+3, x,"  ##     ");
		mvprintw(y+4, x,"    ##   ");
		mvprintw(y+5, x,"      ## ");
		mvprintw(y+6, x," ######  ");
	} else if(value==4) {
		mvprintw(y,   x,"     ##  ");
		mvprintw(y+1, x,"   ####  ");
		mvprintw(y+2, x," ##  ##  ");
		mvprintw(y+3, x,"######## ");
		mvprintw(y+4, x,"     ##  ");
		mvprintw(y+5, x,"     ##  ");
		mvprintw(y+6, x,"    #### ");
	} else if(value==5) {
		mvprintw(y,   x," ######  ");
		mvprintw(y+1, x," ##      ");
		mvprintw(y+2, x," ###     ");
		mvprintw(y+3, x,"   ####  ");
		mvprintw(y+4, x,"     ##  ");
		mvprintw(y+5, x,"     ##  ");
		mvprintw(y+6, x," #####   ");
	} else if(value==6) {
		mvprintw(y,   x,"    #### ");
		mvprintw(y+1, x,"  ##     ");
		mvprintw(y+2, x," ##      ");
		mvprintw(y+3, x," #####   ");
		mvprintw(y+4, x," ##   #  ");
		mvprintw(y+5, x," ##   #  ");
		mvprintw(y+6, x,"  #####  ");
	} else if(value==7) {
		mvprintw(y,   x," ####### ");
		mvprintw(y+1, x,"      ## ");
		mvprintw(y+2, x,"     ##  ");
		mvprintw(y+3, x,"    ##   ");
		mvprintw(y+4, x,"   ##    ");
		mvprintw(y+5, x,"   ##    ");
		mvprintw(y+6, x,"   ##    ");
	} else if(value==8) {
		mvprintw(y,   x,"  #####  ");
		mvprintw(y+1, x," ##   ## ");
		mvprintw(y+2, x,"  ## ##  ");
		mvprintw(y+3, x,"  #####  ");
		mvprintw(y+4, x," ##   ## ");
		mvprintw(y+5, x," ##   ## ");
		mvprintw(y+6, x,"  #####  ");
	} else if(value==9) {
		mvprintw(y,   x,"  #####  ");
		mvprintw(y+1, x," ##   ## ");
		mvprintw(y+2, x," ##   ## ");
		mvprintw(y+3, x,"  ###### ");
		mvprintw(y+4, x,"     ##  ");
		mvprintw(y+5, x,"    ##   ");
		mvprintw(y+6, x,"  ###    ");
	}
}

void Print_DosPuntos(unsigned int y, unsigned int x)
{
	mvprintw(y,   x,"    ");
	mvprintw(y+1, x," ** ");
	mvprintw(y+2, x," ** ");
	mvprintw(y+3, x,"    ");
	mvprintw(y+4, x," ** ");
	mvprintw(y+5, x," ** ");
	mvprintw(y+6, x,"    ");
}
void Print_Number(unsigned int value, unsigned int y, unsigned int x)
{
	unsigned int primer_digito, segundo_digito;
	if(value<10) {
		Print_Digit(0,y,x);
		Print_Digit(value,y,x+9);
	} else {
		primer_digito = value/10;
		segundo_digito = value-(primer_digito*10);
		Print_Digit(primer_digito,y,x);
		Print_Digit(segundo_digito,y,x+9);
	}
}

int main(void)
{
	double elapsed_time;
	time(&start_time);
	int x = 0, y = 0; // Para posición de la bolita que rebota
	int max_y = 0, max_x = 0; // Para límites de pantalla
	int next_x = 0;
	int direction = 1;
	int c; // Para recoger las teclas del usuario
	int quit = 0;
	int pausa = 0;
	unsigned int horas=0;
	unsigned int minutos=0, segundos=0;
	double work_time = 0;
	double tiempo_restante = 0;

	initscr();			     // Start curses mode 		
	//raw();				     // Line buffering disabled. Exit with ctrl+c disabled as well
	keypad(stdscr, TRUE);  // We get F1, F2 etc..		
	noecho();              // Don't echo() while we do getch
	curs_set(FALSE);       // Removes cursor
	nodelay(stdscr, TRUE); // So getch() doesn't wait for input, just returns ERR until something is pressed
	cbreak();              // Disables buffering
	// Start colors
	if(has_colors() == FALSE) {
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_RED);
	init_pair(2, COLOR_YELLOW, COLOR_BLUE);

	work_time = 0;

	while(1) {
		if(pausa) {
			attron(A_BOLD | COLOR_PAIR(1));
		} else {
			//attroff(A_BOLD | COLOR_PAIR(1)| COLOR_PAIR(2));
			attron(A_BOLD | COLOR_PAIR(2));
		}

		clear(); // Clear the screen of all previously-printed characters
		mvprintw(y, x, "o"); // Print our "ball" at the current xy position

		if(!pausa) {
			time(&current_time);
			elapsed_time = (double)difftime(current_time,start_time);
			horas = (work_time+elapsed_time) / 3600;
			minutos = ( (work_time+elapsed_time) - horas*3600 ) / 60;
			segundos = ((work_time+elapsed_time) - horas*3600 - minutos*60);
			mvprintw(2, 2, "Work time: %fs ; Elapsed %fs    %2dh%2dm%2ds  ",work_time,elapsed_time,horas,minutos,segundos);
			
		} else {
			horas = (work_time) / 3600;
			minutos = ( (work_time) - horas*3600 ) / 60;
			segundos = ((work_time) - (horas*3600) - (minutos*60));
			mvprintw(2, 2, "Work time: %fs ; Elapsed %fs    %2dh%2dm%2ds  ",work_time,elapsed_time,horas,minutos,segundos);
		}
		Print_Number(horas, 5,5);
		Print_DosPuntos(5,25);
		Print_Number(minutos, 5,31);
		Print_Number(segundos, 5,60);

		// TODO. Now the timer is set to 8h (28,800 seconds) --> Get this from a parameter
		if(!pausa) {
			tiempo_restante = 28800 - (work_time+elapsed_time); // TODO Make it different from 8h (28800 seconds)
		} else {
			tiempo_restante = 28800 - work_time;
		}
		if(tiempo_restante<0) {
			tiempo_restante=-tiempo_restante;
			mvprintw(15,  84," ########## ");
			mvprintw(15+1,84,"#          #");
			mvprintw(15+2,84,"#   ^  ^   #");
			mvprintw(15+3,84,"#          #");
			mvprintw(15+4,84,"#   \\__/   #");
			mvprintw(15+5,84," ########## ");
			mvprintw(15+6,84,"  ALL DONE! ");
		}
		horas = (tiempo_restante) / 3600;
		minutos = ( (tiempo_restante) - horas*3600 ) / 60;
		segundos = ((tiempo_restante) - (horas*3600) - (minutos*60));
		Print_Number(horas, 15,5);
		Print_DosPuntos(15,25);
		Print_Number(minutos, 15,31);
		Print_Number(segundos, 15,60);

		refresh();

		getmaxyx(stdscr, max_y, max_x);
		max_y++; // TODO: Remove: Bogus to avoid unused variable

		// Para la pelotita
		next_x = x + direction;
		if (next_x >= max_x || next_x < 0) {
			direction*= -1;
		} else {
			x+= direction;
		}
		// Recoge teclas
		if ((c = getch()) != ERR) {
			switch(c) {
				case KEY_F(1):
					quit=1;
					break;
				case ' ':
					if(pausa) {
						time(&start_time);
						pausa = 0;
					} else {
						pausa = 1;
						work_time += elapsed_time;
					}
					break;
			}
			if(quit) break;
		}
		usleep(DELAY_FOR_NCURSES); // Shorter delay between movements
	}

	endwin();			// End curses mode
	return 0;
}
