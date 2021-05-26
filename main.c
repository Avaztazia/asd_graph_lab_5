#include<windows.h>
#include<math.h>
#include <stdio.h>
#include <stdlib.h>

#define numb 11
#define oneLen 180

int nx[numb] = {};
int ny[numb] = {};
double** mat = NULL;
double** dfs = NULL;
double** bfs = NULL;
int visited[numb] = {};
int thisOne = -1;
int check = 0;
char *hums[numb] = {};
int humsPos = 0;
int humsSwitch = 0;

void humAdd ( )
{
    char res;
    switch(humsPos)
    {
        case 0:
            hums[humsPos] = "a";
            break;
        case 1:
            hums[humsPos] = "b";
            break;
        case 2:
            hums[humsPos] = "c";
            break;
        case 3:
            hums[humsPos] = "d";
            break;
        case 4:
            hums[humsPos] = "e";
            break;
        case 5:
            hums[humsPos] = "f";
            break;
        case 6:
            hums[humsPos] = "g";
            break;
        case 7:
            hums[humsPos] = "h";
            break;
        case 8:
            hums[humsPos] = "j";
            break;
        case 9:
            hums[humsPos] = "k";
            break;
        case 10:
            hums[humsPos] = "l";
            break;
        default:
            hums[humsPos] = "m";
            break;
    }
    humsPos++;
}

void pausa ( HWND* hWnd )
{
    printf("\nClick to continue\n");
    while (1)
    {
		if (_kbhit()) {
			char c = _getch();
			InvalidateRect(*hWnd, NULL, TRUE);
			break;
		}
	}
}

double** randmm(int rows, int cols)
{
    double** matrix = (double**)malloc(rows * sizeof(double*));

    for (int i = 0; i < rows; i++)
        matrix[i] = (double*)malloc(cols * sizeof(double));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] =  2.0 / RAND_MAX * rand();
        }
    }

    return matrix;
}

double** mulmr(double num, double **mat, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mat[i][j] = mat[i][j] * num;

            if(mat[i][j] > 1.0)
            {
                mat[i][j] = 1;
            } else mat[i][j] = 0;
        }
    }

    return mat;
}

