#ifndef TASK_HPP_
#define TASK_HPP_

#include <unordered_map>
#include <iostream>
#include <string>
#include <array>

#include "lexer.hpp"

namespace task {
    // перенести это все в заголовный файл

    enum class eCode : int {
        EMPTY, NOT_FOUND, NOT_VALID, STOP,
        UNRECOGNIZED_STRING, SUCCES
    };

    enum eDataType : int {
        DESC, DATE, CATEGORY, ALL
    };

    // Struct of task
    struct block_of_task {
    public:
        friend bool operator<(const block_of_task&, const std::string&) noexcept;

        friend bool operator>(const block_of_task&, const std::string&) noexcept;

        friend bool operator<=(const std::string&, const std::string&) noexcept;

        // friend bool operator>=(const std::string&, const std::string&) noexcept;

        // friend bool operator==(const std::string&, const std::string&) noexcept;
    public:
        std::array<std::string, eDataType::ALL> m_data;
        std::array<bool, eDataType::ALL> m_criteria = { 0 };
        bool m_is_done = 0;
    };

    // Class for handler all tasks
    class TaskHandler {  
        using storage = std::unordered_map<std::string, block_of_task>;
    public:
        TaskHandler() = default;

        TaskHandler(TaskHandler&&) = default;

        TaskHandler(const TaskHandler&) = default;

        virtual ~TaskHandler() = default;
    protected:
        virtual auto addTask(const std::string& t_data) -> void;

        virtual auto doneTask(const std::string& t_data) noexcept -> void;

        virtual auto updateTask(const std::string& t_data) noexcept -> void;

        virtual auto deleteTask(const std::string& t_data) noexcept -> void;
        
        virtual auto selectTask(const std::string& t_data) -> void;
        
        virtual auto handleTokens(block_of_task& t_task, const eToken t_tok) noexcept -> bool;

        virtual auto handleDate(block_of_task& t_task) noexcept -> void;

        virtual auto handleParam(block_of_task& t_task, const eToken t_tok) noexcept -> void;

        virtual auto handleSubStr(block_of_task& t_task, const eToken t_tok) noexcept -> bool;
    public:
        auto printTasks() const noexcept -> void;

        auto parseCommand(const std::string& t_expr) -> const eCode;
        // Потом поменять на const!
        auto getStorage() noexcept -> storage&;
    public:
        TaskHandler& operator=(const TaskHandler&) = default;

        TaskHandler& operator=(TaskHandler&&) = default;
    private:
        std::string m_str_format;
        storage m_tasks;
        Lexer m_lex;
    };
}

#endif // TASK_HPP_