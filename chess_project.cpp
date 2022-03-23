#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// NOTES:
// 1. King must be the only Piece that have value == 6;
// 2. If you want to see when Objects are constructing uncomment respective comments in the code;
// 3. In function play_game() you can choose type of players

//================================technical=====================================

enum Color{white, black};

struct Position{
    int x; //column
    int y; //row
};

// print_pos prints position in system {[0..7],[0..7]} as position in system letter_number (i.e. print_pos({0,3}) should print A4)
void print_pos(Position p){
    switch(p.x){
        case 0:
            cout << "A";
            break;
        case 1:
            cout << "B";
            break;
        case 2:
            cout << "C";
            break;
        case 3:
            cout << "D";
            break;
        case 4:
            cout << "E";
            break;
        case 5:
            cout << "F";
            break;
        case 6:
            cout << "G";
            break;
        case 7:
            cout << "H";
            break;
        default:
            cout << "Invalid position x!";


    }

    if(p.y > 7 or p.y <0){cout << "Invalid position y!";}
    else{cout << p.y + 1;}


}


//===============================Table_of_moves=================================

// Table_of_moves is data structure that keeps moves, add method adds a move, addtab add

class Table_of_moves{
    friend class Player;
private:
    Position* start_tab;
    Position* target_tab;
    int* value_tab;
    int length_of_tab;
    int num_of_moves;
public:
    //accessors
    int get_value_tab(int);
    int get_num_of_moves();
    Position get_start_tab(int);
    Position get_target_tab(int);
    //API
    void add(Position, Position, int);
    void addtab(Table_of_moves*);
    void print_table_of_moves();
    //technical
    Table_of_moves();
    ~Table_of_moves();
    Table_of_moves(const Table_of_moves&);
    Table_of_moves& operator=(const Table_of_moves&) = delete;
};

Table_of_moves::Table_of_moves(){
    length_of_tab = 4;
    num_of_moves = 0;
    //cout << "Table constructed!" << endl;
    start_tab = new Position[length_of_tab];
    target_tab = new Position[length_of_tab];
    value_tab = new int[length_of_tab];
}
Table_of_moves::~Table_of_moves(){
    delete [] start_tab;
    delete [] target_tab;
    delete [] value_tab;
    //cout << "Table destructed!" << endl;

}
Table_of_moves::Table_of_moves(const Table_of_moves& t){
    length_of_tab = t.length_of_tab;
    num_of_moves = t.num_of_moves;
    start_tab = new Position[length_of_tab];
    for(int i=0; i<num_of_moves; i++){
        start_tab[i] = t.start_tab[i];
    }
    target_tab = new Position[length_of_tab];
    for(int i=0; i<num_of_moves; i++){
        target_tab[i] = t.target_tab[i];
    }
    value_tab = new int[length_of_tab];
    for(int i=0; i<num_of_moves; i++){
        value_tab[i] = t.value_tab[i];
    }
}

void Table_of_moves::add(Position start, Position target, int target_value){
    // if there's no free space in the table we must create new table:
    if(num_of_moves == length_of_tab){
        Position* start_tab_aux = new Position[2*length_of_tab];
        Position* target_tab_aux = new Position[2*length_of_tab];
        int* value_tab_aux = new int[2*length_of_tab];
        for(int i=0; i<length_of_tab; i++){
            start_tab_aux[i] = start_tab[i];
            target_tab_aux[i] = target_tab[i];
            value_tab_aux[i] = value_tab[i];
        }
        delete [] start_tab;
        delete [] target_tab;
        delete [] value_tab;
        start_tab = start_tab_aux;
        target_tab = target_tab_aux;
        value_tab = value_tab_aux;
        length_of_tab*=2;
    }

    start_tab[num_of_moves] = start;
    target_tab[num_of_moves] = target;
    value_tab[num_of_moves] = target_value;
    num_of_moves++;
    //cout << "num of moves: " << num_of_moves << ", length of tab: " << length_of_tab << endl;
}
void Table_of_moves::addtab(Table_of_moves* tab){
    for(int i=0; i<tab->num_of_moves; i++){
        add(tab->start_tab[i], tab->target_tab[i], tab->value_tab[i]);
    }
}
void Table_of_moves::print_table_of_moves(){
    for(int i=0; i<num_of_moves; i++){
        cout << i+1 << ": ";
        print_pos(start_tab[i]);
        cout << " -> ";
        print_pos(target_tab[i]);
        cout << ", val:" << value_tab[i] << endl;
    }
}
int Table_of_moves::get_value_tab(int i){
    return value_tab[i];
}
int Table_of_moves::get_num_of_moves(){
    return num_of_moves;
}
Position Table_of_moves::get_start_tab(int i){
    return start_tab[i];
}
Position Table_of_moves::get_target_tab(int i){
    return target_tab[i];
}

//==============================base=class=Piece================================

class Piece{
protected:
    Position pos;
    int val;
    Color col;
public:
    //accessors
    Color getColor();
    int getValue();
    //API
    virtual void print_piece() = 0;
    void Move(Position p);
    virtual Table_of_moves* moves() = 0;

    //technical
    Piece() = delete;
    Piece(Color, Position);
    virtual ~Piece();
    Piece(const Piece&) = delete;
    Piece& operator=(const Piece&) = delete;
};

Piece::Piece(Color c, Position p){
    col = c;
    pos = p;
    //cout << "Piece created" << endl;
}
Piece::~Piece(){
    //cout << "Piece destroyed" << endl;
}
void Piece::Move(Position p){
        pos = p;
}
Color Piece::getColor(){
    return col;
}
int Piece::getValue(){
    return val;
}

//============================derived=classes=Piece=============================

class Pawn: public Piece{
public:
    void print_piece();
    Table_of_moves* moves();
    //technical
    Pawn() = delete;
    Pawn(Color, Position);
    ~Pawn();
    Pawn(const Pawn&) = delete;
    Pawn& operator=(const Pawn&) = delete;
};
class Knight: public Piece{
public:
    void print_piece();
    Table_of_moves* moves();
    //technical
    Knight() = delete;
    Knight(Color, Position);
    ~Knight();
    Knight(const Knight&) = delete;
    Knight& operator=(const Knight&) = delete;
};
class Bishop: public Piece{
public:
    void print_piece();
    Table_of_moves* moves();
    //technical
    Bishop() = delete;
    Bishop(Color, Position);
    ~Bishop();
    Bishop(const Bishop&) = delete;
    Bishop& operator=(const Bishop&) = delete;
};
class Rook: public Piece{
public:
    void print_piece();
    Table_of_moves* moves();
    //technical
    Rook() = delete;
    Rook(Color, Position);
    ~Rook();
    Rook(const Rook&) = delete;
    Rook& operator=(const Rook&) = delete;
};
class Queen: public Piece{
public:
    void print_piece();
    Table_of_moves* moves();
    //technical
    Queen() = delete;
    Queen(Color, Position);
    ~Queen();
    Queen(const Queen&) = delete;
    Queen& operator=(const Queen&) = delete;
};
class King: public Piece{
public:
    void print_piece();
    Table_of_moves* moves();
    //technical
    King() = delete;
    King(Color, Position);
    ~King();
    King(const King&) = delete;
    King& operator=(const King&) = delete;
};