void drawGraph ( HDC hdc, double** matrix )
{
    void arrow(float fi, int px,int py){
            fi = 3.1416*(180.0 - fi)/180.0;
            int lx,ly,rx,ry;
            lx = px+15*cos(fi+0.3);
            rx = px+15*cos(fi-0.3);
            ly = py+15*sin(fi+0.3);
            ry = py+15*sin(fi-0.3);
            MoveToEx(hdc, lx, ly, NULL);
            LineTo(hdc, px, py);
            LineTo(hdc, rx, ry);
    }
    char *nn[numb] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b"};
    int dx = 16, dy = 16, dtx = 7;
    int i;
    HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
    HPEN current = CreatePen(PS_SOLID, 1, RGB(255, 250, 48));
    HPEN finished = CreatePen(PS_SOLID, 1, RGB(128, 255, 48));
    SelectObject(hdc, KPen);
    for (int i = 0; i < numb; i++)
            {
                for (int j = 0; j < numb; j++)
                {
                    if ( matrix[i][j] == 1 && visited[i]) {
                        MoveToEx(hdc, nx[i], ny[i], NULL);
                        if ( ( ( nx[i] == nx[j] ) && ( ( ny[i] - ny[j] == oneLen ) || ( ny[j] - ny[i] == oneLen ) ) ) != 1 && ( ( ny[i] == ny[j] ) && ( ( nx[i] - nx[j] == oneLen ) || ( nx[j] - nx[i] == oneLen ) ) ) != 1 && ( ( i == 0 && j == ( numb - 1 ) ) ||  ( j == 0 && i == ( numb - 1 ) ) ) != 1 ) {
                            if ( i == j ) {

                            }
                            else {
                                POINT pt[3];
                                pt[0].x = nx[i];
                                pt[0].y = ny[i];
                                pt[2].x = nx[j];
                                pt[2].y = ny[j];

                                if ( nx[i] == nx[j] ){

                                    switch ( i - j ) {
                                    case 2: case -2:
                                        if ( nx[i] == oneLen ) {
                                            pt[0].x -= 15;
                                            pt[2].x -= 15;
                                            pt[1].x = nx[i] - oneLen/2;
                                            if ( ny[i] > ny[j] ) {
                                                pt[1].y = ny[i] - oneLen;
                                                arrow(60, nx[j]-dx, ny[j]+dy);
                                            }
                                            else {
                                                pt[1].y = ny[i] + oneLen;
                                                arrow(-60, nx[j]-dx, ny[j]-5);
                                            }
                                        }
                                        else {
                                            pt[0].x += 15;
                                            pt[2].x += 15;
                                            pt[1].x = nx[i] + oneLen;
                                            if ( ny[i] > ny[j] ) {
                                                pt[1].y = ny[i] - oneLen;
                                                arrow(150, nx[j]+dx, ny[j]+dy);
                                            }
                                            else {
                                                pt[1].y = ny[i] + oneLen;
                                                arrow(-150, nx[j]+dx, ny[j]-5);
                                            }
                                        }
                                        Polyline(hdc,pt,3);
                                        break;
                                    default:
                                        LineTo( hdc, nx[j], ny[j] );
                                        if ( ny[i] > ny[j] ) {
                                            arrow(90,nx[j],ny[j]+dy);
                                        }
                                        else {
                                            arrow(-90,nx[j],ny[j]-dy);
                                        }
                                        break;
                                    }

                                }
                                else if ( ny[i] == ny[j] ) {

                                    if ( ny[i] == oneLen || ny[i] == oneLen*3 ) {
                                        pt[1].y = ny[i];
                                        pt[1].x = nx[i];
                                        switch ( nx[i] - nx[j] ) {
                                        case 180*2: case 180*(-2):
                                            if ( ny[i] == oneLen ) {
                                                pt[1].y -= oneLen/2;
                                                if ( nx[i] > nx[j] ) {
                                                    pt[1].x -= oneLen;
                                                    arrow(35,nx[j]+15,ny[j]+6);
                                                }
                                                else {
                                                    pt[1].x += oneLen;
                                                    arrow(-35,nx[j]-15,ny[j]+6);
                                                }
                                            }
                                            else {
                                                pt[1].y += oneLen/2;
                                                if ( nx[i] > nx[j] ) {
                                                    pt[1].x -= oneLen;
                                                    arrow(145,nx[j]+15,ny[j]+6);

                                                }
                                                else {
                                                    pt[1].x += oneLen;
                                                    arrow(-145,nx[j]-15,ny[j]+6);
                                                }
                                            }
                                            break;
                                        case 180*3: case 180*(-3):
                                            if ( nx[i] > nx[j] ) {
                                                pt[0].x += 15;
                                                pt[2].x -= 15;
                                            }
                                            else {
                                                pt[0].x -= 15;
                                                pt[2].x += 15;
                                            }
                                            if ( ny[i] == oneLen ){
                                                pt[1].y -= oneLen/4*2;
                                                if ( nx[i] > nx[j] ) {
                                                    pt[1].x -= oneLen*3/2;
                                                    arrow(-160,nx[j]+15,ny[j]-9);
                                                }
                                                else {
                                                    pt[1].x += oneLen*3/2;
                                                    arrow(160,nx[j]+15,ny[j]-9);
                                                }
                                            }
                                            else {
                                                pt[1].y += oneLen/4*3;
                                                if ( nx[i] > nx[j] ) {
                                                    pt[1].x -= oneLen*3/2;
                                                    arrow(155,nx[j]+9,ny[j]+11);
                                                }
                                                else {
                                                    pt[1].x += oneLen*3/2;
                                                    arrow(-155,nx[j]+9,ny[j]+11);
                                                }
                                            }
                                            break;
                                        case 180*4: case 180*(-4):
                                            if ( nx[i] > nx[j] ) {
                                                pt[0].x += 13;
                                                pt[2].x -= 13;
                                            }
                                            else {
                                                pt[0].x -= 13;
                                                pt[2].x += 13;
                                            }
                                            if ( ny[i] == oneLen ) {
                                                pt[0].y -= 5;
                                                pt[2].y -= 5;
                                                pt[1].y -= oneLen;
                                                if ( nx[i] > nx[j] ) {
                                                    pt[1].x -= oneLen*2;
                                                    arrow(-160,nx[j]+9,ny[j]-15);
                                                }
                                                else {
                                                    pt[1].x += oneLen*2;
                                                    arrow(160,nx[j]+9,ny[j]-15);
                                                }
                                            }
                                            else {
                                                pt[0].y += 5;
                                                pt[2].y += 5;
                                                pt[1].y += oneLen*5/4;
                                                if ( nx[i] > nx[j] ) {
                                                    pt[1].x -= oneLen*2;

                                                }
                                                else {
                                                    pt[1].x += oneLen*2;
                                                    arrow(40,nx[j]-5,ny[j]+15);
                                                }
                                            }
                                            break;
                                        }
                                        Polyline(hdc,pt,3);
                                    }
                                    else {
                                        LineTo( hdc, nx[j], ny[j] );
                                        if ( nx[i] > nx[j] ) {
                                            arrow(180,nx[j]+dx,ny[j]);
                                        }
                                        else {
                                            arrow(0,nx[j]-dx,ny[j]);
                                        }
                                    }

                                }
                                else {

                                    LineTo( hdc, nx[j], ny[j] );
                                    if ( matrix[j][i] == 1 ) {

                                        if ( i - j < 0 ) {
                                            pt[1].x = nx[i] + 20;
                                            pt[1].y = ny[i] - oneLen;
                                            LineTo( hdc, nx[j], ny[j] );
                                            arrow(70,nx[j]-8,ny[j]+dy);
                                            Polyline(hdc,pt,3);
                                            arrow(-100,nx[i]+1,ny[i]-dy);
                                        }

                                    }
                                    else{
                                        if ( ny[i] - ny[j] == oneLen*2 ||  ny[j] - ny[i] == oneLen*2 ) {
                                            switch ( nx[i]-nx[j] ) {
                                            case oneLen:
                                                if ( ny[j] > ny[i]) arrow(70,nx[j]+9,ny[j]-dy);
                                                else arrow(-70,nx[j]+9,ny[j]+dy);
                                                break;
                                            case -oneLen:
                                                if ( ny[j] > ny[i]) arrow(-70,nx[j]-9,ny[j]-dy);
                                                else arrow(70,nx[j]-9,ny[j]+dy);
                                                break;
                                            case oneLen*2:
                                                if ( ny[j] > ny[i]) arrow(-130,nx[j]+12,ny[j]-dy+5);
                                                else arrow(130,nx[j]+12,ny[j]+dy-5);
                                                break;
                                            case -oneLen*2:
                                                if ( ny[j] > ny[i]) arrow(-50,nx[j]-12,ny[j]-dy+5);
                                                else arrow(50,nx[j]-12,ny[j]+dy-5);
                                                break;
                                            case oneLen*3:
                                                if ( ny[j] > ny[i]) arrow(-140,nx[j]+15,ny[j]-dy+7);
                                                else arrow(140,nx[j]+15,ny[j]+dy-7);
                                                break;
                                            case -oneLen*3:
                                                if ( ny[j] > ny[i]) arrow(50,nx[j]-15,ny[j]-dy+7);
                                                else arrow(-50,nx[j]-15,ny[j]+dy-7);
                                                break;
                                            case oneLen*4:
                                                if ( ny[j] > ny[i]) arrow(-150,nx[j]+11,ny[j]-dy+2);
                                                else arrow(140,nx[j]+15,ny[j]+dy-7);
                                                break;
                                            case -oneLen*4:
                                                if ( ny[j] > ny[i]) arrow(30,nx[j]-11,ny[j]-dy+2);
                                                else arrow(-40,nx[j]-15,ny[j]+dy-7);
                                                break;
                                            }
                                        }
                                        else {

                                            if ( nx[i] - nx[j] == oneLen ) {
                                                arrow(-135,nx[j]+10,ny[j]-10);
                                            }
                                            else if ( nx[j] - nx[i] == oneLen ) {
                                                arrow(45,nx[j],ny[j]-10);
                                            }
                                            else if ( nx[i] - nx[j] == oneLen*3 ){
                                                if ( ny[i] > ny[j]) arrow(165,nx[j]+14,ny[j]+5);
                                                else arrow(-165,nx[j]+14,ny[j]-5);
                                            }

                                        }
                                    }
                                }
                            }
                        }
                        else {
                            LineTo( hdc, nx[j], ny[j] );

                            if ( matrix[j][i] == 1 ) {
                                if ( i - j > 0 ) {
                                    POINT pt[3];
                                    pt[0].x = nx[i];
                                    pt[0].y = ny[i];

                                    pt[2].x = nx[j];
                                    pt[2].y = ny[j];

                                    if ( nx[i] == nx[j] && ny[i] > ny[j] ) {
                                        arrow(90, nx[j], ny[j]+dy);
                                        pt[1].x = nx[i]-oneLen/4;
                                        pt[1].y = ny[i]-oneLen/2;
                                        arrow(60, nx[j]-7, ny[j]+dy);
                                    }
                                    else if ( nx[i] == nx[j] && ny[i] < ny[j] ) {
                                        arrow(-90, nx[j], ny[j]-dy);
                                        pt[1].x = nx[i]+oneLen/4;
                                        pt[1].y = ny[i]+oneLen/2;
                                        arrow(-60, nx[j]+7, ny[j]+dy);
                                    }
                                    else if ( nx[i] > nx[j] ) {
                                        arrow(180, nx[j]+dx, ny[j]);
                                        pt[1].x = nx[i]-oneLen/4;
                                        pt[1].y = ny[i]+oneLen/2;
                                        arrow(150, nx[j]+dx, ny[j]+7);
                                    }
                                    else {
                                        arrow(0, nx[j]-dx, ny[j]);
                                        pt[1].x = nx[i]+oneLen/4;
                                        pt[1].y = ny[i]+oneLen/2;
                                        arrow(-150, nx[j]+dx, ny[j]-7);
                                    }
                                    Polyline(hdc,pt,3);
                                }
                            }
                            else {
                                if ( nx[i] == nx[j] && ny[i] > ny[j] ) {
                                    arrow(90, nx[j], ny[j]+dy);
                                }
                                else if ( nx[i] == nx[j] && ny[i] < ny[j] ) {
                                    arrow(-90, nx[j], ny[j]-dy);
                                }
                                else if ( nx[i] > nx[j] ) {
                                     arrow(180, nx[j]+dx, ny[j]);
                                }
                                else {
                                    arrow(0, nx[j]-dx, ny[j]);
                                }
                            }

                        }
                    }
                }
            }

            for ( i = 0; i <= 10; i++ ){
            if ( !check && i == thisOne ) SelectObject(hdc, current);
            else if ( !check && visited[i] ) SelectObject(hdc, finished);
            else SelectObject(hdc, BPen);
              Ellipse ( hdc, nx[i]-dx, ny[i]-dy, nx[i]+dx, ny[i]+dy );
              if (!humsSwitch) TextOut ( hdc, nx[i]-dtx, ny[i]-dy/2, nn[i], 1 );
              else TextOut ( hdc, nx[i]-dtx, ny[i]-dy/2, hums[i], 1 );
            }
}

