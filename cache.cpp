#include<iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <list>

int two_pow(long long int num){

    int pow = 0;

    while(num > 1){

        num = num>>1;
        pow += 1;
    }

    return pow;
}

std::string hexCharToBinary(char hexChar) {

    switch (hexChar) {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A':
        case 'a': return "1010";
        case 'B':
        case 'b': return "1011";
        case 'C':
        case 'c': return "1100";
        case 'D':
        case 'd': return "1101";
        case 'E':
        case 'e': return "1110";
        case 'F':
        case 'f': return "1111";

        default: return ""; 
    }
}

std::string hexStringToBinary(const std::string& hexString) {

    std::string binaryString;

    for (char hexChar : hexString) {
        binaryString += hexCharToBinary(hexChar);
    }
    return binaryString;
}

struct usable_cmd {

    std::string s_or_l = "";
    std::string tag = "";
    std::string idx = "";
};

struct block {

    bool is_valid = 0;
    std::string tag = "hello";
    bool is_dirty = 0;
};

void print(int input){
    std::cout << input << "\n";
}

std::list<block>::iterator isexist_set(std::list<block>& dll, std::string targ){   // if targ exist in set or not

    if (dll.size() == 0){

        // std::cout << "list is empty \n";
        return dll.end();
    }

    std::list<block>::iterator it = dll.begin();

    while(it != dll.end()){

        if (it->tag == targ){
        // std::cout << targ;
            return it;
        }
        it++;
    }

    return it;
}

bool is_set_empty(std::list<block> dll, int num_block){    // checks if set is empty

    if (dll.size() == num_block){
        return false;
    }

    return true;
}

int binarystringToDecimal(const std::string& binaryString) {
    return std::stoi(binaryString, nullptr, 2);
}

