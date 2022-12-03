#include <diagnostic_updater/diagnostic_updater.h>
#include <std_msgs/Bool.h>
#include <diagnostic_updater/publisher.h>
#include <sensor_msgs/LaserScan.h> 
#include <math.h>

#ifdef ERROR
#undef ERROR
#endif
using namespace diagnostic_updater;

int seq;
int scan_seq_old = 0;

std::vector<float> ranges;
float range_min;
float range_max;
float ranges_len   ;
float param_scan;

// Callback function
void scan_callback(const sensor_msgs::LaserScan::ConstPtr& msg){
    seq = msg->header.seq;

    range_max     = msg->range_max;
    range_min     = msg->range_min;
    ranges        = msg->ranges;
    ranges_len    = (msg->ranges).size();
}

void check_seq(diagnostic_updater::DiagnosticStatusWrapper &stat){ 
    if(seq == scan_seq_old) 
        stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "SCAN OFF");
    else
        stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "SCAN ON");

    stat.add("Seq prev", scan_seq_old);
    scan_seq_old = seq;
    stat.add("Seq", seq);
}

void check_range(diagnostic_updater::DiagnosticStatusWrapper &stat){ 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "SCAN OK");
    // for (int i = 0; i < ranges_len   ; i++){
    //     if (ranges[i] > range_min && ranges[i] < range_max)
    //         stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "SCAN OK");
    //     else if (ranges[i] > range_max)
    //         stat.summaryf(diagnostic_msgs::DiagnosticStatus::ERROR, "SCAN ERROR: range [%f] Too high", ranges[i]);
    //     else 
    //         stat.summaryf(diagnostic_msgs::DiagnosticStatus::ERROR, "SCAN ERROR: range [%f] Too low", ranges[i]);
    // }

    // LOGGING
    stat.add("Renge MIN", range_min);
    stat.add("Range MAX", range_max);

    //stat.add("Lenght Range", ranges_len   );
}