// Pawn
Pawn::Pawn(Color c, Position p) : Piece(c,p) {
    val = 1; //cout << "Pawn created" << endl;
}
Pawn::~Pawn(){
    //cout << "Pawn destroyed" << endl;
}
void Pawn::print_piece(){
        if (col == white) cout << "P";
        else cout << "p";
}
// Knight
Knight::Knight(Color c, Position p) : Piece(c,p){
    val = 2;  //cout << "Knight created" << endl;
}
Knight::~Knight(){
    //cout << "Knight destroyed" << endl;
}
void Knight::print_piece(){
        if (col == white) {cout << "N";}
        else {cout << "n";}
}
//Bishop
Bishop::Bishop(Color c, Position p) : Piece(c,p){
    val = 3;  //cout << "Bishop created" << endl;
}
Bishop::~Bishop(){
    //cout << "Bishop destroyed" << endl;
}
void Bishop::print_piece(){
        if (col == white) {cout << "B";}
        else {cout << "b";}
}
//Rook
Rook::Rook(Color c, Position p) : Piece(c,p) {
    val = 4;  //cout << "Rook created" << endl;
}
Rook::~Rook(){
    //cout << "Rook destroyed" << endl;
}
void Rook::print_piece(){
        if (col == white) {cout << "R";}
        else {cout << "r";}
}
//Queen
Queen::Queen(Color c, Position p) : Piece(c,p){
    val = 5;  //cout << "Queen created" << endl;
}
Queen::~Queen(){
    //cout << "Queen destroyed" << endl;
}
void Queen::print_piece(){
        if (col == white) {cout << "Q";}
        else {cout << "q";}
}
//King
King::King(Color c, Position p) : Piece(c,p){
    val = 6;  //cout << "King created" << endl;
}
King::~King(){
    //cout << "King destroyed" << endl;
}
void King::print_piece(){
        if (col == white) {cout << "K";}
        else {cout << "k";}
}


//==================================board=======================================

Piece* Chessboard[8][8];



void ini_board(){
    //pawnes:
    for(int i=0; i<8; i++){
        Chessboard[i][6] = new Pawn(white, {i, 6});
        Chessboard[i][1] = new Pawn(black, {i, 1});
    }



    //knights:
    Chessboard[1][7] = new Knight(white, {1, 7});
    Chessboard[6][7] = new Knight(white, {6, 7});
    Chessboard[1][0] = new Knight(black, {1, 0});
    Chessboard[6][0] = new Knight(black, {6, 0});

    //bishops:
    Chessboard[2][7] = new Bishop(white, {2, 7});
    Chessboard[5][7] = new Bishop(white, {5, 7});
    Chessboard[2][0] = new Bishop(black, {2, 0});
    Chessboard[5][0] = new Bishop(black, {5, 0});

    //rooks:
    Chessboard[0][7] = new Rook(white, {0, 7});
    Chessboard[7][7] = new Rook(white, {7, 7});
    Chessboard[0][0] = new Rook(black, {0, 0});
    Chessboard[7][0] = new Rook(black, {7, 0});

    //queens:
    Chessboard[3][7] = new Queen(white, {3, 7});
    Chessboard[3][0] = new Queen(black, {3, 0});

    //Kings:
    Chessboard[4][7] = new King(white, {4, 7});
    Chessboard[4][0] = new King(black, {4, 0});

    //null areas:
    for(int j=2; j<6; j++){
        for(int i=0; i<6; i++){
            Chessboard[i][j] = nullptr;
        }
    }
}


// destruct_board() destructs pieces!

void destruct_board(){
    for(int j=0; j<8; j++){
        for(int i=0; i<8; i++){
            if(Chessboard[i][j] != nullptr){
                delete Chessboard[i][j];
            }
        }
    }
}
void print_board(){
//    cout << "\n";
//    cout << "Chessboard: \n";
    cout << "___________________________\n";
    cout << "|                         |\n";
    cout << "|     A B C D E F G H     |\n";
    cout << "|                         |\n";
    for(int j=0; j<8; j++){
        cout << "| "<< j+1 << "   ";
        for(int i=0; i<8; i++){
            if(Chessboard[i][j] == nullptr){cout << "." << " ";}
            else{
                Chessboard[i][j]->print_piece();
                cout << " ";
            }
        }
        cout << "  " << j+1 << " |" << "\n";
    }
    cout << "|                         |\n";
    cout << "|     A B C D E F G H     |\n";
    cout << "|_________________________|\n";
    cout << "\n";
}





