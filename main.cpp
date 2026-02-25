#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <map>

enum Side { BUY, SELL };

struct Order {
    int id;
    Side side;
    int price;
    int quantity;
};

void displayOrders(const std::map<int, std::deque<Order>>& asks,
                   const std::map<int, std::deque<Order>, std::greater<>>& bids) {
    std::cout << "Asks:\n";
    std::cout << std::string(50, '-') << '\n';
    for (const auto& [price, orders] : asks) {
        std::cout << '$' << price << " -> [";
        bool first = true;
        for (const Order& order : orders) {
            if (!first) std::cout << ", ";
            std::cout << "Order #" << order.id << " (" << order.quantity << ")";
            first = false;
        }
        std::cout << "]\n";
    }

    std::cout << '\n' << "Bids:\n";
    std::cout << std::string(50, '-') << '\n';
    for (const auto& [price, orders] : bids) {
        std::cout << '$' << price << " -> [";
        bool first = true;
        for (const Order& order : orders) {
            if (!first) std::cout << ", ";
            std::cout << "Order #" << order.id << " (" << order.quantity << ")";
            first = false;
        }
        std::cout << "]\n";
    }
}

void match(std::map<int, std::deque<Order>>& asks,
           std::map<int, std::deque<Order>, std::greater<>>& bids) {
    while (!asks.empty() && !bids.empty()) {
        auto asks_it = asks.begin();
        auto bids_it = bids.begin();

        // if highest buy price >= lowest sell price, initiate trade
        if (bids_it->first < asks_it->first) {
            break;
        }

        auto& asks_deque = asks_it->second;
        auto& bids_deque = bids_it->second;

        auto& ask = asks_deque.front();
        auto& bid = bids_deque.front();

        int sharesTraded = std::min(ask.quantity, bid.quantity);
        std::cout << "TRADE: bid #" << bid.id << " vs ask #" << ask.id << " qty=" << sharesTraded
                  << '\n';
        ask.quantity -= sharesTraded;
        bid.quantity -= sharesTraded;

        if (ask.quantity == 0) asks_deque.pop_front();
        if (bid.quantity == 0) bids_deque.pop_front();

        if (asks_deque.empty()) asks.erase(asks_it);
        if (bids_deque.empty()) bids.erase(bids_it);
    }
}

int main() {
    std::map<int, std::deque<Order>> asks{};
    std::map<int, std::deque<Order>, std::greater<>> bids{};
    int ordersMade{0};

    while (true) {
        std::cout << "enter action (b: buy, s: sell, q: quit): ";

        char action{};
        std::cin >> action;

        int quantity{};
        int price{};

        if (action == 'b') {
            std::cout << "how much would you like to buy? ";
            std::cin >> quantity;

            std::cout << "how much would you buy for? ";
            std::cin >> price;

            std::cout << "order " << ordersMade << ": buying " << quantity << " shares at $"
                      << price << "\n\n";
            bids[price].push_back({ordersMade, Side::BUY, price, quantity});
        } else if (action == 's') {
            std::cout << "how much would you like to sell? ";
            std::cin >> quantity;

            std::cout << "how much would you sell for? ";
            std::cin >> price;

            std::cout << "order " << ordersMade << ": selling " << quantity << " shares at $"
                      << price << "\n\n";
            asks[price].push_back({ordersMade, Side::SELL, price, quantity});
        } else if (action == 'q') {
            std::cout << "quitting" << '\n';
            return 0;
        }

        ordersMade++;
        match(asks, bids);
        displayOrders(asks, bids);
    }

    return 0;
}
