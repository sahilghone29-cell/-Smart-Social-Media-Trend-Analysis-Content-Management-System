# DSA-1 PS 127: Smart Social Media Trend Analysis & Content Management System

## Student Information

| Field | Details |
|---------|---------|
| Student Name | Sahil Ganesh Ghone |
| Roll Number | 150096725002 |
| Cohort Name | Demis Hassabis |
| Batch | 2025-29 |
| Subject | Data Structures and Algorithms (DSA-1) |
| Project Number | PS 127 |
| Project Title | Smart Social Media Trend Analysis & Content Management System |

---

# 2.1 Project Title

**Smart Social Media Trend Analysis & Content Management System**

---

# 2.2 Problem Statement

Organizations require a platform to analyze social media trends, manage content performance, track engagement, and identify emerging topics across digital platforms.

The system should efficiently handle content storage, retrieval, publishing workflows, engagement analysis, audience reach tracking, and community detection using Data Structures and Algorithms.

This project provides a complete social media content management and trend analysis solution implemented entirely in C++ using DSA concepts.

---

# 2.3 Objectives

The objectives of this project are:

- Analyze social media trends based on engagement metrics.
- Manage content publishing workflows.
- Track post performance and engagement.
- Retrieve content efficiently.
- Maintain revision history of posts.
- Analyze audience reach across social networks.
- Detect connected communities in user networks.
- Demonstrate practical implementation of DSA concepts in a real-world application.

---

# 2.4 System Overview / Architecture

The system consists of the following modules:

## Content Database Module
Stores posts using AVL Trees.

## Search Engine Module
Retrieves posts rapidly using Hash Tables.

## Publishing Workflow Module
Manages content scheduling and publishing using Queue.

## Revision Management Module
Tracks content modification history using Stack.

## Trend Analysis Module
Ranks posts according to engagement score using Sorting.

## Social Network Module
Stores relationships among users using Graphs.

## Audience Reach Module
Uses BFS traversal to analyze audience reach.

## Community Detection Module
Uses DFS traversal to identify connected communities.

### Architecture Flow

```text
User Input
     |
     v
Content Management
     |
     +---- AVL Tree (Storage)
     |
     +---- Hash Table (Search)
     |
     +---- Stack (Revision History)
     |
     +---- Queue (Publishing Workflow)
     |
     +---- Sorting (Trending Dashboard)
     |
     +---- Graph
              |
              +---- BFS (Audience Reach)
              |
              +---- DFS (Community Detection)
```

---

# 2.5 Data Structures and Algorithms Used

| DSA Concept | Purpose |
|------------|---------|
| AVL Tree | Store and organize content database |
| Hash Table | Fast post retrieval |
| Stack | Manage post revision history |
| Queue | Manage publishing workflows |
| Sorting Algorithm | Rank trending posts |
| Graph | Store user relationships |
| BFS | Audience reach analysis |
| DFS | Community detection |

---

# 2.6 Implementation Approach

### Step 1: Post Creation

Users can create social media posts.

Posts are stored in:

- AVL Tree
- Hash Table

---

### Step 2: Engagement Calculation

Engagement score is calculated as:

```text
Engagement Score =
Likes + (2 × Comments) + (3 × Shares)
```

---

### Step 3: Content Ranking

Posts are sorted according to engagement score.

Higher engagement posts receive higher priority.

---

### Step 4: Revision Tracking

Whenever a post is edited:

- Previous version is pushed into Stack.
- Undo operation restores previous content.

---

### Step 5: Publishing Workflow

Posts are first placed into Queue.

Publishing occurs in FIFO order.

---

### Step 6: Social Network Analysis

Graph structure stores user relationships.

BFS:
- Audience Reach Analysis

DFS:
- Community Detection

---

# 2.7 Time and Space Complexity Analysis

## Time Complexity

| Operation | Complexity |
|------------|------------|
| AVL Insert | O(log n) |
| AVL Search | O(log n) |
| Hash Search | O(1) |
| Stack Push | O(1) |
| Stack Pop | O(1) |
| Queue Insert | O(1) |
| Queue Remove | O(1) |
| Sorting | O(n log n) |
| BFS Traversal | O(V + E) |
| DFS Traversal | O(V + E) |

## Space Complexity

| Data Structure | Complexity |
|---------------|------------|
| AVL Tree | O(n) |
| Hash Table | O(n) |
| Stack | O(n) |
| Queue | O(n) |
| Graph | O(V + E) |

---

# 2.8 Execution Steps

## Compilation

```bash
g++ SocialDashboard.cpp -o SocialDashboard
```

## Execution

```bash
./SocialDashboard
```

## Menu Options

```text
1. Add Post Instantly
2. Stage Content to Scheduling Queue
3. Release Next Scheduled Workflow Item
4. Modify Existing Post Metadata
5. Trigger Undo Command
6. Execute Rapid Lookup Index
7. Render Performance Dashboard
8. Link Social Platform Users
9. Compute Audience Spread Metrics
10. Scan Disjoint Market Clusters
11. Diagnostic: Output In-Order Structure Sequence
0. Exit
```

