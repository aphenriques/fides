#include "DataView.hpp"

namespace fides {
    DataView::DataView(std::string_view string) : DataView(string.data(), string.size()) {}
    DataView::DataView(const std::string &string) : DataView(string.data(), string.size()) {}

    std::size_t DataView::getSize() const {
        return size_;
    }
}
