/*
     Prosty studencki program graficzny 
	 kodowany w jezyku C z uzyciem OpenGL 
*/

#include "szescian.h"


LONG WINAPI WndProc( HWND, UINT, WPARAM, LPARAM );
HGLRC SetUpOpenGL( HWND hWnd );

// Wartosci poczatkowe
#define	DEFAULT_Z_DIST		500
#define DEFAULT_PIVOT_VERT_ANGLE	0
#define DEFAULT_PIVOT_HORIZ_ANGLE	0
#define DEFAULT_PIVOT_X				0
#define DEFAULT_PIVOT_Y				0


float z_dist=DEFAULT_Z_DIST;						// INSERT, PAGE UP
float pivot_vert_angle=DEFAULT_PIVOT_VERT_ANGLE;	// UP, DOWN
float pivot_horiz_angle=DEFAULT_PIVOT_HORIZ_ANGLE;	// LEFT, RIGHT
float pivot_x=DEFAULT_PIVOT_X;						// DELETE, PAGE DOWN
float pivot_y=DEFAULT_PIVOT_Y;						// HOME, END


// ************ Deklaracje funkcji ************************

void DrawOpenGLScene( void );  // glowna funkcja rysujaca

//   Skladowe funkcje obiektu graficznego

void szescian();
void statek(void);
void podstawa1(void);
// ..............................

//******** Fukcje skladowe ********************************
void podstawa1(void)
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	{
	GLfloat sa[3]={-100.0f,100.0f,-20.0f};
	GLfloat sb[3]={100.0f,100.0f,-20.0f};
	GLfloat sc[3]={100.0f,-100.0f,-20.0f};
	GLfloat sd[3]={-100.0f,-100.0f,-20.0f};
	GLfloat se[3]={-100.0f,100.0f,-10.0f};
	GLfloat sf[3]={100.0f,100.0f,-10.0f};
	GLfloat sg[3]={100.0f,-100.0f,-10.0f};
	GLfloat sh[3]={-100.0f,-100.0f,-10.0f};

	//glColor3d(0.6, 0.4, 0.7);
	glBegin(GL_POLYGON);
		glVertex3fv(sa);
		glVertex3fv(sb);
		glVertex3fv(sc);
		glVertex3fv(sd);
	glEnd();

		//glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex3fv(sb);
		glVertex3fv(sf);
		glVertex3fv(sg);
		glVertex3fv(sc);
	glEnd();

	//glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex3fv(sf);
		glVertex3fv(se);
		glVertex3fv(sh);
		glVertex3fv(sg);
	glEnd();

		//glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex3fv(se);
		glVertex3fv(sa);
		glVertex3fv(sd);
		glVertex3fv(sh);
	glEnd();

		//glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex3fv(sd);
		glVertex3fv(sc);
		glVertex3fv(sg);
		glVertex3fv(sh);
	glEnd();

	//glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex3fv(sa);
		glVertex3fv(sb);
		glVertex3fv(sf);
		glVertex3fv(se);
	glEnd();
	}

}

