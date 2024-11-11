#pragma once

#include <vector>
#include <optional>
#include <memory>
#include <algorithm>
#include <ranges>

template <typename T>
class ObjectPool
{
public:
    explicit ObjectPool(size_t initialSize = 100)
    {
        expand(initialSize);
    }

    template <typename... Args>
    std::shared_ptr<T> acquire(Args&&... args)
    {
        if (auto it = std::ranges::find_if(m_objects, [](const auto& obj) { return obj.use_count() == 1; });
            it != m_objects.end())
        {
            // Instead of modifying the existing object, create a new one
            *it = std::make_shared<T>(std::forward<Args>(args)...);
            return *it;
        }

        m_objects.push_back(std::make_shared<T>(std::forward<Args>(args)...));
        return m_objects.back();
    }

    void release(std::shared_ptr<T>& obj)
    {
        // The object will be automatically returned to the pool when its use_count reaches 1
        obj.reset();
    }

    [[nodiscard]] size_t size() const noexcept
    {
        return m_objects.size();
    }

    [[nodiscard]] size_t available() const noexcept
    {
        return std::ranges::count_if(m_objects, [](const auto& obj) { return obj.use_count() == 1; });
    }

private:
    std::vector<std::shared_ptr<T>> m_objects;

    void expand(size_t amount)
    {
        m_objects.reserve(m_objects.size() + amount);
        std::ranges::generate_n(std::back_inserter(m_objects), amount, [] { return std::make_shared<T>(); });
    }
};
