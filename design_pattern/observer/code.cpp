#include <iostream>
#include <vector>
#include <algorithm>

// observer interface
class Observer {
public:
    virtual void onEvent(const std::string& event) = 0;
    virtual ~Observer() = default;
};

// subject — the thing being observed
class Button {
    std::vector<Observer*> listeners;

public:
    void subscribe(Observer* o) {
        listeners.push_back(o);
    }

    void unsubscribe(Observer* o) {
        listeners.erase(std::remove(listeners.begin(), listeners.end(), o), listeners.end());
    }

    void press() {
        std::cout << "button pressed\n";
        notify("PRESS");
    }

private:
    void notify(const std::string& event) {
        for (auto* o : listeners)
            o->onEvent(event);   // tell everyone
    }
};

// concrete observers
class LEDHandler : public Observer {
public:
    void onEvent(const std::string& event) override {
        if (event == "PRESS") std::cout << "LED toggled\n";
    }
};

class BuzzerHandler : public Observer {
public:
    void onEvent(const std::string& event) override {
        if (event == "PRESS") std::cout << "buzzer beeped\n";
    }
};

int main() {
    Button btn;
    LEDHandler led;
    BuzzerHandler buzzer;

    btn.subscribe(&led);
    btn.subscribe(&buzzer);

    btn.press();

    btn.unsubscribe(&buzzer);
    btn.press();  // only LED responds now
}
