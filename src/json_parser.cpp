#include "json_parser.h"

void parser_setting_file(std::string & file_path, Shannon_C_setting & setting)
{
    using boost::property_tree::ptree;

    std::ifstream json_file(file_path.c_str());
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

    setting.kmer_length = kmer_length;
    setting.has_single = has_single;
    setting.has_pair = has_pair;
    setting.is_double_stranded = is_double_stranded;
    setting.is_compress = is_compress;
    setting.single_read_length = single_read_length;
    setting.pair_1_read_length = pair_1_read_length;
    setting.pair_2_read_length = pair_2_read_length;

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
    setting.contig_graph_setup.set_para(num_test, is_assign_best);

    //metis_setup
    ptree metis_setup = pt.get_child("metis_setup");
    bool use_multiple_partition = metis_setup.get<bool>
                                                    ("use_multiple_partition");
    idx_t partition_size = metis_setup.get<idx_t>("partition_size");
    idx_t penalty = metis_setup.get<idx_t>("penalty");
    real_t overload = metis_setup.get<real_t>("overload");
    setting.metis_setup.set_para(use_multiple_partition, partition_size,
                                 overload,  penalty);
    // multi_graph_setup
    ptree multi_graph_setup = pt.get_child("multi_graph_setup");
    int num_parallel = multi_graph_setup.get<int>("num_parallel");
    int hop_pair = multi_graph_setup.get<int>("max_hop_for_pair_search");
    int hop_path = multi_graph_setup.get<int>("max_hop_for_known_path");
    int single_node_seq_len = multi_graph_setup.get<int>("single_node_seq_len");
    int mate_pair_len = multi_graph_setup.get<int>("mate_pair_len");
    setting.multi_graph_setup.set_para(num_parallel, hop_pair, hop_path,
                                         single_node_seq_len, mate_pair_len);

    //sparse_flow setup
    ptree sparse_flow_setup = pt.get_child("sparse_flow_setup");
    int multiple_test = sparse_flow_setup.get<int>("multiple_test");
    int sf_num_parallel = sparse_flow_setup.get<int>("sf_num_parallel");
    setting.sparse_flow_setup.set_para(multiple_test, sf_num_parallel);

    // output setup
    ptree output_setup = pt.get_child("output_setup");
    bool kmer_with_info = output_setup.get<bool>("kmer_with_info");
    bool contig = output_setup.get<bool>("contig");
    bool component_array = output_setup.get<bool>("component_array");
    bool read_to_component = output_setup.get<bool>("read_to_component");
    bool kmer_to_component = output_setup.get<bool>("kmer_to_component");

    setting.output_setup.set_para(kmer_with_info, contig, component_array,
                         read_to_component, kmer_to_component);
}

void print_setting(Shannon_C_setting & setting)
{
    std::cout << "\033[1;31m";  //34 blue, 31 red, 35 purple
    std::cout << "General setting" << std::endl;
    std::cout << "kmer_length is           : " << static_cast<uint16_t>(setting.kmer_length) << std::endl;
    std::cout << "double stranded          : " << ((setting.is_double_stranded)?("Yes"):("No")) << std::endl;
    std::cout << "has_single               : " << ((setting.has_single)?("Yes"):("No")) << std::endl;
    if(setting.has_single)
        std::cout << "single length            : " << (setting.single_read_length) << std::endl;
    std::cout << "has_pair                 : " << ((setting.has_pair)?("Yes"):("No")) << std::endl;
    if(setting.has_pair)
    {
        std::cout << "pair 1 length            : " << (setting.pair_1_read_length) << std::endl;
        std::cout << "pair 2 length            : " << (setting.pair_2_read_length) << std::endl;
    }
    std::cout << "use compressed contig    : " << ((setting.is_compress)?("Yes"):("No")) << std::endl;
    std::cout << std::endl;

    print_local_file_system(&setting.local_files);

    std::cout << "\033[1;33m";  //34 blue, 31 red, 35 purple
    std::cout << "Duplicate correction     *********** " << std::endl;
    std::cout << "load_factor              : " << setting.dup_setting.load_factor << std::endl;
    std::cout << "rmer_length              : " << (uint16_t)setting.dup_setting.rmer_length << std::endl;
    std::cout << "min_count                : " << setting.dup_setting.min_count << std::endl;
    std::cout << "min_len                  : " << setting.dup_setting.min_len << std::endl;
    std::cout << "threshold                : " << setting.dup_setting.threshold << std::endl;
    std::cout << "is_use_set               : " << ((setting.dup_setting.is_use_set)?("Yes"):("No")) << std::endl;
    std::cout << "num_sort_thread          : " << ((setting.dup_setting.num_sort_thread)) << std::endl;
    std::cout << std::endl;

    std::cout << "\033[1;35m";  //34 blue, 31 red, 35 purple
    std::cout << "Metis setup              *********** " << std::endl;
    std::cout << "use_multiple_partition   : " << ((setting.metis_setup.is_multiple_partition)?("Yes"):("No")) << std::endl;
    std::cout << "partition_size           : " << setting.metis_setup.partition_size << std::endl;
    std::cout << "penalty                  : " << setting.metis_setup.penalty << std::endl;
    std::cout << "overload                 : " << setting.metis_setup.overload << std::endl;
    std::cout << std::endl;

    std::cout << "\033[1;35m";  //34 blue, 31 red, 35 purple
    std::cout << "Contig graph setup       *********** " << std::endl;
    std::cout << "num_test                 : " << setting.contig_graph_setup.num_test << std::endl;
    std::cout << "is_assign_best              : " << ((setting.contig_graph_setup.is_assign_best)?("Yes"):("No")) << std::endl;
    std::cout << std::endl;

    std::cout << "\033[1;35m";  //34 blue, 31 red, 35 purple
    std::cout << "multi graph setup        *********** " << std::endl;
    std::cout << "num_parallel              : " << setting.multi_graph_setup.num_parallel << std::endl;
    std::cout << "max_hop_pair             : " << setting.multi_graph_setup.max_hop_pair << std::endl;
    std::cout << "max_hop_path             : " << setting.multi_graph_setup.max_hop_path << std::endl;
    std::cout << "single_node_seq_len      : " << setting.multi_graph_setup.single_node_seq_len << std::endl;
    std::cout << "mate_pair_len            : " << setting.multi_graph_setup.mate_pair_len << std::endl;
    std::cout << "sparse flow multiple test: " << setting.sparse_flow_setup.multiple_test << std::endl;
    std::cout << "sparse flow num parallel : " << setting.sparse_flow_setup.sf_num_parallel << std::endl;
    std::cout << std::endl;

    std::cout << "\033[1;34m";  //34 blue, 31 red, 35 purple
    std::cout << "Output setting           *********** " << std::endl;
    std::cout << "dump kmer with info      : " << ((setting.output_setup.kmer_with_info)?("Yes"):("No")) << std::endl;
    std::cout << "dump contig              : " << ((setting.output_setup.contig)?("Yes"):("No")) << std::endl;
    std::cout << "dump component_array     : " << ((setting.output_setup.component_array)?("Yes"):("No")) << std::endl;
    std::cout << "dump read to component   : " << ((setting.output_setup.read_to_component)?("Yes"):("No")) << std::endl;
    std::cout << "dump kmer to component   : " << ((setting.output_setup.kmer_to_component)?("Yes"):("No")) << std::endl;

    std::cout << "\033[0m" << std::endl;


}

