#include "json_parser.h"

std::string get_setting_string(Shannon_C_setting & setting)
{
    std::string setting_str;

    setting_str += "kmer_length is           : " + std::to_string(setting.kmer_length) + "\n";
    setting_str += "output_seq_min_len is    : " + std::to_string(setting.output_seq_min_len) + "\n";
    return setting_str;
}

void parser_setting_file(std::string & file_path, Shannon_C_setting & setting)
{
    using boost::property_tree::ptree;

    std::ifstream json_file(file_path);
    ptree pt;
    boost::property_tree::json_parser::read_json(json_file, pt);
    // top level

    uint8_t kmer_length = pt.get<uint8_t>("kmer_length");
    bool is_double_stranded = pt.get<bool>("double_strand");
    bool has_pair = pt.get<bool>("has_pair");
    bool has_single = pt.get<bool>("has_single");
    bool is_compress = pt.get<bool>("is_compress");
    read_length_t single_read_length = pt.get<read_length_t>("single_read_length");
    read_length_t pair_1_read_length = pt.get<read_length_t>("pair_1_read_length");
    read_length_t pair_2_read_length = pt.get<read_length_t>("pair_2_read_length");
    //bool filter_single = pt.get<bool>("filter_single");
    //bool filter_paired = pt.get<bool>("filter_paired");
    int output_seq_min_len = pt.get<int>("output_seq_min_len");
    bool take_single_node_seq = pt.get<bool>("take_single_node_seq");
    bool take_contig_seq = pt.get<bool>("take_contig_seq");
    int num_parallel = pt.get<int>("num_parallel");

    setting.kmer_length = kmer_length;
    setting.has_single = has_single;
    setting.has_pair = has_pair;
    setting.is_double_stranded = is_double_stranded;
    setting.is_compress = is_compress;
    setting.single_read_length = single_read_length;
    setting.pair_1_read_length = pair_1_read_length;
    setting.pair_2_read_length = pair_2_read_length;
    //setting.filter_single = filter_single;
    //setting.filter_paired = filter_paired;
    setting.output_seq_min_len = output_seq_min_len;
    setting.take_single_node_seq = take_single_node_seq;
    setting.take_contig_seq = take_contig_seq;
    setting.num_parallel = num_parallel;

    // file system
    ptree file_structure = pt.get_child("file_structure");

    std::string input_jf_path   = file_structure.get<std::string>("input_jf_path");
    std::string input_kmer_path = file_structure.get<std::string>("input_kmer_path");
    // OK if both empty or both filled
    if(input_kmer_path.empty() && !input_jf_path.empty())
    {
        shc_log_error("kmer dict and jf files must be provided together\n");
        exit(1);
    }
    else if(!input_kmer_path.empty() && input_jf_path.empty())
    {
        shc_log_error("kmer dict and jf files must be provided together\n");
        exit(1);
    }

    // read
    std::string input_read_path = file_structure.get<std::string>("input_read_path");
    std::string input_read_path_1 = file_structure.get<std::string>("input_read_path_1");
    std::string input_read_path_2 = file_structure.get<std::string>("input_read_path_2");
    // output dir
    std::string output_path = file_structure.get<std::string>("output_path");
    std::string reference_seq_path = file_structure.get<std::string>("reference_seq_path");

    boost::filesystem::path base_path_boost = boost::filesystem::current_path();
    std::string base_path(base_path_boost.string());

    Local_files lf(has_single, has_pair,
                   base_path, output_path,
                   input_kmer_path, input_read_path,
                   input_read_path_1, input_read_path_2, reference_seq_path,
                   input_jf_path);

    setting.local_files = lf;


    // dup_correction
    ptree dup_correction = pt.get_child("kmer_setup");
    uint8_t rmer_length = dup_correction.get<uint8_t>("rmer_length");
    double threshold = dup_correction.get<double>("threshold");
    kmer_count_t min_count = dup_correction.get<kmer_count_t>("min_count");
    size_t min_length = dup_correction.get<size_t>("min_length");
    bool is_use_set = dup_correction.get<bool>("is_use_set");
    double load_factor = dup_correction.get<double>("load_factor");
    int num_sort_thread = dup_correction.get<int>("num_sort_thread");
    setting.dup_setting.set_para(rmer_length, threshold, min_count, min_length,
        is_use_set, load_factor, num_sort_thread);

    // contig setup
    ptree contig_graph_setup = pt.get_child("contig_graph_setup");
    int num_test = contig_graph_setup.get<idx_t>("num_test");
    bool is_assign_best = contig_graph_setup.get<bool>("is_assign_best");
    int read_sampler_k = contig_graph_setup.get<int>("read_sampler_k");
    setting.contig_graph_setup.set_para(num_test, is_assign_best, read_sampler_k);

    //metis_setup
    ptree metis_setup = pt.get_child("metis_setup");
    bool use_multiple_partition = metis_setup.get<bool>
                                                    ("use_multiple_partition");
    idx_t partition_size = metis_setup.get<idx_t>("partition_size");
    idx_t non_partition_size = metis_setup.get<idx_t>("non_partition_size");
    idx_t penalty = metis_setup.get<idx_t>("penalty");
    real_t overload = metis_setup.get<real_t>("overload");
    setting.metis_setup.set_para(use_multiple_partition, partition_size,
                                 overload,  penalty, non_partition_size);
    // seq_graph_setup
    ptree seq_graph_setup = pt.get_child("seq_graph_setup");
    int hop_pair = 0;//seq_graph_setup.get<int>("max_hop_for_pair_search"); //not used anymore
    int hop_path = seq_graph_setup.get<int>("max_hop_for_known_path");
    int mate_pair_len = 300;//seq_graph_setup.get<int>("mate_pair_len");  //not used anymore
    setting.seq_graph_setup.set_para(hop_pair, hop_path, mate_pair_len);

    //sparse_flow setup
    ptree sparse_flow_setup = pt.get_child("sparse_flow_setup");
    int multiple_test = sparse_flow_setup.get<int>("multiple_test");
    setting.sparse_flow_setup.set_para(multiple_test);
    shc_log_info(shc_logname, "parsed json info\n");
}


