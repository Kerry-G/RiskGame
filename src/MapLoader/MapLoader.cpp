//
// Created by ker10 on 2019-09-27.
//

#include "MapLoader.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include "../Map/Map.h"
#include "../exceptions.h"


using namespace std;

namespace MapLoader {

    // Constructors
    MapLoader::MapLoader() {
        input_stream = new ifstream();
        continents_temp = new vector<_continent>(0);
        countries_temp = new vector<_country>(0);
        borders_temp = new vector<_border>(0);
        map = new Map::Map();
    }

    MapLoader MapLoader::openFile(const string &path) {
        input_stream->open("ressources/maps/" + path);
        if (!input_stream->is_open()) {
            throw IOException();
        }
        return *this;
    }

    MapLoader MapLoader::readFile() {
        string line;
        while (getline((*input_stream), line)) {
            if (Sections::isStringAValidSection(line)) {
                Sections::Value value = Sections::getSectionFromString(line);
                section = new Sections(value);
                continue; // jump to the next line
            }
            if (section != nullptr && !line.empty()) {
                section->strategy(line, *this);
            }
        }
        return *this;
    }

    MapLoader MapLoader::closeFile() {
        input_stream->close();
        return *this;
    }

    MapLoader MapLoader::load(const string &path) {
        return openFile(path).readFile().closeFile();
    }

    void MapLoader::addContinentToMemory(const _continent &continent) {
        this->continents_temp->emplace_back(continent);
    }

    void MapLoader::addCountryToMemory(const _country &country) {
        this->countries_temp->emplace_back(country);
    }

    void MapLoader::addBorderToMemory(const _border &border) {
        this->borders_temp->push_back(border);
    }

    Map::Map * MapLoader::build() {
        for ( _continent continent : *continents_temp) {
            new Map::Continent(*continent.name, *continent.bonus, *continent.color, map);
        }
        for (_country country : *countries_temp) {
            Map::Country * new_country = new Map::Country(*country.name);
            Map::Continent * continent = map->get_continents().at( (*country.continentIndex) - 1 ); // Indexing in files start at 1
            continent->insert_country(*new_country);
        }
        for (_border border : *borders_temp) {
            Map::Country * country = map->get_countries().at( (*border.countryIndex) -1 );
            for (int value : *border.values){
                map->connect( *country,  *map->get_countries().at( (value - 1) )); // Indexing in files start at 1
            }
        }
        return map;
    };

    void Sections::strategy(const string &line, MapLoader &mapLoader) {
        char *line_c_str = const_cast<char *>(line.c_str());
        char *token = strtok(line_c_str, " ");
        switch ((*section)) {
            case continent: {
                _continent continent{nullptr, nullptr, nullptr};
                continent.name = new string(token);
                token = strtok(nullptr, " ");
                continent.bonus = new int(strtol(token, nullptr, 10));
                token = strtok(nullptr, " ");
                continent.color = new string(token);
                mapLoader.addContinentToMemory(continent);
                break;
            }
            case countries: {
                _country country{nullptr, nullptr, nullptr, nullptr, nullptr};
                country.index = new int(strtol(token, nullptr, 10));
                token = strtok(nullptr, " ");
                country.name = new string(token);
                token = strtok(nullptr, " ");
                country.continentIndex = new int(strtol(token, nullptr, 10));
                token = strtok(nullptr, " ");
                country.x = new int(strtol(token, nullptr, 10));
                token = strtok(nullptr, " ");
                country.y = new int(strtol(token, nullptr, 10));
                mapLoader.addCountryToMemory(country);
                break;
            }
            case borders: {
                _border border{nullptr, new vector<int>(0)};
                border.countryIndex = new int(strtol(token, nullptr, 10));
                token = strtok(nullptr, " ");
                while (token != nullptr) {
                    border.values->push_back(strtol(token, nullptr, 10));
                    token = strtok(nullptr, " ");
                }
                mapLoader.addBorderToMemory(border);
                break;
            }
            default:
                throw exception();
        }
    }

    Sections::Value Sections::getSectionFromString(const string &s) {
        if (s == "[continents]")
            return Value::continent;
        else if (s == "[countries]")
            return Value::countries;
        else if (s == "[borders]")
            return Value::borders;
        else
            throw exception();
    }

    bool Sections::isStringAValidSection(const string &s) {
        return (s == "[continents]" || s == "[countries]" || s == "[borders]");
    }

    Sections::Sections(Sections::Value s) {
        section = new Value{s};
    }

}