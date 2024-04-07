#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Show {
public:
    int id;
    Show(int id) : id(id) {}
};

class FamilyMember {
public:
    int id;
    std::vector<bool> preferredShows;
    std::vector<bool> availability;

    FamilyMember(int id, const std::vector<int>& availableSlots, const std::vector<int>& preferredShows)
        : id(id), preferredShows(168, false), availability(168, false) {
        for (const auto &slot : availableSlots) {
            availability[slot] = true;
        }
        for (const auto &show : preferredShows) {
            this->preferredShows[show] = true;
        }
    }
};

class Schedule {
public:
    std::vector<int> weeklySchedule;
    std::vector<FamilyMember> members;
    std::vector<int> finalSchedule;
    std::vector<std::vector<int>> availToMembers;

    Schedule(const std::vector<int>& weeklySchedule, const std::vector<FamilyMember>& members)
        : weeklySchedule(weeklySchedule), members(members), finalSchedule(168, -1), availToMembers(168) {
        for (int i = 0; i < 168; i++) {
            for (int j = 0; j < members.size(); j++) {
                if (members[j].availability[i]) {
                    availToMembers[i].push_back(j);
                }
            }
        }
    }

    void recordAndScheduleShows() {
        for (int i = 0; i < 168; i++) {
            if (weeklySchedule[i] != -1) {
                finalSchedule[i] = weeklySchedule[i];
                for (auto &memIndex: availToMembers[i]) {
                    members[memIndex].preferredShows[weeklySchedule[i]] = false;
                }
            }
        }

        for (int i = 0; i < 168; i++) {
            if (weeklySchedule[i] == -1) {
                std::unordered_map<int, int> showPopularity;
                for (const auto &memIndex : availToMembers[i]) {
                    for (int show = 0; show < 168; show++) {
                        if (members[memIndex].preferredShows[show]) {
                            showPopularity[show]++;
                        }
                    }
                }

                int maxCount = 0;
                int showToSchedule = -1;
                for (const auto& [show, count] : showPopularity) {
                    if (count > maxCount) {
                        maxCount = count;
                        showToSchedule = show;
                    }
                }

                if (showToSchedule != -1) {
                    finalSchedule[i] = showToSchedule;
                    for (auto &memIndex : availToMembers[i]) {
                        members[memIndex].preferredShows[showToSchedule] = false;
                    }
                }
            }
        }
    }
};

void printSchedule(const Schedule& schedule) {
    std::string daysOfWeek[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    bool showScheduled = false;
    int dayIndex = 0;

    for (int hour = 0; hour < 168; hour++) {
        if (hour % 24 == 0) {
            if (dayIndex > 0 && !showScheduled) {
                std::cout << "No Show Scheduled" << std::endl;
            }
            std::cout << daysOfWeek[dayIndex++] << std::endl;
            showScheduled = false;
        }

        if (schedule.finalSchedule[hour] != -1) {
            int hourOfDay = hour % 24;
            std::cout << "  " << (hourOfDay < 10 ? "0" : "") << hourOfDay << ":00: Show " << schedule.finalSchedule[hour] << std::endl;
            showScheduled = true;
        }
    }

    if (!showScheduled) {
        std::cout << "No Show Scheduled" << std::endl;
    }
}

int main() {
    cout << "Enter number of shows : " << endl;
    int shows;
    cin >> shows;
    
    vector<int> weeklySchedule(168, -1); // Initialize the vector with -1 for each hour of week

    for (int i = 0; i < shows; ++i) {
        string line;
        int day, hour;

        cout << "Enter the day of the week (1-7, 1=>Monday) for airing of " << (i + 1) << " show : ";
        cin >> day;

        if (day < 1 || day > 7) {
            cout << "Invalid day. Please enter a number between 1 and 7." << endl;
            continue;
        }

        cout << "Enter the time (in 24-hour format, e.g., 14 for 2 PM) for airing of " << (i + 1) << " show : ";
        cin >> hour;

        if (hour < 0 || hour > 23) {
            cout << "Invalid hour. Please enter a number between 0 and 23." << endl;
            continue;
        }
        
        int showSlot = ((day - 1) * 24) + hour;
        weeklySchedule[showSlot] = (i + 1);

    }

    cout << "Enter family member data:" << endl;
    vector<FamilyMember> members;
    while (true) {
        cout << "Enter member id (or -1 to stop): ";
        int id;
        cin >> id;
        if (id == -1) break;
        
        cout << "Enter number of availability slots for member " << id << " : ";
        int freeSlots;
        cin >> freeSlots;

        cout << "Enter available slots for member " << id << " ( " << freeSlots <<  " numbers separated by spaces) : ";
        vector<int> availableSlots(freeSlots);
        for (int i = 0; i < freeSlots; i++) {
            cin >> availableSlots[i];
        }
        
        cout << "Enter number of favourite shows for member " << id << " : ";
        int favouriteShows;
        cin >> favouriteShows;

        cout << "Enter preferred shows for member " << id << " ( " << favouriteShows <<  " numbers separated by spaces) : ";
        vector<int> preferredShows(favouriteShows);
        for (int i = 0; i < favouriteShows; i++) {
            cin >> preferredShows[i];
        }

        members.emplace_back(id, availableSlots, preferredShows);
    }

    Schedule schedule(weeklySchedule, members);

    schedule.recordAndScheduleShows();

    printSchedule(schedule);

    return 0;
}