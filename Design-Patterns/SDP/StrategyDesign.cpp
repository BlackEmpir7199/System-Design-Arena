#include <iostream>
#include <string>

// Step 1: Strategy Interface (Abstract Base Class)
class RouteStrategy
{
public:
    virtual ~RouteStrategy() = default;
    virtual std::string buildRoute(const std::string &start, const std::string &end) = 0;
};

// Step 2: Concrete Strategies - Actual Implementations
class BikeRouteStrategy : public RouteStrategy
{
public:
    std::string buildRoute(const std::string &start, const std::string &end)
    {
        return "Bike route from " + start + " to " + end + ": Use bike lanes, scenic paths (30 mins)";
    }
};

class CarRouteStrategy : public RouteStrategy
{
public:
    std::string buildRoute(const std::string &start, const std::string &end) override
    {
        return "Car route from " + start + " to " + end + ": Take highways, avoid traffic (20 mins)";
    }
};

class WalkRouteStrategy : public RouteStrategy
{
public:
    std::string buildRoute(const std::string &start, const std::string &end) override
    {
        return "Walk route from " + start + " to " + end + ": Shortcuts through parks (45 mins)";
    }
};

// step 3:

class Navigator
{
private:
    RouteStrategy *strategy;

public:
    Navigator(RouteStrategy *intitalStrategy)
    {
        strategy = intitalStrategy;
    }

    void setStrategy(RouteStrategy *newStrategy)
    {
        strategy = newStrategy;
    }

    std::string startNavigation(const std::string &start, const std::string &end)
    {
        return strategy->buildRoute(start, end);
    }
};

int main()
{
    // Create context with initial strategy (e.g., car)
    CarRouteStrategy carStrategy;
    BikeRouteStrategy bikeStrategy;
    WalkRouteStrategy walkStrategy;

    // Create context with initial strategy (e.g., car)
    Navigator navigator(&carStrategy);
    std::cout << navigator.startNavigation("Home", "Office") << std::endl;

    // switch to bike
    navigator.setStrategy(&bikeStrategy);
    std::cout << navigator.startNavigation("Home", "Office") << std::endl;

    // switch to walk
    navigator.setStrategy(&walkStrategy);
    std::cout << navigator.startNavigation("Home", "Office") << std::endl;

    return 0;
}