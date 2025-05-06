#ifndef _EVENTBUS_H
#define _EVENTBUS_H

#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <any>
#include <atomic>
#include <memory>
#include <type_traits>
#include <thread>

#include "ThreadPool.hpp"

// function_traits 定义
template<typename T>
struct function_traits;

// 普通函数
template<typename Ret, typename... Args>
struct function_traits<Ret(Args...)> {
    using signature = Ret(Args...);
};

// 函数指针
template<typename Ret, typename... Args>
struct function_traits<Ret(*)(Args...)> : function_traits<Ret(Args...)> {};

// std::function
template<typename Ret, typename... Args>
struct function_traits<std::function<Ret(Args...)>> : function_traits<Ret(Args...)> {};

// 成员函数指针
template<typename ClassType, typename Ret, typename... Args>
struct function_traits<Ret(ClassType::*)(Args...)> : function_traits<Ret(Args...)> {};

// const 成员函数指针
template<typename ClassType, typename Ret, typename... Args>
struct function_traits<Ret(ClassType::*)(Args...) const> : function_traits<Ret(Args...)> {};

// 函数对象（包括lambda）
template<typename Callable>
struct function_traits : function_traits<decltype(&Callable::operator())> {};

// 特化处理 std::bind
template<typename Callable, typename... Args>
struct function_traits<std::_Bind<Callable(Args...)>> 
    : function_traits<Callable> {};

using callback_id = size_t;

class NetworkController;
class WebrtcController;
class ConfigController;
class EventBus {
public:
    EventBus(const EventBus&) = delete;
    EventBus(EventBus&&) = delete;
    EventBus& operator=(const EventBus&) = delete;
    EventBus& operator=(EventBus&&) = delete;

    static EventBus& getInstance() {
        static EventBus instance;
        return instance;
    }

    void registerEvent(std::string eventName) {
        auto [it, inserted] = registered_events.emplace(std::move(eventName));
        if (inserted) {
            callbacks_map.try_emplace(*it).first->second.reserve(3);
            std::cout << "register " << *it << std::endl;
        }
    }

    // 显式模板参数的 subscribe
    template<typename... Args>
    callback_id subscribe(const std::string& eventName, std::function<void(Args...)> callback) {
        if (!isEventRegistered(eventName)) {
            throw std::runtime_error("Event not registered: " + eventName);
        }
        callback_id id = ++next_id;
        callbacks_map[eventName].emplace_back(CallbackWrapper{id, callback});
        return id;
    }

    // 自动推导 Callback 类型的 subscribe
    template<typename Callback>
    callback_id subscribe(std::string eventName, Callback&& callback) {
        using signature = typename function_traits<std::decay_t<Callback>>::signature;
        return subscribe(eventName, std::function<signature>(std::forward<Callback>(callback)));
    }

    // 安全订阅版本（自动注册事件）
    template<typename... Args>
    callback_id subscribeSafe(const std::string& eventName, std::function<void(Args...)> callback) {
        if (!isEventRegistered(eventName)) {
            registerEvent(eventName);
        }
        return subscribe(eventName, callback);
    }
    
    // 自动推导的安全订阅版本
    template<typename Callback>
    callback_id subscribeSafe(std::string eventName, Callback&& callback) {
        using signature = typename function_traits<std::decay_t<Callback>>::signature;
        return subscribeSafe(eventName, std::function<signature>(std::forward<Callback>(callback)));
    }

    template<typename... Args>
    void publish(std::string eventName, Args... args) {
        if (!isEventRegistered(eventName)) {
            throw std::runtime_error("Event not registered: " + eventName);
        }
        // for (auto& wrapper : callbacks_map[eventName]) {
        //     try {
        //         auto callback = std::any_cast<std::function<void(Args...)>>(wrapper.callback);
        //         thread_pool->addTask([callback, args_tuple = std::make_tuple(std::forward<Args>(args)...)]() mutable {
        //             std::apply(callback, std::move(args_tuple));
        //         });
        //     } catch (const std::bad_any_cast&) {
        //         throw std::runtime_error("Callback type mismatch for event: " + eventName);
        //     }
        // }
        auto args_tuple = std::make_shared<std::tuple<std::decay_t<Args>...>>(std::forward<Args>(args)...);

        for (auto& wrapper : callbacks_map[eventName]) {
            try {
                auto callback = std::any_cast<std::function<void(Args...)>>(wrapper.callback);
                thread_pool->addTask([callback, args_tuple]() {
                    std::apply(callback, *args_tuple);
                });
            } catch (const std::bad_any_cast&) {
                throw std::runtime_error("Callback type mismatch for event: " + eventName);
            }
        }
    }

    bool isEventRegistered(const std::string& eventName) const {
        return registered_events.find(eventName) != registered_events.end();
    }

    bool unsubscribe(const std::string& eventName, callback_id id) {
        if (!isEventRegistered(eventName)) return false;
        auto& callbacks = callbacks_map[eventName];
        for (auto it = callbacks.begin(); it != callbacks.end(); ) {
            if (it->id == id) {
                it = callbacks.erase(it);
                return true;
            } else {
                ++it;
            }
        }
        return false;
    }
    void initModuleSubscribe();
private:
    EventBus();
    ~EventBus();
    struct CallbackWrapper {
        callback_id id;
        std::any callback;
    };
    std::unordered_map<std::string, std::vector<CallbackWrapper>> callbacks_map;
    std::unordered_set<std::string> registered_events;
    std::atomic<callback_id> next_id{0};
    std::unique_ptr<ThreadPool<>> thread_pool;

    std::unique_ptr<NetworkController> network_controller;
    std::unique_ptr<WebrtcController> webrtc_controller;
    std::unique_ptr<ConfigController> config_controller;
};

#endif