Table_of_moves* Pawn::moves(){
    Table_of_moves* t = new Table_of_moves();
    // white pawn:
    if(col == white){
        // one-step move forward
        if(pos.y > 0 and Chessboard[pos.x][pos.y - 1] == nullptr){
            t->add(pos, {pos.x, pos.y - 1}, 0);
            // two-step move forward; it's possible if and only if the pawn is set on position {pos.x, 6}
            // and the the position uppon it is free (condition is satisfied see upper)
            if(pos.y == 6 and Chessboard[pos.x][pos.y - 2] == nullptr){
                t->add(pos, {pos.x, pos.y - 2}, 0);
            }
        }
        // capturing
        // right up diagonally capturing
        if(pos.x < 7 and pos.y > 0 and Chessboard[pos.x + 1][pos.y - 1] != nullptr){
            if(Chessboard[pos.x + 1][pos.y - 1]->getColor() == black){
                t->add(pos, {pos.x + 1, pos.y - 1}, Chessboard[pos.x + 1][pos.y - 1]->getValue());
            }
        }
        // left up diagonally capturing
        if(pos.x > 0 and pos.y > 0 and Chessboard[pos.x - 1][pos.y - 1] != nullptr){
            if(Chessboard[pos.x - 1][pos.y - 1]->getColor() == black){
                t->add(pos, {pos.x - 1, pos.y - 1}, Chessboard[pos.x - 1][pos.y - 1]->getValue());
            }
        }
    }


    // black pawn:
    else{
        // one-step move forward
        if(pos.y < 7 and Chessboard[pos.x][pos.y + 1] == nullptr){
            t->add(pos, {pos.x, pos.y + 1}, 0);
            // two-step move forward; it's possible if and only if the pawn is set on position {pos.x, 6}
            // and the the position uppon it is free (condition is satisfied see upper)
            if(pos.y == 1 and Chessboard[pos.x][pos.y + 2] == nullptr){
                t->add(pos, {pos.x, pos.y + 2}, 0);
            }
        }
        // capturing
        // right down diagonally capturing
        if(pos.x < 7 and pos.y < 7 and Chessboard[pos.x + 1][pos.y + 1] != nullptr){
            if(Chessboard[pos.x + 1][pos.y + 1]->getColor() == white){
                t->add(pos, {pos.x + 1, pos.y + 1}, Chessboard[pos.x + 1][pos.y + 1]->getValue());
            }
        }
        // left down diagonally capturing
        if(pos.x > 0 and pos.y < 7 and Chessboard[pos.x - 1][pos.y + 1] != nullptr){
            if(Chessboard[pos.x - 1][pos.y + 1]->getColor() == white){
                t->add(pos, {pos.x - 1, pos.y + 1}, Chessboard[pos.x - 1][pos.y + 1]->getValue());
            }
        }
    }


    return t;
}
Table_of_moves* Knight::moves(){
    Table_of_moves* t = new Table_of_moves();
    // there's eight moves of knights; the 1st is right and 2xup move, further clockwise: 2nd 2xright and up etc.
    // no1
    if(pos.x < 7 and pos.y > 1){
        // move without capturing
        if(Chessboard[pos.x + 1][pos.y - 2] == nullptr){
            t->add(pos, {pos.x + 1, pos.y - 2}, 0);
        }
        else if(Chessboard[pos.x + 1][pos.y - 2]->getColor() != col){
            t->add(pos, {pos.x + 1, pos.y - 2}, Chessboard[pos.x + 1][pos.y - 2]->getValue());
        }
    }

    // no2
    if(pos.x < 6 and pos.y > 0){
        // move without capturing
        if(Chessboard[pos.x + 2][pos.y - 1] == nullptr){
            t->add(pos, {pos.x + 2, pos.y - 1}, 0);
        }
        else if(Chessboard[pos.x + 2][pos.y - 1]->getColor() != col){
            t->add(pos, {pos.x + 2, pos.y - 1}, Chessboard[pos.x + 2][pos.y - 1]->getValue());
        }
    }

    // no3
    if(pos.x < 6 and pos.y < 7){
        // move without capturing
        if(Chessboard[pos.x + 2][pos.y + 1] == nullptr){
            t->add(pos, {pos.x + 2, pos.y + 1}, 0);
        }
        else if(Chessboard[pos.x + 2][pos.y + 1]->getColor() != col){
            t->add(pos, {pos.x + 2, pos.y + 1}, Chessboard[pos.x + 2][pos.y + 1]->getValue());
        }
    }

    // no4
    if(pos.x < 7 and pos.y < 6){
        // move without capturing
        if(Chessboard[pos.x + 1][pos.y + 2] == nullptr){
            t->add(pos, {pos.x + 1, pos.y + 2}, 0);
        }
        else if(Chessboard[pos.x + 1][pos.y + 2]->getColor() != col){
            t->add(pos, {pos.x + 1, pos.y + 2}, Chessboard[pos.x + 1][pos.y + 2]->getValue());
        }
    }

    // no5
    if(pos.x > 0 and pos.y < 6){
        // move without capturing
        if(Chessboard[pos.x - 1][pos.y + 2] == nullptr){
            t->add(pos, {pos.x - 1, pos.y + 2}, 0);
        }
        else if(Chessboard[pos.x - 1][pos.y + 2]->getColor() != col){
            t->add(pos, {pos.x - 1, pos.y + 2}, Chessboard[pos.x - 1][pos.y + 2]->getValue());
        }
    }

    // no6
    if(pos.x > 1 and pos.y < 7){
        // move without capturing
        if(Chessboard[pos.x - 2][pos.y + 1] == nullptr){
            t->add(pos, {pos.x - 2, pos.y + 1}, 0);
        }
        else if(Chessboard[pos.x - 2][pos.y + 1]->getColor() != col){
            t->add(pos, {pos.x - 2, pos.y + 1}, Chessboard[pos.x - 2][pos.y + 1]->getValue());
        }
    }

    // no7
    if(pos.x > 1 and pos.y > 0){
        // move without capturing
        if(Chessboard[pos.x - 2][pos.y - 1] == nullptr){
            t->add(pos, {pos.x - 2, pos.y - 1}, 0);
        }
        else if(Chessboard[pos.x - 2][pos.y - 1]->getColor() != col){
            t->add(pos, {pos.x - 2, pos.y - 1}, Chessboard[pos.x - 2][pos.y - 1]->getValue());
        }
    }

    // no8
    if(pos.x > 0 and pos.y > 1){
        // move without capturing
        if(Chessboard[pos.x - 1][pos.y - 2] == nullptr){
            t->add(pos, {pos.x - 1, pos.y - 2}, 0);
        }
        else if(Chessboard[pos.x - 1][pos.y - 2]->getColor() != col){
            t->add(pos, {pos.x - 1, pos.y - 2}, Chessboard[pos.x - 1][pos.y - 2]->getValue());
        }
    }
    return t;
}
Table_of_moves* Bishop::moves(){
    Table_of_moves* t = new Table_of_moves();
    // see Table_of_moves* Rook::moves();
    // right up move
    // cond = true if there's no piece on path of bishop on some moment
    bool cond = true;
    int i = 1;
    do{
        if(pos.x+i < 8 and pos.y-i > -1){
            if(Chessboard[pos.x+i][pos.y-i] == nullptr){
                t->add(pos, {pos.x+i, pos.y-i}, 0);
            }
            else{
                if(Chessboard[pos.x+i][pos.y-i]->getColor() != col){
                    t->add(pos, {pos.x+i, pos.y-i}, Chessboard[pos.x+i][pos.y-i]->getValue());
                }
                cond = false;
            }
        }
        else{
            cond = false;
        }
        i++;
    } while(cond);

    // right down move
    cond = true;
    i = 1;
    do{
        if(pos.x+i < 8 and pos.y+i < 8){
            if(Chessboard[pos.x+i][pos.y+i] == nullptr){
                t->add(pos, {pos.x+i, pos.y+i}, 0);
            }
            else{
                if(Chessboard[pos.x+i][pos.y+i]->getColor() != col){
                    t->add(pos, {pos.x+i, pos.y+i}, Chessboard[pos.x+i][pos.y+i]->getValue());
                }
                cond = false;
            }
        }
        else{
            cond = false;
        }
        i++;
    } while(cond);

    // left down move
    cond = true;
    i = 1;
    do{
        if(pos.x-i > -1 and pos.y+i < 8){
            if(Chessboard[pos.x-i][pos.y+i] == nullptr){
                t->add(pos, {pos.x-i, pos.y+i}, 0);
            }
            else{
                if(Chessboard[pos.x-i][pos.y+i]->getColor() != col){
                    t->add(pos, {pos.x-i, pos.y+i}, Chessboard[pos.x-i][pos.y+i]->getValue());
                }
                cond = false;
            }
        }
        else{
            cond = false;
        }
        i++;
    } while(cond);

    // left up move
    cond = true;
    i = 1;
    do{
        if(pos.x-i > -1 and pos.y-i > -1){
            if(Chessboard[pos.x-i][pos.y-i] == nullptr){
                t->add(pos, {pos.x-i, pos.y-i}, 0);
            }
            else{
                if(Chessboard[pos.x-i][pos.y-i]->getColor() != col){
                    t->add(pos, {pos.x-i, pos.y-i}, Chessboard[pos.x-i][pos.y-i]->getValue());
                }
                cond = false;
            }
        }
        else{
            cond = false;
        }
        i++;
    } while(cond);

    return t;
}
Table_of_moves* Rook::moves(){
    Table_of_moves* t = new Table_of_moves();
    // see Table_of_moves* Bishop::moves();

    // up move
    // cond = true if there's no piece on path of rook on some moment
    bool cond = true;
    int i = 1;
    do{
        if(pos.y-i > -1){
            if(Chessboard[pos.x][pos.y-i] == nullptr){
                t->add(pos, {pos.x, pos.y-i}, 0);
            }
            else{
                if(Chessboard[pos.x][pos.y-i]->getColor() != col){
                    t->add(pos, {pos.x, pos.y-i}, Chessboard[pos.x][pos.y-i]->getValue());
                }
                cond = false;
            }
        }
        else{
            cond = false;
        }
        i++;
    } while(cond);

    // right move
    cond = true;
    i = 1;
    do{
        if(pos.x+i < 8){
            if(Chessboard[pos.x+i][pos.y] == nullptr){
                t->add(pos, {pos.x+i, pos.y}, 0);
            }
            else{
                if(Chessboard[pos.x+i][pos.y]->getColor() != col){
                    t->add(pos, {pos.x+i, pos.y}, Chessboard[pos.x+i][pos.y]->getValue());
                }
                cond = false;
            }
        }
        else{
            cond = false;
        }
        i++;
    } while(cond);

    // down move
    cond = true;
    i = 1;
    do{
        if(pos.y+i < 8){
            if(Chessboard[pos.x][pos.y+i] == nullptr){
                t->add(pos, {pos.x, pos.y+i}, 0);
            }
            else{
                if(Chessboard[pos.x][pos.y+i]->getColor() != col){
                    t->add(pos, {pos.x, pos.y+i}, Chessboard[pos.x][pos.y+i]->getValue());
                }
                cond = false;
            }
        }
        else{
            cond = false;
        }
        i++;
    } while(cond);

    // left move
    cond = true;
    i = 1;
    do{
        if(pos.x-i > -1){
            if(Chessboard[pos.x-i][pos.y] == nullptr){
                t->add(pos, {pos.x-i, pos.y}, 0);
            }
            else{
                if(Chessboard[pos.x-i][pos.y]->getColor() != col){
                    t->add(pos, {pos.x-i, pos.y}, Chessboard[pos.x-i][pos.y]->getValue());
                }
                cond = false;
            }
        }
        else{
            cond = false;
        }
        i++;
    } while(cond);

    return t;
}
Table_of_moves* Queen::moves(){
    // see Table_of_moves* Bishop::moves(); and Table_of_moves* Rook::moves();
    Table_of_moves* t = new Table_of_moves();

    // right up move
    // cond = true if there's no piece on path of queen on some moment
    bool cond = true;
    int i = 1;
    do{
        if(pos.x+i < 8 and pos.y-i > -1){
            if(Chessboard[pos.x+i][pos.y-i] == nullptr){
                t->add(pos, {pos.x+i, pos.y-i}, 0);
            }
            else{
                if(Chessboard[pos.x+i][pos.y-i]->getColor() != col){
                    t->add(pos, {pos.x+i, pos.y-i}, Chessboard[pos.x+i][pos.y-i]->getValue());
                }
                cond = false;
            }
        }
        else{
            cond = false;
        }
        i++;
    } while(cond);

    // right move
    cond = true;
    i = 1;
    do{
        if(pos.x+i < 8){
            if(Chessboard[pos.x+i][pos.y] == nullptr){
                t->add(pos, {pos.x+i, pos.y}, 0);
            }
            else{
                if(Chessboard[pos.x+i][pos.y]->getColor() != col){
                    t->add(pos, {pos.x+i, pos.y}, Chessboard[pos.x+i][pos.y]->getValue());
                }
                cond = false;
            }
        }
        else{
            cond = false;
        }
        i++;
    } while(cond);

    // right down move
    cond = true;
    i = 1;
    do{
        if(pos.x+i < 8 and pos.y+i < 8){
            if(Chessboard[pos.x+i][pos.y+i] == nullptr){
                t->add(pos, {pos.x+i, pos.y+i}, 0);
            }
            else{
                if(Chessboard[pos.x+i][pos.y+i]->getColor() != col){
                    t->add(pos, {pos.x+i, pos.y+i}, Chessboard[pos.x+i][pos.y+i]->getValue());
                }
                cond = false;
            }
        }
        else{
            cond = false;
        }
        i++;
    } while(cond);

    // down move
    cond = true;
    i = 1;
    do{
        if(pos.y+i < 8){
            if(Chessboard[pos.x][pos.y+i] == nullptr){
                t->add(pos, {pos.x, pos.y+i}, 0);
            }
            else{
                if(Chessboard[pos.x][pos.y+i]->getColor() != col){
                    t->add(pos, {pos.x, pos.y+i}, Chessboard[pos.x][pos.y+i]->getValue());
                }
                cond = false;
            }
        }
        else{
            cond = false;
        }
        i++;
    } while(cond);

    // left down move
    cond = true;
    i = 1;
    do{
        if(pos.x-i > -1 and pos.y+i < 8){
            if(Chessboard[pos.x-i][pos.y+i] == nullptr){
                t->add(pos, {pos.x-i, pos.y+i}, 0);
            }
            else{
                if(Chessboard[pos.x-i][pos.y+i]->getColor() != col){
                    t->add(pos, {pos.x-i, pos.y+i}, Chessboard[pos.x-i][pos.y+i]->getValue());
                }
                cond = false;
            }
        }
        else{
            cond = false;
        }
        i++;
    } while(cond);

    // left move
    cond = true;
    i = 1;
    do{
        if(pos.x-i > -1){
            if(Chessboard[pos.x-i][pos.y] == nullptr){
                t->add(pos, {pos.x-i, pos.y}, 0);
            }
            else{
                if(Chessboard[pos.x-i][pos.y]->getColor() != col){
                    t->add(pos, {pos.x-i, pos.y}, Chessboard[pos.x-i][pos.y]->getValue());
                }
                cond = false;
            }
        }
        else{
            cond = false;
        }
        i++;
    } while(cond);

    // left up move
    cond = true;
    i = 1;
    do{
        if(pos.x-i > -1 and pos.y-i > -1){
            if(Chessboard[pos.x-i][pos.y-i] == nullptr){
                t->add(pos, {pos.x-i, pos.y-i}, 0);
            }
            else{
                if(Chessboard[pos.x-i][pos.y-i]->getColor() != col){
                    t->add(pos, {pos.x-i, pos.y-i}, Chessboard[pos.x-i][pos.y-i]->getValue());
                }
                cond = false;
            }
        }
        else{
            cond = false;
        }
        i++;
    } while(cond);

    // up move
    cond = true;
    i = 1;
    do{
        if(pos.y-i > -1){
            if(Chessboard[pos.x][pos.y-i] == nullptr){
                t->add(pos, {pos.x, pos.y-i}, 0);
            }
            else{
                if(Chessboard[pos.x][pos.y-i]->getColor() != col){
                    t->add(pos, {pos.x, pos.y-i}, Chessboard[pos.x][pos.y-i]->getValue());
                }
                cond = false;
            }
        }
        else{
            cond = false;
        }
        i++;
    } while(cond);


    return t;
}
Table_of_moves* King::moves(){
    Table_of_moves* t = new Table_of_moves();

    // right up
    if(pos.x + 1 < 8 and pos.y - 1 > -1){
        if(Chessboard[pos.x + 1][pos.y - 1] == nullptr){
            t->add(pos, {pos.x + 1, pos.y - 1}, 0);
        }
        else if(Chessboard[pos.x + 1][pos.y - 1]->getColor() != col){
            t->add(pos, {pos.x + 1, pos.y - 1}, Chessboard[pos.x + 1][pos.y - 1]->getValue());
        }
    }

    // right
    if(pos.x + 1 < 8){
        if(Chessboard[pos.x + 1][pos.y] == nullptr){
            t->add(pos, {pos.x + 1, pos.y}, 0);
        }
        else if(Chessboard[pos.x + 1][pos.y]->getColor() != col){
            t->add(pos, {pos.x + 1, pos.y}, Chessboard[pos.x + 1][pos.y]->getValue());
        }
    }

    // right down
    if(pos.x + 1 < 8 and pos.y + 1 < 8){
        if(Chessboard[pos.x + 1][pos.y + 1] == nullptr){
            t->add(pos, {pos.x + 1, pos.y + 1}, 0);
        }
        else if(Chessboard[pos.x + 1][pos.y + 1]->getColor() != col){
            t->add(pos, {pos.x + 1, pos.y + 1}, Chessboard[pos.x + 1][pos.y + 1]->getValue());
        }
    }

    // down
    if(pos.y + 1 < 8){
        if(Chessboard[pos.x][pos.y + 1] == nullptr){
            t->add(pos, {pos.x, pos.y + 1}, 0);
        }
        else if(Chessboard[pos.x][pos.y + 1]->getColor() != col){
            t->add(pos, {pos.x, pos.y + 1}, Chessboard[pos.x][pos.y + 1]->getValue());
        }
    }

    // left down
    if(pos.x - 1 > -1 and pos.y + 1 < 8){
        if(Chessboard[pos.x - 1][pos.y + 1] == nullptr){
            t->add(pos, {pos.x - 1, pos.y + 1}, 0);
        }
        else if(Chessboard[pos.x - 1][pos.y + 1]->getColor() != col){
            t->add(pos, {pos.x - 1, pos.y + 1}, Chessboard[pos.x - 1][pos.y + 1]->getValue());
        }
    }

    // left
    if(pos.x - 1 > -1){
        if(Chessboard[pos.x - 1][pos.y] == nullptr){
            t->add(pos, {pos.x - 1, pos.y}, 0);
        }
        else if(Chessboard[pos.x - 1][pos.y]->getColor() != col){
            t->add(pos, {pos.x - 1, pos.y}, Chessboard[pos.x - 1][pos.y]->getValue());
        }
    }

    // left up
    if(pos.x - 1 > -1 and pos.y - 1 > -1){
        if(Chessboard[pos.x - 1][pos.y - 1] == nullptr){
            t->add(pos, {pos.x - 1, pos.y - 1}, 0);
        }
        else if(Chessboard[pos.x - 1][pos.y - 1]->getColor() != col){
            t->add(pos, {pos.x - 1, pos.y - 1}, Chessboard[pos.x - 1][pos.y - 1]->getValue());
        }
    }

    // up
    if(pos.y - 1 > -1){
        if(Chessboard[pos.x][pos.y - 1] == nullptr){
            t->add(pos, {pos.x, pos.y - 1}, 0);
        }
        else if(Chessboard[pos.x][pos.y - 1]->getColor() != col){
            t->add(pos, {pos.x, pos.y - 1}, Chessboard[pos.x][pos.y - 1]->getValue());
        }
    }

    return t;
}