void print_and_log_all_setting(Shannon_C_setting & setting)
{
    print_and_log_general_setting(setting);
    print_and_log_partition_setting(setting);
    print_and_log_local_file_system(&setting.local_files);
    print_and_log_multi_graph_setting(setting);
    print_and_log_mb_setting(setting);
    print_and_log_sf_setting(setting);
}

void print_and_log_shannon_cmd_setting(Shannon_C_setting & setting)
{
    print_and_log_all_setting(setting);
}

void print_and_log_partition_cmd_setting(Shannon_C_setting & setting)
{
    print_and_log_general_setting(setting);
    print_and_log_partition_setting(setting);
}

void print_and_log_multi_graph_both_cmd_setting(Shannon_C_setting & setting)
{
    print_and_log_general_setting(setting);
    print_and_log_multi_graph_setting(setting);
    print_and_log_mb_setting(setting);
    print_and_log_sf_setting(setting);
}

void print_and_log_output_setting(Shannon_C_setting & setting)
{
    Local_files & local_files = setting.local_files;
    std::cout << "\033[1;33m";
    std::cout << "output save to           : " << local_files.output_path << std::endl;
    std::cout << "output_seq_min_len is    : " << setting.output_seq_min_len << std::endl;
    std::cout << "\033[0m" << std::endl;
    shc_log_info(shc_logname, "output save to             : %s\n", local_files.output_kmer_path.c_str());
    shc_log_info(shc_logname, "output_seq_min_len         : %d\n", setting.output_seq_min_len);
}

void print_and_log_ref_setting(Shannon_C_setting & setting)
{
    std::cout << "\033[1;33m";
    if(!setting.local_files.reference_seq_path.empty())
        std::cout << "reference path           : " << setting.local_files.reference_seq_path << std::endl;
    else
        std::cout << "reference path           : No ref available" << std::endl;
    std::cout << "\033[0m" << std::endl;

    if(!setting.local_files.reference_seq_path.empty())
        shc_log_info(shc_logname, "reference path           : %s\n", setting.local_files.reference_seq_path.c_str());
    else
        shc_log_info(shc_logname, "reference path           : No ref available\n");
}

