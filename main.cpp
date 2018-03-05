#include "asioselector.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AsioSelector w;
    //std::vector
    //w.addDevice();
    std::vector<double> sample_rates = {44100, 48000};
    //std::vector<uint64_t> audio_formats = {0, 1, 2};
    std::vector<std::string> audio_formats = {"16 Bit Int", "32 Bit Int", "32 Bit Float"};
    std::vector<uint64_t> buffer_sizes = {32, 64, 128, 256, 512, 1024};
    w.addDevice("Saffire",sample_rates,buffer_sizes,audio_formats);
    w.addDevice("Reaper",sample_rates,buffer_sizes,audio_formats);
    w.addDevice("Reaper2",sample_rates,buffer_sizes,audio_formats);
    w.addDevice("Reaper3",sample_rates,buffer_sizes,audio_formats);
    w.addDevice("Reaper4",sample_rates,buffer_sizes,audio_formats);
    w.addDevice("Reaper5",sample_rates,buffer_sizes,audio_formats);
    w.addDevice("Reaper6",sample_rates,buffer_sizes,audio_formats);
    w.addDevice("Reaper7",sample_rates,buffer_sizes,audio_formats);
    w.addDevice("Reaper8",sample_rates,buffer_sizes,audio_formats);
    w.addDevice("Reaper9",sample_rates,buffer_sizes,audio_formats);
    w.addDevice("Reaper10",sample_rates,buffer_sizes,audio_formats);
    w.addDevice("Reaper11",sample_rates,buffer_sizes,audio_formats);
    w.addDevice("Reaper12",sample_rates,buffer_sizes,audio_formats);
    w.addDevice("Reaper13",sample_rates,buffer_sizes,audio_formats);
    w.addDevice("Reaper14",sample_rates,buffer_sizes,audio_formats);
    w.addDevice("Reaper15",sample_rates,buffer_sizes,audio_formats);
    w.addDevice("Reaper16",sample_rates,buffer_sizes,audio_formats);

    w.setActiveDeviceUnique(true);
    w.show();

    return a.exec();
}