---

# 2.9 Sample Inputs and Outputs

## Add Post

### Input

```text
1
999
Tech Post
Test
100 50 20
```

### Output

```text
[DATABASE] Post record added to AVL database & Hash storage.
```

---

## Hash Search

### Input

```text
6
999
```

### Output

```text
[HASH SEARCH RESULT - O(1)]

ID: 999
Title: Tech Post
Category: Test
Engagement Score: 260
```

---

## BFS Analysis

### Input

```text
9
1
```

### Output

```text
Alice Jenkins
Bob Vance
Charlie Green

Total Reach = 3 Users
```

---

## DFS Analysis

### Input

```text
10
```

### Output

```text
Cluster Profile Group 1
Cluster Profile Group 2
```

---

# 2.10 Screenshots
1. Main Menu<img width="1105" height="367" alt="Screenshot 2026-06-13 at 10 36 36 AM" src="https://github.com/user-attachments/assets/407c60f1-6366-4c0c-b6ff-550683889ad9" />
2. Add Post Operation<img width="1347" height="95" alt="Screenshot 2026-06-13 at 10 39 20 AM" src="https://github.com/user-attachments/assets/386bff63-156d-4274-96cb-53bcdfc24a54" />
3. Queue Insertion<img width="1347" height="107" alt="Screenshot 2026-06-13 at 10 41 11 AM" src="https://github.com/user-attachments/assets/a68f9db9-1b0b-4472-bf89-762ef6965eb4" />
4. Queue Publishing<img width="1347" height="70" alt="Screenshot 2026-06-13 at 10 41 42 AM" src="https://github.com/user-attachments/assets/dde33831-5d2b-4916-88df-ecf307a111ef" />
5. Edit Post<img width="1347" height="95" alt="Screenshot 2026-06-13 at 10 42 20 AM" src="https://github.com/user-attachments/assets/a888dfd3-54cf-4014-a82e-8d3789b23dd7" />
6. Undo Operation<img width="1347" height="58" alt="Screenshot 2026-06-13 at 10 43 48 AM" src="https://github.com/user-attachments/assets/583d6ab7-0dc9-40d7-8440-2e019bda75b5" />
7. Hash Search Result<img width="1347" height="137" alt="Screenshot 2026-06-13 at 10 44 21 AM" src="https://github.com/user-attachments/assets/5eb8e913-b97b-460a-b8b9-7e6d22e82bd4" />
8. Performance Dashboard<img width="1347" height="128" alt="Screenshot 2026-06-13 at 10 45 00 AM" src="https://github.com/user-attachments/assets/23471b0b-c055-477c-a414-1b3d3fbe82af" />
9. Graph Connection<img width="1347" height="82" alt="Screenshot 2026-06-13 at 10 46 44 AM" src="https://github.com/user-attachments/assets/099cf2b5-5505-4908-af6a-6d44e6e33331" />
10. BFS Audience Analysis<img width="1347" height="113" alt="Screenshot 2026-06-13 at 10 47 25 AM" src="https://github.com/user-attachments/assets/af083958-9797-49d6-a027-7f31b8ad2f96" />
11. DFS Community Detection<img width="1347" height="97" alt="Screenshot 2026-06-13 at 10 47 36 AM" src="https://github.com/user-attachments/assets/d7d26a3a-d259-49c7-b2c3-7eb23904029b" />
12. AVL Database Display<img width="1347" height="97" alt="Screenshot 2026-06-13 at 10 47 45 AM" src="https://github.com/user-attachments/assets/2510b4a1-f4ff-40bc-b551-01232a0271b2" />
13. Program Exit<img width="1347" height="56" alt="Screenshot 2026-06-13 at 10 48 00 AM" src="https://github.com/user-attachments/assets/28936394-329e-49b5-84db-781f6744c4ba" />





# 2.11 Results and Observations

- AVL Tree successfully maintained balanced storage of posts.
- Hashing provided O(1) average-time post retrieval.
- Stack effectively tracked post revision history.
- Queue managed content publishing workflows using FIFO order.
- Sorting ranked posts according to engagement scores.
- Graph efficiently represented social relationships.
- BFS successfully calculated audience reach.
- DFS correctly identified community clusters.
- The dashboard prioritized high-engagement content for improved marketing effectiveness.
- All project objectives were achieved successfully.

---

# 2.12 Conclusion

The Smart Social Media Trend Analysis & Content Management System was successfully implemented using C++ and Data Structures & Algorithms.

The project integrates AVL Trees, Hash Tables, Stack, Queue, Sorting Algorithms, Graphs, BFS, and DFS into a single application that performs content management, trend analysis, audience reach tracking, and community detection.

The system demonstrates how DSA concepts can be applied to solve real-world social media management problems efficiently. The project fulfills all requirements of PS 127 and provides an effective platform for analyzing content performance and user engagement.

---

## Submitted By

**Sahil Ganesh Ghone**

Roll No: 150096725002

Cohort: Demis Hassabis

Batch: 2025-29

DSA-1 Project Submission
