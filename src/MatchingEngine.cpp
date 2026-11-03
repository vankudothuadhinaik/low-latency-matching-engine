#include "MatchingEngine.hpp"

namespace hft {

MatchingEngine::MatchingEngine(std::size_t pool_capacity)
    : book_(pool_capacity) {}

std::vector<Trade> MatchingEngine::submitLimitOrder(OrderId id,
                                                   Side side,
                                                   Price price,
                                                   Quantity quantity) {
    if (price <= 0 || quantity == 0 || book_.find(id) != nullptr) {
        return {};
    }

    // Order IDs are idempotency keys for the lifetime of this engine. Keep the
    // accepted ID after a full fill so replaying a completed order cannot trade
    // again merely because it is no longer present in the resting book.
    if (!seen_order_ids_.insert(id).second) {
        return {};
    }

    // Match first. If the order has residual quantity, add the remainder
    // as a resting order while preserving a single sequence number.
    auto trades = book_.match(id, side, price, quantity);

    Quantity executed = 0;
    for (const auto& trade : trades) {
        executed += trade.quantity;
    }

    const Quantity remaining = quantity - executed;
    if (remaining > 0) {
        book_.addOrder(id, side, price, remaining);
    }

    return trades;
}

bool MatchingEngine::cancel(OrderId id) {
    return book_.cancelOrder(id);
}

} // namespace hft
