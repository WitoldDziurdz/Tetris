
#define _USE_MATH_DEFINES
#include<math.h>
#include <ctime>
#include <stdlib.h>
#include <cstdlib>
#include <cstdio>
#include<stdio.h>

extern "C" {
	//#ifdef BIT64
	//#include"./sdl64/include/SDL.h"
	//#include"./sdl64/include/SDL_main.h"
	//#else
#include"./sdl/include/SDL.h"
#include"./sdl/include/SDL_main.h"
	//#endif
}
#define PI 3.14159265
#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   480

// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt ?rodka obrazka sprite na ekranie
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};

void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	};
};
//wypelnnienie statycznej czensci planszy 
void wypelna_plansze(int**tab_static, int lewa_granica, int prawa_granica, int dolna_granica, int gorna_granica)
{
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 14; j++) {
			*(*(tab_static + i) + j) = 0;
		}
	}
	for (int i = 0; i < dolna_granica; i++)
	{
		*(*(tab_static + i) + lewa_granica) = 1;
		*(*(tab_static + i) + prawa_granica - 1) = 1;
	}
	for (int i = 0; i < prawa_granica; i++)
	{
		*(*(tab_static + dolna_granica - 1) + i) = 1;
		*(*(tab_static + gorna_granica) + i) = 1;
	}
}
// wspulrzedne klocka 2 i ich zminienie w zalerznosci ot konta
void fun_blekitny_klocek(int**tab, int a, int b)
{
	*(*(tab + a) + b) = 2;
	*(*(tab + a + 1) + b) = 2;
	*(*(tab + a) + b + 1) = 2;
	*(*(tab + a + 1) + b + 1) = 2;
}
// wspulrzedne klocka 3 i ich zminienie w zalerznosci ot konta
void fun_czerwony_klocek(int**tab, int a, int b, float kont)
{
	int cos1 = round(1 * cos(2 * (kont + PI / 2)));
	int sin2 = round(1 * sin(kont + PI / 2));
	int cos2 = round(1 * cos(kont + PI / 2));
	int sin3 = round(1 * sin(kont + PI));
	int cos3 = round(1 * cos(kont + PI));
	*(*(tab + a - 1) + b + cos1) = 3;
	*(*(tab + a - abs(sin2)) + b + abs(cos2)) = 3;
	*(*(tab + a) + b) = 3;
	*(*(tab + a + abs(sin3)) + b + abs(cos3)) = 3;
}
// wspulrzedne klocka 4 i ich zminienie w zalerznosci ot konta
void fun_pomoranczowy_klocek(int**tab, int a, int b, float kont)
{
	int sin1 = round(1 * sin(2 * kont - PI / 2));
	int sin2 = round(1 * sin(kont));
	int cos2 = round(1 * cos(kont));
	int sin3 = round(1 * sin(kont + PI / 2));
	int cos3 = round(1 * cos(kont + PI / 2));
	*(*(tab + a - abs(sin2)) + b - abs(cos2)) = 4;
	*(*(tab + a) + b) = 4;
	*(*(tab + a - abs(sin3)) + b + abs(cos3)) = 4;
	*(*(tab + a + sin1) + b + 1) = 4;
}
// wspulrzedne klocka 5 i ich zminienie w zalerznosci ot konta
void fun_zielony_klocek(int**tab, int a, int b, float kont)
{
	int sin1 = round(1 * (sin(PI / 4) / sin(PI / 4 + kont)));
	int cos1 = round(1 * (cos(PI / 4) / cos(PI / 4 + kont)));
	int sin2 = round(1 * sin(kont));
	int cos2 = round(1 * cos(kont));
	int sin3 = round(1 * sin(kont + PI));
	int cos3 = round(1 * cos(kont + PI));
	*(*(tab + a + sin1) + b + cos1) = 5;
	*(*(tab + a + sin2) + b + cos2) = 5;
	*(*(tab + a) + b) = 5;
	*(*(tab + a + sin3) + b + cos3) = 5;
}
// wspulrzedne klocka 6 i ich zminienie w zalerznosci ot konta
void fun_zulty_klocek(int**tab, int a, int b, float kont)
{
	int sin1 = round(1 * (sin(PI / 4) / sin(-PI / 4 + kont)));
	int cos1 = round(1 * (cos(PI / 4) / cos(-PI / 4 + kont)));
	int sin2 = round(1 * sin(kont));
	int cos2 = round(1 * cos(kont));
	int sin3 = round(1 * sin(kont + PI));
	int cos3 = round(1 * cos(kont + PI));
	*(*(tab + a + sin1) + b + cos1) = 6;
	*(*(tab + a + sin2) + b + cos2) = 6;
	*(*(tab + a) + b) = 6;
	*(*(tab + a + sin3) + b + cos3) = 6;
}
// wspulrzedne klocka 7 i ich zminienie w zalerznosci ot konta
void fun_fioletowy_klocek(int**tab, int a, int b, float kont)
{
	int sin1 = round(1 * sin(kont + PI));
	int cos1 = round(1 * cos(kont + PI));
	int sin2 = round(1 * sin(kont));
	int cos2 = round(1 * cos(kont));
	int sin3 = round(1 * sin(kont + PI / 2));
	int cos3 = round(1 * cos(kont + PI / 2));
	*(*(tab + a + sin1) + b + cos1) = 7;
	*(*(tab + a) + b) = 7;
	*(*(tab + a + sin2) + b + cos2) = 7;
	*(*(tab + a + sin3) + b + cos3) = 7;
}
// wspulrzedne klocka 8 i ich zminienie w zalerznosci ot konta
void fun_brazowy_klocek(int**tab, int a, int b, float kont)
{
	int sin1 = round(1 * sin(kont));
	int cos1 = round(1 * cos(kont));
	*(*(tab + a + 2 * abs(sin1)) + b + 2 * abs(cos1)) = 8;
	*(*(tab + a) + b) = 8;
	*(*(tab + a - abs(sin1)) + b - abs(cos1)) = 8;
	*(*(tab + a + abs(sin1)) + b + abs(cos1)) = 8;
}
// funkcjia wybiera klocek i od wolujesie do nastepnej ktura wypelnia tablice wybranym typem klocka
void zmienie_wspolrzendnych(int **tab_dinamic, int a, int b, int prawa_granica, int dolna_granica, int typ_klocka, float kont)
{
	for (int i = 0; i < dolna_granica; i++)
	{
		for (int j = 0; j < prawa_granica; j++)
		{
			*(*(tab_dinamic + i) + j) = 0;

			if (typ_klocka == 2)
				fun_blekitny_klocek(tab_dinamic, a, b);

			else if (typ_klocka == 3)
				fun_czerwony_klocek(tab_dinamic, a, b, kont);

			else if (typ_klocka == 4)
				fun_pomoranczowy_klocek(tab_dinamic, a, b, kont);

			else if (typ_klocka == 5)
				fun_zielony_klocek(tab_dinamic, a, b, kont);

			else if (typ_klocka == 6)
				fun_zulty_klocek(tab_dinamic, a, b, kont);

			else if (typ_klocka == 7)
				fun_fioletowy_klocek(tab_dinamic, a, b, kont);

			else if (typ_klocka == 8)
				fun_brazowy_klocek(tab_dinamic, a, b, kont);
		}
	}
}
// sprawdza sie kolizja po pszez sprawdzanie a potem zwracanie "poprawnych wspulrzendnych"
int sprawdzanie_bocznej_kolizji_(int **tab_static, int **tab_dinamic, int prawa_granica, int dolna_granica, int x2, int numer_strony, int roz_kloc)
{
	for (int i = 0; i < dolna_granica; i++)
	{
		for (int j = 0; j < prawa_granica; j++)
		{
			if (numer_strony == 1) {
				if (*(*(tab_static + i) + j + 1) != 0 && *(*(tab_dinamic + i) + j) != 0)
				{
					return x2;
				}
			}
			if (numer_strony == 2) {
				if ((*(*(tab_static + i) + j - 1) != 0) && (*(*(tab_dinamic + i) + j) != 0))
				{
					return x2;
				}
			}
		}
	}
	if (numer_strony == 1)
		return x2 + roz_kloc;
	if (numer_strony == 2)
		return x2 - roz_kloc;
	return 0;
}
//sprawdza sie czy zaistnialo wydarzenie dolnej kolizji a porem zapisuje sie ten klocek do stztycznej tablicy 
int dolna_kolizja(int **tab_dinamic, int **tab_static, int a, int b, int prawa_granica, int dolna_granica, int typ_klocka, float kont)
{
	for (int i = 0; i < dolna_granica; i++)
	{
		for (int j = 0; j < prawa_granica; j++)
		{
			if (*(*(tab_static + i + 1) + j) != 0 && *(*(tab_dinamic + i) + j) != 0)
			{
				if (typ_klocka == 2)
					fun_blekitny_klocek(tab_static, a, b);

				else if (typ_klocka == 3)
					fun_czerwony_klocek(tab_static, a, b, kont);

				else if (typ_klocka == 4)
					fun_pomoranczowy_klocek(tab_static, a, b, kont);

				else if (typ_klocka == 5)
					fun_zielony_klocek(tab_static, a, b, kont);

				else if (typ_klocka == 6)
					fun_zulty_klocek(tab_static, a, b, kont);

				else if (typ_klocka == 7)
					fun_fioletowy_klocek(tab_static, a, b, kont);

				else if (typ_klocka == 8)
					fun_brazowy_klocek(tab_static, a, b, kont);
				return  1;
			}
		}
	}
	return 0;
}
//rysowanie tablicy w zalerznosci ot typu klocka
void rysowanie(int **tab, SDL_Surface *screen, int prawa_granica, int dolna_granica, int roz_kloc)
{
	SDL_Surface*szary_klocek = SDL_LoadBMP("./szary.bmp");
	SDL_Surface*blekitny_klocek = SDL_LoadBMP("./blekitny.bmp");
	SDL_Surface*czerwony_klocek = SDL_LoadBMP("./czerwony.bmp");
	SDL_Surface *pomoranczowy_klocek = SDL_LoadBMP("./pomoranczowy.bmp");
	SDL_Surface*zielony_klocek = SDL_LoadBMP("./zielony.bmp");
	SDL_Surface *zulty_klocek = SDL_LoadBMP("./zulty.bmp");
	SDL_Surface *fioletowy_klocek = SDL_LoadBMP("./fioletowy.bmp");
	SDL_Surface *brazowy_klocek = SDL_LoadBMP("./brazowy.bmp");
	int x = 0;
	int y = 0;
	y = roz_kloc / 2;
	for (int i = 0; i < dolna_granica; i++)
	{
		x = roz_kloc / 2;
		for (int j = 0; j < prawa_granica; j++)
		{
			if (*(*(tab + i) + j) == 1)
				DrawSurface(screen, szary_klocek, x, y);
			else if (*(*(tab + i) + j) == 2)
				DrawSurface(screen, blekitny_klocek, x, y);
			else if (*(*(tab + i) + j) == 3)
				DrawSurface(screen, czerwony_klocek, x, y);
			else if (*(*(tab + i) + j) == 4)
				DrawSurface(screen, pomoranczowy_klocek, x, y);
			else if (*(*(tab + i) + j) == 5)
				DrawSurface(screen, zielony_klocek, x, y);
			else if (*(*(tab + i) + j) == 6)
				DrawSurface(screen, zulty_klocek, x, y);
			else if (*(*(tab + i) + j) == 7)
				DrawSurface(screen, fioletowy_klocek, x, y);
			else if (*(*(tab + i) + j) == 8)
				DrawSurface(screen, brazowy_klocek, x, y);
			x = x + roz_kloc;
		}
		y = y + roz_kloc;
	}
}
//wyzerowanie tablicy 
void zerowanie_tablicy(int**tab, const int prawa_granica, const int dolna_granica)
{
	for (int i = 0; i < dolna_granica; i++)
	{
		for (int j = 0; j < prawa_granica; j++) {
			*(*(tab + i) + j) = 0;
		}
	}
}
//sprawdzanie konca gry
int sprawdzanie_konca_gry(int**tab, const int prawa_granica, const int gorna_granica)
{
	for (int j = 0; j < prawa_granica; j++) {
		if (*(*(tab + gorna_granica) + j) != 1)
			return 1;
	}
	return 0;
}

