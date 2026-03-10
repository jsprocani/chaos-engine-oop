#ifndef ENGINE_RANDOM_HPP
#define ENGINE_RANDOM_HPP

#include <random>

namespace engine {
    class random {
    public:
        static void init() {
            get_engine().seed(std::random_device{}());
        }
        static int range(const int min, const int max) {
            std::uniform_int_distribution dist(min, max);
            return dist(get_engine());
        }
        static float range(const float min, const float max) {
            std::uniform_real_distribution dist(min, max);
            return dist(get_engine());
        }
        static color random_color() {
            return color(
                static_cast<uchar>(range(50, 255)),
                static_cast<uchar>(range(50, 255)),
                static_cast<uchar>(range(50, 255)),
                255
            );
        }
    private:
        static std::mt19937& get_engine() {
            static std::mt19937 engine;
            return engine;
        }
    };
}

#endif //ENGINE_RANDOM_HPP