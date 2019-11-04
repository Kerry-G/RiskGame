#include "Map.h"
#include "../Player/Player.h"
#include "../Terminal/Terminal.h"
#include <list>
#include <sstream>

namespace Board {

    Country::Country(const string &name) {
        this->name = new string(name);
        this->index = new int(-1);
        this->continent_index = new int(-1);
        this->nb_armies = new int(0);
        this->owner = nullptr;
    }

    Country::~Country() {
        delete index;
        delete name;
        delete continent_index;
        delete nb_armies;

        // Remove dangling pointers
        index = nullptr;
        name = nullptr;
        continent_index = nullptr;
        nb_armies = nullptr;
        owner = nullptr;
    }

    string Country::get_name() {
        return *name;
    }

    int Country::get_armies() {
        return *nb_armies;
    }

    void Country::set_armies(int num) {
        *nb_armies = num;
    }

    void Country::decrement_army() {
        if(*nb_armies > 0)
            *nb_armies = *nb_armies - 1;
        else
            Terminal::error("Can't decrement army amount to -1.");
    }

    void Country::increment_army() {
        *nb_armies = *nb_armies + 1;
    }


    Player::Player *Country::get_owner() {
        return owner;
    }

    void Country::set_owner(Player::Player *p) {
        owner = p;
    }

    string Country::to_string() {
        ostringstream os;
        if (owner) {
            os << "name: " << *name << ", owner: " << owner->get_color() << ", number of armies: " << *nb_armies;
        } else {
            os << "name: " << *name << ", owner: " << "unclaimed" << ", number of armies: " << *nb_armies;
        }
        return os.str();
    }

    int Country::get_index() {
        return *index;
    }

    void Country::set_neighboring_countries(vector<Country *> neighbors) {
        neighboring_countries = new vector<Country *>(std::move(neighbors));
    }

    vector<Country *> *Country::get_neighbors() const {
        return neighboring_countries;
    }

    string Country::to_string_with_neighbors() {
        ostringstream os;
        if (owner) {
            os << "name: " << *name << ", owner: " << owner->get_color() << ", number of armies: " << *nb_armies << "\n";
        } else {
            os << "name: " << *name << ", owner: " << "unclaimed" << ", number of armies: " << *nb_armies << "\n";

        }
        for (Country *neighbor: *neighboring_countries) {
            os << "\t" << neighbor->to_string() << "\n";
        }
        return os.str();
    }

    int * Country::get_continent_index() {
        return this->continent_index;
    }

    Continent::Continent(const string &name, Map *map) {
        this->index = new int(map->get_continents().size());
        this->size = new int(0);
        this->name = new string(name);
        this->bonus = nullptr;
        this->color = nullptr;
        this->map = map;
        map->add_continent(this);
    }

    Continent::Continent(const string &name, const int &bonus, const string &color, Map *map) {
        this->index = new int(map->get_continents().size());
        this->size = new int(0);
        this->name = new string(name);
        this->bonus = new int(bonus);
        this->color = new string(color);
        this->map = map;
        map->add_continent(this);
    }

    Continent::~Continent() {
        delete index;
        delete size;
        delete name;
    }

    void Continent::insert_country(Country &country) {
        map->insert_country(country);
        map->connect(*this, country);
    }

    bool Continent::is_connected() {
        if(*size < 2) return true;
        int current = -1;
        int visited_count = 1;

        // Finding first country in this continent
        vector<Country *> countries = map->get_countries();
        for(unsigned i=0; i<countries.size(); i++){
            if(*countries[i]->continent_index == *index){
                current = *countries[i]->index;
                break;
            }
        }

        if(current == -1) return false;     // Should never happen... Something went wrong

        vector<bool> visited(countries.size(), false);

        list<int> queue;
        visited[current] = true;
        queue.push_back(current);

        vector<int>::iterator it;
        while(!queue.empty()){
            current = queue.front();
            queue.pop_front();

            // Adjacents of current visited node
            for(it = map->edges->at(current).begin(); it!=map->edges->at(current).end(); it++){
                // Not visited, and in continent only
                if(!visited[*it] && *countries[*it]->continent_index == *index){
                    visited[*it] = true;
                    queue.push_back(*it);
                    visited_count++;
                }
            }
        }

        // We visited everyone of them ?
        return visited_count == *size;
    }

    int Continent::get_size() {
        return *size;
    }

    string Continent::get_name() {
        return *name;
    }

    int Continent::get_bonus() {
        return *bonus;
    }

    int * Continent::get_index() {
        return index;
    }


    Map::Map() {
        continents = new vector<Continent *>;
        countries = new vector<Country *>;
        edges = new vector<vector<int>>;
    }

    Map::~Map() {
        for (auto c : *countries)
            delete c;

        countries->clear();

        delete continents;
        delete countries;
        delete edges;
    }

    void Map::insert_country(Country &new_node) {
        // Check if already in (Has an index)
        if(*new_node.index != -1)
            return;

        *new_node.index = countries->size();
        countries->push_back(&new_node);

        // Create edges mem loc
        edges->push_back(*new vector<int>);
    }

    bool Map::are_adjacent(const Country &a, const Country &b) {
        return are_adjacent(*a.index, *b.index);
    }

    bool Map::are_adjacent(int &a, int &b) {
        vector<int> links = edges->at(a);

        for (unsigned i = 0; i < links.size(); i++) {
            if (links.at(i) == b)
                return true;
        }
        return false;
    }

    vector<Country *> Map::get_countries() const {
        return *countries;
    }

    vector<Continent *> Map::get_continents() const {
        return *continents;
    }

    void Map::connect(const Country &a, const Country &b) {
        // Define direction, a to b
        edges->at(*a.index).push_back(*b.index);
    }

    void Map::connect(Continent &cont, Country &country) {
        if (*country.continent_index != -1)
            (*continents->at(*country.continent_index)->size)--;

        *country.continent_index = *cont.index;
        (*cont.size)++;
    }

    void Map::biconnect(const Country &a, const Country &b) {
        connect(a, b);
        connect(b, a);
    }

    bool Map::is_connected() {
        if(countries->size() < 2) return true;

        int current = 0;
        vector<bool> visited(countries->size(), false);

        list<int> queue;
        visited[current] = true;
        queue.push_back(current);

        vector<int>::iterator it;
        while(!queue.empty()){
            current = queue.front();
            queue.pop_front();

            // Adjacents of current visited node
            for(it = edges->at(current).begin(); it!=edges->at(current).end(); it++){
                if(!visited[*it]){
                    visited[*it] = true;
                    queue.push_back(*it);
                }
            }
        }

        // Check if all visited
        for(unsigned i=0; i<visited.size(); i++){
            if(!visited[i])
                return false;
        }

        return true;
    }

    void Map::add_continent(Continent *continent) {
        continents->push_back(continent);
    }

    void Map::set_country_neighbors() {
        for (size_t i = 0; i < countries->size(); i++) {
            vector<Country *> neighbors;
            for (int country_index : edges->at(i)) {
                neighbors.push_back(get_country_from_index(country_index));
            }
            countries->at(i)->set_neighboring_countries(neighbors);
        }
    }

    Country *Map::get_country_from_index(int index) {
        for(Country *country: *countries) {
            if (country->get_index() == index) {
                return country;
            }
        }
        return nullptr;
    }
}