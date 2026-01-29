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

void displayOrders(const std::map<unsigned int, std::deque<Order>> a, const std::map<unsigned int, std::deque<Order>, std::greater<>> b) {
    std::cout << "asks:" << '\n';
    for (const auto& [key, value] : a) {
	std::cout << key << " -> [";
	for(Order o : value)
	    std::cout << "Order " << o.id << " for " << o.quantity << ", ";
	std::cout << "]\n\n";
    }

    std::cout << "bids:" << '\n';
    for (const auto& [key, value] : b) {
	std::cout << key << " -> [";
	for(Order o : value)
	    std::cout << "Order " << o.id << " for " << o.quantity << ", ";
	std::cout << "]\n\n";
    }
}

int main() {
    std::map<unsigned int, std::deque<Order>> asks{};
    std::map<unsigned int, std::deque<Order>, std::greater<>> bids{};
    unsigned int ordersMade{0};

    while(true) {
	std::cout << "enter action (b: buy, s: sell, q: quit): ";
	
	char action{};
	std::cin >> action;

	unsigned int quantity{};
	unsigned int price{};

	switch(action) {
	    case 'b':
		std::cout << "how much would you like to buy? ";
		std::cin >> quantity;

		std::cout << "how much would you buy for? ";
		std::cin >> price;

		std::cout << "buying " << quantity << " shares at $" << price << "\n\n";
		bids[price].push_back({ordersMade, Side::BUY, price, quantity});
		ordersMade++;
		displayOrders(asks, bids);
		break;
	    case 's':
		std::cout << "how much would you like to sell? ";
		std::cin >> quantity;

		std::cout << "how much would you sell for? ";
		std::cin >> price;

		std::cout << "selling " << quantity << " shares at $" << price << "\n\n";
		asks[price].push_back({ordersMade, Side::BUY, price, quantity});
		ordersMade++;
		displayOrders(asks, bids);
		break;
	    case 'q':
		std::cout << "quitting" << '\n';
		return 0;
	    default:
		break;
	}
    }

    return 0;
}
