#pragma once
#include <string>

struct record {
    int id{};
    std::wstring date{};
    int brandID{};
    std::wstring gasBrand{};
    double mileage{};
    double price{};
    double amount{};
    double total{};

    bool operator==(const record& rec) const {
        return this->id == rec.id &&
            this->date == rec.date &&
            this->brandID == rec.brandID &&
            this->gasBrand == rec.gasBrand &&
            this->mileage == rec.mileage &&
            this->price == rec.price &&
            this->amount == rec.amount &&
            this->total == rec.total;
    }
};

struct averageBetweenRefueling {
    double mileage {};
    double mileagePerLiter {};
    double pricePerKm {};
    double price {};
    double pricePerTime {};
    double timePerLiter {};

    bool operator==(const averageBetweenRefueling& abr) const {
        return this->mileage == abr.mileage &&
            this->mileagePerLiter == abr.mileagePerLiter &&
            this->pricePerKm == abr.pricePerKm &&
            this->price == abr.price &&
            this->pricePerTime == abr.pricePerTime &&
            this->timePerLiter == abr.timePerLiter;
    }
};

struct gasBrandStats {
    std::wstring gasBrand {};
    double mileage{};
    double mileagePerLiter{};
    double pricePerKm{};
    double price{};
    double pricePerTime{};
    double timePerLiter{};

    bool operator==(const gasBrandStats& gbs) const {
        return this->gasBrand == gbs.gasBrand &&
            this->mileage == gbs.mileage &&
            this->mileagePerLiter == gbs.mileagePerLiter &&
            this->pricePerKm == gbs.pricePerKm &&
            this->price == gbs.price &&
            this->pricePerTime == gbs.pricePerTime &&
            this->timePerLiter == gbs.timePerLiter;
    }
};