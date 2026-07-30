#include "Observer.h"
#include <iostream>

// WeatherData类实现
WeatherData::WeatherData() : temperature(0.0), humidity(0.0), pressure(0.0) {
    observers.clear();
}

void WeatherData::registerObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void WeatherData::removeObserver(std::shared_ptr<Observer> observer) {
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void WeatherData::notifyObservers() {
    for (const auto& observer : observers) {
        observer->update(temperature, humidity, pressure);
    }
}

void WeatherData::measurementsChanged() {
    notifyObservers();
}

void WeatherData::setMeasurements(float temperature, float humidity, float pressure) {
    this->temperature = temperature;
    this->humidity = humidity;
    this->pressure = pressure;
    measurementsChanged();
}

float WeatherData::getTemperature() const {
    return temperature;
}

float WeatherData::getHumidity() const {
    return humidity;
}

float WeatherData::getPressure() const {
    return pressure;
}

// CurrentConditionsDisplay类实现
CurrentConditionsDisplay::CurrentConditionsDisplay(std::shared_ptr<Subject> weatherData)
    : weatherData(std::move(weatherData)), temperature(0.0), humidity(0.0) {
    // 构造函数中不自动注册，避免循环引用
}

void CurrentConditionsDisplay::update(float temperature, float humidity, float pressure) {
    this->temperature = temperature;
    this->humidity = humidity;
    display();
}

void CurrentConditionsDisplay::display() {
    std::cout << "当前条件：" << temperature << "°C，湿度 " << humidity << "%" << std::endl;
}

// StatisticsDisplay类实现
StatisticsDisplay::StatisticsDisplay(std::shared_ptr<Subject> weatherData)
    : weatherData(std::move(weatherData)), maxTemp(0.0), minTemp(100.0), tempSum(0.0), numReadings(0) {
    // 构造函数中不自动注册，避免循环引用
}

void StatisticsDisplay::update(float temperature, float humidity, float pressure) {
    tempSum += temperature;
    numReadings++;

    if (temperature > maxTemp) {
        maxTemp = temperature;
    }

    if (temperature < minTemp) {
        minTemp = temperature;
    }

    display();
}

void StatisticsDisplay::display() {
    std::cout << "温度统计：平均 " << tempSum / numReadings << "°C，最高 " << maxTemp << "°C，最低 " << minTemp << "°C" << std::endl;
}

// ForecastDisplay类实现
ForecastDisplay::ForecastDisplay(std::shared_ptr<Subject> weatherData)
    : weatherData(std::move(weatherData)), currentPressure(29.92f), lastPressure(0.0f) {
    // 构造函数中不自动注册，避免循环引用
}

void ForecastDisplay::update(float temperature, float humidity, float pressure) {
    lastPressure = currentPressure;
    currentPressure = pressure;
    display();
}

void ForecastDisplay::display() {
    std::cout << "天气预报：";
    if (currentPressure > lastPressure) {
        std::cout << "天气将好转！" << std::endl;
    } else if (currentPressure == lastPressure) {
        std::cout << "天气保持不变。" << std::endl;
    } else {
        std::cout << "天气将变差！" << std::endl;
    }
}

// 主函数示例
int main() {
    // 创建主题对象
    auto weatherData = std::make_shared<WeatherData>();

    // 创建观察者对象
    auto currentDisplay = std::make_shared<CurrentConditionsDisplay>(weatherData);
    auto statisticsDisplay = std::make_shared<StatisticsDisplay>(weatherData);
    auto forecastDisplay = std::make_shared<ForecastDisplay>(weatherData);

    // 手动注册观察者
    weatherData->registerObserver(currentDisplay);
    weatherData->registerObserver(statisticsDisplay);
    weatherData->registerObserver(forecastDisplay);

    // 设置天气数据
    std::cout << "=== 更新1：" << std::endl;
    weatherData->setMeasurements(25.5f, 65.0f, 1013.25f);

    std::cout << "\n=== 更新2：" << std::endl;
    weatherData->setMeasurements(26.7f, 70.0f, 1012.50f);

    std::cout << "\n=== 更新3：" << std::endl;
    weatherData->setMeasurements(24.3f, 60.0f, 1014.00f);

    // 测试移除观察者
    std::cout << "\n=== 移除统计显示器：" << std::endl;
    weatherData->removeObserver(statisticsDisplay);
    weatherData->setMeasurements(27.8f, 75.0f, 1011.75f);

    return 0;
}