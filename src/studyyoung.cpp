#define _CRT_SECURE_NO_WARNINGS
#pragma comment (lib, "libmySQL.lib")
#include <windows.h>  // Windows API 사용
#include <mysql.h>
#include "framework.h"
#include "studyyoung.h"
#include "resource.h"
#include <math.h>
#include <iostream>
#include <string>
#include <sstream>
#include <codecvt>
using namespace std;
#define BSIZE 40

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];
HBITMAP BP;
static int Quiz = 0,Interface = 0;
static int key[41] = { 
    1,3,2,3,1,2,3,3,2,3,
    2,1,3,1,2,3,1,3,1,2,
    2,1,3,2,2,1,2,3,2,3,
    2,1,3,1,2,3,1,1,3,2,
    2
};
static int lname_count = 0, lpassword_count= 0;
static int name_count = 0, password_count=0;
static wchar_t name_str[100];
static wchar_t password_str[100];
static wchar_t lname_str[100];
static wchar_t lpassword_str[100];

static int user_count = 0;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

string Convert_Str(wchar_t* str) {
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    wstring wideStr(str);
    return converter.to_bytes(wideStr);
}

//Class 영역

class UserDB {
public:
    int id;
    wchar_t* name;
    wchar_t* password;
    int step;
    string string_query;
    const char* sql_query;
    string string_query_u;
    const char* sql_query_u;
    BOOL login;
    ~UserDB();
    void Getstringquery();
    void Getsqlquery();
    void Getstringquery_u();
    void Getsqlquery_u();
};
UserDB::~UserDB() {
}
void UserDB::Getstringquery() {
        ostringstream ost_query;
        string string_name = Convert_Str(this->name);
        string string_password = Convert_Str(this->password);
        ost_query << "INSERT INTO quiz (name, password, step) VALUES ('" << string_name 
            << "', '" << string_password << "', " << this->step << ")";
        this->string_query = ost_query.str();
}
void UserDB::Getsqlquery() {
    this->sql_query = string_query.c_str();
}
void UserDB::Getstringquery_u() {
    ostringstream ost_query_u;
    ost_query_u << "UPDATE quiz SET step =" << this->step << " WHERE id =  " << this->id;
    this->string_query_u = ost_query_u.str();
}
void UserDB::Getsqlquery_u() {
    this->sql_query_u = string_query_u.c_str();
}

UserDB users[200];


//함수헤더영역


static void CinDB(UserDB* users);
void ColorRtgCoutText(HDC hdc, BOOL& a, int r, int g, int b, int x1, int y1, int x2, int y2, const wchar_t* str);
void RtgCoutText(HDC hdc, int x1, int y1, int x2, int y2, const wchar_t* str);
void RtgCoutText2(HDC hdc, int x1, int y1, int x2, int y2, int tx, int ty, const wchar_t* str);
static void Change_Interface_2F(BOOL& a, BOOL& b, BOOL& p1, BOOL& p2, BOOL& p3, int& Interface, static int& Quiz);
static void Puzzle_Check(BOOL& p1, BOOL& p2, BOOL& p3, int& Quiz);
void Paint_Quiz(HDC memdc, HDC hdc, HBITMAP Bit, int width, int height, BOOL p1, BOOL p2, BOOL p3, TCHAR* t1, TCHAR* t2, TCHAR* t3, TCHAR* t4);
void Update_User(UserDB* users,int N);
static void UpdateDB(UserDB* users,int N);
int login_user_id();
void CoutText2(const wchar_t* str1, HDC hdc, int x1, int y1, int x2, int y2);




//

