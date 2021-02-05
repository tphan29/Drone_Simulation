#include "order.h"  // NOLINT

namespace csci3081 {
    Order::Order(csci3081::Customer* customer, csci3081::Package* package,
        const picojson::object& details) :
    customer_(customer), package_(package), details_(details) {
    }
    csci3081::Package* Order::GetPackage() {
        return package_;
    }
    csci3081::Customer* Order::GetCustomer() {
        return customer_;
    }
    const picojson::object& Order::GetDetails() {
        return details_;
    }
}  // namespace csci3081
