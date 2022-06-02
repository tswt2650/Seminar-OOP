#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

void Home();
void UserPage(string);
map<string, string> UserList;

class User
{
private:
    vector<string> FriendList;
    struct chat
    {
        string NguoiGui, NguoiNhan;
        vector<string> mess;
    };

public:
    map<string, chat> sms;
    void addFriend(string);
    void unFriend(string);
    void DisplayFriend(string);
    void chat_on(string, string, string);
    void inbox(string);
};

void User::chat_on(string UserName, string NhanTN, string message)
{
    sms[NhanTN].NguoiGui = UserName;
    sms[NhanTN].NguoiNhan = NhanTN;

    if (UserList.find(NhanTN) == UserList.end())
    {
        cout << "\nERROR!!! Khong tim thay ten nguoi dung\a\a\n";
        sleep(2.5);
        UserPage(UserName);
    }

    sms[NhanTN].mess.push_back(UserName + ": " + message);
}

void User::inbox(string UserName)
{
    cout << "\nWelcome " << UserName << " to your Inbox\n\n";
    if (sms.empty())
    {
        cout << "Ban chua co tin nhan nao!";
    }
    else
    {
        cout << "Tat ca tin nhan rieng cua ban:\n\n";
        for (auto message : sms[UserName].mess)
        {
            cout << message << "\n\n";
        }
    }
}

void User::addFriend(string UserName)
{
    string addname;
    cout << "\nNhap ten nguoi dung muon them vao danh sach ban be: ";
    cin >> addname;

    if (addname == UserName)
    {
        cout << "\nERROR!!! Khong the tu them chinh minh vao danh sach ban be!!!\n";
        sleep(1);
        return;
    }

    cout << "\nXin cho trong giay lat! Dang tim kiem\t" << addname << "......\n";
    // waiting time for  new message
    sleep(0.5);

    if (UserList.find(addname) == UserList.end())
    {
        cout << "\nERROR!!! Ten nguoi dung khong ton tai!!!\n";
        return;
    }

    if (find(FriendList.begin(), FriendList.end(), addname) != FriendList.end())
    {
        cout << addname << " da ton tai trong danh sach ban be cua ban!!!\n";
    }

    cout << "\nDa tim thay:\t" << addname << endl;
    FriendList.push_back(addname);
    cout << "\nXin chuc mung! " << addname << " da duoc them vao danh sach ban be cua ban\n\n";
}

void User::DisplayFriend(string UserName)
{
    if (FriendList.empty())
        cout << "Ban chua ket ban voi ai\n\n";
    else
    {
        cout << "\nWelcome " << UserName << " Ban be cua ban:\n"
             << endl;
        for (auto name : FriendList)
        {
            cout << name << endl;
        }

        cout << "\n\nTong so ban be cua ban: " << FriendList.size() << endl;
    }
}

void User::unFriend(string UserName)
{
    if (FriendList.empty())
    {
        cout << "\nDanh sach ban be trong!!!\a\n";
        sleep(1);
    }
    else
    {
        string name;
        cout << "\nNhap ten nguoi dung muon xoa khoi danh sach ban be \n";
        cin >> name;

        auto it = find(FriendList.begin(), FriendList.end(), name);
        if (it == FriendList.end())
        {
            cout << "\nDanh sach ban be cua ban khong ton tai nguoi dung nay\n";
            sleep(1);
            return;
        }

        FriendList.erase(it);
        cout << "\n Xoa " << name << " khoi danh sach ban be.\a\a\a\a\n";
        cout << name << " da bi xoa khoi danh sach ban be cua ban\n";
    }
}

bool isValid(string s)
{
    for (auto i : s)
    {
        if (i == ' ')
            return false;
    }
    return true;
}

bool Login(string &username, string &pwd)
{
    cout << "\tChon ten dang nhap:\t";
    getline(cin, username);

    if (!isValid(username))
    {
        cout << "Ten dang nhap khong duoc chua khoang trang!\n";
        return false;
    }

    cout << "\tChon mat khau:\t";
    getline(cin, pwd);

    if (!isValid(pwd))
    {
        cout << "Mat khau khong duoc chua khoang trang!\n";
        return false;
    }
    return true;
}

