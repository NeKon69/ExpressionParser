#include <iostream>
#include <string>
#include "exprtk.hpp" // Включаем заголовочный файл exprtk

typedef double real_t;
real_t parse(const std::string& expression_string) {
    exprtk::symbol_table<real_t> symbol_table;
    exprtk::expression<real_t> expression;
    exprtk::parser<real_t> parser;

    real_t x;
    real_t y;
    symbol_table.add_variable("x", x);
    symbol_table.add_variable("y", y);
    symbol_table.add_function("sin", std::sin);
    symbol_table.add_function("cos", std::cos);
    symbol_table.add_function("tan", std::tan);
    symbol_table.add_function("exp", std::exp);
    symbol_table.add_function("log", std::log);
    symbol_table.add_function("log2", std::log2);
    symbol_table.add_function("log10", std::log10);
    symbol_table.add_function("abs", std::abs);
    symbol_table.add_function("sqrt", std::sqrt);
    symbol_table.add_constant("pi", 3.14159265358979323846);
    symbol_table.add_constant("e", 2.71828182845904523536);
    symbol_table.add_constant("inf", std::numeric_limits<real_t>::infinity());
    symbol_table.add_constant("nan", std::numeric_limits<real_t>::quiet_NaN());

    expression.register_symbol_table(symbol_table);

    if (!parser.compile(expression_string, expression)) {
        std::cerr << "Error: " << parser.error() << std::endl;
        return 0.0;
    }

    for (int i = 0; i < 10; ++i) {
        x = i;
        y = std::sin(i);
        std::cout << "x: " << x << ", y: " << y << ", result: " << expression.value() << std::endl;
    }
    return expression.value();
}




int main() {
    // 1. Определяем тип данных для вычислений


    // 2. Создаем объекты для парсинга и вычисления
    exprtk::symbol_table<real_t> symbol_table; // Таблица символов (переменные, константы, функции)
    exprtk::expression<real_t> expression;    // Выражение
    exprtk::parser<real_t> parser;              // Парсер

    // 3. Определяем переменные и связываем их с таблицей символов
    real_t x = 1.0; // Значение переменной x
    real_t y = 2.0; // Значение переменной y
    symbol_table.add_variable("x", x); // Добавляем переменную x в таблицу символов
    symbol_table.add_variable("y", y); // Добавляем переменную y в таблицу символов

    expression.register_symbol_table(symbol_table);

    std::string expression_string;
    std::getline(std::cin, expression_string);
    auto num = parse(expression_string);

    bool success = parser.compile(expression_string, expression);

    if (!success) {
        std::cout << "Error: " << parser.error() << std::endl;
        return 1;
    }

    real_t result = expression.value();


    std::cout << "Result: " << result << std::endl;

    return 0;
}