void print_and_log_partition_setting(Shannon_C_setting & setting)
{
    std::cout << "\033[1;31m";  //34 blue, 31 red, 35 purple
    std::cout << "Duplicate correction     *********** " << std::endl;
    std::cout << "load_factor              : " << setting.dup_setting.load_factor << std::endl;
    std::cout << "rmer_length              : " << (uint16_t)setting.dup_setting.rmer_length << std::endl;
    std::cout << "min_count                : " << setting.dup_setting.min_count << std::endl;
    std::cout << "min_len                  : " << setting.dup_setting.min_len << std::endl;
    std::cout << "threshold                : " << setting.dup_setting.threshold << std::endl;
    std::cout << "is_use_set               : " << ((setting.dup_setting.is_use_set)?("Yes"):("No")) << std::endl;
    std::cout << "num_sort_thread          : " << ((setting.dup_setting.num_sort_thread)) << std::endl;
    std::cout << std::endl;

    std::cout << "\033[1;31m";  //34 blue, 31 red, 35 purple
    std::cout << "Metis setup              *********** " << std::endl;
    std::cout << "use_multiple_partition   : " << ((setting.metis_setup.is_multiple_partition)?("Yes"):("No")) << std::endl;
    std::cout << "partition_size           : " << setting.metis_setup.partition_size << std::endl;
    std::cout << "non_partition_size       : " << setting.metis_setup.non_partition_size << std::endl;
    std::cout << "penalty                  : " << setting.metis_setup.penalty << std::endl;
    std::cout << "overload                 : " << setting.metis_setup.overload << std::endl;
    std::cout << std::endl;

    std::cout << "\033[1;31m";  //34 blue, 31 red, 35 purple
    std::cout << "Contig graph setup       *********** " << std::endl;
    std::cout << "num_test                 : " << setting.contig_graph_setup.num_test << std::endl;
    std::cout << "is_assign_best           : " << ((setting.contig_graph_setup.is_assign_best)?("Yes"):("No")) << std::endl;
    std::cout << "read_sampler_k           : " << setting.contig_graph_setup.read_sampler_k << std::endl;
    std::cout << "\033[0m" << std::endl;
    std::cout << std::endl;

    shc_log_info(shc_logname, "Duplicate correction     ***********\n");
    shc_log_info(shc_logname, "load_factor              : %f\n", setting.dup_setting.load_factor);
    shc_log_info(shc_logname, "rmer_length              : %d\n", (uint16_t)setting.dup_setting.rmer_length);
    shc_log_info(shc_logname, "min_count                : %d\n", setting.dup_setting.min_count);
    shc_log_info(shc_logname, "min_len                  : %d\n", setting.dup_setting.min_len);
    shc_log_info(shc_logname, "threshold                : %f\n", setting.dup_setting.threshold);
    shc_log_info(shc_logname, "is_use_set               : %s\n", ((setting.dup_setting.is_use_set)?("Yes"):("No")));
    shc_log_info(shc_logname, "num_sort_thread          : %d\n", ((setting.dup_setting.num_sort_thread)));
    shc_log_info(shc_logname, "\n");

    shc_log_info(shc_logname, "Metis setup              *********** \n");
    shc_log_info(shc_logname, "use_multiple_partition   : %s\n", ((setting.metis_setup.is_multiple_partition)?("Yes"):("No")));
    shc_log_info(shc_logname, "partition_size           : %d\n", setting.metis_setup.partition_size);
    shc_log_info(shc_logname, "non_partition_size       : %d\n", setting.metis_setup.non_partition_size);
    shc_log_info(shc_logname, "penalty `                : %d\n", setting.metis_setup.penalty);
    shc_log_info(shc_logname, "overload                 : %f\n", setting.metis_setup.overload);
    shc_log_info(shc_logname, "\n");

    shc_log_info(shc_logname, "Contig graph setup       *********** \n");
    shc_log_info(shc_logname, "num_test                 : %d\n", setting.contig_graph_setup.num_test);
    shc_log_info(shc_logname, "is_assign_best           : %s\n", ((setting.contig_graph_setup.is_assign_best)?("Yes"):("No")));
    shc_log_info(shc_logname, "read_sampler_k           : %d\n", setting.contig_graph_setup.read_sampler_k);

    shc_log_info(shc_logname, "\n");
}

