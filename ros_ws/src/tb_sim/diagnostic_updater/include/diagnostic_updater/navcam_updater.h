#include <diagnostic_updater/diagnostic_updater.h>
#include <std_msgs/Bool.h>
#include <diagnostic_updater/publisher.h>
#include <sensor_msgs/Image.h> 
#include <math.h>
#ifdef ERROR
#undef ERROR
#endif
using namespace diagnostic_updater;

int seq;
int navcam_seq_old = 0;

// Callback function
void navcam_callback(const sensor_msgs::ImageConstPtr& msg)
{
    // seq = msg->header.seq;
    seq = msg->header.seq;
}

void check_seq(diagnostic_updater::DiagnosticStatusWrapper &stat)
{ 
    if(seq == navcam_seq_old) 
        stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "CAMERA OFF");
    else
        stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "CAMERA ON");

    stat.add("Seq prev", navcam_seq_old);
    navcam_seq_old = seq;
    stat.add("Seq", seq);
}