// liczy usuniente linijki 
int fun_liczba_linijek(int **tab_static, int prawa_granica, int dolna_granica)
{
	int liczba_linijek = 0;
	int liczba = 0;
	int bufor = 0;
	int linija = 0;
	for (int i = 1; i <(dolna_granica - 1); i++)
	{
		liczba = 0;
		linija = 0;
		for (int j = 1; j <(prawa_granica - 1); j++)
		{
			if (*(*(tab_static + i) + j) != 0)
				liczba++;
		}
		if (liczba == (prawa_granica - 2))
		{
			for (int j = 1; j <(prawa_granica - 1); j++) {
				*(*(tab_static + i) + j) = 0;
				linija = i;
			}
			for (int i = linija; i > 1; i--)
			{
				for (int j = 1; j < (prawa_granica - 1); j++)
				{
					bufor = *(*(tab_static + i - 1) + j);
					*(*(tab_static + i) + j) = bufor;
				}
			}
			liczba_linijek++;
		}
	}
	return liczba_linijek;
}
//liczy punkty 
int fun_liczba_punktuw(int liczba_linijek, int pszyspieszenie, int liczba_linijek_psz)
{
	int liczba_punktuw = 0;

	if (liczba_linijek == 1)
	{
		liczba_punktuw = 100 * (pszyspieszenie + 1);
	}
	else if (liczba_linijek == 2)
	{
		liczba_punktuw = 200 * (pszyspieszenie + 1);
	}
	else if (liczba_linijek == 3)
	{
		liczba_punktuw = 400 * (pszyspieszenie + 1);
	}
	else if (liczba_linijek >= 4 && liczba_linijek_psz < 4)
	{
		liczba_punktuw = 800 * (pszyspieszenie + 1);
	}
	else if (liczba_linijek >= 4 && liczba_linijek_psz >= 4)
	{
		liczba_punktuw = 1200 * (pszyspieszenie + 1);
	}
	return liczba_punktuw;
}

