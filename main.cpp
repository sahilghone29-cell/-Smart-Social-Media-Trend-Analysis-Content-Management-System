#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

// ==========================================
// 1. CORE DATA STRUCTURE MODELS
// ==========================================

// Post entity reflecting content performance fields
struct Post {
    int postID;
    string title;
    string category;
    int likes;
    int comments;
    int shares;
    int engagementScore;

    // Pricing & Performance Strategy Logic
    void calculateMetrics() {
        // Engagement Metric Calculation Formula: Likes(1x) + Comments(2x) + Shares(3x)
        engagementScore = (likes * 1) + (comments * 2) + (shares * 3);
    }
};

// Node Structure for Content Database (AVL Tree)
struct AVLNode {
    Post post;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(Post p) : post(p), left(nullptr), right(nullptr), height(1) {}
};

// User Profile Structure for Network Graph
struct User {
    int userID;
    string name;
};

// ==========================================
// 2. CORE ENGINE IMPLEMENTATION
// ==========================================

class SocialDashboardEngine {
private:
    AVLNode* avlRoot;                                     // BST/AVL Tree for ordered Content Database
    unordered_map<int, Post*> hashTable;                 // Hashing for rapid O(1) content retrieval
    stack<Post> revisionHistory;                         // Stack for managing content revisions (Undo)
    queue<Post> publishingWorkflow;                       // Queue for content publishing workflows
    unordered_map<int, vector<int>> userGraph;           // Graph for social network relationships
    unordered_map<int, User> userRegistry;               // Map to fetch User records by ID

