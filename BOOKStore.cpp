#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <string>
#include <iomanip>
using namespace std;
#import "c:\\Program Files\\Common Files\\System\\ADO\\msado15.dll" no_namespace rename("EOF", "EndOfFile")

_ConnectionPtr Conn;
int CurrentUser;

void Main_Menu();//显示主菜单
void User_Menu();//显示用户菜单
void Controler_Menu();//显示管理员菜单
void User_Borrow_Book();//用户 借书
void User_Return_Book();//用户 还书
void User_Search_Book();//用户 查询书
void User_Search_Self_Book();//用户 查询自己的借阅记录
void Controler_Add_Book();//管理员 添加书
void Controler_Delete_Book();//管理员 删除书
void Controler_Modify_Book();//管理员 修改书
void Controler_User_Search_Book();//管理员 查询某用户借书状态
void Controler_Search_All();//管理员 查询图书馆图书状态

void enterUserID() {
    cout << "请输入用户ID:";
    int inputuserID;
    cin >> inputuserID;
    CurrentUser = inputuserID;
}    
//输入用户ID
int main() {

    CurrentUser = 1;


    setlocale(LC_ALL, "chs");
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    try {
        _bstr_t ConnStr("Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=BOOK_STORE");

        _ConnectionPtr Conne(__uuidof(Connection));
        Conn = Conne;

        Conn->Open(
            ConnStr,"","",(long)0);
    }

    catch (_com_error& err) {
        wprintf(L"The application throws the error: %s\n", (wchar_t*)err.ErrorMessage());
        wprintf(L"Description = %s\n", (wchar_t*)err.Description());
    }

    int choice_1;
    int choice_2;
    do {
        Main_Menu();
        cin >> choice_1;
        switch (choice_1)
        {
        case 1:
        {
            enterUserID();
            User_Menu();
            cin >> choice_2;
            switch (choice_2)
            {
            case 1:
            {
                User_Borrow_Book();
                break;
            }
            case 2:
            {
                User_Return_Book();
                break;
            }
            case 3:
            {
                User_Search_Book();
                break;
            }
            case 4:
            {
                User_Search_Self_Book();
                break;
            }

            default:
            {
                break;
            }
            }
        }
        break;
        case 2:
        {
            Controler_Menu();
            cin >> choice_2;
            switch (choice_2)
            {
            case 1:
            {
                Controler_Add_Book();
                break;
            }
            case 2:
            {
                Controler_Delete_Book();
                break;
            }
            case 3:
            {
                Controler_Modify_Book();
                break;
            }
            case 4:
            {
                User_Search_Book();
                break;
            }
            case 5:
            {
                Controler_User_Search_Book();
                break;
            }
            case 6:
            {
                Controler_Search_All();
                break;
            }
            default:
            {
                break;
            }
            }
            break;
        }
        case 3:
        {
            cout << "欢迎下次使用!" << endl;
            break;
        }
        default:
        {
            break;
        }
        }
    } while (choice_1 != 3);

    CoUninitialize();
    return 0;
}
//主函数
void Main_Menu() {
    cout << "**********************************" << endl;
    cout << "*******欢迎进入图书管理系统*******" << endl;
    cout << "1. 用户" << endl;
    cout << "2. 管理员" << endl;
    cout << "3. 退出" << endl;
    cout << "输入你的选择: " << endl;
    cout << "**********************************" << endl;
}
//显示主菜单
void User_Menu() {
    cout << "**********************************" << endl;
    cout << "********欢迎进入用户系统**********" << endl;
    cout << "1. 借阅书籍" << endl;
    cout << "2. 归还书籍" << endl;
    cout << "3. 查找书籍" << endl;
    cout << "4. 查询自己借阅信息" << endl;
    cout << "输入你的选择: " << endl;
    cout << "**********************************" << endl;
}
//显示用户菜单
void Controler_Menu() {
    cout << "**********************************" << endl;
    cout << "********欢迎进入管理员系统********" << endl;
    cout << "1. 添加书籍" << endl;
    cout << "2. 删除书籍" << endl;
    cout << "3. 修改书籍" << endl;
    cout << "4. 查找书籍" << endl;
    cout << "5. 查找书籍借阅信息" << endl;
    cout << "6. 书籍信息" << endl;
    cout << "输入你的选择: " << endl;
    cout << "**********************************" << endl;

}
//显示管理员菜单
void User_Borrow_Book() {
    cout << "输入要借阅的书籍ID: ";
    int BookID;
    cin >> BookID;
    string Borrowing_Date;
    string Return_Date;
    cout << "输入借阅时间：";
    cin >> Borrowing_Date;
    cout << "输入预计归还时间：";
    cin >> Return_Date;

    try {
        _CommandPtr CommandObj(__uuidof(Command));
        CommandObj->ActiveConnection = Conn;

        CommandObj->CommandText = "INSERT INTO Borrow (UserID, BookID, BorrowDate, ReturnDate, Overtime) VALUES (?, ?, ?, ?, 0); UPDATE Books SET Copies=Copies-1 WHERE BookID = ?;";
        CommandObj->CommandType = adCmdText;

        _ParameterPtr ParameterObj1 = CommandObj->CreateParameter("UserID", adInteger, adParamInput, sizeof(int), CurrentUser);
        _ParameterPtr ParameterObj2 = CommandObj->CreateParameter("BookID", adInteger, adParamInput, sizeof(int), BookID);
        _ParameterPtr ParameterObj3 = CommandObj->CreateParameter("BorrowDate", adVarChar, adParamInput, 50, Borrowing_Date.c_str()); 
        _ParameterPtr ParameterObj4 = CommandObj->CreateParameter("ReturnDate", adVarChar, adParamInput, 50, Return_Date.c_str()); 
        _ParameterPtr ParameterObj5 = CommandObj->CreateParameter("BookID2", adInteger, adParamInput, sizeof(int), BookID);

        CommandObj->Parameters->Append(ParameterObj1);
        CommandObj->Parameters->Append(ParameterObj2);
        CommandObj->Parameters->Append(ParameterObj3);
        CommandObj->Parameters->Append(ParameterObj4);
        CommandObj->Parameters->Append(ParameterObj5);

 

        _RecordsetPtr RecordsetObj = 
            CommandObj->Execute(
                NULL,
                NULL, 
                long(0));
        cout << "操作成功." << endl;
    }

    catch (_com_error& err) {
        wprintf(L"The application throws the error: %s\n", (wchar_t*)err.ErrorMessage());
        wprintf(L"Description = %s\n", (wchar_t*)err.Description());
    }
}
//用户 借书
void User_Return_Book() {
    cout << "输入归还书籍ID: ";
    int BorrowingID;
    cin >> BorrowingID;

    try {

        _CommandPtr CommandObj(__uuidof(Command));
        CommandObj->ActiveConnection = Conn;
        CommandObj->CommandText =
            "UPDATE Borrow SET ReturnDate = GETDATE(), Overtime = 1 WHERE BorrowingID = ?;""UPDATE Books SET Copies = Copies + 1 WHERE BookID = (SELECT BookID FROM Borrow WHERE BorrowingID = ?);";
        CommandObj->CommandType = adCmdText;

     
        _ParameterPtr ParameterObj1 = 
            CommandObj->CreateParameter("BorrowingID", adInteger, adParamInput, sizeof(int), BorrowingID);
        _ParameterPtr ParameterObj2 =
            CommandObj->CreateParameter("BorrowingID", adInteger, adParamInput, sizeof(int), BorrowingID);

        CommandObj->Parameters->Append(ParameterObj1);
        CommandObj->Parameters->Append(ParameterObj2);

   
        _RecordsetPtr RecordsetObj = 
            CommandObj->Execute(
                NULL, 
                NULL, 
                long(0));

        cout << "操作成功." << endl;
    }

    catch (_com_error& err) {
        wprintf(L"The application throws the error: %s\n", (wchar_t*)err.ErrorMessage());
        wprintf(L"Description = %s\n", (wchar_t*)err.Description());
    }
}
//用户 还书
void User_Search_Book() {
    cout << "输入需要查询书籍的书名: ";
    string title;
    cin >> title;
    try {

        _CommandPtr CommandObj(__uuidof(Command));
        CommandObj->ActiveConnection = Conn;
        CommandObj->CommandText = "SELECT * FROM Books WHERE Title LIKE ? + '%'";
        CommandObj->CommandType = adCmdText;


        _ParameterPtr ParameterObj1 = 
            CommandObj->CreateParameter("TitlePrefix", adVarChar, adParamInput, 255, _bstr_t(data(title)));

        CommandObj->Parameters->Append(ParameterObj1);


        _RecordsetPtr RecordsetObj = 
            CommandObj->Execute(
                NULL,
                NULL, 
                adCmdText);

  
        cout << "BookID Title       Author          Publisher       Pubdate        Price    Copies" << endl;
        cout << "----------------------------------------------------------------------------------------" << endl;


        while (!RecordsetObj->EndOfFile) {

            int bookID = RecordsetObj->Fields->GetItem("BookID")->Value.intVal;
            string title = (const char*)_bstr_t(RecordsetObj->Fields->GetItem("Title")->Value.bstrVal);

            string author = (const char*)_bstr_t(RecordsetObj->Fields->GetItem("Author")->Value.bstrVal);

            string publisher = (const char*)_bstr_t(RecordsetObj->Fields->GetItem("Publisher")->Value.bstrVal);

            string Pubdate = (const char*)_bstr_t(RecordsetObj->Fields->GetItem("Pubdate")->Value.bstrVal);

            int Copies = RecordsetObj->Fields->GetItem("Copies")->Value.intVal;

            _variant_t variantValue = RecordsetObj->Fields->GetItem("Price")->Value;

            double price = static_cast<double>(variantValue);

            cout << left << setw(7) << bookID;
            cout << left << setw(12) << title;
            cout << left << setw(16) << author;
            cout << left << setw(16) << publisher;
            cout << left << setw(15) << Pubdate;
            cout << right << setw(6) << price;
            cout << right << setw(4) << Copies;
            cout << endl;

            RecordsetObj->MoveNext();
        }
    }


    catch (_com_error& err) 
    {
        wprintf(L"The application throws the error: %s\n", (wchar_t*)err.ErrorMessage());
        wprintf(L"Description = %s\n", (wchar_t*)err.Description());
    }
}
//用户 查询书
void User_Search_Self_Book() {
    try {

        _CommandPtr CommandObj(__uuidof(Command));
        CommandObj->ActiveConnection = Conn;
        CommandObj->CommandText = "select * from Borrow where UserID = ?";
        CommandObj->CommandType = adCmdText;

     
        _ParameterPtr ParameterObj1 = 
            CommandObj->CreateParameter("UserID", adVarChar, adParamInput, sizeof(int), CurrentUser);
        CommandObj->Parameters->Append(ParameterObj1);

   
        _RecordsetPtr RecordsetObj = 
            CommandObj->Execute(NULL, NULL, adCmdText);


        cout << "BorrowingID BookID BorrowDate ReturnDate Overtime" << endl;
        cout << "---------------------------------------------------" << endl;


        while (!RecordsetObj->EndOfFile) {
            
            int borrowingID = RecordsetObj->Fields->GetItem("BorrowingID")->Value.intVal;

            int bookID = RecordsetObj->Fields->GetItem("BookID")->Value.intVal;

            string borrowDate = (const char*)_bstr_t(RecordsetObj->Fields->GetItem("BorrowDate")->Value.bstrVal);

            string returnDate = (const char*)_bstr_t(RecordsetObj->Fields->GetItem("ReturnDate")->Value.bstrVal);

            _variant_t variantValue = RecordsetObj->Fields->GetItem("Overtime")->Value;

            bool Overtime = static_cast<bool>(variantValue);

    
            cout << left << setw(12) << borrowingID;
            cout << left << setw(7) << bookID;
            cout << left << setw(11) << borrowDate;
            cout << left << setw(11) << returnDate;
            cout << right << setw(2) << Overtime;
            cout << endl;

            RecordsetObj->MoveNext();
        }
    }
    catch (_com_error& err) {
        wprintf(L"The application throws the error: %s\n", (wchar_t*)err.ErrorMessage());
        wprintf(L"Description = %s\n", (wchar_t*)err.Description());
    }
}
//用户 查询自己的借阅记录


