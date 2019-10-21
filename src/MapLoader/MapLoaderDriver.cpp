//
// Created by ker10 on 2019-09-28.
//

#include "MapLoaderDriver.h"
#include <iostream>
#include <cassert>
#include "MapLoader.h"
#include "../Map/Map.h"
#include "../exceptions.h"

namespace MapLoader { namespace Driver {
    bool load_Risk_Europe(){
        MapLoader * mapLoader = new MapLoader();
        string s = "RiskEurope.map";
        Map::Map * testMap = nullptr;
        try {
            testMap = mapLoader->load(s)->build();
        } catch (IOException &e) {
            cerr << e.what() << s.c_str() << endl;
        }

        assert( testMap->get_continents().at(8)->get_name() == "East_Europe" );
        assert( testMap->get_countries().at(45)->get_name() == "Ukraine" );
        delete mapLoader;
        return true;
    };

    bool load_uk(){
        MapLoader mapLoader;
        string s = "uk.map";
        Map::Map * testMap = nullptr;
        try {
            testMap = mapLoader.load(s)->build();
        } catch (IOException &e) {
            cerr << e.what() << s.c_str() << endl;
        }
        assert( testMap->get_continents().at(5)->get_name() == "South-England" );
        assert( testMap->get_countries().at(74)->get_name() == "Kent" );
        return true;
    };

    bool load_original_risk_map(){
        MapLoader mapLoader;
        string s = "risk.map";
        Map::Map * testMap = nullptr;
        try {
            testMap = mapLoader.load(s)->build();
        } catch (IOException &e) {
            cerr << e.what() << s.c_str() << endl;
        }
        assert( testMap->get_continents().at(5)->get_name() == "Oceania" );
        assert( testMap->get_countries().at(41)->get_name() == "Eastern-Australia" );
        return true;
    };

    bool load_a_not_correct_mapfile(){
        MapLoader mapLoader;
        string s = "garbage.map";
        Map::Map * testMap = nullptr;
        try {
            testMap = mapLoader.load(s)->build();
        } catch (IOException &e) {
            cerr << e.what() << s.c_str() << endl;
        } catch (exception &e) {
            string message = e.what();
            assert(message == "Invalid file format");
        }
        return true;
    };

    bool load_empty_file(){
        MapLoader mapLoader;
        string s = "undefined.map";
        Map::Map * testMap = nullptr;
        try {
            testMap = mapLoader.load(s)->build();
        } catch (IOException &e ) {
            cerr << e.what() << s.c_str() << endl;
        } catch(exception &e){
            string message = e.what();
            assert(message == "There is no continents in the provided file");
        }
        return true;
    };

    bool load_map_with_only_continent(){
        MapLoader mapLoader;
        string s = "onlyContinents.map";
        Map::Map * testMap = nullptr;
        try {
            testMap = mapLoader.load(s)->build();
        } catch (IOException &e ) {
            cerr << e.what() << s.c_str() << endl;
        } catch(exception &e){
            string message = e.what();
            assert(message == "There is no country in the provided file");
        }
        return true;
    };

    bool load_undefined(){
        MapLoader mapLoader;
        string s = "lmao_there_is_no_file_called_like_that";
        Map::Map * testMap = nullptr;
        try {
            testMap = mapLoader.load(s)->build();
        } catch (IOException &e ) {
            string message = e.what();
            assert(message == "Error opening given file: ");
        }
        return true;
    };


    bool run() {
        cout << "[TEST] -----" << endl;
        cout << "[TEST] - Running MapLoader component tests." << endl;

        load_Risk_Europe();
        load_uk();
        load_original_risk_map();
        load_a_not_correct_mapfile();
        load_empty_file();
        load_map_with_only_continent();
        load_undefined();

        cout << "[TEST] - End of MapLoader component testing." << endl;
        cout << "[TEST] -----" << endl;

        return true;
    }
} }