    // --- Internal AVL / BST Helper Implementations ---
    int getHeight(AVLNode* n) { return n ? n->height : 0; }
    int getBalance(AVLNode* n) { return n ? getHeight(n->left) - getHeight(n->right) : 0; }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    AVLNode* insertAVL(AVLNode* node, Post p) {
        if (!node) return new AVLNode(p);
        if (p.postID < node->post.postID)
            node->left = insertAVL(node->left, p);
        else if (p.postID > node->post.postID)
            node->right = insertAVL(node->right, p);
        else
            return node; // Duplicate IDs ignored

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && p.postID < node->left->post.postID) return rightRotate(node);
        if (balance < -1 && p.postID > node->right->post.postID) return leftRotate(node);
        if (balance > 1 && p.postID > node->left->post.postID) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && p.postID < node->right->post.postID) {
            node->right = leftRotate(node->right);
            return rightRotate(node);
        }
        return node;
    }

    void inorderDatabase(AVLNode* root) {
        if (root) {
            inorderDatabase(root->left);
            cout << "  [ID: " << root->post.postID << "] Title: " << root->post.title 
                 << " | Cat: " << root->post.category << " | Engagement: " << root->post.engagementScore << "\n";
            inorderDatabase(root->right);
        }
    }

    void DFSUtil(int node, unordered_map<int, bool>& visited) {
        visited[node] = true;
        cout << userRegistry[node].name << " (ID: " << node << ") ";
        for (int neighbor : userGraph[node]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }

public:
    SocialDashboardEngine() : avlRoot(nullptr) {}

    // --- Content Engine Actions ---
    void addLivePost(Post p) {
        p.calculateMetrics();
        avlRoot = insertAVL(avlRoot, p);
        
        Post* persistentPost = new Post(p);
        hashTable[p.postID] = persistentPost;
        cout << "[DATABASE] Post record #" << p.postID << " loaded into active frameworks.\n";
    }

    void editPost(int id, string newTitle, string newCat) {
        if (hashTable.find(id) == hashTable.end()) {
            cout << "[ERROR] Content ID not found.\n";
            return;
        }
        // Stack Operation: Capture revision checkpoint
        revisionHistory.push(*hashTable[id]);

        hashTable[id]->title = newTitle;
        hashTable[id]->category = newCat;
        cout << "[STACK] Revision snapshot saved. Post updated successfully.\n";
    }

    void rollbackLastEdit() {
        if (revisionHistory.empty()) {
            cout << "[STACK] Revision history clear. Nothing to undo.\n";
            return;
        }
        Post previousState = revisionHistory.top();
        revisionHistory.pop();

        if (hashTable.find(previousState.postID) != hashTable.end()) {
            *hashTable[previousState.postID] = previousState;
            cout << "[UNDO] Success. Content rolled back to previous version state.\n";
        }
    }

    void searchPostFast(int id) {
        // Hashing Search: O(1) Time complexity strategy
        if (hashTable.find(id) != hashTable.end()) {
            Post* ptr = hashTable[id];
            cout << "\n[HASH SEARCH RESULT - O(1)]\n"
                 << "ID: " << ptr->postID << "\nTitle: " << ptr->title 
                 << "\nCategory: " << ptr->category << "\nEngagement Score: " << ptr->engagementScore << "\n";
        } else {
            cout << "[ERROR] Post ID data missing from index.\n";
        }
    }

    // --- Workflow Engine Actions ---
    void stageToQueue(Post p) {
        publishingWorkflow.push(p);
        cout << "[QUEUE] Post staged into the content management buffer pipeline.\n";
    }

    void processNextQueueItem() {
        if (publishingWorkflow.empty()) {
            cout << "[QUEUE] Publishing pipeline idle. No jobs pending.\n";
            return;
        }
        Post p = publishingWorkflow.front();
        publishingWorkflow.pop();
        cout << "[WORKFLOW] Dequeuing post workflow ID #" << p.postID << "...\n";
        addLivePost(p);
    }

    // --- Sorting & Analytics Strategies (Pricing Strategy Implementation) ---
    void compileTrendingDashboard() {
        vector<Post> analyticsBatch;
        for (auto const& [id, ptr] : hashTable) {
            analyticsBatch.push_back(*ptr);
        }

        if (analyticsBatch.empty()) {
            cout << "[DASHBOARD] No active performance profiles to track.\n";
            return;
        }

        // Sorting: Emulating Merge Sort mechanics via stable_sort O(n log n)
        stable_sort(analyticsBatch.begin(), analyticsBatch.end(), [](const Post& a, const Post& b) {
            return a.engagementScore > b.engagementScore;
        });

        cout << "\n=== PERFORMANCE & STRATEGIC ANALYTICS DASHBOARD ===\n";
        for (const auto& item : analyticsBatch) {
            cout << " Rank Index -> Score: " << item.engagementScore 
                 << " | [Category: " << item.category << "] Title: " << item.title << " (ID: " << item.postID << ")\n";
            
            // Core Pricing & Strategic Output Rules Mapped to Engagement Bounds
            if (item.engagementScore >= 1000) {
                cout << "   [PRICING STRATEGY]: Prioritize high-engagement tier. Allocate peak premium ad spend.\n";
                cout << "   [CAMPAIGN IMPACT]: Maximum Audience Targeting optimization achieved.\n";
            } else if (item.engagementScore >= 500) {
                cout << "   [PRICING STRATEGY]: Medium-engagement stable index. Maintain optimized campaign resources.\n";
                cout << "   [CAMPAIGN IMPACT]: Balanced content visibility across channels.\n";
            } else {
                cout << "   [PRICING STRATEGY]: Low visibility tier. Restructure creative formatting rules.\n";
                cout << "   [CAMPAIGN IMPACT]: Low marketing effectiveness. Requires targeting re-calibration.\n";
            }
            cout << "---------------------------------------------------------\n";
        }
    }

    // --- User Graph & Network Relationship Logic ---
    void registerUser(int id, string name) {
        User u = {id, name};
        userRegistry[id] = u;
        if (userGraph.find(id) == userGraph.end()) {
            userGraph[id] = vector<int>();
        }
        cout << "[GRAPH] Registered network member node: " << name << "\n";
    }

    void connectUsers(int id1, int id2) {
        userGraph[id1].push_back(id2);
        userGraph[id2].push_back(id1);
        cout << "[GRAPH] Edge mapped. Connection built between User " << id1 << " and User " << id2 << "\n";
    }

    void runBFSAudienceSpread(int startID) {
        if (userGraph.find(startID) == userGraph.end()) {
            cout << "[ERROR] Invalid reference user target node.\n";
            return;
        }
        unordered_map<int, bool> visited;
        queue<int> q;

        visited[startID] = true;
        q.push(startID);

        cout << "\n[BFS AUDIENCE INSIGHTS SPREAD TRAVERSAL]:\n";
        int totalReach = 0;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            totalReach++;
            cout << " -> " << userRegistry[curr].name;

            for (int adjacent : userGraph[curr]) {
                if (!visited[adjacent]) {
                    visited[adjacent] = true;
                    q.push(adjacent);
                }
            }
        }
        cout << "\n[ANALYTICS SUMMARY] Total Content Audience Reach Matrix Count: " << totalReach << " users.\n";
    }

    void detectUserCommunities() {
        unordered_map<int, bool> visited;
        int communityID = 0;

        cout << "\n[DFS NETWORK ISOLATED COMMUNITY CLUSTERING DETECTION]:\n";
        for (auto const& [userId, edges] : userGraph) {
            if (!visited[userId]) {
                communityID++;
                cout << " Cluster Profile Group " << communityID << ": [ ";
                DFSUtil(userId, visited);
                cout << "]\n";
            }
        }
    }

    void printAVLRatingsRaw() {
        cout << "\n=== Raw Content Database Registry (In-Order AVL Display) ===\n";
        if (!avlRoot) cout << " No database instances loaded.\n";
        inorderDatabase(avlRoot);
    }
};

