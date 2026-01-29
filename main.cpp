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

int main() {
    std::map<unsigned int, std::deque<Order>> asks{};
    std::map<unsigned int, std::deque<Order>, std::greater<>> bids{};

    while(true) {
	std::cout << "enter action (b: buy, s: sell, q: quit): ";
	
	char action{};
	std::cin >> action;

	unsigned int quantity{};
	unsigned int price{};
	unsigned int ordersMade{0};

	switch(action) {
	    case 'b':
		std::cout << "how much would you like to buy? ";
		std::cin >> quantity;

		std::cout << "how much would you buy for? ";
		std::cin >> price;

		std::cout << "buying " << quantity << " shares at $" << price << "\n\n";
		bids[price].push_back({ordersMade, Side::BUY, price, quantity});
		ordersMade++;

		break;
	    case 's':
		std::cout << "how much would you like to sell? ";
		std::cin >> quantity;

		std::cout << "how much would you sell for? ";
		std::cin >> price;

		std::cout << "selling " << quantity << " shares at $" << price << "\n\n";
		asks[price].push_back({ordersMade, Side::BUY, price, quantity});
		ordersMade++;

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