//==============================Table_of_pieces=================================

class Table_of_pieces{
private:
    Piece** tab;
    Color col;
    int length_of_tab;
    int num_of_pieces;
public:
    //accessors
    int get_length_of_tab();
    int get_num_of_pieces();
    Piece& operator[](int);
    //API
    void remove_piece(Piece*);
    void add_piece(Piece*);
    void print_pieces();
    //technical
    Table_of_pieces(Color);
    Table_of_pieces() = delete;
    ~Table_of_pieces();
    Table_of_pieces(const Table_of_pieces&);
    Table_of_pieces& operator=(const Table_of_pieces&) = delete;
};

Table_of_pieces::Table_of_pieces(Color c){
    col = c;
    length_of_tab = 16;
    num_of_pieces = 0;
    //cout << "Table of pieces constructed!" << endl;
    tab = new Piece*[length_of_tab];
    for(int j=0; j<8; j++){
        for(int i=0; i<8; i++){
            if(Chessboard[i][j] != nullptr){
                if(Chessboard[i][j]->getColor() == c){
                    if(num_of_pieces == length_of_tab){
                        Piece** tab_aux = new Piece*[2*length_of_tab];
                        for(int k=0; k<length_of_tab; k++){
                            tab_aux[k] = tab[k];
                        }
                        delete [] tab;
                        tab = tab_aux;
                        length_of_tab*=2;
                    }
                    tab[num_of_pieces] = Chessboard[i][j];
                    num_of_pieces++;
                }
            }
        }
    }
}
Table_of_pieces::~Table_of_pieces(){
    delete []tab; // don't be afraid, Pieces in the tab will be destructed later in destruct_board();
    //cout << "Table destructed!" << endl;

}
Table_of_pieces::Table_of_pieces(const Table_of_pieces& t){
    col = t.col;
    length_of_tab = t.length_of_tab;
    num_of_pieces = t.num_of_pieces;
    tab = new Piece*[length_of_tab];
    for(int i=0; i<num_of_pieces; i++){
        tab[i] = t.tab[i];
    }
}

