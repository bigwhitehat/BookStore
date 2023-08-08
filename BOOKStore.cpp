#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <string>
#include <iomanip>
using namespace std;
#import "c:\\Program Files\\Common Files\\System\\ADO\\msado15.dll" no_namespace rename("EOF", "EndOfFile")

_ConnectionPtr Conn;
int CurrentUser;

void Main_Menu();//��ʾ���˵�
void User_Menu();//��ʾ�û��˵�
void Controler_Menu();//��ʾ����Ա�˵�
void User_Borrow_Book();//�û� ����
void User_Return_Book();//�û� ����
void User_Search_Book();//�û� ��ѯ��
void User_Search_Self_Book();//�û� ��ѯ�Լ��Ľ��ļ�¼
void Controler_Add_Book();//����Ա �����
void Controler_Delete_Book();//����Ա ɾ����
void Controler_Modify_Book();//����Ա �޸���
void Controler_User_Search_Book();//����Ա ��ѯĳ�û�����״̬
void Controler_Search_All();//����Ա ��ѯͼ���ͼ��״̬

void enterUserID() {
    cout << "�������û�ID:";
    int inputuserID;
    cin >> inputuserID;
    CurrentUser = inputuserID;
}    
//�����û�ID
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
            cout << "��ӭ�´�ʹ��!" << endl;
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
//������
void Main_Menu() {
    cout << "**********************************" << endl;
    cout << "*******��ӭ����ͼ�����ϵͳ*******" << endl;
    cout << "1. �û�" << endl;
    cout << "2. ����Ա" << endl;
    cout << "3. �˳�" << endl;
    cout << "�������ѡ��: " << endl;
    cout << "**********************************" << endl;
}
//��ʾ���˵�
void User_Menu() {
    cout << "**********************************" << endl;
    cout << "********��ӭ�����û�ϵͳ**********" << endl;
    cout << "1. �����鼮" << endl;
    cout << "2. �黹�鼮" << endl;
    cout << "3. �����鼮" << endl;
    cout << "4. ��ѯ�Լ�������Ϣ" << endl;
    cout << "�������ѡ��: " << endl;
    cout << "**********************************" << endl;
}
//��ʾ�û��˵�
void Controler_Menu() {
    cout << "**********************************" << endl;
    cout << "********��ӭ�������Աϵͳ********" << endl;
    cout << "1. ����鼮" << endl;
    cout << "2. ɾ���鼮" << endl;
    cout << "3. �޸��鼮" << endl;
    cout << "4. �����鼮" << endl;
    cout << "5. �����鼮������Ϣ" << endl;
    cout << "6. �鼮��Ϣ" << endl;
    cout << "�������ѡ��: " << endl;
    cout << "**********************************" << endl;

}
//��ʾ����Ա�˵�
void User_Borrow_Book() {
    cout << "����Ҫ���ĵ��鼮ID: ";
    int BookID;
    cin >> BookID;
    string Borrowing_Date;
    string Return_Date;
    cout << "�������ʱ�䣺";
    cin >> Borrowing_Date;
    cout << "����Ԥ�ƹ黹ʱ�䣺";
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
        cout << "�����ɹ�." << endl;
    }

    catch (_com_error& err) {
        wprintf(L"The application throws the error: %s\n", (wchar_t*)err.ErrorMessage());
        wprintf(L"Description = %s\n", (wchar_t*)err.Description());
    }
}
//�û� ����
void User_Return_Book() {
    cout << "����黹�鼮ID: ";
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

        cout << "�����ɹ�." << endl;
    }

    catch (_com_error& err) {
        wprintf(L"The application throws the error: %s\n", (wchar_t*)err.ErrorMessage());
        wprintf(L"Description = %s\n", (wchar_t*)err.Description());
    }
}
//�û� ����
void User_Search_Book() {
    cout << "������Ҫ��ѯ�鼮������: ";
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
//�û� ��ѯ��
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
//�û� ��ѯ�Լ��Ľ��ļ�¼


void Controler_Add_Book() {
    cout << "��������鼮������: ";
    string Title;
    cin >> Title;

    cout << "��������鼮������: ";
    string Author;
    cin >> Author;

    cout << "��������鼮�ĳ�����: ";
    string Publisher;
    cin >> Publisher;

    cout << "��������鼮�ĳ���ʱ��: ";
    string Pubdate;
    cin >> Pubdate;

    cout << "��������鼮�ļ۸�: ";
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

        cout << "�����ɹ�." << endl;
    }
    catch (_com_error& err) {
        wprintf(L"The application throws the error: %s\n", (wchar_t*)err.ErrorMessage());
        wprintf(L"Description = %s\n", (wchar_t*)err.Description());
    }
    cout << "�鼮��ӳɹ�!" << endl;
}
//����Ա �����
void Controler_Delete_Book() {
    cout << "������ɾ���鼮��ID: ";
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

        cout << "ɾ���ɹ�." << endl;
    }

    catch (_com_error& err) {
        wprintf(L"The application throws the error: %s\n", (wchar_t*)err.ErrorMessage());
        wprintf(L"Description = %s\n", (wchar_t*)err.Description());
    }
}
//����Ա ɾ����
void Controler_Modify_Book() {
    cout << "�����޸ĺ��鼮��ID: ";
    int BookID;
    cin >> BookID;

    cout << "�����޸ĺ��鼮������: ";
    string Title;
    cin >> Title;

    cout << "�����޸ĺ��鼮������: ";
    string Author;
    cin >> Author;

    cout << "�����޸ĺ��鼮�ĳ�����: ";
    string Publisher;
    cin >> Publisher;

    cout << "�����޸ĺ��鼮�ĳ�������: ";
    string Pubdate;
    cin >> Pubdate;

    cout << "�����޸ĺ��鼮�ļ۸�: ";
    float Price;
    cin >> Price;


    try {
        _CommandPtr CommandObj(__uuidof(Command));
        CommandObj->ActiveConnection = Conn;
        CommandObj->CommandText = "UPDATE Books SET Title = ?, Author = ?, Publisher = ?, Pubdate = ?, Price = ? WHERE BookID = ?";
        CommandObj->CommandType = adCmdText;

        //������������
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

        cout << "�޸ĳɹ�." << endl;
    }
    catch (_com_error& err) {
        wprintf(L"The application throws the error: %s\n", (wchar_t*)err.ErrorMessage());
        wprintf(L"Description = %s\n", (wchar_t*)err.Description());
    }
}
//����Ա �޸���
void Controler_User_Search_Book() {
    cout << "�����û�ID: ";
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
//����Ա ��ѯĳ�û�����״̬
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
//����Ա ��ѯͼ���ͼ��״̬