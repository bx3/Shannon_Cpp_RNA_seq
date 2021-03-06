#include "log.h"

char shc_logname[200] = {0};
static pthread_mutex_t log_lock = PTHREAD_MUTEX_INITIALIZER;
int init_mem = 0;

void start_timer(struct Block_timer * bt)
{
    bt->start = std::chrono::system_clock::now();
    //clock_gettime(CLOCK_MONOTONIC, &bt->nano_start);
    //bt->mem_start = get_proc_mem_value();
}

void print_important_notice(std::string msg)
{
    std::cout << "\033[0;33m";
    std::cout << "\n** [IMPORTANT MESSAGE] " << std::endl
              << "** " + msg
              << "** [IMPORTANT MESSAGE ENDS]";
    std::cout << "\033[0m" << std::endl << std::endl;
    shc_log_info(shc_logname, "\n** [IMPORTANT MESSAGE]\n");
    shc_log_info(shc_logname, "\n** %s", msg.c_str());
    shc_log_info(shc_logname, "** [IMPORTANT MESSAGE ENDS]\n");
}

void print_warning_notice(std::string msg)
{
    std::cout << "\033[0;31m";
    std::cout << "\n** [IMPORTANT MESSAGE] " << std::endl
              << "** " + msg
              << "** [IMPORTANT MESSAGE ENDS]";
    std::cout << "\033[0m" << std::endl << std::endl;
    shc_log_info(shc_logname, "\n** [IMPORTANT MESSAGE]\n");
    shc_log_info(shc_logname, "\n** %s", msg.c_str());
    shc_log_info(shc_logname, "** [IMPORTANT MESSAGE ENDS]\n");
}

void print_timer(struct Block_timer * bt)
{
    
    std::cout << "\033[0;33m";
    std::cout << "using "
              << bt->nTime/MINUTE_PER_SEC/HOUR_PER_MINUTE << " hours "
              << "<=> " << bt->nTime/HOUR_PER_MINUTE << " minutes "
              << "<=> " << bt->nTime << " sec ";
    std::cout << "\033[0m" << std::endl << std::endl;
}

void stop_timer(struct Block_timer * bt)
{
    //clock_gettime(CLOCK_MONOTONIC,&bt->nano_stamp);
    bt->end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = bt->end - bt->start;
    bt->nTime = static_cast<uint64_t>(elapsed_seconds.count());
    //int mem_use = get_proc_mem_value() - bt->mem_start;
    print_timer(bt);
}

uint64_t take_time(struct Block_timer * bt)
{
    std::chrono::time_point<std::chrono::system_clock> now  = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = now - bt->start;
    uint64_t dur = static_cast<uint64_t>(elapsed_seconds.count());
    return dur;
}

void stop_timer_np(struct Block_timer * bt)
{
    bt->end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = bt->end - bt->start;
    bt->nTime = static_cast<uint64_t>(elapsed_seconds.count());
    //clock_gettime(CLOCK_MONOTONIC,&bt->nano_stamp);
    //bt->nTime = (bt->nano_stamp.tv_sec - bt->nano_start.tv_sec);
}


void log_stop_timer(struct Block_timer * bt)
{
    bt->end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = bt->end - bt->start;
    bt->nTime = static_cast<uint64_t>(elapsed_seconds.count());
    //clock_gettime(CLOCK_MONOTONIC,&bt->nano_stamp);
    //bt->nTime = (bt->nano_stamp.tv_sec - bt->nano_start.tv_sec);
    //int mem_use = 0;// get_proc_mem_value() - bt->mem_start;
    shc_log_info(shc_logname, "**\t\tusing %d hours <=> %d minutes <=> %d sec\n\n",
                    bt->nTime/MINUTE_PER_SEC/HOUR_PER_MINUTE,
                    bt->nTime/HOUR_PER_MINUTE, bt->nTime);
}

int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int get_proc_mem_value(){ //Note: this value is in GB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result/1024/1024;
}

// for debugging
void get_vector_string(std::vector<contig_num_t> & contig_list, std::stringstream & vec_str)
{
    vec_str.str("");
    std::copy(contig_list.begin(), contig_list.end(), std::ostream_iterator<int>(vec_str, " "));
}


void print_byte_list(uint8_t* byte_list, uint16_t out_length)
{
    for (int i=0; i< out_length; i++)
        printf("%u ", byte_list[i]);
    printf("\n");
}

void print_four_base(char* four_base, int length)
{
    char *base = new char[length+1];
    memcpy(base, four_base, length);
    base[length] = '\0';
    printf("%s \t", base);
}

//static bool info_logfile_cleared = false;

void info_log_info(const char * filename, const char* format, ...)
{
    //char filename[50];
    //if(!info_logfile_cleared){
    //    fclose(fopen(filename, "w"));
    //    info_logfile_cleared = true;
    //}
    pthread_mutex_lock(&log_lock);
    va_list args;
    va_start (args, format);
    FILE* stream;
    stream = fopen(filename,"a+");
    vfprintf (stream, format, args);
    va_end (args);
    fclose(stream);

    pthread_mutex_unlock(&log_lock);
}

