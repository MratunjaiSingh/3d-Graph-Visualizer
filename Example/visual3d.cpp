
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <queue>
#include<cmath>
using namespace std;

// ---------------- GRAPH ----------------
vector<vector<int>> adj;
vector<int> bfsOrder;
vector<pair<int, int>> traverseOrder;
vector<vector<int>> levels;

int currentStep = -1;
int lastTime ;
bool isDirectedGraph = true;


// ---------------- ROTATION ----------------
float rotateX = 0;
float rotateY = 0;
float rotateZ = 0;

// ---------------- NODE POSITIONS ----------------
vector<vector<float>> nodes;

// ---------------- BUILD GRAPH ----------------
void buildGraph() {
    adj = {
        {1, 2},
        {0, 2, 3, 4},
        {0, 1, 5, 6},
        {1},
        {1},
        {2},
        {2}
    };
}

// ---------------- DRAW TEXT ----------------
void drawText(float x, float y, float z, int value) {
    glRasterPos3f(x, y, z);
    string s = to_string(value);
    for (char c : s) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

// ---------------- DRAW NODE ----------------
void drawNode(float x, float y, float z, int id) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidSphere(0.2, 20, 20);
    glPopMatrix();

    // label
    glColor3f(0, 0, 0);
    drawText(x - 0.05, y + 0.25, z, id);
}

// ---------------- DRAW EDGE ----------------
// ---------------- DRAW EDGE (SMART) ----------------
void drawEdge(float x1, float y1, float z1,
              float x2, float y2, float z2, bool isTraversed) {
    
    // 1. Color aur Thickness Set Karo
    if (isTraversed) {
        glColor3f(0.8f, 0.0f, 0.0f); // Dark Red traversed path ke liye
        glLineWidth(4.0f);
    } else {
        glColor3f(0.5f, 0.5f, 0.5f); // Grey normal ke liye
        glLineWidth(1.0f);
    }

    // 2. Main Connecting Line Draw Karo
    glBegin(GL_LINES);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glEnd();

    // 3. Agar Directed Graph hai, toh Arrowhead (Marker) banao
    if (isDirectedGraph) {
        // Direction vector nikalna (Destination - Source)
        float dx = x2 - x1;
        float dy = y2 - y1;
        float dz = z2 - z1;
        float len = sqrt(dx * dx + dy * dy + dz * dz);
        
        if (len > 0) {
            dx /= len; dy /= len; dz /= len; // Normalize
        }

        // Destination node (radius 0.2) ke theek pehle rukna hai
        float arrowX = x2 - 0.25 * dx;
        float arrowY = y2 - 0.25 * dy;
        float arrowZ = z2 - 0.25 * dz;

        // Draw Arrowhead Marker
        glPushMatrix();
        glTranslatef(arrowX, arrowY, arrowZ);
        // Traversed hai toh marker bhi red warna dark grey
        if (isTraversed) glColor3f(0.8f, 0.0f, 0.0f); 
        else glColor3f(0.3f, 0.3f, 0.3f); 
        
        glutSolidSphere(0.06, 10, 10); // Chota dot jo arrow ka kaam karega
        glPopMatrix();
    }
}

// ---------------- BFS LEVEL WISE ----------------
// ---------------- BFS LEVEL WISE (UPDATED) ----------------
void BFS(int start) {
    bfsOrder.clear();
    levels.clear();
    traverseOrder.clear(); // Har nayi run par isko clear karna zaroori hai

    vector<bool> vis(adj.size(), false);
    // Queue ab node ke sath uska parent bhi store karegi: {current_node, parent_node}
    queue<pair<int, int>> q; 

    q.push({start, -1}); // Start node ka koi parent nahi hota isliye -1
    vis[start] = true;

    while (!q.empty()) {
        int size = q.size();
        vector<int> level;

        for (int i = 0; i < size; i++) {
            int node = q.front().first;
            int parent = q.front().second;
            q.pop();

            bfsOrder.push_back(node);
            
            // Start node ko chhod kar baaki sabki edges save karo
            if (parent != -1) {
                traverseOrder.push_back({parent, node});
            }
            
            level.push_back(node);

            for (auto nbr : adj[node]) {
                if (!vis[nbr]) {
                    vis[nbr] = true;
                    q.push({nbr, node}); // Nbr node ke liye current node uska parent ban jayega
                }
            }
        }
        levels.push_back(level);
    }
}

