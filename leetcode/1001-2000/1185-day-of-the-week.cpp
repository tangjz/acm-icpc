class Solution {
public:
    string dayOfTheWeek(int dd, int mm, int yy) {
        static const string rep[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        assert(yy > 1582);
        mm < 3 && (mm += 12, --yy);
        int c = yy / 100;
        yy %= 100;
        int w = (c / 4 - 2 * c + yy + yy / 4 + 13 * (mm + 1) / 5 + dd - 1) % 7;
        return rep[w < 0 ? w + 7: w];
    }
};
