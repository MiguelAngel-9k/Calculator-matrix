#include<Windows.h>
#include<iostream>
#include<sstream>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

using namespace std;
LRESULT CALLBACK func(HWND, UINT, WPARAM, LPARAM);
void addMenu(HWND);
void Controls(HWND);
void combos();
void ingresoDatos();
void aritmetica();
void liberar();
void resultados(HWND);
void cuaternio();
void compositar();
void MxV();

struct matrices {

	int matriz[10][10];
	int filas;
	int columnas;
	matrices *siguiente;
	matrices *anterior;

}*origen,*aux,*indicador;



struct mResultados {

	int matrizR[10][10];
	int filasR;
	int columnasR;
	mResultados*siguienteR;
	mResultados*anteriorR;

}*origenR,*auxR;



struct mCompuesta {

	double mComp[4][4]= { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	double mTemporal[4][4]= { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	double mTransformacion[4][4] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	double valorTransformacion;
	int filas=4;
	int columnas=4;
	mCompuesta*sigueinteC;
	mCompuesta*anteriorC;

}*origenC,*auxC;


HINSTANCE hInst;
#define ID_BOTON7 140
#define ID_BOTON4 145
#define ID_BOTON1 150
#define ID_BOTON8 155
#define ID_BOTON9 160
#define ID_BOTON5 165
#define ID_BOTON6 170
#define ID_BOTON2 175
#define ID_BOTON3 180
#define ID_BOTONNEGATE 185
#define ID_BOTON0 190
#define ID_BOTONC 195
#define ID_DISPLAY 200
#define FILE_MENU 135
#define ID_ENTER 205
#define ID_FILA1 210
#define ID_COLUMNAS1 215
#define ID_ARITMETICA 220
#define ID_LISTBOX 225
#define ID_TRANSFORMACIONES 230
#define ID_CHECKBOX 235
#define ID_COMP 240
#define ID_TRANSFORM 245
#define SUMA 0
#define RESTA 1
#define PRODUCTO 2


HWND hBtn7=NULL;
HWND screen=NULL;
HWND hCmb1 = NULL;
HWND hCmb2 = NULL;
HWND hCmb3 = NULL;
HWND hCmb4 = NULL;
HWND RX;
HWND RY;
HWND RZ;
HWND TX;
HWND TY;
HWND TZ;
HWND SX;
HWND SY;
HWND SZ;
HWND PX;
HWND PY;
HWND PZ;
HWND VX;
HWND VY;
HWND VZ;
HWND A;
HWND M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11, M12, M13, M14, M15, M16;
HWND V1, V2, V3, V4;
HWND hWnd;
HWND ventana;
HWND mRes = NULL;
HWND hCheck;
HWND hList;
HMENU hMenu;


char digitos[50];
char negador[50]="NEGATE(";
int NUMEROS ;
char filas1[10];
char columnas1[10];
int nFilas;
int nColumnas;
bool activador =  true;
int buffer;
int limite;
int temp[100];
int matriz1[10][10];
int acum;
float degrees;
string borrador;
string temporal;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
{
	origen = NULL;
	aux = NULL;
	indicador = NULL;
	origenR = NULL;
	auxR = NULL;
	origenC = NULL;
	auxC = NULL;
	hInst = hInstance;
	WNDCLASSEX wClase;
	ZeroMemory(&wClase, sizeof(WNDCLASSEX));
	wClase.cbClsExtra = NULL;
	wClase.cbWndExtra = NULL;
	wClase.cbSize = sizeof(WNDCLASSEX);
	wClase.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wClase.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClase.hIcon = NULL;
	wClase.hIconSm = NULL;
	wClase.hInstance = hInstance;
	wClase.lpfnWndProc = (WNDPROC)func;
	wClase.lpszClassName = "Window Class";
	wClase.lpszMenuName = NULL;
	wClase.style = CS_HREDRAW | CS_VREDRAW;

	hInst = hInstance;

	if (!RegisterClassEx(&wClase))
	{
		int nResult = GetLastError();
		MessageBox(NULL, "CREACION DE LA VENTANA FALLO", "LA VENTANA NO FUNCIONO", MB_OK | MB_ICONERROR);
		
	}

	 hWnd = CreateWindowEx(NULL, "Window Class", "PRIMERA VENTANA", WS_OVERLAPPEDWINDOW, 200, 200, 1000, 600, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		int nResult = GetLastError();
		MessageBox(NULL, "FALLO", "ALL MOSTRAR LA VENTANA FALLO", MB_OK | MB_ICONERROR);
	}

		ShowWindow(hWnd, cmdShow);

		MSG msg;

		ZeroMemory(&msg, sizeof(MSG));

		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}

	return 0;
}


LRESULT CALLBACK func(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		addMenu(hWnd);
		Controls(hWnd);
		combos();
		EnableWindow(hCmb4, FALSE);
		EnableWindow(RX, FALSE);
		EnableWindow(RY, FALSE);
		EnableWindow(RZ, FALSE);
		EnableWindow(TX, FALSE);
		EnableWindow(TY, FALSE);
		EnableWindow(TZ, FALSE);
		EnableWindow(SX, FALSE);
		EnableWindow(SY, FALSE);
		EnableWindow(SZ, FALSE);

		break;
	case WM_COMMAND:
	
		switch (LOWORD(wParam))
		{
		/*case ID_LISTBOX:

			/*if (HIWORD(wParam) == LBN_DBLCLK)
			{
				NUMEROS = SendMessage(hList, LB_GETCOUNT, NULL, NULL);
				SendMessage(hList, LB_DELETESTRING, NUMEROS, NULL);

			}

			break;*/

		case ID_CHECKBOX:

			if (HIWORD(wParam) == BN_CLICKED)
				if (SendDlgItemMessage(hWnd, ID_CHECKBOX, BM_GETCHECK, 0, 0))
				{
					EnableWindow(hCmb4, TRUE);
					EnableWindow(RX, TRUE);
					EnableWindow(RY, TRUE);
					EnableWindow(RZ, TRUE);
					EnableWindow(TX, TRUE);
					EnableWindow(TY, TRUE);
					EnableWindow(TZ, TRUE);
					EnableWindow(SX, TRUE);
					EnableWindow(SY, TRUE);
					EnableWindow(SZ, TRUE);
					EnableWindow(hCmb3, FALSE);
				}
				else
				{
					EnableWindow(hCmb4, FALSE);
					EnableWindow(RX, FALSE);
					EnableWindow(RY, FALSE);
					EnableWindow(RZ, FALSE);
					EnableWindow(TX, FALSE);
					EnableWindow(TY, FALSE);
					EnableWindow(TZ, FALSE);
					EnableWindow(SX, FALSE);
					EnableWindow(SY, FALSE);
					EnableWindow(SZ, FALSE);
					EnableWindow(hCmb3, TRUE);
				}

			break;
		case ID_FILA1:
			if (HIWORD(wParam) == CBN_SELENDOK)
			{
				ZeroMemory(&buffer, sizeof(int));
				buffer = SendMessage(hCmb1, CB_GETCURSEL, 0, 0);
				SendMessage(hCmb1, CB_GETLBTEXT, buffer, (LPARAM)filas1);
				nFilas = atoi(filas1);
				GetWindowText(hCmb2, columnas1, 50);
				nColumnas = atoi(columnas1);
				ZeroMemory(&buffer, sizeof(int));
			}
			break;
		case ID_COLUMNAS1:
			if (HIWORD(wParam) == CBN_SELENDOK)
			{
				ZeroMemory(&buffer, sizeof(int));
				buffer = SendMessage(hCmb2, CB_GETCURSEL, NULL, NULL);
				SendMessage(hCmb2, CB_GETLBTEXT, buffer, (LPARAM)columnas1);
				nColumnas = atoi(columnas1);
				GetWindowText(hCmb1, filas1, 50);
				nFilas = atoi(filas1);
				ZeroMemory(&buffer, sizeof(int));
			}

			break;
		case ID_ARITMETICA:

			if (HIWORD(wParam) == CBN_SELENDOK)
			{
				if (origen != NULL && origen->siguiente != NULL)
				{
					ZeroMemory(&NUMEROS, sizeof(int));
					NUMEROS = SendMessage(hCmb3, CB_GETCURSEL, NULL, NULL);
					aritmetica();
				}
				else {
					MessageBox(NULL, "PRIMERO INGRESE LAS MATRICES", "INFO", MB_OK | MB_ICONERROR);
				}
			}

			break;
		case ID_TRANSFORMACIONES:
			auxC = origenC;

			if (HIWORD(wParam) == CBN_SELENDOK)
			{

				ZeroMemory(&NUMEROS, sizeof(int));
				NUMEROS = SendMessage(hCmb4, CB_GETCURSEL, NULL, NULL);
				SendMessage(hCmb4, CB_GETLBTEXT, NUMEROS, (LPARAM)filas1);
				SendMessage(hList, LB_ADDSTRING, NULL, (LPARAM)filas1);

				switch (NUMEROS)
				{
				case 0: // TRASLADAR
					/*
					HWND TX;
					HWND TY;
					HWND TZ;
					*/
					if (origenC == NULL)
					{
						origenC = new mCompuesta;
						GetWindowText(TX, digitos, 5);
						origenC->valorTransformacion = atof(digitos);
						origenC->mTransformacion[0][3] = origenC->valorTransformacion;
						GetWindowText(TY, digitos, 5);
						origenC->valorTransformacion = atof(digitos);
						origenC->mTransformacion[1][3] = origenC->valorTransformacion;
						GetWindowText(TZ, digitos, 5);
						origenC->valorTransformacion = atof(digitos);
						origenC->mTransformacion[2][3] = origenC->valorTransformacion;

						origenC->sigueinteC = NULL;
						origenC->anteriorC = NULL;

					}
					else {

						while (auxC->anteriorC != NULL)
							auxC = auxC->anteriorC;


						auxC->anteriorC = new mCompuesta;
						auxC->anteriorC->sigueinteC = auxC;
						auxC = auxC->anteriorC;
						GetWindowText(TX, digitos, 5);
						auxC->valorTransformacion = atof(digitos);
						auxC->mTransformacion[0][3] = auxC->valorTransformacion;
						GetWindowText(TY, digitos, 5);
						auxC->valorTransformacion = atof(digitos);
						auxC->mTransformacion[1][3] = auxC->valorTransformacion;
						GetWindowText(TZ, digitos, 5);
						auxC->valorTransformacion = atof(digitos);
						auxC->mTransformacion[2][3] = auxC->valorTransformacion;
						auxC->anteriorC = NULL;


					}
					SetWindowText(TX, "");
					SetWindowText(TY, "");
					SetWindowText(TZ, "");
					break;
				case 1://ROTAR X

					if (origenC == NULL)
					{
						origenC = new mCompuesta;
						GetWindowText(RX, digitos, 5);
						origenC->valorTransformacion = atof(digitos);
						origenC->valorTransformacion = origenC->valorTransformacion*3.14159 / 180;
						origenC->mTransformacion[1][1] = cos(origenC->valorTransformacion);
						origenC->mTransformacion[2][1] = sin(origenC->valorTransformacion);
						origenC->mTransformacion[1][2] = -1*(sin(origenC->valorTransformacion));
						origenC->mTransformacion[2][2] = cos(origenC->valorTransformacion);
						origenC->sigueinteC = NULL;
						origenC->anteriorC = NULL;
					}
					else {
						while (auxC->anteriorC != NULL)
							auxC = auxC->anteriorC;

						auxC->anteriorC = new mCompuesta;
						auxC->anteriorC->sigueinteC = auxC;
						auxC = auxC->anteriorC;
						GetWindowText(RX, digitos, 5);
						auxC->valorTransformacion = atof(digitos);
						auxC->valorTransformacion = auxC->valorTransformacion*3.14159 / 180;
						auxC->mTransformacion[1][1] = cos(auxC->valorTransformacion);
						auxC->mTransformacion[2][1] = sin(auxC->valorTransformacion);
						auxC->mTransformacion[1][2] = -1*(sin(auxC->valorTransformacion));
						auxC->mTransformacion[2][2] = cos(auxC->valorTransformacion);
						auxC->anteriorC = NULL;
					}
					SetWindowText(RX,"");

					break;
				case 2://ROTAR Y

					if (origenC == NULL)
					{
						origenC = new mCompuesta;
						GetWindowText(RY, digitos, 5);
						origenC->valorTransformacion = atof(digitos);
						origenC->valorTransformacion = origenC->valorTransformacion*3.14159 / 180;
						origenC->mTransformacion[0][0] = cos(origenC->valorTransformacion);
						origenC->mTransformacion[0][2] = sin(origenC->valorTransformacion);
						origenC->mTransformacion[2][0] = -1*(sin(origenC->valorTransformacion));
						origenC->mTransformacion[2][2] = cos(origenC->valorTransformacion);
						origenC->sigueinteC = NULL;
						origenC->anteriorC = NULL;
					}
					else {
						while (auxC->anteriorC != NULL)
							auxC = auxC->anteriorC;

						auxC->anteriorC = new mCompuesta;
						auxC->anteriorC->sigueinteC = auxC;
						auxC = auxC->anteriorC;
						GetWindowText(RY, digitos, 5);
						auxC->valorTransformacion = atof(digitos);
						auxC->valorTransformacion = auxC->valorTransformacion*3.14159 / 180;
						auxC->mTransformacion[0][0] = cos(auxC->valorTransformacion);
						auxC->mTransformacion[0][2] = sin(auxC->valorTransformacion);
						auxC->mTransformacion[2][0] = -1*(sin(auxC->valorTransformacion));
						auxC->mTransformacion[2][2] = cos(auxC->valorTransformacion);
						auxC->anteriorC = NULL;
					}
					SetWindowText(RY, "");

					break;
				case 3://ROTAR Z

					if (origenC == NULL)
					{
						origenC = new mCompuesta;
						GetWindowText(RZ, digitos, 5);
						origenC->valorTransformacion = atof(digitos);
						origenC->valorTransformacion = origenC->valorTransformacion*3.14159 / 180;
						origenC->mTransformacion[0][0] = cos(origenC->valorTransformacion);
						origenC->mTransformacion[0][1] = -1 * (sin(origenC->valorTransformacion));
						origenC->mTransformacion[1][0] = sin(origenC->valorTransformacion);
						origenC->mTransformacion[1][1] = cos(origenC->valorTransformacion);
						origenC->sigueinteC = NULL;
						origenC->anteriorC = NULL;
					}
					else {
						while (auxC->anteriorC != NULL)
							auxC = auxC->anteriorC;

						auxC->anteriorC = new mCompuesta;
						auxC->anteriorC->sigueinteC = auxC;
						auxC = auxC->anteriorC;
						GetWindowText(RZ, digitos, 5);
						auxC->valorTransformacion = atof(digitos);
						auxC->valorTransformacion = auxC->valorTransformacion*3.14159 / 180;
						auxC->mTransformacion[0][0] = cos(auxC->valorTransformacion);
						auxC->mTransformacion[0][1] = -1 * (sin(auxC->valorTransformacion));
						auxC->mTransformacion[1][0] = sin(auxC->valorTransformacion);
						auxC->mTransformacion[1][1] = cos(auxC->valorTransformacion);
						auxC->anteriorC = NULL;
					}
					SetWindowText(RZ, "");

					break;
				case 4://TRASLADAR NEGATIVO

					if (origenC == NULL)
					{
						origenC = new mCompuesta;
						GetWindowText(TX, digitos, 5);
						origenC->valorTransformacion = atof(digitos);
						origenC->mTransformacion[0][3] = origenC->valorTransformacion;
						GetWindowText(TY, digitos, 5);
						origenC->valorTransformacion = atof(digitos);
						origenC->mTransformacion[1][3] = origenC->valorTransformacion;
						GetWindowText(TZ, digitos, 5);
						origenC->valorTransformacion = atof(digitos);
						origenC->mTransformacion[2][3] = origenC->valorTransformacion;

						origenC->sigueinteC = NULL;
						origenC->anteriorC = NULL;

					}
					else {

						while (auxC->anteriorC != NULL)
							auxC = auxC->anteriorC;


						auxC->anteriorC = new mCompuesta;
						auxC->anteriorC->sigueinteC = auxC;
						auxC = auxC->anteriorC;
						GetWindowText(TX, digitos, 5);
						auxC->valorTransformacion = atof(digitos);
						auxC->mTransformacion[0][3] = auxC->valorTransformacion;
						GetWindowText(TY, digitos, 5);
						auxC->valorTransformacion = atof(digitos);
						auxC->mTransformacion[1][3] = auxC->valorTransformacion;
						GetWindowText(TZ, digitos, 5);
						auxC->valorTransformacion = atof(digitos);
						auxC->mTransformacion[2][3] = auxC->valorTransformacion;
						auxC->anteriorC = NULL;


					}
					SetWindowText(TX, "");
					SetWindowText(TY, "");
					SetWindowText(TZ, "");

					break;
				case 5://ESCALAR

					if (origenC == NULL)
					{
						origenC = new mCompuesta;
						GetWindowText(SX, digitos, 5);
						origenC->valorTransformacion = atof(digitos);
						origenC->mTransformacion[0][0] = origenC->valorTransformacion;
						GetWindowText(SY, digitos, 5);
						origenC->valorTransformacion = atof(digitos);
						origenC->mTransformacion[1][1] = origenC->valorTransformacion;
						GetWindowText(SZ, digitos, 5);
						origenC->valorTransformacion = atof(digitos);
						origenC->mTransformacion[2][2] = origenC->valorTransformacion;
						origenC->sigueinteC = NULL;
						origenC->anteriorC = NULL;

					}
					else {

						while (auxC->anteriorC != NULL)
							auxC = auxC->anteriorC;

						auxC->anteriorC = new mCompuesta;
						auxC->anteriorC->sigueinteC = auxC;
						auxC = auxC->anteriorC;
						GetWindowText(SX, digitos, 5);
						auxC->valorTransformacion = atof(digitos);
						auxC->mTransformacion[0][0] = auxC->valorTransformacion;
						GetWindowText(SY, digitos, 5);
						auxC->valorTransformacion = atof(digitos);
						auxC->mTransformacion[1][1] = auxC->valorTransformacion;
						GetWindowText(SZ, digitos, 5);
						auxC->valorTransformacion = atof(digitos);
						auxC->mTransformacion[2][2] = auxC->valorTransformacion;
						auxC->anteriorC = NULL;


					}

					break;
				case 6:
					cuaternio();
					SendMessage(hList, LB_DELETESTRING, NULL, NULL);
					break;
				case 7:
					MxV();
					SendMessage(hList, LB_DELETESTRING, NULL, NULL);
					break;
				default:

					break;
				}
			}

			break;
		case ID_TRANSFORM:
			if (origenC != NULL)
			{

				GetWindowText(PX, digitos, 5);
				origenC->mTemporal[0][0] = atof(digitos);
				GetWindowText(PY, digitos, 5);
				origenC->mTemporal[1][0] = atof(digitos);
				GetWindowText(PZ, digitos, 5);
				origenC->mTemporal[2][0] = atof(digitos);
				origenC->mTemporal[3][0] = 1;

				int pos = 780;
				double acum = 0;
				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 1; j++)
					{
						for (int cont = 0; cont < 4; cont++)
							acum = acum + origenC->mTransformacion[i][cont] * origenC->mTemporal[cont][j];

						origenC->mComp[i][j] = acum;
						_itoa_s(origenC->mTemporal[i][0], digitos, 10);
						CreateWindowEx(NULL, "STATIC", digitos, WS_VISIBLE | SS_CENTER | WS_CHILD, pos, 50, 50, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
						//ZeroMemory(digitos, sizeof(&digitos));
						snprintf(digitos, 6/*sizeof(digitos)*/, "%f", auxC->mComp[i][0]);
						CreateWindowEx(NULL, "STATIC", digitos, WS_VISIBLE | SS_CENTER | WS_CHILD, pos, 150, 50, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
						pos = pos + 50;
						acum = 0;
					}

				int j = SendMessage(hList, LB_GETCOUNT, NULL, NULL);
				for (int i = 1; j >= i; i++)
				{
					SendMessage(hList, LB_DELETESTRING, NULL, NULL);
				}

				/*auxC = origenC->anteriorC;
				while (auxC->anteriorC!= NULL)
				{
					if (auxC->sigueinteC == origenC && auxC->anteriorC != NULL)
					{
						auxC->anteriorC->sigueinteC = auxC->sigueinteC;
						auxC->sigueinteC->anteriorC = auxC->anteriorC;
						delete auxC;
						auxC = origenC;
					}
					else if (auxC->sigueinteC == origenC && auxC->anteriorC == NULL)
					{
						delete auxC;
						origenC->anteriorC == NULL;
					}
					auxC = auxC->anteriorC;
				}*/
			}
			else {
				MessageBox(NULL, "NO HAY MATRIZ COMPUESTA", "INFO", MB_ICONERROR | MB_OK);
			}
			origenC;
			break;
		case ID_COMP:
			compositar();
			break;

		case ID_BOTON7:
			GetWindowText(screen, digitos,50);
			strcat_s(digitos, "7");
			SetWindowText(screen, digitos);
			break;
		case ID_BOTON1:
			GetWindowText(screen, digitos, 50);
			strcat_s(digitos, "1");
			SetWindowText(screen, digitos);
			break;
		case ID_BOTON8:		
			GetWindowText(screen, digitos, 50);
			strcat_s(digitos, "8");
			SetWindowText(screen, digitos);
			break;
		case ID_BOTON9:
			GetWindowText(screen, digitos, 50);
			strcat_s(digitos, "9");
			SetWindowText(screen, digitos);
			break;
		case ID_BOTON5:
			GetWindowText(screen, digitos, 50);
			strcat_s(digitos, "5");
			SetWindowText(screen, digitos);
			break;
		case ID_BOTON6:
			GetWindowText(screen, digitos, 50);
			strcat_s(digitos, "6");
			SetWindowText(screen, digitos);
			break;
		case ID_BOTON2:
			GetWindowText(screen, digitos, 50);
			strcat_s(digitos, "2");
			SetWindowText(screen, digitos);
			break;
		case ID_BOTON3:
			GetWindowText(screen, digitos, 50);
			strcat_s(digitos, "3");
			SetWindowText(screen, digitos);
			break;
		case ID_BOTON4:
			GetWindowText(screen, digitos, 50);
			strcat_s(digitos, "4");
			SetWindowText(screen, digitos);
			break;
		case ID_BOTONNEGATE:
			if (activador==true)
			{
				activador = false;
				GetWindowText(screen, digitos, 50);
				SetWindowText(screen, "");
				//NUMEROS = atoi(digitos);
				//NUMEROS = NUMEROS * -1;
				strcat_s(negador, digitos);
				strcpy_s(digitos, negador);
				SetWindowText(screen, digitos);

			}
			else if (activador == false)
			{
				activador = true;
				GetWindowText(screen, digitos, 50);
				SetWindowText(screen, "");
				stringstream sso;
				sso << digitos;
				sso >> borrador;
				NUMEROS = borrador.size();
				NUMEROS = NUMEROS - 6;
				borrador = borrador.substr(7,NUMEROS);
				stringstream so;
				so << borrador;
				so >> digitos;
				SetWindowText(screen, digitos);
				strcpy_s(negador, "NEGATE(");

			}
			break;
		case ID_BOTON0:
			GetWindowText(screen, digitos, 50);
			strcat_s(digitos, "0");
			SetWindowText(screen, digitos);
			break;
		case ID_BOTONC:
			SetWindowText(screen, "");
			GetWindowText(screen, digitos, 50);
			strcpy_s(negador, "NEGATE(");
			activador = true;
			break;
		case ID_ENTER:

			if (limite == 0)
			{
				limite = nFilas * nColumnas;
				nFilas--;
				nColumnas--;
				if (limite == 0)
				{
					if (nFilas != 0)
						limite = nFilas;

					if (nColumnas != 0)
						limite = nColumnas;

				}
			}
			 if(buffer<limite){
				 //CONVERTI MIS NUMEROS A NEGATIVOS TANTO EL BOTON DE NEGADOR ALLA SIDO PULSADO, SI EL BOTON NO SE PULSO, NO SE HARAN NEGATIVOS
				 if (activador == false)
				 {
					 activador = true;
					 GetWindowText(screen, digitos, 50);
					 stringstream sso;
					 sso << digitos;
					 sso >> borrador;
					 NUMEROS = borrador.size();
					 NUMEROS = NUMEROS - 6;
					 borrador = borrador.substr(7, NUMEROS);
					 stringstream so;
					 so << borrador;
					 so >> digitos;
					 NUMEROS = atoi(digitos);
					 temp[buffer] = NUMEROS * -1;
					 SetWindowText(screen, "");
					 strcpy_s(negador, "NEGATE(");
					 buffer++;
				 }
				 //SI EL BOTON NO HA SIDO PULSADO, SEGUIRA CON EL PROTOCOLO NORMAL
				 else {
					 GetWindowText(screen, digitos, 50);
					 temp[buffer] = atoi(digitos);
					 SetWindowText(screen, "");
					 buffer++;
				 }
			}
			if (buffer >= limite)
			{
				ZeroMemory(&buffer, sizeof(int));
			for(int i =0; nFilas>=i;i++)
				for (int j = 0; nColumnas >= j; j++)
				{
					matriz1[i][j] = temp[buffer];
					buffer++;
				}
			ingresoDatos();
			for (int i = 0; nFilas >= i; i++)
				for (int j = 0; nColumnas >= j; j++)
				{
					matriz1[i][j] = 0;
				}
			MessageBox(NULL, "LA MTRAIZ A SIDO LLENADA", "INFO", MB_OK | MB_ICONERROR);
			ZeroMemory(&buffer, sizeof(int));
			ZeroMemory(&limite, sizeof(int));
			//ZeroMemory(&nFilas, sizeof(int));
			//ZeroMemory(&nColumnas, sizeof(int));
			}

			break;
		case FILE_MENU:
			MessageBeep(MB_OK);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}
}

void addMenu(HWND hWnd)
{
	hMenu = CreateMenu();
	HMENU hPopMenu = CreateMenu();
	HMENU hSubMenu = CreateMenu();
	
	AppendMenu(hMenu, MF_POPUP,(UINT_PTR)hPopMenu, "MENU");
	AppendMenu(hMenu, MF_STRING, FILE_MENU, "FILE");
	AppendMenu(hMenu, MF_STRING, FILE_MENU, "HELP");
	AppendMenu(hMenu, MF_STRING, FILE_MENU, "SETTINGS");

	//MENU//
	AppendMenu(hPopMenu, MF_STRING, FILE_MENU, "NEW PRODUCT");
	AppendMenu(hPopMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hPopMenu, MF_POPUP, (UINT_PTR)hSubMenu, "EXIT");

	//SUBMENUS DE MENU//
	AppendMenu(hSubMenu, MF_STRING, NULL, "SAVE & EXIT");
	AppendMenu(hSubMenu, MF_STRING, NULL, "NO SAVE & EXIT");


	SetMenu(hWnd, hMenu);
	return;
}

void Controls(HWND hWnd)
{


	hBtn7 = CreateWindowEx(NULL, "BUTTON", "7", WS_VISIBLE | WS_CHILD, 160, 160, 100, 50, hWnd, (HMENU)ID_BOTON7, GetModuleHandle(NULL), NULL);
	hBtn7 = CreateWindowEx(NULL, "BUTTON", "4", WS_VISIBLE | WS_CHILD, 160, 235, 100, 50, hWnd, (HMENU)ID_BOTON4, GetModuleHandle(NULL), NULL);
	hBtn7 = CreateWindowEx(NULL, "BUTTON", "1", WS_VISIBLE | WS_CHILD, 160, 310, 100, 50, hWnd, (HMENU)ID_BOTON1, GetModuleHandle(NULL), NULL);
	hBtn7 = CreateWindowEx(NULL, "BUTTON", "8", WS_VISIBLE | WS_CHILD, 285, 160, 100, 50, hWnd, (HMENU)ID_BOTON8, GetModuleHandle(NULL), NULL);
	hBtn7 = CreateWindowEx(NULL, "BUTTON", "9", WS_VISIBLE | WS_CHILD, 410, 160, 100, 50, hWnd, (HMENU)ID_BOTON9, GetModuleHandle(NULL), NULL);
	hBtn7 = CreateWindowEx(NULL, "BUTTON", "5", WS_VISIBLE | WS_CHILD, 285, 235, 100, 50, hWnd, (HMENU)ID_BOTON5, GetModuleHandle(NULL), NULL);
	hBtn7 = CreateWindowEx(NULL, "BUTTON", "6", WS_VISIBLE | WS_CHILD, 410, 235, 100, 50, hWnd, (HMENU)ID_BOTON6, GetModuleHandle(NULL), NULL);
	hBtn7 = CreateWindowEx(NULL, "BUTTON", "2", WS_VISIBLE | WS_CHILD, 285, 310, 100, 50, hWnd, (HMENU)ID_BOTON2, GetModuleHandle(NULL), NULL);
	hBtn7 = CreateWindowEx(NULL, "BUTTON", "3", WS_VISIBLE | WS_CHILD, 410, 310, 100, 50, hWnd, (HMENU)ID_BOTON3, GetModuleHandle(NULL), NULL);
	hBtn7 = CreateWindowEx(NULL, "BUTTON", "+/-", WS_VISIBLE | WS_CHILD, 160, 385, 100, 50, hWnd, (HMENU)ID_BOTONNEGATE, GetModuleHandle(NULL), NULL);
	hBtn7 = CreateWindowEx(NULL, "BUTTON", "0", WS_VISIBLE | WS_CHILD, 285, 385, 100, 50, hWnd, (HMENU)ID_BOTON0, GetModuleHandle(NULL), NULL);
	hBtn7 = CreateWindowEx(NULL, "BUTTON", "C/", WS_VISIBLE | WS_CHILD, 410, 385, 100, 50, hWnd, (HMENU)ID_BOTONC, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "BUTTON", "COMPUESTA", WS_VISIBLE | WS_CHILD, 525, 480, 150, 30, hWnd, (HMENU)ID_COMP, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "BUTTON", "TRANSFORMAR", WS_VISIBLE | WS_CHILD, 675, 480, 150, 30, hWnd, (HMENU)ID_TRANSFORM, GetModuleHandle(NULL), NULL);
	screen = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD|WS_BORDER|SS_RIGHT,160, 0, 350, 150, hWnd, NULL ,GetModuleHandle(NULL), NULL);
	RX = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,530,200,25,25,hWnd,NULL,GetModuleHandle(NULL),NULL );
	RZ = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 590, 200, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	RY = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 560, 200, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	TX = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 530, 280, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	TY = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 560, 280, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	TZ = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 590, 280, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	SX = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 530, 360, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	SZ = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 590, 360, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	SY = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 560, 360, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	PX = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 530, 440, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	PZ = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 590, 440, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	PY = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 560, 440, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	VX = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 620, 440, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	VY = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 650, 440, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	VZ = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 680, 440, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	A = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 740, 440, 50, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	M1 = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 650, 200, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	M2 = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 680, 200, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	M3 = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 710, 200, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	M4 = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 740, 200, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	M5 = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 650, 230, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	M6 = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 680, 230, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	M7 = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 710, 230, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	M8 = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 740, 230, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	M9 = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 650, 260, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	M10 = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 680, 260, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	M11 = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 710, 260, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	M12 = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 740, 260, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	M13 = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 650, 290, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	M14 = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 680, 290, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	M15 = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 710, 290, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	M16 = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 740, 290, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	V1 = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 800, 200, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	V2 = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 800, 230, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	V3 = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 800, 260, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	V4 = CreateWindowEx(NULL, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 800, 290, 25, 25, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "ESCALACIONES", WS_VISIBLE | SS_CENTER | WS_CHILD, 530, 310, 100, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "SX", WS_VISIBLE | SS_CENTER | WS_CHILD, 530, 340, 20, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "SY", WS_VISIBLE | SS_CENTER | WS_CHILD, 560, 340, 20, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "SZ", WS_VISIBLE | SS_CENTER | WS_CHILD, 590, 340, 20, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "TRASLACIONES", WS_VISIBLE | SS_CENTER | WS_CHILD, 530, 230, 100, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "TX", WS_VISIBLE | SS_CENTER | WS_CHILD, 530, 260, 20, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "TY", WS_VISIBLE | SS_CENTER | WS_CHILD, 560, 260, 20, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "TZ", WS_VISIBLE | SS_CENTER | WS_CHILD, 590, 260, 20, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "ROTACIONES", WS_VISIBLE | SS_CENTER | WS_CHILD, 525, 150, 100, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "RX", WS_VISIBLE | SS_CENTER | WS_CHILD, 530, 180, 20, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "RY", WS_VISIBLE | SS_CENTER | WS_CHILD, 560, 180, 20, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "RZ", WS_VISIBLE | SS_CENTER | WS_CHILD, 590, 180, 20, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "PUNTO", WS_VISIBLE | SS_LEFT | WS_CHILD, 530, 390, 150, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "PX", WS_VISIBLE | SS_CENTER | WS_CHILD, 530, 420, 20, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "PY", WS_VISIBLE | SS_CENTER | WS_CHILD, 560, 420, 20, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "PZ", WS_VISIBLE | SS_CENTER | WS_CHILD, 590, 420, 20, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "VX", WS_VISIBLE | SS_CENTER | WS_CHILD, 620, 420, 20, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "VY", WS_VISIBLE | SS_CENTER | WS_CHILD, 650, 420, 20, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "VZ", WS_VISIBLE | SS_CENTER | WS_CHILD, 680, 420, 20, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "ANGULO", WS_VISIBLE | SS_LEFT | WS_CHILD, 740, 420, 70, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "ACTIVAR", WS_VISIBLE | SS_CENTER | WS_CHILD, 0, 495, 200, 150, hWnd, NULL, GetModuleHandle(NULL), NULL);
	hBtn7 = CreateWindowEx(NULL, "BUTTON", "ENTER", WS_VISIBLE | WS_CHILD, 160, 460, 350, 50, hWnd, (HMENU)ID_ENTER, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "OPERACION A REALIZAR", WS_VISIBLE | SS_CENTER | WS_CHILD, 10, 55, 100, 45, hWnd, NULL, GetModuleHandle(NULL), NULL);
	hCmb1 = CreateWindowEx(NULL, "COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE | WS_OVERLAPPED, 10, 25, 70, 500, hWnd, (HMENU)ID_FILA1, GetModuleHandle(NULL), NULL);
	hCmb2 = CreateWindowEx(NULL, "COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE | WS_OVERLAPPED, 85, 25, 70, 500, hWnd, (HMENU)ID_COLUMNAS1, GetModuleHandle(NULL), NULL);
	hCmb4 = CreateWindowEx(NULL, "COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE | WS_OVERLAPPED, 10, 450, 145, 500, hWnd, (HMENU)ID_TRANSFORMACIONES, GetModuleHandle(NULL), NULL);
	hCmb3 = CreateWindowEx(NULL, "COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE | WS_OVERLAPPED, 10, 90, 145, 250, hWnd, (HMENU)ID_ARITMETICA, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "MATRIZ 1", WS_VISIBLE | SS_CENTER | WS_CHILD, 10, 5, 85, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "TRANSFORMACIONES", WS_VISIBLE | SS_CENTER | WS_CHILD, 10, 125, 150, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "RESULTADOS", WS_VISIBLE | SS_CENTER | WS_CHILD, 600, 10, 100, 45, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "PUNTO ORIGINAL", WS_VISIBLE | SS_CENTER | WS_CHILD, 800, 10, 100, 45, hWnd, NULL, GetModuleHandle(NULL), NULL);
	CreateWindowEx(NULL, "STATIC", "PUNTO TRANSFORMADO", WS_VISIBLE | SS_CENTER | WS_CHILD, 800, 100, 110, 45, hWnd, NULL, GetModuleHandle(NULL), NULL);
	hList = CreateWindowEx(NULL, "LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_OVERLAPPED, 10, 150, 143, 300, hWnd, (HMENU)ID_LISTBOX, GetModuleHandle(NULL), NULL);
	hCheck = CreateWindowEx(NULL, "BUTTON", NULL, BS_AUTOCHECKBOX|WS_CHILD|WS_VISIBLE, 10, 475, 60, 60, hWnd, (HMENU)ID_CHECKBOX, NULL, NULL);


	return;
}



void combos()
{

	char buffer[10];
	int numeros=0;
	for (int i = 1; i <= 10; i++)
	{
		numeros = i;
		_itoa_s(numeros, buffer, 10);
		SendMessage(hCmb1, CB_ADDSTRING, NULL, (LPARAM)buffer);
		SendMessage(hCmb2, CB_ADDSTRING, NULL, (LPARAM)buffer);
	}

	SendMessage(hCmb3, CB_ADDSTRING, NULL, (LPARAM)"SUMAR MATRICES");
	SendMessage(hCmb3, CB_ADDSTRING, NULL, (LPARAM)"RESTAR MATRICES");
	SendMessage(hCmb3, CB_ADDSTRING, NULL, (LPARAM)"MULTIPLICAR MATRICES");

	SendMessage(hCmb4, CB_ADDSTRING, NULL, (LPARAM)"TRASLADAR");
	SendMessage(hCmb4, CB_ADDSTRING, NULL, (LPARAM)"ROTAR 'X'");
	SendMessage(hCmb4, CB_ADDSTRING, NULL, (LPARAM)"ROTAR 'Y'");
	SendMessage(hCmb4, CB_ADDSTRING, NULL, (LPARAM)"ROTAR 'Z'");
	SendMessage(hCmb4, CB_ADDSTRING, NULL, (LPARAM)"TRASLADAR NEGATIVO");
	SendMessage(hCmb4, CB_ADDSTRING, NULL, (LPARAM)"ESCALAR");
	SendMessage(hCmb4, CB_ADDSTRING, NULL, (LPARAM)"CUATERNIO");
	SendMessage(hCmb4, CB_ADDSTRING, NULL, (LPARAM)"MxV");


	return;
}



void ingresoDatos()
{
	aux = origen;

	if (origen == NULL)
	{
		origen = new matrices;
		origen->filas = nFilas;
		origen->columnas = nColumnas;
		for (int i = 0; nFilas >= i; i++)
		{
			for (int j = 0; nColumnas >= j; j++)
			{
				origen->matriz[i][j] = 0;
				origen->matriz[i][j] = matriz1[i][j];
				matriz1[i][j] = 0;
			}
		}

		origen->anterior = NULL;
		origen->siguiente=NULL;

		aux = origen;
		MessageBox(NULL, "MATRIZ EXITOSA", "INFO", MB_OK | MB_ICONASTERISK);
		return;
	}
	else if(origen!=NULL) {

		while (aux->siguiente != NULL)
			aux = aux->siguiente;

		aux->siguiente = new matrices;
		aux->siguiente->anterior = aux;
		aux = aux->siguiente;

		aux->filas = nFilas;
		aux->columnas = nColumnas;

		for(int i=0;nFilas>=i;i++)
			for (int j = 0; nColumnas >= j; j++)
			{
				aux->matriz[i][j] = matriz1[i][j];
				matriz1[i][j] = 0;
			}

		aux->siguiente = NULL;

		aux = origen;
		MessageBox(NULL, "MATRIZ EXITOSA", "INFO", MB_OK | MB_ICONASTERISK);
		return;

	}

	return;
	aux = origen;
}


void aritmetica()
{
	aux = origen;
	auxR = origenR;
	switch (NUMEROS)
	{
	case SUMA:
		//validadacion de que se puedan sumar
		if (aux->filas == aux->siguiente->filas)
		{
			if (origenR == NULL)
			{
				origenR = new mResultados;
				origenR->filasR = aux->filas;
				origenR->columnasR = aux->columnas;
				indicador = aux->siguiente;
				for (int i = 0; origenR->filasR >= i; i++)
					for (int j = 0; origenR->columnasR >= j; j++)
					{
						origenR->matrizR[i][j] = aux->matriz[i][j] + indicador->matriz[i][j];
					}
				origenR->siguienteR = NULL;
				origenR->anteriorR = NULL;
				liberar();
			}
			else
			{
				while (auxR->siguienteR != NULL)
					auxR = auxR->siguienteR;



				auxR->siguienteR = new mResultados;
				auxR->siguienteR->anteriorR = auxR;
				auxR = auxR->siguienteR;
				auxR->filasR = nFilas;
				auxR->columnasR = nColumnas;
				indicador->siguiente;
				for (int i = 0; auxR->filasR >= i; i++)
					for (int j = 0; auxR->columnasR >= j; j++)
					{
						auxR->matrizR[i][j] = aux->matriz[i][j] + indicador->matriz[i][j];
					}
				auxR->siguienteR = NULL;
				liberar();
			}
			resultados(hWnd);
		}
		else
		{
			MessageBox(NULL, "LA DIMECIONES DE LAS MATRICES SON DIFERENTES", "INFO", MB_OK | MB_ICONERROR);
			liberar();
		}
		break;
	case RESTA:
		if (aux->filas == aux->siguiente->filas)
		{
			if (origenR == NULL)
			{
				origenR = new mResultados;
				origenR->filasR = aux->filas;
				origenR->columnasR = aux->columnas;
				indicador=aux->siguiente;
				for(int i=0;origenR->filasR>=i;i++)
					for (int j = 0; origenR->columnasR >= j; j++)
					{
						indicador->matriz[i][j] = indicador->matriz[i][j] * -1;
						origenR->matrizR[i][j] = aux->matriz[i][j] + indicador->matriz[i][j];
					}
				origenR->siguienteR = NULL;
				origenR->anteriorR = NULL;
				liberar();
			}
			else {

				while (auxR->siguienteR != NULL)
					auxR = auxR->siguienteR;

				auxR->siguienteR = new mResultados;
				auxR->siguienteR->anteriorR = auxR;
				auxR = auxR->siguienteR;
				auxR->filasR = nFilas;
				auxR->columnasR = nColumnas;
				indicador = aux->siguiente;
				for(int i = 0; auxR->filasR>=i;i++)
					for (int j = 0; auxR->columnasR >= j; j++)
					{
						indicador->matriz[i][j] = indicador->matriz[i][j]*-1;
						auxR->matrizR[i][j] = aux->matriz[i][j] + indicador->matriz[i][j];
					}
				auxR->siguienteR = NULL;
				liberar();
			}
			resultados(hWnd);
		}
		else
		{
			MessageBox(NULL, "LAS DIMENCIONES SON DIFERENTES", "INFO", MB_ICONERROR | MB_OK);
			liberar();
		}
		break;
	case PRODUCTO:

		if (aux->columnas == aux->siguiente->filas)
		{
			if (origenR == NULL)
			{
				origenR = new mResultados;
				origenR->filasR = nFilas;
				origenR->columnasR = nColumnas;
				indicador = aux->siguiente;
				int acum = 0;
				for(int i =0;origenR->filasR>=i;i++)
					for (int j = 0; origenR->columnasR >= j; j++)
					{
						for (int cont = 0; cont <= origenR->columnasR; cont++)
							acum = acum + aux->matriz[i][cont] * indicador->matriz[cont][j];

						origenR->matrizR[i][j] = acum;
						acum = 0;
					}
				origenR->siguienteR = NULL;
				origenR->anteriorR = NULL;
				liberar();
			}
			else {
				while (auxR->siguienteR != NULL)
					auxR = auxR->siguienteR;


				auxR->siguienteR = new mResultados;
				auxR->siguienteR->anteriorR=auxR;
				auxR = auxR->siguienteR;
				auxR->filasR = nFilas;
				auxR->columnasR = nColumnas;
				indicador = aux->siguiente;
				int acum = 0;
				for (int i = 0; auxR->filasR >= i; i++)
					for (int j = 0; auxR->columnasR >= j; j++)
					{
						for (int cont = 0; cont <= auxR->columnasR; cont++)
							acum = acum + aux->matriz[i][cont] * indicador->matriz[cont][j];

						auxR->matrizR[i][j] = acum;
						acum = 0;
					}
				auxR->siguienteR = NULL;
				liberar();
			}
			resultados(hWnd);
	    }
		break;
	default:
		break;
	}
}


void liberar()
{
	aux = origen;
	while (aux != NULL)
	{
		if (origen == aux)
		{
			origen = aux->siguiente;
			aux->siguiente->anterior = NULL;
			aux->siguiente = NULL;
			delete aux;
			aux = origen;
		}
		if (aux->siguiente == NULL && aux->anterior == NULL)
		{
			delete aux;
			origen = aux = NULL;
		}
	}
	return;
}


void resultados(HWND hWnd)
{

	auxR = origenR;
	strcpy_s(filas1, "");
	int x = 600;
	int y = 50;

	while (auxR->siguienteR != NULL)
		auxR = auxR->siguienteR;


	if (auxR != origenR)
	{
		for (int i = 0; auxR->anteriorR->filasR >= i; i++)
		{
			for (int j = 0; auxR->anteriorR->columnasR >= j; j++)
			{

				CreateWindowEx(NULL, "STATIC", "   ", WS_VISIBLE | SS_CENTER | WS_CHILD, x, y, 20, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
				x = x + 25;
			}
			x = 600;
			y = y + 25;
		}
		x = 600;
		y = 50;
	}


		for (int i = 0; auxR->filasR >= i; i++)
		{
			for (int j = 0; auxR->columnasR >= j; j++)
			{
				_itoa_s(auxR->matrizR[i][j], filas1, 10);

				 CreateWindowEx(NULL, "STATIC", filas1, WS_VISIBLE | SS_CENTER | WS_CHILD, x, y, 20, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
				strcpy_s(filas1, "");
				x = x + 25;
			}
			x = 600;
			y = y + 25;
		}

		auxR = origenR;
		strcpy_s(filas1, "");
	
}


void compositar()
{
	int borrador = 0;
	auxC = origenC;
	while (auxC->anteriorC != NULL)
		auxC = auxC->anteriorC;
	while(auxC->sigueinteC!=NULL)
	{ 
		double acum = 0;
		for (int i = 0; auxC->filas > i; i++)
			for (int j = 0; auxC->columnas > j; j++)
			{
				for (int cont = 0; cont < auxC->columnas; cont++)
					acum = acum + auxC->mTransformacion[i][cont] * auxC->sigueinteC->mTransformacion[cont][j];

				auxC->mTemporal[i][j] = acum;
				acum = 0;
			}
		for(int i = 0; i<auxC->filas;i++)
			for (int j = 0; j < auxC->columnas; j++)
			{
				auxC->sigueinteC->mTransformacion[i][j] = auxC->mTemporal[i][j];
			}
		auxC = auxC->sigueinteC;
		SendMessage(hList, LB_DELETESTRING, borrador, NULL);
		borrador++;
	}

	for(int i = 0;i<4;i++)
		for (int j = 0; j < 4; j++)
		{
			snprintf(digitos, sizeof(digitos), "%f", auxC->mTransformacion[i][j]);

		}

	return;
}

void cuaternio()
{
	float p1=0.00;
	float p2= 0.00;
	float p3= 0.00;
	float ang= 0.00;
	float v[3];
	float c= 0.00;
	float r[4];
	float R[4];
	float u= 0.00;
	GetWindowText(PX, digitos, 3);
	p1 = atof(digitos);
	GetWindowText(PY, digitos, 3);
	p2 = atof(digitos);
	GetWindowText(PZ, digitos, 3);
	p3 = atof(digitos);
	GetWindowText(VX, digitos, 3);
	v[0] = atof(digitos);
	GetWindowText(VY, digitos, 3);
	v[1] = atof(digitos);
	GetWindowText(VZ, digitos, 3);
	v[2] = atof(digitos);
	GetWindowText(A, digitos, 4);
	ang = atof(digitos);

		u = (v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]);
		u = sqrt(u);
		v[0] = v[0] / u;
		v[1] = v[1] / u;
		v[2] = v[2] / u;
		r[0] = (cos(ang * 3.14159 / 360));
		r[1] = (v[0] * sin(ang * 3.14159 / 360));
		r[2] = (v[1] * sin(ang * 3.14159 / 360));
		r[3] = (v[2] * sin(ang * 3.14159 / 360));
		R[0] = -(r[1] * p1) - (r[2] * p2) - (r[3] * p3);
		R[1] = (r[0] * p1) + (r[2] * p3) - (r[3] * p2);
		R[2] = (r[0] * p2) + (r[3] * p1) - (r[1] * p3);
		R[3] = (r[0] * p3) + (r[1] * p2) - (r[2] * p1);
		r[1] = -1 * r[1];
		r[2] = -1 * r[2];
		r[3] = -1 * r[3];
		c = -(R[1] * r[1]) - (r[2] * R[2]) - (r[3] * R[3]) + (r[0] * R[0]);
		p1 = (R[0] * r[1]) - (r[2] * R[3]) + (r[2] * R[2]) + (r[0] * R[1]);
		if (p1 < 0.01&&p1>0 || p1<0 && p1>-.01) {
			p1 = 0;
		}
		p2 = (R[0] * r[2]) + (r[1] * R[3]) - (r[3] * R[1]) + (r[0] * R[2]);
		if (p2 < 0.01&&p2>0 || p2<0 && p2>-.01) {
			p2 = 0;
		}
		p3 = (R[0] * r[3]) + (r[2] * R[1]) - (r[1] * R[2]) + (r[0] * R[3]);
		if (p3 < 0.01&&p3>0 || p3<0 && p3>-.01) {
			p3 = 0;
		}
		snprintf(digitos, 6/*sizeof(digitos)*/, "%f", p1);
		CreateWindowEx(NULL, "STATIC", digitos, WS_VISIBLE | SS_CENTER | WS_CHILD, 780, 150, 50, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
		snprintf(digitos, 6/*sizeof(digitos)*/, "%f", p2);
		CreateWindowEx(NULL, "STATIC", digitos, WS_VISIBLE | SS_CENTER | WS_CHILD, 830, 150, 50, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
		snprintf(digitos, 6/*sizeof(digitos)*/, "%f", p3);
		CreateWindowEx(NULL, "STATIC", digitos, WS_VISIBLE | SS_CENTER | WS_CHILD, 980, 150, 50, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
}

void MxV()
{
	int matriz[4][4];
	int vector[4][4];
	int resultado[4][4];
	GetWindowText(M1, digitos, 3);
	matriz[0][0] = atoi(digitos);
	GetWindowText(M2, digitos, 3);
	matriz[0][1] = atoi(digitos);
	GetWindowText(M3, digitos, 3);
	matriz[0][2] = atoi(digitos);
	GetWindowText(M4, digitos, 3);
	matriz[0][3] = atoi(digitos);
	GetWindowText(M5, digitos, 3);
	matriz[1][0] = atoi(digitos);
	GetWindowText(M6, digitos, 3);
	matriz[1][1] = atoi(digitos);
	GetWindowText(M7, digitos, 3);
	matriz[1][2] = atoi(digitos);
	GetWindowText(M8, digitos, 3);
	matriz[1][3] = atoi(digitos);
	GetWindowText(M9, digitos, 3);
	matriz[2][0] = atoi(digitos);
	GetWindowText(M10, digitos, 3);
	matriz[2][1] = atoi(digitos);
	GetWindowText(M11, digitos, 3);
	matriz[2][2] = atoi(digitos);
	GetWindowText(M12, digitos, 3);
	matriz[2][3] = atoi(digitos);
	GetWindowText(M13, digitos, 3);
	matriz[3][0] = atoi(digitos);
	GetWindowText(M14, digitos, 3);
	matriz[3][1] = atoi(digitos);
	GetWindowText(M15, digitos, 3);
	matriz[3][2] = atoi(digitos);
	GetWindowText(M16, digitos, 3);
	matriz[3][3] = atoi(digitos);


	GetWindowText(V1, digitos, 3);
	vector[0][0] = atoi(digitos);
	GetWindowText(V2, digitos, 3);
	vector[1][0] = atoi(digitos);
	GetWindowText(V3, digitos, 3);
	vector[2][0] = atoi(digitos);
	GetWindowText(V4, digitos, 3);
	vector[3][0] = atoi(digitos);

	
	int acum = 0;
	for (int i = 0; 3 >= i; i++)
		for (int j = 0; 3 >= j; j++)
		{
			for (int cont = 0; cont <= 3; cont++)
				acum = acum + matriz[i][cont] * vector[cont][j];

			resultado[i][j] = acum;
			acum = 0;
		}

	_itoa_s(resultado[0][0], digitos, 10);
	CreateWindowEx(NULL, "STATIC", digitos, WS_VISIBLE | SS_CENTER | WS_CHILD, 840, 200, 50, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	_itoa_s(resultado[1][0], digitos, 10);
	CreateWindowEx(NULL, "STATIC", digitos, WS_VISIBLE | SS_CENTER | WS_CHILD, 840, 230, 50, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	_itoa_s(resultado[2][0], digitos, 10);
	CreateWindowEx(NULL, "STATIC", digitos, WS_VISIBLE | SS_CENTER | WS_CHILD, 840, 260, 50, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);
	_itoa_s(resultado[3][0], digitos, 10);
	CreateWindowEx(NULL, "STATIC", digitos, WS_VISIBLE | SS_CENTER | WS_CHILD, 840, 290, 50, 20, hWnd, NULL, GetModuleHandle(NULL), NULL);


}