void Controler_Add_Book() {
    cout << "输入添加书籍的书名: ";
    string Title;
    cin >> Title;

    cout << "输入添加书籍的作者: ";
    string Author;
    cin >> Author;

    cout << "输入添加书籍的出版商: ";
    string Publisher;
    cin >> Publisher;

    cout << "输入添加书籍的出版时间: ";
    string Pubdate;
    cin >> Pubdate;

    cout << "输入添加书籍的价格: ";
    float Price;
    cin >> Price;

    try {
  
        _CommandPtr CommandObj(__uuidof(Command));
        CommandObj->ActiveConnection = Conn;
        CommandObj->CommandText = "INSERT INTO Books (Title, Author, Publisher, Pubdate, Price) VALUES(?, ?, ?, ?, ?)";
        CommandObj->CommandType = adCmdText;

        _ParameterPtr ParameterObj1 =
            CommandObj->CreateParameter("Title", adVarChar, adParamInput, 255, _bstr_t(data(Title)));
        _ParameterPtr ParameterObj2 =
            CommandObj->CreateParameter("Author", adVarChar, adParamInput, 255, _bstr_t(data(Author)));
        _ParameterPtr ParameterObj3 =
            CommandObj->CreateParameter("Publisher", adVarChar, adParamInput, 255, _bstr_t(data(Publisher)));
        _ParameterPtr ParameterObj4 =
            CommandObj->CreateParameter("Pubdate", adVarChar, adParamInput, 50, _bstr_t(data(Pubdate)));
        _ParameterPtr ParameterObj5 =
            CommandObj->CreateParameter("Price", adCurrency, adParamInput, 10, Price);

        CommandObj->Parameters->Append(ParameterObj1);
        CommandObj->Parameters->Append(ParameterObj2);
        CommandObj->Parameters->Append(ParameterObj3);
        CommandObj->Parameters->Append(ParameterObj4);
        CommandObj->Parameters->Append(ParameterObj5);

        _RecordsetPtr RecordsetObj = 
            CommandObj->Execute(
                NULL,
                NULL,
                long(0));

        cout << "操作成功." << endl;
    }
    catch (_com_error& err) {
        wprintf(L"The application throws the error: %s\n", (wchar_t*)err.ErrorMessage());
        wprintf(L"Description = %s\n", (wchar_t*)err.Description());
    }
    cout << "书籍添加成功!" << endl;
}
//管理员 添加书
void Controler_Delete_Book() {
    cout << "输入需删除书籍的ID: ";
    int BookID;
    cin >> BookID;
    try {
    
        _CommandPtr CommandObj(__uuidof(Command));
        CommandObj->ActiveConnection = Conn;
        CommandObj->CommandText = "DELETE FROM Books WHERE BookID = ?";
        CommandObj->CommandType = adCmdText;

        _ParameterPtr ParameterObj1 = CommandObj->CreateParameter("BookID", adVarChar, adParamInput, sizeof(int), BookID);
        CommandObj->Parameters->Append(ParameterObj1);

        _RecordsetPtr RecordsetObj = 
            CommandObj->Execute(
                NULL, 
                NULL, 
                long(0));

        cout << "删除成功." << endl;
    }

    catch (_com_error& err) {
        wprintf(L"The application throws the error: %s\n", (wchar_t*)err.ErrorMessage());
        wprintf(L"Description = %s\n", (wchar_t*)err.Description());
    }
}
//管理员 删除书
void Controler_Modify_Book() {
    cout << "输入修改后书籍的ID: ";
    int BookID;
    cin >> BookID;

    cout << "输入修改后书籍的书名: ";
    string Title;
    cin >> Title;

    cout << "输入修改后书籍的作者: ";
    string Author;
    cin >> Author;

    cout << "输入修改后书籍的出版商: ";
    string Publisher;
    cin >> Publisher;

    cout << "输入修改后书籍的出版日期: ";
    string Pubdate;
    cin >> Pubdate;

    cout << "输入修改后书籍的价格: ";
    float Price;
    cin >> Price;


    try {
        _CommandPtr CommandObj(__uuidof(Command));
        CommandObj->ActiveConnection = Conn;
        CommandObj->CommandText = "UPDATE Books SET Title = ?, Author = ?, Publisher = ?, Pubdate = ?, Price = ? WHERE BookID = ?";
        CommandObj->CommandType = adCmdText;

        //创建参数对象
        _ParameterPtr ParameterObj1 =
            CommandObj->CreateParameter("Title", adVarChar, adParamInput, 255, _bstr_t(data(Title)));
        _ParameterPtr ParameterObj2 =
            CommandObj->CreateParameter("Author", adVarChar, adParamInput, 255, _bstr_t(data(Author)));
        _ParameterPtr ParameterObj3 = 
            CommandObj->CreateParameter("Publisher", adVarChar, adParamInput, 255, _bstr_t(data(Publisher)));
        _ParameterPtr ParameterObj4 = 
            CommandObj->CreateParameter("Pubdate", adVarChar, adParamInput, 50, _bstr_t(data(Pubdate)));
        _ParameterPtr ParameterObj5 =
            CommandObj->CreateParameter("Price", adCurrency, adParamInput, 10, Price);
        _ParameterPtr ParameterObj6 = 
            CommandObj->CreateParameter("BookID", adVarChar, adParamInput, sizeof(int), BookID);

        CommandObj->Parameters->Append(ParameterObj1);
        CommandObj->Parameters->Append(ParameterObj2);
        CommandObj->Parameters->Append(ParameterObj3);
        CommandObj->Parameters->Append(ParameterObj4);
        CommandObj->Parameters->Append(ParameterObj5);
        CommandObj->Parameters->Append(ParameterObj6);

        _RecordsetPtr RecordsetObj = 
            CommandObj->Execute(
                NULL, 
                NULL, 
                long(0));

        cout << "修改成功." << endl;
    }
    catch (_com_error& err) {
        wprintf(L"The application throws the error: %s\n", (wchar_t*)err.ErrorMessage());
        wprintf(L"Description = %s\n", (wchar_t*)err.Description());
    }
}
//管理员 修改书
void Controler_User_Search_Book() {
    cout << "输入用户ID: ";
    int UserID;
    cin >> UserID;
    try {
   
        _CommandPtr CommandObj(__uuidof(Command));
        CommandObj->ActiveConnection = Conn;
        CommandObj->CommandText = "SELECT * FROM Borrow WHERE UserID = ?";
        CommandObj->CommandType = adCmdText;

     
        _ParameterPtr ParameterObj1 = 
            CommandObj->CreateParameter("UserID", adVarChar, adParamInput, sizeof(int), UserID);
        CommandObj->Parameters->Append(ParameterObj1);

 
        _RecordsetPtr RecordsetObj = 
            CommandObj->Execute(
                NULL, 
                NULL, 
                long(0));

        cout << "BorrowingID BookID BorrowDate ReturnDate Overtime" << endl;
        cout << "---------------------------------------------------" << endl;


        while (!RecordsetObj->EndOfFile) {
       
            int borrowingID = RecordsetObj->Fields->GetItem("BorrowingID")->Value.intVal;
            int bookID = RecordsetObj->Fields->GetItem("BookID")->Value.intVal;
            string borrowDate = (const char*)_bstr_t(RecordsetObj->Fields->GetItem("BorrowDate")->Value.bstrVal);
            string returnDate = (const char*)_bstr_t(RecordsetObj->Fields->GetItem("ReturnDate")->Value.bstrVal);
            _variant_t variantValue = RecordsetObj->Fields->GetItem("Overtime")->Value;
            bool Overtime = static_cast<bool>(variantValue);

     
            cout << left << setw(12) << borrowingID;
            cout << left << setw(7) << bookID;
            cout << left << setw(11) << borrowDate;
            cout << left << setw(11) << returnDate;
            cout << right << setw(2) << Overtime;
            cout << endl;
            RecordsetObj->MoveNext();
        }
    }
    catch (_com_error& err) {
        wprintf(L"The application throws the error: %s\n", (wchar_t*)err.ErrorMessage());
        wprintf(L"Description = %s\n", (wchar_t*)err.Description());
    }
}
//管理员 查询某用户借书状态
void Controler_Search_All() {
    try {
        _CommandPtr CommandObj(__uuidof(Command));
        CommandObj->ActiveConnection = Conn;
        CommandObj->CommandText = "SELECT * FROM Books";
        CommandObj->CommandType = adCmdText;

        _RecordsetPtr RecordsetObj = 
            CommandObj->Execute(
                NULL, 
                NULL, 
                long(0));
        
        cout << "BookID Title       Author          Publisher       Pubdate        Price   Copies" << endl;
        cout << "----------------------------------------------------------------------------------------" << endl;

 
        while (!RecordsetObj->EndOfFile) {
            int bookID = RecordsetObj->Fields->GetItem("BookID")->Value.intVal;
            string title = (const char*)_bstr_t(RecordsetObj->Fields->GetItem("Title")->Value.bstrVal);
            string author = (const char*)_bstr_t(RecordsetObj->Fields->GetItem("Author")->Value.bstrVal);
            string publisher = (const char*)_bstr_t(RecordsetObj->Fields->GetItem("Publisher")->Value.bstrVal);
            string Pubdate = (const char*)_bstr_t(RecordsetObj->Fields->GetItem("Pubdate")->Value.bstrVal);
            int Copies = RecordsetObj->Fields->GetItem("Copies")->Value.intVal;
            _variant_t variantValue = RecordsetObj->Fields->GetItem("Price")->Value;
            double price = static_cast<double>(variantValue);

          
            cout << left << setw(7) << bookID;
            cout << left << setw(12) << title;
            cout << left << setw(16) << author;
            cout << left << setw(16) << publisher;
            cout << left << setw(15) << Pubdate;
            cout << right << setw(6) << price;
            cout << right << setw(4) << Copies;
            cout << endl;
            RecordsetObj->MoveNext();
        }
    }
    catch (_com_error& err) {
        wprintf(L"The application throws the error: %s\n", (wchar_t*)err.ErrorMessage());
        wprintf(L"Description = %s\n", (wchar_t*)err.Description());
    }
}
//管理员 查询图书馆图书状态