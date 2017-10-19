/* 
 * File:   Kmer_handler.h
 * Author: bx
 *
 * Created on August 17, 2017, 5:57 PM
 */

#ifndef KMER_HANDLER_H
#define	KMER_HANDLER_H

#include <vector>
#include <map>
#include <string.h>
#include <stdlib.h>
#include <set>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include "encoding.h"
#include <algorithm>
#include <inttypes.h>
#include "Contig_handler.h"
#include "shc_google_sparsehash.h"
#include <bits/stringfwd.h>
#include <string>
#include <cmath>
#include "json_parser.h"


#define MAX_KMER_LENGTH 32
#define KMER_HOLDER_LEN 33
#define MAX_KMER_DICTLINE_LENGTH 50
#define DEFAULT_NUM 255
#define MAX_COUNT (std::pow(2,sizeof(kmer_count_t)*8-1)-2)
#define NO_MATCH -1
#define HAS_MATCH 0
#define PREFIX_OFFSET 4
//-1 is a relectant decision, otherwise my compiler gives a overflow warning, 
//I guess in google sparsehash implementation, uint64_t is implicitly converted
//to a signed type
#define SPARSEHASH_DELETE_KEY (std::pow(2,(sizeof(uint64_t)*8)-1)-2) 
#define SPARSEHASH_EMPTY_KEY (std::pow(2,(sizeof(uint64_t)*8)-2)-1) 

typedef std::pair<uint64_t, kmer_count_t> Kmer_Occurence_Pair;

struct Kmer_sorter {
    bool operator()(const Kmer_Occurence_Pair& kmer1, const Kmer_Occurence_Pair& kmer2) const {
	return( kmer1.second > kmer2.second);
    }
};

class Kmer_handler {
    friend class Contig_handler;
    friend class Contig_graph_handler;
    friend class Sequence_graph_handler;
    friend class Multibridge_handler;
public:
    Kmer_handler(Local_files * lfp);        
    Kmer_handler(uint8_t length, kmer_count_t min_count_p, 
                Contig_handler::size_type min_len_p, double R_threshold_p, 
                uint8_t rmer_len, bool is_use_set, Local_files * lfp);
    
    int add_kmer(uint64_t kmer, kmer_count_t count);
    void dump_kmers_to_file(std::string & filename);
    void load_kmers_with_info_from_file(std::string & filename);    
    int build_dict_from_kmer_file();
    
    // info concerning helper function
    bool is_kmer_info_has_ps(uint8_t info);
    bool is_kmer_info_has_prefix(uint8_t info);
    bool is_kmer_info_has_suffix(uint8_t info);    
    void write_kmer_info(uint8_t num, bool is_prefix, const uint64_t *kmer_num);
    void write_all_suffix_info(const uint64_t *kmer_num);
    void write_all_prefix_info(const uint64_t *kmer_num);
    bool is_info_ith_bit_set(uint8_t info, uint8_t i);
    
    //debug
    uint8_t num_bit_info(uint8_t info);
    void traverse_kmer_count();
    
    
    //sorting function
    void sort_kmer_descending_count();
    uint8_t find_prefix_kmer(const uint64_t *kmer, uint64_t *new_kmer_n);
    uint8_t find_suffix_kmer(const uint64_t *kmer, uint64_t *new_kmer_n);    
    //void kmer_change_suffix(uint64_t *kmer, char base);
    
    // contig relating function
    contig_num_t find_contig();        
    void deallocate_kmer_descend_list();  
    void deallocate_contig_count_map();
    void deallocate_rmer_contig_map();
    void deallocate_rmer_count_map();
    
    bool decide_contig_and_build_rmer(kmer_count_t count, Contig_handler::size_type len);    
    bool use_set_to_filter(kmer_count_t count, Contig_handler::size_type len);
    bool use_list_to_filter(kmer_count_t count, Contig_handler::size_type len);
    bool check_len_count(kmer_count_t count, Contig_handler::size_type len);
        
    void delete_kmer_for_contig(uint8_t * contig_start, Contig_handler::size_type contig_len);    
    
    void get_contig_handler(Contig_handler * c_handler);                
    
    uint8_t get_kmer_length();
    uint8_t get_kmer_length_from_file(const std::string& filename);
private:
    kmer_len_t kmer_length;
    Kmer_counter_map kmer_counter;
    Contig_handler * ch;
    std::vector<Kmer_Occurence_Pair> kmer_descend_list;     
        
    struct Duplicate_setting dup_setting;
    //for Rmer contig list implementation, all deallcoated    
    Rmer_contig_map rmer_contig_map;
    Contig_count_map contig_count_map;     
    //for Rmer set implementation, all deallcoated
    Rmer_count_map rmer_count_map;        
    
    //for info
    size_t num_kmer_deleted;    
    
    Local_files *lf;
};

#endif	/* KMER_HANDLER_H */

