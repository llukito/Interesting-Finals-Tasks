#include "allone.h"
#include <iostream>

AllOne::AllOne() {
    head = new Node();
    tail = new Node();
    head->next = tail;
    head->prev = nullptr;
    tail->next = nullptr;
    tail->prev = head;
}

void AllOne::inc(string key) {
    if (map.count(key)) {
        // erase
        nd* removable = map[key]->mp[key];
        removable->prev->next = removable->next;
        removable->next->prev = removable->prev;
        delete removable;
        map[key]->mp.erase(key);

        Node* temp = map[key];
        if (map[key]->next != tail && map[key]->next->freq == map[key]->freq + 1) {
            //insert
            nd* addable = new nd();
            addable->value = key;
            addable->prev = map[key]->next->h;
            addable->next = map[key]->next->h->next;
            map[key]->next->h->next->prev = addable;
            map[key]->next->h->next = addable;

            map[key]->next->mp[key] = addable;

            map[key] = map[key]->next;
        }
        else {
            Node* addable = new Node();
            addable->freq = map[key]->freq + 1;
            addable->h = new nd(); addable->t = new nd();
            addable->h->prev = nullptr;
            addable->t->next = nullptr;
            addable->h->next = addable->t; addable->t->prev = addable->h;

            //insert
            nd* adda = new nd();
            adda->value = key;
            adda->prev = addable->h;
            adda->next = addable->h->next;
            addable->h->next->prev = adda;
            addable->h->next = adda;

            addable->mp[key] = adda;

            map[key]->next->prev = addable;
            addable->next = map[key]->next;
            addable->prev = map[key];
            map[key]->next = addable;

            map[key] = addable;
        }
        if (temp->mp.size() == 0) {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
        }
    }
    else {
        if (head->next != tail && head->next->freq == 1) {
            //insert
            nd* addable = new nd();
            addable->value = key;
            addable->prev = head->next->h;
            addable->next = head->next->h->next;
            head->next->h->next->prev = addable;
            head->next->h->next = addable;

            head->next->mp[key] = addable;

            map[key] = head->next;
        }
        else {
            Node* addable = new Node();
            addable->freq = 1;
            addable->h = new nd(); addable->t = new nd();
            addable->h->prev = nullptr;
            addable->t->next = nullptr;
            addable->h->next = addable->t; addable->t->prev = addable->h;

            //insert
            nd* adda = new nd();
            adda->value = key;
            adda->prev = addable->h;
            adda->next = addable->h->next;
            addable->h->next->prev = adda;
            addable->h->next = adda;

            addable->mp[key] = adda;

            head->next->prev = addable;
            addable->next = head->next;
            addable->prev = head;
            head->next = addable;

            map[key] = addable;
        }
    }
}

void AllOne::dec(string key) {
    if (map[key]->freq == 1) {
        // erase
        nd* removable = map[key]->mp[key];
        removable->prev->next = removable->next;
        removable->next->prev = removable->prev;
        delete removable;
        map[key]->mp.erase(key);

        Node* temp = map[key];
        map.erase(key);
        if (temp->mp.size() == 0) {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
        }
    }
    else {
        // erase
        nd* removable = map[key]->mp[key];
        removable->prev->next = removable->next;
        removable->next->prev = removable->prev;
        delete removable;
        map[key]->mp.erase(key);

        Node* temp = map[key];
        if (map[key]->prev != head && map[key]->prev->freq == map[key]->freq - 1) {
            //insert
            nd* addable = new nd();
            addable->value = key;
            addable->prev = map[key]->prev->h;
            addable->next = map[key]->prev->h->next;
            map[key]->prev->h->next->prev = addable;
            map[key]->prev->h->next = addable;

            map[key]->prev->mp[key] = addable;

            map[key] = map[key]->prev;
        }
        else {
            Node* addable = new Node();
            addable->freq = map[key]->freq - 1;
            addable->h = new nd(); addable->t = new nd();
            addable->h->prev = nullptr;
            addable->t->next = nullptr;
            addable->h->next = addable->t; addable->t->prev = addable->h;

            //insert
            nd* adda = new nd();
            adda->value = key;
            adda->prev = addable->h;
            adda->next = addable->h->next;
            addable->h->next->prev = adda;
            addable->h->next = adda;

            addable->mp[key] = adda;

            map[key]->prev->next = addable;
            addable->prev = map[key]->prev;
            addable->next = map[key];
            map[key]->prev = addable;

            map[key] = addable;
        }
        if (temp->mp.size() == 0) {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
        }
    }
}

string AllOne::getMaxKey() {
    if (tail->prev == head || tail->prev->mp.size() == 0) {
        return "";
    }
    for (auto& entry : tail->prev->mp) {
        return entry.first;
    }
    return "";
}

string AllOne::getMinKey() {
    if (head->next == tail || head->next->mp.size() == 0) {
        return "";
    }
    for (auto& entry : head->next->mp) {
        return entry.first;
    }
    return "";
}
