class Solution {
public:
    vector<double> convertTemperature(double x) {
        return {x + 273.15, x * 1.8 + 32};
    }
};
