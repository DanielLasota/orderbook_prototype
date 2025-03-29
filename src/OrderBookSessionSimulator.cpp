#include "OrderbookSessionSimulator.h"
#include "CSVParser.h"
#include <chrono>
#include <iostream>

OrderbookSessionSimulator::OrderbookSessionSimulator()
    : orderbook() {}

void OrderbookSessionSimulator::processOrderbook(const std::string& csvPath) {
    try {
        std::vector<OrderBookEntry> entries = getOrderbookEntriesFromCSV(csvPath);
        std::vector<OrderBookEntry*> ptr_entries;

        ptr_entries.reserve(entries.size());
        for (auto &entry : entries) {
            ptr_entries.push_back(&entry);
        }

        OrderBookEntry** data = ptr_entries.data();
        size_t count = ptr_entries.size();

        auto start = std::chrono::steady_clock::now();

        // for (size_t i = 0; i < count; ++i) {
        //     OrderBookEntry* entry = data[i];

        // std::cout << entry->TimestampOfReceive << std::endl;
        // std::cout << "Timestamp: " << entry->TimestampOfReceive
        //           << ", Symbol: " << entry->Symbol
        //           << ", Price: " << entry->Price
        //           << ", Quantity: " << entry->Quantity << std::endl;
        //}

        for (auto &entry : entries) {
            orderbook.addOrder(entry);
            orderbook.printOrderBook();
        }

        auto finish = std::chrono::steady_clock::now();

        auto start_ms = std::chrono::duration_cast<std::chrono::milliseconds>(start.time_since_epoch()).count();
        auto finish_ms = std::chrono::duration_cast<std::chrono::milliseconds>(finish.time_since_epoch()).count();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();

        std::cout << "Start timestamp (ms): " << start_ms << std::endl;
        std::cout << "Finish timestamp (ms): " << finish_ms << std::endl;
        std::cout << "elapsed: " << elapsed_ms << " ms" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
