#include "asioselector.h"
#include "ui_asioselector.h"

AsioSelector::AsioSelector(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AsioSelector)
{
    ui->setupUi(this);
}

AsioSelector::~AsioSelector()
{
    delete ui;
}

void AsioSelector::addDevice(std::string device_name, std::vector<double> sample_rates, std::vector<uint64_t> buffer_sizes, std::vector<std::string> audio_formats){
    sample_rate_list.push_back(sample_rates);
    buffer_size_list.push_back(buffer_sizes);
    audio_format_list.push_back(audio_formats);
    //default the first of array
    default_sample_rate.push_back(sample_rates[0]);
    default_buffer_size.push_back(buffer_sizes[0]);
    default_audio_format.push_back(audio_formats[0]);

    current_sample_rate.push_back(sample_rates[0]);
    current_buffer_size.push_back(buffer_sizes[0]);
    current_audio_format.push_back(audio_formats[0]);

    _device_active.push_back(false);
    _use_minimal_latency.push_back(true);
    _use_optimal_format.push_back(true);
    _use_device_timing.push_back(false);
    QListWidgetItem* item = new QListWidgetItem(device_name.c_str());
    ui->asioDevicesList->addItem(item);
}

void AsioSelector::addDevice(std::string device_name, std::vector<double> sample_rates, double default_sample_rate,
                             std::vector<uint64_t> buffer_sizes, uint32_t default_buffer_size, std::vector<std::string> audio_formats, std::string default_audio_format){
    sample_rate_list.push_back(sample_rates);
    buffer_size_list.push_back(buffer_sizes);
    audio_format_list.push_back(audio_formats);
    //default the first of array
    bool found = false;
    for(size_t i = 0; i < sample_rates.size(); i++){
        if(sample_rates[i] == default_sample_rate){
            found = true;
            break;
        }
    }
    if(found){
        this->default_sample_rate.push_back(default_sample_rate);
        this->current_sample_rate.push_back(default_sample_rate);
    } else {
        this->default_sample_rate.push_back(sample_rates[0]);
        this->current_sample_rate.push_back(sample_rates[0]);
    }

    found = false;
    for(size_t i = 0; i < buffer_sizes.size(); i++){
        if(buffer_sizes[i] == default_buffer_size){
            found = true;
            break;
        }
    }
    if(found){
        this->default_buffer_size.push_back(default_buffer_size);
        this->current_buffer_size.push_back(default_buffer_size);
    } else {
        this->default_buffer_size.push_back(buffer_sizes[0]);
        this->current_buffer_size.push_back(buffer_sizes[0]);
    }

    found = false;
    for(size_t i = 0; i < audio_formats.size(); i++){
        if(audio_formats[i] == default_audio_format){
            found = true;
            break;
        }
    }
    if(found){
        this->default_audio_format.push_back(default_audio_format);
        this->current_audio_format.push_back(default_audio_format);
    } else {
        this->default_audio_format.push_back(audio_formats[0]);
        this->current_audio_format.push_back(audio_formats[0]);
    }

    _device_active.push_back(false);
    _use_minimal_latency.push_back(true);
    _use_optimal_format.push_back(true);
    _use_device_timing.push_back(false);
    QListWidgetItem* item = new QListWidgetItem(device_name.c_str());
    ui->asioDevicesList->addItem(item);
}

void AsioSelector::on_okButton_clicked()
{
    if(selected_device >= 0 && selected_device < ui->asioDevicesList->count()){
        this->current_sample_rate[selected_device] = ui->asioSampleRate->currentData().toDouble();
        this->current_buffer_size[selected_device] = ui->asioBufferSize->currentData().toULongLong();
        this->current_audio_format[selected_device] = ui->asioDataFormat->currentData().toString().toUtf8().constData();

        if(unique_active_device){
            if(ui->activeDevice->isChecked()){
                size_t i = 0;
                for(; i < selected_device; i++){
                    this->_device_active[i] = false;
                }
                this->_device_active[selected_device] = true;
                i++;
                for(; i < this->_device_active.size(); i++){
                    this->_device_active[i] = false;
                }
            } else {
                this->_device_active[selected_device] = false;
            }
        } else {
            this->_device_active[selected_device] = ui->activeDevice->isChecked();
        }
        this->_use_optimal_format[selected_device] = ui->optimalFormat->isChecked();
        this->_use_device_timing[selected_device] = ui->deviceTiming->isChecked();
        this->_use_minimal_latency[selected_device] = ui->lowestLatency->isChecked();
    }
    this->close();
}