void log_setting(Shannon_C_setting & setting)
{
    shc_log_info(shc_logname, "General setting\n");
    shc_log_info(shc_logname, "kmer_length is           : %d\n", static_cast<uint16_t>(setting.kmer_length));
    shc_log_info(shc_logname, "double stranded          : %s\n", ((setting.is_double_stranded)?("Yes"):("No")));
    shc_log_info(shc_logname, "has_single               : %s\n", ((setting.has_single)?("Yes"):("No")));

    if(setting.has_single)
        shc_log_info(shc_logname, "single length            : %d\n", (setting.single_read_length));
    shc_log_info(shc_logname, "has_pair                 : %s\n", ((setting.has_pair)?("Yes"):("No")));
    shc_log_info(shc_logname, "General setting\n");

    if(setting.has_pair)
    {
        shc_log_info(shc_logname, "pair 1 length            : %d\n", (setting.pair_1_read_length));
        shc_log_info(shc_logname, "pair 2 length            : %d\n", (setting.pair_2_read_length));
    }
    shc_log_info(shc_logname, "use compressed contig    : %s\n", ((setting.is_compress)?("Yes"):("No")));
    shc_log_info(shc_logname, "\n");

    log_local_file_system(&setting.local_files);

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
    shc_log_info(shc_logname, "penalty `                : %d\n", setting.metis_setup.penalty);
    shc_log_info(shc_logname, "overload                 : %f\n", setting.metis_setup.overload);
    shc_log_info(shc_logname, "\n");

    shc_log_info(shc_logname, "Contig graph setup       *********** \n");
    shc_log_info(shc_logname, "num_test                 : %d\n", setting.contig_graph_setup.num_test);
    shc_log_info(shc_logname, "is_assign_best              : %s\n", ((setting.contig_graph_setup.is_assign_best)?("Yes"):("No")));
    shc_log_info(shc_logname, "\n");

    shc_log_info(shc_logname, "multi graph setup        *********** \n");
    shc_log_info(shc_logname, "num_parallel              : %d\n", setting.multi_graph_setup.num_parallel);
    shc_log_info(shc_logname, "max_hop_pair             : %d\n", setting.multi_graph_setup.max_hop_pair);
    shc_log_info(shc_logname, "max_hop_path `           : %d\n", setting.multi_graph_setup.max_hop_path);
    shc_log_info(shc_logname, "single_node_seq_len      : %d\n", setting.multi_graph_setup.single_node_seq_len);
    shc_log_info(shc_logname, "mate_pair_len            : %d\n", setting.multi_graph_setup.mate_pair_len);
    shc_log_info(shc_logname, "sparse flow multiple test: %d\n", setting.sparse_flow_setup.multiple_test);
    shc_log_info(shc_logname, "sparse flow num parallel : %d\n", setting.sparse_flow_setup.sf_num_parallel);
    shc_log_info(shc_logname, "\n");

    shc_log_info(shc_logname, "Output setting           *********** \n");
    shc_log_info(shc_logname, "dump kmer with info      : %s\n", ((setting.output_setup.kmer_with_info)?("Yes"):("No")));
    shc_log_info(shc_logname, "dump contig              : %s\n", ((setting.output_setup.contig)?("Yes"):("No")));
    shc_log_info(shc_logname, "dump component_array     : %s\n", ((setting.output_setup.component_array)?("Yes"):("No")));
    shc_log_info(shc_logname, "dump read to component   : %s\n", ((setting.output_setup.read_to_component)?("Yes"):("No")));
    shc_log_info(shc_logname, "dump kmer to component   : %s\n", ((setting.output_setup.kmer_to_component)?("Yes"):("No")));
    shc_log_info(shc_logname, "\n");
}
