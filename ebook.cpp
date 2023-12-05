#include <iostream>
#include <iomanip>
#include <vector>
#include <map>

class ReadingManager {
public:
    ReadingManager() : user_page_counts_(MAX_USER_COUNT_ + 1, 0), num_users_(0) {
        user_page_counts_.reserve(MAX_USER_COUNT_ + 1);
    }

    void Read(const int user_id, int page_count) {
        int prev_page_count = user_page_counts_[user_id];
        if (prev_page_count == 0) {
            ++num_users_;
        } else {
            std::map<int, int>::iterator it = page_to_num_users_.find(prev_page_count);
            if (it->second == 1) {
                page_to_num_users_.erase(it);
            } else {
                --it->second;
            }
        }
        user_page_counts_[user_id] = page_count;
        ++page_to_num_users_[page_count];
    }

    double Cheer(const int user_id) const {
        int page_count = user_page_counts_[user_id];
        if (page_count == 0) {
            return 0.0;
        }
        if (num_users_ == 1) {
            return 1.0;
        }
        int num_users_with_less_pages = 0;
        for (const auto& pair : page_to_num_users_) {
            if (pair.first < page_count) {
                num_users_with_less_pages += pair.second;
            } else if (pair.first == page_count) {
                break;
            }
        }
        return static_cast<double>(num_users_with_less_pages) / (num_users_ - 1);
    }

private:
    static const int MAX_USER_COUNT_ = 100'000;
    std::vector<int> user_page_counts_;
    std::map<int, int> page_to_num_users_;
    unsigned int num_users_;
};

int main() {
    ReadingManager manager;

    int query_count;
    std::cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        std::string query_type;
        std::cin >> query_type;
        int user_id;
        std::cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            std::cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            std::cout << std::setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}
