#include <iostream>
#include <cmath>
using namespace std;

struct GameDlc
{
    int idDlc;
    string namaDlc;
    GameDlc *next;
};

struct Game
{
    string id;
    string nama;
    GameDlc *dlcHead;
    GameDlc *dlcTail;
    Game *next;
};

Game *headGame = nullptr;
void hapusSemuaDlc(Game *&game);

void pushGame(const string &id, const string &nama)
{
    Game *newGame = new Game();
    newGame->id = id;
    newGame->nama = nama;
    newGame->dlcHead = nullptr;
    newGame->dlcTail = nullptr;
    newGame->next = headGame;
    headGame = newGame;

    // cout << "Game " << nama << " ditambahkan." << endl;
}

bool isIdUsed(const string &id)
{
    Game *temp = headGame;
    while (temp != nullptr)
    {
        if (temp->id == id)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void tambahGame()
{
    cin.ignore();
    string id, namaGame;

    cout << "Masukkan Id: ";
    getline(cin, id);

    if (isIdUsed(id))
    {
        cout << "ID " << id << " sudah digunakan. Silakan masukkan ID yang berbeda." << endl;
        return;
    }

    cout << "Masukkan nama game: ";
    getline(cin, namaGame);

    pushGame(id, namaGame);
}

Game *findGame(const string &id)
{
    Game *temp = headGame;
    while (temp != nullptr)
    {
        if (temp->id == id)
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void enqueueDlcToGame(const string &gameId, const int &dlcId, const string &namaDlc)
{
    Game *game = findGame(gameId);
    if (game == nullptr)
    {
        cout << "Game dengan ID " << gameId << " tidak ada." << endl;
        return;
    }

    GameDlc *newDlc = new GameDlc();
    newDlc->idDlc = dlcId;
    newDlc->namaDlc = namaDlc;
    newDlc->next = nullptr;

    if (game->dlcHead == nullptr)
    {
        game->dlcHead = newDlc;
        game->dlcTail = newDlc;
    }
    else
    {
        game->dlcTail->next = newDlc;
        game->dlcTail = newDlc;
    }
}

void pop()
{
    if (headGame == nullptr)
    {
        cout << "Belum ada game" << endl;
        return;
    }

    Game *temp = headGame;
    headGame = headGame->next;

    if (temp->dlcHead != nullptr)
    {
        hapusSemuaDlc(temp);
    }

    cout << "Game " << temp->nama << " telah dihapus" << endl;
    delete temp;
}

void displayGames()
{
    Game *tempGame = headGame;
    while (tempGame != nullptr)
    {
        cout << "Game: " << tempGame->nama << " (ID: " << tempGame->id << ")" << endl;
        GameDlc *tempDlc = tempGame->dlcHead;
        while (tempDlc != nullptr)
        {
            cout << "  DLC: " << tempDlc->namaDlc << " (ID: " << tempDlc->idDlc << ")" << endl;
            tempDlc = tempDlc->next;
        }
        tempGame = tempGame->next;
    }
}

void ubahNamaGame(Game *&game)
{
    cin.ignore();
    string namaBaru;
    cout << "Masukkan nama baru >> ";
    getline(cin, namaBaru);

    game->nama = namaBaru;
}

bool checkIdDlc(Game *&game, const int &id)
{
    GameDlc *temp = game->dlcHead;

    while (temp != nullptr)
    {
        if (temp->idDlc == id)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void tambahDlc(Game *&game)
{
    cin.ignore();
    int id;
    string nama;

    cout << "Masukkan id dlc >>";
    cin >> id;
    cin.ignore();
    if (checkIdDlc(game, id))
    {
        cout << "Id telah digunakan" << endl;
        return;
    }
    cout << "Masukkan nama dlc >>";
    getline(cin, nama);

    GameDlc *newDlc = new GameDlc();
    newDlc->idDlc = id;
    newDlc->namaDlc = nama;
    newDlc->next = nullptr;
    if (game->dlcHead == nullptr)
    {
        game->dlcHead = newDlc;
        game->dlcTail = newDlc;
    }
    else
    {
        game->dlcTail->next = newDlc;
        game->dlcTail = newDlc;
    }
}

bool fibonacciSearchDlcLinked(GameDlc *dlcHead, const int &keyword)
{
    int fibMMm2 = 0;              
    int fibMMm1 = 1;              
    int fibM = fibMMm2 + fibMMm1; 

    
    int n = 0;
    GameDlc *temp = dlcHead;
    while (temp)
    {
        ++n;
        temp = temp->next;
    }

    
    if (n == 0)
        return false;

    int offset = -1;
    while (fibM < n)
    {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    GameDlc *prev = nullptr;
    GameDlc *curr = dlcHead;

    
    while (fibM > 0)
    {
        int i = min(offset + fibMMm2, n - 1);

        
        for (int j = 0; j < i && curr; j++)
        {
            prev = curr;
            curr = curr->next;
        }

        
        if (curr && curr->idDlc == keyword)
        {
            cout << "DLC ditemukan " << curr->namaDlc << " (ID: " << curr->idDlc << ")" << endl;
            return true;
        }
        
        else if (curr && curr->idDlc < keyword)
        {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
            prev = curr;
            curr = curr->next;
        }
        
        else
        {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
    }

    
    return false;
}

bool jumpSearchDlcLinked(GameDlc *dlcHead, const int &keyword)
{
    int n = 0;
    GameDlc *temp = dlcHead;
    while (temp)
    {
        ++n;
        temp = temp->next;
    }

    int step = sqrt(n);
    int prev = 0;
    temp = dlcHead;
    while (temp && temp->idDlc < keyword)
    {
        for (int j = 0; j < step && temp->next; j++)
        {
            temp = temp->next;
            prev++;
        }
    }

    int currentStep = 0;
    GameDlc *dlc = dlcHead;
    while (dlc && currentStep < prev && dlc->idDlc < keyword)
    {
        dlc = dlc->next;
        currentStep++;
    }

    if (dlc && dlc->idDlc == keyword)
    {
        cout << "DLC ditemukan: " << dlc->namaDlc << " (ID: " << dlc->idDlc << ")" << endl;
        return true;
    }

    return false;
}


void searchDlcInGame(Game *game)
{
    cout << "Pilih metode pencarian DLC:\n1. Fibonacci Search\n2. Jump Search\nPilih metode: ";
    string choice;
    cin >> choice;
    cin.ignore();

    int keyword;
    cout << "Masukkan keyword pencarian DLC: ";
    cin >> keyword;

    bool found = false;
    if (choice == "1")
    {
        found = fibonacciSearchDlcLinked(game->dlcHead, keyword);
    }
    else if (choice == "2")
    {
        found = jumpSearchDlcLinked(game->dlcHead, keyword);
    }
    else
    {
        cout << "Pilihan tidak valid." << endl;
        return;
    }

    if (!found)
    {
        cout << "Tidak ditemukan DLC dengan keyword: \"" << keyword << "\"." << endl;
    }
}

void displayDlc(Game *game)
{
    if (game->dlcHead == nullptr)
    {
        cout << "Game " << game->nama << " tidak memiliki dlc." << endl;
        return;
    }

    GameDlc *tempDlc = game->dlcHead;
    while (tempDlc != nullptr)
    {
        cout << "DLC: " << tempDlc->namaDlc << " (ID: " << tempDlc->idDlc << ")" << endl;
        tempDlc = tempDlc->next;
    }
}


void badCharHeuristic(const string &str, int badChar[256])
{
    int m = str.size();
    for (int i = 0; i < 256; i++)
    {
        badChar[i] = -1;
    }
    for (int i = 0; i < m; i++)
    {
        badChar[(int)str[i]] = i;
    }
}


bool boyerMooreSearch(const string &text, const string &pattern)
{
    int n = text.size();
    int m = pattern.size();
    int badChar[256];

    badCharHeuristic(pattern, badChar);

    int s = 0; 
    while (s <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j])
        {
            j--;
        }

        if (j < 0)
        {
            return true;
            s += (s + m < n) ? m - badChar[text[s + m]] : 1;
        }
        else
        {
            s += max(1, j - badChar[text[s + j]]);
        }
    }
    return false;
}

void searchGame(const string &keyword)
{
    Game *tempGame = headGame;
    bool found = false;
    while (tempGame != nullptr)
    {
        if (boyerMooreSearch(tempGame->nama, keyword))
        {
            cout << "Game ditemukan: " << tempGame->nama << " (ID: " << tempGame->id << ")" << endl;
            found = true;
        }
        tempGame = tempGame->next;
    }

    if (!found)
    {
        cout << "tidak ada game yang ditemukan dengan nama \"" << keyword << "\"." << endl;
    }
}

void hapusSemuaDlc(Game *&game)
{
    GameDlc *dlc = game->dlcHead;
    while (dlc != nullptr)
    {
        GameDlc *temp = dlc;
        dlc = dlc->next;
        delete temp;
    }
    game->dlcHead = nullptr;
    game->dlcTail = nullptr;
}

void dequeueDlc(Game *&game)
{
    if (game->dlcHead == nullptr)
    {
        cout << "Dlc belum ditambahkan" << endl;
        return;
    }
    GameDlc *temp = game->dlcHead;
    game->dlcHead = game->dlcHead->next;

    if (game->dlcHead == nullptr)
    {
        game->dlcTail = nullptr;
    }

    cout << "DLC " << temp->namaDlc << " dihapus dari game " << game->nama << endl;
    delete temp;
}


Game *split(Game *head)
{
    Game *fast = head;
    Game *slow = head;
    Game *prev = nullptr;

    while (fast && fast->next)
    {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    if (prev)
    {
        prev->next = nullptr;
    }

    return slow;
}


Game *mergeSortedLists(Game *left, Game *right)
{
    if (!left)
        return right;
    if (!right)
        return left;

    Game *result = nullptr;

    if (left->id < right->id)
    {
        result = left;
        result->next = mergeSortedLists(left->next, right);
    }
    else
    {
        result = right;
        result->next = mergeSortedLists(left, right->next);
    }

    return result;
}


Game *mergeSortedListsDescending(Game *left, Game *right)
{
    if (!left)
        return right;
    if (!right)
        return left;

    Game *result = nullptr;

    
    if (left->id > right->id)
    {
        result = left;
        result->next = mergeSortedListsDescending(left->next, right);
    }
    else
    {
        result = right;
        result->next = mergeSortedListsDescending(left, right->next);
    }

    return result;
}


Game *mergeSortGames(Game *head)
{
    if (!head || !head->next)
    {
        return head;
    }

    Game *mid = split(head);
    Game *left = mergeSortGames(head);
    Game *right = mergeSortGames(mid);

    return mergeSortedLists(left, right);
}


Game *mergeSortGamesDescending(Game *head)
{
    if (!head || !head->next)
    {
        return head;
    }

    Game *mid = split(head);
    Game *left = mergeSortGamesDescending(head);
    Game *right = mergeSortGamesDescending(mid);

    return mergeSortedListsDescending(left, right);
}


void sortGames()
{
    headGame = mergeSortGames(headGame);
    cout << "Game telah di sorting berdasarkan ID." << endl;
}


void sortGamesDescending()
{
    headGame = mergeSortGamesDescending(headGame);
    cout << "Game telah di sorting berdasarkan ID secara descending." << endl;
}


Game *mergeSortedListsByName(Game *left, Game *right)
{
    if (!left)
        return right;
    if (!right)
        return left;

    Game *result = nullptr;

    if (left->nama < right->nama)
    {
        result = left;
        result->next = mergeSortedListsByName(left->next, right);
    }
    else
    {
        result = right;
        result->next = mergeSortedListsByName(left, right->next);
    }

    return result;
}


Game *mergeSortedListsByNameDescending(Game *left, Game *right)
{
    if (!left)
        return right;
    if (!right)
        return left;

    Game *result = nullptr;

    if (left->nama > right->nama)
    {
        result = left;
        result->next = mergeSortedListsByNameDescending(left->next, right);
    }
    else
    {
        result = right;
        result->next = mergeSortedListsByNameDescending(left, right->next);
    }

    return result;
}


Game *mergeSortGamesByName(Game *head)
{
    if (!head || !head->next)
    {
        return head;
    }

    Game *mid = split(head);
    Game *left = mergeSortGamesByName(head);
    Game *right = mergeSortGamesByName(mid);

    return mergeSortedListsByName(left, right);
}


Game *mergeSortGamesByNameDescending(Game *head)
{
    if (!head || !head->next)
    {
        return head;
    }

    Game *mid = split(head);
    Game *left = mergeSortGamesByNameDescending(head);
    Game *right = mergeSortGamesByNameDescending(mid);

    return mergeSortedListsByNameDescending(left, right);
}


void sortGamesByName()
{
    headGame = mergeSortGamesByName(headGame);
    cout << "Game telah disorting berdasarkan nama secara ascending." << endl;
}


void sortGamesByNameDescending()
{
    headGame = mergeSortGamesByNameDescending(headGame);
    cout << "Game telah disorting berdasarkan nama secara descending." << endl;
}


GameDlc *getTail(GameDlc *cur)
{
    while (cur != nullptr && cur->next != nullptr)
        cur = cur->next;
    return cur;
}


GameDlc *partitionIDAsc(GameDlc *head, GameDlc *end, GameDlc **newHead, GameDlc **newEnd)
{
    GameDlc *pivot = end;
    GameDlc *prev = nullptr, *cur = head, *tail = pivot;

    while (cur != pivot)
    {
        if (cur->idDlc < pivot->idDlc)
        {
            if ((*newHead) == nullptr)
                (*newHead) = cur;
            prev = cur;
            cur = cur->next;
        }
        else
        {
            if (prev)
                prev->next = cur->next;
            GameDlc *temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if ((*newHead) == nullptr)
        (*newHead) = pivot;
    (*newEnd) = tail;
    return pivot;
}


GameDlc *quickSortRecurIDAsc(GameDlc *head, GameDlc *end)
{
    if (!head || head == end)
        return head;

    GameDlc *newHead = nullptr, *newEnd = nullptr;
    GameDlc *pivot = partitionIDAsc(head, end, &newHead, &newEnd);

    if (newHead != pivot)
    {
        GameDlc *temp = newHead;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = nullptr;

        newHead = quickSortRecurIDAsc(newHead, temp);
        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRecurIDAsc(pivot->next, newEnd);
    return newHead;
}

void quickSortIDAsc(Game *game)
{
    if (!game || !game->dlcHead)
        return;
    game->dlcHead = quickSortRecurIDAsc(game->dlcHead, getTail(game->dlcHead));
    displayDlc(game);
}


GameDlc *partitionIDDesc(GameDlc *head, GameDlc *end, GameDlc **newHead, GameDlc **newEnd)
{
    GameDlc *pivot = end;
    GameDlc *prev = nullptr, *cur = head, *tail = pivot;

    while (cur != pivot)
    {
        if (cur->idDlc > pivot->idDlc)
        {
            if ((*newHead) == nullptr)
                (*newHead) = cur;
            prev = cur;
            cur = cur->next;
        }
        else
        {
            if (prev)
                prev->next = cur->next;
            GameDlc *temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if ((*newHead) == nullptr)
        (*newHead) = pivot;
    (*newEnd) = tail;
    return pivot;
}

GameDlc *quickSortRecurIDDesc(GameDlc *head, GameDlc *end)
{
    if (!head || head == end)
        return head;

    GameDlc *newHead = nullptr, *newEnd = nullptr;
    GameDlc *pivot = partitionIDDesc(head, end, &newHead, &newEnd);

    if (newHead != pivot)
    {
        GameDlc *temp = newHead;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = nullptr;

        newHead = quickSortRecurIDDesc(newHead, temp);
        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRecurIDDesc(pivot->next, newEnd);
    return newHead;
}

void quickSortIDDesc(Game *game)
{
    if (!game || !game->dlcHead)
        return;
    game->dlcHead = quickSortRecurIDDesc(game->dlcHead, getTail(game->dlcHead));
    displayDlc(game);
}

/
GameDlc *partitionNamaAsc(GameDlc *head, GameDlc *end, GameDlc **newHead, GameDlc **newEnd)
{
    GameDlc *pivot = end;
    GameDlc *prev = nullptr, *cur = head, *tail = pivot;

    while (cur != pivot)
    {
        if (cur->namaDlc < pivot->namaDlc)
        {
            if ((*newHead) == nullptr)
                (*newHead) = cur;
            prev = cur;
            cur = cur->next;
        }
        else
        {
            if (prev)
                prev->next = cur->next;
            GameDlc *temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if ((*newHead) == nullptr)
        (*newHead) = pivot;
    (*newEnd) = tail;
    return pivot;
}


GameDlc *quickSortRecurNamaAsc(GameDlc *head, GameDlc *end)
{
    if (!head || head == end)
        return head;

    GameDlc *newHead = nullptr, *newEnd = nullptr;
    GameDlc *pivot = partitionNamaAsc(head, end, &newHead, &newEnd);

    if (newHead != pivot)
    {
        GameDlc *temp = newHead;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = nullptr;

        newHead = quickSortRecurNamaAsc(newHead, temp);
        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRecurNamaAsc(pivot->next, newEnd);
    return newHead;
}

void quickSortNamaAsc(Game *game)
{
    if (!game || !game->dlcHead)
        return;
    game->dlcHead = quickSortRecurNamaAsc(game->dlcHead, getTail(game->dlcHead));
    displayDlc(game);
}


GameDlc *partitionNamaDesc(GameDlc *head, GameDlc *end, GameDlc **newHead, GameDlc **newEnd)
{
    GameDlc *pivot = end;
    GameDlc *prev = nullptr, *cur = head, *tail = pivot;

    while (cur != pivot)
    {
        if (cur->namaDlc > pivot->namaDlc)
        {
            if ((*newHead) == nullptr)
                (*newHead) = cur;
            prev = cur;
            cur = cur->next;
        }
        else
        {
            if (prev)
                prev->next = cur->next;
            GameDlc *temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if ((*newHead) == nullptr)
        (*newHead) = pivot;
    (*newEnd) = tail;
    return pivot;
}

GameDlc *quickSortRecurNamaDesc(GameDlc *head, GameDlc *end)
{
    if (!head || head == end)
        return head;

    GameDlc *newHead = nullptr, *newEnd = nullptr;
    GameDlc *pivot = partitionNamaDesc(head, end, &newHead, &newEnd);

    if (newHead != pivot)
    {
        GameDlc *temp = newHead;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = nullptr;

        newHead = quickSortRecurNamaDesc(newHead, temp);
        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRecurNamaDesc(pivot->next, newEnd);
    return newHead;
}

void quickSortNamaDesc(Game *game)
{
    if (!game || !game->dlcHead)
        return;
    game->dlcHead = quickSortRecurNamaDesc(game->dlcHead, getTail(game->dlcHead));
    displayDlc(game);
}

void sortDlcGamesMenu(Game *game)
{
    while (true)
    {
        string pilih;
        cout << "1. Sort berdasarkan ID\n"
                "2. Sort berdasarkan Nama\n"
                "3. Kembali\n"
                "Pilih >>";
        cin >> pilih;
        if (pilih == "1")
        {
            while (true)
            {
                cout << "Sort berdasarkan ID\n"
                        "1. Ascending\n"
                        "2. Descending\n"
                        "3. Kembali\n"
                        "Pilih >>";
                cin >> pilih;
                if (pilih == "1")
                {
                    quickSortIDAsc(game);
                    continue;
                }
                else if (pilih == "2")
                {
                    quickSortIDDesc(game);
                    continue;
                }
                else if (pilih == "3")
                {
                    break;
                }
                else
                {
                    cout << "Pilihan tidak ditemukan" << endl;
                    continue;
                }
            }
        }
        else if (pilih == "2")
        {
            while (true)
            {
                cout << "Sort berdasarkan Nama\n"
                        "1. Ascending\n"
                        "2. Descending\n"
                        "3. Kembali\n"
                        "Pilih >>";
                cin >> pilih;
                if (pilih == "1")
                {
                    quickSortNamaAsc(game);
                    continue;
                }
                else if (pilih == "2")
                {
                    quickSortNamaDesc(game);
                    continue;
                }
                else if (pilih == "3")
                {
                    break;
                }
                else
                {
                    cout << "Pilihan tidak ditemukan" << endl;
                    continue;
                }
            }
        }
        else if (pilih == "3")
        {
            break;
        }
        else
        {
            cout << "Pilihan tidak ditemukan" << endl;
            continue;
        }
    }
}

void sortGamesMenu()
{
    string pilih;
    cout << "1. Sort berdasarkan ID\n"
            "2. Sort berdasarkan Nama\n"
            "3. Kembali\n"
            "Pilih >>";
    cin >> pilih;
    do
    {
        if (pilih == "1")
        {
            cout << "Sort berdasarkan ID\n"
                    "1. Ascending\n"
                    "2. Descending\n"
                    "3. Kembali\n"
                    "Pilih >>";
            cin >> pilih;
            do
            {
                if (pilih == "1")
                {
                    sortGames();
                    break;
                }
                else if (pilih == "2")
                {
                    sortGamesDescending();
                    break;
                }
                else
                {
                    cout << "Pilihan tidak ditemukan" << endl;
                    break;
                }
            } while (pilih != "3");
        }
        else if (pilih == "2")
        {
            cout << "Sort berdasarkan Nama\n"
                    "1. Ascending\n"
                    "2. Descending\n"
                    "3. Kembali\n"
                    "Pilih >>";
            cin >> pilih;
            do
            {
                if (pilih == "1")
                {
                    sortGamesByName();
                    break;
                }
                else if (pilih == "2")
                {
                    sortGamesByNameDescending();
                    break;
                }
                else
                {
                    cout << "Pilihan tidak ditemukan" << endl;
                    break;
                }
            } while (pilih != "3");
        }
        else
        {
            cout << "Pilihan tidak ditemukan" << endl;
            break;
        }
    } while (pilih != "3");
}

void editGame()
{
    displayGames();
    string id;
    string ulang = "y";
    cout << "Pilih id >>";
    cin >> id;

    Game *game = findGame(id);
    if (game == nullptr)
    {
        cout << "Game dengan ID " << id << " tidak ditemukan." << endl;
        return;
    }

    while (ulang == "y")
    {
        cout << "1. Ubah nama game\n"
                "2. Tambah DLC game\n"
                "3. Lihat DLC game\n"
                "4. Dequeue DLC game\n"
                "5. Cari DLC di game\n"
                "6. Sort DLC di game\n"
                "7. Kembali\n";

        string pilih;
        cout << "Pilih >>";
        cin >> pilih;
        if (pilih == "1")
        {
            ubahNamaGame(game);
        }
        else if (pilih == "2")
        {
            tambahDlc(game);
        }
        else if (pilih == "3")
        {
            displayDlc(game);
        }
        else if (pilih == "4")
        {
            dequeueDlc(game);
        }
        else if (pilih == "5")
        {
            searchDlcInGame(game);
        }
        else if (pilih == "6")
        {
            sortDlcGamesMenu(game);
        }
        else if (pilih == "7")
        {
            ulang = "t";
        }
        else
        {
            cout << "Pilihan tidak ditemukan" << endl;
        }
    }
}

void awal()
{
    string pilih;
    do
    {
        cout << "1. Tambah Game\n"
                "2. Lihat Game\n"
                "3. Pilih Game\n"
                "4. Pop Game\n"
                "5. Cari Game\n"
                "6. Sort Game\n"
                "7. Keluar\n";

        cout << "Pilih >> ";
        cin >> pilih;

        if (pilih == "1")
        {
            tambahGame();
        }
        else if (pilih == "2")
        {
            displayGames();
        }
        else if (pilih == "3")
        {
            editGame();
        }
        else if (pilih == "4")
        {
            pop();
        }
        else if (pilih == "5")
        {
            cin.ignore();
            string keyword;
            cout << "Masukkan keyword pencarian: ";
            getline(cin, keyword);
            searchGame(keyword);
        }
        else if (pilih == "6")
        {
            sortGamesMenu();
        }
        else
        {
            cout << "Pilihan tidak ada" << endl;
        }
    } while (pilih != "7");
    cout << "Berhasil Keluar" << endl;
}

int main()
{
    
    pushGame("1", "Halo Infinite");
    pushGame("2", "Cyberpunk 2077");

    
    enqueueDlcToGame("1", 1, "Campaign Expansion");
    enqueueDlcToGame("1", 2, "Multiplayer Update");
    enqueueDlcToGame("2", 1, "Night City Expansion");

    awal();
    return 0;
}
