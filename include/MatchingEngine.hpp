#pragma once

#include "OrderBook.hpp"

#include <unordered_set>
#include <vector>

namespace hft {

class MatchingEngine {
public:
    explicit MatchingEngine(std::size_t pool_capacity = 4096);

    // Process a limit order. Any executable quantity is matched immediately;
    // residual quantity is added to the book.
    std::vector<Trade> submitLimitOrder(OrderId id,
                                        Side side,
                                        Price price,
                                        Quantity quantity);

    bool cancel(OrderId id);

    const OrderBook& book() const noexcept { return book_; }

private:
    OrderBook book_;
    // An accepted order ID is never reusable, even after the order is fully filled.
    std::unordered_set<OrderId> seen_order_ids_;
};

} // namespace hft
