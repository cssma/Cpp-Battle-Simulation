// Martyna Cios

#include <iostream>
#include <string>
using namespace std;

class PLAYER_CLASS {
protected:
    string id;
    string id_;
    unsigned int defense;

    unsigned int maxHealth;
    unsigned int currHealth;
    unsigned int attack;
    unsigned int agility;
    friend class CAESAR_CLASS;
    friend class ARENA_CLASS;
    friend class SQUAD_CLASS;
    bool isDead;

    unsigned int previousCount;
public:
    void die() {
        currHealth = 0;
        isDead = true;
    }

public:
    PLAYER_CLASS() {
        id = "";
        id_ = "";
        maxHealth = 0;
        currHealth = 0;
        attack = 0;
        agility = 0;
        isDead = false;
        previousCount = 0;
    }
    PLAYER_CLASS ( unsigned int maxH, unsigned int currH, unsigned int att, unsigned int agil, unsigned int prvCnt ) {
        maxHealth = maxH;
        currHealth = currH;
        attack = att;
        agility = agil;
    }


    virtual unsigned int getRemainingHealth()
    {
        unsigned int remHelt = ( currHealth * 100 ) / maxHealth;
        return remHelt;
    };

    virtual unsigned int getDamage() {
        return attack;
    }

    virtual unsigned int getAgility() {
        return agility;
    }

    virtual void takeDamage( unsigned int ) = 0;

    virtual void applyWinnerReward() {
        attack = attack + 2;
        agility = agility + 2;
    }

    virtual void cure() {
        currHealth = maxHealth;
    }

    virtual void printParams() = 0;

    virtual string getId() {
        if ( id != "" )
            return id;
    }
};

class CAESAR_CLASS {
    int defendantNumber;
public:
    CAESAR_CLASS() {
        defendantNumber = 0;
    }
    void judgeDeathOrLife( PLAYER_CLASS* defendant ) {
        defendantNumber++;
        if ( defendantNumber % 3 == 0 ) {
            defendant->die();
        }
    }
};

class ARENA_CLASS {
    CAESAR_CLASS caesar;

public:
    ARENA_CLASS ( CAESAR_CLASS* caesar ) {
        this->caesar = *caesar;
    }

    void fight ( PLAYER_CLASS* player1, PLAYER_CLASS* player2 ) {
        if ( player1->getRemainingHealth() > 0 && player2->getRemainingHealth() > 0 ) {
            if ( player2->getAgility() > player1->getAgility() ) {
                PLAYER_CLASS* help = player2;
                player2 = player1;
                player1 = help;
            }
            player1->printParams();
            player2->printParams();
            int remainingAttacks = 40;
            bool secondPlayerTurn = false;
            while ( player1->getRemainingHealth() >= 10 && player2->getRemainingHealth() >= 10 && remainingAttacks > 0 ) {
                if ( secondPlayerTurn && !( player2->getRemainingHealth() < 10 ) && !(player1->getRemainingHealth() < 10 ) ) {
                    player1->takeDamage( player2->getDamage());
                    remainingAttacks--;
                    player1->printParams();
                    if ( player1->getRemainingHealth() <= 0 ) {
                        player1->die();
                    }
                    secondPlayerTurn = false;
                }
                if ( !secondPlayerTurn && !(player1->getRemainingHealth() < 10 ) && !( player2->getRemainingHealth() < 10 )) {
                    player2->takeDamage( player1->getDamage() );
                    remainingAttacks--;
                    player2->printParams();
                    if ( player2->getRemainingHealth() <= 0 ) {
                        player2->die();
                    }
                    secondPlayerTurn = true;
                }
            }
            if ( !(player1->getRemainingHealth() <= 0 )) {
                if ( remainingAttacks % 2 == 0 )
                    caesar.judgeDeathOrLife( player1 );
                player1->printParams();
            }
            if ( !(player2->getRemainingHealth() <= 0 )) {
                if ( remainingAttacks % 2 == 0 )
                    caesar.judgeDeathOrLife( player2 );
                player2->printParams();
            }
            if ( !(player1->getRemainingHealth() <= 0 )) {
                player1->applyWinnerReward();
                player1->cure();
            }
            if ( !(player2->getRemainingHealth() <= 0 )) {
                player2->applyWinnerReward();
                player2->cure();
            }
            player1->printParams();
            player2->printParams();
        }
    }
};

class HUMAN_CLASS : public virtual PLAYER_CLASS {

public:
    HUMAN_CLASS( string id ) : PLAYER_CLASS( 200, 200, 30, 10, 0 )
    {
        this->id = id;
        defense = 10;
        isDead = false;
    }

