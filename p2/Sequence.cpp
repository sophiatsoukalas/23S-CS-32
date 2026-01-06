#include "Sequence.h"
#include <iostream>
Sequence::Sequence() { // default constructor
    head = new Node;
    head->next = nullptr;
    head->prev = nullptr;
}
Sequence::Sequence(const Sequence& other) { // copy constructor
    head = new Node;
    for (int counter = 0; counter < other.size(); counter++) {
        insert(counter, other.traverse(counter)->value);
    }
}
Sequence& Sequence::operator=(const Sequence& other) { // assignment operator overloading
    if (this != &other) {
        Sequence temp(other);
        swap(temp);
    }
    return *this;
}
Sequence::~Sequence() { // destructor
    for (int counter = size()-1; counter >= 0; counter--) erase(counter);
    delete head;
}


bool Sequence::empty() const {
    return (size() == 0);
}
int Sequence::size() const {
    int count = 0;
    for (Node* p = head->next; p != nullptr && p != head; p = p->next) count++;
    return count;
}
int Sequence::insert(int pos, const ItemType& value) { // inserts value at position pos in list
    if (pos > size()) return -1;

    Node* newNode = new Node;
    newNode->value = value;
    if (pos == size()) { // appends newNode to end of list
        Node* temp = (empty()) ? head : traverse(pos-1); // defines "previous" node
        newNode->next = head;
        newNode->prev = temp;
        temp->next = newNode;
        head->prev = newNode;
    } else {
        newNode->next = traverse(pos);
        newNode->prev = traverse(pos)->prev;
        traverse(pos)->prev = newNode;
        newNode->prev->next = newNode;
    }
    return pos;
}
int Sequence::insert(const ItemType& value) { // inserts value at first position where arg value < the value at the position
    ItemType x;
    if (empty()) {
        insert(0, value);
        return 0;
    }
    for (int counter = 0; counter < size(); counter++) { // searches LL to insert value
        get(counter, x);
        if (x >= value) {
            insert(counter, value);
            return counter;
        }
    }
    insert(size(), value);
    return size()-1;
}
bool Sequence::erase(int pos) { // deletes node at position pos
    if (empty() || traverse(pos) == nullptr) return false;
    Node* delNode = traverse(pos);
    
    if (size() == 1) { // case: node is only node in LL (reduce LL to dummy node)
        head->next = nullptr;
        head->prev = nullptr;
    } else {
        if (pos == size()-1) { // case: node is at end of LL
            head->prev = delNode->prev;
            delNode->prev->next = head;
        } else {
            delNode->next->prev = delNode->prev;
            delNode->prev->next = delNode->next;
        }
    }
    delete delNode;
    return true;
}
int Sequence::remove(const ItemType& value) { // erases all nodes with given value
    int counter = 0;
    while (find(value) != -1) { // while value exists in LL
        erase(find(value));
        counter++;
    }
    return counter;
}
bool Sequence::get(int pos, ItemType& value) const { // obtains val at position pos
    if (traverse(pos) == nullptr) return false;
    value = traverse(pos)->value;
    return true;
}
bool Sequence::set(int pos, const ItemType& value) { // sets node val to value at position pos
    if (traverse(pos) == nullptr) return false;
    traverse(pos)->value = value;
    return true;
}
int Sequence::find(const ItemType& value) const { // finds first instance of value in LL
    int pos = 0;
    Node* temp = head->next;
    for (; temp != head && temp->value != value; temp = temp->next) pos++;
    if (temp == head) pos = -1; // LL has been iterated thru
    return pos;
}
void Sequence::swap(Sequence& other) { // swaps the LLs of given Sequences via pointers
    Node* temp = this->head;
    this->head = other.head;
    other.head = temp;
}

Sequence::Node* Sequence::traverse(int pos) const { // get pointer to Node at position pos
    if (pos >= size() || pos < 0) return nullptr;

    Node* temp = head->next;

    for (int counter = 0; counter < pos; counter++) {
        temp = temp->next;
    }
    return temp;
}

int subsequence(const Sequence& seq1, const Sequence& seq2) { // tests if seq1 includes seq2
    if (seq1.size() >= seq2.size() && !seq1.empty() && !seq2.empty()) { // valid conditions for iteration
        int s1pos = 0;
        ItemType s1val, s2val;
        for (int s2pos = 0; s2pos < seq2.size(); s2pos++) {
            if (s1pos >= seq1.size()) return -1;
            seq1.get(s1pos, s1val);
            seq2.get(s2pos, s2val);

            if (s1val == s2val) { // given current s2val and this condition, both s1 and s2 will advance one pos
                s1pos++;
                continue; // continue iterative check
            }
            // OTHERWISE, reset s2 iteration and check for next instance where s1val == s2val at s2pos=0
            s2pos = 0;
            for (; s1pos < seq1.size(); s1pos++) {
                seq1.get(s1pos, s1val);
                seq2.get(s2pos, s2val);
                if (s1val == s2val) {
                    s1pos++;
                    break;
                }
            }
        }
        return s1pos-seq2.size(); // returns starting position of matching subseq in s1
    }
    return -1; // returns if invalid starting conditions
}

void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
    bool same_seq = &seq1 == &result || &seq2 == &result;
    Sequence* res = (same_seq) ? new Sequence : &result; // if there's overlapping addresses, define new Sequence. otherwise, use &result
    
    for (int counter = res->size()-1; counter >= 0; counter--) res->erase(counter);// make res empty
    
    ItemType temp;
    for (int counter = 0; counter < seq1.size(); counter++) { // add reversed seq1 to res
        seq1.get(counter, temp);
        res->insert(0, temp);
    }

    for (int counter = 0; counter < seq2.size(); counter++) { // add reversed seq2 to res
        seq2.get(counter, temp);
        res->insert(seq1.size(), temp);
    }
    
    if (same_seq) { // if new Sequence was made, assign result to it and delete res allocation
        result = *res;
        delete res;
    }
}