//////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]){

    long long total_loads = 0;
    long long total_stores = 0;
    long long load_hits = 0;
    long long load_misses = 0;
    long long store_hits = 0;
    long long store_misses = 0;
    long long total_cycles = 0;

    // std::cout << argv[1];

    std::string str_num_of_set = (argv[1]);
    // std::string str_num_of_set = "256";
    int num_of_set = stoi(str_num_of_set);
    int log_set = two_pow(num_of_set);


    // print(log_set);

    std::string str_num_of_block = argv[2];
    // std::string str_num_of_block = "4";
    int num_of_block = stoi(str_num_of_block);

    std::string str_num_of_byte_block = argv[3];
    // std::string str_num_of_byte_block = "16";
    int num_of_byte_block = stoi(str_num_of_byte_block);
    int log_byte = two_pow(num_of_byte_block);
    // print(log_byte);

    const int B = num_of_byte_block/4;

    std::string alloc_type = argv[4];
    std::string write_type = argv[5];
    std::string evict_type = argv[6];
    // std::cout << "evict - " << evict_type << "\n";

    // std::string alloc_type = "write-allocate ";
    // std::string write_type = "write-back";
    // std::string evict_type = "lru";

    // int num1;
    // std::cin >> num1 ;
    // std::string str;
    // std::cin >> str;

    std::vector< usable_cmd > cmd_vec;

    while(std::cin){

        usable_cmd cmd;

        std::string str;
        std::cin >> str;    // str contains s or l

        if (str.size() == 0){
            break;
        }

        cmd.s_or_l = str;

        std::cin >> str;    // str contains hexstring
        str = str.substr(2);

        std::string binstring = hexStringToBinary(str);
        // std::cout << binstring << "\n";

        int sz = binstring.size();
        // print(sz);

        cmd.idx = binstring.substr(sz - (log_byte + log_set), log_set);

        cmd.tag = binstring.substr(0, sz - (log_byte + log_set));

        cmd_vec.push_back(cmd);
        std::cin >> str;
    }

    // for (auto x : cmd_vec){
    //     std::cout << x.s_or_l << " " << x.tag << " " << x.idx << "\n";
    // }

    // std::cout << cmd_vec[0].idx << "\n";

    // std::cout << "\n";

    // initializing and then filling the vector with sets and sets with blocks

    std::vector< std::list< block > > cache(num_of_set);
    // std::cout << " c sz - " << cache.size() << "\n";

    // for (int i = 0; i < num_of_set; i++){

    //     std::vector<block> vec(num_of_block);
    //     cache.push_back(vec);
    // }

    // std::cout << "hi205\n";

    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    for (auto cmd_vec_elt : cmd_vec){


        int decimal_idx = binarystringToDecimal(cmd_vec_elt.idx);
        // std::cout << decimal_idx << "- d idx \n";
        std::list<block> set_list = cache[decimal_idx];
        // std::cout << set_list.size();
        // std::cout << "hi211\n";


        if (alloc_type == "write-allocate"){
            
            if (write_type == "write-back"){

                if (cmd_vec_elt.s_or_l == "l"){

                    std::list<block>::iterator is_data_in_cache = isexist_set(set_list, cmd_vec_elt.tag);

                    if (is_data_in_cache != set_list.end()  && set_list.size() != 0){    // hit

                        total_loads++;
                        load_hits++;
                        total_cycles++;

                        if (evict_type == "lru"){

                            block new_block = *(is_data_in_cache);
                            set_list.erase(is_data_in_cache);
                            set_list.push_front(new_block);
                            cache[decimal_idx] = set_list;
                            continue;
                        }

                        else if (evict_type == "fifo"){
                            continue;
                        }
                    }

                    else if (set_list.size() == 0 || is_data_in_cache == set_list.end()){   // miss

                        bool is_set_khaali = is_set_empty(set_list, num_of_block);

                        if (is_set_khaali == true){

                            block new_block;
                            new_block.is_dirty = false;
                            new_block.is_valid = true;
                            new_block.tag = cmd_vec_elt.tag;

                            total_loads++;
                            load_misses++;
                            total_cycles += 100*B + 1;

                            if (evict_type == "lru"){

                                set_list.push_front(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }

                            else if (evict_type == "fifo"){
                                set_list.push_back(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }
                            
                        }

                        else if (is_set_khaali == false){

                            block new_block;
                            new_block.is_dirty = false;
                            new_block.is_valid = true;
                            new_block.tag = cmd_vec_elt.tag;

                            total_loads++;
                            load_misses++;
                            total_cycles += 100*B + 1;

                            if (evict_type == "lru"){

                                block last_block = set_list.back();

                                if (last_block.is_dirty == true){
                                    total_cycles += 100*B;
                                }

                                set_list.pop_back();
                                set_list.push_front(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }

                            else if (evict_type == "fifo"){

                                block first_block = set_list.front();

                                if (first_block.is_dirty == true){
                                    total_cycles += 100*B;
                                }

                                set_list.pop_front();
                                set_list.push_back(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }
                        }

                    }

                }

                else if (cmd_vec_elt.s_or_l == "s"){

                    std::list<block>::iterator is_data_in_cache = isexist_set(set_list, cmd_vec_elt.tag);
              
                    // std::cout << is_data_in_cache->tag << " d_tag - \n ";
                    // std::cout << "hi316\n";

                    if (is_data_in_cache != set_list.end() && set_list.size() != 0){    // hit
                        // std::cout << "hi321\n";
                        total_stores++;
                        store_hits++;
                        total_cycles++;

                        // std::cout << is_data_in_cache->tag << " d_tag - \n ";

                        if (evict_type == "lru"){

                            block new_block = *(is_data_in_cache);

                            new_block.is_dirty = true;///

                            set_list.erase(is_data_in_cache);
                            set_list.push_front(new_block);
                            cache[decimal_idx] = set_list;
                            continue;
                        }

                        else if (evict_type == "fifo"){

                            is_data_in_cache->is_dirty = true;

                            // block new_block = *(is_data_in_cache);

                            // new_block.is_dirty = true;///
                            
                            cache[decimal_idx] = set_list;

                            continue;
                        }

                        // std::cout << "hi350\n";
                    }

                    else if (set_list.size() == 0 || is_data_in_cache == set_list.end()){   // miss

                        // std::cout << "hi isset khaali\n";////////////////////////////
                        bool is_set_khaali = is_set_empty(set_list, num_of_block);

                        if (is_set_khaali == true){

                            block new_block;
                            new_block.is_dirty = true;///
                            new_block.is_valid = true;
                            new_block.tag = cmd_vec_elt.tag;

                            total_stores++;
                            store_misses++;
                            total_cycles += 100*B + 1;

                            if (evict_type == "lru"){
                                // std::cout << "if lru loop\n";
                                set_list.push_front(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }

                            else if(evict_type == "fifo"){
                                set_list.push_back(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }
                        }

                        else if (is_set_khaali == false){

                            block new_block;
                            new_block.is_dirty = true;///
                            new_block.is_valid = true;
                            new_block.tag = cmd_vec_elt.tag;

                            total_stores++;
                            store_misses++;
                            total_cycles += 100*B + 1;


                            if (evict_type == "lru"){

                                block last_block = set_list.back();

                                if (last_block.is_dirty == true){
                                    total_cycles += 100*B;
                                }

                                set_list.pop_back();
                                set_list.push_front(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }

                            else if(evict_type == "fifo"){

                                block first_block = set_list.front();

                                if (first_block.is_dirty == true){
                                    total_cycles += 100*B;
                                }

                                set_list.pop_front();
                                set_list.push_back(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }
                        }
                    }
                }
            }

            else if(write_type == "write-through"){

                if (cmd_vec_elt.s_or_l == "l"){

                    std::list<block>::iterator is_data_in_cache = isexist_set(set_list, cmd_vec_elt.tag);

                    if (is_data_in_cache != set_list.end()  && set_list.size() != 0){    // hit

                        total_loads++;
                        load_hits++;
                        total_cycles++;

                        if (evict_type == "lru"){

                            block new_block = *(is_data_in_cache);
                            set_list.erase(is_data_in_cache);
                            set_list.push_front(new_block);
                            cache[decimal_idx] = set_list;
                            continue;
                        }

                        else if (evict_type == "fifo"){
                            continue;
                        }
                    }

                    else if (set_list.size() == 0 || is_data_in_cache == set_list.end()) {    // miss

                        bool is_set_khaali = is_set_empty(set_list, num_of_block);

                        if (is_set_khaali == true){

                            block new_block;
                            new_block.is_dirty = false;
                            new_block.is_valid = true;
                            new_block.tag = cmd_vec_elt.tag;

                            total_loads++;
                            load_misses++;
                            total_cycles += 100*B + 1;

                            if (evict_type == "lru"){

                                set_list.push_front(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }

                            else if (evict_type == "fifo"){

                                set_list.push_back(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }
                        }

                        else if (is_set_khaali == false){

                            block new_block;
                            new_block.is_dirty = false;
                            new_block.is_valid = true;
                            new_block.tag = cmd_vec_elt.tag;

                            total_loads++;
                            load_misses++;
                            total_cycles += 100*B + 1;

                            if (evict_type == "lru"){

                                set_list.pop_back();
                                set_list.push_front(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }

                            else if (evict_type == "fifo"){

                                set_list.pop_front();
                                set_list.push_back(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }
                        }
                    } 
                }

                else if (cmd_vec_elt.s_or_l == "s"){
                    
                    std::list<block>::iterator is_data_in_cache = isexist_set(set_list, cmd_vec_elt.tag);

                    if (is_data_in_cache != set_list.end()  && set_list.size() != 0){    // hit

                        total_stores++;
                        store_hits++;
                        total_cycles += 101;

                        if (evict_type == "lru"){

                            block new_block = *(is_data_in_cache);
                            set_list.erase(is_data_in_cache);
                            set_list.push_front(new_block);
                            cache[decimal_idx] = set_list;
                            continue;
                        }

                        else if (evict_type == "fifo"){
                            continue;
                        }
                    }

                    else if (set_list.size() == 0 || is_data_in_cache == set_list.end()){   // miss

                        bool is_set_khaali = is_set_empty(set_list, num_of_block);

                        if (is_set_khaali == true){

                            total_stores++;
                            store_misses++;
                            total_cycles += 100*B + 1 + 100;

                            block new_block;
                            new_block.is_dirty = false;
                            new_block.is_valid = true;
                            new_block.tag = cmd_vec_elt.tag;

                            if (evict_type == "lru"){

                                set_list.push_front(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }

                            else if (evict_type == "fifo"){

                                set_list.push_back(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }
                        }

                        else if (is_set_khaali == false){

                            total_stores++;
                            store_misses++;
                            total_cycles += 100*B + 1 + 100;

                            block new_block;
                            new_block.is_dirty = false;
                            new_block.is_valid = true;
                            new_block.tag = cmd_vec_elt.tag;

                            if (evict_type == "lru"){

                                set_list.pop_back();
                                set_list.push_front(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }

                            else if (evict_type == "fifo"){

                                set_list.pop_front();
                                set_list.push_back(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }
                        }
                    }
                }
            }
        }

        else if(alloc_type == "no-write-allocate"){
            
            if (write_type == "write-back"){

                if (cmd_vec_elt.s_or_l == "l"){

                    std::list<block>::iterator is_data_in_cache = isexist_set(set_list, cmd_vec_elt.tag);

                    if (is_data_in_cache != set_list.end()  && set_list.size() != 0){    // hit

                        total_loads++;
                        load_hits++;
                        total_cycles++;

                        if (evict_type == "lru"){

                            block new_block = *(is_data_in_cache);
                            set_list.erase(is_data_in_cache);
                            set_list.push_front(new_block);
                            cache[decimal_idx] = set_list;
                            continue;
                        }

                        else if (evict_type == "fifo"){
                            continue;
                        }
                    }   

                    else if (set_list.size() == 0 || is_data_in_cache == set_list.end()){   // miss

                        bool is_set_khaali = is_set_empty(set_list, num_of_block);

                        if (is_set_khaali == true){

                            total_loads++;
                            load_misses++;
                            total_cycles += 100*B + 1;

                            block new_block;
                            new_block.is_dirty = false;
                            new_block.is_valid = true;
                            new_block.tag = cmd_vec_elt.tag;

                            if (evict_type == "lru"){

                                set_list.push_front(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }

                            else if (evict_type == "fifo"){

                                set_list.push_back(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }
                        }

                        else if (is_set_khaali == false){

                            block new_block;
                            new_block.is_dirty = false;
                            new_block.is_valid = true;
                            new_block.tag = cmd_vec_elt.tag;

                            total_loads++;
                            load_misses++;
                            total_cycles += 100*B + 1;

                            if (evict_type == "lru"){

                                block last_block = set_list.back();

                                if (last_block.is_dirty == true){
                                    total_cycles += 100*B;
                                }

                                set_list.pop_back();
                                set_list.push_front(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }

                            else if (evict_type == "fifo"){

                                block first_block = set_list.front();

                                if (first_block.is_dirty == true){
                                    total_cycles += 100*B;
                                }

                                set_list.pop_front();
                                set_list.push_back(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }
                        }
                    }                 
                }

                else if (cmd_vec_elt.s_or_l == "s"){
                    
                    std::list<block>::iterator is_data_in_cache = isexist_set(set_list, cmd_vec_elt.tag);

                    if (is_data_in_cache != set_list.end()  && set_list.size() != 0){    // hit

                        total_stores++;
                        store_hits++;
                        total_cycles++;

                        if (evict_type == "lru"){

                            block new_block = *(is_data_in_cache);

                            new_block.is_dirty = true;///

                            set_list.erase(is_data_in_cache);
                            set_list.push_front(new_block);
                            cache[decimal_idx] = set_list;
                            continue;
                        }

                        else if (evict_type == "fifo"){

                            is_data_in_cache->is_dirty = true;

                            // block new_block = *(is_data_in_cache);

                            // new_block.is_dirty = true;///

                            cache[decimal_idx] = set_list;

                            continue;
                        }
                    }

                    else if (set_list.size() == 0 || is_data_in_cache == set_list.end()){   // miss

                        total_stores++;
                        store_misses++;
                        total_cycles += 100;
                        continue;
                    }

                }

            }

            else if(write_type == "write-through"){

                if (cmd_vec_elt.s_or_l == "l"){

                    std::list<block>::iterator is_data_in_cache = isexist_set(set_list, cmd_vec_elt.tag);

                    if (is_data_in_cache != set_list.end()  && set_list.size() != 0){    // hit

                        total_loads++;
                        load_hits++;
                        total_cycles++;

                        if (evict_type == "lru"){

                            block new_block = *(is_data_in_cache);
                            set_list.erase(is_data_in_cache);
                            set_list.push_front(new_block);
                            cache[decimal_idx] = set_list;
                            continue;
                        }

                        else if (evict_type == "fifo"){
                            continue;
                        }
                    }

                    else if (set_list.size() == 0 || is_data_in_cache == set_list.end()){   // miss

                        bool is_set_khaali = is_set_empty(set_list, num_of_block);

                        if (is_set_khaali == true){

                            block new_block;
                            new_block.is_dirty = false;
                            new_block.is_valid = true;
                            new_block.tag = cmd_vec_elt.tag;

                            total_loads++;
                            load_misses++;
                            total_cycles += 100*B + 1;

                            if (evict_type == "lru"){

                                set_list.push_front(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }

                            else if (evict_type == "fifo"){

                                set_list.push_back(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }
                        }

                        else if (is_set_khaali == false){

                            block new_block;
                            new_block.is_dirty = false;
                            new_block.is_valid = true;
                            new_block.tag = cmd_vec_elt.tag;

                            total_loads++;
                            load_misses++;
                            total_cycles += 100*B + 1;

                            if (evict_type == "lru"){

                                set_list.pop_back();
                                set_list.push_front(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }

                            else if (evict_type == "fifo"){

                                set_list.pop_front();
                                set_list.push_back(new_block);
                                cache[decimal_idx] = set_list;
                                continue;
                            }
                        }

                    }

                }

                else if (cmd_vec_elt.s_or_l == "s"){

                    std::list<block>::iterator is_data_in_cache = isexist_set(set_list, cmd_vec_elt.tag);

                    if (is_data_in_cache != set_list.end()  && set_list.size() != 0){    // hit

                        total_stores++;
                        store_hits++;
                        total_cycles += 101;

                        if (evict_type == "lru"){

                            block new_block = *(is_data_in_cache);
                            set_list.erase(is_data_in_cache);
                            set_list.push_front(new_block);
                            cache[decimal_idx] = set_list;
                            continue;
                        }

                        else if (evict_type == "fifo"){
                            continue;
                        }
                    }

                    else if (set_list.size() == 0 || is_data_in_cache == set_list.end()){ // miss

                        total_stores++;
                        store_misses++;
                        total_cycles += 100;
                        continue;
                    }
                    
                }
                
            }
        }
    }

    std::cout << "total_loads - " << total_loads << "\n";
    std::cout << "total_store - " << total_stores << "\n";
    std::cout << "load_hits - " << load_hits << "\n";
    std::cout << "load_miss - " << load_misses << "\n";
    std::cout << "store_hits - " << store_hits << "\n";
    std::cout << "store_misses - " << store_misses << "\n";
    std::cout << "total_cycles - " << total_cycles << "\n";
}