    void takeDamage ( unsigned int substractHealth ) {
        int goods = defense + getAgility();
        if ( goods < substractHealth ) {
            int tempHealth = currHealth - (substractHealth - ( goods ));

            if (tempHealth <= 0) {
                die();
            } else {
                currHealth = tempHealth;
            }
        }
    }

    void printParams() {
        if ( getRemainingHealth() == 0 )
            cout << id << ":" << "R.I.P." << endl;
        else
            cout << id << ":" << maxHealth << ":" << currHealth << ":" <<
                 getRemainingHealth() << "%:" << getDamage() << ":" << getAgility() <<
                 ":" << defense << endl;
    }

    string getId() {
        return id;
    }

};

class BEAST_CLASS : public virtual PLAYER_CLASS {

public:
    friend class SQUAD_CLASS;
    BEAST_CLASS ( string id ) : PLAYER_CLASS( 150, 150, 40, 20, 0 ) {
        this->id_ = id;
        isDead = false;
    }

    unsigned int getDamage() {
        if ( getRemainingHealth() < 25 )
            return 2 * PLAYER_CLASS::getDamage();
        else
            return PLAYER_CLASS::getDamage();
    }

    void takeDamage( unsigned int substractHealth ) {
        int goods = getAgility() / 2;
        if ( goods < substractHealth ) {
            int tempHealth = currHealth - ( substractHealth - goods );

            if (tempHealth <= 0) {
                die();
            } else {
                currHealth = tempHealth;
            }
        }
    }

    void printParams() {
        if ( getRemainingHealth() <= 0 )
            cout << id_ << ":" << "R.I.P." << endl;
        else
            cout << id_ << ":" << maxHealth << ":" << currHealth << ":" <<
                 getRemainingHealth() << "%:" << getDamage() << ":" << getAgility() << endl;
    }

    string getId() {
        return id_;
    }
};

class BERSERKER_CLASS : virtual public HUMAN_CLASS, virtual public BEAST_CLASS {

public:
    BERSERKER_CLASS ( string humanId, string beastId ) : PLAYER_CLASS ( 200, 200, 35, 5, 0 ),
                                                        HUMAN_CLASS( humanId ), BEAST_CLASS( beastId )
    {
        id = humanId;
        id_ = beastId;
        defense = 15;
        isDead = false;
    }

    unsigned int getDamage() {
        if ( getRemainingHealth() >= 25 )
            return HUMAN_CLASS::getDamage();
        else
            return BEAST_CLASS::getDamage();
    }

    void takeDamage ( unsigned int substractHealth ) {
        if ( getRemainingHealth() >= 25 )
            HUMAN_CLASS::takeDamage( substractHealth );
        else
            BEAST_CLASS::takeDamage( substractHealth );
    }

    void printParams() {
        if ( getRemainingHealth() >= 25 || currHealth <= 0 )
            HUMAN_CLASS::printParams();
        else
            BEAST_CLASS::printParams();
    }

    string getId() {
        if ( getRemainingHealth() >= 25 || currHealth <= 0 ) {
            return id;
        }
        else {
            return id_;
        }
    }
};

class SQUAD_CLASS : public PLAYER_CLASS {
    struct Node {
        PLAYER_CLASS* player;
        string id;
        string id_;
        Node* next;
        Node* prev;
    };
    Node* head;

public:

    SQUAD_CLASS ( string id ) {
        this->id = id;
        //this->id_ = id;
        head = NULL;

        maxHealth = 0;
        currHealth = 0;
        attack = 0;
        agility = 0;
        defense = 0;
        isDead = false;
        previousCount = 0;
    }

    void die() {
        Node* current = head;
        while ( current != NULL ) {
            current->player->die();
            current->player->isDead = true;
            current = current->next;
        }
        head = NULL;
    }

    void cure() {
        Node* current = head;
        while ( current != NULL ) {
            if ( current->player->getRemainingHealth() > 0 )
                current->player->cure();
            current = current->next;
        }
    }

    void applyWinnerReward() {
        Node *current = head;
        while ( current != NULL ) {
            current->player->applyWinnerReward();
            current = current->next;
        }
    }

    void addPlayer ( PLAYER_CLASS* newPlayer ) {
        if ( !( newPlayer->getRemainingHealth() <= 0 )) {
            Node *current = head;
            while ( current != NULL ) {
                if ( current->player == newPlayer )
                    return;
                current = current->next;
            }
            Node* newNode = new Node();
            newNode->player = newPlayer;
            newNode->id = getId();
            newNode->id_ = getId();
            newNode->next = NULL;

            if ( head == NULL )
            {
                head = newNode;
                newNode->prev = NULL;
            }
            else
            {
                Node* last = head;
                while ( last->next != NULL )
                    last = last->next;
                last->next = newNode;
                newNode->prev = last;
            }
        }
    }