void Home()
{
    int flag = 0, choice;

    while (true)
    {
        system("cls");
        cout << "\n\t\t*****************************************"
             << "\n\t\t*      WELCOME TO THE V-MESSENGER       *"
             << "\n\t\t*****************************************";

        cout << "\n1-Dang ky\n";
        cout << "2-Dang nhap\n";
        cout << "3-Thoat\n";
        cout << "Please Enter your choice: \n";
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1:
        {
            cin.ignore();
            string username, pwd;

            while (true)
            {
                if (Login(username, pwd))
                    break;
            }

            if (UserList.empty())
                UserList[username] = pwd;
            else
            {
                if (UserList.find(username) != UserList.end()) {
                    cout << "\nXin loi! Ten dang nhap da duoc su dung!! Vui long chon Ten dang nhap khac!!!\n";
                    sleep(3);
                    system("cls");
                }
                else
                    UserList[username] = pwd;
            }
            break;
        }
        case 2:
        {
            cin.ignore();
            string lusername, lpwd;

            if (!Login(lusername, lpwd) || UserList[lusername] != lpwd) {
                cout << "\nTen dang nhap hoac mat khau khong dung\n\t!!Vui long nhap lai!!!\n";
                sleep(3);
                system("cls");
            }
            else
            {
                cout << "\nWELCOME " << lusername << "!  Dang nhap thanh cong!! \n";
                UserPage(lusername);
                flag = 1;
                sleep(2);
                system("cls");
            }
            break;
        }
        case 3:
        {
            cout << "\nHien thi\n";

            cout << "\nTat ca nguoi dung:\n";
            for (auto user : UserList)
            {
                cout << user.first << "\t" << user.second << endl;
            }
            return;
        }
        }
        if (flag == 1)
            break;
    }
}

map<string, User> f;
void UserPage(string UserName)
{
    int chon1, chon2;
MainMenu:
    system("cls");
    cout << "\n\t\t*****************************************"
         << "\n\t\t*      WELCOME TO THE V-MESSENGER       *"
         << "\n\t\t*****************************************";

    cout << "\n\t    ***********Choose from following menu**********\n";
    cout << "\n1-Tin nhan rieng";
    cout << "\n2-Chat";
    cout << "\n3-Danh sach ban be";
    cout << "\n4-Them ban";
    cout << "\n5-Xoa ban";
    cout << "\n6-Dang xuat\n\n";
    cin >> chon1;
    system("cls");
    switch (chon1)
    {
    case 1:
    {
        f[UserName].inbox(UserName);
        cout << "\nPress any number except '0' to go back to main menu\n";
        cin >> chon2;
        if (chon2)
            goto MainMenu;
        break;
    }
    case 2:
    {
        string NhanTN;
        cout << "\nNhap ten nguoi nhan:\n";
        cin >> NhanTN;

        string message;
        cout << "\nNhap noi dung tin nhan: " << endl;
        cin.ignore();
        getline(cin, message);

        f[NhanTN].chat_on(UserName, NhanTN, message);
        cout << "\nTin nhan cua ban da duoc gui thanh cong!\n";

        sleep(2.5);
        goto MainMenu;
        break;
    }
    case 3:
    {
        f[UserName].DisplayFriend(UserName);
        cout << "\npress any number except '0' to go back to main menu\n";
        cin >> chon2;
        if (chon2)
            goto MainMenu;
        break;
    }
    case 4:
    {
        f[UserName].addFriend(UserName);
        sleep(2.5);
        goto MainMenu;
        break;
    }
    case 5:
    {
        f[UserName].unFriend(UserName);
        sleep(2.5);
        goto MainMenu;
        break;
    }
    case 6:
    {
        system("cls");
        cout << "\nDang xuat thanh cong!!!\n";
        Home();
        break;
    }
    }
}

int main()
{
    Home();
    return 0;
}