void printMatrix ( double** matrix, int rows, int cols ) {
    for ( int i = 0; i < rows; i++ ){
        for ( int j = 0; j < cols; j++ )
            printf("%.0f\t", matrix[i][j]);
        printf("\n");
    }
}

void generateMatrixes (  )
{
    for ( int i = 0; i < numb; i++ ) {
        if ( i == 0 ) {
            nx[i] = oneLen*3;
            ny[i] = oneLen;
        }
        else if ( i < 3) {
            nx[i] = nx[i-1] - oneLen;
            ny[i] = ny[i-1];
        }
        else if ( i < 5 ) {
            nx[i] = nx[i-1];
            ny[i] = ny[i-1] + oneLen;
        }
        else if ( i < 9 ){
            nx[i] = nx[i-1] + oneLen;
            ny[i] = ny[i-1];
        }
        else {
            nx[i] = nx[i-1];
            ny[i] = ny[i-1] - oneLen;
        }
    }
    srand(0412);
    double** T = randmm(numb, numb);
    double coef = 1.0 - 1*0.01 - 2*0.005 - 0.15;
    mat = mulmr(coef, T, numb, numb);
    dfs = randmm(numb, numb);
    bfs = randmm(numb, numb);
    printf("\nMatrix:\n");
    printMatrix ( mat, numb, numb );

}