    unsigned int getAgility() {
        if ( head != NULL ) {
            Node* current = head;
            unsigned int minAgility = 4294967295;
            while ( current != NULL ) {
                if ( current->player->getRemainingHealth() > 0 && current->player->isDead == false ) {
                    if (current->player->getAgility() < minAgility)
                        minAgility = current->player->getAgility();
                }
                current = current->next;
            }
            return minAgility;
        }
    }

    unsigned int getDamage() {
        if ( head != NULL ) {
            Node* current = head;
            unsigned int damageSum = 0;
            while ( current != NULL ) {
                if ( current->player->getRemainingHealth() > 0 && current->player->isDead == false ) {
                    damageSum += current->player->getDamage();
                }
                current = current->next;
            }
            return damageSum;
        }
        else return 0;
    }

    unsigned int getRemainingHealth () {
        if ( head != NULL ) {
            Node* current = head;
            unsigned int maxRemHealth = 0;
            while ( current != NULL ) {
                if ( current->player->getRemainingHealth() > maxRemHealth )
                    maxRemHealth = current->player->getRemainingHealth();
                current = current->next;
            }
            return maxRemHealth;
        }
        else
            return 0;
    }

    unsigned int countMembers () {
        unsigned int membersCount = 0;
        Node* current = head;

        while ( current != NULL )
        {
            if ( current->player->getRemainingHealth() > 0 && current->player->isDead == false ) {
                membersCount++;
            }
            else {
                current->player->isDead = true;
            }
            current = current->next;
        }

        previousCount = membersCount;
        return membersCount;
    }



    void takeDamage(unsigned int attack)
    {
        if (head != NULL)
        {
            int preCount = previousCount;

            unsigned int nodesCount = countMembers();
            unsigned int damage = 0;

            if ( preCount > 0 ) {
                damage = attack / preCount;
            }
            else {
                damage = attack / countMembers();
            }

            Node *current = head;
            while (current != NULL)
            {
                current->player->takeDamage(damage);

                if (current->player->getRemainingHealth() <= 0 || current->player->isDead == true )
                {
                    current->player->isDead = true;
                    Node* next_n = current->next;
                    Node* prev_n = current->prev;
                    if ( current == head ) {
                        if ( next_n == NULL ){
                            head = NULL;
                        }
                        else {
                            head = next_n;
                            next_n->prev = NULL;
                        }
                    }
                    else {
                        if ( next_n == NULL ) {
                            prev_n->next = NULL;
                        }
                        else {
                            next_n->prev = prev_n;
                            prev_n->next = next_n;
                        }
                    }
                    Node* toDelete = current;


                    current = current->next;
                    delete toDelete;
                }
                else
                {
                    current = current->next;
                }
            }
        }
    }

    void sortPlayers() {
        Node* i = head->next;
        while ( i != NULL )
        {
            Node* j = i;
            i = i->next;

            Node* k = head;
            Node* prev = NULL;

            while (k != j && (
                    k->player->getId() < j->player->getId() ||
                    (k->player->getId() == j->player->getId() && k->player->maxHealth < j->player->maxHealth) ||
                    (k->player->getId() == j->player->getId() && k->player->maxHealth == j->player->maxHealth &&
                     k->player->currHealth < j->player->currHealth) ||
                    (k->player->getId() == j->player->getId() && k->player->maxHealth == j->player->maxHealth &&
                     k->player->currHealth == j->player->currHealth && k->player->attack < j->player->attack) ||
                    (k->player->getId() == j->player->getId() && k->player->maxHealth == j->player->maxHealth &&
                     k->player->currHealth == j->player->currHealth && k->player->attack == j->player->attack &&
                     k->player->agility < j->player->agility))) {
                prev = k;
                k = k->next;
            }
            if (k == j) continue;

            j->prev->next = j->next;
            if (j->next) {
                j->next->prev = j->prev;
            }

            if (prev) {
                prev->next = j;
            } else {
                head = j;
            }
            k->prev = j;
            j->next = k;
            j->prev = prev;

        }
    }

    void printParams() {
        if ( head == NULL )
        {
            cout << id << ":nemo" << endl;
        }
        else
        {
            cout <<
                 getId() << ":" <<
                 countMembers() << ":"<<
                 getRemainingHealth() << "%:"<<
                 getDamage() << ":" <<
                 getAgility() << endl;

            sortPlayers();

            Node* current = head;
            while ( current != NULL )
            {
                if ( current->player->getRemainingHealth() > 0 && current->player->isDead == false ) {
                    current->player->printParams();
                    current = current->next;
                }
                else {
                    current->player->isDead = true;
                    current = current->next;
                }
            }
        }
    }
};



