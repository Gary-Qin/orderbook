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
    auto asks_it = asks.begin();
    auto bids_it = bids.begin();

    // if highest buy price >= lowest sell price, initiate trade
    while (bids_it->first >= asks_it->first &&
           !(asks.begin() == asks.end() || bids.begin() == bids.end())) {
        std::deque<Order>& asks_deque = asks_it->second;
        std::deque<Order>& bids_deque = bids_it->second;
        auto asks_deque_it = asks_deque.begin();
        auto bids_deque_it = bids_deque.begin();

        if (asks_deque_it->quantity > bids_deque_it->quantity) {
            std::cout << "ORDER: full fill of bid #" << bids_deque_it->id
                      << ", partial fill of ask #" << asks_deque_it->id << '\n';
            asks_deque_it->quantity -= bids_deque_it->quantity;
            bids_deque.pop_front();
        } else if (bids_deque_it->quantity > asks_deque_it->quantity) {
            std::cout << "ORDER: partial fill of bid #" << bids_deque_it->id
                      << ", full fill of ask #" << asks_deque_it->id << '\n';
            bids_deque_it->quantity -= asks_deque_it->quantity;
            asks_deque.pop_front();
        } else {
            std::cout << "ORDER: full fill of bid #" << bids_deque_it->id << ", full fill of ask #"
                      << asks_deque_it->id << '\n';
            asks_deque.pop_front();
            bids_deque.pop_front();
        }

        if (asks_it->second.empty()) {
            asks_it = asks.erase(asks_it);
        }

        if (bids_it->second.empty()) {
            bids_it = bids.erase(bids_it);
        }
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
