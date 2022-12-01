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
int telecam_seq_old = 0;

// Callback function
void telecam_callback(const sensor_msgs::ImageConstPtr& msg)
{
    // seq = msg->header.seq;
    seq = msg->header.seq;
}

void check_seq(diagnostic_updater::DiagnosticStatusWrapper &stat)
{ 
    if(seq == telecam_seq_old) 
        stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "CAMERA OFF");
    else
        stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "CAMERA ON");

    stat.add("Seq prev", telecam_seq_old);
    telecam_seq_old = seq;
    stat.add("Seq", seq);
}



