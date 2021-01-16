//
//  main.cpp
//  GPS_solution
//
//  Created by Haoning Jin on 2020/12/7.
//

#include <iostream>
#include <fstream>
#include <cassert>
#include <ctime>
#include <iomanip>

using namespace std;

class Smart_String{
private:
    char *buffer;
public:
    Smart_String(); //The buffer is initialized to nullptr value
    Smart_String(const char *); //A null terminated char array
    Smart_String(const Smart_String &); //Deep copy constructor
    ~Smart_String();  //Delete any heap memory and assign buffer nullptr value
    Smart_String& operator = (const Smart_String &); //Deep copy assignment
    int length() const; //Return the number of printable characters
    bool empty() const;  //Return true if length is 0. Otherwise return false
    char& operator [] (const int &) const;  //Assert index and then return the char at the index
    Smart_String operator + (const char &) const; //See assignment 1
    Smart_String& operator += (const char &); //See assignment 1
    bool operator == (const Smart_String &) const; //See assignment 1
    bool operator != (const Smart_String &) const; //See assignment 1
    friend istream& operator >> (istream &, Smart_String &); //Implemented for you
    friend ostream& operator << (ostream &, const Smart_String &); //Implemented for you
};

Smart_String::Smart_String(){
    buffer = nullptr;
}

Smart_String::Smart_String(const char *c){
    int len{0};
    if (c == nullptr) {
        len = 0;
    }
    else{
        while (c[len] != '\0') {
            len ++;
        }
    }
    if (len == 0) {
        buffer = nullptr;
    }
    else{
        buffer = new char [len + 1];
        for (int i{0}; i < len; i++) {
            buffer[i] = c[i];
        }
        buffer[len + 1] = '\0';
    }
}

Smart_String::Smart_String(const Smart_String &c){
    int size = c.length();
    if (size == 0) {
        buffer = nullptr;
    }
    else{
        buffer = new char [size + 1];
        for (int i{0}; i < size; i++) {
            buffer[i] = c[i];
        }
        buffer[size + 1] = '\0';
    }
}

Smart_String::~Smart_String(){
    if (buffer != nullptr) {
        delete [] buffer;
        buffer = nullptr;
    }
}

Smart_String& Smart_String::operator=(const Smart_String &s){
    if(this == &s){
        return *this;
    }
    this -> ~Smart_String();
    this -> buffer = new char [s.length()];
    for(int i{0}; i < s.length(); i++){
        this -> buffer[i] = s[i];
    }
    this -> buffer[s.length()] = '\0';
    return *this;
}

int Smart_String::length() const{
    if(buffer == nullptr){
        return 0;
    }
    int i{0};
    while(buffer[i] != '\0'){
        i++;
    }
    return i;
}

bool Smart_String::empty() const{
    if(buffer == nullptr || buffer[0] == '\0'){
        return true;
    }
    return false;
}

char& Smart_String::operator[](const int &index) const{
    if (index >= 0 && index < this -> length()) {
        return this -> buffer[index];
    }
    else{
        cout << "ERROR Index Out of Bounds." << endl;
        abort();
    }
}

Smart_String Smart_String::operator+(const char &c) const{
    Smart_String temp = new char [this -> length() + 1];
    for(int i{0}; i < this -> length(); i++){
        temp[i] = this -> buffer[i];
    }
    temp[this -> length()] = c;
    temp[this -> length() + 1] = '\0';
    return temp;
}

Smart_String& Smart_String::operator+=(const char &c){
    *this = *this + c;
    return *this;
}

bool Smart_String::operator==(const Smart_String &s) const{
    if(this -> length() != s.length()){
        return false;
    }
    for(int i{0}; i < this -> length(); i++){
        if(this -> buffer[i] != s[i]){
            return false;
        }
    }
    return true;
}

bool Smart_String::operator!=(const Smart_String &s) const{
    return !(*this == s);
}