void Clean_str(static wchar_t* str, static int& count) {
    for (int i = 0; i < 100; ++i) {
        
    }
}
BOOL Check_Str_Free(int& Interface,static int& count1, static int& count2) {
    if (count1 == 0 || count2 == 0) {
        Interface = 0;
        return TRUE;
    }
    else
        return FALSE;
}
static void CoutDB(UserDB* users, static int& user_count);
double LengthPts(int x1, int y1, int x2, int y2) {
    return(sqrt((float)(x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
BOOL InCircle(int x, int y, int mx, int my) {
    if (LengthPts(x, y, mx, my) < BSIZE) return TRUE;
    else return FALSE;
}
static class text_xy {
    int x1, y1, x2, y2;
};
void Clean_Str(static wchar_t* str, static int& count) {
    while (count > 0) {
        count--;
        str[count] = NULL;
    }
}
void Change_Bool_1(int mx, int my, int x1, int y1, int x2, int y2, BOOL& p1) {
    if (x1 < mx && mx < x2 && y1 < my && my < y2) {
        p1 = TRUE;
    }
}
void Change_Bool_2(int mx, int my, int x1, int y1, int x2, int y2, BOOL& p1, BOOL& p2) {
    if (x1 < mx && mx < x2 && y1 < my && my < y2) {
        p1 = TRUE;
        p2 = FALSE;
    }
}
void Change_Bool_3(int mx, int my, int x1, int y1, int x2, int y2, BOOL& p1, BOOL& p2, BOOL& p3) {
    if (x1 < mx && mx < x2 && y1 < my && my < y2) {
        if (p1 == TRUE)
            p1 = FALSE;
        else {
            p1 = TRUE;
        }
        p2 = FALSE;
        p3 = FALSE;
    }
}
static int Bool_Check_2(BOOL& a, BOOL& b) {
    int tmp = 0;
    if (a == TRUE) tmp = 1;
    if (b == TRUE) tmp = 2;
    a = FALSE;
    b = FALSE;
    return tmp;
}
static int Bool_Check_3(BOOL& a, BOOL& b, BOOL& c) {
    int tmp = 0;
    if (a == TRUE) tmp = 1;
    if (b == TRUE) tmp = 2;
    if (c == TRUE) tmp = 3;
    a = FALSE;
    b = FALSE;
    c = FALSE;
    return tmp;
}
void Register_User(wchar_t* str1, wchar_t* str2, UserDB* users) {
    int N = user_count;
    users[N].id = N;
    users[N].name = str1;
    users[N].password = str2;
    users[N].step = 0;
    users[N].Getstringquery();
    users[N].Getsqlquery();
}
void Check_User(wchar_t* str1, wchar_t* str2, UserDB* users,int& Quiz) {
    int i = 0;
    while (user_count > i) {
       
        if (wcscmp(str1, users[i].name) == 0) {
            if (wcscmp(str2, users[i].password) == 0) {
                users[i].login = TRUE;
                Quiz = users[i].step;
                Interface = 2;
                return;
            }
        }
        i++;
    }
}
void Update_User(UserDB* users, int N) {
    users[N].step = Quiz;
    users[N].Getstringquery_u();
    users[N].Getsqlquery_u();
    users[N].login = FALSE;
}
static void Change_Interface_B1(BOOL& a, BOOL& b, int& Interface, static wchar_t* str1, static wchar_t* str2,
    UserDB* users,static int& count1,static int& count2) {
    int select = Bool_Check_2(a, b);
    switch (select) {
    case 1: { //홈으로
        a = FALSE;
        b = FALSE;
        Clean_Str(str1, count1);
        Clean_Str(str2, count2);
        Interface = 0;
        break;
     }
    case 2: { //회원가입
        a = FALSE;
        b = FALSE;
        if (Check_Str_Free(Interface, count1, count2))
            break;
        else {
            Register_User(str1, str2, users);
            CinDB(users);
            Clean_Str(str1, count1);
            Clean_Str(str2, count2);
            MessageBox(NULL, L"회원가입을 축하합니다!!", L"알림", MB_ICONINFORMATION);
            Interface = 0;
            break;
        }
     }
    }
}
static void Change_Interface_0F(BOOL& a, BOOL& b,int& Interface) {
    int select = Bool_Check_2(a, b);
    switch (select) {
    case 1: { //로그인창 이동
        CoutDB(users,user_count);
        Interface = 1;
        break;
     }
    case 2: {//회원가입창 이동
        Interface = -1;
        break;
     }
    }       
}
static void Change_Interface_1F(BOOL& a, BOOL& b, int& Interface, static wchar_t* str1, 
    static wchar_t* str2, UserDB* users, static int& count1, static int& count2,int& Quiz) {
    int select = Bool_Check_2(a, b);
    switch (select) {
    case 1: { //홈으로
        Clean_Str(str1, count1);
        Clean_Str(str2, count2);
        a = FALSE;
        b = FALSE;
        Interface = 0;
        break;
    }
    case 2: {//로그인
        a = FALSE;
        b = FALSE;
        if (Check_Str_Free(Interface, count1, count2))
            break;
        else {
            Check_User(str1, str2, users,Quiz);
            MessageBox(NULL, L"로그인되었습니다!", L"알림", MB_ICONINFORMATION);
            Clean_Str(str1, count1);
            Clean_Str(str2, count2);
            break;
        }
    }
    }
}
static void Change_Interface_2F(BOOL& a, BOOL& b, BOOL& p1, BOOL& p2, BOOL& p3, int& Interface, 
    static int& Quiz) {
    int select = Bool_Check_2(a, b);
    switch (select) {
    case 1: { //옵션
        Interface = 3;
        break;
    }
    case 2: {//NEXT QUIZ
        Puzzle_Check(p1, p2, p3, Quiz);
        break;
     }
    }
}
static void Change_Interface_3F(BOOL& a, BOOL& b, int& Interface) {
    int select = Bool_Check_2(a, b);
    switch (select) {
    case 1: { //예

        int N = login_user_id();
        Update_User(users,N);
        UpdateDB(users,N);
        Interface = 0;
        break;
    }
    case 2: {//아니오
        Interface = 2;       
        break;
    }
    }
}
int login_user_id(){
    int i = 0;
    while (user_count > i) {
        if (users[i].login) {
            return i;
        }
        i++;
    }
}
static void Puzzle_Check(BOOL& p1,BOOL& p2,BOOL& p3,int& Quiz) {
        if (Bool_Check_3(p1, p2, p3) == key[Quiz]) {
            int i = 0;
            while(user_count>i){
                if (users[i].login == TRUE) {

                    users[i].step++;
                    p1 = FALSE, p2 = FALSE, p3 = FALSE;
                    Quiz++;
                    MessageBox(NULL, L"정답입니다!", L"알림", MB_ICONINFORMATION);
                    return;
                }
             i++;
            }
        }
        else {
            MessageBox(NULL, L"틀렸습니다!", L"알림", MB_ICONEXCLAMATION);
            p1 = FALSE, p2 = FALSE, p3 = FALSE;
        
        }
}
void Write_Str(WPARAM wParam, BOOL a, BOOL b, static int& acount, static int& bcount, static wchar_t* astr, static wchar_t* bstr) {
    if (a == TRUE) {
        if (wParam == VK_BACK && acount > 0) {
            acount--;
            astr[acount] = NULL;
        }
        else if (wParam != VK_BACK) {
            astr[acount++] = wParam;
            astr[acount] = NULL;
        }
    }
    if (b == TRUE) {
        if (wParam == VK_BACK && bcount > 0) {
            bcount--;
            bstr[bcount] = NULL;
        }
        else if (wParam != VK_BACK) {
            bstr[bcount++] = wParam;
            bstr[bcount] = NULL;
        }
    }

}
void Show_Step(HDC hdc, int x1, int y1, int x2, int y2) {
    char str[20];
    Rectangle(hdc, x1, y1, x2, y2);
    sprintf_s(str, sizeof(str), "%d", Quiz);
    TextOutA(hdc, 180,75 ,str , strlen(str));
}
void ColorRtg(HDC hdc ,BOOL pz,int r, int g, int b, int x1,int y1,int x2,int y2 ){
    if (pz == TRUE) {
        HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
        HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, brush);
        Rectangle(hdc, x1, y1, x2, y2);
        SelectObject(hdc, oldbrush);
        DeleteObject(brush);
    }
    else {
        Rectangle(hdc, x1, y1, x2, y2);
    }
}
void Paint_Quiz(HDC memdc, HDC hdc, HBITMAP Bit,int width,int height,BOOL p1, BOOL p2, BOOL p3, 
    const TCHAR* t1, const TCHAR* t2, const TCHAR* t3, const TCHAR* t4){
    SelectObject(memdc, BP);
    StretchBlt(hdc, 0, 0, 800*1.8, 450*1.6, memdc, 0, 0, 800,450, SRCCOPY);
    Show_Step(hdc, 154, 70, 224, 100);
    SelectObject(memdc, Bit);
    Rectangle(hdc, 154, 100, 940, 400);
    
    StretchBlt(hdc, 154 + (786 - width) / 2, 100, width, height, memdc, 0, 0, width, height, SRCCOPY);
    
    TextOut(hdc, 400, 50, _T("다음 퍼즐 중 Code가 작동하기 위한 퍼즐을 선택하세요"), 31);

    ColorRtgCoutText(hdc, p1, 255, 0, 0, 300, 450, 400, 500, t1);
    ColorRtgCoutText(hdc, p2, 255, 0, 0, 500, 450, 600, 500, t2);
    ColorRtgCoutText(hdc, p3, 255, 0, 0, 700, 450, 800, 500, t3);
    RtgCoutText2(hdc, 940, 100, 1400, 400, 945, 105, t4);
    RtgCoutText(hdc, 1320, 20, 1400, 80, L"종료");
    RtgCoutText(hdc, 1120, 430, 1230, 500, L"확인");
}

void Make_Quiz(const TCHAR* m1, const TCHAR* m2, const TCHAR* m3, const TCHAR* m4, HDC memdc, 
    HDC hdc, HBITMAP Bit, int width, int height, BOOL p1, BOOL p2, BOOL p3) {

    Paint_Quiz(memdc, hdc, Bit, width, height, p1, p2, p3, m1, m2, m3, m4);
}


   
wchar_t* wTrans_Data(const char* udata){
    int count = MultiByteToWideChar(CP_UTF8, 0, udata, -1, NULL, 0);
    wchar_t* wdata = new wchar_t[count];
     MultiByteToWideChar(CP_UTF8, 0, udata, -1, wdata, count);
     return wdata;
}
int iTrans_Data(const char* udata) {
    return atoi(udata);
}
void ReadDB(UserDB* users, MYSQL_ROW row,int user_count) {
    users[user_count].id = iTrans_Data(row[0]);
    users[user_count].name = wTrans_Data(row[1]);
    users[user_count].password = wTrans_Data(row[2]);
    users[user_count].step = iTrans_Data(row[3]);
}

static void CoutDB(UserDB* users, static int& user_count) {
    MYSQL* conn=mysql_init(NULL);

    const char* host = "localhost";     
    const char* user = "root";          
    const char* password = "121212";  
    const char* database = "quizinfo";   
    unsigned int port = 3306;

    mysql_real_connect(conn, host, user, password, database, port, NULL, 0);
    mysql_set_character_set(conn, "utf8");
        
    const char* query = "SELECT id, name, password, step FROM quiz";
    mysql_query(conn, query);
      
    MYSQL_RES* result = mysql_store_result(conn);
    int num_fields = mysql_num_fields(result);
    MYSQL_FIELD* fields = mysql_fetch_fields(result);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        ReadDB(users, row, user_count++);
    }
    mysql_free_result(result);
    mysql_close(conn);
}

static void CinDB(UserDB* users) {
    MYSQL* conn;
    conn = mysql_init(NULL);

    const char* host = "localhost";
    const char* user = "root";
    const char* password = "121212";
    const char* database = "quizinfo";
    unsigned int port = 3306;

    mysql_real_connect(conn, host, user, password, database, port, NULL, 0);
    mysql_set_character_set(conn, "utf8");
    if (users[user_count].name != NULL) {
        mysql_query(conn, users[user_count].sql_query);
        mysql_commit(conn);
    }
    mysql_close(conn);
}
static void UpdateDB(UserDB* users,int N) {
    MYSQL* conn;
    conn = mysql_init(NULL);

    const char* host = "localhost";
    const char* user = "root";
    const char* password = "121212";
    const char* database = "quizinfo";
    unsigned int port = 3306;

    mysql_real_connect(conn, host, user, password, database, port, NULL, 0);
    mysql_set_character_set(conn, "utf8");
    if (users[N].name != NULL) {
        mysql_query(conn, users[N].sql_query_u);
        mysql_commit(conn);
    }
    mysql_close(conn);
}
void CoutText(const wchar_t* str1, HDC hdc, int x1, int y1) {
    TextOutW(hdc,x1,y1, str1, wcslen(str1));
}
void RtgCoutText(HDC hdc, int x1, int y1, int x2, int y2, const wchar_t* str) {
    Rectangle(hdc, x1, y1, x2, y2);
    CoutText2(str, hdc, x1, y1, x2, y2);
}
void CoutText2(const wchar_t* str1,HDC hdc, int x1,int y1,int x2,int y2){
    RECT tt = { x1,y1,x2,y2 };
    DrawTextW(hdc, str1, wcslen(str1),&tt, DT_CENTER| DT_VCENTER | DT_SINGLELINE);
}
void RtgCoutText2(HDC hdc, int x1, int y1, int x2, int y2,int tx,int ty, const wchar_t* str){
    Rectangle(hdc, x1, y1, x2, y2);
    CoutText(str, hdc, tx, ty);
}
void ColorRtgCoutText(HDC hdc,BOOL& a ,int r, int g, int b, int x1, int y1, int x2, int y2, const wchar_t* str) {
    ColorRtg(hdc, a, r, g, b, x1, y1, x2, y2);
    CoutText2(str, hdc, x1, y1, x2, y2);
}

void Eraser_Char(WPARAM wParam, int& count, static wchar_t* str){
    if (wParam == (VK_BACK && count > 0)) count--;
    else str[count++] = wParam;
    str[count] = NULL;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_STUDYYOUNG, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    hInst = hInstance;
    


    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_STUDYYOUNG));
  
    

    
    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STUDYYOUNG));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_STUDYYOUNG);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc, memdc;
    PAINTSTRUCT ps;
    static HBITMAP Bit4, Bit5, Bit6, Bit7, Bit8, Bit9, Bit10, Bit11, Bit12, Bit13, PP1, PP2, PP3, PP4, QBit11, QBit12, QBit13, QBit14, QBit15,
        QBit16, QBit17, QBit18, QBit19, QBit20, QBit21, QBit22, QBit23, QBit24, QBit25, QBit26, QBit27, QBit28, QBit29, QBit30, QBit31, QBit32,
        QBit33, QBit34, QBit35, QBit36, QBit37, QBit38, QBit39, QBit40, QBit41; 
    static BOOL puzzle1 = FALSE, puzzle2 = FALSE, puzzle3 = FALSE, check = FALSE, option=FALSE;
    static BOOL BT1 = FALSE, BT2 = FALSE;
    static BOOL RG1 = FALSE, RG2 = FALSE, IN1 = FALSE, IN2 = FALSE;
    static BOOL WR1 = FALSE, WR2 = FALSE, MO1 = FALSE, MO2 = FALSE;
    static BOOL Y1 = FALSE, N1 = FALSE;
    int my, mx;


    switch (message)
    {
    case WM_CREATE: {
        CoutDB(users, user_count);
 
        Bit4 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP4));
        Bit5 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5));
        Bit6 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP6));
        Bit7 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP7));
        Bit8 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP8));
        Bit9 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP9));
        Bit10 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP10));
        Bit11 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP11));
        Bit12 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP12));
        Bit13 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP13));
        PP1 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP14));
        PP2 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP17));
        PP3 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP21));
        PP4 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP23));
        QBit11 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP24));
        QBit12 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP25));
        QBit13 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP26));
        QBit14 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP27));
        QBit15 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP28));
        QBit16 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP29));
        QBit17 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP30));
        QBit18 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP31));
        QBit19 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP32));
        QBit20 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP33));
        QBit21 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP34));
        QBit22 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP35));
        QBit23 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP36));
        QBit24 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP37));
        QBit25 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP38));
        QBit26 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP39));
        QBit27 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP40));
        QBit28 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP44));      
        QBit29 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP41));
        QBit30 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP42));
        QBit31 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP45));
        QBit32 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP71));
        QBit33 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP49));
        QBit34 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP52));
        QBit35 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP53));
        QBit36 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP61));
        QBit37 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP60));
        QBit38 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP59));
        QBit39 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP56));
        QBit40 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP57));
        QBit41 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP58));
        BP = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP68));
        

        break;
    }
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        memdc = CreateCompatibleDC(hdc);


        switch (Interface) {
        case -1: {
            SelectObject(memdc, PP2);
            StretchBlt(hdc, 0, 30, 696, 492, memdc, 0, 0, 696, 492, SRCCOPY);
            RtgCoutText2(hdc, 730, 130, 1130, 280, 755, 200, L"ID : ");
            RtgCoutText2(hdc, 730, 300, 1130, 450, 735, 370, L"PASSWORD : ");
            RtgCoutText(hdc, 450, 500, 650, 600, L"홈으로");
            RtgCoutText(hdc, 670, 500, 870, 600, L"등록");
            RtgCoutText(hdc, 730, 20, 1130, 100, L"ID와 PASSWORD를 등록해주세요!");
            TextOut(hdc, 780, 200, name_str, name_count);
            TextOut(hdc, 830, 370, password_str, password_count);

            break;
        }
        case 0: {
            RtgCoutText(hdc, 330, 0, 1020, 40, L"시작해보세요!!!    어디서도 할 수 없는 경험!!!");
            SelectObject(memdc, PP1);
            StretchBlt(hdc, 330, 50, 696, 492, memdc, 0, 0, 696, 492, SRCCOPY);
            RtgCoutText(hdc, 330, 530, 670, 660, L"로그인");
            RtgCoutText(hdc, 690, 530, 1030, 660, L"회원가입");
            break;
        }
        case 1: {
            SelectObject(memdc, PP3);
            StretchBlt(hdc, 0, 30, 800, 450, memdc, 0, 0, 800, 450, SRCCOPY);
            RtgCoutText2(hdc, 830, 130, 1230, 280, 855, 200, L"ID : ");
            RtgCoutText2(hdc, 830, 300, 1230, 450, 835, 370, L"PASSWORD : ");
            RtgCoutText(hdc, 820, 500, 1020, 600, L"홈으로");
            RtgCoutText(hdc, 1040, 500, 1240, 600, L"로그인");
            RtgCoutText(hdc, 830, 20, 1230, 100, L"로그인 해주세요!");
            TextOut(hdc, 880, 200, lname_str, lname_count);
            TextOut(hdc, 930, 370, lpassword_str, lpassword_count);
            break;
        }
        case 2: {
            switch (Quiz) { 
            case 0: {
                Make_Quiz(_T("main"), _T("if"), _T("cout"), _T("출력 :  "), memdc, hdc, Bit4, 
                    200, 150, puzzle1, puzzle2, puzzle3);
               break;
            }
            case 1: {
                Make_Quiz(_T("cin"), _T("for"), _T("cout"), _T("출력 : 안녕하세요! 프로그래밍의 세계의 오신걸 환영합니다! "), 
                    memdc, hdc, Bit5, 665, 146, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 2: {
                Make_Quiz(_T("double"), _T("int"), _T("char"), _T("출력 : 3  5"), memdc, hdc, Bit6, 
                    469, 144, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 3: {
                Make_Quiz(_T("int"), _T("string"), _T("char"), _T("alpabet 출력 : A "), memdc, hdc, Bit7, 542, 154, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 4: {
                Make_Quiz(_T("double"), _T("int"), _T("char"), _T("A 출력 : 61.8"), memdc, hdc, Bit8, 447, 144, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 5: {
                Make_Quiz(_T("true"), _T("bool"), _T("string"), _T("A 출력: FALSE B 출력: TRUE "), memdc, hdc, Bit9, 547, 156, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 6: {
                Make_Quiz(_T("bool"), _T("double"), _T("string"), _T("반가워요 "), memdc, hdc, Bit10, 534, 149, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 7: {
                Make_Quiz(_T("cout"), _T("for"), _T("cin"), _T("6 입력  6 "), memdc, hdc, Bit11, 442, 153, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 8: {
                Make_Quiz(_T("double"), _T("char"), _T("int"), _T("S 입력 출력: S"), memdc, hdc, Bit12, 402, 155, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 9: {
                Make_Quiz(_T("char"), _T("int"), _T("double"), _T("출력: 3.14"), memdc, hdc, Bit13, 457, 134, puzzle1, puzzle2, puzzle3);
                break;
            }
          
            case 10: { 
                Make_Quiz(_T("*"), _T("+"), _T("/"), _T("출력: 8"), memdc, hdc, QBit11, 554, 162, puzzle1, puzzle2, puzzle3);
                break;
            }

            case 11: {
                Make_Quiz(_T("*"), _T("+"), _T("/"), _T("출력: 15"), memdc, hdc, QBit12, 554, 153, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 12: {
                Make_Quiz(_T("/"), _T("+"), _T("-"), _T("출력: -2"), memdc, hdc, QBit13, 490, 158, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 13: {
                Make_Quiz(_T("/"), _T("+"), _T("*"), _T("출력: 0 "), memdc, hdc, QBit14, 462, 155, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 14: {
                Make_Quiz(_T("/"), _T("+"), _T("-"), _T("A 출력 : 9.4"), memdc, hdc, QBit15, 511, 151, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 15: {
                Make_Quiz(_T("char"), _T("double"), _T("string"), _T("출력: 안녕"), memdc, hdc, QBit16, 485, 164, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 16: {
                Make_Quiz(_T("bool"), _T("int"), _T("string"), _T("출력: 1"), memdc, hdc, QBit17, 489, 171, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 17: {
                Make_Quiz(_T("int"), _T("false"), _T("true"), _T("출력: 1 "), memdc, hdc, QBit18, 483, 164, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 18: {
                Make_Quiz(_T("*"), _T("=="), _T("+"), _T("출력: 6 "), memdc, hdc, QBit19, 450, 168, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 19: {
                Make_Quiz(_T("/"), _T("-"), _T("+"), _T("출력: -3"), memdc, hdc,QBit20, 472, 155, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 20: {
                Make_Quiz(_T("<"), _T(">"), _T("=="), _T("출력: 1"), memdc, hdc, QBit21, 477, 225, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 21: {
                Make_Quiz(_T("if"), _T("bool"), _T("for"), _T("출력: 1"), memdc, hdc, QBit22, 511, 214, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 22: {
                Make_Quiz(_T("double"), _T("true"), _T("false"), _T("출력: 0"), memdc, hdc, QBit23, 459, 222, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 23: {
                Make_Quiz(_T("double"), _T("else"), _T("int"), _T("출력: 1  "), memdc, hdc, QBit24, 474, 255, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 24: {
                Make_Quiz(_T("6"), _T("4"), _T("5"), _T("출력: 1"), memdc, hdc, QBit25, 460, 257, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 25: {
                Make_Quiz(_T("=="), _T("!="), _T(">"), _T("출력: 1"), memdc, hdc, QBit26, 492, 234, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 26: {
                Make_Quiz(_T("=="), _T("!="), _T("+"), _T("출력: 1 "), memdc, hdc, QBit27, 470, 237, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 27: {
                Make_Quiz(_T(">"), _T("1"), _T("<"), _T("출력: 1 "), memdc, hdc, QBit28, 438, 200, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 28: {
                Make_Quiz(_T("if"), _T("switch"), _T("case"), _T("출력: 1"), memdc, hdc, QBit29, 439, 273, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 29: {
                Make_Quiz(_T("if"), _T("switch"), _T("case"), _T("출력: 4"), memdc, hdc, QBit30, 436, 278, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 30: {
                Make_Quiz(_T("0"), _T("1"), _T("2"), _T("출력: 8"), memdc, hdc, QBit31, 426, 313, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 31: {
                Make_Quiz(_T("0"), _T("1"), _T("2"), _T("출력: 6"), memdc, hdc, QBit32, 471, 387, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 32: {
                Make_Quiz(_T("--"), _T("-+"), _T("++"), _T("출력: 6"), memdc, hdc, QBit33, 427 , 145, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 33: {
                Make_Quiz(_T("for"), _T("if"), _T("switch"), _T("출력:안녕 안녕 안녕"), memdc, hdc, QBit34, 365, 139, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 34: {
                Make_Quiz(_T("1"), _T("2"), _T("3"), _T("맑은 날씨 맑은 날씨"), memdc, hdc, QBit35, 385, 146, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 35: {
                Make_Quiz(_T("4"), _T("8"), _T("7"), _T("출력: 12"), memdc, hdc, QBit36, 398, 155, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 36: {
                Make_Quiz(_T("a[5]"), _T("a[3]"), _T("a[4]"), _T("출력: "), memdc, hdc, QBit37, 385, 119, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 37: {
                Make_Quiz(_T("0"), _T("1"), _T("2"), _T("출력: 6"), memdc, hdc, QBit38, 307, 126, puzzle1, puzzle2, puzzle3);
                break;
            }
            case 38: {
                Make_Quiz(_T("2"), _T("3"), _T("4"), _T("출력: 10"), memdc, hdc, QBit39, 456, 152, puzzle1, puzzle2, puzzle3);
                break;
             }
            case 39: {
                Make_Quiz(_T("switch"), _T("while"), _T("for"), _T("출력: 1 2 3 4 5"), memdc, hdc, QBit40, 463, 164, puzzle1, puzzle2, puzzle3);
                break;
             }
            case 40: {
                Make_Quiz(_T("6"), _T("7"), _T("8"), _T("출력: 28"), memdc, hdc, QBit41, 422, 205, puzzle1, puzzle2, puzzle3);
                break;
             }
            case 41: {
                SelectObject(memdc, BP);
                StretchBlt(hdc, 0, 0, 800 * 1.8, 450 * 1.6, memdc, 0, 0, 800, 450, SRCCOPY);
                RtgCoutText(hdc, 500, 200, 800, 300, L"모든 퍼즐을 맞추셨습니다!!");
                RtgCoutText(hdc, 1320, 20, 1400, 80, L"종료");
          
                break;
             }
            }
            break;
        }
        case 3: {
            SelectObject(memdc, PP4);
            StretchBlt(hdc, 0, 0, 800*2, 450*2, memdc, 0, 0, 800, 450, SRCCOPY);
            RtgCoutText(hdc, 530, 120, 980, 200, L"정말 종료하실건가요?");
            RtgCoutText(hdc, 530, 250, 730, 400, L"예");
            RtgCoutText(hdc, 780, 250, 980, 400, L"아니오");
            break;
        }
     


        }

        DeleteDC(memdc);
        EndPaint(hWnd, &ps);

        break;
    }
    case WM_KEYUP: {
        break;
    }
    case WM_CHAR: {
        hdc = GetDC(hWnd);
        switch (Interface) {
        case -1: {
            Write_Str(wParam, IN1, IN2, name_count, password_count, name_str, password_str);
            break;
         }
        case 1:{
            Write_Str(wParam, WR1, WR2, lname_count, lpassword_count, lname_str, lpassword_str);
            break;
         }
        }
        InvalidateRgn(hWnd, NULL, TRUE);
        ReleaseDC(hWnd, hdc);
        break;
    }
    case WM_TIMER: {
        break;
    }
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }

        break;
    }
    case WM_LBUTTONDOWN: {
        mx = LOWORD(lParam);
        my = HIWORD(lParam);


        switch (Interface) {
        case -1: {
            Change_Bool_2(mx, my, 730, 130, 1130, 280, IN1, IN2);
            Change_Bool_2(mx, my, 730, 300, 1130, 450, IN2, IN1);
            Change_Bool_2(mx, my, 450, 500, 650, 600, RG1, RG2);
            Change_Bool_2(mx, my, 670, 500, 870, 600, RG2, RG1);
            Change_Interface_B1(RG1, RG2, Interface, name_str, password_str, users, name_count, password_count);
            InvalidateRgn(hWnd, NULL, TRUE);
            break;
         }
        case 0: {
            Change_Bool_2(mx, my, 330, 530, 670, 660, BT1, BT2);
            Change_Bool_2(mx, my, 690, 530, 1030, 660, BT2, BT1);
            Change_Interface_0F(BT1, BT2, Interface);
            InvalidateRgn(hWnd, NULL, TRUE);
            break;
         }
        case 1: {
            Change_Bool_2(mx, my, 830, 130, 1230, 280, WR1, WR2);
            Change_Bool_2(mx, my, 830, 300, 1230, 450, WR2, WR1);
            Change_Bool_2(mx, my, 800, 500, 1000, 600, MO1, MO2);
            Change_Bool_2(mx, my, 1040, 500, 1240, 600, MO2, MO1);
            Change_Interface_1F(MO1, MO2, Interface, lname_str, lpassword_str, users, lname_count, 
                lpassword_count,Quiz);
            InvalidateRgn(hWnd, NULL, TRUE);
            break;
         }
        case 2: {
            Change_Bool_3(mx, my, 300, 450, 400, 500, puzzle1, puzzle2, puzzle3);
            Change_Bool_3(mx, my, 500, 450, 600, 500, puzzle2, puzzle1, puzzle3);
            Change_Bool_3(mx, my, 700, 450, 800, 500, puzzle3, puzzle1, puzzle2);
            Change_Bool_2(mx, my, 1120, 430, 1230, 500, check, option);
            Change_Bool_2(mx, my, 1320, 20, 1380, 80, option,check);
            Change_Interface_2F(option, check, puzzle1, puzzle2, puzzle3, Interface, Quiz);
            InvalidateRgn(hWnd, NULL, TRUE);
            break;
         }
        case 3: {
            Change_Bool_2(mx, my, 530, 250, 730, 400, Y1, N1);
            Change_Bool_2(mx, my, 780, 250, 980, 400, N1, Y1);
            Change_Interface_3F(Y1, N1, Interface);
            InvalidateRgn(hWnd, NULL, TRUE);
            break;
         }
      
        }


        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);

        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

   


// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
