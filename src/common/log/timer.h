//// @date 2024-08-21
/// @file timer.h
/// @author Peng Yubin, modified by Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief
///
///
/// TODO: use Singleton.h for concise.

#pragma once
#include <MnBase/Singleton.h>
#include <chrono>
#include <common/log.h>
#include <map>
#include <vector>
#include <set>


struct TimeLogger : mn::Singleton<TimeLogger> {

    void register_timing(const std::string& task, size_t duration) {
        Record record{task, duration};
        records.push_back(record);
    }

    void print_timing() {
        spdlog::info("共有 {} 条计时记录.", records.size());
        for (const auto& record : records) {
            spdlog::info("任务: {}, 耗时: {} 微秒.", record.tag.c_str(), record.us);
        }
    }

    void print_statistics() {
        std::map<std::string_view, Statistic> stats;
        for (auto const& [tag, us] : records) {
            auto& stat = stats[tag];
            stat.total_us += us;
            stat.max_us = std::max(stat.max_us, us);
            stat.min_us = !stat.count_rec ? us : std::min(stat.min_us, us);
            stat.count_rec++;
            stat.tag = tag;
        }
        struct StatisticCompare {
            using value_type = std::pair<std::string_view, Statistic>;
            bool operator()(const value_type& lhs, const value_type& rhs) const {
                return lhs.second.total_us > rhs.second.total_us;
            }
        };

        auto dump = [](size_t val, size_t w) {
            size_t tpwv = 1;
            for (size_t i = 0; i < w - 1; i++)
                tpwv *= 10;
            std::string result = "";
            // val = val/1000000;
            if (val > tpwv) {
                if (val / 1000000000 > tpwv / 10) {
                    result = std::to_string(val / 1000000000000) + "T";
                } else if (val / 1000000 > tpwv / 10) {
                    result = std::to_string(val / 1000000000) + "G";
                } else if (val / 1000 > tpwv / 10) {
                    result = std::to_string(val / 1000000) + "M";
                } else {
                    result = std::to_string(val / 1000) + "K";
                }
            } else {
                result = std::to_string(val);
            }
            return result;
        };

        std::multiset<std::pair<std::string_view, Statistic>, StatisticCompare> sortstats(stats.begin(), stats.end());
        
        spdlog::info("运行时间统计(微秒):");
        spdlog::info("   avg   |   min   |   max   |  total  | cnt | tag");
        for (const auto& stat : sortstats) {
            spdlog::info("{:>8} | {:>7} | {:>7} | {:>7} | {:>3} | {}", 
                         dump(stat.second.max_us/stat.second.count_rec, 6),
                         dump(stat.second.max_us, 6), 
                         dump(stat.second.min_us, 6), 
                         dump(stat.second.total_us, 6),
                         stat.second.count_rec, 
                         stat.second.tag);
        }
    }

    struct Record {
        const std::string tag;
        size_t            us;
    };

    struct Statistic {
        size_t      max_us    = 0;
        size_t      min_us    = 0;
        size_t      total_us  = 0;
        size_t      count_rec = 0;
        std::string tag       = "";
    };

  private:
    inline thread_local static std::vector<Record> records;
};

class Timer {
  public:
    Timer(const std::string& task) : beg(ClockType::now()), _task(task) {}

    ~Timer() {
        end         = ClockType::now();
        auto   diff = end - beg;
        size_t us   = std::chrono::duration_cast<std::chrono::microseconds>(diff).count();
        TimeLogger::instance().register_timing(_task, us);
    }

    using ClockType = std::chrono::high_resolution_clock;
    using Record    = TimeLogger::Record;

  private:
    const std::string     _task;
    ClockType::time_point beg;
    ClockType::time_point end;
};

#define FUNCTION_TIMER Timer timer(__PRETTY_FUNCTION__)
