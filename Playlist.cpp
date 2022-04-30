#include <string>
#include <iostream>
#include <sstream>
#include "Playlist.h"

using namespace std;

bool Playlist::Song_Entry::set_id(int id) {
    if (id < 0) {
        return false;
    }
    else {
        _id = id;
        return true;
    }
}

bool Playlist::Song_Entry::set_name(string name) {
    if (name == "") {
        return false;
    }
    else {
        _name = name;
        return true;
    }
}

Playlist::Node::~Node() {
    _next = nullptr;
    delete _next;
}

Playlist::Node *Playlist::Node::insert_next(Node *p) {
    p->_next = _next;
    _next = p;
    return p;
}

Playlist::Node *Playlist::Node::remove_next() {  
    Node *temp = _next;
    _next = temp->_next;
    delete temp;
    return this;

}

Playlist::Playlist() {
    Song_Entry s(-1, "HEAD");
    Node *node = new Node(s);
    _head = node;
    _tail = node;
    _prev_to_current = node;
    _size = 0;
}

Playlist::~Playlist() {
    clear();
    _head = nullptr;
    delete _head;
}


Playlist::Song_Entry &Playlist::get_current_song() const { 
    if (_prev_to_current->get_next() != nullptr) {
        return _prev_to_current->get_next()->get_song();
    }
    else {
        return _head->get_next()->get_song();
    }
}

Playlist *Playlist::clear() {
    rewind();

    while (_prev_to_current->get_next() != nullptr) {
        _prev_to_current->remove_next();
    }

    _prev_to_current = _head;
    _tail = _head;
    _size = 0;
    return this;
}

Playlist *Playlist::rewind() {
    _prev_to_current = _head;
    return this;
}

Playlist *Playlist::push_back(const Playlist::Song_Entry& s) {
    Node *temp = _prev_to_current;
    _prev_to_current = _tail;
    insert_at_cursor(s); // _size++
    _prev_to_current = temp;
    return this;
}

Playlist *Playlist::push_front(const Playlist::Song_Entry& s) {
    Node *temp = _prev_to_current;
    _prev_to_current = _head;
    insert_at_cursor(s); // _size++
    _prev_to_current = temp;
    return this;
}

Playlist *Playlist::insert_at_cursor(const Song_Entry& s) {
    Node *node = new Node(s);

    if (_prev_to_current->get_next() == nullptr) {
        _tail = node;
    }
    
    _prev_to_current->insert_next(node);
    _size++;
    return this;
}

Playlist *Playlist::remove_at_cursor() {
    if (_prev_to_current->get_next() == nullptr) {
        return nullptr;
    }
    else {
        _prev_to_current->remove_next();
        _size--;
        return this;
    }
}

Playlist *Playlist::advance_cursor() {
    if (_prev_to_current == _tail) {
        return nullptr;
    }
    else {
        _prev_to_current = _prev_to_current->get_next();
        return this;
    }
}

Playlist *Playlist::circular_advance_cursor() {
    if (_prev_to_current == _tail) {
        _prev_to_current = _head->get_next();
    }
    else {
        _prev_to_current = _prev_to_current->get_next();        
    }

    return this;
}

Playlist::Song_Entry& Playlist::find_by_id(int id) const {
    Node *temp = _head->get_next();
    
    while (temp != nullptr) {
        if (temp->get_song().get_id() == id) {
            return temp->get_song();
        }
        else {
            temp = temp->get_next();
        }
    }
    
    return _head->get_song();
}

Playlist::Song_Entry& Playlist::find_by_name(std::string songName) const {
    Node *temp = _head->get_next();
    
    while (temp != nullptr) {
        if (temp->get_song().get_name() == songName) {
            return temp->get_song();
        }
        else {
            temp = temp->get_next();
        }
    }
    
    return _head->get_song();
}

std::string Playlist::to_string() const {
   Node *temp = _head->get_next();
   std::string s = "";

   s += "Playlist: " + std::to_string(get_size()) + " entries.\n"; 

    for (int i = 0; i < 25 && temp != nullptr; ++i) {
        s += "{ id: " + std::to_string(temp->get_song().get_id()) + ", name: " + temp->get_song().get_name() + " }";
        
        if (temp == _prev_to_current) {
            s += " [P]";
        }
        
        if (temp == _tail) {
            s += " [T]";
        }

        s += '\n';
        temp = temp->get_next();
    }

    if (_size > 25) {
        s += "...";
    }

    return s;
}