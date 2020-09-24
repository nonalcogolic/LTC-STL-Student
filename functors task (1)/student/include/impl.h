#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    int index{0};
    BeerBrand operator()(){

        index = (index + 1) % (static_cast<int>(BeerBrand::Max));
        index =  static_cast<BeerBrand>(index) == BeerBrand::None ? index + 1 : index;
        return static_cast<BeerBrand>(index);
    }
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(const BeerBrand type)
{
    return type == BeerBrand::Corona || type == BeerBrand::HoeGaarden;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](const BeerBrand lhs, const BeerBrand rhs)
{
    return getBeerCountry(lhs) == getBeerCountry(rhs);
};

struct MixingPolicy
{
    /**
     * @todo Implement static transformator function
     * @return crafted cocktail
     *
     * @note Cookbook:
     * Gin + Lime juice = Gimlet;
     * Gin + Grapefruit juice = Greyhount;
     * Whiskey + SevenUp = SevenPlusSeven;
     * Others + Others = Oops;
     */
    static Cocktail mix(const AlcoholDrink alco, const NonAlcoholDrink nonAlco)
    {
        auto retValue = Cocktail::Oops;
        switch (alco)
        {
        case AlcoholDrink::Gin:
            if (nonAlco == NonAlcoholDrink::LimeJuice || nonAlco == NonAlcoholDrink::GrapefruitJuice)
            retValue = nonAlco == NonAlcoholDrink::LimeJuice ? Cocktail::Gimlet : Cocktail::Greyhount;
            break;

        case AlcoholDrink::Whiskey:
            retValue = nonAlco == NonAlcoholDrink::SevenUp ? Cocktail::SevenPlusSeven : Cocktail::Oops;
            break;
        default:
            ;
        }

        return retValue;
    }
};

std::function<Cocktail(const AlcoholDrink, const NonAlcoholDrink)> mixer {&MixingPolicy::mix};