void dfsfunc ( HWND hWnd, int needed ) {
    printf("checking %i\n",needed);
    visited[needed] = 1;
    thisOne = needed;
    humAdd( thisOne );
    pausa( hWnd );
    for ( int i = 0; i < numb; i++ )
        if ( mat[needed][i] && !visited[i] )
        {
            dfs[needed][i] = 1;
            dfsfunc(hWnd, i);
        }
}

void bfsfunc ( HWND hWnd, int needed ) {
    visited[needed] = 1;
    thisOne = needed;
    int queuePos = 0;
    int queu[numb] = {};
    for ( int i = 0; i < numb; i++ ) queu[i] = -1;
    queu[queuePos] = needed;
    visited[needed] = 1;
    int n, l;
    l = 0;
    while ( l < numb && queu[l] != -1 )
    {
        printf("checking %i\n",n);
        thisOne = n;
        humAdd( thisOne );
        n = queu[l];
        l++;
        pausa( hWnd );
        for ( int i = 0; i < numb; i++ )
            if ( mat[n][i] && !visited[i] )
            {
                queuePos++;
                queu[queuePos] = i;
                visited[i] = 1;
                bfs[n][i] = 1;
            }
    }

    for ( int i = 0; i < numb; i++ )
        if ( mat[needed][i] && !visited[i] )
        {
            dfs[needed][i] = 1;
            dfsfunc(hWnd, i);
        }
}

