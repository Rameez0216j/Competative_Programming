## Problem Statement (Rewritten Simply):

You are given:

- Three teams: Team1, Team2, Team3.
- Each team can complete a task in `n1`, `n2`, `n3` days respectively.
- You have `T` tasks to complete.
- **Each task must go through all 3 teams, in order** (i.e., first Team1, then Team2, then Team3).
- A team can only work on one task at a time and teams work independently.

**Goal:**  
Find the **minimum number of days (`D`)** required to finish all `T` tasks.

---

## Key Observations

### Team 1:
- Can start immediately at day 0.
- Since it takes `n1` days per task, in `D` days it can process:
  ```
  tasks_by_team1 = D // n1
  ```

---

### Team 2:
- **Must wait until Team 1 finishes first task**, i.e., wait `n1` days.
- Then, it starts processing.
- Has only `(D - n1)` days left.
- Can process:
  ```
  tasks_by_team2 = (D - n1) // n2   (if D > n1)
  ```

But here's the **catch**:  
Even if Team 2 can do more tasks, it canâ€™t work faster than Team 1 gives tasks.

So we take the minimum of:
```python
tasks_stage2 = min(tasks_by_team1, tasks_by_team2)
```

### Why this `min`?
- If **Team 1 is slower** (`n1 > n2`), then Team 2 will be waiting.
- If **Team 1 is faster** (`n1 < n2`), then Team 2 will become the bottleneck.
- So, total tasks that **can fully complete Team 2** stage is **limited by both sides**.

---

### Team 3:
- Waits for both Team 1 and Team 2 to finish.
- So it starts only after `n1 + n2` days.
- Has `(D - n1 - n2)` days to work.
- Can process:
  ```
  tasks_by_team3 = (D - n1 - n2) // n3   (if D > n1 + n2)
  ```

And again, it depends on how many tasks are ready from Team 2:
```python
tasks_stage3 = min(tasks_stage2, tasks_by_team3)
```

---

## Binary Search Framework

We use binary search to **minimize the number of days (`D`)** such that `tasks_stage3 >= T`.

---

## Code with Explanation

```python
def min_days(n1, n2, n3, T):
    def can_finish(D):
        # Team 1: no wait, can work for all D days
        tasks1 = D // n1

        # Team 2: must wait n1 days for first task from Team 1
        if D < n1:
            return False  # Not even the first task can pass Team 1
        tasks2 = (D - n1) // n2
        stage2 = min(tasks1, tasks2)

        # Team 3: must wait for both Team 1 and Team 2
        if D < n1 + n2:
            return False
        tasks3 = (D - n1 - n2) // n3
        stage3 = min(stage2, tasks3)

        return stage3 >= T  # Can we finish T tasks?

    # Binary Search: answer lies between 0 and a big enough number
    low, high = 0, T * (n1 + n2 + n3)

    while low < high:
        mid = (low + high) // 2
        if can_finish(mid):
            high = mid
        else:
            low = mid + 1

    return low
```

---

## Example 1:
```python
n1 = 3, n2 = 2, n3 = 1, T = 5
```

Letâ€™s try to understand how tasks move:

- Team 1: every 3 days â†’ 1 task  
  So in 15 days: 15 // 3 = 5 tasks

- Team 2: wait 3 days, then every 2 days  
  So in (15 - 3) = 12 days â†’ 12 // 2 = 6 tasks  
  But canâ€™t process more than Team 1 gave â†’ min(5, 6) = 5

- Team 3: wait 5 days (3+2), then every 1 day  
  So in (15 - 5) = 10 days â†’ 10 tasks  
  But canâ€™t process more than Team 2 gave â†’ min(5, 10) = 5

So, 15 days is enough. Binary search helps find the smallest such day.

---

## Why Use `min()` at Each Stage?

Because **each team depends on the team before it.**  
Even if a team is fast, it canâ€™t go faster than tasks arriving from the previous stage.

So, to get **true task completion**, we always take the minimum of:
- Tasks already done in the previous stage
- Tasks that can be handled by the current stage in available time

---

## Recap of Cases

### Case 1: `n1 > n2`  
- Team 1 is slow  
- Team 2 is idle often  
- So actual progress of Team 2 = limited by Team 1

### Case 2: `n1 < n2`  
- Team 1 is fast  
- Team 2 becomes bottleneck  
- Actual progress = what Team 2 can process

This logic repeats across each stage.