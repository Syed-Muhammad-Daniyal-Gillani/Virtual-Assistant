#include <iostream>
#include <string>
#include <string.h>
#include <chrono>
#include <thread>
#include <windows.h>
#include "mmsystem.h"
#include <fstream>
#include <SFML/Audio.hpp>
using namespace std;

void delay(string text)
{
    for (char c : text)
    {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(50));
    }
}
class phonebook
{
public:
    struct Contact {
        string name = "";
        string phone = "";
        Contact* next = nullptr;
    };

    Contact* head = nullptr;

    void addContact(string name, string phone) {
        Contact* newContact = new Contact();
        newContact->name = name;
        newContact->phone = phone;
        newContact->next = head;
        head = newContact;
    }

    void printContacts() {
        Contact* current = head;
        cout << "Name \t Phone Number" << endl;
        while (current != nullptr) {
            cout << current->name << "\t" << current->phone << endl;
            current = current->next;
        }
    }

    void saveContacts() {
        ofstream file("contacts.txt");
        Contact* current = head;
        while (current != nullptr) {
            file << current->name << "\t" << current->phone << endl;
            current = current->next;
        }
        file.close();
    }

    void loadContacts() {
        ifstream file("contacts.txt");
        string name, phone;
        while (file >> name >> phone) {
            addContact(name, phone);
        }
        file.close();
    }
};
struct Node {
    string task;
    Node* next = NULL;
};
//-----------------------------------TickTacToe Class-------------------------------------------||
class tiktaktoe
{
public:

    char board[3][3] = { {'1','2','3'},{'4','5','6'},{'7','8','9'} };
    int choice = 0;
    int row = 0, col = 0;
    char turn = 'X';
    bool draw = false;

    void dispboard() {
        system("cls");
        cout << "PLAYER - 1 [X] || PLAYER - 2 [O]  " << endl;
        cout << "     |     |     " << endl;
        cout << "  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "  " << endl;
        cout << "_   _|  -  |   __" << endl;
        cout << "     |     |     " << endl;
        cout << "  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "  " << endl;
        cout << "_   _|  -  |   __" << endl;
        cout << "     |     |     " << endl;
        cout << "  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "  " << endl;
        cout << "     |     |     " << endl;
    }
    void player_turn() {
        bool flag = false;
        if (turn == 'X') {
            cout << "  Player - 1 [X] turn : ";
        }
        else if (turn == 'O') {
            cout << "  Player - 2 [O] turn : ";
        }
        do {

            try {
                cin >> choice;
                if (!(choice >= 1 && choice <= 9)) {
                    throw(choice);
                }
                flag = false;
            }
            catch (int c) {
                delay("Enter the correct value");
                flag = true;
            }
        } while (flag);
        switch (choice) {
        case 1:
        {
            row = 0;
            col = 0;
            break;
        }
        case 2:
        {
            row = 0;
            col = 1;
            break;
        }
        case 3:
        {
            row = 0;
            col = 2;
            break;
        }
        case 4:
        {
            row = 1;
            col = 0;
            break;
        }
        case 5:
        {
            row = 1;
            col = 1;
            break;
        }
        case 6:
        {
            row = 1;
            col = 2;
            break;
        }
        case 7:
        {
            row = 2;
            col = 0;
            break;
        }
        case 8:
        {
            row = 2;
            col = 1;
            break;
        }
        case 9:
        {
            row = 2;
            col = 2;
            break;
        }
        }

        if (turn == 'X' && board[row][col] != 'X' && board[row][col] != 'O')
        {
            board[row][col] = 'X';
            turn = 'O';
        }
        else if (turn == 'O' && board[row][col] != 'X' && board[row][col] != 'O')
        {
            board[row][col] = 'O';
            turn = 'X';
        }
        else
        {
            cout << "Box is already taken, please choose another box " << endl;
            player_turn();
        }
        dispboard();
    }
    bool win()
    {
        for (int i = 0; i < 3; i++)
            if (board[i][0] == board[i][1] && board[i][0] == board[i][2] || board[0][i] == board[1][i] && board[0][i] == board[2][i])
                return false;
        if (board[0][0] == board[1][1] && board[0][0] == board[2][2] || board[0][2] == board[1][1] && board[0][2] == board[2][0])
            return false;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] != 'X' && board[i][j] != 'O')
                    return true;
        draw = true;
        return false;
    }


};
//-----------------------------------TickTacToe Class-------------------------------------------||
class ToDoList {
private:
    Node* head;
    Node* tail;
    string fileName;

public:
    ToDoList(string file) : fileName(file) {
        head = nullptr;
        tail = nullptr;
        loadList();
    }

