#ifndef fides_DataView_hpp
#define fides_DataView_hpp

#include <concepts>
#include <string>
#include <string_view>
#include <type_traits>

namespace fides {
    template<typename T>
    concept Byte = (sizeof(T) == sizeof(char));

    class DataView {
    public:
        template<Byte T>
        DataView(const T *data, std::size_t size);

        template<Byte T>
        DataView(const std::vector<T> &vector);

        DataView(std::string_view string);
        DataView(const std::string &string);

        template<typename T = void>
            requires Byte<T> || std::same_as<T, void>
        const T * getData() const;

        std::size_t getSize() const;

    private:
        const void * const data_;
        const std::size_t size_;
    };

    //--

    template<Byte T>
    DataView::DataView(const T *data, std::size_t size) : data_(data), size_(size) {}

    template<Byte T>
    DataView::DataView(const std::vector<T> &vector) : DataView(vector.data(), vector.size()) {}

    template<typename T>
        requires Byte<T> || std::same_as<T, void>
    const T * DataView::getData() const {
        if constexpr (std::is_same_v<T, void> == true) {
            return data_;
        } else {
            return static_cast<const T *>(data_);
        }
    }
}

#endif
