#ifndef CPP_OBSERVER_H
#define CPP_OBSERVER_H

#include <vector>
#include <string>
#include <memory>
#include <algorithm>

// 前向声明
class Subject;

// 抽象观察者类
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(float temperature, float humidity, float pressure) = 0;
};

// 抽象主题类
class Subject {
public:
    virtual ~Subject() = default;
    virtual void registerObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void removeObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void notifyObservers() = 0;
};

// 抽象显示元素类
class DisplayElement {
public:
    virtual ~DisplayElement() = default;
    virtual void display() = 0;
};

// 具体主题类：天气数据
class WeatherData : public Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers;
    float temperature;
    float humidity;
    float pressure;

public:
    WeatherData();
    ~WeatherData() override = default;

    void registerObserver(std::shared_ptr<Observer> observer) override;
    void removeObserver(std::shared_ptr<Observer> observer) override;
    void notifyObservers() override;
    void measurementsChanged();
    void setMeasurements(float temperature, float humidity, float pressure);
    // 天气数据的getter方法
    float getTemperature() const;
    float getHumidity() const;
    float getPressure() const;
};

// 具体观察者类：当前条件显示器
class CurrentConditionsDisplay : public Observer, public DisplayElement {
private:
    std::shared_ptr<Subject> weatherData;
    float temperature;
    float humidity;

public:
    explicit CurrentConditionsDisplay(std::shared_ptr<Subject> weatherData);
    ~CurrentConditionsDisplay() override = default;

    void update(float temperature, float humidity, float pressure) override;
    void display() override;
};

// 具体观察者类：统计数据显示器
class StatisticsDisplay : public Observer, public DisplayElement {
private:
    std::shared_ptr<Subject> weatherData;
    float maxTemp;
    float minTemp;
    float tempSum;
    int numReadings;

public:
    explicit StatisticsDisplay(std::shared_ptr<Subject> weatherData);
    ~StatisticsDisplay() override = default;

    void update(float temperature, float humidity, float pressure) override;
    void display() override;
};

// 具体观察者类：预报显示器
class ForecastDisplay : public Observer, public DisplayElement {
private:
    std::shared_ptr<Subject> weatherData;
    float currentPressure;
    float lastPressure;

public:
    explicit ForecastDisplay(std::shared_ptr<Subject> weatherData);
    ~ForecastDisplay() override = default;

    void update(float temperature, float humidity, float pressure) override;
    void display() override;
};

#endif //CPP_OBSERVER_H