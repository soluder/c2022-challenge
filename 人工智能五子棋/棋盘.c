#include <windows.h>
#include<windowsx.h>
#include<tchar.h>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
int XPos, YPos;
int* AI(int pawn[320][320],int X,int Y);
int evaluate(int pawn[320][320], int xPos, int yPos);
int check(int pawn[320][320]);
int pawn[320][320];


LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wndclass;
    TCHAR szAppName[] = TEXT("人工智障五子棋");
    TCHAR szClassName[] = TEXT("wangzai666");
    HWND hwnd;
    MSG msg;

    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WindowProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szClassName;
    wndclass.hIconSm = NULL;
    RegisterClassEx(&wndclass);


    hwnd = CreateWindowEx(0, szClassName, szAppName, WS_OVERLAPPEDWINDOW, 100, 100, 600, 600, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    for (int i = 0; i < 320; i++)
    {
        for (int j = 0; j < 320; j++)
        {
            pawn[i][j] = 0;
        }
    }
     

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int breakcount = 0;
    static int X=0,Y=0;
    static int testcount=0;
    static int flag=-1;
    int flag2=0;
    static int xcount=0, ycount=0;
    HDC hdc;
    HFONT  hFont;
    PAINTSTRUCT ps;
    RECT rectboard,rectregret,rectrestart,rectadmitdefeat,rectround;
    COLORREF color;
    int width = 20;
    int xPos, yPos;
    int* AIresult=NULL;
    int left = 20;
    int right = 320;
    int bottom = 320;
    int top = 20;
    //设置棋盘基准点
    rectboard.left = 20;
    rectboard.right = 300;
    rectboard.bottom = 300;
    rectboard.top = 20;
    rectregret.left = 420;
    rectregret.top = 100;
     rectregret.right = 520;
    rectregret.bottom = 150;
    rectadmitdefeat.left = 420;
    rectadmitdefeat.top = 150;
    rectadmitdefeat.right = 520;
    rectadmitdefeat.bottom = 200;
    rectrestart.left = 420;
    rectrestart.top = 200;
    rectrestart.right = 520;
    rectrestart.bottom = 250;

    



    switch (uMsg)
    {
        

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        SetTextAlign(hdc, GetTextAlign(hdc) & (~TA_CENTER));
        color = RGB(0, 0, 255);
       //绘制横线
        for (int i = rectboard.top; i <= rectboard.bottom; i += width)
        {
            MoveToEx(hdc, rectboard.left, i, NULL);
            LineTo(hdc, rectboard.right, i);
        }
        for (int i = rectboard.left; i <= rectboard.right; i += width)
        {
            MoveToEx(hdc, i, rectboard.top, NULL);
            LineTo(hdc, i, rectboard.bottom);
        }
        TextOut(hdc,18,4,TEXT("1"),1 );
        TextOut(hdc,38,4 , TEXT("2"),1 );
        TextOut(hdc,58 ,4 , TEXT("3"), 1);
        TextOut(hdc, 78,4 , TEXT("4"),1 );
        TextOut(hdc, 98, 4, TEXT("5"), 1);
        TextOut(hdc, 118, 4, TEXT("6"), 1);
        TextOut(hdc, 138,4 , TEXT("7"), 1);
        TextOut(hdc, 158, 4, TEXT("8"), 1);
        TextOut(hdc, 178, 4, TEXT("9"), 1);
        TextOut(hdc, 194, 4, TEXT("10"), 2);
        TextOut(hdc, 214, 4, TEXT("11"), 2);
        TextOut(hdc, 234, 4, TEXT("12"), 2);
        TextOut(hdc, 254, 4, TEXT("13"), 2);
        TextOut(hdc, 274, 4, TEXT("14"), 2);
        TextOut(hdc, 294, 4, TEXT("15"), 2);
        TextOut(hdc,9,32 , TEXT("2"),1);
        TextOut(hdc,9 ,52 , TEXT("3"),1 );
        TextOut(hdc, 9, 72, TEXT("4"), 1);
        TextOut(hdc,9 ,92 , TEXT("5"),1 );
        TextOut(hdc,9,112 , TEXT("6"), 1);
        TextOut(hdc,9,132 , TEXT("7"), 1);
        TextOut(hdc,9,152 , TEXT("8"), 1);
        TextOut(hdc,9,172 , TEXT("9"), 1);
        TextOut(hdc,4 ,192, TEXT("10"),2 );
        TextOut(hdc,4,212 , TEXT("11"), 2);
        TextOut(hdc,4,232 , TEXT("12"), 2);
        TextOut(hdc,4,252 , TEXT("13"), 2);
        TextOut(hdc,4,272 , TEXT("14"), 2);
        TextOut(hdc,4,292 , TEXT("15"), 2);
        
       
      


        //绘制回合数
        Rectangle(hdc, 400, 10, 580, 50);
        MoveToEx(hdc, 530, 10, NULL);
        LineTo(hdc, 530, 50);
        Rectangle(hdc, 0, 400, 600, 590);
        //绘制悔棋
        Rectangle(hdc, rectregret.left, rectregret.top, rectregret.right, rectregret.bottom);
        //绘制认输
        Rectangle(hdc, rectadmitdefeat.left, rectadmitdefeat.top, rectadmitdefeat.right, rectadmitdefeat.bottom);
        //绘制重开
        Rectangle(hdc, rectrestart.left, rectrestart.top, rectrestart.right, rectrestart.bottom);


            EndPaint(hwnd, &ps);
    //下棋
    case WM_LBUTTONDOWN:
        hdc = GetDC(hwnd);
        xPos = GET_X_LPARAM(lParam);
        yPos = GET_Y_LPARAM(lParam); 
           for (int i = rectboard.left; i <= rectboard.right; i += width)
            {
                for (int j = rectboard.top; j <= rectboard.bottom; j += width)
                {
                    if (xPos <= i + 6 && xPos >= i - 6 && yPos <= j + 6 && yPos >= j - 6)
                    {
                        if (pawn[i][j] != 1 && pawn[i][j] != -1)
                        {
                            pawn[i][j] = -1;
                            X = i;
                            Y = j;
                            Ellipse(hdc, i - 10, j - 10, i + 10, j + 10);
                            breakcount++;
                            break;
                        }
                    }
                }
                if (breakcount)
                {
                    break;
                }
            }
           if (breakcount)
           {
               int i, j;
               AIresult = AI(pawn, X, Y);
               i = *AIresult;
               j = *(AIresult + 1);
               pawn[i][j] = 1;
               SelectObject(hdc, GetStockObject(BLACK_BRUSH));
               Ellipse(hdc, i - 10, j - 10, i + 10, j + 10);
           }
            ReleaseDC(hwnd, hdc);
            flag2 = check(pawn);


            if (flag2 == 1) {
                MessageBox(NULL, TEXT("电脑获胜"), TEXT("再接再厉"), MB_OK);
            }
            else if (flag2 == -1)
            {
                MessageBox(NULL, TEXT("玩家获胜"), TEXT("再接再厉"), MB_OK);

            }
        
            


        
    return 0;


    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