void podstawa(double r, double h,double p)
{
	double x, y, PI = 3.14, alpha;

	glBegin(GL_TRIANGLE_FAN);
	glColor3d(0.6, 0.1, 0.3);
	glVertex3d(0, 0, -30);

	for (alpha = 0;alpha <= 2 * PI; alpha += PI / p)
	{
		x = r * sin(alpha);
		y = r * cos(alpha);
		glVertex3d(x, y, -30);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glColor3d(0.7, 0.7, 0.8);
	for (alpha = 0;alpha <= 2 * PI; alpha += PI / p)
	{
		x = r * sin(alpha);
		y = r * cos(alpha);
		glVertex3d(x, y, -30);
		glVertex3d(x, y, h);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3d(0.2, 0.4, 0.1);
	glVertex3d(0, 0, h);

	for (alpha = 0;alpha >= -2 * PI; alpha -= PI / p)
	{
		x = r * sin(alpha);
		y = r * cos(alpha);
		glVertex3d(x, y, h);
	}
	glEnd();
}
void szescian()
{	
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	{
	GLfloat sa[3]={-63.0f,18.0f,10.0f};
	GLfloat sb[3]={65.0f,-28.0f,10.0f};
	GLfloat sc[3]={68.0f,-20.0f,10.0f};
	GLfloat sd[3]={-60.0f,26.0f,10.0f};
	GLfloat se[3]={-63.0f,18.0f,30.0f};
	GLfloat sf[3]={65.0f,-28.0f,30.0f};
	GLfloat sg[3]={68.0f,-20.0f,30.0f};
	GLfloat sh[3]={-60.0f,26.0f,30.0f};


		// Parametry wierzcholkow
	
	// Sciany skladowe
	//glColor3f(1.0f, 0.0f, 0.0f);


	
	glColor3d(0.6, 0.4, 0.7);
	glBegin(GL_POLYGON);
		glVertex3fv(sa);
		glVertex3fv(sb);
		glVertex3fv(sc);
		glVertex3fv(sd);
	glEnd();

		//glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex3fv(sb);
		glVertex3fv(sf);
		glVertex3fv(sg);
		glVertex3fv(sc);
	glEnd();

	//glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex3fv(sf);
		glVertex3fv(se);
		glVertex3fv(sh);
		glVertex3fv(sg);
	glEnd();

		//glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex3fv(se);
		glVertex3fv(sa);
		glVertex3fv(sd);
		glVertex3fv(sh);
	glEnd();

		//glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex3fv(sd);
		glVertex3fv(sc);
		glVertex3fv(sg);
		glVertex3fv(sh);
	glEnd();

	//glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex3fv(sa);
		glVertex3fv(sb);
		glVertex3fv(sf);
		glVertex3fv(se);
	glEnd();
	}
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	{
	
	GLfloat sa[3]={-63.0f,-18.0f,10.0f};
	GLfloat sb[3]={65.0f,28.0f,10.0f};
	GLfloat sc[3]={68.0f,20.0f,10.0f};
	GLfloat sd[3]={-60.0f,-26.0f,10.0f};
	GLfloat se[3]={-63.0f,-18.0f,30.0f};
	GLfloat sf[3]={65.0f,28.0f,30.0f};
	GLfloat sg[3]={68.0f,20.0f,30.0f};
	GLfloat sh[3]={-60.0f,-26.0f,30.0f};

	
	glColor3d(0.6, 0.4, 0.7);
	glBegin(GL_POLYGON);
		glVertex3fv(sa);
		glVertex3fv(sb);
		glVertex3fv(sc);
		glVertex3fv(sd);
	glEnd();

		//glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex3fv(sb);
		glVertex3fv(sf);
		glVertex3fv(sg);
		glVertex3fv(sc);
	glEnd();

	//glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex3fv(sf);
		glVertex3fv(se);
		glVertex3fv(sh);
		glVertex3fv(sg);
	glEnd();

		//glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex3fv(se);
		glVertex3fv(sa);
		glVertex3fv(sd);
		glVertex3fv(sh);
	glEnd();

		//glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex3fv(sd);
		glVertex3fv(sc);
		glVertex3fv(sg);
		glVertex3fv(sh);
	glEnd();

	//glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex3fv(sa);
		glVertex3fv(sb);
		glVertex3fv(sf);
		glVertex3fv(se);
	glEnd();
	
	}
}

void statek(void)
{
	double x, y, PI = 3.14, alpha,x1,y1;
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUAD_STRIP); //korpus
	glColor3d(0.6, 0.4, 0.7);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 20*sin(alpha);
		y = 20*cos(alpha);
		glVertex3d(x, y, 0);
		glVertex3d(x, y, 100);
	}
	glColor3d(1, 0, 0);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 20 * sin(alpha);
		y = 20 * cos(alpha);
		glVertex3d(x, y, 100);
		glVertex3d(x/2, y/2, 150);
	}
	x1 = x;
	y1 = y;
	glEnd();
	glBegin(GL_QUAD_STRIP);

	for (alpha = 0;alpha >= -2 * PI;alpha -= PI / 6)
	{
		x = 10 * sin(alpha);
		y = 10 * cos(alpha);
		glVertex3d(x, y, 145);
		glVertex3d(0, 0, 170);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);//lewy dolny silnik
	glColor3d(0.6, 0.4, 0.7);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10*sin(alpha) - 20;
		y = 10*cos(alpha) - 20;
		glVertex3d(x, y, 0);
		glVertex3d(x, y, 40);
	}
	glColor3d(0.4, 0.6, 0.2);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10 * sin(alpha) - 20;
		y = 10 * cos(alpha) - 20;
		glVertex3d(x, y, 40);
		glVertex3d(-20, -20, 50);
	}
	
	glEnd();
	glBegin(GL_QUAD_STRIP);//lewy górny silnik
	glColor3d(0.6, 0.4, 0.7);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10 * sin(alpha) - 20;
		y = 10 * cos(alpha) + 20;
		glVertex3d(x, y, 0);
		glVertex3d(x, y, 40);
	}
	glColor3d(0.4, 0.6, 0.2);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10 * sin(alpha) - 20;
		y = 10 * cos(alpha) + 20;
		glVertex3d(x, y, 40);
		glVertex3d(-20, 20, 50);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);//prawy dolny silnik
	glColor3d(0.6, 0.4, 0.7);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10 * sin(alpha) + 20;
		y = 10 * cos(alpha) - 20;
		glVertex3d(x, y, 0);
		glVertex3d(x, y, 40);
	}
	glColor3d(0.4, 0.6, 0.2);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10 * sin(alpha) + 20;
		y = 10 * cos(alpha) - 20;
		glVertex3d(x, y, 40);
		glVertex3d(20, -20, 50);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);//prawy górny silnik
	glColor3d(0.6, 0.4, 0.7);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10 * sin(alpha) + 20;
		y = 10 * cos(alpha) + 20;
		glVertex3d(x, y, 0);
		glVertex3d(x, y, 40);
	}
	glColor3d(0.4, 0.6, 0.2);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 10 * sin(alpha) + 20;
		y = 10 * cos(alpha) + 20;
		glVertex3d(x, y, 40);
		glVertex3d(20, 20, 50);
	}
	glEnd();
	//////////////////////skrzyd³a
	glBegin(GL_QUAD_STRIP);
	glColor3d(0.6, 0.4, 0.7);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 5*sin(alpha) - 60;
		y = 5*cos(alpha) + 30;
		glVertex3d(x, y, 10);
		glVertex3d(x, y, 30);
	}
	glColor3d(0.4, 0.6, 0.2);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 5 * sin(alpha) - 60;
		y = 5 * cos(alpha) + 30;
		glVertex3d(x, y, 30);
		glVertex3d(-60, 30, 35);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glColor3d(0.6, 0.4, 0.7);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 5*sin(alpha) - 60;
		y = 5*cos(alpha) - 30;
		glVertex3d(x, y, 10);
		glVertex3d(x, y, 30);
	}
	glColor3d(0.4, 0.6, 0.2);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 5 * sin(alpha) - 60;
		y = 5 * cos(alpha) - 30;
		glVertex3d(x, y, 30);
		glVertex3d(-60, -30, 35);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glColor3d(0.6, 0.4, 0.7);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 5*sin(alpha) + 60;
		y = 5*cos(alpha) - 30;
		glVertex3d(x, y, 10);
		glVertex3d(x, y, 30);
	}
	glColor3d(0.4, 0.6, 0.2);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 5 * sin(alpha) + 60;
		y = 5 * cos(alpha) - 30;
		glVertex3d(x, y, 30);
		glVertex3d(60, -30, 35);
	}
	glEnd();


	glBegin(GL_QUAD_STRIP);
	glColor3d(0.6, 0.4, 0.7);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 5*sin(alpha) + 60;
		y = 5*cos(alpha) + 30;
		glVertex3d(x, y, 10);
		glVertex3d(x, y, 30);
	}
	glColor3d(0.4, 0.6, 0.2);
	for (alpha = 0;alpha <= 2 * PI;alpha += PI / 6)
	{
		x = 5 * sin(alpha) + 60;
		y = 5 * cos(alpha) + 30;
		glVertex3d(x, y, 30);
		glVertex3d(60, 30, 35);
	}
	glEnd(); 
	szescian();
}



