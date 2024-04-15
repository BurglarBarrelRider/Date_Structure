

#include <iostream>
#include <vector>
#include <algorithm> // for sort method

using namespace std;

struct Date {
    int day, month, year;

    Date(int d, int m, int y) {
        day = d;
        month = m;
        year = y;  
    }

    bool isValidDate(){
        if (year < 0 || month < 1 || month > 12 || day < 1)
            return false;
    
        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int maximumInMonthDay = daysInMonth[month - 1];
        if (month == 2 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))) // check if leap
            maximumInMonthDay = 29;
    
        return day <= maximumInMonthDay; // if YES then return TRUE
    }

    void newDate(int d, int m, int y) {
        day = d;
        month = m;
        year = y;
    }

    string getDayOfWeek() const {
        string days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        
        // Январь и февраль считаются как 13 и 14 месяцы предыдущего года
        if (month < 3) {
            month += 12;
            year--;
        }
    
        int dayIndex = (day + 2*month + 3*(month+1)/5 + year + year/4 - year/100 + year/400) % 7;
        return days[dayIndex];
    }


    int daysDifference(int Date& otherDate){
        int cumulativeDays[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};  // накопительные 
    
        int days1 = year * 365 + day + cumulativeDays[month - 1];
        int days2 = otherDate.year * 365 + otherDate.day + cumulativeDays[otherDate.month - 1];
    
        return abs(days1 - days2);
    }

    void displayDate(){
        string months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        cout << months[month - 1] << " " << day << ", " << year << endl;
    }

    bool operator<(const Date& otherDate) const {
        if (year != otherDate.year)
            return year < otherDate.year;
        if (month != otherDate.month)
            return month < otherDate.month;
        return day < otherDate.day;
    }
};

int main() {
    vector<Date> dates = {
        Date(1, 1, 2023),
        Date(15, 6, 2022),
        Date(31, 12, 2023)
    };
    sort(dates.begin(), dates.end());

    for (const auto& date : dates) {
        if (date.isValidDate()) {
            date.displayDate();
        } else {
            cout << "error" << endl;
        }
    }

    return 0;
}