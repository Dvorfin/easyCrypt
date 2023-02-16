#include <iostream>
#include <string>

using namespace std;

class Cryptor
{

public:

    int Crypt(string &msg, string &key)
    {
        UpTransform(msg);
        UpTransform(key); // переводим ключ и сообщение из строчных в заглавные

        if (!flag) 
        {
        
        for(int j = 0; j < msg.length(); j++)
        {
            msgNum = static_cast<int>(msg[j]) - 64; // сдвиг от таблицы аски на 64 влево
            keyNum = static_cast<int>(key[index]) - 64; // чтобы букве 'A' соответствовал номер 1

            cout << "j: " << j << "\tindex: " << index << endl;

            if (index < key.length()) // если ключ короче сообщения, то мы ключ должны повторить на следующий блок сообщения в длину ключа
            {
                index++;
            }

            if (index == key.length())
            {
                index = 0;
            }
                
            if((msgNum + keyNum) <= 26) // если сумма аски кодов больше мошности алфавит, то
            { 
                msg[j] = static_cast<char>(msgNum + keyNum) + 64; // складываем номера букв и переводим их в чар
                cout << "msgNum: " << msgNum << "\tkeyNum: " << keyNum << endl;

            } else {

                msg[j] = static_cast<char>(msgNum + keyNum - 26) + 64;
                cout << "msgNum: " << msgNum << "\tkeyNum: " << keyNum << endl;

            }
        }

        cout << endl << "Msg sucsessfully crypted" << endl;

        }

        index = 0;
        flag = 0;

        return 0;
    }
    

    int Decrypt(string &msg, string &key)
    {   
        UpTransform(msg);
        UpTransform(key); // переводим ключ и сообщение из строчных в заглавные

        if (!flag)
        {

        for(int j = 0; j < msg.length(); j++)
        {
            msgNum = static_cast<int>(msg[j]) - 64; // сдвиг от таблицы аски на 64 влево
            keyNum = static_cast<int>(key[index]) - 64; // чтобы букве 'A' соответствовал номер 1

            cout << "j: " << j << "\tindex: " << index << endl;

            if (index < key.length()) // если ключ короче сообщения, то мы ключ должны повторить на следующий блок сообщения в длину ключа
            {
                index++;
            }

            if (index == key.length())
            {
                index = 0;
            }
                
            if((msgNum - keyNum) < 0) // если сумма аски кодов больше мошности алфавит, то
            { 
                msg[j] = static_cast<char>(msgNum - keyNum + 26) + 64; // складываем номера букв и переводим их в чар
                cout << "msgNum: " << msgNum << "\tkeyNum: " << keyNum << endl;

            } else {

                msg[j] = static_cast<char>(msgNum - keyNum) + 64;
                cout << "msgNum: " << msgNum << "\tkeyNum: " << keyNum << endl;

            }
        }

        }
        
        index = 0;
        flag = 0;

        return 0;
    }


    void UpTransform(string &msgToTransform)
    {
        try
        {
            for(int j = 0; j < msgToTransform.length(); j++)
            {

                msgNum = static_cast<int>(msgToTransform[j]); // аски номер символа сообщения

                if (  ((32 <= msgNum) && (msgNum <= 64)) || ((91 <= msgNum) && (msgNum <= 96)) || (msgNum < 0) )  // если не заглавная и не буква
                {
                    flag = 1;
                    throw "Incorrect msg or key!";
                } 
                else if ((97 <= msgNum) && (msgNum <= 122))  // если буква маленька, то делаем ее большой
                {
                    msgToTransform[j] = msgNum - 32;
                } 
               
            }
        }
        catch(const char* exception)
        {
            cerr << endl << "Crypt error: " << exception << endl;
        }
        
    }

    void Show(string msg) // просто вывод данных
    {
        if (!flag)
        {
            cout << "Message: ";

            for(int j = 0; j < msg.length(); j++)
            {
                cout << msg[j];
            }

            cout << endl;
        }

    }

private:

    //string msg;
    int keyNum; 
    // номера символа ключа и сообщения по таблице аски
    int msgNum;
    bool flag = 0;
    int index = 0;
    bool flag2 = 0;

};

int main()
{

    string message;
    string key;

    Cryptor msg;

    cout << "Enter msg to crypt: ";
    cin >> message;

    cout << "Enter key: ";
    cin >> key;

    msg.Crypt(message, key);
    msg.Show(message);

    cout << "Enter msg to decrypt: ";
    cin >> message;

    cout << "Enter key: ";
    cin >> key;

    msg.Decrypt(message, key);
    msg.Show(message);
    
}

// to do: добавить считывание данных для шифрования и для записи зашифрованных данных обратно в файл; 
// добваить в класс методы чисто для шифрования и дешифрования, которые будут вызывать в других методах внутри самого класса
