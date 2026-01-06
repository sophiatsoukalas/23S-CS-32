#include "Player.h"
#include <iostream>
using namespace std;

// Base Class: Player

Player::Player(std::string name) : m_name(name) {}

std::string Player::name() const {
    return m_name;
}


bool Player::isInteractive() const {
    return false;
}

Player::~Player() {}



// Derived Class: HumanPlayer

HumanPlayer::HumanPlayer(std::string name) : Player(name) {}


bool HumanPlayer::isInteractive() const {
    return true;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const {
    int hole;
    cout << "Your move: ";
    cin >> hole;
    while (hole < 1 || hole > b.holes()) {
        cout << "Choose a valid number between 1 and " << b.holes() << ": ";
        cin >> hole;
    }
    return hole;
}




// Derived Class: BadPlayer

BadPlayer::BadPlayer(std::string name) : Player(name) {}

int BadPlayer::chooseMove(const Board& b, Side s) const {
    for (int i = 1; i <= b.holes(); i++) {
        if (b.beans(s, i) != 0) return i;
    }
    return 1;
}



// Derived Class: SmartPlayer

SmartPlayer::SmartPlayer(std::string name) : Player(name) {
    this->root = new TreeNode;
}

bool SmartPlayer::comp(int current, int other, Side s) const {
    return (s == SOUTH) ? current > other : current < other;
}



int SmartPlayer::chooseMove(const Board& b, Side s) const {
    Side endSide;
    int endHole;
    this->root->setBoard(b);
    JumpyTimer timer(1000);
    this->deepen(this->root, s, endSide, endHole);
    this->evalTree(this->root, s, NUM_LEVELS, 4990, timer);
    int config = 0;
    int prospect = this->root->children[0]->value;
    for (int i = 1; i < root->children.size(); ++i) {
        int other = root->children[i]->value;
        if (this->comp(prospect, other, s)) {
            config = i;
            prospect = other;
        }
    }
    int bestHole = this->root->children[config]->hole;
    return bestHole;

}
int SmartPlayer::valuecalc(const Board& b) const {
    bool over = (b.beansInPlay(SOUTH) == 0) || (b.beansInPlay(NORTH) == 0);
    bool hasWinner = b.beans(SOUTH, POT) != b.beans(NORTH, POT);
    if (over && hasWinner) return (b.beans(SOUTH, POT) > b.beans(NORTH, POT)) ? MAX : -MAX;

    int relative_diff = b.beans(SOUTH, POT) - b.beans(NORTH, POT);
    int value = relative_diff;
    return value;
}

void SmartPlayer::TreeNode::setBoard(const Board& b) {
    this->board = b;
}

// constructor for root node
SmartPlayer::TreeNode::TreeNode() {
    this->parent = nullptr;
}


SmartPlayer::TreeNode::TreeNode(TreeNode* parent, Board b) {
    this->parent = parent;
    this->board = b;
}

SmartPlayer::TreeNode::~TreeNode() {
    for (size_t i = 0; i < this->children.size(); ++i)
        delete this->children[i];
    this->children.clear();
}

SmartPlayer::~SmartPlayer() {
    delete this->root;
}




// deepen the game tree by one level
void SmartPlayer::deepen(TreeNode* parent, Side s, Side& endSide, int& endHole) const {
    for (int j = 1; j < parent->board.holes(); ++j) {
        if (parent->board.beans(s, j) == 0)
            continue;
        // creating new child node
        TreeNode* child = new TreeNode(parent, parent->board);
        child->board.sow(s, j, endSide, endHole);
        child->hole = j;
        parent->children.push_back(child);
    }
}


void SmartPlayer::evalTree(TreeNode* current, Side s, int n, double timeLimit, JumpyTimer& timer) const
{
    if (n == 0 || timeLimit <= 0) {
        current->value = valuecalc(current->board);
    } //  do base case heuristic computation
    else
    {
        Side end;
        int hole;
        deepen(current, s, end, hole);
        for (size_t branchesLeftToExplore = current->children.size(); branchesLeftToExplore > 0; branchesLeftToExplore--)
        {
            
            
//              // Allocate remaining time limit equally among remaining braches to explore
            double thisBranchTimeLimit = timeLimit / branchesLeftToExplore;
//
//              // Save branch start time so can compute the time the branch took
            double startTime = timer.elapsed();
//              // Explore this branch
            //deepen(current->children[branchesLeftToExplore-1], opponent(s), end, hole);
            evalTree(current->children[branchesLeftToExplore-1], opponent(s), n-1, thisBranchTimeLimit, timer);
//              // Adjust remaining time
            timeLimit -= (timer.elapsed() - startTime);
           if (timeLimit <= 0)
                timeLimit = 0;
        }
    }
    return;
}



