class ParkingSystem {
    int ctr[3];
public:
    ParkingSystem(int big, int medium, int small) {
        ctr[0] = big;
        ctr[1] = medium;
        ctr[2] = small;
    }

    bool addCar(int carType) {
        if(ctr[--carType] <= 0)
            return 0;
        --ctr[carType];
        return 1;
    }
};

/**
 * Your ParkingSystem object will be instantiated and called as such:
 * ParkingSystem* obj = new ParkingSystem(big, medium, small);
 * bool param_1 = obj->addCar(carType);
 */
