#include "defines.hpp"

namespace def {

std::ostream& operator<<(std::ostream& t_stream, const date& t_date) {
    t_stream << t_date.m_year << '-' << t_date.m_month << '-' << t_date.m_day << ' '
             << t_date.m_hour << ':' << t_date.m_minute;
    return t_stream;
}

// Function for give ints from string
auto date::getDateFromStr(const std::string& t_data) -> date {
    std::istringstream input(t_data);
    std::string str_line;
    date d;

    char c = 0;
    while (std::getline(input, str_line)) {
        std::istringstream is(str_line);
        is >> d.m_year >> c >> d.m_month >> c >> d.m_day >> c >> d.m_hour >> c >> d.m_minute;
    }

    return d;
}

// Overload operators
bool operator<(const block_of_task& t_task, const std::string& t_data) noexcept {
    auto date_task = date::getDateFromStr(t_task.m_data[DATE]);
    auto date_str = date::getDateFromStr(t_data);

    return std::tie(date_task.m_year, date_task.m_month, date_task.m_day, date_task.m_hour,
                    date_task.m_minute) < std::tie(date_str.m_year, date_str.m_month,
                                                   date_str.m_day, date_str.m_hour,
                                                   date_str.m_minute);
}

bool operator>(const block_of_task& t_task, const std::string& t_data) noexcept {
    auto date_task = date::getDateFromStr(t_task.m_data[DATE]);
    auto date_str = date::getDateFromStr(t_data);

    return std::tie(date_task.m_year, date_task.m_month, date_task.m_day, date_task.m_hour,
                    date_task.m_minute) > std::tie(date_str.m_year, date_str.m_month,
                                                   date_str.m_day, date_str.m_hour,
                                                   date_str.m_minute);
}

bool operator<=(const block_of_task& t_task, const std::string& t_data) noexcept {
    auto date_task = date::getDateFromStr(t_task.m_data[DATE]);
    auto date_str = date::getDateFromStr(t_data);

    return std::tie(date_task.m_year, date_task.m_month, date_task.m_day, date_task.m_hour,
                    date_task.m_minute) <= std::tie(date_str.m_year, date_str.m_month,
                                                    date_str.m_day, date_str.m_hour,
                                                    date_str.m_minute);
}

bool operator>=(const block_of_task& t_task, const std::string& t_data) noexcept {
    auto date_task = date::getDateFromStr(t_task.m_data[DATE]);
    auto date_str = date::getDateFromStr(t_data);

    return std::tie(date_task.m_year, date_task.m_month, date_task.m_day, date_task.m_hour,
                    date_task.m_minute) >= std::tie(date_str.m_year, date_str.m_month,
                                                    date_str.m_day, date_str.m_hour,
                                                    date_str.m_minute);
}

bool operator==(const block_of_task& t_task, const std::string& t_data) noexcept {
    auto date_task = date::getDateFromStr(t_task.m_data[DATE]);
    auto date_str = date::getDateFromStr(t_data);

    return std::tie(date_task.m_year, date_task.m_month, date_task.m_day, date_task.m_hour,
                    date_task.m_minute) == std::tie(date_str.m_year, date_str.m_month,
                                                    date_str.m_day, date_str.m_hour,
                                                    date_str.m_minute);
}

} // namespace def
