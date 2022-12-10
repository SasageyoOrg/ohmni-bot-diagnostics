#include <diagnostic_updater/diagnostic_updater.h>
#include <std_msgs/Bool.h>
#include <diagnostic_updater/publisher.h>
#include <sensor_msgs/LaserScan.h> 
#include <math.h>

#ifdef ERROR
#undef ERROR
#endif
using namespace diagnostic_updater;

int scan_seq_old = 0;
int seq;

float scan_threshold_max;
float scan_threshold_min;

std::vector<float> ranges;
int ranges_len;

std::vector<int> pos;

// Callback function
void scan_callback(const sensor_msgs::LaserScan::ConstPtr& msg){
    seq = msg->header.seq;

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
    bool detected = false;
    int pos = 0;

    for (int i = 0; (i < ranges_len); i++){
        if (ranges[i] > scan_threshold_min && ranges[i] <= scan_threshold_max){
            detected = true;
            pos = i;
        }
    }

    if(detected)
        stat.summaryf(diagnostic_msgs::DiagnosticStatus::ERROR, "SCAN ERROR: object detected [%f]cm away", ranges[pos]);
    else
        stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "SCAN OK");

    // LOGGING
    stat.add("Range Threshold MAX", scan_threshold_max);
    stat.add("Range Threshold min", scan_threshold_min);
}