void checker ( HDC hdc )
{
    if ( !check ) drawGraph( hdc, mat );
    else if ( check == 1 ) drawGraph( hdc, dfs );
    else drawGraph( hdc, bfs );
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


DWORD WINAPI secondfun (LPVOID lpParam)                                                             //second
{
    generateMatrixes();
    for ( int i = 0; i < numb; i++ ) {
        visited[i] = 0;
        for ( int j = 0; j < numb; j++ ) {
            dfs[i][j] = 0;
            bfs[i][j] = 0;
        }
    }
    while ( TRUE )
    {
        thisOne = -1;
        for ( int i = 0; i < numb; i++ )
            if ( !visited[i] )
            {
                thisOne = i;
                break;
            }
        if ( thisOne == -1 ) break;
        dfsfunc ( lpParam, thisOne );
    }
    printf("\nDFS matrix:\n");
    printMatrix ( dfs, numb, numb );
    printf("\nSwitch to dfs graph\n");
    pausa( lpParam );
    check = 1;
    printf("\nSwitch to new numbers\n");
    pausa( lpParam );
    humsSwitch = 1;
    printf("\nStart bfs\n");
    pausa( lpParam );
    check = 0;
    humsSwitch = 0;
    humsPos = 0;
    for ( int i = 0; i < numb; i++ )
        visited[i] = 0;
    thisOne = -1;
    while ( TRUE )
    {
        thisOne = -1;
        for ( int i = 0; i < numb; i++ )
            if ( !visited[i] )
            {
                thisOne = i;
                break;
            }
        if ( thisOne == -1 ) break;
        bfsfunc ( lpParam, thisOne );
    }
    printf("\nBFS matrix:\n");
    printMatrix ( bfs, numb, numb );
    printf("\nSwitch to new numbers\n");
    pausa( lpParam );
    humsSwitch = 1;

}

//îáúÿâëÿåì ñòðîêó-èìÿ ïðîãðàììû
char ProgName[]="Lab 5";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w; //ñîçäà¸ì ýêçåìïëÿð ñòðóêòóðû WNDCLASS

    w.lpszClassName=ProgName; //èìÿ ïðîãðàììû - îáúÿâëåíî âûøå
    w.hInstance=hInstance; //èäåíòèôèêàòîð òåêóùåãî ïðèëîæåíèÿ
    w.lpfnWndProc=WndProc; //óêàçàòåëü íà ôóíêöèþ îêíà
    w.hCursor=LoadCursor(NULL, IDC_ARROW); //çàãðóæàåì êóðñîð
    w.hIcon=0; //èêîíêè ó íàñ íå áóäåò ïîêà
    w.lpszMenuName=0; //è ìåíþ ïîêà íå áóäåò
    w.hbrBackground = LTGRAY_BRUSH; //WHITE_BRUSH;// öâåò ôîíà îêíà
    w.style=CS_HREDRAW|CS_VREDRAW; //ñòèëü - ïåðåðèñîâûâàåìîå ïî õ è ïî ó
    w.cbClsExtra=0;
    w.cbWndExtra=0;

    if(!RegisterClass(&w))
        return 0;

   // HWND hWnd;
    //MSG lpMsg;

//Ñîçäàäèì îêíî â ïàìÿòè, çàïîëíèâ àðãóìåíòû CreateWindow
    hWnd=CreateWindow(ProgName, //Èìÿ ïðîãðàììû
        "Lab 5", //Çàãîëîâîê îêíà
        WS_OVERLAPPEDWINDOW, //Ñòèëü îêíà - ïåðåêðûâàþùååñÿ
        0, //ïîëîæåíèå îêíà íà ýêðàíå ïî õ
        0, //ïîëîæåíèå ïî ó
        1920, //øèðèíà
        1080, //âèñîòà
        (HWND)NULL, //èäåíòèôèêàòîð ðîäèòåëüñêîãî îêíà
        (HMENU)NULL, //èäåíòèôèêàòîð ìåíþ
        (HINSTANCE)hInstance, //èäåíòèôèêàòîð ýêçåìïëÿðà ïðîãðàììû
        (HINSTANCE)NULL); //îòñóòñòâèå äîïîëíèòåëüíûõ ïàðàìåòðîâ

//Âûâîäèì îêíî èç ïàìÿòè íà ýêðàí
    ShowWindow(hWnd, nCmdShow);

    DWORD dwThreadId = 1;

    HANDLE secpot;
    secpot = CreateThread(NULL, 0, secondfun, &hWnd, 0, &dwThreadId);


//Îáíîâèì ñîäåðæèìîå îêíà
 //   UpdateWindow(hWnd);

//Öèêë îäåðæàííÿ ïîâ³äîìëåíü

    while(GetMessage(&lpMsg, hWnd, 0, 0)) { //Ïîëó÷àåì ñîîáùåíèå èç î÷åðåäè
            TranslateMessage(&lpMsg); //Ïðåîáðàçóåò ñîîáùåíèÿ êëàâèø â ñèìâîëû
            DispatchMessage(&lpMsg); //Ïåðåäà¸ò ñîîáùåíèå ñîîòâåòñòâóþùåé ôóíêöèè îêíà
        }
    return(lpMsg.wParam);
    }

//Ôóíêöèÿ îêíà
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
                        WPARAM wParam, LPARAM lParam)
    {
    HDC hdc; //ñîçäà¸ì êîíòåêñò óñòðîéñòâà
    PAINTSTRUCT ps; //ñîçäà¸ì ýêçåìïëÿð ñòðóêòóðû ãðàôè÷åñêîãî âûâîäà



//Öèêë îáðàáîòêè ñîîáùåíèé
    switch(messg){
    //ñîîáùåíèå ðèñîâàíèÿ
        case WM_PAINT :

            hdc=BeginPaint(hWnd, &ps);
            checker ( hdc );
            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}