//******************************************************** 
//  Glowna funkcja WINDOWS
//******************************************************** 

int WINAPI WinMain (HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
                    LPSTR lpszCmdLine,
					int nCmdShow)
{
    static char szAppName[] = "OpenGL";                    
    static char szTitle[]=    "SZESCIAN"; // Nazwa okna
    WNDCLASS wc;   // zmienna klasy okna
    MSG      msg;  // zmienna komunikatu 
    HWND     hWnd; // uchwyt okna

    // wypelnianie klasy okna 

    wc.style         =
        CS_HREDRAW | CS_VREDRAW;// styl okna
    wc.lpfnWndProc   = 
        (WNDPROC)WndProc;       // procedura okna
    wc.cbClsExtra    = 0;       // dodatkowe dane
    wc.cbWndExtra    = 0;       
    wc.hInstance     =
        hInstance;              // instancja 
    wc.hIcon         = NULL;    // nazwa ikony 
    wc.hCursor       =
        LoadCursor(NULL, IDC_ARROW);// kursor
    wc.hbrBackground = 
        (HBRUSH)(COLOR_WINDOW+1);// domyslny kolor okna
    wc.lpszMenuName  = NULL;     
    wc.lpszClassName =
        szAppName;               // nazwa klasy

    // Rejestracja klasy okna

    RegisterClass( &wc );
  
    // Konstrukcja glownego okna 

    hWnd = CreateWindow(
                szAppName, // app name
                szTitle,   // Text for window title bar
                WS_OVERLAPPEDWINDOW// Window style 
                  // NEED THESE for OpenGL calls to work!
                 | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
                NULL,     // no parent window
                NULL,     // Use the window class menu.
                hInstance,// This instance owns this window
                NULL      // We don't use any extra data
        );

    // Jezeli okno nie zostanie utworzone, zwrot 0
    if ( !hWnd )
        {
        return( 0 );
        }

    
	ShowWindow( hWnd, nCmdShow );// Wyswietlanie okna
    UpdateWindow( hWnd );        // Aktualizacja okna

    // Uruchiomienie petli komunikatow
    while (GetMessage(&msg, NULL, 0, 0)) 
	{
        TranslateMessage( &msg ); // Przetwarzanie wiadomosci
        DispatchMessage( &msg );  // Zwolnienie wiadomosci
    }

    return( msg.wParam ); 
}