int Table_of_pieces::get_length_of_tab(){
    return length_of_tab;
}
int Table_of_pieces::get_num_of_pieces(){
    return num_of_pieces;
}
Piece& Table_of_pieces::operator[](int i){
    return *tab[i];
}
// removing piece only from Table_of_pieces
void Table_of_pieces::remove_piece(Piece* p){
    bool found = false;
    for(int i=0; i<num_of_pieces && !found; i++){
        if(tab[i] == p){
            found = true;
            if(i != num_of_pieces-1) tab[i] = tab[num_of_pieces-1];
            tab[num_of_pieces-1] = nullptr;
            num_of_pieces-=1;
        }
    }
}
void Table_of_pieces::add_piece(Piece* p){
    if(num_of_pieces == length_of_tab){
                        Piece** tab_aux = new Piece*[2*length_of_tab];
                        for(int k=0; k<length_of_tab; k++){
                            tab_aux[k] = tab[k];
                        }
                        delete [] tab;
                        tab = tab_aux;
                        length_of_tab*=2;
                        }
    tab[num_of_pieces] = p;
    num_of_pieces++;
}
void Table_of_pieces::print_pieces(){
    for(int i=0; i<num_of_pieces; i++){
        tab[i]->print_piece();
    }
    cout << endl;
}



//===================================tests======================================

// test_val shows if value of each piece is initialized correctly
void test_val(){
    cout << "\nPieces value:" << endl;
    cout << "\n";
    for(int j=0; j<8; j++){
        for(int i=0; i<8; i++){
            if(Chessboard[i][j] == nullptr){cout << "0 ";}
            else{cout << Chessboard[i][j]->getValue() << " ";}
        };
        cout << endl;
    }
}

// test_print_pos shows if positions in system {[0..7],[0..7]} is converted to system letter_number correctly
void test_print_pos(){
    cout << endl;
    for(int j=0; j<8; j++){
        for(int i=0; i<8; i++){
            print_pos({i,j});
            cout << " ";
        }
        cout << endl;
    }
}


//===========================base=class=Player==================================