void print_and_log_input_path_setting(Shannon_C_setting & setting)
{
    Local_files & local_files = setting.local_files;
    std::cout << "\033[1;33m";
    if(!local_files.input_kmer_path.empty())
    {
        std::cout << "single kmer input from   : " << local_files.input_kmer_path << std::endl;
    }
    if(local_files.has_single)
    {
        std::cout << "single read input from   : " << local_files.input_read_path << std::endl;
    }

    if(local_files.has_pair)
    {
        std::cout << "read pair1 input from    : " << local_files.input_read_path_1 << std::endl;
        std::cout << "read pair2 input from    : " << local_files.input_read_path_2 << std::endl;
    }
    std::cout << "\033[0m" << std::endl;


    if(!local_files.input_kmer_path.empty())
    {
        shc_log_info(shc_logname, "single kmer input from   : %s", local_files.input_kmer_path.c_str());
    }
    if(local_files.has_single)
    {
        shc_log_info(shc_logname, "single read input from   : %s", local_files.input_read_path.c_str());
    }

    if(local_files.has_pair)
    {
        shc_log_info(shc_logname, "read pair1 input from    : %s\n", local_files.input_read_path_1.c_str());
        shc_log_info(shc_logname, "read pair2 input from    : %s\n", local_files.input_read_path_2.c_str());
    }
    if(!local_files.input_kmer_path.empty())
    {
        shc_log_info(shc_logname, "single kmer input from   : %s\n", local_files.input_kmer_path.c_str());
    }
}

void print_and_log_read_length_setting(Shannon_C_setting & setting)
{
    std::cout << "\033[1;33m";
    std::cout << "has_single               : " << ((setting.has_single)?("Yes"):("No")) << std::endl;
    if(setting.has_single)
        std::cout << "single read length       : " << (setting.single_read_length) << std::endl;
    std::cout << "has_pair                 : " << ((setting.has_pair)?("Yes"):("No")) << std::endl;
    if(setting.has_pair)
    {
        std::cout << "pair 1 length            : " << (setting.pair_1_read_length) << std::endl;
        std::cout << "pair 2 length            : " << (setting.pair_2_read_length) << std::endl;
    }
    std::cout << "\033[0m";

    shc_log_info(shc_logname, "has_single               : %s\n", ((setting.has_single)?("Yes"):("No")));
    if(setting.has_single)
        shc_log_info(shc_logname, "single length            : %d\n", (setting.single_read_length));
    shc_log_info(shc_logname, "has_pair                 : %s\n", ((setting.has_pair)?("Yes"):("No")));
    if(setting.has_pair)
    {
        shc_log_info(shc_logname, "pair 1 length            : %d\n", (setting.pair_1_read_length));
        shc_log_info(shc_logname, "pair 2 length            : %d\n", (setting.pair_2_read_length));
    }
}

void print_and_log_kmer_strand_setting(Shannon_C_setting & setting)
{
    std::cout << "\033[1;33m";
    std::cout << "kmer_length is           : " << static_cast<uint16_t>(setting.kmer_length) << std::endl;
    std::cout << "double stranded          : " << ((setting.is_double_stranded)?("Yes"):("No")) << std::endl;
    std::cout << "\033[0m";
    shc_log_info(shc_logname, "kmer_length is           : %d\n", static_cast<uint16_t>(setting.kmer_length));
    shc_log_info(shc_logname, "double stranded          : %s\n", ((setting.is_double_stranded)?("Yes"):("No")));
}

void print_and_log_general_setting(Shannon_C_setting & setting)
{
    ;
}

void print_and_log_mb_setting(Shannon_C_setting & setting)
{
    std::cout << "\033[1;34m";
    std::cout << "Multi-bridge     ***********" << std::endl;
    std::cout << "max_hop_path             : " << setting.seq_graph_setup.max_hop_path << std::endl;
    std::cout << "\033[0m" << std::endl;
    shc_log_info(shc_logname, "Multi-bridge     ***********\n");
    shc_log_info(shc_logname, "max_hop_path             : %d\n", setting.seq_graph_setup.max_hop_path);
}

void print_and_log_sf_setting(Shannon_C_setting & setting)
{
    std::cout << "\033[1;34m";
    std::cout << "Sparse flow     ***********" << std::endl;
    std::cout << "sparse flow multiple test: " << setting.sparse_flow_setup.multiple_test << std::endl;
    std::cout << "\033[0m" << std::endl;
    shc_log_info(shc_logname, "Sparse flow     ***********\n");
    shc_log_info(shc_logname, "sparse flow multiple test: %d\n", setting.sparse_flow_setup.multiple_test);
}

void print_and_log_multi_graph_setting(Shannon_C_setting & setting)
{
    std::cout << "\033[1;34m";
    std::cout << "Multi-graph     ***********" << std::endl;
    std::cout << "num_parallel             : " << setting.num_parallel << std::endl;
    std::cout << "\033[0m" << std::endl;
    shc_log_info(shc_logname, "Multi-graph     ***********\n");
    shc_log_info(shc_logname, "num_parallel             : %d\n", setting.num_parallel);
}
