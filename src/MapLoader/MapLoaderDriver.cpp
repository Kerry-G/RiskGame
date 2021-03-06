//
// Created by ker10 on 2019-09-28.
//

#include "MapLoaderDriver.h"
#include <cassert>
#include "MapLoader.h"
#include "../Map/Map.h"
#include "../exceptions.h"
#include "../Terminal/Terminal.h"

namespace MapLoader {
    namespace Driver {
        bool load_Risk_Europe() {
            MapLoader *mapLoader = new MapLoader();
            string s = "RiskEurope.map";
            Board::Map *testMap = nullptr;
            try {
                testMap = mapLoader->load(s)->build();
            } catch (IOException &e) {
                string error = e.what(s);
                Terminal::error(error);
            }

            assert(testMap->get_continents().at(8)->get_name() == "East_Europe");
            assert(testMap->get_countries().at(45)->get_name() == "Ukraine");

            delete testMap;
            delete mapLoader;
            return true;
        };

        bool load_uk() {
            MapLoader mapLoader;
            string s = "uk.map";
            Board::Map *testMap = nullptr;
            try {
                testMap = mapLoader.load(s)->build();
            } catch (IOException &e) {
                string error = e.what(s);
                Terminal::error(error);
            }
            assert(testMap->get_continents().at(5)->get_name() == "South-England");
            assert(testMap->get_countries().at(74)->get_name() == "Kent");
            delete testMap;
            return true;
        };

        bool load_original_risk_map() {
            MapLoader mapLoader;
            string s = "risk.map";
            Board::Map *testMap = nullptr;
            try {
                testMap = mapLoader.load(s)->build();
            } catch (IOException &e) {
                string error = e.what(s);
                Terminal::error(error);
            }
            assert(testMap->get_continents().at(5)->get_name() == "Oceania");
            assert(testMap->get_countries().at(41)->get_name() == "Eastern-Australia");
            delete testMap;
            return true;
        };

        bool load_a_not_correct_mapfile() {
            MapLoader mapLoader;
            string s = "garbage.map";
            Board::Map *testMap = nullptr;
            try {
                testMap = mapLoader.load(s)->build();
            } catch (IOException &e) {
                string error = e.what(s);
                Terminal::error(error);
            } catch (exception &e) {
                string message = e.what();
                assert(message == "Invalid file format");
            }
            return true;
        };

        bool load_empty_file() {
            MapLoader mapLoader;
            string s = "undefined.map";
            Board::Map *testMap = nullptr;
            try {
                testMap = mapLoader.load(s)->build();
            } catch (IOException &e) {
                string error = e.what(s);
                Terminal::error(error);
            } catch (exception &e) {
                string message = e.what();
                assert(message == "There is no continents in the provided file");
            }
            return true;
        };

        bool load_map_with_only_continent() {
            MapLoader mapLoader;
            string s = "onlyContinents.map";
            Board::Map *testMap = nullptr;
            try {
                testMap = mapLoader.load(s)->build();
            } catch (IOException &e) {
                string error = e.what(s);
                Terminal::error(error);
            } catch (exception &e) {
                string message = e.what();
                assert(message == "There is no country in the provided file");
            }
            return true;
        };

        bool load_undefined() {
            MapLoader mapLoader;
            const string s = "longer_name_break_exception";
            Board::Map *testMap = nullptr;
            try {
                testMap = mapLoader.load(s)->build();
                assert(false);
            } catch (IOException &e) {
                string message = e.what(s);
            }
            delete testMap;
            return true;
        };

        bool load_conquest_zuluquadrant() {
            MapLoader mapLoader;
            string s = "ZuluQuadrant.map";
            Board::Map *testMap = nullptr;
            try {
                testMap = mapLoader.load(s)->build();
            } catch (IOException &e) {
                string error = e.what(s);
                Terminal::error(error);
            }

            assert(testMap->is_connected());
            assert(testMap->get_continents().size() == 6);
            assert(testMap->get_countries().size() == 35);

            delete testMap;
            return true;
        };

        bool load_conquest_frogger() {
            MapLoader mapLoader;
            string s = "Frogger.map";
            Board::Map *testMap = nullptr;
            try {
                testMap = mapLoader.load(s)->build();
            } catch (IOException &e) {
                string error = e.what(s);
                Terminal::error(error);
            }

            assert(testMap->is_connected());
            assert(testMap->get_continents().size() == 13);
            assert(testMap->get_countries().size() == 139);

            delete testMap;
            return true;
        };

        bool load_conquest_world() {
            MapLoader mapLoader;
            string s = "World+.map";
            Board::Map *testMap = nullptr;
            try {
                testMap = mapLoader.load(s)->build();
            } catch (IOException &e) {
                string error = e.what(s);
                Terminal::error(error);
            }

            assert(testMap->is_connected());
            assert(testMap->get_continents().size() == 6);
            assert(testMap->get_countries().size() == 47);

            delete testMap;
            return true;
        };

        bool run() {
            load_Risk_Europe();
            load_uk();
            load_original_risk_map();
            load_a_not_correct_mapfile();
            load_empty_file();
            load_map_with_only_continent();
            load_undefined();

            // Conquest / Adapter tests
            // MapLoader dynamically chooses between different reader depending on format
            load_conquest_zuluquadrant();
            load_conquest_frogger();
            load_conquest_world();

            return true;
        }
    }
}