// ---------------- ASSIGN POSITIONS ----------------
void assignPositions() {
    nodes.clear();
    nodes.resize(adj.size());

    float startY = 1.5;
    float gapY = 1.2;

    for (int i = 0; i < levels.size(); i++) {
        float y = startY - i * gapY;

        int sz = levels[i].size();
        float startX = -(sz - 1) * 0.7;

        for (int j = 0; j < sz; j++) {
            int node = levels[i][j];
            float x = startX + j * 1.4;

            nodes[node] = {x, y, 0};
        }
    }
}

// ---------------- KEYBOARD ----------------
void keyboard(unsigned char key, int x, int y) {

    // Y-axis
    if (key == 'l' || key == 'L') rotateY -= 5;
    if (key == 'r' || key == 'R') rotateY += 5;

    // X-axis
    if (key == 'u' || key == 'U') rotateX -= 5;
    if (key == 'd' || key == 'D') rotateX += 5;

    // Z-axis
    if (key == 'z' || key == 'Z') rotateZ -= 5;
    if (key == 'x' || key == 'X') rotateZ += 5;

    glutPostRedisplay();
}


// ---------------- DISPLAY (Cleaned Up) ----------------
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0, 2, 6,
              0, 0, 0,
              0, 1, 0);

    // ROTATIONS
    glRotatef(rotateX, 1, 0, 0);
    glRotatef(rotateY, 0, 1, 0);
    glRotatef(rotateZ, 0, 0, 1);

    // DRAW EDGES
    glColor3f(0, 0, 0);
    // 1. DRAW EDGES FIRST 
    for (int i = 0; i < adj.size(); i++) {
        for (auto nbr : adj[i]) {
            // Agar directed hai toh har edge draw karo. 
            // Agar undirected hai, toh duplicate se bachne ke liye sirf i < nbr draw karo.
            if (isDirectedGraph || i < nbr) { 
                
                bool isTraversed = false;

                for (int j = 0; j <= currentStep && j < traverseOrder.size(); j++) {
                    int u = traverseOrder[j].first;
                    int v = traverseOrder[j].second;
                    
                    // Directed mein sirf exact match (u->v). Undirected mein dono side check.
                    if (isDirectedGraph) {
                        if (u == i && v == nbr) isTraversed = true;
                    } else {
                        if ((u == i && v == nbr) || (u == nbr && v == i)) isTraversed = true;
                    }
                }

                // Naya drawEdge function call kar rahe hain yahan
                drawEdge(nodes[i][0], nodes[i][1], nodes[i][2],
                         nodes[nbr][0], nodes[nbr][1], nodes[nbr][2], isTraversed);
            }
        }
    }
    glLineWidth(1.0f); // Line width reset
   

    // DRAW NODES
    for (int i = 0; i < nodes.size(); i++) {
        bool visited = false;

        // Check if node is visited up to currentStep
        for (int j = 0; j <= currentStep && j < bfsOrder.size(); j++) {
            if (bfsOrder[j] == i) {
                visited = true;
                break;
            }
        }

        if (visited)
            glColor3f(1, 0, 0); // Red for visited
        else
            glColor3f(0, 0, 1); // Blue for unvisited

        drawNode(nodes[i][0], nodes[i][1], nodes[i][2], i);
    }

    glutSwapBuffers();
    glFlush();
}

// ---------------- ANIMATION (Proper Timer) ----------------
void update(int value) {
    if (currentStep < (int)bfsOrder.size() - 1) {
        currentStep++;
        cout << "Step: " << currentStep << " - Node Visited: " << bfsOrder[currentStep] << endl;
        glutPostRedisplay(); // Redraw only when a step changes
    }
    
    // Register timer for the next step (1000ms = 1 sec)
    glutTimerFunc(1000, update, 0);
}

// ---------------- INIT (Fixed Global Variable) ----------------
void init() {
    lastTime = glutGet(GLUT_ELAPSED_TIME); // Fixed variable shadowing
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);

    buildGraph();
    BFS(0);
    assignPositions();
    
    cout << "BFS Order: ";
    for (auto x : bfsOrder) cout << x << " ";
    cout << endl;

}
//
// ---------------- RESHAPE ----------------
void reshape(int w, int h) {
    // Window ka aspect ratio set karna
    if (h == 0) h = 1; // Divide by zero se bachne ke liye
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 45 degree field of view, 0.1 se 100 tak ki visibility range
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

// ---------------- MAIN (Fixed Registration) ----------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);

    glutCreateWindow("BFS Graph Visualization 3D");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    // Start animation timer loop (calls update after 1000ms)
    glutTimerFunc(1000, update, 0); 

    glutMainLoop();
    return 0;
}