//wzytywanie pliku
void wczytywanie_pliku(char **name, char **rekordy, int poz_rekordy, int l_txt_rekordy, const char *filename_rekordy)
{
	FILE *fin;
	int k = 0;
	int l = 0;
	fin = fopen(filename_rekordy, "r");

	for (int i = 0; i < 2 * poz_rekordy; i++)
	{
		if (i % 2 == 0)
		{
			fgets(*(name + l), l_txt_rekordy, fin);
			l++;
		}
		else
		{
			fgets(*(rekordy + k), l_txt_rekordy, fin);
			k++;
		}
	}
	fclose(fin);
}
//pozycja w liscie
int liczenie_pozycji(char **rekordy, int summa_punktuw, int  poz_rekordy)
{
	int pozycja = 0;
	for (int i = 0; i < poz_rekordy; i++)
	{
		if (summa_punktuw < atoi(*(rekordy + i)))
			pozycja++;
	}
	pozycja++;
	return pozycja;
}
// main
#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char **argv) {
	SDL_Event event;
	SDL_Surface *screen, *charset;
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;
	const char *filename_rekordy = "rekordy.txt";
	const int l_txt_rekordy = 20;
	const int poz_rekordy = 6;
	const int czas_etap = 10000;
	const double czas_opadania = 1000;
	const int lewa_granica = 0;
	const int prawa_granica = 14;
	const int gorna_granica = 0;
	const int dolna_granica = 24;
	const int Y_static = 25;
	const int X_static = 32;
	const int Y_dinamic = 24;
	const int X_dinamic = 14;
	const int Y_klocka_poz = 30;
	const int X_klocka_poz = 130;
	const int X_text = 300;
	const int Y_text = 30;
	const int nl_text = 20;
	const int roz_kloc = 20;
	const int max_pszyspieszenie = 10;
	float kont = 0;
	double delta1, delta2;
	int t1, t2, t3, t4, x2, y2, quit, rc;
	int  a = 0;
	int  b = 0;
	int numer_strony = 0;
	int pozycja = 0;
	int ret = 0;
	int pause = 0;
	int nowa_gra = 0;
	int koniec_gry = 0;
	int moment_prsys = 0;
	int pszyspieszenie = 1;
	int summa_punktuw = 0;
	int liczba_punktuw = 0;
	int indykator = 0;
	int typ_klocka = 2;
	int liczba_linijek = 0;
	int liczba_linijek_psz = 0;
	char text[128];

	int **tab_static = new int*[Y_static];    // tablica w ktura jest zapizywana statycna czesc planszy
	for (int i = 0; i < Y_static; i++) {
		tab_static[i] = new int[X_static];
	}

	int ** tab_dinamic = new int*[Y_dinamic];    // tablica w ktura jest zapizywana dynamiczna czesc planszy
	for (int i = 0; i < Y_dinamic; i++) {
		tab_dinamic[i] = new int[X_dinamic];
	}

	char **name = new char*[poz_rekordy];    // tablica w ktura jest zapizywana nazwy urzytkownikow
	for (int i = 0; i < poz_rekordy; i++) {
		name[i] = new char[l_txt_rekordy];
	}

	char **rekordy = new char*[poz_rekordy];     // tablica w ktura jest zapizywane rekordy 
	for (int i = 0; i < poz_rekordy; i++) {
		rekordy[i] = new char[l_txt_rekordy];
	}

	zerowanie_tablicy(tab_dinamic, prawa_granica, dolna_granica); //zeruje tablice 
	wypelna_plansze(tab_static, lewa_granica, prawa_granica, dolna_granica, gorna_granica);  //zostaja wypolnione statyczne czesci gry(granicy)
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
	};
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_SetWindowTitle(window, "Szablon do zdania drugiego 2014");
	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	// wy??czenie widoczno?ci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);
	charset = SDL_LoadBMP("./cs8x8.bmp");
	if (charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	SDL_SetColorKey(charset, true, 0x000000);

	int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);

	srand(time(NULL));
	typ_klocka = 2 + rand() % 7;
	quit = 0;
	t1 = 0;
	t3 = 0;
	t4 = 0;
	x2 = X_klocka_poz;
	y2 = Y_klocka_poz;
	while (!quit) {
		SDL_FillRect(screen, NULL, czarny);
		if (nowa_gra)   // ten "if" zlorzy do sformowania paczantku gry (wszyskie ustawienia = paczatku gry )
		{
			liczba_linijek_psz = 0;
			pszyspieszenie = 1;
			liczba_punktuw = 0;
			summa_punktuw = 0;
			quit = 0;
			nowa_gra = 0;
			t1 = 0;
			t3 = 0;
			t4 = 0;
			x2 = X_klocka_poz;
			y2 = Y_klocka_poz;
			zerowanie_tablicy(tab_dinamic, prawa_granica, dolna_granica);
			wypelna_plansze(tab_static, lewa_granica, prawa_granica, dolna_granica, gorna_granica);
		}

		if (ret) // mechanizm ustawiajacy nowy klocek na planszy
		{
			typ_klocka = 2 + rand() % 7;  // randomny typ klocka
			x2 = X_klocka_poz;    // wszpulrzedne nowego klocka
			y2 = Y_klocka_poz;
			ret = 0;
		}

		if (!pause)     // ten mechanizm slurzy do nie pszyspieszenie po wlaczeniu pauzy 
			t2 = SDL_GetTicks();
		else
			t2 = t2;

		while (pause && !quit) // wlacza i wylacza pauze
		{
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
					else if (event.key.keysym.sym == SDLK_p) pause = 0;
					break;
				case SDL_QUIT:
					quit = 1;
					break;
				};
			};
		}
		delta1 = t2 - t1; //ruznice czasu slurzance do zmienienia etapu gry  
		delta2 = t2 - t3;
		if (czas_opadania / pszyspieszenie - delta1 < 0.0001) //pszesuwanie klocka w dol
		{
			y2 += 20;
			t1 = t2;
		}
		if (indykator) // mechanizm  ktury po nacisnienciu pszyspieszenia zeruje licznik pszyspieszenia zalerzny ot czasu 
		{
			indykator = 0;
			delta2 = 0;
		}
		if (delta2 > czas_etap) // zmienienie etapu gry zalerzne ot czasu gry z uwzglednieniem max pszyspieszenia za granicy kturego nie wykracza pszyspieszenie
		{
			pszyspieszenie++;
			if (pszyspieszenie > max_pszyspieszenie)
				pszyspieszenie = max_pszyspieszenie;
			t3 = t2;
		}


		a = (y2 - 10) / 20; // zmienie polorzenia klocka zalerzne ot uzyskanych wszpulrzednych z funkcji powyrzej 
		b = (x2 - 10) / 20;
		zmienie_wspolrzendnych(tab_dinamic, a, b, prawa_granica, dolna_granica, typ_klocka, kont); //funkcja zmienijace te wspulrzedne i wykonajoca rotacje klocka
		while (moment_prsys) // petla slurzanca do natychmiastowego spadania klocka, wykonujesie do puki klocek nie spadnie
		{
			y2 += 20;
			a = (y2 - 10) / 20;
			zmienie_wspolrzendnych(tab_dinamic, a, b, prawa_granica, dolna_granica, typ_klocka, kont);
			for (int i = 0; i < 24; i++)
			{
				for (int j = 0; j < 14; j++)
				{
					if (*(*(tab_static + i + 1) + j) != 0 && *(*(tab_dinamic + i) + j) != 0)
						moment_prsys = 0;
				}
			}
		}
		ret = dolna_kolizja(tab_dinamic, tab_static, a, b, prawa_granica, dolna_granica, typ_klocka, kont); //funkcja obslugue i sprawdza dola kolizje a takrze zwraca czy bylo takie zdarzenie jak kolizja dolna
		liczba_linijek = fun_liczba_linijek(tab_static, prawa_granica, dolna_granica);  //obsluguje zdarzenie usuniencia linijek i zwraca liczbe usunientych linijek
		if (liczba_linijek)
		{
			liczba_punktuw = fun_liczba_punktuw(liczba_linijek, pszyspieszenie, liczba_linijek_psz); // funkcja liczy punkty w zalerznosci ot etapu gry, licby usunientych linijek i licby usunientych linijek ipopszednio
			summa_punktuw = summa_punktuw + liczba_punktuw; //sumuje punkty
			liczba_linijek_psz = liczba_linijek; // zapamientanie zeszlej liczby usunientych linijek 
		}
		wczytywanie_pliku(name, rekordy, poz_rekordy, l_txt_rekordy, filename_rekordy);//funkcja wzytuje plik
		pozycja = liczenie_pozycji(rekordy, summa_punktuw, poz_rekordy); //funkcja zwraca pozycje gracza na liscie rekorduw
		koniec_gry = sprawdzanie_konca_gry(tab_static, prawa_granica, gorna_granica); // sprawdza koniec gry i zwraca prawde albo falsz 
		sprintf(text, "%s %d", "Pozycja uzyskana w liscie rekorduw:", pozycja);   // drukowanie tekstu 
		DrawString(screen, X_text, Y_text + 4 * nl_text, text, charset);
		sprintf(text, "%s %d", "Punkty uzyskane ostatnim razem:", liczba_punktuw);
		DrawString(screen, X_text, Y_text, text, charset);
		sprintf(text, "%s %d", "Suma uzyskanych punktow:", summa_punktuw);
		DrawString(screen, X_text, Y_text + nl_text, text, charset);
		rysowanie(tab_dinamic, screen, prawa_granica, dolna_granica, roz_kloc); // rysowanie dwuch tablic jedna dynamicna(spadajacy klocek) druga statycna(granicy i klocki jurz spadniete)
		rysowanie(tab_static, screen, prawa_granica, dolna_granica, roz_kloc);
		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);// rendorowanie 
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);// rendorowanie 
		SDL_RenderPresent(renderer);// rendorowanie 

		if (koniec_gry)// srawdza czy nastapil koniec gry 
		{
			while (!quit && !nowa_gra) {
				if (pozycja <= poz_rekordy)
				{
					for (int i = 0; i < poz_rekordy; i++) // rysuje kiste rekorduw
					{
						sprintf(text, "%s", *(name + i));
						DrawString(screen, X_text, Y_text + 5 * nl_text + i*nl_text, text, charset);
						sprintf(text, "%s", *(rekordy + i));
						DrawString(screen, X_text + 100, Y_text + 5 * nl_text + i * nl_text, text, charset);
					}
				}
				sprintf(text, "%s", "Koniec gry morzesz:"); // tekst wyswietlany w pod koniec gry
				DrawString(screen, X_text, Y_text + 2 * nl_text, text, charset);
				sprintf(text, "Esc - wyjscie, n - nowa gra");
				DrawString(screen, X_text, Y_text + 3 * nl_text, text, charset);
				SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
				SDL_RenderCopy(renderer, scrtex, NULL, NULL);
				SDL_RenderPresent(renderer);
				while (SDL_PollEvent(&event)) {  //zdarzenia dzialajece pod koniec gry 
					switch (event.type) {
					case SDL_KEYDOWN:
						if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
						else if (event.key.keysym.sym == SDLK_n) nowa_gra = 1;
						break;
					case SDL_QUIT:
						quit = 1;
						break;
					};
				};
			};
			koniec_gry = 0;
		}
		while (SDL_PollEvent(&event)) { // lista zdarzen i pszyciski im odpawiadajece
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1; // wyjscie
				else if (event.key.keysym.sym == SDLK_DOWN) moment_prsys = 1; // pszyspieszenie
				else if (event.key.keysym.sym == SDLK_p) pause = 1; // pauza
				else if (event.key.keysym.sym == SDLK_n) nowa_gra = 1;// nowa gra
				else if (event.key.keysym.sym == SDLK_f) // pszyspieszenie(zwiekszenie etapu gry)
				{
					pszyspieszenie++;
					if (pszyspieszenie > max_pszyspieszenie) //sprawdza czy jest max etap gry i nie pozwala zwieksenia etapu 
						pszyspieszenie = max_pszyspieszenie;
					indykator = 1; //slorzy dla anulowania czasu 
				}
				else if (event.key.keysym.sym == SDLK_RIGHT) {
					numer_strony = 1;
					x2 = sprawdzanie_bocznej_kolizji_(tab_static, tab_dinamic, prawa_granica, dolna_granica, x2, numer_strony, roz_kloc);//funkcja sprawdza boczna kolizje z prawej strony
				}
				else if (event.key.keysym.sym == SDLK_LEFT) {
					numer_strony = 2;
					x2 = sprawdzanie_bocznej_kolizji_(tab_static, tab_dinamic, prawa_granica, dolna_granica, x2, numer_strony, roz_kloc);//funkcja sprawdza boczna kolizje z lefej strony
				}
				else if (event.key.keysym.sym == SDLK_UP)  kont = kont + PI / 2; //obracanie klocka po przez zwiekszenia konta
				else if (event.key.keysym.sym == SDLK_SPACE)  kont = kont + PI / 2;//obracanie klocka po przez zwiekszenia konta
				break;
			case SDL_QUIT:
				quit = 1;
				break;
			};
		};

	};
	// zwolnienie powierzchni
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
};
