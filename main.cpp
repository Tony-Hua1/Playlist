#include "Playlist.h"
#include "Playlist.cpp"

using namespace std;

int main() {
    Playlist my_list;
    Playlist *p;

    p = &my_list;
    cout << p->to_string() << endl;
    p->insert_at_cursor(Playlist::Song_Entry(1, "The Family Madrigal"));
    p->advance_cursor();
    cout << p->to_string() << endl;
    p->insert_at_cursor(Playlist::Song_Entry(2, "Waiting On A Miracle"));
    p->insert_at_cursor(Playlist::Song_Entry(3, "Surface Pressure"));
    cout << p->to_string() << endl;
    p->push_back(Playlist::Song_Entry(9,"Colombia, Mi Encanto"));
    cout << p->to_string() << endl;
    p->push_front(Playlist::Song_Entry(7, "All Of You"));
    cout << p->to_string() << endl;
    p->remove_at_cursor();
    cout << p->to_string() << endl;
    p->insert_at_cursor(Playlist::Song_Entry(1, "The Family Madrigal"));
    p->insert_at_cursor(Playlist::Song_Entry(2, "Waiting On A Miracle"));
    p->insert_at_cursor(Playlist::Song_Entry(3, "Surface Pressure"));
    p->insert_at_cursor(Playlist::Song_Entry(4, "We Don't Talk About Bruno"));
    p->insert_at_cursor(Playlist::Song_Entry(5, "What Else Can I Do?"));
    p->insert_at_cursor(Playlist::Song_Entry(6, "Dos Oruguitas"));
    cout << p->to_string() << endl;
    p->rewind();
    p->advance_cursor();
    p->circular_advance_cursor();
    p->clear();
    cout << p->to_string() << endl;

    return 0;
}