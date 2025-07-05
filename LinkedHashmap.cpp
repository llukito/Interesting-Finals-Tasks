
#include "LinkedHashMap.h"
#include <iostream>

using namespace std;

const int kHashMask = 0x7FFFFFFF;

int hashCode(string key) {
    int hashVal = 0;
    for (int x = 0; x < key.length(); ++x) {
        hashVal ^= (hashVal << 5) +
            (hashVal >> 2) +
            key[x];
    }
    return hashVal & kHashMask;
}

const int kNumBuckets = 5;


LinkedHashMap::LinkedHashMap() {
    capacity = kNumBuckets;
    array = new Cell * [capacity];
    for (int i = 0; i < capacity; i++) {
        array[i] = nullptr;
    }
    loglen = 0;

    head = new DoublyCell(); tail = new DoublyCell();
    head->next = tail; tail->prev = head;
    head->prev = tail->next = nullptr;

    iterator = head;
}

LinkedHashMap::Cell* LinkedHashMap::check(string key) {
    int idx = hashCode(key) % capacity;
    Cell* h = array[idx];
    while (h) {
        if (h->key == key) {
            return h;
        }
        h = h->next;
    }
    return h;
}

void LinkedHashMap::grow() {
    capacity *= 2;
    Cell** newArray = new Cell * [capacity];
    for (int i = 0; i < capacity; i++) {
        newArray[i] = nullptr;
    }
    for (int i = 0; i < capacity / 2; i++) {
        Cell* h = array[i];
        while (h) {
            Cell* temp = h->next;
            int idx = hashCode(h->key) % capacity;
            h->next = newArray[idx];
            newArray[idx] = h;
            h = temp;
        }
    }
    delete[] array;
    array = newArray;
}

void LinkedHashMap::put(string key, int value) {
    if (static_cast<double>(loglen) / capacity > 2) {
        grow();
    }
    int idx = hashCode(key) % capacity;
    Cell*& h = array[idx];
    Cell* cl = check(key);
    if (cl) {
        cl->value = value;
        DoublyCell* dc = cl->place;
        dc->value = value;
        //dequeue
        dc->prev->next = dc->next;
        dc->next->prev = dc->prev;
        // enqueue
        tail->prev->next = dc;
        dc->prev = tail->prev;
        dc->next = tail;
        tail->prev = dc;
    }
    else {
        Cell* addable = new Cell();
        addable->key = key; addable->value = value;

        DoublyCell* dc = new DoublyCell();
        dc->key = key; dc->value = value;
        tail->prev->next = dc;
        dc->prev = tail->prev;
        dc->next = tail;
        tail->prev = dc;

        addable->place = dc;
        addable->next = h;
        h = addable;

        loglen++;
    }
}

bool LinkedHashMap::containsKey(string key) {
    return check(key);
}

int LinkedHashMap::get(string key) {
    Cell* cl = check(key);
    if (!cl) {
        return -1;
    }
    return cl->value;
}

void LinkedHashMap::remove(string key) {
    int idx = hashCode(key) % capacity;
    if (!array[idx])return;
    if (array[idx]->key == key) {
        DoublyCell* dc = array[idx]->place;
        dc->prev->next = dc->next;
        dc->next->prev = dc->prev;
        delete dc;
        Cell* temp = array[idx];
        array[idx] = array[idx]->next;
        delete temp;
        loglen--;
        return;
    }
    Cell* prev = array[idx];
    Cell* h = array[idx]->next;
    while (h) {
        if (h->key == key) {
            DoublyCell* dc = h->place;
            dc->prev->next = dc->next;
            dc->next->prev = dc->prev;
            delete dc;
            prev->next = h->next;
            delete h;
            loglen--;
            return;
        }
        prev = h;
        h = h->next;
    }
}

void LinkedHashMap::resetKeyIterator() {
    iterator = head;
}

bool LinkedHashMap::hasNextKey() {
    return iterator->next != tail;
}

string LinkedHashMap::nextKey() {
    string val = iterator->next->key;
    iterator = iterator->next;
    return val;
}

int LinkedHashMap::size() {
    return loglen;
}

