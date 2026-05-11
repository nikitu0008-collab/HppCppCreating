#include <string>
#include <cstdint>
class Create{
    public:
        Create() : answer_("unknown"), col_(0) {}
        ~Create()= default;
        auto Add()->void{}
    private:
        std::string answer_;
        uint16_t col_;
};
