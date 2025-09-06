#include <iostream>
#include <memory>
using namespace std;

namespace helper
{
    template <typename T>
    constexpr typename std::enable_if<!std::is_convertible<T, std::string>::value, std::string>::type
    to_string(const T &val)
    {
        return std::to_string(val);
    };

    template <typename T>
    constexpr typename std::enable_if<std::is_convertible<T, std::string>::value, std::string>::type
    to_string(const T &val)
    {
        return val;
    };
}

template <typename Data>
class String_list
{
    struct Node
    {
        using node_ptr = std::unique_ptr<Node>;
        Data data{};
        node_ptr next = nullptr;

        operator std::string() const
        {
            return helper::to_string(this->data);
        }
    };
    using node_ptr = std::unique_ptr<Node>;
    node_ptr head = nullptr;
    std::size_t size = 0;

public:
    struct Iterator
    {
        friend class String_list;
        Iterator() noexcept : current_node(nullptr) {};
        Iterator(const node_ptr &node) noexcept : current_node(node.get()) {};

        Iterator &operator++() noexcept
        {
            if (current_node != nullptr)
            {
                previous_node = current_node;
                current_node = current_node->next.get();
            }
            return *this;
        };
        Iterator operator++(int) noexcept
        {
            Iterator tempIter = *this;
            ++*this;
            return tempIter;
        };
        bool operator!=(const Iterator &other) const noexcept
        {
            return this->current_node != other.current_node;
        };
        Data operator*() const noexcept
        {
            return this->current_node->data;
        };

    private:
        Node *previous_node = nullptr;
        Node *current_node = nullptr;
    };
    Iterator begin() const noexcept
    {
        return Iterator(this->head);
    };
    Iterator end() const noexcept
    {
        return Iterator();
    };
    Iterator insert(const Iterator &pos, const Data &value)
    {
        if (pos.current_node != nullptr)
        {
            // node_ptr newNode = std::make_unique<Node>(value);
            node_ptr newNode = std::make_unique<Node>();
            newNode->data = value;

            // newNode->next = std::move(pos.current_node->next);

            if (pos.previous_node == nullptr)
            {
                newNode->next = std::move(head);

                head = std::move(newNode);
                size++;
                return Iterator(head);
            }
            else
            {
                newNode->next = std::move(pos.previous_node->next);

                pos.previous_node->next = std::move(newNode);
                size++;
                return Iterator(pos.previous_node->next);
            }
        }
        return pos;
    };

    String_list() = default;
    String_list(std::initializer_list<Data> listOfItems) noexcept
    {
        if (listOfItems.size() != 0)
        {
            auto it = listOfItems.begin();

            // head = std::make_unique<Node>(*it);
            head = std::make_unique<Node>();
            head->data = *it;

            size++;
            Node *current = head.get();
            ++it;
            for (; it != listOfItems.end(); ++it)
            {
                // current->next = std::make_unique<Node>(*it);
                current->next = std::make_unique<Node>();
                current->next->data = *it;

                current = current->next.get();
                size++;
            }
        }
    };

    String_list(const String_list &other) noexcept
    {
        std::cout << "*** Copy constructor ***" << '\n';
        if (other.head == nullptr)
            return;

        head = std::make_unique<Node>(other.head->data);
        Node *current = head.get();
        size = 1;

        Node *otherCurrent = other.head->next.get();
        while (otherCurrent != nullptr)
        {
            current->next = std::make_unique<Node>(otherCurrent->data);
            otherCurrent = otherCurrent->next.get();
            current = current->next.get();
            size++;
        }
    }
    String_list &operator=(const String_list &other) noexcept
    {
        std::cout << "*** Copy assignment operator ***" << '\n';
        String_list tempList(other);
        head.swap(tempList.head);
        std::swap(size, tempList.size);
        return *this;
    }
    String_list(String_list &&other) noexcept
    {
        std::cout << "*** Move constructor ***" << '\n';
        head.swap(other.head);
        size = other.size;

        other.head = nullptr;
        other.size = 0;
    }
    String_list &operator=(String_list &&other) noexcept
    {
        std::cout << "*** Move assignment operator ***" << '\n';
        this->clear();

        head.swap(other.head);
        size = other.size;

        other.head = nullptr;
        other.size = 0;

        return *this;
    }
    ~String_list() noexcept {};

    std::size_t l_size() const noexcept { return size; };
    bool isEmpty() const { return l_size() == 0; };

    void push_front(const Data &data)
    {
        if (isEmpty())
        {
            head = std::make_unique<Node>(data, nullptr);
        }
        else
        {
            node_ptr newNode = std::make_unique<Node>(data, nullptr);
            newNode->next = std::move(head);
            head = std::move(newNode);
        }
        size++;
    };
    void push_back(const Data &data) noexcept
    {
        if (isEmpty())
        {
            head = std::make_unique<Node>(data, nullptr);
        }
        else
        {
            Node *current = head.get();
            while (current->next != nullptr)
            {
                current = current->next.get();
            }
            current->next = std::make_unique<Node>(data, nullptr);
        }
        size++;
    }
    void clear() noexcept
    {
        if (!isEmpty())
        {
            Node *current = head.get();
            while (current != nullptr)
            {
                Node *temp = current;
                temp = nullptr;
                current = current->next.get();
            }
            head = nullptr;
            size = 0;
        }
    }
    void reverse() noexcept
    {
        node_ptr current;
        current = std::move(head);
        node_ptr next = nullptr;
        node_ptr temp = nullptr;

        while (current != nullptr)
        {
            next = std::move(current->next);
            current->next = std::move(temp);
            temp = std::move(current);
            current = std::move(next);
        }
        head = std::move(temp);
    }

    void printList() const
    {
        if (isEmpty())
        {
            std::cout << "Empty list" << '\n';
        }
        else
        {
            Node *current = head.get();
            while (current != nullptr)
            {
                std::cout << std::string(*current) << '\n';
                current = current->next.get();
            }
        }
    }
};

int main()
{
    // String_list<std::string> myFirstList = {"one", "two", "three"};
    // myFirstList.printList();

    // String_list<unsigned long long> longList = {12, 3123, 4324532, 4324231313, 54654645};
    // for (const auto &item : longList)
    // {
    //     std::cout << item << '\n';
    // }
    // auto iterator = longList.begin();
    // std::cout << "This is the second element: " << *(++iterator) << '\n';

    String_list<unsigned long long> ulist = {12, 3123, 4324532, 4324231313, 54654645};
    auto itr = ulist.begin();
    for (; itr != ulist.end(); ++itr)
    {
        // if (*itr == 4324532ull)
        if (*itr == 12ull)
        {
            itr = ulist.insert(itr, 11111);
            ++itr;
        }
    }
    for (const auto &item : ulist)
    {
        std::cout << item << '\n';
    }

    return 0;
}