istream& operator >> (istream &in, Smart_String &s){
    //This function reads from keyboard or file characters until either a TAB, EOL, or EOF is reached
    //The function ignores any leading or trailing spaces.

    //Define some useful constant values
    #define SPACE ' '
    #define TAB '\t'
    #define EOL '\n'

    //Delete the old value of s
    s.~Smart_String();

    //Skip leading spaces, tabs, and empty lines
    char ch = '\0';
    while (!in.eof()){
        in.get(ch);
        if (ch == SPACE || ch == TAB || ch == EOL)
            continue;
        break;
    }

    //Append the value in ch to s
    if (ch != SPACE && ch != TAB && ch != EOL)
        s += ch;

    //Read characters into s until a TAB or EOL or EOF is reached
    while (!in.eof()){
        in.get(ch);
        if (ch == TAB || ch == EOL || in.eof())
            break;
        else
            s += ch;
    }

    //Remove any trailing spaces
    int trailingSpacesCount = 0;
    for (int i = s.length()-1; i >= 0; i--){
        if (s[i] != SPACE)
            break;
        trailingSpacesCount++;
    }
    Smart_String temp;
    for (int i = 0; i < s.length()-trailingSpacesCount; i++)
        temp += s[i];
    s = temp;

    return in;
}

ostream& operator << (ostream &out, const Smart_String &s){
    for (int i = 0; i < s.length(); i++)
        out << s[i];
    return out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class SmarterArray{
private:
    T *A;
    int size;

public:
    //Constructors
    SmarterArray(); //Implemented for you
    SmarterArray(const T*, const int&); //Deep copy of the argument
    SmarterArray(const SmarterArray<T>&); //Deep copy of the argument

    //Assignment operator
    SmarterArray<T>& operator = (const SmarterArray<T>&); //Memory clean up and deep copy of the argument

    //Destructor
    ~SmarterArray(); //Memory clean up

    //Getters, Setters, operators and other functions
    int getSize() const; //Return the number of elements in the container
    T& operator[](const int&) const; //Assert index and then return the element at the given index
    int find(const T&) const; //Return the index of the first element that is == to the argument.
                                //Return -1 if not found.
    void append(const T&);  //Store the argument value after the last element
    void insert(const int &, const T&); //Assert the integer argument index >= 0 && index <= size and then
                                        //Insert the T type argument into the calling object at the index.
                                        //If the integer argument is equal to size, then perform append
    bool remove(const int&); //If the index is valid, then remove the element at the index argument
                            //from the calling object and return true. Otherwise return false.
                            //You don't need to assert the index argument.
    bool operator == (const SmarterArray<T>&) const; //return true if sizes are equal and
                                                        //elements at same indexes are equal
    
    template <class T1>
    friend ostream& operator << (ostream&, const SmarterArray<T1>&); //Implemented for you
};

template <class T>
SmarterArray<T>::SmarterArray(){
    this -> A = nullptr;
    this -> size = 0;
}

template <class T>
SmarterArray<T>::SmarterArray(const T* A, const int& size){
    this -> size = size;
    if (this -> getSize() > 0) {
        this -> A = new T[this -> getSize()];
        for (int i{0}; i < this -> getSize(); i++) {
            this -> A[i] = A[i];
        }
    }
}

template <class T>
SmarterArray<T>::SmarterArray(const SmarterArray<T>& L){
    this -> size = L.getSize();
    if (this -> getSize() > 0) {
        this -> A = new T [this -> getSize()];
        for (int i{0}; i < this -> getSize(); i++) {
            this -> A[i] = L[i];
        }
    }
}

template <class T>
SmarterArray<T>& SmarterArray<T>::operator=(const SmarterArray<T> &L){
    if(this == &L){
        return *this;
    }
    this -> ~SmarterArray<T>();
    this -> size = L.getSize();
    if(this -> getSize() > 0){
        this -> A = new T [this -> getSize()];
        for(int i{0}; i < this -> getSize(); i++){
            this -> A[i] = L[i];
        }
    }
    return *this;
}

template <class T>
SmarterArray<T>::~SmarterArray(){
    if(this -> getSize() > 0){
        delete [] this -> A;
        this -> size = 0;
    }
}

template <class T>
int SmarterArray<T>::getSize() const{
    return this -> size;
}

template <class T>
T& SmarterArray<T>::operator[](const int &index) const{
    if(index > this -> getSize()){
        cout << "ERROR! Index out of bounds." << endl;
        abort();
    }
    return this -> A[index];
}

template <class T>
int SmarterArray<T>::find(const T &e) const{
    for(int i{0}; i < this -> getSize(); i++){
        if(this -> A[i] == e){
            return i;
        }
    }
    return -1;
}

template <class T>
void SmarterArray<T>::append(const T &e){
    T* temp = new T [this -> getSize() + 1];
    for(int i{0}; this -> getSize(); i++){
        temp[i] = this -> A[i];
    }
    temp[this -> getSize()] = e;
    if(this -> getSize() > 0){
        delete [] this -> A;
    }
    this -> A = temp;
    this -> size += 1;
}

template <class T>
void SmarterArray<T>::insert(const int &index, const T &e){
    T* temp = new T [this -> getSize() + 1];
    for(int i{0}; i < index; i++){
        temp[i] = this -> A[i];
    }
    temp[index] = e;
    for(int i{index}; i < this -> getSize(); i++){
        temp[i + 1] = this -> A[i];
    }
    if(this -> getSize() > 0){
        delete [] this -> A;
    }
    this -> A = temp;
    this -> size += 1;
}

template <class T>
bool SmarterArray<T>::remove(const int &index){
    if(index > this -> getSize()){
        return false;
    }
    T *temp = new T [this -> getSize() - 1];
    for(int i{0}; i < index; i++){
        temp[i] = this -> A[i];
    }
    for(int i{index + 1}; i < this -> getSize(); i++){
        temp[i - 1] = this -> A[i];
    }
    if(this -> getSize() > 0){
        delete [] this -> A;
    }
    this -> A = temp;
    this -> size -= 1;
    return true;
}

template <class T>
bool SmarterArray<T>::operator==(const SmarterArray<T> &L) const{
    if(this -> getSize() != L.getSize()){
        return false;
    }
    for(int i{0}; i < this -> getSize(); i++){
        if(this -> A[i] != L[i]){
            return false;
        }
    }
    return true;
}

template <class T>
ostream& operator << (ostream& out, const SmarterArray<T>& L){
    if (L.getSize() == 0)
        out << "[Empty List]";
    else{
        for (int i = 0; i < L.getSize()-1; i++)
            out << L[i] << endl;
        out << L[L.getSize()-1] << endl;
    }
    return out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Edge{
    int desVertexIndex; //the index (in the graph) of the destination vertex of this edge
    double cost; //cost of an edge
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Vertex{
private:
    Smart_String name; //name of the vertex
    SmarterArray<Edge> E; //edges emanating from this vertex. All the elements of E have the same origin
//vertex which is the this object. But they have different destination vertices which are given by the
//desVertexIndex member variable of each element

public:
    Vertex(); //Assign name = "N/A" and initialize E to an empty container
    Vertex(const Smart_String &); //Assign name = the argument and initialize E to an empty container
    Smart_String getName() const; //Return the name
    SmarterArray<Edge> getEdgeSet() const; //Return E
    int getEdgeSetSize() const; //Return the size of E
    Edge getEdge(const int &) const; //Assert an edge whose destination vertex index is equal to the
                                        //argument exists in E and then return it
    double getEdgeCost(const int &desVertexIndex) const; //Assert an edge whose destination vertex index
                                        //is equal to the argument exists in E and then return its cost
    void appendEdge(const int &desVertexIndex, const double &cost); //Assert there is no existing edge
                //whose destination vertex index and cost are equal to the argument values and then
                //append a new element whose destination vertex index and cost are initialized with the
                //argument values to E
    friend ostream& operator << (ostream &, const Vertex &); //Implemented for you
};

Vertex::Vertex(){
    this -> name = "N/A";
    this -> E.~SmarterArray();
}

Vertex::Vertex(const Smart_String &name){
    this -> name = name;
    this -> E.~SmarterArray();
}
Smart_String Vertex::getName() const{
    return this -> name;
}
SmarterArray<Edge> Vertex::getEdgeSet() const{
    return this -> E;
}
int Vertex::getEdgeSetSize() const{
    return this -> E.getSize();
}
Edge Vertex::getEdge(const int &desVertexIndex) const{
    for (int i = 0; i < this -> getEdgeSetSize(); i++){
        if (this -> E[i].desVertexIndex == desVertexIndex) {
            return this -> E[i];
        }
    }
    assert(false);
}

double Vertex::getEdgeCost(const int &desVertexIndex) const{
    for (int i{0}; i < this -> getEdgeSetSize(); i++) {
        if (this -> E[i].desVertexIndex == desVertexIndex) {
            return this -> E[i].cost;
        }
    }
    assert(false);
}

void Vertex::appendEdge(const int &desVertexIndex, const double &cost){
    for (int i = 0; i < this -> getEdgeSetSize(); i++){
        assert(E[i].desVertexIndex == desVertexIndex);
    }
    Edge *temp = new Edge;
    temp -> desVertexIndex = desVertexIndex;
    temp -> cost = cost;
    this -> E.append(*temp);
}

ostream& operator << (ostream &out, const Vertex &vertex){
    out << "Name = " << vertex.name << endl;
    out << "Edge Set" << endl;
    for (int i = 0; i < vertex.E.getSize(); i++)
        out << "\t to ---> " << vertex.E[i].desVertexIndex << ", cost = " << vertex.E[i].cost << endl;
    return out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Graph
{
private:
    SmarterArray<Vertex> V;
public:
    Graph();//Construct empty graph
    Graph(const char *); //Construct a graph from a text file whose path is given by the argument
        //The text file input will consist in every line a pair of cities and the cost to go from one to
        //the other. The pair of cities and their cost will be separated by one or more SPACE or TAB
        //characters. It doesn't matter how many spaces or tabs are present. BUT THERE HAS TO BE AT LEAST
        //ONE TAB CHARACTER between the pairs of cities and AT LEAST ONE TAB between the second city and
        //the cost. This is because the CMPT135_String class uses TAB as a deliminator (separator). This
        //means city names can be made up of one or more words separated by spaces. An example of one line
        //of text in the input text file is:
        //        New Westminster             Port Coquitlam        4.5
        //In this example, there has to be at least one TAB char between "New Westminster" and "Port
        //Coquitlam" and at least one TAB character between "Port Coquitlam" and 4. Of course there can be
        //more than one TAB characters. The number of TABs can be equal or different. There are can be
        //zero or more spaces as much as you like without causing any problem. Moreover there can be as
        //many empty lines as one likes at the end of the file. However there MUST NOT BE any empty line
        //before the last line consisting of city pair and cost.
        /*
        Thus this function should perform the following tasks
1.    Construct a non-default file input streaming object using the argument file name
2.    Assert the file is opened successfully
3.    While EOF is not reached
a.    Read city name (CMPT135_String data type). This is the departure city.
b.    If departure city is empty CMPT135_String object, then break.
c.    Read city name (CMPT135_String data type). This is the destination city.
d.    Read the cost
e.    Append a new vertex whose name is the departure city and whose edge set is empty. You must use the appendVertex member function to append appropriately.
f.    Append a new vertex whose name is the destination city and whose edge set is empty. You must use the appendVertex member function to append appropriately.
g.    Append a new edge from the departure city to the destination city with a cost read in part (d) above.
h.    Append a new edge from the destination city to the departure city with a cost read in part (d) above.
4.    Close the input file stream object and you are done.
        */
    SmarterArray<Vertex> getVertexSet() const; //Return V
    int getVertexSetSize() const; //Return the number of elements of V
    Vertex getVertex(const int &) const; //Assert the index argument and then return the element at index
    int getVertexIndex(const Smart_String &) const; //Return the index of an element whose name matches                                                        //the argument. If no such element is found, return -1
                                                    //Assertion is not required
    int getVertexIndex(const Vertex &) const; //Return the index of the element whose name matches the
                                            //name of the vertex argument. If no such element is found,
                                            //return -1. Assertion is not required
    Smart_String getRandomVertexName() const; //Pick a vertex at random and return its name
    void appendVertex(const Vertex &); //Append the argument only if no such vertex already exists
                                        //If same name vertex already exists then do nothing (just return)
                                        //Assertion is not required
    void appendVertex(const Smart_String &); //Append a new vertex with the given name and empty E
    void appendEdge(const Smart_String &dep, const Smart_String &des, const double &cost); //Assert
//two vertices whose names match the arguments exist. Then append an edge to the vertex whose name matches
//the dep argument. The destination vertex index of the edge must be set to the index of the vertex whose
//name matches des and its cost must be set to the cost argument
    friend ostream& operator << (ostream &, const Graph &); //Implemented for you
};

Graph::Graph(){
    V.~SmarterArray();
}

Graph::Graph(const char *c){
    ifstream fin("Connectivity Map");
    assert(! fin.fail());
    Smart_String departureCity;
    Smart_String destinationCity;
    while(fin.eof() == false){
        fin >> departureCity;
        if (destinationCity == nullptr){
            break;
        }
        else{
            fin >> destinationCity;
            double cost;
            fin >> cost;
            this -> appendVertex(departureCity);
            this -> appendVertex(destinationCity);
            this -> appendEdge(departureCity, destinationCity, cost);
            this -> appendEdge(destinationCity, departureCity, cost);
        }
    }
    fin.close();
}

SmarterArray<Vertex> Graph::getVertexSet() const{
    return this -> V;
}

int Graph::getVertexSetSize() const{
    return this -> V.getSize();
}

Vertex Graph::getVertex(const int &index) const{
    assert(index <= this -> V.getSize());
    return this -> V[index];
}

int Graph::getVertexIndex(const Vertex &vertex) const{
    for (int i = 0; i < getVertexSetSize(); i++){
        if(this -> V[i].getName() == vertex.getName())
            return i;
    }
    return -1;
}

Smart_String Graph::getRandomVertexName() const{
    int num = rand() % (this -> V.getSize());
    return this -> V[num].getName();
}

void Graph::appendVertex(const Vertex &vertex){
    for(int i = 0; i < this -> V.getSize(); i++){
        if(this -> V[i].getName() == vertex.getName()){
            return;
        }
    }
    V.append(vertex);
}

void Graph::appendVertex(const Smart_String &name){
    for (int i = 0; i < this->V.getSize(); i++){
        if(V[i].getName() == name){
            return;
        }
    }
    Vertex temp(name);
    V.append(temp);
}


void Graph::appendEdge(const Smart_String &dep, const Smart_String &des, const double &cost){
    assert(this -> getVertexIndex(dep) != -1 && this -> getVertexIndex(des) != -1);
    for(int i = 0; i < this -> V.getSize(); i++){
        if(this -> V[i].getName() == dep){
            V[i].appendEdge(this -> getVertexIndex(des), cost);
        }
    }
}


ostream& operator << (ostream &out, const Graph &g){
    const int CITY_NAME_WIDTH = 25;
    out << endl;
    out << "The graph has " << g.getVertexSetSize() << " vertices." << endl;
    out << "These vertices are" << endl;
    for (int i = 0; i < g.getVertexSetSize(); i++)
    {
        Vertex v = g.V[i];
        out << "Vertex at index " << i << " = " << v.getName() << endl;
    }
    out << endl;
    out << "Each vertex together with its edge set looks like as follows" << endl;
    for (int i = 0; i < g.getVertexSetSize(); i++)
    {
        Vertex v = g.V[i];
        out << v << endl;
    }
    out << endl;
    out << "The graph connectivities are as follows..." << endl;
    out.setf(ios::fixed | ios::left);    //Left aligned fixed decimal places formatting
    for (int i = 0; i < g.getVertexSetSize(); i++)
    {
        Vertex depVertex = g.getVertex(i);
        SmarterArray<Edge> E = depVertex.getEdgeSet();
        for (int j = 0; j < E.getSize(); j++)
        {
            int desVertexIndex = E[j].desVertexIndex;
            Vertex desVertex = g.getVertex(desVertexIndex);
            out << depVertex.getName() << setw(CITY_NAME_WIDTH - depVertex.getName().length()) << " ";
            out << desVertex.getName() << setw(CITY_NAME_WIDTH - desVertex.getName().length()) << " ";
            out << setprecision(2) << E[j].cost << endl;
        }
    }
    out.unsetf(ios::fixed | ios::left);    //Removing formatting
    cout.precision(0);                    //Resetting the decimal places to default
    return out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Path{
private:
    SmarterArray<Smart_String> p; //The names of the vertices along the path

public:
    Path(); //Construct an empty path

    int length() const; //Return the number of vertices in the path (the number of elements of p)
    int find(const Smart_String &) const; //Return the index of element of p whose name matches the
                                            //argument. If no element satisfies the condition, then return -1
    double computePathCost(const Graph &) const; //Compute the sum of the costs of edges along this path
                                            //given the underlying graph argument
    Smart_String& operator [] (const int &) const; //Assert index is valid and then return the
                                            //element of p at the given index
    void append(const Smart_String &); //Append the argument to the calling object
    void insert(const int &index, const Smart_String &); //Assert the condition index >= 0 &&
                                            //index <= the length and then insert the CMPT135_String argument
                                            //at the specified index
    void remove(const int &); //Assert the index argument and then remove the element at the specified index
    friend ostream& operator << (ostream &, const Path &); //Implemented for you.
};

Path::Path(){
}

int Path::length() const{
    return this -> p.getSize();
}
int Path::find(const Smart_String &c) const{
    for (int i{0}; i < this -> p.getSize(); i++) {
        if (this -> p[i] == c) {
            return i;
        }
    }
    return -1;
}
double Path::computePathCost(const Graph &g) const{
    double cost{0};
    SmarterArray<Vertex> V = g.getVertexSet();
    for (int i = 0; i < this -> p.getSize() - 1; i++)
    {
        int depIndex = g.getVertexIndex(this -> p[i]);
        int desIndex = g.getVertexIndex(this -> p[i+1]);
        if(g.getVertexIndex(this -> p[i]) == -1 || g.getVertexIndex(this -> p[i+1]) == -1)
        {
            cout << "ERROR!!!" << endl;
            abort();
        }
        cost += V[depIndex].getEdgeCost(desIndex);
    }
    return cost;
}

Smart_String& Path::operator[](const int &index) const{
    assert(index >= 0 && index < length());
    return this -> p[index];
}
void Path::append(const Smart_String &c){
    this -> p.append(c);
}

void Path::insert(const int &index, const Smart_String &c){
    assert(index >= 0 && index <= length());
    if (index == length()) {
        this -> p.append(c);
        return;
    }
    this -> p.insert(index, c);
}

void Path::remove(const int &index){
    assert(index >= 0 && index <= length());
    this -> p.remove(index);
}

ostream& operator << (ostream &out, const Path &p)
{
    out << "[";
    if (p.length() > 0)
    {
        for (int i = 0; i < p.length()-1; i++)
            out << p[i] << " -> ";
        out << p[p.length()-1];
    }
    out << "]";
    return out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    /*srand(time(0));
    Graph g("Connectivity Map.txt");
    cout << "Graph constructed successfully." << endl;
    cout << g << endl;

    CMPT135_String departure = g.getRandomVertexName();
    CMPT135_String destination = g.getRandomVertexName();
    cout << "Computing shortest path from " << departure << " to " << destination << endl;
    //Path minCostPath = computeMinCostPath(g, departure, destination);
    cout << endl;
    cout << "Departure: " << departure << endl;
    cout << "Destination: " << destination << endl;
    if (minCostPath.length() == 0)
        cout << "No path found." << endl;
    else
        cout << "The minimum cost path is: " << minCostPath << " with cost = " << minCostPath.computePathCost(g) << endl;
    
    system("Pause");*/
    return 0;
}