bool isSelfCheckmating(Position start, Position target);
bool isCheckmating(Position start, Position target);
bool isChecking(Position start, Position target);
void move_piece(Position start, Position target);

class Player{
    friend class RationalPlayer;
    friend class ConservativePlayer;
    friend class RandomPlayer;
protected:
    Table_of_pieces* pieces;
    Color col;
    bool checked; // eventually delete checked
    bool checkmated;
    bool blocked; // blocked == true if Player can't do any move (unnecessarily player is checkmated);
public:
    //accessors
    bool isChecked();
    bool isCheckmated();
    bool isBlocked();
    Color getColor();
    //API
    bool canCaptureTheOpponentsKing(); // ifCheckingTheOpponent == true if player Player "can" capture the opponent's King;
    bool isCheckmatedByTheOpponentNow();
    void remove_piece(Piece*);
    void add_piece(Piece*);
    void print_pieces();
    Table_of_moves* all_moves();
    virtual void move() = 0;
    //technical
    Player() = delete;
    Player(Color);
    virtual ~Player();
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
};

Player* white_player;
Player* black_player;

Player::Player(Color c){
    checked = false;
    checkmated = false;
    blocked = false;
    col = c;
    pieces = new Table_of_pieces(c);
    //cout << "Player created!" << endl;
}
Player::~Player(){
    delete pieces;
    //cout << "Player destructed!" << endl;
}
bool Player::isChecked(){
    return checked;
}
bool Player::isCheckmated(){
    return checkmated;
}
bool Player::isBlocked(){
    return blocked;
}
Color Player::getColor(){
    return col;
}
bool Player::canCaptureTheOpponentsKing(){
    bool cond = false;
    Table_of_moves* T = all_moves();
    for(int i=0; i<T->num_of_moves && !cond; i++){
        cond = (T->get_value_tab(i) == 6); // King must be the only Piece that have value == 6
    }
    delete T;

    return cond;
}
bool Player::isCheckmatedByTheOpponentNow(){
    bool cond = true;

    Table_of_moves* T = all_moves();
    for(int i=0; i<T->num_of_moves && cond; i++){
        cond = isSelfCheckmating(T->start_tab[i], T->target_tab[i]);
    }
    if(T->num_of_moves == 0){
        if(col == white) cond = black_player->canCaptureTheOpponentsKing();
        else cond = white_player->canCaptureTheOpponentsKing();
    }
    delete T;
    return cond;
}
void Player::remove_piece(Piece* p){
    pieces->remove_piece(p);
}
void Player::add_piece(Piece* p){
    pieces->add_piece(p);
}
void Player::print_pieces(){
    pieces->print_pieces();
}
Table_of_moves* Player::all_moves(){
    Table_of_moves* T = new Table_of_moves;
    for(int i=0; i<pieces->get_num_of_pieces(); i++){
        Table_of_moves* tab_aux = (*pieces)[i].moves();
        T->addtab(tab_aux);
        delete tab_aux;
    }
    return T;
}

//=========================derived=classes=Player===============================

class RandomPlayer: public Player{
public:
    //API
    void move();
    //technical
    RandomPlayer() = delete;
    RandomPlayer(Color c);
    ~RandomPlayer();
    RandomPlayer(const RandomPlayer&) = delete;
    RandomPlayer& operator=(const RandomPlayer&) = delete;
};
class ConservativePlayer: public Player{
public:
    //API
    void move();
    //technical
    ConservativePlayer() = delete;
    ConservativePlayer(Color c);
    ~ConservativePlayer();
    ConservativePlayer(const ConservativePlayer&) = delete;
    ConservativePlayer& operator=(const ConservativePlayer&) = delete;
};
class RationalPlayer: public Player{
public:
    //API
    void move();
    //technical
    RationalPlayer() = delete;
    RationalPlayer(Color c);
    ~RationalPlayer();
    RationalPlayer(const RandomPlayer&) = delete;
    RationalPlayer& operator=(const RationalPlayer&) = delete;
};



