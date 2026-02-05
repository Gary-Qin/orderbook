#include <deque>
#include <functional>
#include <iostream>
#include <map>

enum Side { BUY, SELL };

struct Order {
    unsigned int id;
    Side side;
    unsigned int price;
    unsigned int quantity;
};

void displayOrders(const std::map<unsigned int, std::deque<Order>>& asks,
                   const std::map<unsigned int, std::deque<Order>, std::greater<>>& bids) {
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

void match(std::map<unsigned int, std::deque<Order>>& asks,
           std::map<unsigned int, std::deque<Order>, std::greater<>>& bids) {}

int main() {
    std::map<unsigned int, std::deque<Order>> asks{};
    std::map<unsigned int, std::deque<Order>, std::greater<>> bids{};
    unsigned int ordersMade{0};

    while (true) {
        std::cout << "enter action (b: buy, s: sell, q: quit): ";

        char action{};
        std::cin >> action;

        unsigned int quantity{};
        unsigned int price{};

        if (action == 'b') {
            std::cout << "how much would you like to buy? ";
            std::cin >> quantity;

            std::cout << "how much would you buy for? ";
            std::cin >> price;

            std::cout << "buying " << quantity << " shares at $" << price << "\n\n";
            bids[price].push_back({ordersMade, Side::BUY, price, quantity});
        } else if (action == 's') {
            std::cout << "how much would you like to sell? ";
            std::cin >> quantity;

            std::cout << "how much would you sell for? ";
            std::cin >> price;

            std::cout << "selling " << quantity << " shares at $" << price << "\n\n";
            asks[price].push_back({ordersMade, Side::BUY, price, quantity});
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