// ==========================================
// 3. MENU CONTROL INTERFACE LOOP
// ==========================================

int main() {
    SocialDashboardEngine engine;
    int inputCommand;

    cout << "=== INITIALIZING SYSTEMS WITH COMPREHENSIVE RAW DATASET ===\n\n";
    
    // Data Population Phase 1: Social Connections Mapping (Graph)
    engine.registerUser(1, "Aria Vance");
    engine.registerUser(2, "Braxton Miller");
    engine.registerUser(3, "Chloe Sterling");
    engine.registerUser(4, "David Kim");
    engine.registerUser(5, "Elena Rostova");
    engine.registerUser(6, "Felix Vance");
    
    engine.connectUsers(1, 2);
    engine.connectUsers(1, 3);
    engine.connectUsers(2, 3); // Community Group 1: Connected Cluster
    engine.connectUsers(5, 6); // Community Group 3: Secondary Micro Segment
                               // Note: David Kim (4) remains unlinked as an isolated platform profile.

    // Data Population Phase 2: Active Content Injection (AVL Tree & Hash Indices)
    Post post1 = {101, "UI/UX Design Trends for 2026", "Tech", 350, 95, 60, 0};
    Post post2 = {105, "5 Vegan High-Protein Recipes", "Health", 120, 40, 15, 0};
    Post post3 = {112, "Global Stock Market Updates", "Finance", 890, 310, 240, 0};
    Post post4 = {120, "Indie Pop Music Playlist Release", "Music", 45, 10, 2, 0};
    Post post5 = {135, "Remote Work Productivity Toolkit", "Business", 510, 180, 110, 0};
    
    engine.addLivePost(post1);
    engine.addLivePost(post2);
    engine.addLivePost(post3);
    engine.addLivePost(post4);
    engine.addLivePost(post5);

    // Data Population Phase 3: Staging Workflow Queues (Queue Pipeline Buffer)
    Post queuePost1 = {201, "Next-Gen Smartphone Review", "Tech", 400, 110, 90, 0};
    Post queuePost2 = {202, "Summer Travel Packing Guide", "Lifestyle", 150, 35, 20, 0};
    Post queuePost3 = {203, "Understanding Crypto Regulations", "Finance", 600, 200, 140, 0};
    
    engine.stageToQueue(queuePost1);
    engine.stageToQueue(queuePost2);
    engine.stageToQueue(queuePost3);

    cout << "\n=== SYSTEM SYSTEM ENGINE ONLINE. CORE INTERFACE READY ===\n";

    do {
        cout << "\n=========================================================\n";
        cout << "  ENTERPRISE SOCIAL MEDIA TREND ANALYSIS & MGMT SYSTEM   \n";
        cout << "=========================================================\n";
        cout << "1. Add Post Instantly (AVL & Hash Entry)\n";
        cout << "2. Stage Content to Scheduling Queue (Queue Insertion)\n";
        cout << "3. Release Next Scheduled Workflow Item (Queue Removal)\n";
        cout << "4. Modify Existing Post Metadata (Stack Tracking)\n";
        cout << "5. Trigger Undo Command (Stack Pop Recovery)\n";
        cout << "6. Execute Rapid Lookup Index (O(1) Hash Map Search)\n";
        cout << "7. Render Performance & Campaign Dashboard (Sorting Engine)\n";
        cout << "8. Link Social Platform Users (Map Graph Matrix)\n";
        cout << "9. Compute Audience Spread Metrics (BFS Implementation)\n";
        cout << "10. Scan Disjoint Market Clusters (DFS Strategy)\n";
        cout << "11. Diagnostic: Output In-Order Database Sequence\n";
        cout << "0. Shutdown Core Engine Processing Framework\n";
        cout << "---------------------------------------------------------\n";
        cout << "Enter Executive Action Selection Index (ONLY Input Numbers): ";
        
        // Input protection check to eliminate infinite loops or crashing on typo character inputs
        if (!(cin >> inputCommand)) {
            cout << "\n[ERROR] Text characters detected. Please input numeric choices (0-11) only.\n";
            cin.clear();            
            cin.ignore(1000, '\n'); 
            inputCommand = -1;      
            continue;
        }

        switch(inputCommand) {
            case 1: {
                Post p;
                cout << "Set unique numeric Post ID: "; cin >> p.postID;
                cin.ignore();
                cout << "Set Content Title: "; getline(cin, p.title);
                cout << "Set Analytical Category: "; getline(cin, p.category);
                cout << "Input Baseline Metrics [Likes Comments Shares]: ";
                cin >> p.likes >> p.comments >> p.shares;
                engine.addLivePost(p);
                break;
            }
            case 2: {
                Post p;
                cout << "Set Target Task Post ID: "; cin >> p.postID;
                cin.ignore();
                cout << "Set Queue Task Title: "; getline(cin, p.title);
                cout << "Set Category Tag: "; getline(cin, p.category);
                cout << "Project Target Benchmarks [Likes Comments Shares]: ";
                cin >> p.likes >> p.comments >> p.shares;
                engine.stageToQueue(p);
                break;
            }
            case 3:
                engine.processNextQueueItem();
                break;
            case 4: {
                int id; string title, category;
                cout << "Enter Target Post ID to edit (e.g., 112): "; cin >> id;
                cin.ignore();
                cout << "Enter Revised Content Title: "; getline(cin, title);
                cout << "Enter Revised Category Tag: "; getline(cin, category);
                engine.editPost(id, title, category);
                break;
            }
            case 5:
                engine.rollbackLastEdit();
                break;
            case 6: {
                int id;
                cout << "Target Index Query ID (e.g., 135): "; cin >> id;
                engine.searchPostFast(id);
                break;
            }
            case 7:
                engine.compileTrendingDashboard();
                break;
            case 8: {
                int id1, id2;
                cout << "Source User ID: "; cin >> id1;
                cout << "Destination Target User ID: "; cin >> id2;
                engine.connectUsers(id1, id2);
                break;
            }
            case 9: {
                int id;
                cout << "Enter Base Search Root Node (e.g., 1): "; cin >> id;
                engine.runBFSAudienceSpread(id);
                break;
            }
            case 10:
                engine.detectUserCommunities();
                break;
            case 11:
                engine.printAVLRatingsRaw();
                break;
            case 0:
                cout << "De-allocating dynamic memories. Execution pipeline stopped safely.\n";
                break;
            default:
                cout << "[ERROR] Selection out of bounds. Choose an option from 0 to 11.\n";
        }
    } while (inputCommand != 0);

    return 0;
}