RandomPlayer::RandomPlayer(Color c): Player(c){
    //cout << "Random player created!" << endl;
}
RandomPlayer::~RandomPlayer(){
    //cout << "Random player destructed!" << endl;
}
void RandomPlayer::move(){
    Table_of_moves* T = all_moves();

    if(T->get_num_of_moves() == 0){
        blocked = true;
        delete T;
    }
    else{
        Table_of_moves* aux = new Table_of_moves;
        for(int i=0; i<T->get_num_of_moves(); i++){
            if(!isSelfCheckmating(T->get_start_tab(i), T->get_target_tab(i)))
                aux->add(T->get_start_tab(i), T->get_target_tab(i), T->get_value_tab(i));
        }
        delete T;
        T = aux;

        if(T->get_num_of_moves() == 0) checkmated = true;
        else{
            checked = false;

            int i = rand() % T->get_num_of_moves();

            if(isCheckmating(T->get_start_tab(i), T->get_target_tab(i))){
                if(col == white) black_player->checkmated = true;
                else white_player->checkmated = true;
            }
            else if(isChecking(T->get_start_tab(i), T->get_target_tab(i))){
                if(col == white) black_player->checked = true;
                else white_player->checked = true;
            }

            move_piece(T->get_start_tab(i), T->get_target_tab(i));






        }

        delete T;
    }
}
ConservativePlayer::ConservativePlayer(Color c): Player(c){
    //cout << "Conservative player created!" << endl;
}
ConservativePlayer::~ConservativePlayer(){
    //cout << "Conservative player destructed!" << endl;
}
void ConservativePlayer::move(){
    Table_of_moves* T = all_moves();

    if(T->get_num_of_moves() == 0){
        blocked = true;
        delete T;
    }
    else{
        Table_of_moves* aux = new Table_of_moves;
        int max_right = 0;
        for(int i=0; i<T->get_num_of_moves(); i++){
            if(!isSelfCheckmating(T->get_start_tab(i), T->get_target_tab(i))){
                if(max_right < T->get_start_tab(i).x) max_right = T->get_start_tab(i).x;
                aux->add(T->get_start_tab(i), T->get_target_tab(i), T->get_value_tab(i));
            }
        }
        delete T;
        T = aux;

        if(T->get_num_of_moves() == 0) checkmated = true;
        else{
            checked = false;
            // choosing the most right Piece:
            aux = new Table_of_moves;
            int max_value = 0;
            for(int i=0; i<T->get_num_of_moves(); i++){
                if(T->get_start_tab(i).x == max_right){
                    aux->add(T->get_start_tab(i), T->get_target_tab(i), T->get_value_tab(i));
                    if(max_value < Chessboard[T->get_start_tab(i).x][T->get_start_tab(i).y]->getValue())
                        max_value = Chessboard[T->get_start_tab(i).x][T->get_start_tab(i).y]->getValue();
                }
            }
            delete T;
            T = aux; // in T there are only the most right Pieces; their maximum value is max_val;


            if(col == white){

                        aux = new Table_of_moves;
                        int nearest_y = 0; /* change color */
                        for(int i=0; i<T->get_num_of_moves(); i++){
                            if(Chessboard[T->get_start_tab(i).x][T->get_start_tab(i).y]->getValue() == max_value){
                                aux->add(T->get_start_tab(i), T->get_target_tab(i), T->get_value_tab(i));
                                if(T->get_start_tab(i).y > nearest_y /* change color */) nearest_y = T->get_start_tab(i).y;
                            }
                        }
                        delete T;
                        T = aux; // in T there are only these Moves of the most valuable Pieces; the smallest distance between them to white edge = nearest_y;

                        aux = new Table_of_moves;
                        int most_right_move = 0;
                        for(int i=0; i<T->get_num_of_moves(); i++){
                            if(T->get_start_tab(i).y == nearest_y){
                                aux->add(T->get_start_tab(i), T->get_target_tab(i), T->get_value_tab(i));
                                if(T->get_target_tab(i).x > most_right_move) most_right_move = T->get_target_tab(i).x;
                            }
                        }
                        delete T;
                        T = aux; // in T there are only these Moves of the Pieces that are the nearest white edge; the most right move is equal most_right_move

                        aux = new Table_of_moves;
                        int most_forward_move = 7;/* change color */
                        for(int i=0; i<T->get_num_of_moves(); i++){
                            if(T->get_target_tab(i).x == most_right_move){
                                aux->add(T->get_start_tab(i), T->get_target_tab(i), T->get_value_tab(i));
                                if(T->get_target_tab(i).y < most_forward_move/* change color */) most_forward_move = T->get_target_tab(i).y;
                            }
                        }
                        delete T;
                        T = aux; // in T there are only the most right Moves; the most forward move is equal most_forward_move

                        aux = new Table_of_moves;
                        for(int i=0; i<T->get_num_of_moves(); i++){
                            if(T->get_target_tab(i).y == most_forward_move)
                                aux->add(T->get_start_tab(i), T->get_target_tab(i), T->get_value_tab(i));
                        }
                        delete T;
                        T = aux; // in T there is only one move (so T->num_of_moves == 1) that is the most forward


            }
            else{
                        aux = new Table_of_moves;
                        int nearest_y = 7;
                        for(int i=0; i<T->get_num_of_moves(); i++){
                            if(Chessboard[T->get_start_tab(i).x][T->get_start_tab(i).y]->getValue() == max_value){
                                aux->add(T->get_start_tab(i), T->get_target_tab(i), T->get_value_tab(i));
                                if(T->get_start_tab(i).y < nearest_y) nearest_y = T->get_start_tab(i).y;
                            }
                        }
                        delete T;
                        T = aux; // in T there are only these Moves of the most valuable Pieces; the smallest distance between them to black edge = nearest_y;

                        aux = new Table_of_moves;
                        int most_right_move = 0;
                        for(int i=0; i<T->get_num_of_moves(); i++){
                            if(T->get_start_tab(i).y == nearest_y){
                                aux->add(T->get_start_tab(i), T->get_target_tab(i), T->get_value_tab(i));
                                if(T->get_target_tab(i).x > most_right_move) most_right_move = T->get_target_tab(i).x;
                            }
                        }
                        delete T;
                        T = aux; // in T there are only these Moves of the Pieces that are the nearest black edge; the most right move is equal most_right_move

                        aux = new Table_of_moves;
                        int most_forward_move = 0;
                        for(int i=0; i<T->get_num_of_moves(); i++){
                            if(T->get_target_tab(i).x == most_right_move){
                                aux->add(T->get_start_tab(i), T->get_target_tab(i), T->get_value_tab(i));
                                if(T->get_target_tab(i).y > most_forward_move) most_forward_move = T->get_target_tab(i).y;
                            }
                        }
                        delete T;
                        T = aux; // in T there are only the most right Moves; the most forward move is equal most_forward_move

                        aux = new Table_of_moves;
                        for(int i=0; i<T->get_num_of_moves(); i++){
                            if(T->get_target_tab(i).y == most_forward_move)
                                aux->add(T->get_start_tab(i), T->get_target_tab(i), T->get_value_tab(i));
                        }
                        delete T;
                        T = aux; // in T there is only one move (so T->num_of_moves == 1) that is the most forward

            }

            if(isCheckmating(T->get_start_tab(0), T->get_target_tab(0))){
                if(col == white) black_player->checkmated = true;
                else white_player->checkmated = true;
            }
            else if(isChecking(T->get_start_tab(0), T->get_target_tab(0))){
                if(col == white) black_player->checked = true;
                else white_player->checked = true;
            }

            move_piece(T->get_start_tab(0), T->get_target_tab(0));



        }


        delete T;
    }

}
RationalPlayer::RationalPlayer(Color c): Player(c){
    //cout << "Rational player created!" << endl;
}
RationalPlayer::~RationalPlayer(){
    //out << "Rational player destructed!" << endl;
}
void RationalPlayer::move(){
    Table_of_moves* T = all_moves();

    if(T->get_num_of_moves() == 0){
        blocked = true;
        delete T;
    }
    else{
        Table_of_moves* aux = new Table_of_moves;
        for(int i=0; i<T->get_num_of_moves(); i++){
            if(!isSelfCheckmating(T->get_start_tab(i), T->get_target_tab(i))){
                aux->add(T->get_start_tab(i), T->get_target_tab(i), T->get_value_tab(i));
            }
        }
        delete T;

        T = aux;

        if(T->get_num_of_moves() == 0) checkmated = true;

        // 1. checkmating
        else{
            checked = false;
            aux = new Table_of_moves;
            int max_val = 0;
            for(int i=0; i<T->get_num_of_moves(); i++){
                int value = T->get_value_tab(i);
                if(max_val < value) max_val = value;
                if(isCheckmating(T->get_start_tab(i), T->get_target_tab(i))){

                        aux->add(T->get_start_tab(i), T->get_target_tab(i), T->get_value_tab(i));
                    }
            }


            if(aux->get_num_of_moves() != 0){
                // random checkmating move
                int j = rand() % aux->get_num_of_moves();
                // don't capture King: ( King is the only Piece that has value == 6)
                if(Chessboard[aux->get_target_tab(j).x][aux->get_target_tab(j).y] != nullptr){
                    if(Chessboard[aux->get_target_tab(j).x][aux->get_target_tab(j).y]->getValue() != 6){
                    move_piece(aux->get_start_tab(j), aux->get_target_tab(j));
                    }
                }
                else move_piece(aux->get_start_tab(j), aux->get_target_tab(j));
                // marking the opponent as checkmated
                if(col == white) black_player->checkmated = true;
                else white_player->checkmated = true;
                delete aux;
            }

            // else 2. capturing the most valuable Piece
            else{
                // aux is empty
                if(max_val>0){
                for(int i=0; i<T->get_num_of_moves(); i++){
                    if(T->get_value_tab(i) == max_val){
                            aux->add(T->get_start_tab(i), T->get_target_tab(i), T->get_value_tab(i));
                        }
                }
                if(aux->get_num_of_moves() != 0){
                        // random most valuable move
                        int j = rand() % aux->get_num_of_moves();
                        if(isChecking(aux->get_start_tab(j), aux->get_target_tab(j))){
                            if(col == white) black_player->checked = true;
                            else white_player->checked = true;
                        }
                        move_piece(aux->get_start_tab(j), aux->get_target_tab(j));
                        delete aux;
                    }
                }
                // else 3. checking
                else{
                    // aux is empty
                    for(int i=0; i<T->get_num_of_moves(); i++){
                        if(isChecking(T->get_start_tab(i), T->get_target_tab(i))){
                                aux->add(T->get_start_tab(i), T->get_target_tab(i), T->get_value_tab(i));
                            }
                    }

                    if(aux->get_num_of_moves() != 0){
                        // random checking move
                        int j = rand() % aux->get_num_of_moves();
                        move_piece(aux->get_start_tab(j), aux->get_target_tab(j));
                        // marking the opponent as checked
                        if(Chessboard[aux->get_target_tab(j).x][aux->get_target_tab(j).y]->getColor() == white) black_player->checked = true;
                        else white_player->checked = true;
                        delete aux;
                    }

                    // else 4. random move
                    else{
                        int j = rand() % T->get_num_of_moves();
                        move_piece(T->get_start_tab(j), T->get_target_tab(j));
                        delete aux;

                    }


                }


            }


        }

        delete T;
    }



}