//******************************************************** 
//    Procedura okna
//******************************************************** 
 
LONG WINAPI WndProc(HWND hWnd,
					UINT msg,
                    WPARAM wParam,
					LPARAM lParam)
{
    HDC hDC;

    static HGLRC hRC; // Note this is STATIC!
    
	PAINTSTRUCT ps;

    GLdouble gldAspect;

    GLsizei glnWidth, glnHeight;

	float change;


    // Petla komunikatow 
	
    switch (msg)
      {
       case WM_CREATE:
           hRC = SetUpOpenGL( hWnd );	// Inicjalizacja OpenGL
           return 0;
    
       case WM_SIZE:
            hDC = GetDC (hWnd);			// Kontekst urzadzenia
            wglMakeCurrent (hDC, hRC);
        
            // Usawienie rozmiarow okna graficznego
            
			glnWidth = (GLsizei) LOWORD (lParam);
            glnHeight = (GLsizei) HIWORD (lParam);
            
			// Aspekt DC
			gldAspect = (GLdouble)glnWidth/(GLdouble)glnHeight;
       
            glMatrixMode( GL_PROJECTION );// Ustawienie macierzy projekcji
            
			glLoadIdentity();
            
			// Rodzaj transformacji ekranowej
            gluPerspective(
                30.0,      // kat 
                gldAspect, // aspekt
                1.0,       // polozenie plaszczyzny blizszej
                1000.0 );  // polozenie plaszczyzny dalszej

            glViewport( 0, 0, glnWidth, glnHeight );
            
			// czyszczenie
			glClearColor(0.5f,0.5f,0.5f,1.0f);
			
			glEnable(GL_COLOR_MATERIAL);
			wglMakeCurrent( NULL, NULL );
            ReleaseDC( hWnd, hDC );
            return 0;

        case WM_PAINT:
            // rysowanie sceny

            hDC = BeginPaint( hWnd, &ps );
            wglMakeCurrent( hDC, hRC );
            
            DrawOpenGLScene();
			
			SwapBuffers(hDC);
            
            wglMakeCurrent( NULL, NULL );

            EndPaint( hWnd, &ps );
            return 0;       
            
        case WM_DESTROY:
            // zamykanie 
            wglDeleteContext( hRC );
            PostQuitMessage( 0 );
            return 0;

		case WM_KEYDOWN: //************ OBSLUGA KLAWISZY ***********************
			if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
				change=1.0f;
			else
				change=0.1f;

			switch ((int)wParam)
			{
				// obrot w pionie
				case VK_UP:
					pivot_vert_angle+=5;
					if (pivot_vert_angle>=360)
						pivot_vert_angle-=360;
					InvalidateRect(hWnd, NULL, FALSE);
					break;
				case VK_DOWN:
					pivot_vert_angle-=5;
					if (pivot_vert_angle<0)
						pivot_vert_angle+=360;
					InvalidateRect(hWnd, NULL, FALSE);
					break;

				// obrot w poziomie
				case VK_RIGHT:
					pivot_horiz_angle+=5;
					if (pivot_horiz_angle>=360)
						pivot_horiz_angle-=360;
					InvalidateRect(hWnd, NULL, FALSE);
					break;
				case VK_LEFT:
					pivot_horiz_angle-=5;
					if (pivot_horiz_angle<0)
						pivot_horiz_angle+=360;
					InvalidateRect(hWnd, NULL, FALSE);
					break;

				// przesuniecia w poziomie
				case VK_NEXT:
					if ((pivot_x+change)<400)
						pivot_x+=change;
					InvalidateRect(hWnd, NULL, FALSE);
					break;
				case VK_DELETE:
					if ((pivot_x-change)>-400)
						pivot_x-=change;
					InvalidateRect(hWnd, NULL, FALSE);
					break;

				// przesuniecia w pionie
				case VK_HOME:
					if ((pivot_y+change)<400)
						pivot_y+=change;
					InvalidateRect(hWnd, NULL, FALSE);
					break;
				case VK_END:
					if ((pivot_y-change)>-400)
						pivot_y-=change;
					InvalidateRect(hWnd, NULL, FALSE);
					break;

				// odleglosc
				case VK_INSERT:
					if ((z_dist+change)<600)
						z_dist+=change;
					InvalidateRect(hWnd, NULL, FALSE);
					break;
				case VK_PRIOR:
					if ((z_dist-change)>1)
						z_dist-=change;
					InvalidateRect(hWnd, NULL, FALSE);
					break;

				// wyjscie z programu
				case VK_ESCAPE:
					PostMessage(hWnd, WM_CLOSE, 0, 0);
					return 0;
			}
        }

    
    return DefWindowProc( hWnd, msg, wParam, lParam );
}



