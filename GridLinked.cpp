#include "GridLinked.h"
#include <stdexcept>
#include <iostream>
using namespace std;

GridLinked::GridLinked(int numRows, int numCols) {
    rows =numRows;
    cols = numCols;
    it = nullptr;
    head = nullptr;

    Node* prevRow = nullptr; 
    for (int r = 0; r < rows; r++) {
        Node* prev = nullptr;
        Node* rowHead = nullptr;
        Node* above = prevRow;

        for (int c = 0; c < cols; c++) {
            Node* curr = new Node(0);
            if (!rowHead) rowHead = curr;

            if (prev) {
                prev->right = curr;
                curr->left = prev;
            }

            if (above) {
                above->down = curr;
                curr->up = above;
                above = above->right;
            }

            prev = curr;
        }

        if (!head) head = rowHead;
        prevRow = rowHead;
    }

    bottom = at(rows - 1, 0); 
}

GridLinked::~GridLinked() {
    while (head) {
        Node* next = head->down;
        while (head) {
            Node* temp = head->right;
            delete head;
            head = temp;
        }
        head = next;
    }
}

GridLinked::Node* GridLinked::at(int row, int col) const {
    Node* temp = head;
    for (int i = 0; i < row; i++) temp = temp->down;
    for (int i = 0; i < col; i++) temp = temp->right;
    return temp;
}

void GridLinked::Set(int row, int col, int val) {
    at(row, col)->val = val;
}

int GridLinked::Get(int row, int col) const {
    return at(row, col)->val;
}

int GridLinked::SetIteratorPosition(int row, int col) {
    it = at(row, col);
    return it->val;
}

int GridLinked::Left() {
    it = it->left;
    return it->val;
}

bool GridLinked::HasLeft() const {
    return it->left != nullptr;
}

int GridLinked::Right() {
    it = it->right;
    return it->val;
}

bool GridLinked::HasRight() const {
    return it->right != nullptr;
}

int GridLinked::Up() {
    it = it->up;
    return it->val;
}

bool GridLinked::HasUp() const {
    return it->up != nullptr;
}

int GridLinked::Down() {
    it = it->down;
    return it->val;
}

bool GridLinked::HasDown() const {
    return it->down != nullptr;
}

void GridLinked::AddRow() {
    Node* above = bottom;
    Node* prev = nullptr;
    Node* newRowHead = nullptr;

    for (int c = 0; c < cols; ++c) {
        Node* curr = new Node(0);
        if (!newRowHead) newRowHead = curr;

        // link horizontally
        if (prev) {
            prev->right = curr;
            curr->left = prev;
        }

        // link vertically
        if (above) {
            above->down = curr;
            curr->up = above;
            above = above->right;
        }

        prev = curr;
    }

    bottom = newRowHead;
    ++rows;
}

void GridLinked::InsertRow(int row) {
    if (row == 0) {
        Node* prev = nullptr;
        Node* newHead = nullptr;

        for (int c = 0; c < cols; ++c) {
            Node* curr = new Node(0);
            if (!newHead) newHead = curr;

            if (prev) {
                prev->right = curr;
                curr->left = prev;
            }

            Node* downNode = at(0, c);
            curr->down = downNode;
            downNode->up = curr;

            prev = curr;
        }

        head = newHead;
        ++rows;
        return;
    }

    if (row == rows) {
        AddRow();
        return;
    }

    Node* aboveRow = at(row - 1, 0);
    Node* belowRow = aboveRow->down;

    Node* prev = nullptr;
    Node* currHead = nullptr;
    Node* upPtr = aboveRow;
    Node* downPtr = belowRow;

    for (int c = 0; c < cols; ++c) {
        Node* curr = new Node(0);
        if (!currHead) currHead = curr;

        if (prev) {
            prev->right = curr;
            curr->left = prev;
        }

        upPtr->down = curr;
        curr->up = upPtr;
        upPtr = upPtr->right;

        if (downPtr) {
            curr->down = downPtr;
            downPtr->up = curr;
            downPtr = downPtr->right;
        }

        prev = curr;
    }
    ++rows;
}