// hard coded using with caution
void info_log_num_without_new_line(char *filename, size_t num)
{
    info_log_info(filename, "%3d ", num);
}

void info_log_str_without_new_line(char *filename, const char * c)
{
    info_log_info(filename, "%s ", c);
}

void info_print_bit(char *filename, uint8_t bit_to_print)
{
    uint16_t mask = 0x1;
    uint16_t selectBit = 0x0;
    uint16_t result = 0x0;
    //backward order
    for (int i = 0; i< 8 ; i++)
    {
        selectBit = (((mask<<i) & bit_to_print)>>i) & mask;
        result = (result << 1) | selectBit;
    }
    //print out bit
    info_log_info(filename, "[Info content][INFO] ");
    for (int i = 0; i< 8;i++)
    {
        info_log_info(filename, "%d", (((mask<<i) & result)>>i) & mask);
    }
    info_log_info(filename, "\n");
}

#ifdef SHC_LOGGING_ENABLED
#include <time.h>

static shc_log_level filter_level = SHC_LOG_LEVEL_VERBOSE;
static bool logfile_cleared = false;

/** this function is used with MARCO to write the desired message on the screen*/
void shc_log_write(shc_log_level level, const char *caller, const char *format, ...)
{
    /* Only process this message if its level exceeds the current threshold */
    if (level >= filter_level)
    {
        va_list args;
        char s[100000];

        /* Write the log message */
        va_start(args, format);
        vsprintf(s, format, args);
        printf("[%s]%s", caller, s);

        //vfprintf(stderr, format, args);
        va_end(args);
    }
}



/**
 * this function is used with MARCO to write data in a certain file specified by the
 * filename in the argument. The file will be automatically cleared when this is a
 * new process/test.
 */
void shc_log_file_write(const char* filename,shc_log_level level, const char *caller,
        const char *format, ...)
{
    pthread_mutex_lock(&log_lock);
    if(!logfile_cleared){
        FILE* fp = fopen(filename, "w");
        if(fp != NULL){
            time_t rawtime;
            time ( &rawtime );
            fprintf(fp, "SHC Log File: [%s] \n", ctime (&rawtime));
            fclose(fp);
        }
        logfile_cleared = true;
    }

    FILE* fp = fopen(filename, "a+");
    if(fp!=NULL){
        /* Only process this message if its level exceeds the current threshold */
        if (level >= filter_level)
        {
            va_list args;
            char s[100000];

            /* Write the log message */
            va_start(args, format);
            vsprintf(s, format, args);
            fprintf(fp, "[%s]%s", caller, s);
            va_end(args);
        }
        fclose(fp);
    }
    pthread_mutex_unlock(&log_lock);
}


#ifdef DCF_TX_CONTENT_LOGGING_ENABLED
/**
 * this function is used to write detailed  information into a log
 * file, which includes delimitor
 */
#include <time.h>
static bool sch_contig_logfile_cleared = false;
void tx_content_log_info(uint8_t* addr, const char* format, ...)
{
    char filename[50];
    sprintf(filename, "TX_CONTENT_%02x%02x%02x%02x%02x%02x.log", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
    if(!tx_content_logfile_cleared){
        fclose(fopen(filename, "w"));
        tx_content_logfile_cleared = true;
    }
    va_list args;
    va_start (args, format);
    FILE* stream;
    stream = fopen(filename,"a+");
    vfprintf (stream, format, args);
    va_end (args);
    fclose(stream);
}

/**
 * this function is used with tx_content_log_info, this function is used to
 * print out every bit of a uint16_t type, the LSB is on the right side.
 * @param addr
 * @param bit_to_print
 */
void tx_content_print_bit(uint8_t *addr, uint16_t bit_to_print)
{
    uint16_t mask = 0x1;
    uint16_t selectBit = 0x0;
    uint16_t result = 0x0;
    //backward order
    for (int i = 0; i< 16 ; i++)
    {
        selectBit = (((mask<<i) & bit_to_print)>>i) & mask;
        result = (result << 1) | selectBit;
    }
    //print out bit
    for (int i = 0; i< 16;i++)
    {
        tx_content_log_info(addr, "%d", (((mask<<i) & result)>>i) & mask);
    }
}
#endif

#ifdef SHC_CONTIG_LOGGING_ENABLED
/**
 * this function is used to write detailed  information into a log
 * file, which includes delimitor
 */
static bool shc_contig_logfile_cleared = false;
void shc_contig_log_info(const char* format, ...)
{
    char filename[50];
    sprintf(filename, "SHC_CONIG_INFO.log");
    if(!shc_contig_logfile_cleared){
        fclose(fopen(filename, "w"));
        shc_contig_logfile_cleared = true;
    }
    va_list args;
    va_start (args, format);
    FILE* stream;
    stream = fopen(filename,"a+");
    vfprintf (stream, format, args);
    va_end (args);
    fclose(stream);
}
#endif

#endif