//*******************************************************
//  Uruchomienie OpenGL w srodowisku Windows wymaga 
//  wlaczenie trybu pikselowego oraz ustawienia 
//  kontekstu renderowania
//*******************************************************

HGLRC SetUpOpenGL( HWND hWnd )
{
    static PIXELFORMATDESCRIPTOR pfd =
	{
        sizeof (PIXELFORMATDESCRIPTOR), // rozmiar struktury 
        1,                              // numer wersji
        PFD_DRAW_TO_WINDOW |            // flaga rysowania w oknie,
            PFD_SUPPORT_OPENGL |        // uzycie OpenGL
		    PFD_DOUBLEBUFFER,	        // uzycie podwojnego buforowania
        PFD_TYPE_RGBA,                  // model kolorow - RGBA 
        24,                             // kolor 24-bitowy
        0, 0, 0,                        
        0, 0, 0,                        // trezerwa
        0, 0,                           // brak bufora alpha 
        0, 0, 0, 0, 0,                  // brak bufora akumulacji
        32,                             // bufor glebokosci 32-bitowy
        0,                              // brak bufora szablonu
        0,                              // brak bufora pomocniczego
        PFD_MAIN_PLANE,					// warstwa
        0,                              // rezerwa - 0 
        0,                              // maska
        0,                              // maska widoczna
        0                               // maska bledow
    };

	// zmienne
    int nMyPixelFormatID;

    HDC hDC;
    
	HGLRC hRC;

    hDC = GetDC( hWnd );
    
	// Inicjalizacja trybu pikselowego 

	nMyPixelFormatID = ChoosePixelFormat( hDC, &pfd );
    SetPixelFormat( hDC, nMyPixelFormatID, &pfd );
	
	// Inicjalizacja kontekstu renderowania
    
	hRC = wglCreateContext( hDC );
    ReleaseDC( hWnd, hDC );

    return hRC;
}



//******************************************************** 
//  Glowna funkcja rysujaca.
//******************************************************** 

void DrawOpenGLScene( )
{
	GLfloat position[4]={10.0f, 10.0, 100.0f, 0.0f};
    
	// flagi czynnosci pomocniczych

    glEnable( GL_DEPTH_TEST );
    
	// czyszczenie buforow
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	//glEnable(GL_CULL_FACE);
	glEnable(GL_COLOR_MATERIAL);

	auxInitDisplayMode(AUX_SINGLE|AUX_RGBA);
	
	// wlaczenie oswietlenia
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

    
    // transformacja obserwacji
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // umiejscowienie kamery w odleglym miejscu
  	glTranslatef( pivot_x, pivot_y, -z_dist );
	glRotatef(pivot_vert_angle, 1, 0, 0);
	glRotatef(pivot_horiz_angle, 0, 1, 0);
	
	glPushMatrix();
		//szescian !!!!!!!!!!!!!!!!!!!!!!!!!!
		//szescian();
		//statek();
		//podstawa(150,-10,20);
		podstawa1();
	glPopMatrix();

    glFlush ();
}
