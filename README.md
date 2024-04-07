# CapstoneProject
Certainly! Below is the formatted version of your capstone project description in Markdown:

---

# Capstone Project (2023-24)

## Team Name: Wizards of the O(z!)

## Team Problem: P9

### Team Members:

- Parshv Joshi (202301039)
- Siddharth Rambhia (202301072)
- Prasanna Gupta (202301124)
- Rishit Raj Jain (202301167)

## Pseudocode

### Initialize the weekly schedule with user input, representing the fixed schedule of shows for each hour in a week.
### Initialize family members with their ID, available time slots, and preferred shows.

```
For each hour in the week:
    If a show is already scheduled, update the family members' preferences to indicate the show has been recorded.
    If no show is scheduled, determine the most popular show among available family members and schedule it.
Print the final schedule, showing the allocated shows for each hour of the week.
```

#### Time Complexity: O(n)
#### Space Complexity: O(n)

### Algorithm

```
class Show
    initialize(id)

class FamilyMember
    initialize(id, availableSlots, preferredShows)
    for each slot in availableSlots
        set availability[slot] to true
    for each show in preferredShows
        set this.preferredShows[show] to true

class Schedule
    initialize(weeklySchedule, members)
    for each hour in 0 to 167
        for each member in members
            if member is available at hour
                add member index to availToMembers[hour]

function recordAndScheduleShows()
    for each hour in 0 to 167
        if weeklySchedule[hour] is not empty
            set finalSchedule[hour] to weeklySchedule[hour]
            update members' preference
        else
            calculate show popularity among available members
            schedule the most popular show
            update members' preference

function printSchedule(schedule)
    for each hour in 0 to 167
        print day and hour
        if a show is scheduled
            print the show

main()
    prompt user for weekly schedule
    prompt user for family member data
    initialize Schedule
    call recordAndScheduleShows()
    call printSchedule()
```

## Sample Test Case

### Data Structures Used

- **Vector**: 
    - Vectors dynamically resize themselves to accommodate the number of elements inserted.
    - Elements in vectors can be accessed randomly in constant time (O(1)), making them suitable for scenarios where frequent access to elements by index is required.
    - Contiguous Memory: Vectors store their elements in contiguous memory locations.
- **Unordered map**: 
    - Unordered maps provide fast lookup times (average-case constant time complexity, O(1)) for accessing elements by key, making them suitable for scenarios where fast retrieval of key-value pairs is required.
    - Unordered maps use hash tables internally, which results in efficient storage and retrieval of key-value pairs, especially when dealing with large datasets.
- **Unordered set**: 
    - Similar to unordered maps, unordered sets offer fast lookup times (average-case constant time complexity, O(1)), making them suitable for scenarios where fast membership testing is required.
    - Unordered sets store unique elements only, automatically discarding duplicate values. This property is useful when dealing with collections where uniqueness is important.

### Contributions

- **Siddharth Rambhia**: designed and implemented the algorithm to schedule shows
- **Parshv Joshi**: decided on and implemented the data structures used in the project
- **Prasanna Gupta**: designed and implemented the code to handle inputs
- **Rishit Jain**: implemented the code to output the schedule and wrote the documentation.

---

Feel free to adjust the formatting as per your preferences!