void AsioSelector::on_applyButton_clicked()
{
    if(selected_device >= 0 && selected_device < ui->asioDevicesList->count()){
        this->current_sample_rate[selected_device] = ui->asioSampleRate->currentData().toDouble();
        this->current_buffer_size[selected_device] = ui->asioBufferSize->currentData().toULongLong();
        this->current_audio_format[selected_device] = ui->asioDataFormat->currentData().toString().toUtf8().constData();
;
        if(unique_active_device){
            if(ui->activeDevice->isChecked()){
                size_t i = 0;
                for(; i < selected_device; i++){
                    this->_device_active[i] = false;
                }
                this->_device_active[selected_device] = true;
                i++;
                for(; i < this->_device_active.size(); i++){
                    this->_device_active[i] = false;
                }
            } else {
                this->_device_active[selected_device] = false;
            }
        } else {
            this->_device_active[selected_device] = ui->activeDevice->isChecked();
        }
        this->_use_optimal_format[selected_device] = ui->optimalFormat->isChecked();
        this->_use_device_timing[selected_device] = ui->deviceTiming->isChecked();
        this->_use_minimal_latency[selected_device] = ui->lowestLatency->isChecked();
    }
}

void AsioSelector::on_defaultsButton_clicked()
{
    if(selected_device >= 0 && selected_device < ui->asioDevicesList->count()){
        //long way around via a search to get the default
        QVariant s = QVariant(default_sample_rate[selected_device]);//sample_rate_list[selected_device][0]);
        ui->asioSampleRate->setCurrentIndex(ui->asioSampleRate->findText(s.toString()));

        s = QVariant(default_buffer_size[selected_device]);//buffer_size_list[selected_device][0]);
        ui->asioBufferSize->setCurrentIndex(ui->asioBufferSize->findText(s.toString()));

        s = QVariant(default_audio_format[selected_device].c_str());//audio_format_list[selected_device][0].c_str());
        ui->asioDataFormat->setCurrentIndex(ui->asioDataFormat->findText(s.toString()));

        ui->activeDevice->setChecked( false );
        ui->lowestLatency->setChecked( true );
        ui->optimalFormat->setChecked( true );
        ui->deviceTiming->setChecked( false );
    }
}

void AsioSelector::on_asioDevicesList_currentRowChanged(int currentRow)
{
    this->selected_device = currentRow;
    ui->asioSampleRate->clear();
    for(size_t i = 0; i < sample_rate_list[currentRow].size(); i++){
        QVariant t = QVariant(sample_rate_list[currentRow][i]);
        ui->asioSampleRate->addItem( t.toString(), t );
    }
    QVariant s = QVariant(current_sample_rate[currentRow]);
    ui->asioSampleRate->setCurrentIndex(ui->asioSampleRate->findText(s.toString()));

    ui->asioBufferSize->clear();
    for(size_t i = 0; i < buffer_size_list[currentRow].size(); i++){
        QVariant t = QVariant(buffer_size_list[currentRow][i]);
        ui->asioBufferSize->addItem(t.toString(), t);
    }
    s = QVariant(current_buffer_size[currentRow]);
    ui->asioBufferSize->setCurrentIndex(ui->asioBufferSize->findText(s.toString()));

    ui->asioDataFormat->clear();
    for(size_t i = 0; i < audio_format_list[currentRow].size(); i++){
        QVariant t = QVariant(audio_format_list[currentRow][i].c_str());
        QString ts = t.toString();
        ui->asioDataFormat->addItem(ts, ts);
    }
    s = QVariant(current_audio_format[currentRow].c_str());
    ui->asioDataFormat->setCurrentIndex(ui->asioDataFormat->findText(s.toString()));

    ui->activeDevice->setChecked( _device_active[currentRow] );
    ui->lowestLatency->setChecked( _use_minimal_latency[currentRow] );
    ui->deviceTiming->setChecked( _use_device_timing[currentRow] );
    ui->optimalFormat->setChecked( _use_optimal_format[currentRow] );
}

std::vector<uint32_t> AsioSelector::getActiveDevices(){
    std::vector<uint32_t> ret;
    ret.reserve(_device_active.size());
    for(size_t i = 0; i < _device_active.size(); i++){
        if(_device_active[i])
            ret.push_back(i);
    }
    ret.shrink_to_fit();
    return ret;
}
