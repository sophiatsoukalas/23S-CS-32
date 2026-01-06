#ifndef Player_h
#define Player_h

#include <string>
#include "Side.h"
#include "Board.h"
#include <vector>




class Player {
private:
    std::string m_name;
public:
    Player(std::string name);
    std::string name() const;
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const = 0;
    virtual ~Player();
};


class HumanPlayer : public Player {
public:
    HumanPlayer(std::string name);
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const;
};


class BadPlayer : public Player {
public:
    BadPlayer(std::string name);
    virtual int chooseMove(const Board& b, Side s) const;
};

class SmartPlayer : public Player {
private:
    class TreeNode {
    public:
        int value;
        int hole;
        Board board;
        std::vector<TreeNode*> children;
        TreeNode* parent;
        TreeNode(TreeNode* parent, Board b);
        TreeNode();
        ~TreeNode();
        void setBoard(const Board& b); // setting board for root node only
    };
    TreeNode* root;
    bool comp(int current, int other, Side s) const;
    int valuecalc(const Board& b) const;
    void evalTree(TreeNode* current, Side s, int n, double timeLimit, JumpyTimer& timer) const;
    void deepen(TreeNode* t, Side s, Side& endSide, int& endHole) const;
public:
    SmartPlayer(std::string name);
    virtual int chooseMove(const Board& b, Side s) const;
    ~SmartPlayer();
};


#endif /* Player_h */