int no_of_round = 1;

//  try_move_piece returns pointer to target position's piece and removes it from Table_of_pieces of Player
Piece* try_move_piece(Position start, Position target){
    Piece* P = Chessboard[target.x][target.y];
    if(Chessboard[target.x][target.y] == nullptr){
        Chessboard[start.x][start.y]->Move(target);
        Chessboard[target.x][target.y] = Chessboard[start.x][start.y];
        Chessboard[start.x][start.y] = nullptr;

    }
    else{
        Chessboard[start.x][start.y]->Move(target);
        Chessboard[target.x][target.y] = Chessboard[start.x][start.y];
        Chessboard[start.x][start.y] = nullptr;
    }

    return P;
}
//  move_piece changes position of piece and eventually deletes captured piece
void move_piece(Position start, Position target){

    if(Chessboard[target.x][target.y] == nullptr){
        Chessboard[start.x][start.y]->Move(target);
        Chessboard[target.x][target.y] = Chessboard[start.x][start.y];
        Chessboard[start.x][start.y] = nullptr;
        Chessboard[target.x][target.y]->print_piece();
        cout << " ";
        print_pos(start);
        cout << " -> ";
        print_pos(target);
        cout << endl;
    }

    else{
        Piece* P = Chessboard[target.x][target.y];
        Chessboard[start.x][start.y]->print_piece();
        cout << ": ";
        print_pos(start);
        cout << " -> ";
        print_pos(target);
        cout << endl;
        cout << "Captured: ";
        Chessboard[target.x][target.y]->print_piece();
        cout << endl;
        Chessboard[start.x][start.y]->Move(target);
        Chessboard[target.x][target.y] = Chessboard[start.x][start.y];
        Chessboard[start.x][start.y] = nullptr;
        if(P->getColor() == white_player->getColor()) white_player->remove_piece(P);
        else black_player->remove_piece(P);
        delete P;
    }

}
// isSelfCheckmating == true iff after move from start to target the opponent is checkmating
bool isSelfCheckmating(Position start, Position target){
    bool cond = false;
    Piece* P = try_move_piece(start, target);

    if(Chessboard[target.x][target.y]->getColor() == white){
        if(P != nullptr) black_player->remove_piece(P);
        cond = black_player->canCaptureTheOpponentsKing();
        if(P != nullptr) black_player->add_piece(P);
    }
    else{
        if(P != nullptr) white_player->remove_piece(P);
        cond = white_player->canCaptureTheOpponentsKing();
        if(P != nullptr) white_player->add_piece(P);
    }
    // undoing the move
    try_move_piece(target, start);
    Chessboard[target.x][target.y] = P;
    return cond;
}
// read_me: isCheckmating == true iff the Player checkmates the opponent but remember to check isSelfCheckmating firstly
bool isCheckmating(Position start, Position target){
    bool cond = false;
    // case that maybe is impossible to exist
    if(Chessboard[target.x][target.y] != nullptr){
        if(Chessboard[target.x][target.y]->getValue() == 6)
            cond = true;
    }
    else{
    Piece* P = try_move_piece(start, target);
    if(Chessboard[target.x][target.y]->getColor() == white){
        if(P != nullptr) black_player->remove_piece(P);
        cond = black_player->isCheckmatedByTheOpponentNow();
        if(P != nullptr) black_player->add_piece(P);
    }
    else{
        if(P != nullptr) white_player->remove_piece(P);
        cond = white_player->isCheckmatedByTheOpponentNow();
        if(P != nullptr) white_player->add_piece(P);
    }
    // undoing the move
    try_move_piece(target, start);
    Chessboard[target.x][target.y] = P;

    }
    return cond;
}
// read_me: isChecking == true iff the Player checks the opponent but remember to check isSelfCheckmating firstly
bool isChecking(Position start, Position target){
    bool cond = false;
    Piece* P = try_move_piece(start, target);
    if(Chessboard[target.x][target.y]->getColor() == white){
        if(P != nullptr) black_player->remove_piece(P);
        cond = white_player->canCaptureTheOpponentsKing();
        if(P != nullptr) black_player->add_piece(P);
    }
    else{
        if(P != nullptr) white_player->remove_piece(P);
        cond = black_player->canCaptureTheOpponentsKing();
        if(P != nullptr) white_player->add_piece(P);
    }
    // undoing the move
    try_move_piece(target, start);
    Chessboard[target.x][target.y] = P;

    return cond;
}
// print_state prints state if any Player is checked/blocked/checkmated;
void print_state(){
    if(white_player->isBlocked() && !white_player->isChecked() && !white_player->isCheckmated()) cout << "White player is blocked\n";
    if(black_player->isBlocked() && !black_player->isChecked() && !black_player->isCheckmated()) cout << "Black player player is blocked\n";

    if(white_player->isChecked()) cout << "White player is checked\n";
    if(black_player->isChecked()) cout << "Black player is checked\n";

    if(white_player->isCheckmated()) cout << "White player is checkmated\n";
    if(black_player->isCheckmated()) cout << "Black player is checkmated\n";
}
void print_results(){
    if(white_player->isCheckmated()) cout << "Black player wins!\n";
    else if(black_player->isCheckmated()) cout << "White player wins!\n";
    else if(white_player->isBlocked()) cout << "Draw. White player cannot move.\n";
    else if(black_player->isBlocked()) cout << "Draw. Black player cannot move.\n";
    else if(no_of_round == 50) cout << "Draw. There's 50 rounds.\n";
}


//====================================game======================================

void play_game(){
    // Here you can choose players:
    white_player = new RationalPlayer(white);
    black_player = new RandomPlayer(black);

    cout << "============GAME===========\n\n\n\n\n\n";

    print_board();

    int no_of_moves = 0;
    srand((unsigned)time(0));
    do{
        if(no_of_moves %2 == 0) {
            cout << "\n\n=======ROUND no. " << no_of_round << "=========\n\n";
            white_player->move();
        }
        else{
            black_player->move();
            no_of_round++;
        }

        print_state();
        print_board();
        no_of_moves++;
    } while(!white_player->isBlocked() && !white_player->isCheckmated() && !black_player->isBlocked() && !black_player->isCheckmated() && no_of_round<50);

    print_results();

    delete white_player;
    delete black_player;
}


//====================================main======================================

int main(int argc, char** argv) {
    ini_board();
    play_game();
    destruct_board();
}
