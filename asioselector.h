#ifndef ASIOSELECTOR_H
#define ASIOSELECTOR_H

#include <QVariant>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMainWindow>

namespace Ui {
class AsioSelector;
}

class AsioSelector : public QMainWindow
{
    Q_OBJECT

public:
    explicit AsioSelector(QWidget *parent = 0);
    ~AsioSelector();
    void setActiveDeviceUnique(bool val){
        unique_active_device = val;
    }

    bool getActiveDeviceUnique(){
        return unique_active_device;
    }

    uint32_t getSelectedDevice(){
        return selected_device;
    }

    std::vector<uint32_t> getActiveDevices();

    void setSampleRateForDevice(uint32_t index, double sample_rate){
        this->current_sample_rate[index] = sample_rate;
    }

    void setBufferSizeForDevice(uint32_t index, uint64_t buffer_size){
        this->current_buffer_size[index] = buffer_size;
    }

    void setAudioFormatForDevice(uint32_t index, std::string audio_format){
        this->current_audio_format[index] = audio_format;
    }

    double getSampleRateForDevice(uint32_t index){
        return current_sample_rate[index];
    }

    uint64_t getBufferSizeForDevice(uint32_t index){
        return current_buffer_size[index];
    }

    std::string getAudioFormatForDevice(uint32_t index){
        return current_audio_format[index];
    }

    double getDefaultSampleRateForDevice(uint32_t index){
        return default_sample_rate[index];
    }

    uint64_t getDefaultBufferSizeForDevice(uint32_t index){
        return default_buffer_size[index];
    }

    std::string getDefaultAudioFormatForDevice(uint32_t index){
        return default_audio_format[index];
    }

    std::vector<double> getSampleRatesForDevice(uint32_t index){
        return sample_rate_list[index];
    }

    std::vector<uint64_t> getBufferSizesForDevice(uint32_t index){
        return buffer_size_list[index];
    }

    std::vector<std::string> getAudioFormatsForDevice(uint32_t index){
        return audio_format_list[index];
    }

    void addDevice(std::string device_name, std::vector<double> sample_rates, std::vector<uint64_t> buffer_sizes, std::vector<std::string> audio_formats);

    void addDevice(std::string device_name, std::vector<double> sample_rates, double default_sample_rate,
                   std::vector<uint64_t> buffer_sizes, uint32_t default_buffer_size, std::vector<std::string> audio_formats, std::string default_audio_format);

private slots:
    void on_okButton_clicked();

    void on_applyButton_clicked();

    void on_defaultsButton_clicked();

    void on_asioDevicesList_currentRowChanged(int currentRow);

private:
    //QWidgetList* asioDevicesList;
    /*list of gui options, must be filled for gui to work*/
    std::vector<std::vector<double>> sample_rate_list;
    std::vector<std::vector<uint64_t>> buffer_size_list;
    std::vector<std::vector<std::string>> audio_format_list;

    /*the currently selected gui option for a particular device*/
    std::vector<double> current_sample_rate;
    std::vector<uint64_t> current_buffer_size;
    std::vector<std::string> current_audio_format;

    /*the default gui option for a particular device*/
    std::vector<double> default_sample_rate;
    std::vector<uint64_t> default_buffer_size;
    std::vector<std::string> default_audio_format;

    std::vector<bool> _device_active;
    std::vector<bool> _use_minimal_latency;
    std::vector<bool> _use_optimal_format;
    std::vector<bool> _use_device_timing;

    uint32_t selected_device = -1;

    bool unique_active_device = false;

    Ui::AsioSelector *ui;
};

#endif // ASIOSELECTOR_H