    void addTask(string task) {
        Node* newNode = new Node;
        newNode->task = task;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        saveList();
    }
    void deleteTask(int a) {
        Node* current = head;
        Node* previous = head;
        if (a == 1) {
            head = head->next;
            delete current;
        }
        else {
            for (int i = 0; i < a - 1; i++) {
                previous = current;
                current = current->next;
            }
            previous->next = current->next;
            delete current;
        }
        saveList();
    }

    void displayList() {
        cout << endl;
        Node* current = head;
        int count = 1;
        while (current != nullptr) {
            cout << count << ") " << current->task << endl;
            current = current->next;
            count++;
        }
        cout << endl;
    }
private:
    void saveList() {
        ofstream file(fileName);
        Node* current = head;
        while (current != nullptr) {
            file << current->task << endl;
            current = current->next;
        }
        file.close();
    }

    void loadList() {
        ifstream file(fileName);
        string task;
        while (getline(file, task)) {
            addTask(task);
        }
        file.close();
    }
};
//----------------------Add new functions for chatbot to this class-----------------------------||
//---------------------Chatbot_functions Class with public inheritence--------------------------||
class chatbot_functions : public tiktaktoe, phonebook
{
public:
    // Starting Chatbot function
    void startbot()
    {
        delay("Starting chatbot"); 
        cout << endl;
        delay("Please wait!!!");
        cout << endl;
        for (int i = 0; i <= 2; i++)
        {
            delay("Loading...<_0x0_/");
            system("cls");
        }
    }
    // Function to wrap  query keywords and be able to use them in an IF statement. Credits to Naseer's brother.
    //------------Wrap-function (Wraps two if conditions for chatbot)-----------------||
    bool wrapper(string chat, string query)
    {
        return (chat.find(query) != string::npos);
    }
    //-----------------------------To Do List Function--------------------------------||
    void to_do_list() {
        delay("T O  D O  L I S T"); cout << endl;
        ToDoList list("tasks.txt");
        cout << "Choose the following:" << endl;
        cout << "1) View List" << endl << "2) Insert a Task" << endl << "3) Remove a task" << endl << "4) Exit" << endl;
        int ans;
        bool flag = false;
        do {
            cin >> ans;
            cin.ignore(1, '\n');
            system("cls");
            if (ans == 1) {
                delay("Display List");
                cout << endl;
                list.displayList();
                delay("Anything else i can do for you?"); 
                cout << endl;
                cout << "1) View List" << endl << "2) Insert a Task" << endl << "3) Remove a task" << endl << "4) Exit" << endl;
            }
            else if (ans == 2) {
                delay("Insert");
                cout << endl;
                string task;
                cout << " Enter the task: ";
                getline(cin, task);
                list.addTask(task);
                delay("New task added Successfully !! Anything else i can do for you?"); cout << endl;
                cout << "1) View List" << endl << "2) Insert a Task" << endl << "3) Remove a task" << endl << "4) Exit" << endl;
            }
            else if (ans == 3) {
                delay("Delete");
                cout << endl;
                int deltask;
                cout << " Enter the task number you wish to delete: " << endl << endl;
                list.displayList();
                cin >> deltask;
                list.deleteTask(deltask);
                delay("Task deleted successfully!! Anything else i can do for you?"); cout << endl;
                cout << "1) View List" << endl << "2) Insert a Task" << endl << "3) Remove a task" << endl << "4) Exit" << endl;
            }
            else if (ans == 4) {
                flag = true;
            }
            else delay("Bruhhhhhhh... Enter only the options mentioned above. Don't tell me that I, an AI, has iq higher than you...");
        } while (!flag);
        delay("Bye");
        cout << endl;
    }
    void musicPlayer() 
    {
        // Create a music object and load a music file
        string file;
        cout << "Enter name of music file you want to play ending with .mp3" << endl;
        getline(cin, file);
        sf::Music music;
        if (!music.openFromFile(file))
        {
            cout << "Error loading music" << endl;
            return;
        }
        music.play();
        // While music is running
        while (true)
        {
            //Take User Input
            char input;
            cin >> input;
            switch (input)
            {
            case 'p':
                music.pause();
                break;
            case 'r':
                music.play();
                break;
            case 'd':
                cout << "Duration: " << music.getDuration().asSeconds() << " seconds" << endl;
                break;
            case 'q':
                return;
                break;
            }
        }
        return;
    }
    void Ticktactoe() {
        delay("T I C K  T A C  T O E  G A M E");
        while (win()) {
            dispboard();
            player_turn();
            win();
        }
        if (turn == 'X' && draw == false)
        {
            delay("Congratulations ! Player1 has won the game");
        }
        else if (turn == 'O' && draw == false)
        {
            delay("Congratulations Player2 has won the game");
        }
        else
            delay("ITS A DRAW, XD");

        return;
    }
    int launch_phonebook()
    {
        loadContacts();
        delay("P H O N E  B O O K");
        cout << endl;
        int choice;
        do {
            cout << "1. Add Contact" << endl;
            cout << "2. Print Contacts" << endl;
            cout << "3. Save and Exit" << endl;
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore(25, '\n');

            if (choice == 1)
            {
                string name, phone;
                cout << "Enter name: ";
                getline(cin, name);
                cout << endl;
                cout << "Enter phone number: ";
                getline(cin, phone);
                cout << endl;
                addContact(name, phone);
                delay("New contact added");
                cout << endl;
                delay("anything else i can do for you?");
                cout << endl;
            }
            else if (choice == 2) 
            {
                printContacts();
                delay("anything else i can do for you?");
                cout << endl;
            }
            else if (choice == 3) 
            {
                saveContacts();
                break;
            }
            else {
                delay("Invalid choice");
                cout << endl;
            }
        } while (true);

        return 0;
    }
};
//---------------------Chatbot Class with public inheritence--------------------------||
class chatbot : public chatbot_functions
{
public:
    //------------------------------Chatbot-function----------------------------------||
    void chat()
    {
        cout << "Chatbot active: " << endl;
        //-------------------------Declarations----------------------------||
        string chat, word;
        //While loop
        while (1)
        {
            //-------------------------Get string------------------------------||
            getline(cin, chat);
            //------------------Convert string to lowercase--------------------||
            for (int i = 0; i < chat.length(); i++)
            {
                if (chat[i] >= 'A' && chat[i] <= 'Z')
                {
                    chat[i] = chat[i] + 32;
                }
            }
            //------------------------"What-list"------------------------------||
            if (wrapper(chat, "what"))
            {
                if (chat.find(word = "time") != string::npos)
                {
                    delay("Look at the bottom right corner of the screen its usually written over there 7OxO7");
                    cout << endl;
                }
                else if (chat.find(word = "weather") != string::npos)
                {
                    delay("Its a lovely weather <3");
                    cout << endl;
                }
                else if (wrapper(chat, "your") && wrapper(chat, "age"))
                {
                    delay("I'm less than 1 year old ;-; ");
                    cout << endl;
                }
                else if (wrapper(chat, "your") && wrapper(chat, "name"))
                {
                    delay("I am called Emebot ^-^ ");
                    cout << endl;
                }
                else if (wrapper(chat, "your") && wrapper(chat, "food"))
                {
                    delay("I love eating RAM <3 ...... gib more RAM  70.07");                 
                    cout << endl;
                }
            }
            //-------------------------"Who-list"------------------------------||
            else if (wrapper(chat, "who"))
            {
                if (chat.find(word = "you") != string::npos)
                {
                    delay("I'm your personal assistant!! "); cout << endl;
                }
                else if (chat.find(word = "i") != string::npos)
                {
                    delay("You're my client"); cout << endl;
                }
            }
            //-------------------------"How-list"------------------------------||        
            else if (wrapper(chat, "how"))
            {
                if (chat.find(word = "you") != string::npos)
                {
                    delay("Hi! I'm fine, thanks for asking :)");
                    cout << endl;
                }
            }
            //-------------------------"Play List"-----------------------------||
            else if ( wrapper(chat,"play")|| wrapper(chat, "launch")|| wrapper(chat, "run"))
            {
                if (wrapper(chat, "music") || wrapper(chat, "songs"))
                {
                    delay("Launching MusicPlayer"); 
                    cout << endl;
                    musicPlayer();
                    cout << "Music has ended. Thanks for listening." << endl;
                }                
                else if (wrapper(chat, "game"))
                {
                    delay("Launching TickTacToe");
                    cout << endl;
                    Ticktactoe();
                    cout << endl;
                }
                else if (wrapper(chat, "to") && wrapper(chat, "do") && wrapper(chat, "list"))
                {
                    delay("Launching To-Do-List");
                    cout << endl;
                    to_do_list();
                    cout << endl;
                }                
                else if (wrapper(chat, "phonebook"))
                {
                    delay("Launching PhoneBook");
                    cout << endl;
                    launch_phonebook();
                    cout << endl;
                }
            }
            else if (wrapper(chat, "exit"))
            {
                delay("It was nice talking to you...");
                delay("Shutting down");
                break;
            }
            //-----------------------"If none matched"-------------------------||    
            else
            {
                delay("Sorry I cannot understand what you're asking"); cout << endl;
            }
        }
    }
};
int main()
{
    chatbot mybot;
    mybot.startbot();
    delay("Hi I am your virtual assistant >w< ");
    cout << endl;
    delay("Starting chatbot - Standby...");
    cout << endl;
    mybot.chat();
}