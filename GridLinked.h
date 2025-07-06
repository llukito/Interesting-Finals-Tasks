// GridLinked.h
#ifndef GRIDLINKED_H
#define GRIDLINKED_H

class GridLinked {
public:
    GridLinked(int numRows, int numCols);
    ~GridLinked();

    void Set(int row, int col, int val);
    int  Get(int row, int col) const;

    int SetIteratorPosition(int row, int col);
    int  Left();    bool HasLeft() const;
    int  Right();   bool HasRight() const;
    int  Up();      bool HasUp() const;
    int  Down();    bool HasDown() const;

    void AddRow();
    void InsertRow(int row);

private:
    struct Node {
        int val;
        Node* up, * down, * left, * right;
        Node(int v = 0)
            : val(v), up(nullptr), down(nullptr), left(nullptr), right(nullptr) {
        }
    };

    Node* head;
    int rows, cols;

    Node* it;
    Node* bottom;

    Node* at(int row, int col) const;
};

#endif // GRIDLINKED_H