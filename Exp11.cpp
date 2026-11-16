#include <iostream>
#include <iomanip>
using namespace std;

struct Meter      { static constexpr double factor = 1.0;     static constexpr const char* sym = "m";  };
struct Kilometer  { static constexpr double factor = 1000.0;  static constexpr const char* sym = "km"; };
struct Centimeter { static constexpr double factor = 0.01;    static constexpr const char* sym = "cm"; };
struct Millimeter { static constexpr double factor = 0.001;   static constexpr const char* sym = "mm"; };  // NEW
struct Mile       { static constexpr double factor = 1609.344; static constexpr const char* sym = "mi"; }; // NEW

template <typename Unit>
class Quantity
{
    double value;
public:
    constexpr Quantity(double v) : value(v) {}
    constexpr double getValue() const { return value; }

    // NEW: only quantities of the SAME unit can be added (type safety)
    constexpr Quantity operator+(const Quantity& other) const
    {
        return Quantity(value + other.value);
    }
};

template <typename ToUnit, typename FromUnit>
constexpr Quantity<ToUnit> convert(const Quantity<FromUnit>& q)
{
    double baseValue = q.getValue() * FromUnit::factor;
    return Quantity<ToUnit>(baseValue / ToUnit::factor);
}

template <typename U>
void show(const char* label, const Quantity<U>& q)
{
    cout << setprecision(10) << label << q.getValue() << " " << U::sym << endl;
}

int main()
{
    constexpr Quantity<Meter> distance(5000);
    constexpr auto km = convert<Kilometer>(distance);
    constexpr auto cm = convert<Centimeter>(distance);
    constexpr auto mm = convert<Millimeter>(distance);
    constexpr auto mi = convert<Mile>(distance);

    // Compile-time proof
    static_assert(km.getValue() == 5.0, "5000 m must be 5 km");

    constexpr Quantity<Meter> total = distance + Quantity<Meter>(250);

    show("Distance in Meters     : ", distance);
    show("Distance in Kilometers : ", km);
    show("Distance in Centimeters: ", cm);
    show("Distance in Millimeters: ", mm);
    show("Distance in Miles      : ", mi);
    show("Total after adding 250 : ", total);

    // Quantity<Meter> + Quantity<Kilometer> will NOT compile -> type safety
    return 0;
}
